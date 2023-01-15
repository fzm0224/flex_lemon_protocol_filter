#ifndef __FILTER_PROTO_H__
#define __FILTER_PROTO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "filter_gstring.h"
#include "filter_hashtable.h"

typedef enum {
    PROTO_VALUE_UNVALID,
	PROTO_VALUE_STRING,
	PROTO_VALUE_INTEGER,
	PROTO_NO_VALUE
} proto_value_t;

#define MAX_FIELD_NUM 10240
#define MAX_FIELD_LEN 128

typedef struct _filter_field_t {
	char field[MAX_FIELD_LEN];
	proto_value_t type;
} filter_field_t;

/* 
 * filter string.
 * This can be modified to read the configuration file and load it, 
 * which is more flexible
 */
static const filter_field_t filter_fields[MAX_FIELD_NUM] = {
	// modbus
	{"modbus", PROTO_NO_VALUE},
	{"modbus.function_code", PROTO_VALUE_INTEGER},
	{"modbus.address", PROTO_VALUE_INTEGER},
	{"modbus.address_length", PROTO_VALUE_INTEGER},

	// mqtt
	{"mqtt", PROTO_NO_VALUE},
	{"mqtt.message_type", PROTO_VALUE_INTEGER},
	{"mqtt.mqtt_payload_len", PROTO_VALUE_INTEGER},
	{"mqtt.payload_len", PROTO_VALUE_INTEGER},
	{"mqtt.version", PROTO_VALUE_INTEGER},
	{"mqtt.c_flag", PROTO_VALUE_STRING},
	{"mqtt.keepalive", PROTO_VALUE_INTEGER},
	{"mqtt.client_id_len", PROTO_VALUE_INTEGER},
	{"mqtt.client_id", PROTO_VALUE_STRING},
	{"mqtt.protocol", PROTO_VALUE_STRING},
	{"mqtt.username_len", PROTO_VALUE_INTEGER},
	{"mqtt.username", PROTO_VALUE_STRING},
	{"mqtt.passwd_len", PROTO_VALUE_INTEGER},
	{"mqtt.passwd", PROTO_VALUE_STRING},
	{"mqtt.topic_len", PROTO_VALUE_INTEGER},
	{"mqtt.topic", PROTO_VALUE_STRING},
	{"mqtt.topic_qos", PROTO_VALUE_INTEGER},
	{"mqtt.message", PROTO_VALUE_STRING},

	// end
	{"", PROTO_VALUE_UNVALID},
};

gboolean proto_init(void);
gboolean proto_exist(const char* field_name);
gboolean proto_type_getbyname(const char* field_name, proto_value_t *proto_value);
gboolean proto_explore(void);
void proto_fini(void);

#endif

