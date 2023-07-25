CFLAGS := $(CFLAGS) -std=c99 -g
CFLAGS  += -I./filter_protocol/ -I ./include/ -I ./json 
LDFLAGS := -L ./

all:
	gcc ./filter_protocol/*.c ./json/*.c main.c -o filter -L ./ -lfilter -lm -Wl,-rpath=. $(CFLAGS) $(LDFLAGS)
clean:
	rm -f filter
