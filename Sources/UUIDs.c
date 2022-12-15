#include "p_Executive.h"

#define INITGUID
#include <Executive/initguid.h>

#include <Executive/MObject.h>
#include <Executive/MFactory.h>

#include <Executive/IObject.h>
#include <Executive/IMemoryManager.h>
#include <Executive/IRegion.h>
#include <Executive/IRegionHolder.h>
#include <Executive/IAllocator.h>
#include <Executive/IPlatform.h>
#include <Executive/IPlatformDiagnostics.h>
#include <Executive/IBootEnvironment.h>

#include <Executive/IIterator.h>

#include <Executive/IContainer.h>
#include <Executive/INamespace.h>
#include <Executive/IMutableContainer.h>
#include <Executive/IDirectoryEntry.h>
#include <Executive/IDirectoryEntryTarget.h>
#include <Executive/ILink.h>

#include <Executive/IWriteChannel.h>

#include <Executive/ITasker.h>
#include <Executive/ITask.h>
#include <Executive/IThread.h>
#include <Executive/IJob.h>
#include <Executive/IEvent.h>

#include <Executive/MDirectoryEntryTarget.h>

#include <Executive/Classes.h>

#include <PAL/Platform.h>
#include <PAL/BootEnvironment.h>
#include <PAL/MemoryManager.h>
#include <PAL/PlatformDiagnostics.h>
