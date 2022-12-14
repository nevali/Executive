if EXEC_BUILD_DYNAMIC

## Dynamic configuration: the Executive has the capability to locate and
## initialise an appropriate PAL (which does not need to be specified at build
## time) itself

sbin_PROGRAMS += Executive.Dynamic

Executive_Dynamic_CPPFLAGS = @AM_CPPFLAGS@ @EXEC_GLUE_CPPFLAGS@ -DEXEC_BUILD_DYNAMIC=1 ${WARNING_CPPFLAGS}
Executive_Dynamic_SOURCES = $(ENTRYPOINT)
Executive_Dynamic_LDADD = @EXEC_GLUE_OBJECT_DYNAMIC@ $(top_builddir)/Sources/libExecutiveServices.la
Executive_Dynamic_LDFLAGS = @AM_LDFLAGS@ @EXEC_GLUE_LDFLAGS@
Executive_Dynamic_DEPENDENCIES = $(ENTRYPOINT) $(Executive_Dynamic_LDADD)

endif
