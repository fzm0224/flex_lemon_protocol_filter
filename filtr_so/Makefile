CC := gcc
CFLAGS := $(CFLAGS) -std=c99 -g

all:
	$(CC) ./tools/lemon.c -o ./tools/lemon
# 使用lemon编译规则文件filter_grammar.y生成filter_grammar.h和filter_grammar.c
	./tools/lemon filter_grammar.y
# 解决lemon生成的filter_grammar.c中存在的_U_导致的编译错误
	sed -i 's/\_U\_//' ./filter_grammar.c
# 使用flex编译规则文件filter_scanner.l生成filter_scanner.h和filter_scanner.c
	flex --outfile=filter_scanner.c --header-file=filter_scanner.h filter_scanner.l
	$(CC) -shared -fPIC *.c -I./ -o libfilter.so

install:
	cp ./libfilter.so ../test_filter/
	cp ./libfilter.h ../test_filter/include

clean:
	rm -f ./tools/lemon
	rm -f filter_scanner.c filter_scanner.h
	rm -f filter_grammar.c filter_grammar.h filter_grammar.out
	rm -f libfilter.so ../test_filter/libfilter.so
