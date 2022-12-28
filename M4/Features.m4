dnl EX_CHECK_FEATURE_ENABLED([MACRO-NAME],[OPTION-NAME],[description])
dnl - Allow user to disable a feature
AC_DEFUN([_EX_CHECK_FEATURE],[
	if test x$feature_enabled = xyes ; then
		AC_MSG_RESULT([yes])
		AC_DEFINE_UNQUOTED([FEATURE_]$1, [1], [Enable ]$3)
	else
		AC_MSG_RESULT([no])
	fi
])

AC_DEFUN([EX_CHECK_FEATURE_ENABLED],[
	feature_enabled=yes
	AC_MSG_CHECKING([whether to enable ]]$3[)
	AC_ARG_ENABLE($2,[AS_HELP_STRING([--disable-]$2,[disable ]$3)],[feature_enabled=$enableval])
	_EX_CHECK_FEATURE([$1],[$2],[$3])
])

AC_DEFUN([EX_CHECK_FEATURE_DISABLED],[
	feature_enabled=no
	AC_MSG_CHECKING([whether to enable ]]$3[)
	AC_ARG_ENABLE($2,[AS_HELP_STRING([--enable-]$2,[enable ]$3)],[feature_enabled=$enableval])
	_EX_CHECK_FEATURE([$1],[$2],[$3])
])

AC_DEFUN([EX_CHECK_FEATURES],[
	EX_CHECK_FEATURE_ENABLED([BOOTPROGRESS],[boot-progress],[boot progress messages (at LogLevel=INFO)])
	EX_CHECK_FEATURE_ENABLED([PAL_DIAGNOSTICS],[pal-diagnostics],[/System/Platform/Diagnostics (where supported)])
	EX_CHECK_FEATURE_ENABLED([CONSOLE],[console],[/System/Platform/Console (where supported)])
	EX_CHECK_FEATURE_DISABLED([DEBUG_PHASING],[debug-phasing],[additional diagnostics when phase transitions occur])
	EX_CHECK_FEATURE_DISABLED([DEBUG_CONTEXTS],[debug-contexts],[additional diagnostics when context-switching])
	EX_CHECK_FEATURE_DISABLED([DEBUG_NAMESPACE],[debug-namespace],[additional diagnostics for namespace operations])
	EX_CHECK_FEATURE_DISABLED([DEBUG_CLASSES],[debug-classes],[additional diagnostics for class and metaclass operations])
	EX_CHECK_FEATURE_DISABLED([DEBUG_MEM],[debug-memory],[additional diagnostics for memory management operations])
	EX_CHECK_FEATURE_ENABLED([SELF_TESTS],[self-tests],[self-tests (where supported)])
	EX_CHECK_FEATURE_DISABLED([TRACE],[trace],[trace-level diagnostic logging])
	EX_CHECK_FEATURE_ENABLED([COOPERATIVE_TASKER],[cooperative-tasker],[enable the built-in co-operative tasker])
])
