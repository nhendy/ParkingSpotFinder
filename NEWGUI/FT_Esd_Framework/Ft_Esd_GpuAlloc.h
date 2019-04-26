/*

Allocation mechanism for RAM_G.

Allocation returns a handle, consisting part of the allocation index and a sequence code to invalidate the allocation.
Handle can be turned into an address using Ft_Esd_GpuAlloc_Get. This call should be repeated each frame,
since the allocation may be invalidated by a graphics device reset, or the allocation may be moved by a memory
defragmentation process.
Supports up to MAX_NUM_ALLOCATIONS simultaneous allocations.

*/

#ifndef FT_ESD_GPUALLOC_H
#define FT_ESD_GPUALLOC_H

#include "FT_DataTypes.h"

#define MAX_NUM_ALLOCATIONS 64UL

// Set the GC flag. This automatically frees the allocation when the USED flag is not set during Update.
// Using this flag means you must call Ft_Esd_GpuAlloc_Get on each frame to keep the allocation alive
#define GA_GC_FLAG 1

// Used flag is set whenever Ft_Esd_GpuAlloc_Get is called, reset on every Update
#define GA_USED_FLAG 2

// Handle to a gpu memory allocation
typedef struct
{
	/// Id in the allocation reference table
	ft_uint16_t Id;
	/// Sequence number used to invalidate handles
	ft_uint16_t Seq;

} Ft_Esd_GpuHandle;

// Internal information about a gpu memory allocation handle
typedef struct
{
	ft_uint16_t Idx;
	ft_uint16_t Seq;

} Ft_Esd_GpuAllocRef;

// Internal gpu allocation entry
typedef struct
{
	ft_uint32_t Address;
	ft_uint32_t Length;
	ft_uint16_t Id;
	ft_uint16_t Flags;

} Ft_Esd_GpuAllocEntry;

typedef struct
{
	/// Reference to an allocation entry, by allocation Id
	Ft_Esd_GpuAllocRef AllocRefs[MAX_NUM_ALLOCATIONS];
	/// Allocation map, 
	Ft_Esd_GpuAllocEntry AllocEntries[MAX_NUM_ALLOCATIONS];
	/// Number of valid alloc entries
	ft_uint32_t NbAllocEntries;

} Ft_Esd_GpuAlloc;

// Initialize or reset gpu ram allocation mechanism
void Ft_Esd_GpuAlloc_Reset(Ft_Esd_GpuAlloc *ga);

// Run basic garbage collection and any other mechanisms, call first in the Update cycle, after the frame is fully rendered and swapped
void Ft_Esd_GpuAlloc_Update(Ft_Esd_GpuAlloc *ga);

// Allocate a gpu ram block
Ft_Esd_GpuHandle Ft_Esd_GpuAlloc_Alloc(Ft_Esd_GpuAlloc *ga, ft_uint32_t size, ft_uint16_t flags);

// Free a gpu ram block
void Ft_Esd_GpuAlloc_Free(Ft_Esd_GpuAlloc *ga, Ft_Esd_GpuHandle handle);

// Get ram address from handle. Returns ~0 when invalid.
ft_uint32_t Ft_Esd_GpuAlloc_Get(Ft_Esd_GpuAlloc *ga, Ft_Esd_GpuHandle handle);

// Get total used GPU RAM
ft_uint32_t Ft_Esd_GpuAlloc_GetTotalUsed(Ft_Esd_GpuAlloc *ga);

// Get total GPU RAM
ft_uint32_t Ft_Esd_GpuAlloc_GetTotal(Ft_Esd_GpuAlloc *ga);

#ifndef NDEBUG
void Ft_Esd_GpuAlloc_Print(Ft_Esd_GpuAlloc *ga);
#else
#define Ft_Esd_GpuAlloc_Print(ga) do { } while (0)
#endif

#endif /* #ifndef FT_ESD_GPUALLOC_H */

/* end of file */
