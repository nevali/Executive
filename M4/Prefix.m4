dnl EX_EXEC_PREFIX_DEFAULT(EXEC-PREFIX)
dnl - Like AC_PREFIX_DEFAULT
AC_DEFUN([EX_EXEC_PREFIX_DEFAULT],[

	if test "$exec_prefix" = "NONE" ; then
		AS_VAR_SET([exec_prefix],[$1])
		true
	fi

])dnl
