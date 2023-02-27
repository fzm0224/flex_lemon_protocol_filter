CFLAGS := $(CFLAGS) -std=c99 -g
CFLAGS  += -I./filter_protocol/ -I ./include/ -I ./json 
LDFLAGS := -L ./

all:
	gcc ./filter_protocol/*.c ./json/*.c main.c -o filter -lfilter -lm $(CFLAGS) $(LDFLAGS)
clean:
	rm -f filter
