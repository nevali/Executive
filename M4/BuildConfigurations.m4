AC_DEFUN([EX_CHECK_BUILDCONFIG],[

AC_ARG_VAR([EXEC_BUILD_CONFIG],[the name of a build configuration to use])
AC_ARG_VAR([BUILDCONF],[the name of a build configuration to use (if EXEC_BUILD_CONFIG is unset)])
test x"$EXEC_BUILD_CONFIG" = x"" && EXEC_BUILD_CONFIG="$BUILDCONF"
AC_ARG_WITH([build-config],[AS_HELP_STRING([--with-build-config=NAME],[use build configuration NAME])],[EXEC_BUILD_CONFIG="$withval"])

if test x"$EXEC_BUILD_CONFIG" = x"" ; then
	# the default build configuration depends upon whether this is a source
	# distribution or a git clone - GENERIC for the former, DEVELOP for the
	# latter
	#
	# this means that users building from source get a standard build by
	# default, whilst developers working within a git repository get
	# a development build by default; obviously both can be overridden,
	# this is only the default 
	if test -d "$srcdir/.git" ; then
		EXEC_BUILD_CONFIG="DEVELOP"
	else
		EXEX_BUILD_CONFIG="GENERIC"
	fi
fi

AC_MSG_CHECKING([which build configuration to use])

# ac_enable option [value]
ac_enable() {
	_var=enable_"[$]1"
	m4_changequote(,)dnl
	_var=$(echo $_var | sed -e "s%[^A-Za-z]%_%g")
	m4_changequote([,])dnl
	_val="[$]2"
	test x"$_val" = x"" && _val="yes"
	eval $_var="\$_val"
	AC_MSG_RESULT([ - setting option --enable-[$]1=$_val])
}

ac_disable() {
	ac_enable "[$]1" "no"
}

# ac_with option [value]
ac_with() {
	_var=with_"[$]1"
	m4_changequote(,)dnl
	_var=$(echo $_var | sed -e "s%[^A-Za-z]%_%g")
	m4_changequote([,])dnl
	_val="[$]2"
	test x"$_val" = x"" && _val="yes"
	AC_MSG_RESULT([ - setting option --with-[$]1=$_val])
	eval $_var=\$val
}

ac_without() {
	ac_with "[$]1" "no"
}

if test "$EXEC_BUILD_CONFIG" = "no" ; then
	EXEC_BUILD_CONFIG=""
	AC_MSG_RESULT([none])
else
	AC_MSG_RESULT([${EXEC_BUILD_CONFIG}])
	AC_SUBST([EXEC_BUILD_CONFIG])
	AC_DEFINE_UNQUOTED([EXEC_BUILD_CONFIG],["${EXEC_BUILD_CONFIG}"],[The name of the build configuration])
	if test -r "./BuildConfigurations/${EXEC_BUILD_CONFIG}" ; then
		set -e
		. "./BuildConfigurations/${EXEC_BUILD_CONFIG}"
		set +e
	elif test -r "$srcdir/BuildConfigurations/${EXEC_BUILD_CONFIG}" ; then
		set -e
		. "$srcdir/BuildConfigurations/${EXEC_BUILD_CONFIG}"
		set +e
	else
		AC_MSG_ERROR([cannot locate BuildConfigurations/${EXEC_BUILD_CONFIG} in either build or source trees])
	fi
fi

])