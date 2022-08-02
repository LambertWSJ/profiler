CC = gcc
CFLGAG = -w
CFLAGS += -include common.h
DST = main
SRC = $(DST).c

OBJS = $(DST).o 
OBJS += profile.o
OBJS += map.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) -g

build: $(OBJS)
	$(CC) $(CFLGAGS) -o $(DST) $^ -g

run: build
	./$(DST)

debug: build
	gdb -q ./$(DST)

clean:
	$(RM) $(DST) *.o
	$(RM) $(DST) *.log
	$(RM) $(DST)