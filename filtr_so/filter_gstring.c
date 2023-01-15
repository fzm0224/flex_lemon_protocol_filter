#include "filter_gstring.h"

#define MY_MAXSIZE ((gsize)-1)

/********** Private **********/
static inline gsize nearest_power (gsize base, gsize num)
{
    if (num > MY_MAXSIZE / 2) {
        return MY_MAXSIZE;
    } else {
        gsize n = base;

        while (n < num)
            n <<= 1;

        return n;
    }
}

static void g_string_maybe_expand (GString *string, gsize len)
{
    if (string->len + len >= string->allocated_len) {
        string->allocated_len = nearest_power (1, string->len + len + 1);
        string->str = realloc (string->str, string->allocated_len);
    }
}

GString * g_string_sized_new (gsize dfl_size)
{
    GString *string = malloc (sizeof(GString));
    if (!string) {
        return NULL;
    }

    string->allocated_len = 0;
    string->len = 0;
    string->str = NULL;

    g_string_maybe_expand (string, MAX (dfl_size, 2));
    string->str[0] = 0;

    return string;
}

GString * g_string_insert_len (GString *string, gssize pos, const gchar *val, gssize len)
{
    gsize len_unsigned, pos_unsigned;

    if (!string) {
        return NULL;
    }
    if (!(len == 0 || val != NULL)) {
        return string;
    }

    if (len == 0)
        return string;

    if (len < 0) {
        len = strlen (val);
    }
    len_unsigned = len;

    if (pos < 0) {
        pos_unsigned = string->len;
    } else {
        pos_unsigned = pos;
        if (pos_unsigned > string->len) {
            return string;
        }
    }

    if (val >= string->str && val <= string->str + string->len) {
        gsize offset = val - string->str;
        gsize precount = 0;

        g_string_maybe_expand (string, len_unsigned);
        val = string->str + offset;
        /* At this point, val is valid again.  */

        /* Open up space where we are going to insert.  */
        if (pos_unsigned < string->len) {
            memmove (string->str + pos_unsigned + len_unsigned,
                 string->str + pos_unsigned, string->len - pos_unsigned);
        }

        /* Move the source part before the gap, if any.  */
        if (offset < pos_unsigned) {
            precount = MIN (len_unsigned, pos_unsigned - offset);
            memcpy (string->str + pos_unsigned, val, precount);
        }

        /* Move the source part after the gap, if any.  */
        if (len_unsigned > precount) {
            memcpy (string->str + pos_unsigned + precount,
                val + /* Already moved: */ precount +
                      /* Space opened up: */ len_unsigned,
                len_unsigned - precount);
        }
    } else {
        g_string_maybe_expand (string, len_unsigned);

        if (pos_unsigned < string->len) {
            memmove (string->str + pos_unsigned + len_unsigned,
                 string->str + pos_unsigned, string->len - pos_unsigned);
        }

        /* insert the new string */
        if (len_unsigned == 1)
            string->str[pos_unsigned] = *val;
        else
            memcpy (string->str + pos_unsigned, val, len_unsigned);
    }

    string->len += len_unsigned;
    string->str[string->len] = 0;

    return string;
}

GString * g_string_insert_c (GString *string, gssize pos, gchar c)
{
    if (!string) {
        return NULL;
    }

    gsize pos_unsigned;

    g_string_maybe_expand (string, 1);

    if (pos < 0) {
        pos = string->len;
    } else {
        if ((gsize) pos > string->len) {
            return string;
        }
    }

    pos_unsigned = pos;

    /* If not just an append, move the old stuff */
    if (pos_unsigned < string->len) {
        memmove (string->str + pos_unsigned + 1,
                string->str + pos_unsigned, string->len - pos_unsigned);
    }

    string->str[pos_unsigned] = c;

    string->len += 1;

    string->str[string->len] = 0;

    return string;
}

GString * g_string_append_len (GString *string, const gchar *val, gssize len)
{
    return g_string_insert_len (string, -1, val, len);
}



/********** API **********/
GString * g_string_new (const gchar *init)
{
    GString *string;

    if (init == NULL || *init == '\0') {
        string = g_string_sized_new (2);
    } else {
        gint len;

        len = strlen (init);
        string = g_string_sized_new (len + 2);

        g_string_append_len (string, init, len);
    }

    return string;
}

gchar * g_string_free (GString *string, gboolean free_segment)
{
    if (!string) {
        return NULL;
    }

    gchar *segment;

    if (free_segment) {
        free (string->str);
        string->str = NULL;
        string->len = 0;
        segment = NULL;
        free(string);
        string = NULL;
    } else {
        segment = string->str;
        string->str = NULL;
        string->len = 0;
    }

    return segment;
}

GString * g_string_append (GString *string, const gchar *val)
{
    return g_string_insert_len (string, -1, val, -1);
}

GString * g_string_append_c (GString *string, gchar c)
{
    if (!string) {
        return NULL;
    }
    return g_string_insert_c (string, -1, c);
}

gchar* g_strdup (const gchar *str)
{
    gchar *new_str;
    gsize length;

    if (str) {
        length = strlen (str) + 1;
        new_str = malloc (sizeof(char) * length);
        memcpy (new_str, str, length);
    } else {
        new_str = NULL;
    }

    return new_str;
}

int g_strcmp0 (const char *str1, const char *str2)
{
    if (!str1)
        return -(str1 != str2);
    if (!str2)
        return str1 != str2;
    return strcmp (str1, str2);
}