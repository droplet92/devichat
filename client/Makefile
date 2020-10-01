OBJS = client.o message.o io.o
SRCS = $(OBJS:.o=.c)
CC = clang
LDFLAGS = -lpthread

all: client

client: $(OBJS)
	$(CC) -g -o devichat $(OBJS) $(LDFLAGS)

dep:
	$(CC) -M $(SRCS)

clean:
	rm -rf $(OBJS)
