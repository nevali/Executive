AC_DEFUN([EX_CHECK_SIMULATOR],[
ex_build_simulator=yes
test $cross_compiling = yes && ex_build_simulator=no
AC_MSG_CHECKING([whether to build Simulator versions])
AC_MSG_RESULT([$ex_build_simulator])
AM_CONDITIONAL([BUILD_SIMULATOR],[test x$ex_build_simulator = xyes])
])