#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proto_list.h"
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

    if(strcmp(key, FIELD_MQTT_MSG_TYPE) == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->message_type);
    } else if(strcmp(key, FIELD_MQTT_PAYLOAD_LEN) == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->mqtt_payload_len);
    } else if(strcmp(key, FIELD_MQTT_PROTO_LEN) == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->protocol_len);
    } else if(strcmp(key, FIELD_MQTT_VERSION) == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->version);
    } else if(strcmp(key, FIELD_MQTT_CONNECT_FLAG) == 0) {
        return sttype_test_string(op, svalue, mqtt_data->c_flag);
    } else if(strcmp(key, FIELD_MQTT_KEEPALIVE) == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->keepalive);
    } else if(strcmp(key, FIELD_MQTT_CLIENTID_LEN) == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->client_id_len);
    } else if(strcmp(key, FIELD_MQTT_CLIENTID) == 0) {
        return sttype_test_string(op, svalue, mqtt_data->client_id);
    } else if(strcmp(key, FIELD_MQTT_PROTO) == 0) {
        return sttype_test_string(op, svalue, mqtt_data->protocol);
    } else if(strcmp(key, FIELD_MQTT_USERNAME_LEN) == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->username_len);
    } else if(strcmp(key, FIELD_MQTT_USERNAME) == 0) {
        return sttype_test_string(op, svalue, mqtt_data->username);
    } else if(strcmp(key, FIELD_MQTT_PASSWD_LEN) == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->passwd_len);
    } else if(strcmp(key, FIELD_MQTT_PASSWD) == 0) {
        return sttype_test_string(op, svalue, mqtt_data->passwd);
    } else if(strcmp(key, FIELD_MQTT_TOPIC_LEN) == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->topic_len);
    } else if(strcmp(key, FIELD_MQTT_TOPIC) == 0) {
        return sttype_test_string(op, svalue, mqtt_data->topic);
    } else if(strcmp(key, FIELD_MQTT_TOPIC_QOS) == 0) {
        return sttype_test_integer(op, ivalue, mqtt_data->topic_qos);
    } else if(strcmp(key, FIELD_MQTT_MSG) == 0) {
        return sttype_test_string(op, svalue, mqtt_data->message);
    } else {
        return FALSE;
    }
}

gboolean check_mqtt(stnode_t* node, istp_proto_mqtt_filter_data* mqtt_data)
{
    char *field = node->data;
    if (field) {
        if (0 == strcmp(field, FIELD_MQTT)) {
            return TRUE;
        }
        if (0 == strcmp(field, FIELD_MQTT_MSG_TYPE)) {
            if (mqtt_data->message_type) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_PAYLOAD_LEN)) {
            if (mqtt_data->mqtt_payload_len) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_PROTO_LEN)) {
            if (mqtt_data->protocol_len) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_VERSION)) {
            if (mqtt_data->version) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_CONNECT_FLAG)) {
            if (mqtt_data->c_flag) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_KEEPALIVE)) {
            if (mqtt_data->keepalive) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_CLIENTID_LEN)) {
            if (mqtt_data->client_id_len) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_CLIENTID)) {
            if (mqtt_data->client_id) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_PROTO)) {
            if (mqtt_data->protocol) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_USERNAME_LEN)) {
            if (mqtt_data->username_len) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_USERNAME)) {
            if (mqtt_data->username) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_PASSWD_LEN)) {
            if (mqtt_data->passwd_len) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_PASSWD)) {
            if (mqtt_data->passwd) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_TOPIC_LEN)) {
            if (mqtt_data->topic_len) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_TOPIC)) {
            if (mqtt_data->topic) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_TOPIC_QOS)) {
            if (mqtt_data->topic_qos) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_MSG)) {
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