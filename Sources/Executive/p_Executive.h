/* Executive Microkernel
 * Sources/Executive/p_Executive.h
 */

/* Copyright (c) 2022 Mo McRoberts.
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

/* Prevent multiple inclusions */
#ifndef P_EXECUTIVE_H_
# define P_EXECUTIVE_H_        1

/* */
# define INITGUID_EXTERN       1

# include <stddef.h>

# include <PAL/PAL.h>

# include <Executive/Internal/Entry.h>
# include <Executive/Internal/Runtime.h>
# include <Executive/Internal/Classes.h>
# include <Executive/Internal/Directory.h>

# include <Executive/IAllocator.h>
# include <Executive/IBootEnvironment.h>
# include <Executive/IPlatformDiagnostics.h>

# include <Executive/IIterator.h>

# include <Executive/IContainer.h>
# include <Executive/INamespace.h>
# include <Executive/IMutableContainer.h>
# include <Executive/IDirectoryEntry.h>
# include <Executive/IDirectoryEntryTarget.h>
# include <Executive/ILink.h>

# include <Executive/IWriteChannel.h>

# include <Executive/ISubsystem.h>

# include <Executive/ITasker.h>
# include <Executive/ITask.h>
# include <Executive/IThread.h>
# include <Executive/IJob.h>
# include <Executive/IEvent.h>

# include <Executive/MObject.h>
# include <Executive/MFactory.h>
# include <Executive/MDirectoryEntryTarget.h>

# include <Executive/Classes.h>

# include <Executive/Internal/Executive.h>

# if FEATURE_BOOTPROGRESS
#  define PROGRESS_LOGLEVEL            LOG_INFO
# else
#  define PROGRESS_LOGLEVEL            LOG_DEBUG
# endif

typedef union Executive_BootEnvironment Executive_BootEnvironment;
typedef struct Executive_CooperativeTasker Executive_CooperativeTasker;
typedef union Executive_CooperativeTasker_Task Executive_CooperativeTasker_Task;
typedef union Executive_CooperativeTasker_Thread Executive_CooperativeTasker_Thread;

# ifdef __cplusplus
extern "C" {
# endif

extern struct IObject_vtable_ Executive_IObject_vtable;
extern struct IContainer_vtable_ Executive_IContainer_vtable;
extern struct IDirectoryEntryTarget_vtable_ Executive_IDirectoryEntryTarget_vtable;

extern IBootEnvironment *Executive_BootEnvironment_create(void);

extern ITasker *Executive_CooperativeTasker_create(void);

extern void Executive_init_sysContainer(void);

# ifdef __cplusplus
}
# endif

#endif /*!P_EXECUTIVE_H_*/
