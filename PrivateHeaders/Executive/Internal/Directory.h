/* Executive Microkernel
 *   PrivateHeaders/Executive/Internal/Directory.h
 */

/* Copyright (c) 2015-2022 Mo McRoberts.
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

#ifndef EXECUTIVE_INTERNAL_DIRECTORY_H_
# define EXECUTIVE_INTERNAL_DIRECTORY_H_ 1

# include <Executive/IContainer.h>
# include <Executive/IMutableContainer.h>
# include <Executive/IDirectoryEntry.h>
# include <Executive/IDirectoryEntryTarget.h>
# include <Executive/INamespace.h>
# include <Executive/ILink.h>

# include <Executive/MObject.h>
# include <Executive/MFactory.h>
# include <Executive/MDirectoryEntryTarget.h>

typedef struct Executive_Directory Executive_Directory;
typedef struct Executive_Directory_Entry Executive_Directory_Entry;
typedef union Executive_Directory_Iterator Executive_Directory_Iterator;
typedef struct Executive_Directory_Link Executive_Directory_Link;

/** Executive::DirectoryKind **/

typedef enum
{
	/* generic (user) container */
	DK_CONTAINER = 0,
	/* Root container */
	DK_ROOT,
	/* (User) domain container */
	DK_DOMAIN,
	/* System domain container */
	DK_SYSTEM,
	/* Local domain container */
	DK_LOCAL,
	/* Cluster domain container */
	DK_CLUSTER,
	/* Network Domain container */
	DK_NETWORK
} DirectoryKind;


/* Metaclasses */

/* This callback, registered in Classes.c, is the only "public" interface */
STATUS Executive_Directory_metaClass(REFUUID clsid, REFUUID iid, void **out);

extern struct MObject_vtable_ Executive_Directory_MetaClass_MObject_vtable;
extern struct MFactory_vtable_ Executive_Directory_MetaClass_MFactory_vtable;
extern struct MDirectoryEntryTarget_vtable_ Executive_Directory_MetaClass_MDirectoryEntryTarget_vtable;

/** Executive::Directory **/

/* virtual method tables */
extern const struct IObject_vtable_ Executive_Directory_IObject_vtable;
extern const struct IContainer_vtable_ Executive_Directory_IContainer_vtable;
extern const struct IMutableContainer_vtable_ Executive_Directory_IMutableContainer_vtable;
extern const struct INamespace_vtable_ Executive_Directory_INamespace_vtable;
extern const struct IDirectoryEntryTarget_vtable_ Executive_Directory_IDirectoryEntryTarget_vtable;

/* IObject */
STATUS Executive_Directory_queryInterface(IObject *me, REFUUID iid, void **out);
REFCOUNT Executive_Directory_retain(IObject *me);
REFCOUNT Executive_Directory_release(IObject *me);
/* IContainer */
STATUS Executive_Directory_resolve(IContainer *me, const char *name, IDirectoryEntry **entry);
IIterator *Executive_Directory_iterator(IContainer *me);
/* IMutableContainer */
STATUS Executive_Directory_IMutableContainer_create(IMutableContainer *me, const char *name, REFUUID clsid, REFUUID iid, void **out);
STATUS Executive_Directory_add(IMutableContainer *me, const char *name, REFUUID clsid, IObject *target);
STATUS Executive_Directory_createLink(IMutableContainer *me, const char *name, const char *target, bool force);

/* INamespace */
STATUS Executive_Directory_resolveEntry(INamespace *me, const char *path, IContainer *scope, IDirectoryEntry **dentry);
STATUS Executive_Directory_resolveContainer(INamespace *me, const char *path, IContainer *scope, IContainer **container, const char **basename);
STATUS Executive_Directory_open(INamespace *me, const char *path, IContainer *scope, REFUUID iid, void **out);
STATUS Executive_Directory_INamespace_create(INamespace *me, const char *path, IContainer *scope, REFUUID clsid, REFUUID iid, void **out);
STATUS Executive_Directory_INamespace_add(INamespace *me, const char *path, IContainer *scope, REFUUID clsid, IObject *target);
STATUS Executive_Directory_INamespace_createLink(INamespace *me, const char *path, IContainer *scope, const char *target, bool force);
STATUS Executive_Directory_INamespace_setFlags(INamespace *me, const char *path, IContainer *scope, DirectoryEntryFlags flags);

/* IDirectoryEntryTarget */
void Executive_Directory_linked(IDirectoryEntryTarget *me, IDirectoryEntry *entry);
void Executive_Directory_unlinked(IDirectoryEntryTarget *me, IDirectoryEntry *entry);

/** Executive::Directory::Entry **/
Executive_Directory_Entry *Executive_Directory_Entry_create(const char *name, REFUUID clsid, DirectoryEntryFlags flags);

void Executive_Directory_dump(IContainer *me);

/** Executive::Directory::Iterator */
Executive_Directory_Iterator *Executive_Directory_Iterator_create(Executive_Directory_Entry *dirent);

/** Executive::Directory::Link */
Executive_Directory_Link *Executive_Directory_Link_create(const char *target);

#endif /*!EXECUTIVE_INTERNAL_DIRECTORY_H_*/