#include "elib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/*
 * Consistent method of crashing.
 */

void
die(const char *msg, const char *restrict format, ...)
{
	fprintf(stderr, "[FAILURE]: ");
	va_list ap;
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
	fprintf(stderr, "\n");
	exit(-1);
}
