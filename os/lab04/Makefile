CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lm

OBJS = solution.o bill.o fred.o john.o sam.o wrap_functions.o

all: solution libload_wrap.so

solution: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Wl,--wrap=fred -Wl,--wrap=john -o solution $(LDFLAGS)

libload_wrap.so: load_wrap.c
	$(CC) -shared -fPIC load_wrap.c -o $@ $(LDFLAGS)

clean:
	rm -f *.o solution libload_wrap.so

run: solution libload_wrap.so
	LD_PRELOAD=./libload_wrap.so ./solution