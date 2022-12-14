#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Runtime.h"

void *
Executive_Memory_duplicate(const void *src, size_t nbytes)
{
	void *p;

	ExAssert(src);
	if(NULL == (p = ExAlloc(nbytes)))
	{
		EXLOGF((LOG_CONDITION, "%%E-NOMEM: Executive::Memory::duplicate(): ExAlloc(%u) failed", nbytes));
		return NULL;
	}
	Executive_Memory_copy(p, src, nbytes);
	return p;
}

void
Executive_Memory_copy(void *dest, const void *src, size_t nbytes)
{
	size_t si;
	const uint8_t *sp = (const uint8_t *) src;
	uint8_t *dp = (uint8_t *) dest;

	for(si = 0; si < nbytes; si++)
	{
		dp[si] = sp[si];
	}
}
