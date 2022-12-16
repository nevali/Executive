#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Runtime.h"

static struct { STATUS status; const char *name; const char *msg; } statusMap[] = {
	{ E_SUCCESS, "%SUCCESS", "The operation completed successfully" },

	{ E_BADOBJ, "%E-BAD-OBJECT", "An invalid object descriptor was specified" },
	{ E_NOTIMPL, "%E-NOT-IMPL", "Interface is not implemented" },
	{ E_INVAL, "%E-BAD-PARAM", "Request parameter is invalid" },

	{ E_PERM, "%E-PERM", "Operation not permitted" },
	{ E_ACCESS, "%E-ACCESS", "Access denied" },
	{ E_NOENT, "%E-NOENT", "The specified object does not exist" },
	{ E_EXISTS, "%E-EXISTS", "The specified object already exists" },
	{ E_EOF, "%E-EOF", "End of file reached" },
	{ E_NOT_CONTAINER, "%E-NOT-CONTAINER", "The specified object is not a container" },
	{ E_NOMEM, "%E-NOMEM", "Out of memory" },

	{ E_IO, "%E-IO", "I/O error" },
	
	{ 0, NULL, NULL }
};

const char *
Executive_Status_name(STATUS s)
{
	size_t c;

	if(s >= 0)
	{
		return statusMap[0].name;
	}
	for(c = 0; statusMap[c].name; c++)
	{
		if(statusMap[c].status == s)
		{
			return statusMap[c].name;
		}
	}
	return "%E-UNKNOWN";
}

const char *
Executive_Status_defaultMessage(STATUS s)
{
	size_t c;

	if(s >= 0)
	{
		return statusMap[0].msg;
	}
	for(c = 0; statusMap[c].name; c++)
	{
		if(statusMap[c].status == s)
		{
			return statusMap[c].msg;
		}
	}
	return "Unknown error";
}
