/*
 * Author: Tatu Ylonen <ylo@cs.hut.fi>
 * Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
 *                    All rights reserved
 *
 * As far as I am concerned, the code I have written for this software
 * can be used freely for any purpose.  Any derived versions of this
 * software must be clearly marked as such, and if the derived work is
 * incompatible with the protocol description in the RFC file, it must be
 * called by a name other than "ssh" or "Secure Shell".
 */
/*
 * Copyright (c) 2000 Markus Friedl.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "includes.h"
#include "sshd_vm.h"
#include "sysfun.h"
RCSID("$OpenBSD: log.c,v 1.25 2003/01/11 18:29:43 markus Exp $");

#include "log.h"
#include "xmalloc.h"
#include "cli_pmgr.h"

//#include <syslog.h>/*isiah*/

#if 0
static LogLevel log_level = SYSLOG_LEVEL_INFO;
static int log_on_stderr = 1;
static int log_facility = LOG_AUTH;
static char *argv0;

extern char *__progname;

/* textual representation of log-facilities/levels */

static struct {
	const char *name;
	SyslogFacility val;
} log_facilities[] = {
	{ "DAEMON",	SYSLOG_FACILITY_DAEMON },
	{ "USER",	SYSLOG_FACILITY_USER },
	{ "AUTH",	SYSLOG_FACILITY_AUTH },
	{ "LOCAL0",	SYSLOG_FACILITY_LOCAL0 },
	{ "LOCAL1",	SYSLOG_FACILITY_LOCAL1 },
	{ "LOCAL2",	SYSLOG_FACILITY_LOCAL2 },
	{ "LOCAL3",	SYSLOG_FACILITY_LOCAL3 },
	{ "LOCAL4",	SYSLOG_FACILITY_LOCAL4 },
	{ "LOCAL5",	SYSLOG_FACILITY_LOCAL5 },
	{ "LOCAL6",	SYSLOG_FACILITY_LOCAL6 },
	{ "LOCAL7",	SYSLOG_FACILITY_LOCAL7 },
	{ NULL,		SYSLOG_FACILITY_NOT_SET }
};

static struct {
	const char *name;
	LogLevel val;
} log_levels[] =
{
	{ "QUIET",	SYSLOG_LEVEL_QUIET },
	{ "FATAL",	SYSLOG_LEVEL_FATAL },
	{ "ERROR",	SYSLOG_LEVEL_ERROR },
	{ "INFO",	SYSLOG_LEVEL_INFO },
	{ "VERBOSE",	SYSLOG_LEVEL_VERBOSE },
	{ "DEBUG",	SYSLOG_LEVEL_DEBUG1 },
	{ "DEBUG1",	SYSLOG_LEVEL_DEBUG1 },
	{ "DEBUG2",	SYSLOG_LEVEL_DEBUG2 },
	{ "DEBUG3",	SYSLOG_LEVEL_DEBUG3 },
	{ NULL,		SYSLOG_LEVEL_NOT_SET }
};

SyslogFacility
log_facility_number(char *name)
{
	int i;

	if (name != NULL)
		for (i = 0; log_facilities[i].name; i++)
			if (strcasecmp(log_facilities[i].name, name) == 0)
				return log_facilities[i].val;
	return SYSLOG_FACILITY_NOT_SET;
}

LogLevel
log_level_number(char *name)
{
	int i;

	if (name != NULL)
		for (i = 0; log_levels[i].name; i++)
			if (strcasecmp(log_levels[i].name, name) == 0)
				return log_levels[i].val;
	return SYSLOG_LEVEL_NOT_SET;
}
#endif

/* Error messages that should be logged. */

#if 0
void
error(const char *fmt,...)
{
	va_list args;

	va_start(args, fmt);
	do_log(SYSLOG_LEVEL_ERROR, fmt, args);
	va_end(args);
}
#endif

/* Log this message (information that usually should go to the log). */

#if 0
void
log(const char *fmt,...)
{
	va_list args;

	va_start(args, fmt);
	do_log(SYSLOG_LEVEL_INFO, fmt, args);
	va_end(args);
}
#endif

/* More detailed messages (information that does not need to go to the log). */

void
verbose(const char *fmt,...)
{
#if 0
	va_list args;

	va_start(args, fmt);
	do_log(SYSLOG_LEVEL_VERBOSE, fmt, args);
	va_end(args);
#endif
}

/* Debugging messages that should not be logged during normal operation. */

void
debug(const char *fmt,...)
{
#if 0
	va_list args;

	va_start(args, fmt);
	do_log(SYSLOG_LEVEL_DEBUG1, fmt, args);
	va_end(args);
#endif

}

void
debug2(const char *fmt,...)
{
#if 0
	va_list args;

	va_start(args, fmt);
	do_log(SYSLOG_LEVEL_DEBUG2, fmt, args);
	va_end(args);
#endif
}

void
debug3(const char *fmt,...)
{
#if 0
	va_list args;

	va_start(args, fmt);
	do_log(SYSLOG_LEVEL_DEBUG3, fmt, args);
	va_end(args);
#endif
}

/* Fatal cleanup */

/*struct fatal_cleanup {
	struct fatal_cleanup *next;
	void (*proc) (void *);
	void *context;
};*//*isiah*/

//static struct fatal_cleanup *fatal_cleanups = NULL;/*isiah*/

/* Registers a cleanup function to be called by fatal() before exiting. */

void
fatal_add_cleanup(void (*proc) (void *), void *context)
{
	struct fatal_cleanup *cu;
	struct fatal_cleanup *fatal_cleanups; /*isiah*/

    /* ES3526VB-PoE-A8-00200
       SSHD_VM_GetSshFatalCleanups() may get failure
     */
    if (FALSE == SSHD_VM_GetSshFatalCleanups(&fatal_cleanups))
        return;

	cu = xmalloc(sizeof(*cu));
	cu->proc = proc;
	cu->context = context;
	cu->next = fatal_cleanups;
	fatal_cleanups = cu;
	SSHD_VM_SetSshFatalCleanups(fatal_cleanups);
}

/* Removes a cleanup frunction to be called at fatal(). */

void
fatal_remove_cleanup(void (*proc) (void *context), void *context)
{
	struct fatal_cleanup **cup, *cu;
	struct fatal_cleanup *fatal_cleanups; /*isiah*/

    /* ES3526VB-PoE-A8-00200
       SSHD_VM_GetSshFatalCleanups() may get failure
     */
    if (FALSE == SSHD_VM_GetSshFatalCleanups(&fatal_cleanups))
        return;

    for (cup = &fatal_cleanups; *cup; cup = &cu->next)
    {
		cu = *cup;
        if (cu->proc == proc && cu->context == context)
        {
			*cup = cu->next;
			xfree(cu);
			return;
		}
	}
	fatal("fatal_remove_cleanup: no such cleanup function: 0x%lx 0x%lx",
	    (u_long) proc, (u_long) context);
}

/* Remove all cleanups, to be called after fork() */
void
fatal_remove_all_cleanups(void)
{
	struct fatal_cleanup *cu, *next_cu;
	struct fatal_cleanup *fatal_cleanups; /*isiah*/

    /* ES3526VB-PoE-A8-00200
       SSHD_VM_GetSshFatalCleanups() may get failure
     */
    if (FALSE == SSHD_VM_GetSshFatalCleanups(&fatal_cleanups))
        return;

    for (cu = fatal_cleanups; cu; cu = next_cu)
    {
		next_cu = cu->next;
		xfree(cu);
	}
	fatal_cleanups = NULL;
	SSHD_VM_SetSshFatalCleanups(fatal_cleanups);
}

/* Cleanup and exit */
void
fatal_cleanup(void)
{
    struct fatal_cleanup *fatal_cleanups; /*isiah*/

    /* ES3526VB-PoE-A8-00200
       SSHD_VM_GetSshFatalCleanups() may get failure
     */
    if (TRUE == SSHD_VM_GetSshFatalCleanups(&fatal_cleanups))
    {
        struct fatal_cleanup *cu, *next_cu;

        /* Call cleanup functions. */
        for (cu = fatal_cleanups; cu; cu = next_cu)
        {
            next_cu = cu->next;
            debug("Calling cleanup 0x%lx(0x%lx)",
                (u_long) cu->proc, (u_long) cu->context);
                (*cu->proc) (cu->context);
        }
    }

    fatal_remove_all_cleanups();/*isiah*/

//	exit(255);
    SSHD_VM_ClearSshServerOptions();
/* isiah.2004-01-02*/
/*move session number to CLI */
/*    SSHD_VM_SetCreatedSessionNumber( SSHD_VM_GetCreatedSessionNumber()-1 );*/
    CLI_PMGR_DecreaseRemoteSession();

    SYSFUN_DelSelfThread();
}


/*
 * Initialize the log.
 */

#if 0
void
log_init(char *av0, LogLevel level, SyslogFacility facility, int on_stderr)
{
	argv0 = av0;

	switch (level) {
	case SYSLOG_LEVEL_QUIET:
	case SYSLOG_LEVEL_FATAL:
	case SYSLOG_LEVEL_ERROR:
	case SYSLOG_LEVEL_INFO:
	case SYSLOG_LEVEL_VERBOSE:
	case SYSLOG_LEVEL_DEBUG1:
	case SYSLOG_LEVEL_DEBUG2:
	case SYSLOG_LEVEL_DEBUG3:
		log_level = level;
		break;
	default:
		fprintf(stderr, "Unrecognized internal syslog level code %d\n",
		    (int) level);
		exit(1);
	}

	log_on_stderr = on_stderr;
	if (on_stderr)
		return;

	switch (facility) {
	case SYSLOG_FACILITY_DAEMON:
		log_facility = LOG_DAEMON;
		break;
	case SYSLOG_FACILITY_USER:
		log_facility = LOG_USER;
		break;
	case SYSLOG_FACILITY_AUTH:
		log_facility = LOG_AUTH;
		break;
	case SYSLOG_FACILITY_LOCAL0:
		log_facility = LOG_LOCAL0;
		break;
	case SYSLOG_FACILITY_LOCAL1:
		log_facility = LOG_LOCAL1;
		break;
	case SYSLOG_FACILITY_LOCAL2:
		log_facility = LOG_LOCAL2;
		break;
	case SYSLOG_FACILITY_LOCAL3:
		log_facility = LOG_LOCAL3;
		break;
	case SYSLOG_FACILITY_LOCAL4:
		log_facility = LOG_LOCAL4;
		break;
	case SYSLOG_FACILITY_LOCAL5:
		log_facility = LOG_LOCAL5;
		break;
	case SYSLOG_FACILITY_LOCAL6:
		log_facility = LOG_LOCAL6;
		break;
	case SYSLOG_FACILITY_LOCAL7:
		log_facility = LOG_LOCAL7;
		break;
	default:
		fprintf(stderr,
		    "Unrecognized internal syslog facility code %d\n",
		    (int) facility);
		exit(1);
	}
}
#endif

#define MSGBUFSIZ 1024

#if 0
void
do_log(LogLevel level, const char *fmt, va_list args)
{
	char msgbuf[MSGBUFSIZ];
	char fmtbuf[MSGBUFSIZ];
	char *txt = NULL;
	int pri = LOG_INFO;

	if (level > log_level)
		return;

	switch (level) {
	case SYSLOG_LEVEL_FATAL:
		if (!log_on_stderr)
			txt = "fatal";
		pri = LOG_CRIT;
		break;
	case SYSLOG_LEVEL_ERROR:
		if (!log_on_stderr)
			txt = "error";
		pri = LOG_ERR;
		break;
	case SYSLOG_LEVEL_INFO:
		pri = LOG_INFO;
		break;
	case SYSLOG_LEVEL_VERBOSE:
		pri = LOG_INFO;
		break;
	case SYSLOG_LEVEL_DEBUG1:
		txt = "debug1";
		pri = LOG_DEBUG;
		break;
	case SYSLOG_LEVEL_DEBUG2:
		txt = "debug2";
		pri = LOG_DEBUG;
		break;
	case SYSLOG_LEVEL_DEBUG3:
		txt = "debug3";
		pri = LOG_DEBUG;
		break;
	default:
		txt = "internal error";
		pri = LOG_ERR;
		break;
	}
	if (txt != NULL) {
		snprintf(fmtbuf, sizeof(fmtbuf), "%s: %s", txt, fmt);
		vsnprintf(msgbuf, sizeof(msgbuf), fmtbuf, args);
	} else {
		vsnprintf(msgbuf, sizeof(msgbuf), fmt, args);
	}
	if (log_on_stderr) {
		fprintf(stderr, "%s\r\n", msgbuf);
	} else {
		openlog(argv0 ? argv0 : __progname, LOG_PID, log_facility);
		syslog(pri, "%.500s", msgbuf);
		closelog();
	}
}
#endif