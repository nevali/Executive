Dynamic_cppflags = @AM_CPPFLAGS@ @EXEC_GLUE_CPPFLAGS@ -DEXEC_BUILD_DYNAMIC=1 ${WARNING_CPPFLAGS}
Dynamic_sources = $(ENTRYPOINT)
Dynamic_libs = @EXEC_GLUE_OBJECT_DYNAMIC@ $(top_builddir)/Sources/libExecutiveServices.la 
Dynamic_ldflags = @AM_LDFLAGS@ @EXEC_GLUE_LDFLAGS@

Executive_Dynamic_CPPFLAGS = $(Dynamic_cppflags)
Executive_Dynamic_SOURCES = $(Dynamic_sources)
Executive_Dynamic_LDADD = $(Dynamic_libs) @EXEC_GLUE_DYNAMIC_LIBS@
Executive_Dynamic_LDFLAGS = $(Dynamic_ldflags)
Executive_Dynamic_DEPENDENCIES = $(Executive_Dynamic_SOURCES) $(Dynamic_libs)

Executive_Dynamic_Free_CPPFLAGS = $(Dynamic_cppflags)
Executive_Dynamic_Free_SOURCES = $(Dynamic_sources)
Executive_Dynamic_Free_LDADD = $(Dynamic_libs) @EXEC_GLUE_DYNAMIC_LIBS@
Executive_Dynamic_Free_LDFLAGS = $(Dynamic_ldflags)
Executive_Dynamic_Free_DEPENDENCIES = $(Executive_Dynamic_Free_SOURCES) $(Dynamic_libs)

Executive_Dynamic_Debug_CPPFLAGS = $(Dynamic_cppflags)
Executive_Dynamic_Debug_SOURCES = $(Dynamic_sources)
Executive_Dynamic_Debug_LDADD = $(Dynamic_libs) @EXEC_GLUE_DYNAMIC_LIBS@
Executive_Dynamic_Debug_LDFLAGS = $(Dynamic_ldflags)
Executive_Dynamic_Debug_DEPENDENCIES = $(Executive_Dynamic_Debug_SOURCES) $(Dynamic_libs)

if EXEC_BUILD_DYNAMIC
## Dynamic configuration: the Executive has the capability to locate and
## initialise an appropriate PAL (which does not need to be specified at build
## time) itself
if BUILD_RELEASE
sbin_PROGRAMS += Executive.Dynamic
endif
if BUILD_FREE
sbin_PROGRAMS += Executive.Dynamic.Free
endif
if BUILD_DEBUG
sbin_PROGRAMS += Executive.Dynamic.Debug
endif
endif

CLEANFILES += Executive.Dynamic Executive.Dynamic.Free Executive.Dynamic.Debug
