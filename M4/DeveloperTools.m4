dnl EX_CHECK_DEVTOOLS
dnl - Determine which of the bundled developer tools should be built and used

AC_DEFUN([EX_CHECK_DEVTOOLS],[

	AC_ARG_ENABLE([idl],[AS_HELP_STRING([--disable-idl],[don't build the IDL compiler or regenerate any files from IDL source])])

	AS_VAR_SET([DeveloperTools_subdirs],[""])
	AC_MSG_CHECKING([whether to build and use the IDL compiler])
	if test x"$enable_idl" = x"no" ; then
		AC_MSG_RESULT([no])
		AS_VAR_SET([IDL],[true])
		with_idl=no
	else
		AC_MSG_RESULT([yes])
		with_idl=yes
		AC_CONFIG_SUBDIRS([DeveloperTools/idl])
		AS_VAR_SET([DeveloperTools_subdirs],["idl"])
		AS_VAR_SET([IDL],["\$(top_builddir)/DeveloperTools/idl/idl"])
	fi
	AC_SUBST([IDL])
	AC_SUBST([DeveloperTools_subdirs])
	AM_CONDITIONAL([WITH_IDL],[test x$with_idl = xyes])

])dnl
