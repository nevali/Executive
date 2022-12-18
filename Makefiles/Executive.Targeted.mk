## Targeted configuration: link a specific PAL to the Executive

Targeted_sources = $(ENTRYPOINT)
Targeted_cppflags = @AM_CPPFLAGS@ @EXEC_GLUE_CPPFLAGS@ -DEXEC_BUILD_TARGETED=1 ${WARNING_CPPFLAGS}
Targeted_ldflags = @AM_LDFLAGS@
Targeted_glue =  $(top_builddir)/@EXEC_GLUE_OBJECT_TARGETED@

Targeted_resident = $(top_builddir)/Subsystems/libResident.la

Targeted_POSIX_sources = $(Targeted_sources)
Targeted_POSIX_cppflags = $(Targeted_cppflags) @EXEC_PAL_POSIX_CPPFLAGS@
Targeted_POSIX_glue = $(Targeted_glue)
Targeted_POSIX_ldflags = $(Targeted_ldflags) @EXEC_GLUE_LDFLAGS@ @EXEC_PAL_POSIX_LDFLAGS@ -no-undefined

###

Executive_Targeted_POSIX_SOURCES = $(Targeted_POSIX_sources)
Executive_Targeted_POSIX_CPPFLAGS = $(Targeted_POSIX_cppflags)
Executive_Targeted_POSIX_LDADD = $(Targeted_POSIX_glue) $(top_builddir)/@EXEC_PAL_POSIX_DLL_Release@ $(top_builddir)/Sources/libExecutiveServices.la $(Targeted_resident)
Executive_Targeted_POSIX_LDFLAGS = $(Targeted_POSIX_ldflags)
Executive_Targeted_POSIX_DEPENDENCIES = $(Targeted_POSIX_sources) $(Executive_Targeted_POSIX_LDADD)

Executive_Targeted_POSIX_Free_SOURCES = $(Targeted_POSIX_sources)
Executive_Targeted_POSIX_Free_CPPFLAGS = $(Targeted_POSIX_cppflags)
Executive_Targeted_POSIX_Free_LDADD = $(Targeted_POSIX_glue) $(top_builddir)/@EXEC_PAL_POSIX_DLL_Free@ $(top_builddir)/Sources/libExecutiveServices.la $(Targeted_resident)
Executive_Targeted_POSIX_Free_LDFLAGS = $(Targeted_POSIX_ldflags)
Executive_Targeted_POSIX_Free_DEPENDENCIES = $(Targeted_POSIX_sources) $(Executive_Targeted_POSIX_Free_LDADD)

Executive_Targeted_POSIX_Debug_SOURCES = $(Targeted_POSIX_sources)
Executive_Targeted_POSIX_Debug_CPPFLAGS = $(Targeted_POSIX_cppflags)
Executive_Targeted_POSIX_Debug_LDADD = $(Targeted_POSIX_glue) $(top_builddir)/@EXEC_PAL_POSIX_DLL_Debug@ $(top_builddir)/Sources/libExecutiveServices.la $(Targeted_resident)
Executive_Targeted_POSIX_Debug_LDFLAGS = $(Targeted_POSIX_ldflags)
Executive_Targeted_POSIX_Debug_DEPENDENCIES = $(Targeted_POSIX_sources) $(Executive_Targeted_POSIX_Debug_LDADD)

if EXEC_BUILD_TARGETED

# We must iterate each of the potential PALs

if EXEC_BUILD_TARGETED_POSIX
if BUILD_RELEASE
sbin_PROGRAMS += Executive.Targeted.POSIX
endif
if BUILD_FREE
sbin_PROGRAMS += Executive.Targeted.POSIX.Free
endif
if BUILD_DEBUG
sbin_PROGRAMS += Executive.Targeted.POSIX.Debug
endif
endif

endif

CLEANFILES += Executive.Targeted.POSIX Executive.Targeted.POSIX.Free Executive.Targeted.POSIX.Debug