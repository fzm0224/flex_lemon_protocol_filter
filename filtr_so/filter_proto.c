#define  _GNU_SOURCE    // fix getline() warnning

#include "filter_proto.h"

static HashTable *g_proto_name_map = NULL;
static char *g_last_field_name = NULL;

gboolean proto_init(void)
{
    g_proto_name_map = malloc(sizeof(HashTable));
    memset(g_proto_name_map, 0, sizeof(HashTable));
    assert(!ht_is_initialized(g_proto_name_map));
    if (0 != ht_setup(g_proto_name_map, MAX_FIELD_LEN, sizeof(int), 0)) {
        printf("[Error]: ht_setup() error!\n");
        return FALSE;
    }
    assert(ht_is_initialized(g_proto_name_map));
    return TRUE;
}

gboolean proto_exist(const char* field_name)
{
    gboolean existed = FALSE;
    if(!field_name) return FALSE;
    
    if (g_strcmp0(field_name, g_last_field_name) == 0) {
		return TRUE;
	}
    char tmp_field_name[MAX_FIELD_LEN];
    memset(tmp_field_name, 0, MAX_FIELD_LEN);
    strncpy(tmp_field_name, field_name, strlen(field_name));
    existed = ht_contains(g_proto_name_map, (void *)tmp_field_name);
    if(existed) {
        free(g_last_field_name);
        g_last_field_name = g_strdup(tmp_field_name);
        return TRUE;
    }

    return FALSE;
}

gboolean proto_type_getbyname(const char* field_name, proto_value_t *proto_value)
{
    gpointer v = NULL;
    
    if(!field_name) {
        return FALSE;
    }
    char tmp_field_name[MAX_FIELD_LEN];
    memset(tmp_field_name, 0, MAX_FIELD_LEN);
    strncpy(tmp_field_name, field_name, strlen(field_name));
    v = ht_lookup(g_proto_name_map, (void *)tmp_field_name);
    if(v) {
        *proto_value = *(proto_value_t*)v;
        return TRUE;
    }

    return FALSE;
}

gboolean proto_explore(void)
{
    int i = 0;
    for (i = 0; i < MAX_FIELD_NUM; i++) {
        if (PROTO_VALUE_UNVALID == filter_fields[i].type)
            break;
        if (HT_ERROR == ht_insert(g_proto_name_map, (void *)filter_fields[i].field, (void *)&filter_fields[i].type)) {
            printf("[Error]: protoExplore() error! i = %d\n", i);
            return FALSE;
        }
    }
    if (0 == i)
        return FALSE;
    else
        return TRUE;
}

void proto_fini(void)
{
    if (g_proto_name_map) {
        ht_destroy(g_proto_name_map);
        free(g_proto_name_map);
        g_proto_name_map = NULL;
    }
    if (g_last_field_name) {
        free(g_last_field_name);
        g_last_field_name = NULL;
    }
}