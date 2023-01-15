#ifndef __FILTER_MQTT_H__
#define __FILTER_MQTT_H__

#include "libfilter.h"


typedef struct _istp_proto_mqtt_filter_data {
    int message_type;
    int mqtt_payload_len;
    int protocol_len;
    int version;
    char* c_flag;
    int keepalive;
    int client_id_len;
    char* client_id;
    char* protocol;
    int username_len;
    char* username;
    int passwd_len;
    char* passwd;
    int topic_len;
    char* topic;
    int topic_qos;
    char* message;
} istp_proto_mqtt_filter_data;


gboolean cmp_mqtt(stnode_t* keynode , stnode_t* valuenode, test_op_t op, istp_proto_mqtt_filter_data* mqtt_data);
gboolean mqtt_node(stnode_t* node, istp_proto_mqtt_filter_data* mqtt_data);
gboolean doFilterMqtt(dfwork_t* dfw, istp_proto_mqtt_filter_data* mqtt_data);


#endif