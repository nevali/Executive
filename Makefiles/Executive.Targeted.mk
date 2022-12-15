## Targeted configuration: link a specific PAL to the Executive

if EXEC_BUILD_TARGETED

# We must iterate each of the potential PALs

if EXEC_BUILD_TARGETED_POSIX

sbin_PROGRAMS += Executive.Targeted.POSIX

Executive_Targeted_POSIX_CPPFLAGS =  @AM_CPPFLAGS@ @EXEC_GLUE_CPPFLAGS@ -DEXEC_BUILD_TARGETED=1 @EXEC_PAL_POSIX_CPPFLAGS@ ${WARNING_CPPFLAGS}
Executive_Targeted_POSIX_SOURCES = $(ENTRYPOINT)
Executive_Targeted_POSIX_LDADD = \
	$(top_builddir)/Sources/@EXEC_GLUE_OBJECT_TARGETED@ \
	$(top_builddir)/@EXEC_PAL_POSIX_DLL@ \
	$(top_builddir)/Sources/libExecutiveServices.Debug.la
Executive_Targeted_POSIX_LDFLAGS = @AM_LDFLAGS@ @EXEC_GLUE_LDFLAGS@ @EXEC_PAL_POSIX_LDFLAGS@ -no-undefined
Executive_Targeted_POSIX_DEPENDENCIES = $(ENTRYPOINT) $(Executive_Targeted_POSIX_LDADD)

endif

endif
