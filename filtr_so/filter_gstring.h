#ifndef __FILTER_GSTRING_H__
#define __FILTER_GSTRING_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "libfilter.h"

#define G_MININT32	((gint32) (-G_MAXINT32 - 1))
#define G_MAXINT32	((gint32) 0x7fffffff)

#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))

#define g_assert_not_reached()   \
            do { (void) 0; __builtin_unreachable (); } while(0);

#define g_assert(expr)    \
            do { (void) 0; } while(0);


GString* g_string_new (const gchar *init);
gchar* g_string_free (GString *string, gboolean free_segment);
GString* g_string_append (GString *string, const gchar *val);
GString* g_string_append_c (GString *string, gchar c);

gchar* g_strdup (const gchar *str);
int g_strcmp0 (const char *str1, const char *str2);

#endif