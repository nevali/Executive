#ifndef RUNTIME_INTERNAL_PRIVATE_H_
# define RUNTIME_INTERNAL_PRIVATE_H_

# include <Runtime/Runtime.h>
# include <Executive/IWriteChannel.h>

typedef struct RuntimePrivateData RuntimePrivateData;

struct RuntimePrivateData
{
	IThread *mainThread;
	ITask *task;
	INamespace *ns;
	IAddressSpace *addressSpace;
#if 0
	IReadChannel *stdin;
#endif
	IWriteChannel *stdout;
	IWriteChannel *stderr;
};

extern RuntimePrivateData Rt__private__ RUNTIME_PRIVATE__("__Runtime_Private__");

/* This interface is called by the Simulator infrastructure to initialise the
 * Runtime framework after the embedded Executive has been initialised
 */
EXTERN_C void Rt__Initialise(IThread *mainThread) RUNTIME_PRIVATE__("__Runtime__Initialise__");

#endif /*!RUNTIME_INTERNAL_PRIVATE_H_*/
