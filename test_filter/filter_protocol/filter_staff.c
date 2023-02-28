#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proto_list.h"
#include "filter_staff.h"

gboolean cmp_staff(stnode_t* keynode, stnode_t* valuenode, test_op_t op, istp_proto_staff_filter_data* staff_data)
{
    char* key = keynode->data;
    int ivalue = 0;
    char* svalue = NULL;

    if(valuenode->type == STTYPE_INTEGER)
        ivalue = valuenode->value;
    else
        svalue = valuenode->data;

    if(strcmp(key, FIELD_STAFF_COUNTRY) == 0) {
        return sttype_test_string(op, svalue, staff_data->country);
    } else if(strcmp(key, FIELD_STAFF_CITY) == 0) {
        return sttype_test_string(op, svalue, staff_data->city);
    } else if(strcmp(key, FIELD_STAFF_NAME) == 0) {
        return sttype_test_string(op, svalue, staff_data->name);
    } else if(strcmp(key, FIELD_STAFF_SEX) == 0) {
        return sttype_test_integer(op, ivalue, staff_data->sex);
    } else if(strcmp(key, FIELD_STAFF_AGE) == 0) {
        return sttype_test_integer(op, ivalue, staff_data->age);
    } else {
        return FALSE;
    }
}

gboolean check_not_staff(stnode_t* node)
{
    int i = 0;
    char *field = node->data;
    if (field) {
        if (0 != strcmp(field, FIELD_STAFF)) {
            for (i = 0; i < MAX_FIELD_NUM; i++) {
                if (0 == strcmp(FIELD_STAFF, filter_protos[i])) {
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

gboolean check_staff(stnode_t* node, istp_proto_staff_filter_data* staff_data)
{
    char *field = node->data;
    if (field) {
        if (0 == strcmp(field, FIELD_STAFF)) {
            return TRUE;
        }
        if (0 == strcmp(field, FIELD_STAFF_COUNTRY)) {
            if (staff_data->country) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_STAFF_CITY)) {
            if (staff_data->city) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_STAFF_NAME)) {
            if (staff_data->name) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_STAFF_SEX)) {
            if (staff_data->sex) {
                return TRUE;
            }
        }
        if (0 == strcmp(field, FIELD_STAFF_AGE)) {
            if (staff_data->age) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

gboolean staff_mode(stnode_t* node, istp_proto_staff_filter_data* staff_data)
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
            case TEST_OP_CONTAINS:
                ret = cmp_staff(test->val1, test->val2, test->op, staff_data);
                break;
            case TEST_OP_AND:
                if(staff_mode(test->val1, staff_data) == TRUE) {
                    if(staff_mode(test->val2, staff_data) == TRUE) {
                        ret = TRUE;
                    } else {
                        ret = FALSE;
                    }
                } else {
                    ret = FALSE;
                }
                break;
            case TEST_OP_OR:
                if(staff_mode(test->val1, staff_data) == TRUE) {
                    ret = TRUE;
                } else {
                    if(staff_mode(test->val2, staff_data) == TRUE) {
                        ret = TRUE;
                    } else {
                        ret = FALSE;
                    } 
                }
                break;
            case TEST_OP_NOT:
                if (((stnode_t*)(test->val1))->type == STTYPE_TEST) {
                    test_t *test1 = (test_t*)stnode_data((stnode_t*)(test->val1));
                    if (check_not_staff(test1->val1) == TRUE) {
                        ret = TRUE;
                    }
                }
                break;
            case TEST_OP_EXISTS:
                if (check_staff(test->val1, staff_data) == TRUE) {
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

gboolean do_filter_staff(dfwork_t* dfw, istp_proto_staff_filter_data* staff_data)
{
    gboolean ret = FALSE;

    ret = staff_mode(dfw->st_root, staff_data);
    
    return ret;
}

int json_to_staff(char *json_data, istp_proto_staff_filter_data *staff_data, int *staff_num, int max_num) 
{
    int i = 0;
    cJSON *root = NULL;
    cJSON *item = NULL;
    cJSON *staff_items = NULL;
    cJSON *staff = NULL;

    root = cJSON_Parse(json_data);
    if (!root) {
        printf("cJSON_Parse error!");
        return -1;
    }
    
    guint8 tmp_country[64] = {0};
    item = cJSON_GetObjectItem(root, "Country");
    if (item) {
        memcpy(tmp_country, item->valuestring, strlen(item->valuestring));
        memcpy(staff_data->country, item->valuestring, strlen(item->valuestring));
        staff_data->flag.have_country = 1;
    }

    guint8 tmp_city[64] = {0};
    item = cJSON_GetObjectItem(root, "City");
    if (item) {
        memcpy(tmp_city, item->valuestring, strlen(item->valuestring));
        memcpy(staff_data->city, item->valuestring, strlen(item->valuestring));
        staff_data->flag.have_city = 1;
    }

    staff_items = cJSON_GetObjectItem(root, "Infos");
    if (!staff_items) {
        *staff_num = 0;
    } else {
        *staff_num = cJSON_GetArraySize(staff_items);
        if (*staff_num >= max_num) {
            return -2;
        }

        for (i = 0; i < *staff_num; i++) {
            if (staff_data[0].flag.have_country) {
                memcpy(staff_data[i].country, tmp_country, strlen(tmp_country));
                staff_data[i].flag.have_country = 1;
            }
            if (staff_data[0].flag.have_city) {
                memcpy(staff_data[i].city, tmp_city, strlen(tmp_city));
                staff_data[i].flag.have_city = 1;
            }

            staff = cJSON_GetArrayItem(staff_items, i);
            if(!staff) {
                continue;
            }
            item = cJSON_GetObjectItem(staff, "Name");
            if (item) {
                memcpy(staff_data[i].name, item->valuestring, strlen(item->valuestring));
                staff_data[i].flag.have_name = 1;
            }
            item = cJSON_GetObjectItem(staff, "Sex");
            if (item) {
                staff_data[i].sex = item->valueint;
                staff_data[i].flag.have_sex = 1;
            }
            item = cJSON_GetObjectItem(staff, "Age");
            if (item) {
                staff_data[i].age = item->valueint;
                staff_data[i].flag.have_age = 1;
            }
        }
    }

    cJSON_Delete(root);

    return 0;
}