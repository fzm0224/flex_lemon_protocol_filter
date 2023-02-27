#ifndef __PROTO_LIST_H__
#define __PROTO_LIST_H__


#include "libfilter.h"

// filter fields
#define FIELD_NULL							""

#define FIELD_MODBUS 						"modbus"
#define FIELD_MODBUS_FUNC 					"modbus.function_code"
#define FIELD_MODBUS_ADDR 					"modbus.address"
#define FIELD_MODBUS_ADDR_LEN 				"modbus.address_length"

#define FIELD_MQTT 							"mqtt"
#define FIELD_MQTT_MSG_TYPE 				"mqtt.message_type"
#define FIELD_MQTT_PAYLOAD_LEN				"mqtt.mqtt_payload_len"
#define FIELD_MQTT_CONNECT_FLAG 			"mqtt.c_flag"
#define FIELD_MQTT_KEEPALIVE 				"mqtt.keepalive"
#define FIELD_MQTT_CLIENTID 				"mqtt.client_id"
#define FIELD_MQTT_USERNAME 				"mqtt.username"
#define FIELD_MQTT_PASSWD 					"mqtt.passwd"
#define FIELD_MQTT_MSG 						"mqtt.message"

#define FIELD_STAFF							"staff"
#define FIELD_STAFF_COUNTRY					"staff.country"
#define FIELD_STAFF_CITY					"staff.city"
#define FIELD_STAFF_NAME					"staff.name"
#define FIELD_STAFF_SEX						"staff.sex"
#define FIELD_STAFF_AGE						"staff.age"


static char* filter_protos[MAX_FIELD_NUM] = {
	FIELD_MODBUS,
	FIELD_MQTT,
	FIELD_STAFF,
	FIELD_NULL
};

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
	{FIELD_MQTT_CONNECT_FLAG, PROTO_VALUE_STRING},
	{FIELD_MQTT_KEEPALIVE, PROTO_VALUE_INTEGER},
	{FIELD_MQTT_CLIENTID, PROTO_VALUE_STRING},
	{FIELD_MQTT_USERNAME, PROTO_VALUE_STRING},
	{FIELD_MQTT_PASSWD, PROTO_VALUE_STRING},
	{FIELD_MQTT_MSG, PROTO_VALUE_STRING},

	// staff
	{FIELD_STAFF, PROTO_NO_VALUE},
	{FIELD_STAFF_COUNTRY, PROTO_VALUE_STRING},
	{FIELD_STAFF_CITY, PROTO_VALUE_STRING},
	{FIELD_STAFF_NAME, PROTO_VALUE_STRING},
	{FIELD_STAFF_SEX, PROTO_VALUE_INTEGER},
	{FIELD_STAFF_AGE, PROTO_VALUE_INTEGER},

	// end
	{FIELD_NULL, PROTO_VALUE_UNVALID},
};


#endif