OBJS = server.o client.o message.o signals.o
SRCS = $(OBJS:.o=.c)
CC = clang

all: client

client: $(OBJS)
	$(CC) -g -o devichat_server $(OBJS)

dep:
	$(CC) -M $(SRCS)

clean:
	rm -rf $(OBJS)
