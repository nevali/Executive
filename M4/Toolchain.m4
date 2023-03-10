dnl EX_CHECK_TOOLCHAIN
dnl - Attempt to determine what kind of toolchain (Clang, GCC, OpenWatcom,
dnl   bcc, etc.) is available

AC_DEFUN([EX_CHECK_TOOLCHAIN],[

CPPFLAGS="${CPPFLAGS}"
CFLAGS="${CFLAGS}"
CXXFLAGS="${CXXFLAGS}"

AC_SUBST([AM_CPPFLAGS])
AC_SUBST([AM_CFLAGS])
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])

## Depending upon the host type, the default toolchain will vary, as will the
## amount of support that needs to be provided for it to be usable

if test -z "$CC" ; then
	case "$host_platform" in
		msdos|os2|winnt)
			EX_CHECK_TOOLCHAIN_WATCOM
			;;
		*)
			EX_CHECK_TOOLCHAIN_CLANG
			;;
	esac
fi

AC_ARG_ENABLE([errors-as-warnings],[AS_HELP_STRING([--disable-errors-as-warnings],[don't treat compiler warnings as errors])],,[enable_errors_as_warnings=yes])
if test x"$GCC" = x"yes" ; then
	AS_VAR_APPEND([AM_CPPFLAGS],[" -W -Wall -Wno-null-pointer-arithmetic -Wno-address"])
	if test $enable_errors_as_warnings = yes ; then
		AS_VAR_SET([WARNING_CPPFLAGS],["-Werror"])
	fi
fi

AS_VAR_APPEND([AM_CPPFLAGS],[" -I\${top_builddir}/PrivateHeaders"])
AS_VAR_APPEND([AM_CPPFLAGS],[" -I\${top_srcdir}/PrivateHeaders"])
AS_VAR_APPEND([AM_CPPFLAGS],[" -I\${top_builddir}/Frameworks/Executive/Headers"])
AS_VAR_APPEND([AM_CPPFLAGS],[" -I\${top_srcdir}/Frameworks/Executive/Headers"])
AS_VAR_APPEND([AM_CPPFLAGS],[" -I\${top_builddir}/Frameworks/PAL/Headers"])
AS_VAR_APPEND([AM_CPPFLAGS],[" -I\${top_srcdir}/Frameworks/PAL/Headers"])
AS_VAR_APPEND([AM_CPPFLAGS],[" -I\${top_builddir}/Frameworks/Runtime/Headers"])
AS_VAR_APPEND([AM_CPPFLAGS],[" -I\${top_srcdir}/Frameworks/Runtime/Headers"])

AC_SUBST([WARNING_CPPFLAGS])
])

AC_DEFUN([EX_CHECK_TOOLCHAIN_WATCOM],[
AC_MSG_CHECKING([for OpenWatcom])
if test -z "$WATCOM" ; then
	if test -d /usr/local/watcom ; then
		WATCOM="/usr/local/watcom"
	fi
fi
test -d "$WATCOM" || unset WATCOM
if test -z "$WATCOM" ; then
	AC_MSG_RESULT([not found])
else
	AC_MSG_RESULT([$WATCOM])
fi

])

AC_DEFUN([EX_CHECK_TOOLCHAIN_CLANG],[
dnl EXEC_CHECK_TOOLCHAIN

AC_PROG_CC([clang gcc c99 cc])

])
