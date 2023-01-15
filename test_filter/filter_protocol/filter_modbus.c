#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filter_modbus.h"

gboolean cmp_modbus(stnode_t* keynode, stnode_t* valuenode, test_op_t op, istp_proto_modbus_filter_data* modbus_data)
{
    char* key = keynode->data;
    int ivalue = 0;
    char* svalue = NULL;

    if(valuenode->type == STTYPE_INTEGER)
        ivalue = valuenode->value;
    else
        svalue = valuenode->data;

    if(strcmp(key, "modbus.function_code") == 0) {
        return sttype_test_integer(op, ivalue, modbus_data->function_code);
    } else if(strcmp(key, "modbus.address") == 0) {
        return sttype_test_integer(op, ivalue, modbus_data->address);
    } else if(strcmp(key, "modbus.address_length") == 0) {
        return sttype_test_integer(op, ivalue, modbus_data->address_length);
    } else {
        return FALSE;
    }
}

gboolean checkModbus(stnode_t* node, istp_proto_modbus_filter_data* modbus_data)
{
    char *field = node->data;
    if (field) {
        if (0 == strcmp(field, "modbus")) {
            return TRUE;
        }
        if (0 == strcmp(field, "modbus.function_code")) {
            if (modbus_data->function_code) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "modbus.address")) {
            if (modbus_data->address) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "modbus.address_length")) {
            if (modbus_data->address_length) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

gboolean modbus_mode(stnode_t* node, istp_proto_modbus_filter_data* modbus_data)
{
    gboolean ret = FALSE;

    if(node->type == STTYPE_TEST) {
        test_t	*test = (test_t*)stnode_data(node);
        switch(test->op) {
            case TEST_OP_EQ:
            case TEST_OP_NE:
            case TEST_OP_GT:
            case TEST_OP_GE:
            case TEST_OP_LT:
            case TEST_OP_LE:
                ret = cmp_modbus(test->val1, test->val2, test->op, modbus_data);
                break;
            case TEST_OP_AND:
                if(modbus_mode(test->val1, modbus_data) == TRUE) {
                    if(modbus_mode(test->val2, modbus_data) == TRUE) {
                        ret = TRUE;
                    } else {
                        ret = FALSE;
                    }
                } else {
                    ret = FALSE;
                }
                break;
            case TEST_OP_OR:
                if(modbus_mode(test->val1, modbus_data) == TRUE) {
                    ret = TRUE;
                } else {
                    if(modbus_mode(test->val2, modbus_data) == TRUE) {
                        ret = TRUE;
                    } else {
                        ret = FALSE;
                    } 
                }
                break;
            case TEST_OP_EXISTS:
                if (checkModbus(test->val1, modbus_data) == TRUE) {
                    ret = TRUE;
                }
                break;
            default:
                break;
        }
    } else {
        // 数据节点直接返回TRUE
        return TRUE;
    }

    return ret;
}

gboolean do_filter_modbus(dfwork_t* dfw, istp_proto_modbus_filter_data* modbus_data)
{
    gboolean ret = FALSE;

    ret = modbus_mode(dfw->st_root, modbus_data);
    
    return ret;
}
