# flex_lemon_protocol_filter
基于flex和lemon实现的一个协议过滤器库（借鉴Wireshark），支持>，&lt;，==，>=，&lt;=，()，||，&amp;&amp;等。


===== 目录文件 =====
filter_so目录：
  存放库代码。
test_filter目录:
  存放测试代码，测试程序主要自定义了两个协议的结构字段，对其某些字段进行过滤。
  注：目前用于过滤的关键字硬编码到库的代码中（filter_proto.h文件中），后续可以根据需求改为从配置文件中读取加载的方式，方便配置修改。
ReadMe.txt文件：
  存放测试程序的执行过滤语句。


===== 使用示例 =====
root@VM-16-4-ubuntu:~/DFilter/flex_lemon_protocol_filter/filtr_so# ls
filter.c            filter.h            filter_scanner.l      libfilter.h
filter_grammar.c    filter_hashtable.c  filter_semcheck.c     libfilter.so
filter_grammar.h    filter_hashtable.h  filter_semcheck.h     Makefile
filter_grammar.out  filter_proto.c      filter_sttype.c       tools
filter_grammar.y    filter_proto.h      filter_sttype.h
filter_gstring.c    filter_scanner.c    filter_syntax_tree.c
filter_gstring.h    filter_scanner.h    filter_syntax_tree.h
root@VM-16-4-ubuntu:~/DFilter/flex_lemon_protocol_filter/filtr_so# 
root@VM-16-4-ubuntu:~/DFilter/flex_lemon_protocol_filter/filtr_so# make clean
rm -f ./tools/lemon
rm -f filter_scanner.c filter_scanner.h
rm -f filter_grammar.c filter_grammar.h filter_grammar.out
rm -f libfilter.so ../test_filter/libfilter.so
root@VM-16-4-ubuntu:~/DFilter/flex_lemon_protocol_filter/filtr_so# make
gcc ./tools/lemon.c -o ./tools/lemon
./tools/lemon filter_grammar.y
sed -i 's/\_U\_//' ./filter_grammar.c
flex --outfile=filter_scanner.c --header-file=filter_scanner.h filter_scanner.l
gcc -shared -fPIC *.c -I./ -o libfilter.so
root@VM-16-4-ubuntu:~/DFilter/flex_lemon_protocol_filter/filtr_so# 
root@VM-16-4-ubuntu:~/DFilter/flex_lemon_protocol_filter/filtr_so# make install
cp ./libfilter.so ../test_filter/
cp ./libfilter.h ../test_filter/include
root@VM-16-4-ubuntu:~/DFilter/flex_lemon_protocol_filter/filtr_so#
root@VM-16-4-ubuntu:~/DFilter/flex_lemon_protocol_filter/filtr_so# cd ../test_filter/
root@VM-16-4-ubuntu:~/DFilter/flex_lemon_protocol_filter/test_filter# 
root@VM-16-4-ubuntu:~/DFilter/flex_lemon_protocol_filter/test_filter# make clean
rm -f filter
root@VM-16-4-ubuntu:~/DFilter/flex_lemon_protocol_filter/test_filter# 
root@VM-16-4-ubuntu:~/DFilter/flex_lemon_protocol_filter/test_filter# make
gcc ./filter_protocol/*.c main.c -o filter -lfilter  -std=c99 -g -I./filter_protocol/ -I ./include/  -L ./
root@VM-16-4-ubuntu:~/DFilter/flex_lemon_protocol_filter/test_filter# 
root@VM-16-4-ubuntu:~/DFilter/flex_lemon_protocol_filter/test_filter# ./filter "mqtt.message_type >= 1 && mqtt.username == \"liyongfeng\" && mqtt.passwd == \"123456\""
Token: 9 Text:(m:e9b00b9e t:4 d:mqtt.message_type)
Token: 8 Text:(m:e9b00b9e t:0 d:(null))
Token: 12 Text:(m:e9b00b9e t:6 i:1)
Token: 1 Text:(m:e9b00b9e t:0 d:(null))
Token: 9 Text:(m:e9b00b9e t:4 d:mqtt.username)
Token: 3 Text:(m:e9b00b9e t:0 d:(null))
Token: 10 Text:(m:e9b00b9e t:3 d:liyongfeng)
Token: 1 Text:(m:e9b00b9e t:0 d:(null))
Token: 9 Text:(m:e9b00b9e t:4 d:mqtt.passwd)
Token: 3 Text:(m:e9b00b9e t:0 d:(null))
Token: 10 Text:(m:e9b00b9e t:3 d:123456)
op: &&
op: &&
op: >=
mqtt.message_type
1
op: ==
mqtt.username
liyongfeng
op: ==
mqtt.passwd
123456
MQTT Filter OK!
========== MQTT Data ==========
message_type = 1
mqtt_payload_len = 57
protocol_len = 4
version = 4
c_flag = 0xc2
keepalive = 60
client_id_len = 23
client_id = mosq-rpGQ0xhBgQl6rA2hbZ
protocol = MQTT
username_len = 10
username = liyongfeng
passwd_len = 8
passwd = 123456
topic_len = -1
topic = (null)
topic_qos = -1
message = (null)
root@VM-16-4-ubuntu:~/DFilter/flex_lemon_protocol_filter/test_filter#
