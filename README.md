# flex_lemon_protocol_filter
基于flex和lemon实现的一个过滤器库（借鉴Wireshark），过滤表达式支持>（大于），<（小于），==（等于），>=（大于等于），<=（小于等于），()（括号），||（或），&&（与），!（非），contains（包含） 等。根据需求，可以实现对任意json串中某些字段的过滤。

示例：
    
    ./filter '(staff.name == "Wangwu" && staff.sex == 0 && staff.age < 30) || staff.name == "Zhongli"' '{"Country":"China", "City":"Beijing", "Infos":[{"Name":"Zhangsan", "Sex":1, "Age":25}, {"Name":"Lisi", "Sex":1, "Age":26}, {"Name":"Wangwu", "Sex":0, "Age":24}, {"Name":"Zhaoliu", "Sex":0, "Age":28}]}' 'staff'
    
    ./filter 'staff.name contains "Li"' '{"Country":"China", "City":"Beijing", "Infos":[{"Name":"Zhangsan", "Sex":1, "Age":25}, {"Name":"Lisi", "Sex":1, "Age":26}, {"Name":"Wangwu", "Sex":0, "Age":24}, {"Name":"Zhaoliu", "Sex":0, "Age":28}]}' 'staff'



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

    ./filter '(staff.name == "Wangwu" && staff.sex == 0 && staff.age < 30) || staff.name == "Zhongli"' '{"Country":"China", "City":"Beijing", "Infos":[{"Name":"Zhangsan", "Sex":1, "Age":25}, {"Name":"Lisi", "Sex":1, "Age":26}, {"Name":"Wangwu", "Sex":0, "Age":24}, {"Name":"Zhaoliu", "Sex":0, "Age":28}]}' 'staff'

    
