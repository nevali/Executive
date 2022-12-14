## Executive Microkernel
##   Sources/Glue/Glue.mk
##   Common build logic for Glue modules


# Note that these modules/libraries are not actually linked into the Executive,
# it's just a way of building the Glue with the correct flags

## Dynamic build - the Glue locates a PAL and passes it to the Executive itself

if EXEC_BUILD_DYNAMIC

noinst_LTLIBRARIES += Glue.Dynamic.la

Glue_Dynamic_la_SOURCES = $(GLUESRC)
Glue_Dynamic_la_CPPFLAGS = ${AM_CPPFLAGS} -DEXEC_BUILD_DYNAMIC=1
Glue_Dynamic_la_LDFLAGS = -module

endif

## Modular build - will be linked against a stub PAL

if EXEC_BUILD_MODULAR

noinst_LTLIBRARIES += Glue.Modular.la

Glue_Modular_la_SOURCES = $(GLUESRC)
Glue_Modular_la_CPPFLAGS = ${AM_CPPFLAGS} -DEXEC_BUILD_MODULAR=1
Glue_Modular_la_LDFLAGS = -module

endif

## Targeted build - linked against a specific PAL

if EXEC_BUILD_TARGETED

noinst_LTLIBRARIES += Glue.Targeted.la

Glue_Targeted_la_SOURCES = $(GLUESRC)
Glue_Targeted_la_CPPFLAGS = ${AM_CPPFLAGS} -DEXEC_BUILD_TARGETED=1
Glue_Targeted_la_LDFLAGS = -module

endif

## Monolith build - statically-linked against a specific PAL and other subsystems

if EXEC_BUILD_MONOLITH

noinst_LTLIBRARIES += Glue.Monolith.la

Glue_Monolith_la_SOURCES = $(GLUESRC)
Glue_Monolith_la_CPPFLAGS = ${AM_CPPFLAGS} -DEXEC_BUILD_MONOLITH=1
Glue_Monolith_la_LDFLAGS = -static -module

endif
