# Executive

An experimental minimal microkernel.

[![Apache 2.0 licensed][license]](#license)
![Implemented in C][language]

## Top of the pile

* Signals / despatch / process contexts for callbacks
* Reserved descriptors
* External tasks flag
* Tasker should return to caller when no tasks available
* POSIX: check signal handling setup in thread creation
* POSIX: check timing of naps and ticks
* PAL: platform timer

* Build: --enable-native-glue (build native glue on hosted build if one is available)

* Runtime: libc - implement a basic c90 libc (no descriptors, only streams, no fork, etc.)

* POSIX: plain vs curses Console

* Short-cuts feature flag -- whether inter-module access is strictly via accessors, or direct access to data structures


## Introduction

The _Executive_ is an experimental minimal microkernel that aims to be
portable, useful, and lightweight. The Executive is so named not because
it governs everything, but because it facilitates and only works well when it
_delegates_.

## Design goals

### Lightweight

### Portable

### Flexible

### Modern

## Platforms and builds

The Executive can be built in a number of different ways, dependent upon
the target platform.

:
:

The following special `ABI` values are recognised by `configure`:

* `native` - build a "native" build for the host operating system; that is, no standard libraries are used
* `kernel` - build as a kernel extension (module, device driver) for the host operating system
* `ntapi` - (Windows only) - build an "NT Native API" executable
* `service` - (Windows only) - build a Windows Service executable

Depending upon the target platform and ABI, your build may result in a number
of different Executive executables being generated

## Operation

The Executive begins life as a single-user, single-processor, single-tasking
operating system with no memory protection, executing in a privileged
processor mode (e.g., on x86, in Ring 0). It, coupled with a Platform
Adaptation Layer (PAL), provide a limited set of core system services which
can be used to bootstrap a more complete and functional system.

Although the Executive itself is a single-tasking microkernel, it nevertheless
knows what tasks and threads are, and manages the data structures required by
a multitasking system. The same applies to processors, devices, user and group
security, memory protection, paging, and so on.

In all of these cases, although the Executive (or PAL) may provide a minimal
stub implementation with limited functionality, its role is primarily
intended to be that of a facilitator and book-keeper, with the responsibility
for actually doing the work handed over to other components of the system.

To make this possible, the Executive defines an binary interface (ABI),
a set of programming interfaces (APIs), and maintains an extensible tree-like
model of the system, known as the _Object Directory_, which is very loosely
analogous to a virtual filesystem.

Because the Executive does not include memory protection or other common
features, any executables it launches are inherently privileged processes:
essentially equivalent to a kernel thread in a modern monolithic kernel
such as Linux. The Executive itself will therefore only permit
cryptographically-signed executables to be launched, allowing the integrity of
the system to be maintained whilst allowing for extreme modularity and
flexibility.

## Initialisation

The way that the Executive's executable is loaded and control transferred to
it is governered by the target platform. For a _hosted_ or _native_ build,
the host operating system is responsible for starting the Executive. For a
_freestanding_ build, it's a bootloader, whether that be one embedded into
firmware (real or virtualised), or an additional software component.

### Glue

Regardless of how the Executive is mapped or copied into memory and control
transferred to it, initialisation begins within the _Glue_, a small module
which is statically-linked into the start of Executive binary. The Glue
isn't specific to the platform, but rather to the pre-boot environment. For
example, all UEFI-based platforms can use the same Glue code, which can then
be compiled once for each architecture.

The name (and address) of the symbol within the Glue that is considered to be
the Executive's entry-point varies. For _hosted_ builds, i.e., those
generating an executable intended to be used within another operating system,
and using that operating system's standard libraries, it will be `main()` or
`WinMain()`. For _native_ builds, which are similar but do _not_ use the
standard libraries, it may be something like `__start`. For _freestanding_
builds, those intended to be started via a bootloader, it's dependent
upon the bootloader's needs, defaulting to `__glue_entry` if nothing else
dictates otherwise. Necessarily, and supported by the build system, the
Glue is accompanied by a set of configuration specifying compiler and
linker flags to be used to build the Executive.

The function invoked as the Glue's entry-point assembles information provided
to it by the bootloader, such as command-line arguments and firmware variables,
into a structure understood by the Executive, and then transfers control to the
Executive's own entry-point, `Executive()`.

### Platform Adaptation Layer

The Executive's entry-point immediately performs initialisation of the Platform
Adaptation Layer, or PAL, by calling its `PAL_queryPlatformInterface()` function
to obtain a pointer to a structure (an interface pointer) whose first member is
a pointer to a virtual method (despatch) table conforming to the `IPlatform`
COM interface (canonically defined in [IDL/PAL/IPlatform.idl](IDL/PAL/Platform.idl)).

When the Executive invokes `PAL_queryPlatformInterface()`, typically a
relatively small number of instructions since the bootloader transferred
control to the Glue, the PAL has the opportunity to perform any early
platform-specific initialisation. This could conceivably include initialising
a serial console interface for diagnostic output (provided doing so doesn't
require any dynamic memory allocation!)

Once the PAL has been initialised, it returns a pointer to its prepared
`IPlatform` interface to the Executive.

The PAL may include bundled platform-specific versions of some objects, such
as the memory manager. The Executive determines if this is the case via
`IPlatform` method calls during its initialisation.

### Executive initialisation

Once the PAL has been initialised and an `IPlatform` interface pointer has been
supplied to the Executive, it can begin its own initialisation of the system,
beginning with a memory manager (without which no dynamic memory management is
possible). The Executive first calls the `IPlatform::memoryManager()` method
to obtain the platform-specific default memory manager if there is one, and if
not initialises its built-in default memory manager. In either case, the result
is a COM interface pointer conforming to `IMemoryManager`.

Next, the Executive invokes `IPlatform::bootEnvironment()` to obtain a platform-
specific boot environment object, supplying it any arguments and environment
variables that were passed to it by the Glue. If the PAL doesn't provide its
own boot environment object, the Executive constructs one of its own.

### Object classes

Once memory management is available and the boot environment has been
initialised, the Executive can begin preparing the object system, starting
with the _Object classes_. This is the basic mechanism by which one part of the
system can  _Object Directory_, which is the Executive's
view of the running system, arranged as a hierarchical tree-like structure
which can be navigated, by any task, similarly to a virtual filesystem.

### The Object Directory


All key objects that the Executive maintains, whether that's its representations
of tasks, threads, physical devices, regions of memory, and simply convenient
internal abstractions, are structured as COM object, and follow normal COM
polymorphism, memory management, and reference-counting rules. Within the
Executive's memory space, all interactions with those objects is via (virtual)
method calls on their interface pointers.

To bring these together into a unified hierarchy, the Executive implements
_Containers_, a simple, generic, in-memory list of objects, and _Directory
Entries_, which are simply a way of associating metadata with another COM
interface pointer so that it can be located subsequently. That metadata
includes a (human-readable) name, and a UUID identifying the _kind_ of
object (which will be it's interface pointer's IID). Although all COM
interface pointers inherit from a common polymorphic base interface, it can
still be useful to know in advance, without having to interate through
a series of different interface UUIDs, what kind of an object something
generally is: a "Task" and a "Picture" and a "Mount Point" are three very
different kinds of thing, but may still have some interfaces in common. For
the object type in the Directory Entry, we use the IID (UUID) of the interface
that best identifies what the object is: if it's a task, it's `ITask`'s IID
(and not `IMutableTask` even if that interface is supported, because `ITask` is
considered to be the "lowest common denominator" interface).


For example, the root of the Object Directory is a container, which is simply
an in-memory list of directory entries and some associated methods for
manipulating them. If we create another container, and then a directory entry
for that container, giving the entry the name `Tasks`, then we would have
created a tasks "directory" beneath the root of our "filesystem". If we then
create a directory entry inside that container with the name "1" pointing at
the Executive's first task object, then by starting from the root container,
we could resolve a string like "/Tasks/1" by traversing the directory, arriving
at the _polymorphic COM interface pointer_ pointed to by our directory
entry.



Next, the Executive begins constructing the initial _Executive task_, also
known as _Task 0_. This task represents the Executive itself (with at least
one thread per CPU on a normal running system). At this point, in the execution
flow, "tasks" and "threads" are simply modelled concepts—that is, the Executive
is simply populating data structures which will be used by other code later
on.




## Marshalling

Marshalling is the process of allowing (COM) method calls to pass across a
process boundary, and in particular the management of how COM instances
(interface pointers) are passed by those calls, which is accomplished via
a per-task set of _object descriptors_, which are (like file descriptors on
many systems) numeric identifiers. Each task has an object descriptor table
which maps an interface pointer to its numeric object descriptor and vice
versa. When an object is "marshalled into a task" for the first time, a new
entry is added to the object descriptor table.

Every task starts off with an initial object descriptor 0 which is guaranteed
to exist for the lifetime of the task, and represents the caller's current
thread.



### Kernel objects and system calls

All Odin objects follow the COM patterns and binary interface rules. Within the context of a task, file descriptors — or rather *object descriptors* — are actually just reference-counted handles to COM interface pointers. Under normal circumstances, descriptors 0, 1, and 2 would indeed be descriptors to objects which support character I/O calls, just as a file descriptors represent, but in principle any descriptor could refer to any type of object whose internal implementation is in a separate address-space from the user's. 

All system calls take two fixed parameters: a numeric object descriptor, and a method index. Upon a call being despatched within Odin, it locates the interface pointer referred to by that object descriptor, and invokes the function pointer in the interface's method table matching the method index, passing it the remaining system call paramters. As all function pointers in the table are the same size, so the depatch handler can simply treat it as an array of word-returning varargs-accepting function pointers.

For any interface pointer whose class implementation is within Odin's privileged address space, this *marshaling* of the method call via a system call interface is easily comparable to any call in a modern operating system which operates on a target object of some kind—particularly filesystem calls, because filesystem interfaces tend to be heavily abstracted to allow for extensibility, such as new filesystem drivers being enabled without recompiling the kernel.

### Platforms and build types

A specific platform is identified by a GNU-style `config.guess` string in the form:

```
CPU-SYSTYPE-OS[-ABI]
```

An OS of `none` indicates a _freestanding_ build — i.e., the resulting
executable is intended to be launched by a bootloader.

A platform that specifies an `OS` (such as `linux` or `freebsd`) is a _hosted_
build—the resulting binary requires the platform operating system to run (and may
also require the platform's C library).

An `ABI` of `native` indicates a _native_ build: a static binary for the
platform OS should be built, and also that the Executive should be built
 _without_ a `libc` — in other words, it should make system calls to the host
kernel directly. The resultant executable should function as if it were an
entirely normal statically-linked executable would on the target platform,
except for it not actually being statically-linked with anything and so
having a correspondingly small footprint.

Only some subsets and combinations of `CPU`, `SYSTYPE`, `OS`, and `ABI` are supported.

### Object handoff

Core services provided by the Executive can be _handed off_ to a privileged
task, which will then provide that service to system from that point on. This
can typically only be performed once: because the Executive allows handoff of
the system memory manager, for example, does not imply that the task the
service was handed off to has to allow the same to happen again (although it
would in principle be possible in some cases).

Handoff involves transferring certain aspects of internal state from one
implementation of an object (the Executive's own) to another implementation
(within a task), by way of a _handoff object_, which is passed to the caller
as part of the handoff process.

The task providing the service queries for the `IServiceHandoff` interface
on the existing implementation, and if it's available, invokes the `handoffTo`
method, passing an `IHandoffFactory` instance pointer, whose `handoff` method
will be invoked by the Executive to trigger initialisation of the new
implementation. Assuming that method returns successfully, the Executive
marshals the interface pointer it receives and updates and global and object
directory references to point to it in place of the old implementation.

For example, the handoff object for the memory manager contains the details of
all of the regions of (virtual) memory and their owning objects, allowing the
new memory manager to pick up exactly where the old one left off.

### Build dispositions

The Executive can be built in a number of different ways, depending upon the
target platform and bootloader capabilities:

* **Dynamic**: Dynamic linking/loading is available, only for hosted builds
* **Modular**: Bootloader arranges for the Executive and the correct PAL to be loaded
* **Targeted**: Executive and PAL combined into a single platform-specific executable
* **Monolithic**: Executive, PAL, _and_ other executables are combined into a single executable

# Old notes

### Classes



### Inter-process communication

Where the caller, Odin, and class implementation are in different address spaces, the system call mechanism doubles as a transparent inter-process communication mechanism. Rather than the object descriptor pointing directly
to the implementation, it can point to a marshaler instead. A marshaler is a special kind of instance which simply forwards method calls somewhere else and returns whatever the result was back to the caller. In this case, the object descriptor would point to a marshaling instance which passes the call on to the thread which is providing the implementation.

Indeed, all object descriptors actually point to a marshaler of one sort or another, for two reasons. Most importantly, to insulate reference-counting of the kernel object from user-space reference counting (an object descriptor needs to know when it shouldn’t exist any more, but there can be multiple descriptors in different tasks for the same instance).

Second, in order to pass parameters which are pointers, or other object
descriptors, through a system call boundary, something needs to know which regions of memory constitute parameter buffers, and of course how big they are and how to access them. This applies again, with a little more complexity, when making IPC calls from the privileged context within Odin out to an unprivileged user-space task providing some kind of capability.

The rules regarding buffer translation differ from interface to interface (because each has different sets of methods accepting different kinds of parameters), but the Talisker IDL compiler will generate the relevant user-space stubs and the data required for Odin's marshaler to do its job properly. All interfaces are identified by a UUID, and Odin's marshaler tracks the UUID of the interface against the pointer it has so that it look up the correct marshaling data for that interface. If the data isn't available, then all method calls except those from `IUnknown` will fail.

### Access control at marshaling boundaries

The `queryInterface()` method of `IUnknown` is implemented by all COM classes; it is guaranteed by the ABI to be the first pointer in the method table, and always have a consistent method signature.

In Odin’s marshaling scheme, any interface pointer *returned* by a method call is assigned a new object descriptor whose value is returned to the caller—its own marshaling logic can create a new marhsalling instance wrapped around the newly-returned file descriptor.

Because of this, any interface pointer returned by a call to `queryInterface()` will result in a new object descriptor being created for the task.

Therefore, if the interfaces for read-only versus read-write access are *different*, then a marshaler within Odin could invoke logic prior to perform access-control checks before the real `queryInterface()` implementation is invoked.

In effect, then, within Odin itself, any kind of access control is represented by a principal (some object that requires access to something) and the IID of the interface on the target object to which access should be granted.

A side-effect of this is that the unit of access control can be almost anything—an interface is simply a set of operations a caller can perform on an object, so it is logical that this *is* the fundamental unit of access control.

### The task descriptor

Every task is always launched with a minimum of one object descriptor assigned to it (although usually more), which points to the task's own interface pointer. This descriptor's marshaler will refuse to allow the descriptor to be closed from user-space; requests to inherit the descriptor into a child process will always fail, although a child process can be given access to the parent's by cloning the task descriptor and marking the resulting interface as being inheritable.

### The thread descriptor



### The object namespace

Any COM object can be placed into the global object namespace by linking it to an object directory container by establishing an in-memory a *directory entry* instance for it, which represents the name, type, ownership, notional size, and ACLs of the target object within that directory.

Filesystem operations consist of traversing and manipulating this tree of object directories: Odin provides a transient in-memory root object directory, analogous to the root filesystem in Unix-like systems. This transient directory supports the creation of directory *entries* to represent running objects, but doesn’t have any capabilities to store any data: in other words, it supports creating subdirectories, symbolic links, device nodes, and so on, but not "real" files.

Real filesystem implementations provide instances which implement the same object directory interfaces, but whose data is read from disk as needed; mounting a filesystem is therefore a case of initialising a filesystem object (supplying it with the block device object), obtaining its object directory interface, and creating a directory entry for it at the mount-point.

The root object directory has the following structure:

    /
        Volumes
		    [mount points are generally created here]
			[root volume]
				Local
					Applications
					Library
						Preferences
						Caches
						: (see /Volumes/Root/Talisker/Library, below)
					Users
						sara
						joe
						admin
							Applications
							Desktop
							Pictures
							Movies
							Music
							Downloads
							Library
							    :
				Talisker
					Applications
						Utilities
					Library
						Preferences
						Desktop Pictures
						Fonts
						Personalities
						UserTemplate
						Sounds
						
			Boot [initial RAMdisk]
			Root → [root volume]
		Devices
		    [device nodes are automatically created here]
		Local → /Volumes/Root/Local
		Network
		    Applications → [mounted network share]
		    Library → [mounted network share]
			Users → [mounted network share]
			Servers
			    [domain]
				    [share]
				    [host]
					    [share]
		Talisker
		    Applications → /Volumes/Root/Talisker/Applications
			Library → /Volumes/Root/Talisker/Library
			System
				Classes
					[class uuid] → [class factory instance or executable]
					[name] → [class uuid]
				Interfaces
					[uuid]
						ImplementedBy
							[class uuid]
				Subsystems
					[uuid]
				ContentTypes
					application
						x-unknown
							Extensions
								bin
					image
						jpeg
							Extensions
								jpg
					Extensions
						jpg → [MIME type entry for image/jpeg]
					
				Tasks
					me → [link to PID of invoker]
					[pid]
						name
						environment
						cmdline
						state
						priority
						Threads
							[tid]
								state
									

Because objects are polymorphic and are generally-accessible via RPC, the directory entries within `/Talisker/System/Tasks` refer not to synthesised files in a virtual filesystem, but the Odin’s own representations of each task: "opening" one of those tasks within the directory is actually just obtaining an object descriptor for that task.

For example, imagine that our IDirectory interface has a `resolve` method which parses a path, traversing the tree, and returns an IDirectoryEntry interface pointer if one is found. "Opening" the "file" that it refers to is simply a case of calling a method on the directory entry to obtain an interface pointer from the retained object.

The resolve method might look like this:

    int IDirectory::resolve(const char *path, IDirectoryEntry **result);

while the method to open a directory entry might look like this:

	int IDirectoryEntry::open(const uuid_t iid, void **result);

Given a thread has a current working directory, and a thread can always access its own thread interface via the thread descriptor, a traditional "open" call could look a little like this:

    int
	open(const char *path, int flags, ...)
	{
		uuid_t iid;
		IDirectory *cwd;
		IDirectoryEntry *de;
		IUnknown *file;
		
		/* The access bits determine which interface we're going to request */
		if(flags & O_RDWR)
		{
			iid = IID_IReadWriteFile;
		}
		elif(flags & O_RDONLY)
		{
			iid = IID_IReadFile;
		}
		else
		{
			iid = IID_WriteFile;
		}
		
		/* omitting code to deal with appending, truncating, or creating
		 * new files!
		 */
    
		/* use the thread API to obtain a reference to the current working directory */
		if(self->cwd(&cwd)) 
		{
			/* somehow we don't have a valid CWD */
			/* errno will be set for us */
			return -1;
		}
		r = cwd->resolve(path, &de))
		{
			/* errno will be set for us */
			cwd->release();
			return -1;
		}
		cwd->release();
		if(de->open(iid, (void **) &file))
		{
			de->release();
			return -1;
		}
		de->release();
		return self->descriptor(file);
	}

### Subsystems

Although the sequence above broadly matches what most traditional operating systems do in response to an open() call, it is nevertheless true that if in an Odin-based system each of these calls is an IPC, possibly involving multiple context switches, then performance will probably not compare favourably to other systems for performing similar operations.

Odin's philosophy is not one of reducing the footprint of the system at the expense of performance or capability, but to reduce the footprint *in order to maximise flexibility*.

Rather than that this call sequence necessarily being executed in user-mode, consider that it could be encapsulated into an interface providing a certain API: for example, ISO C’s standard I/O calls.

While this call *could* be serviced via a library which is able to run solely in user-mode, there would undoubtedly be a performance increase if an `open()` call was marshaled via an object descriptor into a method call whose implementation had direct access to the same memory space as Odin's methods that it calls.

In Odin, the formalised mechanism for achieving this is through *subsystems*. When executed with sufficient privilege, a subsystem task can request that it be converted to a kernel-mode task (if it isn't already), so that it can avoid context-switch penalties. Once elevated to kernel-mode, a subsystem's existence is advertised via `/Talisker/System/Subsystems` as well as a method on the task interface.

### Advertising capabilities

Classically, clients of COM objects are only aware of the interfaces that they know about, and won't tend to have a preferred list of interfaces which certain objects would ideally support—even if they do, they still need to query for each separately to determine availability.

Because instances within the namespace are essentially advertising themselves, they also a need a mechanism to advertise what they *are*—or rather, what interfaces they support.

To do this, objects can expose the `ISupports` interface, which provides a single method, `supports()`, which a client can use to query an instance for what *other* interfaces it supports (or at least those which it is willing to advertise the availability of).

### Interpreters

Interpreters are special kinds of proxy classes which allow an object supporting one interface to support another interface that it does not natively support itself.

For example, an interpreter can be used to allow a JSON file on disk to support being opened and providing a Dictionary (a set of key-value pair) interface, or an image metadata interface be opened on a JPEG image file.

Interpreters are used to allow files on disk to be executable: all executables supported by a running system, whether they're scripts, binaries, or something else, are executed by way of their IExecutable inteface.

Interpreters bind a matching rule to a class implementation that they provide and the interface UUID provided by that class: the matching rule is a combination of the UUID of a the interface, and if it's a file, include constraints on file access bits (e.g., is the execute bit set?), or on content type (which may be defined by filename pattern, magic numbers, or present in filesystem metadata).

They provide a class which implements `IInterpreterFactory`-a type of class factory which initialises a wrapper around the interface provded.

For example, a [Mach-O](https://en.wikipedia.org/wiki/Mach-O) executable interpreter might register itself as follows:

	Provides:         IID_IExecutable
	Matches:
	    Interface:    IID_IFile
		File access:  IID_ExcutableFile
		Signature:
			0: <CF> <FA> <ED> <FE>
			1: <CE> <FA> <ED> <FE>
			2: <CA> <FE> <BA> <BE>
		

When `queryInterface()` is invoked on an object advertising `IFile`, and the interface requested is `IExecutable`, and one of the three provided binary signatures match, then the ELF interpreter's factory’s `interpreterInstance()` method is invoked:

	int interpreterInstance([in] const uuid_t inneriid, [in,iid_is(inneriid)] void *innerobject, [in] const uuid_t interpiid, [out,iid_is(interpiiid)] void **interpreter);

In this case, it would be invoked with:

	factory->interpreterInstance(IID_IFile, fileobject, IID_IExecutable, &ptr);

From the perspective of the user of the object descriptor, this is completely transparent: all executable Mach-O files appear to natively support the IExecutable interface, allowing them to be executed in a task.

### Built-in device drivers

#### Character devices

##### Maintenance console

If enabled, Odin has the capability to use a serial a serial console for log output, defaulting to 9600,8,N,1.

If Odin is running in user-space on a host operating system, a “host console” which sends output to standard error is provided instead.

#### Filesystems

##### Archive filesystem

#### Interpreters

##### ELF interpreter

The ELF interpreter provides a loader capable of presenting an `IExecutable` interface to any ELF executable for a supported architecture and ABI that is accessible as a executable `IFile`.

Unlike other interpreter classes, the ELF interpreter is compiled in to Odin on most systems, and so the initial set of tasks which are launched at system start-up (prior to interpreters for any other executable formats being launched) must also be ELF binaries.

## Building from source

## Running Odin

### Deployment scenarios

For desktops and servers, the envisaged deployment scenario is as a dom0 kernel beneath a hypervisor, allowing personalities to launch VMs to provide whatever high-level capabilities (running Linux or Windows applications, for example) might be required.

On more constrained systems, a hypervisor may not be feasible, and instead Odin runs on bare-metal. On systems without an MMU, a different memory manager could be employed—or even left to the rudimentary management Odin itself performs.

Odin is intended to be small, portable and extensible enough to be able to form a useful basis for operating systems running on everything from IoT devices to midrange and mainframe systems.

## License

Copyright © 2017 Mo McRoberts.

[`BuildScripts/get-version.sh`](BuildScripts/get-version.sh) is also Copyright © 2014 BBC.

Licensed under the terms of the [Apache License, Version 2.0](http://www.apache.org/licenses/LICENSE-2.0).

[travis]: https://img.shields.io/travis/TaliskerPlatform/Odin.app.svg
[license]: https://img.shields.io/badge/license-Apache%202.0-blue.svg
[language]: https://img.shields.io/badge/implemented%20in-C-yellow.svg