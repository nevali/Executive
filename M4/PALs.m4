dnl EX_ARG_ENABLE_PALS
dnl - ensure $enable_pals is set
AC_DEFUN([EX_ARG_ENABLE_PALS],[
AC_ARG_ENABLE([pals],[AS_HELP_STRING([--disable-pals],[don't attempt to build any PALs, implies --disable-targeted and --disable-monolith])],,[enable_pals=auto])
])dnl
dnl
dnl EX_CHECK_PALS
dnl - Determine which PALs to build
AC_DEFUN([EX_CHECK_PALS],[
AC_REQUIRE([EX_CHECK_GLUE])dnl
dnl ## PAL selection
dnl
dnl PAL logic is more complex than that of the Glue, because multiple PALs can
dnl be built for a given platform, and versions of the Executive linked to each
dnl can be generated, as well as, potentially, versions supporting the
dnl selection of an appropriate PAL at runtime, as opposed to build time

AC_MSG_RESULT([configuring Platform Adaptation Layers (PALs) for $host ($host_type)...])

save_LIBS="$LIBS"

AS_VAR_SET([exec_pal_list], [""])
AC_SUBST([exec_pal_list])

dnl ## POSIX PAL
dnl

EXEC_PAL_CONFIG([POSIX])

LIBS="$save_LIBS"

AC_MSG_CHECKING([which Platform Adaptation Layers (PALs) to build])
test $enable_pals = no && exec_pal_list=""
if test -z "$exec_pal_list" ; then
	AC_MSG_RESULT([none])
	if test $enable_pals = auto || test $enable_pals = yes ; then
		AC_MSG_ERROR([no Platform Adaptation Layers could be configured for this platform (configure with '--disable-pals' if you wish to explicitly build without PALs)])
	fi
else
	AC_MSG_RESULT([$exec_pal_list])
fi
])

AC_DEFUN([EXEC_PAL_CONFIG],[
AC_REQUIRE([EX_ARG_ENABLE_PALS])dnl
	AC_MSG_RESULT([- attempting to configure the ]$1[ PAL...])

AS_VAR_SET([exec_pal_]$1[_enabled], ["no"])
AS_VAR_SET([exec_pal_]$1[_build_targeted], [no])
AS_VAR_SET([exec_pal_]$1[_build_monolith], [no])
m4_foreach([BUILDTYPE],[[Release], [Free], [Debug]], [
	m4_foreach([OBJTYPE],[[MOD], [DLL], [LIB]],[
		AS_VAR_SET([EXEC_PAL_]OBJTYPE[_]BUILDTYPE, [""])
		AS_VAR_SET([EXEC_PAL_]$1[_]OBJTYPE[_]BUILDTYPE, [""])
	])
])
AS_VAR_SET([EXEC_PAL_]$1[_cppflags], [""])
AS_VAR_SET([EXEC_PAL_]$1[_ldflags], [""])
AS_VAR_SET([EXEC_PAL_]$1[_libs], [""])

AS_VAR_SET([exec_pal_enabled],["no"])
AS_VAR_SET([exec_pal_build_targeted], [no])
AS_VAR_SET([exec_pal_build_monolith], [no])
AS_VAR_SET([EXEC_PAL_cppflags], [""])
AS_VAR_SET([EXEC_PAL_ldflags], [""])
AS_VAR_SET([EXEC_PAL_libs], [""])

m4_include([PAL/]$1[/config.ac])dnl

if test $exec_pal_enabled = yes ; then
	AS_VAR_APPEND([exec_pal_list],[" ]$1["])
	AS_VAR_SET([exec_pal_]$1[_enabled], ["yes"])
	AC_SUBST([exec_pal_]$1[_enabled])
	AS_VAR_SET([exec_pal_]$1[_build_targeted], [$exec_pal_build_targeted])
	AC_SUBST([exec_pal_]$1[_build_targeted])
	AS_VAR_SET([exec_pal_]$1[_build_monolith], [$exec_pal_build_monolith])
	AC_SUBST([exec_pal_]$1[_build_monolith])
	m4_foreach([BUILDTYPE],[[Release], [Free], [Debug]], [
		m4_foreach([OBJTYPE],[[MOD], [DLL], [LIB]],[
			if test -z "$[EXEC_PAL_]OBJTYPE[_]BUILDTYPE" ; then
				[EXEC_PAL_]OBJTYPE[_]BUILDTYPE[="$EXEC_PAL_]OBJTYPE["]
			fi
			AS_VAR_SET([EXEC_PAL_]$1[_]OBJTYPE[_]BUILDTYPE, ["$EXEC_PAL_]OBJTYPE[_]BUILDTYPE["])
			AC_SUBST([EXEC_PAL_]$1[_]OBJTYPE[_]BUILDTYPE)
		])
	])
	AS_VAR_SET([EXEC_PAL_]$1[_cppflags], ["$EXEC_PAL_cppflags"])
	AC_SUBST([EXEC_PAL_]$1[_cppflags])
	AS_VAR_SET([EXEC_PAL_]$1[_LDFLAGS], ["$EXEC_PAL_ldflags"])
	AC_SUBST([EXEC_PAL_]$1[_ldflags])
	AS_VAR_SET([EXEC_PAL_]$1[_LIBS], ["$EXEC_PAL_libs"])
	AC_SUBST([EXEC_PAL_]$1[_libs])
fi

AM_CONDITIONAL([EXEC_BUILD_TARGETED_]$1, [test "$exec_pal_]$1[_build_targeted" = "yes"])
AM_CONDITIONAL([EXEC_BUILD_MONOLITH_]$1, [test "$exec_pal_]$1[_build_monolith" = "yes"])
])
