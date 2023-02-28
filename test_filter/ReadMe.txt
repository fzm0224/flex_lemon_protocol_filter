Modbus测试：
./filter 'modbus.function_code == 3 && modbus.address == 1099' '{"function_code":3,"address":1099,"address_length":100}' "modbus"
./filter 'modbus.function_code == 3 || (modbus.address == 1099 && modbus.address_length == 2)' '{"function_code":3,"address":1099,"address_length":100}' "modbus"
./filter 'modbus.function_code == 3 || (modbus.address == 1099 && modbus.address_length == 2)' '{"function_code":3,"address":1099,"address_length":100}' "modbus"
./filter 'modbus' '{"function_code":3,"address":1099,"address_length":100}' "modbus"
./filter '!modbus' '{"function_code":3,"address":1099,"address_length":100}' "modbus"
./filter '!modbus && modbus.function_code == 3 && modbus.address == 1099' '{"function_code":3,"address":1099,"address_length":100}' "modbus"



MQTT测试：
./filter 'mqtt.message_type >= 1 && mqtt.username == "liyongfeng" && mqtt.passwd == "123456"' '{"message_type":1,"message_flag":0,"mqtt_payload_len":57,"protocol_len":4,"protocol":"MQTT","version":4,"c_flag":"0xc2","keepalive":60,"client_id_len":23,"client_id":"mosq-3iO2bSuBNshd5wDIVQ","username_len":10,"username":"liyongfeng","passwd_len":8,"passwd":"123456"}' "mqtt"
./filter 'mqtt' '{"message_type":1,"message_flag":0,"mqtt_payload_len":57,"protocol_len":4,"protocol":"MQTT","version":4,"c_flag":"0xc2","keepalive":60,"client_id_len":23,"client_id":"mosq-3iO2bSuBNshd5wDIVQ","username_len":10,"username":"liyongfeng","passwd_len":8,"passwd":"123456"}' "mqtt"
./filter '!mqtt' '{"message_type":1,"message_flag":0,"mqtt_payload_len":57,"protocol_len":4,"protocol":"MQTT","version":4,"c_flag":"0xc2","keepalive":60,"client_id_len":23,"client_id":"mosq-3iO2bSuBNshd5wDIVQ","username_len":10,"username":"liyongfeng","passwd_len":8,"passwd":"123456"}' "mqtt"
./filter '!modbus && mqtt.message_type >= 1 && mqtt.username == "liyongfeng" && mqtt.passwd == "123456"' '{"message_type":1,"message_flag":0,"mqtt_payload_len":57,"protocol_len":4,"protocol":"MQTT","version":4,"c_flag":"0xc2","keepalive":60,"client_id_len":23,"client_id":"mosq-3iO2bSuBNshd5wDIVQ","username_len":10,"username":"liyongfeng","passwd_len":8,"passwd":"123456"}' "mqtt"
./filter 'mqtt.username contains "feng"' '{"message_type":1,"message_flag":0,"mqtt_payload_len":57,"protocol_len":4,"protocol":"MQTT","version":4,"c_flag":"0xc2","keepalive":60,"client_id_len":23,"client_id":"mosq-3iO2bSuBNshd5wDIVQ","username_len":10,"username":"liyongfeng","passwd_len":8,"passwd":"123456"}' "mqtt"



STAFF测试：
./filter 'staff.country == "China" && staff.city == "Beijing" && staff.name == "Wangwu" && staff.sex == 0 && staff.age == 24' '{"Country":"China", "City":"Beijing", "Infos":[{"Name":"Zhangsan", "Sex":1, "Age":25}, {"Name":"Lisi", "Sex":1, "Age":26}, {"Name":"Wangwu", "Sex":0, "Age":24}, {"Name":"Zhaoliu", "Sex":0, "Age":28}]}' 'staff'
./filter 'staff.name == "Wangwu" || staff.name == "Zhongli"' '{"Country":"China", "City":"Beijing", "Infos":[{"Name":"Zhangsan", "Sex":1, "Age":25}, {"Name":"Lisi", "Sex":1, "Age":26}, {"Name":"Wangwu", "Sex":0, "Age":24}, {"Name":"Zhaoliu", "Sex":0, "Age":28}]}' 'staff'
./filter 'staff' '{"Country":"China", "City":"Beijing", "Infos":[{"Name":"Zhangsan", "Sex":1, "Age":25}, {"Name":"Lisi", "Sex":1, "Age":26}, {"Name":"Wangwu", "Sex":0, "Age":24}, {"Name":"Zhaoliu", "Sex":0, "Age":28}]}' 'staff'
./filter '!staff' '{"Country":"China", "City":"Beijing", "Infos":[{"Name":"Zhangsan", "Sex":1, "Age":25}, {"Name":"Lisi", "Sex":1, "Age":26}, {"Name":"Wangwu", "Sex":0, "Age":24}, {"Name":"Zhaoliu", "Sex":0, "Age":28}]}' 'staff'
./filter 'staff.name contains "Li"' '{"Country":"China", "City":"Beijing", "Infos":[{"Name":"Zhangsan", "Sex":1, "Age":25}, {"Name":"Lisi", "Sex":1, "Age":26}, {"Name":"Wangwu", "Sex":0, "Age":24}, {"Name":"Zhaoliu", "Sex":0, "Age":28}]}' 'staff'