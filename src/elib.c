#include "elib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <syslog.h>

/*
 * Consistent method of crashing.
 */
void
die(const char *restrict format, ...)
{
	fprintf(stderr, "[FAILURE]: ");
	va_list ap;
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
	fprintf(stderr, "\n");
	exit(-1);
}

/*
 * Consistent method of Logging daemon errs.
 */
void
derr(const char *restrict format, ...)
{
	va_list ap;
	va_start(ap, format);
	vsyslog(LOG_ERR, format, ap);
	va_end(ap);
}

/*
 * Consistent method of Logging daemon info.
 */
void
dlog(const char *restrict format, ...)
{
	va_list ap;
	va_start(ap, format);
	vsyslog(LOG_INFO, format, ap);
	va_end(ap);
}
