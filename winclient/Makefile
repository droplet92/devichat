OBJS = client.o message.o io.o
SRCS = $(OBJS:.o=.c) io.h
CC = gcc
LDFLAGS = -lws2_32

all: client

client: $(OBJS)
	$(CC) -g -o devichat $(OBJS) $(LDFLAGS)

dep:
	$(CC) -M $(SRCS)

clean:
	del $(OBJS)
