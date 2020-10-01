#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

#include "message.h"
#include "io.h"


int main(int argc, char** argv)
{
  struct sockaddr_in server_addr;
  int socket_fd;
  char* msg, * lastch;
  pthread_t tid;

  if (argc != 3)
  {
    fprintf(stderr, "Usage: devichat [ipaddress] [port]\n");
    return 1;
  }

  if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  {
    fprintf(stderr, "socket() failed.\n");
    return 1;
  }
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  server_addr.sin_port = htons(atoi(argv[2]));

  if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
  {
    fprintf(stderr, "connect() failed.\n");
    return 1;
  }

  pthread_create(&tid, NULL, recv_msg, &socket_fd);
  sleep(1);

  while ((msg = readall(STDIN_FILENO)))
  {
    lastch = &msg[strlen(msg) - 1];
    if (!strcmp(msg, "\n"))
      continue;
    if (*lastch == '\n')
      *lastch = '\0';
    if (send(socket_fd, msg, strlen(msg), 0) < 0)
    {
      fprintf(stderr, "send() failed.\n");
      break;
    }
  }
  pthread_join(tid, NULL);
  close(socket_fd);
  return 0;
}
