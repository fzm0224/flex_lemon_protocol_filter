#include <stdio.h>

#include "proto_list.h"
#include "filter_modbus.h"
#include "filter_mqtt.h"
#include "filter_staff.h"


void help() {
    printf("Usage:\n");
    printf("\t./test_filter [expression] [json] [protoname]\n");
    printf("options:\n");
    printf("\t[expression]: filter expression.\n");
    printf("\t[json]: json string.\n");
    printf("\t[protoname]: protocol name. eg: mqtt\n");
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("argc error!");
        help();
        return -1;
    }

    g_filter_fields = filter_fields;
    
    int ret = 0;
    char *expression = argv[1];
    char *json_data = argv[2];
    char *proto_name = argv[3];
    dfwork_t *dfw = NULL;

    ret = filter_init(expression, &dfw);
    if (-1 == ret) {
        filter_fini(dfw);
        return -1;
    }

    printf("============== Result ==============\n");
    if (0 == strcmp(proto_name, FIELD_MODBUS)) {
        istp_proto_modbus_filter_data modbus_filter_data;

        memset(&modbus_filter_data, 0, sizeof(modbus_filter_data));
        ret = json_to_modbus(json_data, &modbus_filter_data);
        if (-1 == ret) {
            filter_fini(dfw);
            return -1;
        }
        ret = filter_start(dfw, &modbus_filter_data, (pfunc_t)do_filter_modbus);
        if (-1 == ret) {
            printf("Modbus Filter Fail!!!!!!\n");
            filter_fini(dfw);
            return -1;
        } else {
            printf("===== Modbus Filter OK! =====\n");
        }
    }
    else if (0 == strcmp(proto_name, FIELD_MQTT)) {
        istp_proto_mqtt_filter_data mqtt_filter_data;

        memset(&mqtt_filter_data, 0, sizeof(mqtt_filter_data));
        ret = json_to_mqtt(json_data, &mqtt_filter_data);
        if (-1 == ret) {
            mqtt_data_free(&mqtt_filter_data);
            filter_fini(dfw);
            return -1;
        }
        ret = filter_start(dfw, &mqtt_filter_data, (pfunc_t)do_filter_mqtt);
        if (-1 == ret) {
            printf("MQTT Filter Fail!!!!!!\n");
            mqtt_data_free(&mqtt_filter_data);
            filter_fini(dfw);
            return -1;
        } else {
            printf("===== MQTT Filter OK! =====\n");
            mqtt_data_free(&mqtt_filter_data);
        }
    }
    else if (0 == strcmp(proto_name, FIELD_STAFF)) {
        istp_proto_staff_filter_data staff_filter_data[1024];
        int staff_num = -1, i = 0, filter_ok_flag = 0;

        memset(staff_filter_data, 0, sizeof(staff_filter_data));
        ret = json_to_staff(json_data, staff_filter_data, &staff_num, 1024);
        if (-1 == ret) {
            filter_fini(dfw);
            return -1;
        }
        if (-2 == ret) {
            printf("staff array item too many, max %d!\n", 1024);
            filter_fini(dfw);
            return -1;
        }
        for (i = 0; i <= staff_num; i++) {
            ret = filter_start(dfw, &staff_filter_data[i], (pfunc_t)do_filter_staff);
            if (0 == ret) {
                printf("===== STAFF Filter OK! =====\n");
                filter_ok_flag = 1;
                break;
            }
        }
        if (0 == filter_ok_flag) {
            printf("STAFF Filter Fail!!!!!!\n");
            filter_fini(dfw);
            return -1;
        }
    }

    filter_fini(dfw);

    return 0;
}
