#ifndef __FILTER_MODBUS_H__
#define __FILTER_MODBUS_H__

#include "libfilter.h"


typedef struct _istp_proto_modbus_filter_data {
    int function_code;
    int address;
    int address_length; 
} istp_proto_modbus_filter_data;


gboolean cmp_modbus(stnode_t* keynode , stnode_t* valuenode, test_op_t op, istp_proto_modbus_filter_data* modbus_data);
gboolean modbus_mode(stnode_t* node, istp_proto_modbus_filter_data* modbus_data);
gboolean do_filter_modbus(dfwork_t* dfw, istp_proto_modbus_filter_data* modbus_data);


#endif
