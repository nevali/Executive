## Executive Microkernel
##
## Platform Adaptation Layers (PALs)

## Copyright 2017 Mo McRoberts.
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

# Each PAL can be built in a number of different ways from the same sources,
# depending upon the target platform. To make this easier, the build logic
# is centralised here

lib_LTLIBRARIES =
noinst_LTLIBRARIES = 
nodist_noinst_DATA = libPAL.${PALNAME}@EXEC_BUILD_SUFFIX@.Static.la ../PAL.${PALNAME}@EXEC_BUILD_SUFFIX@.lo
LIBS =
CLEANFILES = *.la *.lo
PALCPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS}

# Build convenience libraries for each of the types of PAL we can use
noinst_LTLIBRARIES += libPALx.Static.la
if EXEC_BUILD_MODULAR
noinst_LTLIBRARIES +=  libPALx.Module.la
endif
if EXEC_BUILD_DYNAMIC
noinst_LTLIBRARIES += libPALx.DLL.la
endif

libPALx_Static_la_SOURCES = ${PALSRC}
libPALx_Static_la_CPPFLAGS = $(PALCPPFLAGS) -DEXEC_PAL_BUILD_STATIC=1
libPALx_Module_la_SOURCES = ${PALSRC}
libPALx_Module_la_CPPFLAGS = $(PALCPPFLAGS) -DEXEC_PAL_BUILD_MOD=1
libPALx_DLL_la_SOURCES = ${PALSRC}
libPALx_DLL_la_CPPFLAGS = $(PALCPPFLAGS) -DEXEC_PAL_BUILD_DLL=1


# XXX TODO: this should be if PAL_BUILD_MOD
if EXEC_BUILD_DYNAMIC
## Dynamic configuration: the Executive has the capability to locate and
## initialise an appropriate PAL (which does not need to be specified at build
## time) itself - to support this configuration we build a "PAL" module
nodist_noinst_DATA += ../PAL.${PALNAME}@EXEC_BUILD_SUFFIX@.la
endif

# XXX TODO: this should be if PAL_BUILD_DLL
if EXEC_BUILD_MODULAR
## Modular configuration: an external loader arranges for the correct PAL to be
## loaded, and so it doesn't need to be specified at build time - to support this
## configuration we build a libPAL shared (dynamically-linked) library
nodist_noinst_DATA += ../libPAL.${PALNAME}@EXEC_BUILD_SUFFIX@.la
endif

libPAL.${PALNAME}@EXEC_BUILD_SUFFIX@.Static.la: libPALx.Static.la
	@echo "Creating libPAL.${PALNAME}@EXEC_BUILD_SUFFIX@.la static library" >&2
	$(LIBTOOL) --mode=link $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) -avoid-version -all-static -rpath $(libdir) $(LDFLAGS) -o $@ $+

../PAL.${PALNAME}@EXEC_BUILD_SUFFIX@.lo: libPALx.Static.la
	@echo "Creating relocatable PAL.${PALNAME}@EXEC_BUILD_SUFFIX@.lo" >&2
	$(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link ld -r -o $@ $+
../libPAL.${PALNAME}@EXEC_BUILD_SUFFIX@.la: libPALx.DLL.la
	@echo "Creating libPAL.${PALNAME}@EXEC_BUILD_SUFFIX@.la shared library" >&2
	$(LIBTOOL) --mode=link $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) -avoid-version -shared -rpath $(libdir) $(LDFLAGS) -o $@ $+
../PAL.${PALNAME}@EXEC_BUILD_SUFFIX@.la: libPALx.Module.la
	@echo "Creating PAL.${PALNAME}@EXEC_BUILD_SUFFIX@.la dynamic shared object" >&2
	$(LIBTOOL) --mode=link $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(PAL_MOD_ldflags) $(LDFLAGS) -o $@ $+


# Install the PAL binaries intended to be used at runtime as [lib]PAL.${PALNAME}
install-exec-hook:
	@echo " $(MKDIR_P) '$(DESTDIR)$(libdir)'"; \
	  $(MKDIR_P) "$(DESTDIR)$(libdir)" || exit 1; \
	  echo " $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) ../PAL.${PALNAME}@EXEC_BUILD_SUFFIX@.lo '$(DESTDIR)$(libdir)'"; \
	  $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) ../PAL.${PALNAME}@EXEC_BUILD_SUFFIX@.lo "$(DESTDIR)$(libdir)"
if EXEC_BUILD_DYNAMIC
	@echo " $(MKDIR_P) '$(DESTDIR)$(libdir)'"; \
	  $(MKDIR_P) "$(DESTDIR)$(libdir)" || exit 1; \
	  echo " $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) ../PAL.${PALNAME}@EXEC_BUILD_SUFFIX@.la '$(DESTDIR)$(libdir)'"; \
	  $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) ../PAL.${PALNAME}@EXEC_BUILD_SUFFIX@.la "$(DESTDIR)$(libdir)"
endif
if EXEC_BUILD_MODULAR
	@echo " $(MKDIR_P) '$(DESTDIR)$(libdir)'"; \
	  $(MKDIR_P) "$(DESTDIR)$(libdir)" || exit 1; \
	  echo " $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) ../libPAL.${PALNAME}@EXEC_BUILD_SUFFIX@.la '$(DESTDIR)$(libdir)'"; \
	  $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) ../libPAL.${PALNAME}@EXEC_BUILD_SUFFIX@.la "$(DESTDIR)$(libdir)"
endif
	for name in PAL PAL.${PALNAME}@EXEC_BUILD_SUFFIX@ libPAL@EXEC_BUILD_SUFFIX@ libPAL.${PALNAME}@EXEC_BUILD_SUFFIX@ ; do \
		rm $(DESTDIR)$(libdir)/$$name.la || true ; \
		rm $(DESTDIR)$(libdir)/$$name.a || true ; \
		rm $(DESTDIR)$(libdir)/$$name.lo || true ; \
	done
