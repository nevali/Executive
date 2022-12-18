# Executive Microkernel

## Subsystems interface

Subsystems are the bridge between the Executive and a functioning useable
userland.

At least one subsystem, Bootstrap, must be available at boot, either provided
by the bootloader or compiled into the kernel binary.

The Bootstrap subsystem sets up bundled _Personalities_, which allow programs
to be executed, and launches the first user-space task.

The Executive::Subsystems class keeps track of the available subsystems and
makes them visible in the object directory.

The Executive's startup code looks for `/Systems/Subsystems/Bootstrap` and
atttempts to invoke `ISubsystem::start()` on it
