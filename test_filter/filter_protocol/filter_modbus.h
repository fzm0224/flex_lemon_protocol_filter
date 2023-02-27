#ifndef __FILTER_MODBUS_H__
#define __FILTER_MODBUS_H__

#include "libfilter.h"
#include "cJSON.h"

typedef struct _istp_proto_modbus_filter_data_flag {
    guint32 have_function_code:1,
            have_address:1,
            have_address_length:1; 
} istp_proto_modbus_filter_data_flag;

typedef struct _istp_proto_modbus_filter_data {
    istp_proto_modbus_filter_data_flag flag;
    guint8 function_code;
    guint16 address;
    guint16 address_length; 
} istp_proto_modbus_filter_data;


int json_to_modbus(char *json_data, istp_proto_modbus_filter_data *modbus_data);

gboolean cmp_modbus(stnode_t* keynode , stnode_t* valuenode, test_op_t op, istp_proto_modbus_filter_data* modbus_data);
gboolean modbus_mode(stnode_t* node, istp_proto_modbus_filter_data* modbus_data);
gboolean do_filter_modbus(dfwork_t* dfw, istp_proto_modbus_filter_data* modbus_data);


#endif
