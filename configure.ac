## Executive Microkernel
## Autoconf/Automake-based build system
##   This file is used to generate a "configure" script, which is included
##   in a distribution source package, but not stored in the Git repository,
##   and is used detect the system type, apply build configuration options,
##   and generate the Makefiles which are used to build the Executive.
##
##   Run "autoconf -fi" to generate a "configure" script from this file
##
##   Macros named EX_xxx or EXEC_xxx are defined in ${srcdir}/M4/*.m4

## Copyright 2015-2022 Mo McRoberts.
##
##  Licensed under the Apache License, Version 2.0 (the "License");
##  you may not use this file except in compliance with the License.
##  You may obtain a copy of the License at
##
##      http://www.apache.org/licenses/LICENSE-2.0
##
##  Unless required by applicable law or agreed to in writing, software
##  distributed under the License is distributed on an "AS IS" BASIS,
##  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
##  See the License for the specific language governing permissions and
##  limitations under the License.

## BuildScripts/get-version.sh generates a version number from git tags
AC_INIT([Executive],m4_esyscmd([/bin/sh BuildScripts/get-version.sh]))
## M4 macros are in a subdirectory named "M4"
AC_CONFIG_MACRO_DIR([M4])
## Build scripts are in a subdirectory named "BuildScripts"
AC_CONFIG_AUX_DIR([BuildScripts])
## Detect the system type
EXEC_CANONICAL_SYSTEM
## Detect the toolchain (compiler/linker/etc.) type
EX_CHECK_TOOLCHAIN
## By default, install plaform-specific files to a platform-specific
## subdirectory of '${prefix}'
##
## This only applies if the exec-prefix has not otherwise been specified
EX_EXEC_PREFIX_DEFAULT(['${prefix}/${host_bindir}'])
## By default, install to a subdirectory of the build directory (override with
## e.g., "./configure --prefix=/opt/local")
AC_PREFIX_DEFAULT([$(pwd)/BuildProducts])
## Determine which bundled developer tools to build and use
EX_CHECK_DEVTOOLS
## Allow "./configure --disable-pals"
EX_ARG_ENABLE_PALS
## Determine which build dispositions to enable
EX_ARG_ENABLE_DISPOSITIONS
## Initialise Automake
AM_INIT_AUTOMAKE([foreign subdir-objects])
## Disable automatic re-generation of the build system whenever changes are
## detecte
## <https://www.gnu.org/software/automake/manual/html_node/maintainer_002dmode.html>
AM_MAINTAINER_MODE
## Specify the location of the build configuration header file
AC_CONFIG_HEADERS([PrivateHeaders/BuildConfiguration.h])
## Define preprocessor macros identifying the package and build
EX_DEFINE_BUILDINFO
## Configure libtool
LT_INIT
## This implementation of the Executive is written in C
LT_LANG([C])
## Check that the host architecture is supported
EX_CHECK_ARCHITECTURE
## Check which build types to perform
EX_CHECK_BUILDTYPES
## Determine which Glue module to use
EX_CHECK_GLUE
## Check which Platform Adaptation Layers (PALs) to build
EX_CHECK_PALS
## Now know which PALs are being built, we can confirm the build dispositions
EX_CHECK_DISPOSITIONS
## Checks for the Executive runtime library 
AC_CHECK_HEADERS([stdarg.h stddef.h stdint.h stdlib.h float.h inttypes.h])
if test $ac_cv_sizeof_long_long -gt 0 ; then
	AC_DEFINE_UNQUOTED([HAVE_LONG_LONG_INT],[1],[define if the "long long int" type is available])
fi
if test $ac_cv_sizeof_unsigned_long_long -gt 0 ; then
	AC_DEFINE_UNQUOTED([HAVE_UNSIGNED_LONG_LONG_INT],[1],[define if the "unsigned long long int" type is available])
fi
if test $ac_cv_sizeof_long_double -gt 0 ; then
	AC_DEFINE_UNQUOTED([HAVE_LONG_DOUBLE],[1],[define if the "long double" type is available])
fi
## Silence the #warning embedded in header files generated from IDL not yet
## considered to be stable
AS_VAR_APPEND([AM_CPPFLAGS],[" -DW_NO_UNSTABLE_INTERFACES"])

## Specify substituted output files
AC_CONFIG_FILES([
Makefile
DeveloperTools/Makefile
Frameworks/Makefile
Frameworks/Executive/Makefile
Frameworks/Executive/IDL/Makefile
Frameworks/Executive/Headers/Makefile
Frameworks/Executive/Headers/Executive/Makefile
Frameworks/PAL/Makefile
Frameworks/PAL/Headers/Makefile
Frameworks/PAL/Headers/PAL/Makefile
PrivateHeaders/Makefile
PrivateHeaders/Executive/Makefile
PrivateHeaders/Executive/Internal/Makefile
Sources/Makefile
Sources/Runtime/Makefile
Sources/Runtime/snprintf/Makefile
Sources/Runtime/arm64/Makefile
Sources/Executive/Makefile
Sources/Allocator/Makefile
Sources/Allocator/dlmalloc/Makefile
Sources/Classes/Makefile
Sources/Directory/Makefile
Sources/Subsystems/Makefile
Glue/Makefile
Glue/posix/Makefile
Glue/linux/Makefile
PAL/Makefile
PAL/Stand-in/Makefile
PAL/POSIX/Makefile
Subsystems/Makefile
Subsystems/Stubs/Makefile
Subsystems/Bootstrap/Makefile
])
## Generate output files
AC_OUTPUT
