/* Executive Microkernel
 * Runtime Framework
 *   This framework provides low-level user-space APIs to applications, via
 *   the Executive's system call mechanism
 */

/* Copyright 2015-2022 Mo McRoberts.
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

#ifndef P_UUIDS_H_
# define P_UUIDS_H_                    1

# define INITGUID_EXTERN               1

# include <Executive/UUID.h>

# include <Runtime/Internal/Classes.h>

/* Included in the Executive */

# include <PAL/Platform.h>
# include <PAL/PlatformDiagnostics.h>
# include <PAL/MemoryManager.h>
# include <PAL/BootEnvironment.h>
# include <Executive/Classes.h>
# include <Executive/MObject.h>
# include <Executive/MDirectoryEntryTarget.h>
# include <Executive/MFactory.h>
# include <Executive/IObject.h>
# include <Executive/IAllocator.h>
# include <Executive/IRegionHolder.h>
# include <Executive/IBootEnvironment.h>
# include <Executive/IDirectoryEntryTarget.h>
# include <Executive/IPlatform.h>
# include <Executive/IPlatformDiagnostics.h>
# include <Executive/ISubsystem.h>
# include <Executive/ITasker.h>
# include <Executive/INamespace.h>
# include <Executive/ITask.h>
# include <Executive/IThread.h>
# include <Executive/IAddressSpace.h>
# include <Executive/IRegion.h>
# include <Executive/IWriteChannel.h>
# include <Executive/IContainer.h>
# include <Executive/IMutableContainer.h>
# include <Executive/IDirectoryEntry.h>
# include <Executive/ILink.h>
# include <Executive/IIterator.h>
# include <Executive/IExecutable.h>

/* User-space only */

# include <Executive/IContext.h>

#endif /*!P_UUIDS_H_*/
