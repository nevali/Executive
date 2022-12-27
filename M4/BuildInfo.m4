dnl EX_DEFINE_BUILDINFO
dnl - Set macros that identify the build and product
AC_DEFUN([EX_DEFINE_BUILDINFO],[
dnl ## Build identification
dnl
dnl Various environment variables are given default values if they are not
dnl set, and made available to the preprocessor

now=$(date +%s)

PRODUCT_NAME=${PRODUCT_NAME:-"The Operating System"}
dnl AC_DEFINE_UNQUOTED([PRODUCT_NAME],["${PRODUCT_NAME}"],[The name of the product this component is part of])
AC_SUBST([PRODUCT_NAME])

PRODUCT_SHORTNAME=${PRODUCT_SHORTNAME:-"${PRODUCT_NAME}"}
dnl AC_DEFINE_UNQUOTED([PRODUCT_SHORTNAME],["${PRODUCT_SHORTNAME}"],[The abbreviated name of the product this component is part of])
AC_SUBST([PRODUCT_SHORTNAME])

PRODUCT_FULLNAME=${PRODUCT_FULLNAME:-"${PRODUCT_NAME}"}
dnl AC_DEFINE_UNQUOTED([PRODUCT_FULLNAME],["${PRODUCT_FULLNAME}"],[The expanded name of the product this component is part of])
AC_SUBST([PRODUCT_FULLNAME])

PRODUCT_RELEASE=${PRODUCT_RELEASE:-"Release 0/Development Build"}
dnl AC_DEFINE_UNQUOTED([PRODUCT_RELEASE],["${PRODUCT_RELEASE}"],[The release of the product this component is part of])
AC_SUBST([PRODUCT_RELEASE])

PRODUCT_SHORTREL=${PRODUCT_SHORTREL:-"R0-DEV"}
dnl AC_DEFINE_UNQUOTED([PRODUCT_SHORTREL],["${PRODUCT_SHORTREL}"],[The abbreviated form of the release of the product this component is part of])
AC_SUBST([PRODUCT_SHORTREL])

PRODUCT_NAME_RELEASE=${PRODUCT_NAME_RELEASE:-"${PRODUCT_NAME} ${PRODUCT_RELEASE}"}
AC_SUBST([PRODUCT_NAME_RELEASE])

PRODUCT_BUILD_USER=${PRODUCT_BUILD_USER:-$(id -un)}
AC_SUBST([PRODUCT_BUILD_USER])

PRODUCT_BUILD_HOST=${PRODUCT_BUILD_HOST:-$(hostname | cut -f1 -d.)}
AC_SUBST([PRODUCT_BUILD_HOST])

PRODUCT_BUILD_DATE=${PRODUCT_BUILD_DATE:-$(TZ=UTC date -jf %s $now "+%Y-%m-%d" || date "+%Y-%m-%d" 2>/dev/null)}
AC_SUBST([PRODUCT_BUILD_DATE])

PRODUCT_BUILD_YEAR=${PRODUCT_BUILD_YEAR:-$(TZ=UTC date -jf %s $now "+%Y" || date "+%Y"  2>/dev/null)}
AC_SUBST([PRODUCT_BUILD_YEAR])

PRODUCT_BUILD_MONTH=${PRODUCT_BUILD_MONTH:-$(TZ=UTC date -jf %s $now "+%m" || date "+%m" 2>/dev/null)}
case "$PRODUCT_BUILD_MONTH" in
	0*)
		PRODUCT_BUILD_MONTH=$(echo $PRODUCT_BUILD_MONTH | cut -c2-)
		;;
esac
AC_SUBST([PRODUCT_BUILD_MONTH])

PRODUCT_BUILD_DAY=${PRODUCT_BUILD_DAY:-$(TZ=UTC date -jf %s $now "+%d" || date "+%d" 2>/dev/null)}
case "$PRODUCT_BUILD_DAY" in
	0*)
		PRODUCT_BUILD_DAY=$(echo $PRODUCT_BUILD_DAY | cut -c2-)
		;;
esac
AC_SUBST([PRODUCT_BUILD_DAY])

PRODUCT_BUILD_TIME=${PRODUCT_BUILD_TIME:-$(TZ=UTC date -jf %s $now "+%H:%M:%S" || date "+%H:%M:%S" 2>/dev/null)}
AC_SUBST([PRODUCT_BUILD_TIME])

PRODUCT_BUILD_ID=${PRODUCT_BUILD_ID:-$(printf "%x\n" $now)}
AC_SUBST([PRODUCT_BUILD_ID])

AC_CONFIG_COMMANDS([PrivateHeaders/ProductInformation.h],[
	rm -f PrivateHeaders/ProductInformation.h
	cat >>PrivateHeaders/ProductInformation.h <<EOF
/* automatically generated by 'configure' */

#define PRODUCT_NAME "${PRODUCT_NAME}"
#define PRODUCT_RELEASE "${PRODUCT_RELEASE}"
#define PRODUCT_FULLNAME "${PRODUCT_FULLNAME}"
#define PRODUCT_SHORTNAME "${PRODUCT_SHORTNAME}"
#define PRODUCT_SHORTREL "${PRODUCT_SHORTREL}"
#define PRODUCT_NAME_RELEASE "${PRODUCT_NAME_RELEASE}"
EOF
],[
PRODUCT_NAME="${PRODUCT_NAME}"
PRODUCT_RELEASE="${PRODUCT_RELEASE}"
PRODUCT_FULLNAME="${PRODUCT_FULLNAME}"
PRODUCT_SHORTNAME="${PRODUCT_SHORTNAME}"
PRODUCT_SHORTREL="${PRODUCT_SHORTREL}"
PRODUCT_NAME_RELEASE="${PRODUCT_NAME_RELEASE}"
])dnl
AC_CONFIG_COMMANDS([PrivateHeaders/BuildInformation.h],[
	rm -f PrivateHeaders/BuildInformation.h
	cat >>PrivateHeaders/BuildInformation.h <<EOF
/* automatically generated by 'configure' */

#define PRODUCT_BUILD_DATE "${PRODUCT_BUILD_DATE}"
#define PRODUCT_BUILD_TIME "${PRODUCT_BUILD_TIME}"
#define PRODUCT_BUILD_HOST "${PRODUCT_BUILD_HOST}"
#define PRODUCT_BUILD_USER "${PRODUCT_BUILD_USER}"
#define PRODUCT_BUILD_ID 0x${PRODUCT_BUILD_ID}
#define PRODUCT_BUILD_ID_STR "${PRODUCT_BUILD_ID}"

#define PRODUCT_BUILD_YEAR ${PRODUCT_BUILD_YEAR}
#define PRODUCT_BUILD_MONTH ${PRODUCT_BUILD_MONTH}
#define PRODUCT_BUILD_DAY ${PRODUCT_BUILD_DAY}
EOF
],[
PRODUCT_BUILD_DATE="${PRODUCT_BUILD_DATE}"
PRODUCT_BUILD_TIME="${PRODUCT_BUILD_TIME}"
PRODUCT_BUILD_HOST="${PRODUCT_BUILD_HOST}"
PRODUCT_BUILD_USER="${PRODUCT_BUILD_USER}"
PRODUCT_BUILD_ID="${PRODUCT_BUILD_ID}"
PRODUCT_BUILD_YEAR="${PRODUCT_BUILD_YEAR}"
PRODUCT_BUILD_MONTH="${PRODUCT_BUILD_MONTH}"
PRODUCT_BUILD_DAY="${PRODUCT_BUILD_DAY}"
])dnl
])dnl
