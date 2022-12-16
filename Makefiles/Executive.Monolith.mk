## Monolithic configuration: link a specific PAL, possibly along with other
## executables, to the Executive

Monolith_sources = $(ENTRYPOINT)
Monolith_cppflags = @AM_CPPFLAGS@ @EXEC_GLUE_CPPFLAGS@ -DEXEC_BUILD_MONOLITH=1 ${WARNING_CPPFLAGS}
Monolith_glue = $(top_builddir)/Sources/@EXEC_GLUE_OBJECT_MONOLITH@

Monolith_POSIX_cppflags = $(Monolith_cppflags) @EXEC_PAL_POSIX_CPPFLAGS@ 
Monolith_POSIX_sources = $(Monolith_sources)
Monolith_POSIX_glue = $(Monolith_glue)
Monolith_POSIX_ldflags = @AM_LDFLAGS@ @EXEC_GLUE_LDFLAGS@ @EXEC_PAL_POSIX_LDFLAGS@ -static-libtool-libs

###

Executive_Monolith_POSIX_CPPFLAGS = $(Monolith_POSIX_cppflags)
Executive_Monolith_POSIX_SOURCES = $(Monolith_POSIX_sources)
Executive_Monolith_POSIX_LDADD = $(Monolith_POSIX_glue) $(top_builddir)/@EXEC_PAL_POSIX_LIB_Release@ $(top_builddir)/Sources/libExecutiveServices.la
Executive_Monolith_POSIX_LDFLAGS = $(Monolith_POSIX_ldflags)
Executive_Monolith_POSIX_DEPENDENCIES = $(Executive_Monolith_POSIX_LDADD)

Executive_Monolith_POSIX_Free_CPPFLAGS = $(Monolith_POSIX_cppflags)
Executive_Monolith_POSIX_Free_SOURCES = $(Monolith_POSIX_sources)
Executive_Monolith_POSIX_Free_LDADD = $(Monolith_POSIX_glue) $(top_builddir)/@EXEC_PAL_POSIX_LIB_Free@ $(top_builddir)/Sources/libExecutiveServices.la
Executive_Monolith_POSIX_Free_LDFLAGS = $(Monolith_POSIX_ldflags)
Executive_Monolith_POSIX_Free_DEPENDENCIES = $(Executive_Monolith_POSIX_Free_LDADD)

Executive_Monolith_POSIX_Debug_CPPFLAGS = $(Monolith_POSIX_cppflags) 
Executive_Monolith_POSIX_Debug_SOURCES = $(Monolith_POSIX_sources)
Executive_Monolith_POSIX_Debug_LDADD =  $(Monolith_POSIX_glue) $(top_builddir)/@EXEC_PAL_POSIX_LIB_Debug@ $(top_builddir)/Sources/libExecutiveServices.la
Executive_Monolith_POSIX_Debug_LDFLAGS = $(Monolith_POSIX_ldflags)
Executive_Monolith_POSIX_Debug_DEPENDENCIES = $(Executive_Monolith_POSIX_Debug_LDADD)

if EXEC_BUILD_MONOLITH
if EXEC_BUILD_MONOLITH_POSIX
if BUILD_RELEASE
sbin_PROGRAMS += Executive.Monolith.POSIX
endif
if BUILD_FREE
sbin_PROGRAMS += Executive.Monolith.POSIX.Free
endif
if BUILD_DEBUG
sbin_PROGRAMS += Executive.Monolith.POSIX.Debug
endif
endif
endif

CLEANFILES += Executive.Monolith.POSIX Executive.Monolith.POSIX.Free Executive.Monolith.POSIX.Debug
