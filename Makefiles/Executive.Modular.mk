if EXEC_BUILD_MODULAR

## Modular configuration: an external loader arranges for the correct PAL to be
## loaded, and so it doesn't need to be specified at build time

sbin_PROGRAMS += Executive.Modular

Executive_Modular_CPPFLAGS =  @AM_CPPFLAGS@ @EXEC_GLUE_CPPFLAGS@ -DEXEC_BUILD_MODULAR=1 ${WARNING_CPPFLAGS}
Executive_Modular_SOURCES = $(ENTRYPOINT)
Executive_Modular_LDADD = @EXEC_GLUE_OBJECT_MODULAR@ \
	$(top_builddir)/Sources/libExecutiveServices.Debug.la \
	$(top_builddir)/Stubs/libPAL.la
Executive_Modular_LDFLAGS = @AM_LDFLAGS@ @EXEC_GLUE_LDFLAGS@
Executive_Modular_DEPENDENCIES = $(ENTRYPOINT) $(Executive_Modular_LDADD)

endif
