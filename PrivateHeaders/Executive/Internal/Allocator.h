#ifndef EXECUTIVE_INTERNAL_ALLOCATOR_H_
# define EXECUTIVE_INTERNAL_ALLOCATOR_H_

# include <Executive/IAllocator.h>
# include <Executive/IAddressSpace.h>

typedef union Executive_Allocator Executive_Allocator;

extern IAllocator *Executive_Allocator_create(IAddressSpace *addressSpace);

extern void *Executive_Allocator_map(Executive_Allocator *me, size_t size, RegionFlags flags);
extern int Executive_Allocator_unmap(Executive_Allocator *me, void *addr, size_t size);

#endif /*EXECUTIVE_INTERNAL_ALLOCATOR_H_*/
