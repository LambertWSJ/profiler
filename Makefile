CC = gcc
FLGAGS = -lpthread -g -w
DST = main
SRC = $(DST).c

OBJS = $(DST).o 
OBJS += profile.o

%.o: %.c
	$(CC) -c -o $@ $< -g

build: $(OBJS)
	-$(CC) $(FLGAGS) -o $(DST) $^

run: build
	./$(DST)

debug: build
	gdb -q ./$(DST)

clean:
	$(RM) $(DST) *.o
	$(RM) $(DST) *.log
	$(RM) $(DST)