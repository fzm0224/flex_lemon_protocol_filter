# flex_lemon_protocol_filter
基于flex和lemon实现的一个过滤器库（借鉴Wireshark），过滤表达式支持>，&lt;，==，>=，&lt;=，()，||，&amp;&amp;，! 等。根据需求，可以实现对任意json串中某些字段的过滤。



===== 目录文件 =====

filter_so目录：

    存放库代码。
  
test_filter目录:

    存放测试代码，测试程序主要自定义了两个协议的结构字段，对其某些字段进行过滤。
  
ReadMe.txt文件：

    存放测试程序的执行过滤语句。
  


编译运行：
cd ./filter_so
make clean
make
make install

cd ../test_filter
make clean
make

./filter 'modbus.function_code == 3 || (modbus.address == 1099 && modbus.address_length == 2)' '{"function_code":3,"address":1099,"address_length":100}' "modbus"

    
