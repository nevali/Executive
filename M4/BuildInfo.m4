dnl EX_DEFINE_BUILDINFO
dnl - Set macros that identify the build and product
AC_DEFUN([EX_DEFINE_BUILDINFO],[
dnl ## Build identification
dnl
dnl Various environment variables are given default values if they are not
dnl set, and made available to the preprocessor

now=$(date +%s)

PRODUCT_NAME=${PRODUCT_NAME:-"The Operating System"}
AC_DEFINE_UNQUOTED([PRODUCT_NAME],["${PRODUCT_NAME}"],[The name of the product this component is part of])
AC_SUBST([PRODUCT_NAME])

PRODUCT_SHORTNAME=${PRODUCT_SHORTNAME:-"${PRODUCT_NAME}"}
AC_DEFINE_UNQUOTED([PRODUCT_SHORTNAME],["${PRODUCT_SHORTNAME}"],[The abbreviated name of the product this component is part of])
AC_SUBST([PRODUCT_SHORTNAME])

PRODUCT_FULLNAME=${PRODUCT_FULLNAME:-"${PRODUCT_NAME}"}
AC_DEFINE_UNQUOTED([PRODUCT_FULLNAME],["${PRODUCT_FULLNAME}"],[The expanded name of the product this component is part of])
AC_SUBST([PRODUCT_FULLNAME])

PRODUCT_RELEASE=${PRODUCT_RELEASE:-"Release 0/Development Build"}
AC_DEFINE_UNQUOTED([PRODUCT_RELEASE],["${PRODUCT_RELEASE}"],[The release of the product this component is part of])
AC_SUBST([PRODUCT_RELEASE])

PRODUCT_SHORTREL=${PRODUCT_SHORTREL:-"R0-DEV"}
AC_DEFINE_UNQUOTED([PRODUCT_SHORTREL],["${PRODUCT_SHORTREL}"],[The abbreviated form of the release of the product this component is part of])
AC_SUBST([PRODUCT_SHORTREL])

PRODUCT_NAME_RELEASE=${PRODUCT_NAME_RELEASE:-"${PRODUCT_NAME} ${PRODUCT_RELEASE}"}

PRODUCT_BUILD_USER=${PRODUCT_BUILD_USER:-$(id -un)}
AC_DEFINE_UNQUOTED([PRODUCT_BUILD_USER],["${PRODUCT_BUILD_USER}"],[The name of the user who performed this build])
AC_SUBST([PRODUCT_BUILD_USER])

PRODUCT_BUILD_HOST=${PRODUCT_BUILD_HOST:-$(hostname | cut -f1 -d.)}
AC_DEFINE_UNQUOTED([PRODUCT_BUILD_HOST],["${PRODUCT_BUILD_HOST}"],[The name of the host this build was performed on])
AC_SUBST([PRODUCT_BUILD_HOST])

PRODUCT_BUILD_DATE=${PRODUCT_BUILD_DATE:-$(TZ=UTC date -jf %s $now "+%Y-%m-%d" 2>/dev/null)}
AC_DEFINE_UNQUOTED([PRODUCT_BUILD_DATE],["${PRODUCT_BUILD_DATE}"],[The date of this build in YYYY-MM-DD format])
AC_SUBST([PRODUCT_BUILD_DATE])

PRODUCT_BUILD_YEAR=${PRODUCT_BUILD_YEAR:-$(TZ=UTC date -jf %s $now "+%Y"  2>/dev/null)}
AC_DEFINE_UNQUOTED([PRODUCT_BUILD_YEAR],[${PRODUCT_BUILD_YEAR}],[The year of this build])
AC_SUBST([PRODUCT_BUILD_YEAR])

PRODUCT_BUILD_MONTH=${PRODUCT_BUILD_MONTH:-$(TZ=UTC date -jf %s $now "+%m"  2>/dev/null)}
case "$PRODUCT_BUILD_MONTH" in
	0*)
		PRODUCT_BUILD_MONTH=$(echo $PRODUCT_BUILD_MONTH | cut -c2-)
		;;
esac
AC_DEFINE_UNQUOTED([PRODUCT_BUILD_MONTH],[${PRODUCT_BUILD_MONTH}],[The month of this build])
AC_SUBST([PRODUCT_BUILD_MONTH])

PRODUCT_BUILD_DAY=${PRODUCT_BUILD_DAY:-$(TZ=UTC date -jf %s $now "+%d"  2>/dev/null)}
case "$PRODUCT_BUILD_DAY" in
	0*)
		PRODUCT_BUILD_DAY=$(echo $PRODUCT_BUILD_DAY | cut -c2-)
		;;
esac
AC_DEFINE_UNQUOTED([PRODUCT_BUILD_DAY],[${PRODUCT_BUILD_DAY}],[The day of the month of this build])
AC_SUBST([PRODUCT_BUILD_DAY])

PRODUCT_BUILD_TIME=${PRODUCT_BUILD_TIME:-$(TZ=UTC date -jf %s $now "+%H:%M:%S" 2>/dev/null)}
AC_DEFINE_UNQUOTED([PRODUCT_BUILD_TIME],["${PRODUCT_BUILD_TIME}"],[The timestamp of this build in HH:MM:SS format])
AC_SUBST([PRODUCT_BUILD_TIME])

PRODUCT_BUILD_ID=${PRODUCT_BUILD_ID:-$(printf "%x\n" $now)}
AC_DEFINE_UNQUOTED([PRODUCT_BUILD_ID],[0x${PRODUCT_BUILD_ID}],[A hexadecimal number identifying this particular build])
AC_DEFINE_UNQUOTED([PRODUCT_BUILD_ID_STR],["${PRODUCT_BUILD_ID}"],[A string containing a hexadecimal number identifying this particular build])
AC_SUBST([PRODUCT_BUILD_ID])

])dnl
