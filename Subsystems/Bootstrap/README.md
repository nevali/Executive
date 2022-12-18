# Executive Microkernel

## Bootstrap subsystem

The Bootstrap subsystem is started by the Executive as soon as it's fully
fully initialised and ready for user-space tasks.

At this point, there are no personalities available, and no other subsystems,
and often the Bootstrap system is compiled into the Executive itself.
