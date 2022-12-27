/* Executive Microkernel
 * POSIX Platform Adaptation Layer - Console device
 */

/* Copyright (c) 2015-2022 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#if FEATURE_CONSOLE

# include "p_POSIX.h"

# define INTF_TO_CLASS(i)              (PAL_POSIX_Console *)((i)->instptr)

static void PAL_POSIX_Console_start(void);

static STATUS PAL_POSIX_Console_queryInterface(IObject *me, REFUUID iid, void **out);
static REFCOUNT PAL_POSIX_Console_retain(IObject *me);
static REFCOUNT PAL_POSIX_Console_release(IObject *me);

static size_t PAL_POSIX_Console_write(IWriteChannel *self, const char *str);
static size_t PAL_POSIX_Console_writeLn(IWriteChannel *self, const char *str);

static struct IObject_vtable_ PAL_POSIX_Console_IObject_vtable = {
	PAL_POSIX_Console_queryInterface,
	PAL_POSIX_Console_retain,
	PAL_POSIX_Console_release
};

static struct IWriteChannel_vtable_ PAL_POSIX_Console_IWriteChannel_vtable = {
	(STATUS (*)(IWriteChannel *, REFUUID, void **)) &PAL_POSIX_Console_queryInterface,
	(REFCOUNT (*)(IWriteChannel *)) &PAL_POSIX_Console_retain,
	(REFCOUNT (*)(IWriteChannel *))PAL_POSIX_Console_release,
	PAL_POSIX_Console_send,
	PAL_POSIX_Console_write,
	PAL_POSIX_Console_writeLn
};

static PAL_POSIX_Console PAL_POSIX_console = {
	{ NULL, NULL }, /* Object */
	{ NULL, NULL }, /* WriteChannel */
	{
		false	
	}
};

void
PAL_POSIX_Console_init(void)
{
	PAL_POSIX_console.Object.lpVtbl = (void *) &PAL_POSIX_Console_IObject_vtable;
	PAL_POSIX_console.Object.instptr = &PAL_POSIX_console;
	PAL_POSIX_console.WriteChannel.lpVtbl = &PAL_POSIX_Console_IWriteChannel_vtable;
	PAL_POSIX_console.WriteChannel.instptr = &PAL_POSIX_console;
	PAL_POSIX_Platform_setConsole(&PAL_POSIX_console);
}

/* IObject */

static STATUS
PAL_POSIX_Console_queryInterface(IObject *me, REFUUID riid, void **ptr)
{
	UNUSED__(me);

	if(!memcmp(riid, &IID_IObject, sizeof(UUID)))
	{
		if(ptr)
		{
			/* no retain() because this class is a singleton */
			*ptr = &(PAL_POSIX_console.Object);
		}
		return E_SUCCESS;
	}
	if(!memcmp(riid, &IID_IWriteChannel, sizeof(UUID)))
	{
		if(ptr)
		{
			*ptr = &(PAL_POSIX_console.WriteChannel);
		}
		return E_SUCCESS;
	}
	return E_NOENT;
}

static REFCOUNT
PAL_POSIX_Console_retain(IObject *me)
{
	UNUSED__(me);
	
	/* PAL_POSIX_Console is a singleton */
	return 2;
}

static REFCOUNT
PAL_POSIX_Console_release(IObject *me)
{
	UNUSED__(me);

	/* PAL_POSIX_Console is a singleton */
	return 1;
}

size_t
PAL_POSIX_Console_send(IWriteChannel *self, const uint8_t *buf, size_t nbytes)
{
	UNUSED__(self);

	if(!PAL_POSIX_console.data.started)
	{
		PAL_POSIX_Console_start();
	}
	fwrite((void *) buf, nbytes, 1, stdout);
	return nbytes;
}

size_t
PAL_POSIX_Console_write(IWriteChannel *self, const char *str)
{
	UNUSED__(self);

	return PAL_POSIX_Console_send(self, (const uint8_t *) str, strlen(str));
}

size_t
PAL_POSIX_Console_writeLn(IWriteChannel *me, const char *str)
{
	size_t n;

	n = PAL_POSIX_Console_send(me, (const uint8_t *) str, strlen(str));
	n += PAL_POSIX_Console_send(me, (const uint8_t *) "\n", 1);
	return n;
}

/*INTERNAL*/
size_t
PAL_POSIX_Console_logf(PAL_POSIX_Console *self, LogLevel level, const char *format, ...)
{
	va_list args;

	va_start(args, format);
	return PAL_POSIX_Console_vlogf(self, level, format, args);
}

size_t
PAL_POSIX_Console_vlogf(PAL_POSIX_Console *self, LogLevel level, const char *format, va_list args)
{
	size_t r;

	UNUSED__(self);

	if(level < PAL_POSIX->data.logLevel)
	{
		return 0;
	}
	if(!PAL_POSIX_console.data.started)
	{
		PAL_POSIX_Console_start();
	}
	switch(level)
	{
		case LOG_EMERGENCY:
			printf("\033[0;41;37;1m\033[97m  EMERGENCY: ");
			break;
		case LOG_ALERT:
			printf(   "\033[0;31;91m      ALERT: ");
			break;
		case LOG_CRITICAL:
			printf(   "\033[0;31;91m   CRITICAL: ");
			break;
		case LOG_ERROR:
			printf(   "\033[0;31;91m      Error: ");
			break;
		case LOG_WARNING:
			printf(   "\033[0;33;93m    Warning: ");
			break;
		case LOG_NOTICE:
			printf(   "\033[0;37m     Notice: ");
			break;
		case LOG_INFO:
			printf(         "\033[0;37m             ");
			break;
		default:
			printf("\033[37m<%d>  ", level);
	}
	r = vprintf(format, args);
	printf("\033[K\033[0;100;37;1;97m\n");
	return r;
}

/*INTERNAL*/

static void
PAL_POSIX_Console_start(void)
{
	PAL_POSIX_console.data.started = true;
#if HAVE_SETUPTERM
	setupterm();
#endif
	printf("\033[100;37;1;97m\033[2J\033[1;1H");
	fflush(stdout);
}


#endif /*FEATURE_CONSOLE*/
