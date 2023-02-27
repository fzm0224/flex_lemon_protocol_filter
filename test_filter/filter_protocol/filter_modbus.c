#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proto_list.h"
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

    if(strcmp(key, FIELD_MODBUS_FUNC) == 0) {
        return sttype_test_integer(op, ivalue, modbus_data->function_code);
    } else if(strcmp(key, FIELD_MODBUS_ADDR) == 0) {
        return sttype_test_integer(op, ivalue, modbus_data->address);
    } else if(strcmp(key, FIELD_MODBUS_ADDR_LEN) == 0) {
        return sttype_test_integer(op, ivalue, modbus_data->address_length);
    } else {
        return FALSE;
    }
}

gboolean check_not_modbus(stnode_t* node)
{
    int i = 0;
    char *field = node->data;
    if (field) {
        if (0 != strcmp(field, FIELD_MODBUS)) {
            for (i = 0; i < MAX_FIELD_NUM; i++) {
                if (0 == strcmp(FIELD_MODBUS, filter_protos[i])) {
                    continue;
                }
                if (0 == strcmp(FIELD_NULL, filter_protos[i])) {
                    break;
                }
                if (0 == strcmp(field, filter_protos[i])) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

gboolean check_modbus(stnode_t* node, istp_proto_modbus_filter_data* modbus_data)
{
    char *field = node->data;
    if (field) {
        if (0 == strcmp(field, FIELD_MODBUS)) {
            return TRUE;
        }
        if (0 == strcmp(field, FIELD_MODBUS_FUNC)) {
            if (modbus_data->function_code) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MODBUS_ADDR)) {
            if (modbus_data->address) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MODBUS_ADDR_LEN)) {
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
            case TEST_OP_NOT:
                if (((stnode_t*)(test->val1))->type == STTYPE_TEST) {
                    test_t *test1 = (test_t*)stnode_data((stnode_t*)(test->val1));
                    if (check_not_modbus(test1->val1) == TRUE) {
                        ret = TRUE;
                    }
                }
                break;
            case TEST_OP_EXISTS:
                if (check_modbus(test->val1, modbus_data) == TRUE) {
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

int json_to_modbus(char *json_data, istp_proto_modbus_filter_data *modbus_data) 
{
    cJSON *root = NULL;
    cJSON *item = NULL;

    root = cJSON_Parse(json_data);
    if (!root) {
        printf("cJSON_Parse error!");
        return -1;
    }
    item = cJSON_GetObjectItem(root, "function_code");
    if (item) {
        modbus_data->function_code = item->valueint;
        modbus_data->flag.have_function_code = 1;
    }

    item = cJSON_GetObjectItem(root, "address");
    if (item) {
        modbus_data->address = item->valueint;
        modbus_data->flag.have_address = 1;
    }

    item = cJSON_GetObjectItem(root, "address_length");
    if (item) {
        modbus_data->address_length = item->valueint;
        modbus_data->flag.have_address_length = 1;
    }

    cJSON_Delete(root);

    return 0;
}