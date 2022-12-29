AC_DEFUN([EX_CHECK_SIMULATOR],[
exec_build_simulator=yes
test $cross_compiling = yes && exec_build_simulator=no
AC_MSG_CHECKING([whether to build the Simulator])
AC_MSG_RESULT([$exec_build_simulator])
AM_CONDITIONAL([BUILD_SIMULATOR],[test x$exec_build_simulator = xyes])
if test x$exec_build_simulator = xyes ; then
	LT_LANG([CXX])
	if test $GXX = yes ; then
		AS_VAR_APPEND([AM_CXXFLAGS], [" -fno-rtti -fno-exceptions"])
	fi
fi
])
