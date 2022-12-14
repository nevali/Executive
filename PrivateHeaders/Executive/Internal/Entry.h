#ifndef EXECUTIVE_INTERNAL_ENTRY_H_
# define EXECUTIVE_INTERNAL_ENTRY_H_

# include <Executive/Linkage.h>
# include <Executive/Types.h>
# include <Executive/Errors.h>
# include <Executive/UUID.h>

typedef enum
{
	EEF_HAVE_ARGS = (1<<0),
	EEF_HAVE_ENVIRON = (1<<1),
	EEF_HAVE_PAL_METACLASS = (1<<2),
	EEF_HAVE_HOSTID = (1<<3),
	EEF_HAVE_HOSTUUID = (1<<4)
} ExecutiveEntryFlags;

struct ExecutiveEntryParameters
{
	ExecutiveEntryFlags flags;
	int argc;
	char **argv;
	char **environ;
	int (*PAL_metaClass)(REFUUID clsid, REFUUID iid, void **out);
	char hostid[64];
	UUID hostuuid;
};

void Executive_start(struct ExecutiveEntryParameters *params) EXEC_LINKAGE__(__start, "0.0");

#endif /*EXECUTIVE_INTERNAL_ENTRY_H_*/