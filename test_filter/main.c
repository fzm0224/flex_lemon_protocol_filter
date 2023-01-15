#include <stdio.h>

#include "filter_modbus.h"
#include "filter_mqtt.h"


// test modbus
istp_proto_modbus_filter_data modbus_filter_data = { 
    .function_code = 5,
    .address = 1117,
    .address_length = 1 
};

// test mqtt
istp_proto_mqtt_filter_data mqtt_filter_data = { 
    .message_type = 1,
    .mqtt_payload_len = 57, 
    .protocol_len = 4,
    .version = 4,
    .c_flag = "0xc2",
    .keepalive = 60, 
    .client_id_len = 23, 
    .client_id = "mosq-rpGQ0xhBgQl6rA2hbZ",
    .protocol = "MQTT",
    .username_len = 10, 
    .username = "liyongfeng",
    .passwd_len = 8,
    .passwd = "123456",
    .topic_len = -1, 
    .topic = NULL,
    .topic_qos = -1, 
    .message = NULL
};

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("[Error]: argc != 2\n");
        return -1;
    }


    int ret = 0;
    char *expression = argv[1];
    dfwork_t *dfw = NULL;

    ret = filter_init(expression, &dfw);
    if (-1 == ret) {
        filter_fini(dfw);
        return -1;
    }

#if 0
    ret = filter_start(dfw, &modbus_filter_data, (pfunc_t)do_filter_modbus);
    if (-1 == ret) {
        printf("Modbus Filter Fail!!!!!!\n");
        filter_fini(dfw);
        return -1;
    } else {
        printf("Modbus Filter OK!!!!!!\n");
        printf("========== Modbus Data ==========\n");
        printf("function_code = %d, address = %d, address_length = %d\n", 
                modbus_filter_data.function_code, modbus_filter_data.address, modbus_filter_data.address_length);
    }
#else
    ret = filter_start(dfw, &mqtt_filter_data, (pfunc_t)doFilterMqtt);
    if (-1 == ret) {
        printf("MQTT Filter Fail!\n");
        filter_fini(dfw);
        return -1;
    } else {
        printf("MQTT Filter OK!\n");
        printf("========== MQTT Data ==========\n");
        printf("message_type = %d\nmqtt_payload_len = %d\nprotocol_len = %d\n"
                "version = %d\nc_flag = %s\nkeepalive = %d\nclient_id_len = %d\n"
                "client_id = %s\nprotocol = %s\nusername_len = %d\nusername = %s\n"
                "passwd_len = %d\npasswd = %s\ntopic_len = %d\ntopic = %s\n"
                "topic_qos = %d\nmessage = %s\n", 
	            mqtt_filter_data.message_type, mqtt_filter_data.mqtt_payload_len, mqtt_filter_data.protocol_len, 
                mqtt_filter_data.version, mqtt_filter_data.c_flag, mqtt_filter_data.keepalive, mqtt_filter_data.client_id_len, 
                mqtt_filter_data.client_id, mqtt_filter_data.protocol, mqtt_filter_data.username_len, mqtt_filter_data.username, 
                mqtt_filter_data.passwd_len, mqtt_filter_data.passwd, mqtt_filter_data.topic_len, mqtt_filter_data.topic, 
                mqtt_filter_data.topic_qos, mqtt_filter_data.message);
    }
#endif
    
    filter_fini(dfw);

    return 0;
}
