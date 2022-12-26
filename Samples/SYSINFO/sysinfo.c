/* Executive Microkernel
 * SYSINFO
 *  Report information about the system
 */

#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
# include "BuildInformation.h"
# include "ProductInformation.h"
#endif

#include <Runtime/Runtime.h>

#include <Executive/ILink.h>

#define RTLOGF(P) RtLogFormat P

static void dumpDir(IContainer *self, const char *name, int depth);

STATUS
mainThread(IThread *self)
{
	STATUS status;
	IContainer *root;

	UNUSED__(self);

#ifdef EXEC_BUILD_CONFIG
	RtLog(LOG_NOTICE, PRODUCT_FULLNAME " SYSINFO [" EXEC_BUILD_CONFIG " build " PRODUCT_BUILD_ID_STR "]");
#else
	RtLog(LOG_DEBUG, PRODUCT_FULLNAME " SYSINFO [build " PRODUCT_BUILD_ID_STR "]");
#endif

	if(E_SUCCESS == (status = RtOpenAs("/", &IID_IContainer, (void **) &root)))
	{
		dumpDir(root, "/", 0);
		IContainer_release(root);
	}
	else
	{
		RtLog(LOG_WARNING, "SYSINFO: failed to open root directory as <IContainer>");
	}
	return E_SUCCESS;
}

static void
dumpDir(IContainer *self, const char *name, int depth)
{
	size_t c;
	char ename[64], space[80], flagsbuf[16];
	UUID clsid;
	UUIDBUF cbuf;
	const char *cname;
	DirectoryEntryFlags flags;
	IIterator *iterator;
	IObject *current;
	IDirectoryEntry *dirent;
	IContainer *container;
	ILink *link;

	UNUSED__(name);
	
	for(c = 0; c < sizeof(space)-1 && c < (size_t) depth; c++)
	{
		space[c] = '-';
	}
	space[c] = 0;
	if(c > 1)
	{
		space[c - 1] = ' ';
	}
	iterator = IContainer_iterator(self);
	if(!iterator)
	{
		RTLOGF((LOG_DEBUG, "DEBUG: container '%s' does not provide an iterator", name));
		return;
	}
	do
	{
		current = IIterator_current(iterator);
		if(!current)
		{
			break;
		}
		if(E_SUCCESS != IObject_queryInterface(current, &IID_IDirectoryEntry, (void **) &dirent))
		{
			RTLOGF((LOG_WARNING, "WARNING: failed to obtain directory entry from iterator"));
			IObject_release(current);
			continue;
		}
		IObject_release(current);
		IDirectoryEntry_classid(dirent, &clsid);
		RtUuidStr(&clsid, cbuf);
/*		cname = Executive_nameOfClass(&clsid);
		if(!cname) */
		{
			cname = cbuf;
		}
		flags = IDirectoryEntry_flags(dirent);
		flagsbuf[0] = (flags & DEF_IMMUTABLE ? '!' : '-');
		flagsbuf[1] = (flags & DEF_SYSTEM ? 's' : '-');
		flagsbuf[2] = (flags & DEF_HIDDEN ? 'h' : '-');
		if(flags & DEF_VOID)
		{
			flagsbuf[3] = '?';
		}
		else if(flags & DEF_LINK)
		{
			flagsbuf[3] = '@';
		}
		else if(flags & DEF_MOUNTPOINT)
		{
			flagsbuf[3] = '#';
		}
		else if(flags & DEF_CONTAINER)
		{
			flagsbuf[3] = '+';
		}
		else
		{
			flagsbuf[3] = '-';
		}
		flagsbuf[4] = 0;
		IDirectoryEntry_name(dirent, ename, sizeof(ename));
		if((flags & DEF_LINK) && E_SUCCESS == IDirectoryEntry_queryTargetInterface(dirent, &IID_ILink, (void **) &link))
		{
			RTLOGF((LOG_NOTICE, "%42s %s  %s%s -> %s", cname, flagsbuf, space, ename, ILink_target(link)));
			ILink_release(link);
		}
		else
		{
			RTLOGF((LOG_NOTICE, "%42s %s  %s%s", cname, flagsbuf, space, ename));
		}
		if((flags & DEF_CONTAINER) && E_SUCCESS == IDirectoryEntry_queryTargetInterface(dirent, &IID_IContainer, (void **) &container))
		{
			dumpDir(container, ename, depth + 2);
			IContainer_release(container);
		}
		IDirectoryEntry_release(dirent);
	}
	while(E_SUCCESS == IIterator_next(iterator));
	IIterator_release(iterator);
}
