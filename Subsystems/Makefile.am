## Executive Microkernel
##   Sources/Subsystems/Makefile.am
##   Subsystems

## Subsystems are the programs executed by the Executive directly, and they are
## used to provide critical system services
##
## Some subsystems constitute Personalities: that is, they provide a defined
## operating environment for user programs to execute within
##
## There is not necessarily any technical difference between a "subsystem
## executable" and a "user program executable", but they're also not
## necessarily the same, either

AM_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS}

SUBDIRS = Bootstrap Stubs .

noinst_LTLIBRARIES = libResident.la

libResident_la_SOURCES = Resident.c
libResident_la_LIBADD = Bootstrap/libBootstrap.Resident.la
