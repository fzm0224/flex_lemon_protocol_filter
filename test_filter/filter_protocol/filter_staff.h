#ifndef __FILTER_STAFF_H__
#define __FILTER_STAFF_H__

#include "libfilter.h"
#include "cJSON.h"

typedef struct _istp_proto_staff_filter_data_flag {
    guint32 have_country:1,
            have_city:1,
            have_name:1,
            have_sex:1,
            have_age:1; 
} istp_proto_staff_filter_data_flag;

typedef struct _istp_proto_staff_filter_data {
    istp_proto_staff_filter_data_flag flag;
    guint8 country[64];
    guint8 city[64];
    guint8 name[64];
    guint8 sex;     // 0 woman, 1 man
    guint8 age;
} istp_proto_staff_filter_data;


int json_to_staff(char *json_data, istp_proto_staff_filter_data *staff_data, int *staff_num, int max_num);

gboolean cmp_staff(stnode_t* keynode , stnode_t* valuenode, test_op_t op, istp_proto_staff_filter_data* staff_data);
gboolean staff_mode(stnode_t* node, istp_proto_staff_filter_data* staff_data);
gboolean do_filter_staff(dfwork_t* dfw, istp_proto_staff_filter_data* staff_data);


#endif
