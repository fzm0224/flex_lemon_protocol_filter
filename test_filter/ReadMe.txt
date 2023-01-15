Modbus测试：
./filter "modbus.function_code == 6 || (modbus.address == 1117 && modbus.address_length == 1)"
./filter "modbus.function_code == 6 || (modbus.address == 1117 && modbus.address_length == 2)"
./filter "modbus.function_code == 5 || (modbus.address == 1117 && modbus.address_length == 2)"
./filter "modbus"


MQTT测试：
./filter "mqtt.message_type == 2 || (mqtt.username == \"liyongfeng\" && mqtt.passwd == \"123456\")"
./filter "mqtt.message_type >= 1 && mqtt.username == \"liyongfeng\" && mqtt.passwd == \"123456\""
./filter "mqtt"
