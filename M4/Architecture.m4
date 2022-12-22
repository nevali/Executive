dnl EX_CHECK_ARCHITECTURE
dnl - Check that the source tree contains support for the host architecture
AC_DEFUN([EX_CHECK_ARCHITECTURE],[

AC_MSG_CHECKING([if architecture $host_family is supported])
if test -d "$srcdir/Frameworks/Executive/Headers/Executive/${host_family}" && \
	test -r "$srcdir/Frameworks/Executive/Headers/Executive/${host_family}/Types.h" ; then
	AC_MSG_RESULT([yes])
else
	AC_MSG_RESULT([no])
	AC_MSG_ERROR([support for architecture ${host_family} is currently not available])
fi

## Checks for basic types

AC_CHECK_SIZEOF([int])
AC_CHECK_SIZEOF([long])
AC_CHECK_SIZEOF([long long])
AC_CHECK_SIZEOF([unsigned long long])
AC_CHECK_SIZEOF([long double])
AC_CHECK_SIZEOF([void *])

])dnl
