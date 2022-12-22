/* Runtime utilities 
 */

#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Runtime.h"

bool
RtUuidEqual(REFUUID a, REFUUID b)
{
	RTASSERT(a != NULL);
	RTASSERT(b != NULL);

	if(a->d.d1 != b->d.d1 ||
		a->d.d2 != b->d.d2 ||
		a->d.d3 != b->d.d3 ||
		a->d.d4 != b->d.d4)
	{
		return false;
	}
	return true;
}

size_t
RtUuidStr(REFUUID uuid, UUIDBUF buf)
{
	if(!uuid)
	{
		return RtStrCopy(buf, sizeof(UUIDBUF), "<NULL>");
	}
	return RtStrBufFormat(buf, sizeof(UUIDBUF), "{ %08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x }",
		uuid->uuid.time_low, uuid->uuid.time_mid, uuid->uuid.time_hi_and_version,
		uuid->uuid.clock_seq_hi_and_reserved, uuid->uuid.clock_seq_low,
		uuid->uuid.node[0], uuid->uuid.node[1], uuid->uuid.node[2],
		uuid->uuid.node[3], uuid->uuid.node[4], uuid->uuid.node[5]);
}

void
RtUuidCopy(UUID *dest, REFUUID src)
{
	RtMemCopy(dest, src, sizeof(UUID));
}
