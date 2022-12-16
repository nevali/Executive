Modular_sources = $(ENTRYPOINT)
Modular_cppflags = @AM_CPPFLAGS@ @EXEC_GLUE_CPPFLAGS@ -DEXEC_BUILD_MODULAR=1 ${WARNING_CPPFLAGS}
Modular_libs = @EXEC_GLUE_OBJECT_MODULAR@ $(top_builddir)/Stubs/libPAL.la $(top_builddir)/Sources/libExecutiveServices.la

Executive_Modular_CPPFLAGS = $(Modular_cppflags)
Executive_Modular_SOURCES = $(Modular_sources)
Executive_Modular_LDADD = $(Modular_libs) 
Executive_Modular_LDFLAGS = @AM_LDFLAGS@ @EXEC_GLUE_LDFLAGS@
Executive_Modular_DEPENDENCIES = $(Modular_sources) $(Executive_Modular_LDADD)

Executive_Modular_Free_CPPFLAGS = $(Modular_cppflags)
Executive_Modular_Free_SOURCES = $(Modular_sources)
Executive_Modular_Free_LDADD =  $(Modular_libs)
Executive_Modular_Free_LDFLAGS = @AM_LDFLAGS@ @EXEC_GLUE_LDFLAGS@
Executive_Modular_Free_DEPENDENCIES = $(Modular_sources) $(Executive_Modular_Free_LDADD)

Executive_Modular_Debug_CPPFLAGS = $(Modular_cppflags)
Executive_Modular_Debug_SOURCES = $(Modular_sources)
Executive_Modular_Debug_LDADD =  $(Modular_libs)
Executive_Modular_Debug_LDFLAGS = @AM_LDFLAGS@ @EXEC_GLUE_LDFLAGS@
Executive_Modular_Debug_DEPENDENCIES = $(Modular_sources) $(Executive_Modular_Debug_LDADD)

if EXEC_BUILD_MODULAR

## Modular configuration: an external loader arranges for the correct PAL to be
## loaded, and so it doesn't need to be specified at build time

if BUILD_RELEASE
sbin_PROGRAMS += Executive.Modular
endif
if BUILD_FREE
sbin_PROGRAMS += Executive.Modular.Free
endif
if BUILD_DEBUG
sbin_PROGRAMS += Executive.Modular.Debug
endif
endif

CLEANFILES += Executive.Modular Executive.Modular.Free Executive.Modular.Debug
