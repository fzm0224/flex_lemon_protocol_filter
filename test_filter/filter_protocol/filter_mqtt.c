#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filter_mqtt.h"


gboolean cmp_mqtt(stnode_t* keynode , stnode_t* valuenode, test_op_t op, istp_proto_mqtt_filter_data* mqtt_data)
{
    char* key = keynode->data;
    int ivalue = 0;
    char* svalue = NULL;

    if(valuenode->type == STTYPE_INTEGER)
        ivalue = valuenode->value;
    else
        svalue = valuenode->data;

    if(strcmp(key, "mqtt.message_type") == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->message_type);
    } else if(strcmp(key, "mqtt.mqtt_payload_len") == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->mqtt_payload_len);
    } else if(strcmp(key, "mqtt.protocol_len") == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->protocol_len);
    } else if(strcmp(key, "mqtt.version") == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->version);
    } else if(strcmp(key, "mqtt.c_flag") == 0) {
        return sttype_test_string(op, svalue, mqtt_data->c_flag);
    } else if(strcmp(key, "mqtt.keepalive") == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->keepalive);
    } else if(strcmp(key, "mqtt.client_id_len") == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->client_id_len);
    } else if(strcmp(key, "mqtt.client_id") == 0) {
        return sttype_test_string(op, svalue, mqtt_data->client_id);
    } else if(strcmp(key, "mqtt.protocol") == 0) {
        return sttype_test_string(op, svalue, mqtt_data->protocol);
    } else if(strcmp(key, "mqtt.username_len") == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->username_len);
    } else if(strcmp(key, "mqtt.username") == 0) {
        return sttype_test_string(op, svalue, mqtt_data->username);
    } else if(strcmp(key, "mqtt.passwd_len") == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->passwd_len);
    } else if(strcmp(key, "mqtt.passwd") == 0) {
        return sttype_test_string(op, svalue, mqtt_data->passwd);
    } else if(strcmp(key, "mqtt.topic_len") == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->topic_len);
    } else if(strcmp(key, "mqtt.topic") == 0) {
        return sttype_test_string(op, svalue, mqtt_data->topic);
    } else if(strcmp(key, "mqtt.topic_qos") == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->topic_qos);
    } else if(strcmp(key, "mqtt.message") == 0) {
        return sttype_test_string(op, svalue, mqtt_data->message);
    } else {
        return FALSE;
    }
}

gboolean check_mqtt(stnode_t* node, istp_proto_mqtt_filter_data* mqtt_data)
{
    char *field = node->data;
    if (field) {
        if (0 == strcmp(field, "mqtt")) {
            return TRUE;
        }
        if (0 == strcmp(field, "mqtt.message_type")) {
            if (mqtt_data->message_type) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.mqtt_payload_len")) {
            if (mqtt_data->mqtt_payload_len) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.protocol_len")) {
            if (mqtt_data->protocol_len) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.version")) {
            if (mqtt_data->version) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.c_flag")) {
            if (mqtt_data->c_flag) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.keepalive")) {
            if (mqtt_data->keepalive) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.client_id_len")) {
            if (mqtt_data->client_id_len) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.client_id")) {
            if (mqtt_data->client_id) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.protocol")) {
            if (mqtt_data->protocol) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.username_len")) {
            if (mqtt_data->username_len) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.username")) {
            if (mqtt_data->username) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.passwd_len")) {
            if (mqtt_data->passwd_len) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.passwd")) {
            if (mqtt_data->passwd) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.topic_len")) {
            if (mqtt_data->topic_len) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.topic")) {
            if (mqtt_data->topic) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.topic_qos")) {
            if (mqtt_data->topic_qos) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, "mqtt.message")) {
            if (mqtt_data->message) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

gboolean mqtt_node(stnode_t* node, istp_proto_mqtt_filter_data* mqtt_data)
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
                ret = cmp_mqtt(test->val1, test->val2, test->op, mqtt_data);
                break;
            case TEST_OP_AND:
                if(mqtt_node(test->val1, mqtt_data) == TRUE) {
                    if(mqtt_node(test->val2, mqtt_data) == TRUE) {
                        ret = TRUE;
                    } else {
                        ret = FALSE;
                    }
                } else {
                    ret = FALSE;
                }
                break;
            case TEST_OP_OR:
                if(mqtt_node(test->val1, mqtt_data) == TRUE) {
                    ret = TRUE;
                } else {
                    if(mqtt_node(test->val2, mqtt_data) == TRUE) {
                        ret = TRUE;
                    } else {
                        ret = FALSE;
                    } 
                }
                break;
            case TEST_OP_EXISTS:
                if (check_mqtt(test->val1, mqtt_data) == TRUE) {
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

gboolean doFilterMqtt(dfwork_t* dfw, istp_proto_mqtt_filter_data* mqtt_data)
{
    gboolean ret = FALSE;

    ret = mqtt_node(dfw->st_root, mqtt_data);

    return ret;
}