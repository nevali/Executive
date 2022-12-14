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

nodist_noinst_DATA = PAL.${PALNAME}.lo

CLEANFILES = PAL.${PALNAME}.la libPAL.${PALNAME}.la PAL.${PALNAME}.lo

# XXX TODO: this should be if PAL_BUILD_MOD
if EXEC_BUILD_DYNAMIC

## Dynamic configuration: the Executive has the capability to locate and
## initialise an appropriate PAL (which does not need to be specified at build
## time) itself - to support this configuration we build a "PAL" module

noinst_LTLIBRARIES += PAL.la
nodist_noinst_DATA += PAL.${PALNAME}.la

PAL_la_SOURCES = ${PALSRC}
PAL_la_CPPFLAGS = @AM_CPPFLAGS@ -DEXEC_PAL_BUILD_MOD=1 ${WARNING_CPPFLAGS}
PAL_la_LDFLAGS = ${PAL_MOD_LDFLAGS}

PAL.${PALNAME}.la: PAL.la
	$(LIBTOOL) --mode=link $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(PAL_la_LDFLAGS) $(LDFLAGS) -o PAL.${PALNAME}.la $(PAL_la_OBJECTS)

endif

# XXX TODO: this should be if PAL_BUILD_DLL
if EXEC_BUILD_MODULAR

## Modular configuration: an external loader arranges for the correct PAL to be
## loaded, and so it doesn't need to be specified at build time - to support this
## configuration we build a libPAL shared (dynamically-linked) library

noinst_LTLIBRARIES += libPAL.la
nodist_noinst_DATA += libPAL.${PALNAME}.la

libPAL_la_SOURCES = ${PALSRC}
libPAL_la_LDFLAGS = -avoid-version -shared -rpath $(libdir)
libPAL_la_CPPFLAGS = @AM_CPPFLAGS@ -DEXEC_PAL_BUILD_DLL=1 ${WARNING_CPPFLAGS}

libPAL.${PALNAME}.la: libPAL.la
	$(LIBTOOL) --mode=link $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(libPAL_la_LDFLAGS) $(LDFLAGS) -o libPAL.${PALNAME}.la $(libPAL_la_OBJECTS)

endif

## To support (statically) targeted and monolith configurations, we build a
## version of the PAL for static linking

noinst_LTLIBRARIES += libPAL.Static.Release.la libPAL.Static.Free.la libPAL.Static.Debug.la

libPAL_Static_Release_la_SOURCES = ${PALSRC}
libPAL_Static_Release_la_CPPFLAGS = @AM_CPPFLAGS@ -DEXEC_PAL_BUILD_STATIC=1 ${WARNING_CPPFLAGS} ${RELEASE_CPPFLAGS}
libPAL_Static_Release_la_LDFLAGS =  -static

libPAL_Static_Free_la_SOURCES = ${PALSRC}
libPAL_Static_Free_la_CPPFLAGS = @AM_CPPFLAGS@ -DEXEC_PAL_BUILD_STATIC=1 ${WARNING_CPPFLAGS} ${FREE_CPPFLAGS}
libPAL_Static_Free_la_LDFLAGS =  -static

libPAL_Static_Debug_la_SOURCES = ${PALSRC}
libPAL_Static_Debug_la_CPPFLAGS = @AM_CPPFLAGS@ -DEXEC_PAL_BUILD_STATIC=1 ${WARNING_CPPFLAGS} ${DEBUG_CPPFLAGS}
libPAL_Static_Debug_la_LDFLAGS =  -static

PAL.${PALNAME}.lo: $(libPAL_Static_Release_la_OBJECTS)
	$(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link ld -r -o $@ $+

PAL.${PALNAME}.Debug.lo: $(libPAL_Static_Debug_la_OBJECTS)
	$(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link ld -r -o $@ $+

# Install the PAL binaries intended to be used at runtime as [lib]PAL.${PALNAME}
install-exec-hook:
	@echo " $(MKDIR_P) '$(DESTDIR)$(libdir)'"; \
	  $(MKDIR_P) "$(DESTDIR)$(libdir)" || exit 1; \
	  echo " $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) PAL.${PALNAME}.lo '$(DESTDIR)$(libdir)'"; \
	  $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) PAL.${PALNAME}.lo "$(DESTDIR)$(libdir)"
if EXEC_BUILD_DYNAMIC
	@echo " $(MKDIR_P) '$(DESTDIR)$(libdir)'"; \
	  $(MKDIR_P) "$(DESTDIR)$(libdir)" || exit 1; \
	  echo " $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) PAL.${PALNAME}.la '$(DESTDIR)$(libdir)'"; \
	  $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) PAL.${PALNAME}.la "$(DESTDIR)$(libdir)"
endif
if EXEC_BUILD_MODULAR
	@echo " $(MKDIR_P) '$(DESTDIR)$(libdir)'"; \
	  $(MKDIR_P) "$(DESTDIR)$(libdir)" || exit 1; \
	  echo " $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) libPAL.${PALNAME}.la '$(DESTDIR)$(libdir)'"; \
	  $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) libPAL.${PALNAME}.la "$(DESTDIR)$(libdir)"
endif
	for name in PAL PAL.${PALNAME} libPAL libPAL.${PALNAME} ; do \
		rm $(DESTDIR)$(libdir)/$$name.la || true ; \
		rm $(DESTDIR)$(libdir)/$$name.a || true ; \
		rm $(DESTDIR)$(libdir)/$$name.lo || true ; \
	done
