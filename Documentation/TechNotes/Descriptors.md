# Descriptors

Each task has its own set of _object descriptors_, each of which represents an
interface pointer either within kernel-space, or within another task's address
space.

Upon starting a task's main thread, a fixed number (per platform) of
descriptors are reserved for the system, with some populated with
well-known objects (see `Frameworks/Executive/Headers/Executive/SystemCall.h`),
and those following made up of the inherited descriptors, with the
first three of those generally being known as "standard input",
"standard output", and "standard error".

This approach allows a user-space `libc` to translate a "file descriptor"
to an object descriptor simply by adding the count of reserved descriptors
(retrievable from the task object and obtained by the runtime at startup),
and vice versa. Even if all descriptors are released (closed), the
Executive won't ever issue new descriptor with a value below that fixed
count.

An important but minor detail is that none of the well-known objects'
interfaces are any of those used for standard I/O operations - anything that
might be considered a "file" by a user-space library will always get a
descriptor outside of this reserved range, including the very first task
launched)

Because I/O kernel method calls all have unique despatch IDs, the Executive
is easily able to catch the case where, say, IWriteChannel::send() is called
on a descriptor which doesn't support that interface, resulting from a
call to a `libc` `write()` function with an incorrect file descriptor, and
will return a specific error code which can be translated to `errno = EBADF`
