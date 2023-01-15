#ifndef __FILTER_H__
#define __FILTER_H__


#include <stdarg.h>

#include "libfilter.h"
#include "filter_syntax_tree.h"
#include "filter_sttype.h"
#include "filter_gstring.h"


typedef struct {
	dfwork_t *dfw;
	GString* quoted_string;
} df_scanner_state_t;

/* Scanner's lval */
extern stnode_t *df_lval;

/* Return value for error in scanner. */
#define SCAN_FAILED	-1		/* not 0, as that means end-of-input */

/* Set dfw->error_message */
void dfilter_fail(dfwork_t *dfw, const char *format, ...);


#endif

