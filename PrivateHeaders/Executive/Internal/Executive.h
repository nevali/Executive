/* This header is used by the Executive's start-up code (Sources/entrypoint.c) */

#include <Executive/IPlatform.h>

struct ExecutiveEntryParameters;

int Executive_initialise(struct ExecutiveEntryParameters *params, IPlatform *platform);
