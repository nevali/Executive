AC_DEFUN([EX_CHECK_BUILDTYPES],[

AC_ARG_ENABLE([debug],[AS_HELP_STRING([--disable-debug],[disable debugging builds (default=enabled)])],,[enable_debug=auto])
AC_ARG_ENABLE([release],[AS_HELP_STRING([--enable-release],[enable optimised release builds (default=disabled)])],,[enable_release=auto])

	AC_MSG_CHECKING([what type of build to perform])
case "$enable_debug,$enable_release" in
	yes,yes)
		AC_MSG_ERROR([cannot specify --enable-debug and --enable-release together]) ;;
	auto,auto|auto,no)
		exec_build_type=debug ;;	
	yes,no|yes,auto)
		exec_build_type=debug ;;
	no,yes|auto,yes)
		exec_build_type=release ;;
	no,no|no,auto)
		exec_build_type=free ;;
	*)
		AC_MSG_ERROR([unexpected option provided to --enable-debug or --enable-release])
		;;
esac
AC_MSG_RESULT([$exec_build_type])

case "$exec_build_type" in
	debug)
		AS_VAR_APPEND([AM_CPPFLAGS],[" -DEXEC_BUILD_DEBUG=1 -DEXEC_BUILD_CONFIG='\"Debug\"'"])
		AS_VAR_SET([EXEC_BUILD_SUFFIX],[".Debug"])
		AC_SUBST([EXEC_BUILD_SUFFIX])
		enable_debug=yes ; enable_free=no ; enable_release=no ;;
	free)
		AS_VAR_APPEND([AM_CPPFLAGS],[" -DNDEBUG -DEXEC_BUILD_FREE=1 -DEXEC_BUILD_CONFIG='\"Free\"'"])
		AS_VAR_SET([EXEC_BUILD_SUFFIX],[".Free"])
		AC_SUBST([EXEC_BUILD_SUFFIX])
		enable_debug=no ; enable_free=yes ; enable_release=no ;;
	release)
		AS_VAR_APPEND([AM_CPPFLAGS],[" -DNDEBUG -DEXEC_BUILD_RELEASE=1 -DEXEC_BUILD_CONFIG='\"Release\"'"])
		AS_VAR_SET([EXEC_BUILD_SUFFIX],[""])
		AC_SUBST([EXEC_BUILD_SUFFIX])
		enable_debug=no ; enable_free=no ; enable_release=yes ;;
esac
AS_VAR_SET([EXEC_BUILD_TYPE],["$exec_build_type"])
AC_SUBST([EXEC_BUILD_TYPE])
AM_CONDITIONAL([BUILD_DEBUG],[test $exec_build_type = debug])
AM_CONDITIONAL([BUILD_FREE],[test $exec_build_type = free])
AM_CONDITIONAL([BUILD_RELEASE],[test $exec_build_type = release])
])