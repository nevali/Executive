dnl EX_ARG_ENABLE_DISPOSITIONS
AC_DEFUN([EX_ARG_ENABLE_DISPOSITIONS],[
	dnl # Dynamic build
dnl
dnl A "dynamic" build is one where the Executive (and specifically the Glue) is
dnl able to locate and load the correct PAL itself, without any needing to be
dnl available or known at build time. This is only supported when building the
dnl Executive for platforms which have runtime dynamic loading capabilities.

AC_ARG_ENABLE([dynamic],[AS_HELP_STRING([--disable-dynamic],[don't perform a dynamic build of the Executive])],[exec_build_dynamic=$enableval],[exec_build_dynamic=auto])

dnl # Modular build
dnl
dnl A "modular" build is one where the Executive does NOT have the ability to
dnl locate and load a PAL itself, nor is it linked with a PAL at build time,
dnl but nevertheless expects a PAL to be provided at runtime by the loader. For
dnl example, a Multiboot loader could provide the PAL as a boot module, and on
dnl Linux, LD_PRELOAD could be used to preload the correct PAL

AC_ARG_ENABLE([modular],[AS_HELP_STRING([--disable-modular],[don't perform a modular build of the Executive])],[exec_build_modular=$enableval],[exec_build_modular=auto])

dnl # Targeted build
dnl
dnl Targeted builds explicitly link the Executive to a particular PAL (either
dnl dynamically or statically, depending upon the platform and configuration
dnl options). If targeted builds are enabled, one executable will be generated
dnl for each PAL (each will be identical except for the PAL they link with).

AC_ARG_ENABLE([targeted],[AS_HELP_STRING([--disable-targeted],[don't perform a targeted build of the Executive])],[exec_build_targeted=$enableval],[exec_build_targeted=auto])

dnl # Monolith build
dnl
dnl Monolith builds are similar to targeted builds, but bundle the Executive,
dnl PAL, and other components together into a single binary. This is primarily
dnl for platforms where there is no useful concept of a filesystem.

AC_ARG_ENABLE([monolith],[AS_HELP_STRING([--disable-monolith],[don't perform a monolith build of the Executive])],[exec_build_monolith=$enableval],[exec_build_monolith=auto])

dnl If the user explicitly requested the PALs are not built (via --disable-pals)
dnl then neither targeted nor modular builds make any sense

if test $enable_pals = no ; then
	exec_build_targeted=no
	exec_build_modular=no
fi
])dnl
dnl
dnl EX_CHECK_DISPOSITIONS
dnl - Depending upon the variables set by the selected Glue module,
dnl   determine which build dispositions to enable, defining the
dnl   Automake conditionals used to perform them
dnl
dnl   Note that $exec_build_targeted and $exec_build_monolith may
dnl   be set to "auto" after this macro, because we haven't yet
dnl   configured the PALs
AC_DEFUN([EX_CHECK_DISPOSITIONS],[
AC_REQUIRE([EX_ARG_ENABLE_DISPOSITIONS])dnl
AC_REQUIRE([EX_CHECK_GLUE])dnl
AC_REQUIRE([EX_CHECK_PALS])dnl

	AC_MSG_CHECKING([whether to perform a dynamic build])
	if test "$exec_build_dynamic" = "yes" && test -z "$EXEC_GLUE_OBJECT_DYNAMIC" ; then
		AC_MSG_ERROR([a dynamic build was requested but is not supported by the $exec_glue Glue])
	fi
	test -z "$EXEC_GLUE_OBJECT_DYNAMIC" && exec_build_dynamic="no"
	test "$exec_build_dynamic" = "auto" && exec_build_dynamic="yes"
	AC_MSG_RESULT([$exec_build_dynamic])
	AM_CONDITIONAL([EXEC_BUILD_DYNAMIC],[test x$exec_build_dynamic = xyes])

	AC_MSG_CHECKING([whether to perform a modular build])
	if test "$exec_build_modular" = "yes" && test -z "$EXEC_GLUE_OBJECT_MODULAR" ; then
		AC_MSG_ERROR([a modular build was requested but is not supported by the $exec_glue Glue])
	fi
	test -z "$EXEC_GLUE_OBJECT_MODULAR" && exec_build_modular="no"
	test "$exec_build_modular" = "auto" && exec_build_modular="yes"
	AC_MSG_RESULT([$exec_build_modular])
	AM_CONDITIONAL([EXEC_BUILD_MODULAR],[test x$exec_build_modular = xyes])

	AC_MSG_CHECKING([whether to perform targeted builds])
	if test "$exec_build_targeted" = "yes" && test -z "$EXEC_GLUE_OBJECT_MODULAR" ; then
		AC_MSG_ERROR([targeted builds were requested but are not supported by the $exec_glue Glue])
	fi
	if test -z "$exec_pal_list" && test "$exec_build_targeted" = "yes" ; then
		AC_MSG_ERROR([targeted builds were requested but no PALs have been configured])
	fi
	test "$exec_build_targeted" = "auto" && exec_build_targeted="yes"
	( test -z "$exec_pal_list" || test -z "$EXEC_GLUE_OBJECT_TARGETED" ) && exec_build_targeted="no"
	AC_MSG_RESULT([$exec_build_targeted])
	AM_CONDITIONAL([EXEC_BUILD_TARGETED],[test x$exec_build_targeted = xyes])

	AC_MSG_CHECKING([whether to perform monolith builds])
	if test "$exec_build_monolith" = "yes" && test -z "$EXEC_GLUE_OBJECT_MONOLITH" ; then
		AC_MSG_ERROR([monolith builds were requested but are not supported by the $exec_glue Glue])
	fi
	test "$exec_build_monolith" = "auto" && exec_build_monolith="yes"
	( test -z "$exec_pal_list" || test -z "$EXEC_GLUE_OBJECT_MONOLITH" ) && exec_build_monolith="no"
	AC_MSG_RESULT([$exec_build_monolith])
	AM_CONDITIONAL([EXEC_BUILD_MONOLITH],[test x$exec_build_monolith = xyes])

	if test $exec_build_dynamic = no && \
		test $exec_build_modular = no && \
		test $exec_build_targeted = no && \
		test $exec_build_monolith = no ; then
		AC_MSG_ERROR([no build types available for $host_type $host_platform])
	fi

])dnl
