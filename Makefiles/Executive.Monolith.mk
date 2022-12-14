## Monolithic configuration: link a specific PAL, possibly along with other
## executables, to the Executive

if EXEC_BUILD_MONOLITH

if EXEC_BUILD_MONOLITH_POSIX

sbin_PROGRAMS += Executive.Monolith.POSIX

Executive_Monolith_POSIX_CPPFLAGS = @AM_CPPFLAGS@ @EXEC_GLUE_CPPFLAGS@ -DEXEC_BUILD_MONOLITH=1 @EXEC_PAL_POSIX_CPPFLAGS@ ${WARNING_CPPFLAGS}
Executive_Monolith_POSIX_SOURCES = $(ENTRYPOINT)
Executive_Monolith_POSIX_LDADD = \
	$(top_builddir)/Sources/@EXEC_GLUE_OBJECT_MONOLITH@ \
	$(top_builddir)/@EXEC_PAL_POSIX_LIB@ \
	$(top_builddir)/Sources/libExecutiveServices.la
Executive_Monolith_POSIX_LDFLAGS = @AM_LDFLAGS@ @EXEC_GLUE_LDFLAGS@ @EXEC_PAL_POSIX_LDFLAGS@ -static-libtool-libs
Executive_Monolith_POSIX_DEPENDENCIES = $(ENTRYPOINT) $(Executive_Monolith_POSIX_LDADD)

endif

endif
