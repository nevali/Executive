AC_DEFUN([EX_CHECK_GLUE],[
dnl ## Glue selection
dnl
dnl This configuration must result in exactly one Glue implementation for the
dnl build to be possible. The order of this list is significant, with higher-
dnl priority matches being towards the top of the list; once a Glue
dnl implementation indicates that it's compatible with the target platform and
dnl build options, the selection is made and no further candidates are
dnl evaluated

AC_MSG_RESULT([determining available Glue implementations for $host ($host_type)...])

dnl ## Freestanding glue
dnl
dnl Freestanding builds are those where the resulting Executive executable is
dnl intended to be started directly by a system's firmware or bootloader

dnl The "multiboot" glue is used to allow the Executive to launched by a
dnl Multiboot-compliant bootloader, such as GRUB

dnl EXEC_GLUE_CONFIG([multiboot])

dnl The "uefi" glue is used to build a version for booting on UEFI systems

dnl EXEC_GLUE_CONFIG([uefi])

dnl ## Kernel extension glue
dnl
dnl Kernel extension glue is used where the Executive is being built as a
dnl kernel extension (module, or device driver) for another operating system

dnl ## Native glue
dnl
dnl Native builds are those targeting a particular operating system kernel,
dnl but do not make use of the standard libraries and instead makes system
dnl calls directly. As such, there is different glue for each host supported
dnl host kernel

EXEC_GLUE_CONFIG([linux])

dnl ## Hosted glue

dnl The "dos" glue allows the Executive to be built as an executable that runs
dnl on MS-DOS-compatible (PC-DOS, FreeDOS, etc.) systems

dnl EXEC_GLUE_CONFIG([dos])

dnl The "posix" glue can be used for any hosted build (i.e., one creating an
dnl ordinary user-space executable) targeting a Posix-like operating system,
dnl such as Linux, FreeBSD, or macOS

EXEC_GLUE_CONFIG([posix])

dnl The "stdc" glue can be used for any hosted build targeting an operating
dnl system that provides an environment specified by the ISO C specifications

EXEC_GLUE_CONFIG([stdc])

AC_MSG_CHECKING([which Glue implementation to build])
if test -z "$exec_glue" ; then
	AC_MSG_RESULT([none found])
	AC_MSG_ERROR([unable to determine Glue to use for a $host_type $host_platform build])
else
	AC_MSG_RESULT([$exec_glue])
fi
])dnl
AC_DEFUN([EXEC_GLUE_CONFIG],[
	if test -z "$exec_glue" ; then
		AC_MSG_RESULT([ - attempting to configure ]$1[...])
		AS_VAR_SET([exec_glue_enabled], ["no"])
		AS_VAR_SET([EXEC_GLUE_OBJECT_DYNAMIC], [""])
		AS_VAR_SET([EXEC_GLUE_OBJECT_MODULAR], [""])
		AS_VAR_SET([EXEC_GLUE_OBJECT_TARGETED], [""])
		AS_VAR_SET([EXEC_GLUE_OBJECT_MONOLITH], [""])
		AS_VAR_SET([EXEC_GLUE_DYNAMIC_LIBS], [""])
		AS_VAR_SET([EXEC_GLUE_CPPFLAGS], [""])
		AS_VAR_SET([EXEC_GLUE_LDFLAGS], [""])
		m4_include([Sources/Glue/]$1[/config.ac])dnl
		if test "$exec_glue_enabled" = "yes" ; then
			AS_VAR_SET([exec_glue],["]$1["])
		else
			AS_VAR_SET([exec_glue], [""])
		fi
		AC_SUBST([exec_glue])
		AC_SUBST([EXEC_GLUE_OBJECT_DYNAMIC])
		AC_SUBST([EXEC_GLUE_OBJECT_MODULAR])
		AC_SUBST([EXEC_GLUE_OBJECT_TARGETED])
		AC_SUBST([EXEC_GLUE_OBJECT_MONOLITH])
		AC_SUBST([EXEC_GLUE_DYNAMIC_LIBS])
		AC_SUBST([EXEC_GLUE_CPPFLAGS])
		AC_SUBST([EXEC_GLUE_LDFLAGS])
	fi
])
