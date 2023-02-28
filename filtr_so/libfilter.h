#ifndef __LIBFILTER_H__
#define __LIBFILTER_H__


#define TRUE    1
#define FALSE   0

#define MAX_FIELD_NUM 10240
#define MAX_FIELD_LEN 128


typedef enum {
    PROTO_VALUE_UNVALID,
	PROTO_VALUE_STRING,
	PROTO_VALUE_INTEGER,
	PROTO_NO_VALUE
} proto_value_t;

typedef struct _filter_field_t {
	char field[MAX_FIELD_LEN];
	proto_value_t type;
} filter_field_t;

filter_field_t *g_filter_fields;


typedef signed char     gint8;
typedef unsigned char   guint8;
typedef signed short    gint16;
typedef unsigned short  guint16;
typedef signed int      gint32;
typedef unsigned int    guint32;

typedef char            gchar;
typedef short           gshort;
typedef long            glong;
typedef int             gint;
typedef gint            gboolean;
typedef float           gfloat;
typedef double          gdouble;

typedef unsigned int    gsize;
typedef signed int      gssize;

typedef unsigned char   guchar;
typedef unsigned short  gushort;
typedef unsigned long   gulong;
typedef unsigned int    guint;

typedef void*           gpointer;
typedef const void*     gconstpointer;

typedef struct {
    gchar  *str;
    gsize len;    
    gsize allocated_len;
} GString;


typedef enum {
	STTYPE_UNINITIALIZED,
	STTYPE_TEST,
	STTYPE_UNPARSED,
	STTYPE_STRING,
	STTYPE_FIELD,
	STTYPE_FVALUE,
	STTYPE_INTEGER,
	STTYPE_RANGE,
	STTYPE_FUNCTION,
	STTYPE_SET,
	STTYPE_NUM_TYPES
} sttype_id_t;

typedef struct {
	guint32		magic;
	sttype_id_t	type;
	gpointer	data;
	gint32		value;
	gboolean	inside_brackets;
	const char	*deprecated_token;
} stnode_t;

typedef struct {
	stnode_t	*st_root;
	gboolean	syntax_error;
	gchar		*error_message;
} dfwork_t;

typedef gboolean (*pfunc_t)(dfwork_t*, void*);


typedef enum {
	TEST_OP_UNINITIALIZED,
	TEST_OP_EXISTS,
	TEST_OP_NOT,
	TEST_OP_AND,
	TEST_OP_OR,
	TEST_OP_EQ,
	TEST_OP_NE,
	TEST_OP_GT,
	TEST_OP_GE,
	TEST_OP_LT,
	TEST_OP_LE,
	TEST_OP_CONTAINS
} test_op_t;

typedef struct {
	guint32		magic;
	test_op_t	op;
	stnode_t	*val1;
	stnode_t	*val2;
} test_t;


gpointer stnode_data(stnode_t *node);

gboolean sttype_test_string(test_op_t op, char* val1, char* val2);
gboolean sttype_test_integer(test_op_t op, int val1, int val2);


// filter API
int filter_init(char *expression, dfwork_t **dfw);
int filter_start(dfwork_t *dfw, void *data, pfunc_t pfunc);
void filter_fini(dfwork_t *dfw);


#endif