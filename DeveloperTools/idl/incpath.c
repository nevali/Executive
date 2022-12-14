/* Copyright (c) 2008-2015 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "p_comidl.h"

/* This is horribly inefficient, but it doesn't really need to be optimised */

typedef struct incpath_struct incpath_t;

struct incpath_struct
{
	char *path;
	int is_framework;
};

static incpath_t **incpath;
static size_t nincpath;

static incpath_t *
incpath_add(const char *path, int isfw)
{
	incpath_t **q, *p;
	size_t l;
	
	if(NULL == (q = (incpath_t **) realloc(incpath, sizeof(incpath_t *) * (nincpath + 1))))
	{
		return NULL;
	}
	incpath = q;
	if(NULL == (p = (incpath_t *) calloc(1, sizeof(incpath_t))))
	{
		return NULL;
	}
	l = strlen(path);
	if(NULL == (p->path = (char *) calloc(1, l + 2)))
	{
		free(p);
		return NULL;
	}
	strcpy(p->path, path);
	if(0 == l || '/' != p->path[l - 1])
	{
		p->path[l] = '/';
		p->path[l + 1] = 0;
	}
	p->is_framework = isfw;
	q[nincpath] = p;
	nincpath++;
	return p;
}

int
idl_incpath_reset(void)
{
	size_t c;
	
	for(c = 0; c < nincpath; c++)
	{
		free(incpath[c]->path);
		free(incpath[c]);
	}
	free(incpath);
	incpath = NULL;
	nincpath = 0;
	return 0;
}

int
idl_incpath_add_includedir(const char *path)
{
	if(NULL == incpath_add(path, 0))
	{
		return -1;
	}
	return 0;
}

int
idl_incpath_add_frameworkdir(const char *path)
{
	if(NULL == incpath_add(path, 1))
	{
		return -1;
	}
	return 0;
}

int
idl_incpath_locate(char *buf, size_t buflen, const char *path)
{
	size_t c;
	char pathbuf[PATH_MAX + 1];
	struct stat sbuf;
	
	/* Look in the most recently-added locations first */
	for(c = nincpath; c; c--)
	{
		if(strlen(incpath[c - 1]->path) + strlen(path) > PATH_MAX)
		{
			fprintf(stderr, "%s: %s%s: path too long\n", progname, incpath[c - 1]->path, path);
			continue;
		}
		strcpy(pathbuf, incpath[c - 1]->path);
		strcat(pathbuf, path);
		if(0 == stat(pathbuf, &sbuf))
		{
			if(strlen(pathbuf) + 1 > buflen)
			{
				fprintf(stderr, "%s: %s: path too long\n", progname, pathbuf);
				return -1;
			}
			strcpy(buf, pathbuf);
			return 0;
		}
	}
	return -1;
}
