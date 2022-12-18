#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Runtime.h"

size_t
Executive_String_length(const char *str)
{
	size_t c;

	ExAssert(NULL != str);
	for(c = 0; str[c]; c++)
	{
	}
/*	EXLOGF((LOG_TRACE, "Executive_String_length('%s') = %u", str, c)); */
	return c;
}

char *
Executive_String_duplicate(const char *str)
{
	ExAssert(NULL != str);
	return (char *) Executive_Memory_duplicate(str, Executive_String_length(str) + 1);
}

const char *
Executive_String_pos(const char *str, int ch)
{
	ExAssert(NULL != str);
	for(; *str; str++)
	{
		if(*str == ch)
		{
			return str;
		}
	}
	return NULL;
}

int
Executive_String_equal(const char *a, const char *b)
{
	ExAssert(NULL != a);
	ExAssert(NULL != b);
	
	for(; *a && *b; ++a, ++b)
	{
		if(*a != *b)
		{
			return 0;
		}
	}
	if(*a != *b)
	{
		return 0;
	}
	return 1;
}

int
Executive_String_lequal(const char *a, const char *b, size_t max)
{
	ExAssert(NULL != a);
	ExAssert(NULL != b);
	
	for(; *a && *b && max; ++a, ++b)
	{
		max--;
		if(*a != *b)
		{
			return 0;
		}
	}
	if(!max)
	{
		return 1;
	}
	if(*a != *b)
	{
		return 0;
	}
	return 1;
}

size_t
Executive_String_lcopy(char *dest, size_t size, const char *src, size_t max)
{
	size_t count;

	for(count = 0; size > 1 && max && src; count++)
	{
		*dest = *src;
		dest++;
		src++;
		size--;
		max--;
		dest[0] = 0;
	}
	return count;
}
