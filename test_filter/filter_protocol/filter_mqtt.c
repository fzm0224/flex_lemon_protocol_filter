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

    if(0 == strcmp(key, FIELD_MQTT_MSG_TYPE) && mqtt_data->flag.have_message_type) {
        return sttype_test_integer(op, ivalue, mqtt_data->message_type);
    } else if(0 == strcmp(key, FIELD_MQTT_PAYLOAD_LEN) && mqtt_data->flag.have_mqtt_payload_len) {
        return sttype_test_integer(op, ivalue, mqtt_data->mqtt_payload_len);
    } else if(0 == strcmp(key, FIELD_MQTT_CONNECT_FLAG) && mqtt_data->flag.have_c_flag) {
        return sttype_test_string(op, svalue, mqtt_data->c_flag);
    } else if(0 == strcmp(key, FIELD_MQTT_KEEPALIVE) && mqtt_data->flag.have_keepalive) {
        return sttype_test_integer(op, ivalue, mqtt_data->keepalive);
    } else if(0 == strcmp(key, FIELD_MQTT_CLIENTID) && mqtt_data->flag.have_client_id) {
        return sttype_test_string(op, svalue, mqtt_data->client_id);
    } else if(0 == strcmp(key, FIELD_MQTT_USERNAME) && mqtt_data->flag.have_username) {
        return sttype_test_string(op, svalue, mqtt_data->username);
    } else if(0 == strcmp(key, FIELD_MQTT_PASSWD) && mqtt_data->flag.have_passwd) {
        return sttype_test_string(op, svalue, mqtt_data->passwd);
    } else if(0 == strcmp(key, FIELD_MQTT_MSG) && mqtt_data->flag.have_message) {
        return sttype_test_string(op, svalue, mqtt_data->message);
    } else {
        return FALSE;
    }
}

gboolean check_not_mqtt(stnode_t* node)
{
    int i = 0;
    char *field = node->data;
    if (field) {
        if (0 != strcmp(field, FIELD_MQTT)) {
            for (i = 0; i < MAX_FIELD_NUM; i++) {
                if (0 == strcmp(FIELD_MQTT, filter_protos[i])) {
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

gboolean check_mqtt(stnode_t* node, istp_proto_mqtt_filter_data* mqtt_data)
{
    char *field = node->data;
    if (field) {
        if (0 == strcmp(field, FIELD_MQTT)) {
            return TRUE;
        }
        if (0 == strcmp(field, FIELD_MQTT_MSG_TYPE)) {
            if (mqtt_data->flag.have_message_type) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_PAYLOAD_LEN)) {
            if (mqtt_data->flag.have_mqtt_payload_len) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_CONNECT_FLAG)) {
            if (mqtt_data->flag.have_c_flag) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_KEEPALIVE)) {
            if (mqtt_data->flag.have_keepalive) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_CLIENTID)) {
            if (mqtt_data->flag.have_client_id) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_USERNAME)) {
            if (mqtt_data->flag.have_username) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_PASSWD)) {
            if (mqtt_data->flag.have_passwd) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_MQTT_MSG)) {
            if (mqtt_data->flag.have_message) {
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
            case TEST_OP_NOT:
                if (((stnode_t*)(test->val1))->type == STTYPE_TEST) {
                    test_t *test1 = (test_t*)stnode_data((stnode_t*)(test->val1));
                    if (check_not_mqtt(test1->val1) == TRUE) {
                        ret = TRUE;
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

gboolean do_filter_mqtt(dfwork_t* dfw, istp_proto_mqtt_filter_data* mqtt_data)
{
    gboolean ret = FALSE;

    ret = mqtt_node(dfw->st_root, mqtt_data);

    return ret;
}

int json_to_mqtt(char *json_data, istp_proto_mqtt_filter_data *mqtt_data) 
{
    cJSON *root = NULL;
    cJSON *item = NULL;
    int len = 0;

    root = cJSON_Parse(json_data);
    if (!root) {
        printf("cJSON_Parse error!");
        return -1;
    }
    item = cJSON_GetObjectItem(root, "message_type");
    if (item) {
        mqtt_data->message_type = item->valueint;
        mqtt_data->flag.have_message_type = 1;
    }
    item = cJSON_GetObjectItem(root, "mqtt_payload_len");
    if (item) {
        mqtt_data->mqtt_payload_len = item->valueint;
        mqtt_data->flag.have_mqtt_payload_len = 1;
    }
    item = cJSON_GetObjectItem(root, "c_flag");
    if (item) {
        len = strlen(item->valuestring);
        mqtt_data->c_flag = (char *)malloc(len + 1);
        if (!mqtt_data->c_flag) {
            printf("mqtt c_flag malloc error!");
            return -1;
        }
        memset(mqtt_data->c_flag, 0, len + 1);
        memcpy(mqtt_data->c_flag, item->valuestring, len);
        mqtt_data->flag.have_c_flag = 1;
    }
    item = cJSON_GetObjectItem(root, "keepalive");
    if (item) {
        mqtt_data->keepalive = item->valueint;
        mqtt_data->flag.have_keepalive = 1;
    }
    item = cJSON_GetObjectItem(root, "client_id");
    if (item) {
        len = strlen(item->valuestring);
        mqtt_data->client_id = (char *)malloc(len + 1);
        if (!mqtt_data->client_id) {
            printf("mqtt client_id malloc error!");
            return -1;
        }
        memset(mqtt_data->client_id, 0, len + 1);
        memcpy(mqtt_data->client_id, item->valuestring, len);
        mqtt_data->flag.have_client_id = 1;
    }
    item = cJSON_GetObjectItem(root, "username");
    if (item) {
        len = strlen(item->valuestring);
        mqtt_data->username = (char *)malloc(len + 1);
        if (!mqtt_data->username) {
            printf("mqtt username malloc error!");
            return -1;
        }
        memset(mqtt_data->username, 0, len + 1);
        memcpy(mqtt_data->username, item->valuestring, len);
        mqtt_data->flag.have_username = 1;
    }
    item = cJSON_GetObjectItem(root, "passwd");
    if (item) {
        len = strlen(item->valuestring);
        mqtt_data->passwd = (char *)malloc(len + 1);
        if (!mqtt_data->passwd) {
            printf("mqtt passwd malloc error!");
            return -1;
        }
        memset(mqtt_data->passwd, 0, len + 1);
        memcpy(mqtt_data->passwd, item->valuestring, len);
        mqtt_data->flag.have_passwd = 1;
    }
    item = cJSON_GetObjectItem(root, "message");
    if (item) {
        len = strlen(item->valuestring);
        mqtt_data->message = (char *)malloc(len + 1);
        if (!mqtt_data->message) {
            printf("mqtt message malloc error!");
            return -1;
        }
        memset(mqtt_data->message, 0, len + 1);
        memcpy(mqtt_data->message, item->valuestring, len);
        mqtt_data->flag.have_message = 1;
    }

    cJSON_Delete(root);
    
    return 0;
}

int mqtt_data_free(istp_proto_mqtt_filter_data *mqtt_data)
{
    if (mqtt_data) {
        if (mqtt_data->c_flag) {
            free(mqtt_data->c_flag);
            mqtt_data->c_flag = NULL;
        }
        if (mqtt_data->client_id) {
            free(mqtt_data->client_id);
            mqtt_data->client_id = NULL;
        }
        if (mqtt_data->username) {
            free(mqtt_data->username);
            mqtt_data->username = NULL;
        }
        if (mqtt_data->passwd) {
            free(mqtt_data->passwd);
            mqtt_data->passwd = NULL;
        }
        if (mqtt_data->message) {
            free(mqtt_data->message);
            mqtt_data->message = NULL;
        }
    }
    return 0;
}