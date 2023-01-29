#ifndef __PROTO_LIST_H__
#define __PROTO_LIST_H__


#include "libfilter.h"

// filter fields
#define FIELD_MODBUS 						"modbus"
#define FIELD_MODBUS_FUNC 					"modbus.function_code"
#define FIELD_MODBUS_ADDR 					"modbus.address"
#define FIELD_MODBUS_ADDR_LEN 				"modbus.address_length"

#define FIELD_MQTT 							"mqtt"
#define FIELD_MQTT_MSG_TYPE 				"mqtt.message_type"
#define FIELD_MQTT_PAYLOAD_LEN				"mqtt.mqtt_payload_len"
#define FIELD_MQTT_PROTO_LEN				"mqtt.protocol_len"
#define FIELD_MQTT_VERSION 					"mqtt.version"
#define FIELD_MQTT_CONNECT_FLAG 			"mqtt.c_flag"
#define FIELD_MQTT_KEEPALIVE 				"mqtt.keepalive"
#define FIELD_MQTT_CLIENTID_LEN 			"mqtt.client_id_len"
#define FIELD_MQTT_CLIENTID 				"mqtt.client_id"
#define FIELD_MQTT_PROTO 					"mqtt.protocol"
#define FIELD_MQTT_USERNAME_LEN 			"mqtt.username_len"
#define FIELD_MQTT_USERNAME 				"mqtt.username"
#define FIELD_MQTT_PASSWD_LEN 				"mqtt.passwd_len"
#define FIELD_MQTT_PASSWD 					"mqtt.passwd"
#define FIELD_MQTT_TOPIC_LEN 				"mqtt.topic_len"
#define FIELD_MQTT_TOPIC 					"mqtt.topic"
#define FIELD_MQTT_TOPIC_QOS 				"mqtt.topic_qos"
#define FIELD_MQTT_MSG 						"mqtt.message"


static filter_field_t filter_fields[MAX_FIELD_NUM] = {
	// modbus
	{FIELD_MODBUS, PROTO_NO_VALUE},
	{FIELD_MODBUS_FUNC, PROTO_VALUE_INTEGER},
	{FIELD_MODBUS_ADDR, PROTO_VALUE_INTEGER},
	{FIELD_MODBUS_ADDR_LEN, PROTO_VALUE_INTEGER},

	// mqtt
	{FIELD_MQTT, PROTO_NO_VALUE},
	{FIELD_MQTT_MSG_TYPE, PROTO_VALUE_INTEGER},
	{FIELD_MQTT_PAYLOAD_LEN, PROTO_VALUE_INTEGER},
	{FIELD_MQTT_PROTO_LEN, PROTO_VALUE_INTEGER},
	{FIELD_MQTT_VERSION, PROTO_VALUE_INTEGER},
	{FIELD_MQTT_CONNECT_FLAG, PROTO_VALUE_STRING},
	{FIELD_MQTT_KEEPALIVE, PROTO_VALUE_INTEGER},
	{FIELD_MQTT_CLIENTID_LEN, PROTO_VALUE_INTEGER},
	{FIELD_MQTT_CLIENTID, PROTO_VALUE_STRING},
	{FIELD_MQTT_PROTO, PROTO_VALUE_STRING},
	{FIELD_MQTT_USERNAME_LEN, PROTO_VALUE_INTEGER},
	{FIELD_MQTT_USERNAME, PROTO_VALUE_STRING},
	{FIELD_MQTT_PASSWD_LEN, PROTO_VALUE_INTEGER},
	{FIELD_MQTT_PASSWD, PROTO_VALUE_STRING},
	{FIELD_MQTT_TOPIC_LEN, PROTO_VALUE_INTEGER},
	{FIELD_MQTT_TOPIC, PROTO_VALUE_STRING},
	{FIELD_MQTT_TOPIC_QOS, PROTO_VALUE_INTEGER},
	{FIELD_MQTT_MSG, PROTO_VALUE_STRING},

	// end
	{"", PROTO_VALUE_UNVALID},
};


#endif