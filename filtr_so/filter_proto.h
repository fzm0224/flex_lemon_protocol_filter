#ifndef __FILTER_PROTO_H__
#define __FILTER_PROTO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "libfilter.h"
#include "filter_gstring.h"
#include "filter_hashtable.h"


gboolean proto_init(void);
gboolean proto_exist(const char* field_name);
gboolean proto_type_getbyname(const char* field_name, proto_value_t *proto_value);
gboolean proto_explore(void);
void proto_fini(void);

#endif

