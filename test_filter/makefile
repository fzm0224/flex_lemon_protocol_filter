CFLAGS := $(CFLAGS) -std=c99 -g
CFLAGS  += -I./filter_protocol/ -I ./include/ 
LDFLAGS := -L ./

all:
	gcc ./filter_protocol/*.c main.c -o filter -lfilter $(CFLAGS) $(LDFLAGS)
clean:
	rm -f filter
