#ifndef __FILTER_MQTT_H__
#define __FILTER_MQTT_H__


#include "libfilter.h"
#include "cJSON.h"

typedef struct _istp_proto_mqtt_filter_data_flag {
    guint32 have_message_type:1,
			have_mqtt_payload_len:1,
			have_c_flag:1,
			have_keepalive:1,
			have_client_id:1,
			have_username:1,
			have_passwd:1,
			have_message:1;
} istp_proto_mqtt_filter_data_flag;

typedef struct _istp_proto_mqtt_filter_data {
    istp_proto_mqtt_filter_data_flag flag;
    int message_type;
    int mqtt_payload_len;
    char* c_flag;
    int keepalive;
    char* client_id;
    char* username;
    char* passwd;
    char* message;
} istp_proto_mqtt_filter_data;

int json_to_mqtt(char *json_data, istp_proto_mqtt_filter_data *mqtt_data);
int mqtt_data_free(istp_proto_mqtt_filter_data *mqtt_data);

gboolean cmp_mqtt(stnode_t* keynode , stnode_t* valuenode, test_op_t op, istp_proto_mqtt_filter_data* mqtt_data);
gboolean mqtt_node(stnode_t* node, istp_proto_mqtt_filter_data* mqtt_data);
gboolean do_filter_mqtt(dfwork_t* dfw, istp_proto_mqtt_filter_data* mqtt_data);


#endif