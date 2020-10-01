#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>

#include "client.h"
#include "message.h"
#include "signals.h"

#define BACKLOG_SIZE  5

extern int client_fd;


int main(int argc, char** argv)
{
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_len = sizeof(client_addr);
  int socket_fd;
  char buf[BUFSIZ];
  ssize_t nbytes;
  pid_t pid;

  if (argc != 2)
  {
    fprintf(stderr, "Usage: devichat_server [port]\n");
    return 1;
  }

  RegisterHandlers();

  if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  {
    fprintf(stdout, "socket() failed.\n");
    return 1;
  }
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(atoi(argv[1]));

  if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
  {
    fprintf(stdout, "bind() failed.\n");
    return 1;
  }
  listen(socket_fd, BACKLOG_SIZE);

  while (1)
  {
    client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd < 0)
    {
      fprintf(stdout, "accept() failed.\n");
      break;
    }

    if (nclient >= MAX_CLIENT)
    {
      send(client_fd, "The chatroom is full.\n", 23, 0);
      printf("new client attempt to join this room, but rejected because here is full.\n");
      continue;
    }
  
    if (pipe(client_list[nclient].pipe_upward) < 0 ||
        pipe(client_list[nclient].pipe_downward) < 0)
    {
      fprintf(stderr, "pipe() failed.\n");
      return 1;
    }
    int flags = fcntl(client_list[nclient].pipe_upward[READ], F_GETFL, 0);
    fcntl(client_list[nclient].pipe_upward[READ], F_SETFL, flags | O_NONBLOCK);

    if ((pid = fork()) < 0)
    {
      fprintf(stderr, "fork() failed.\n");
      break;
    }
    else if (pid == 0)
    {
      // child
      close(client_list[nclient].pipe_upward[READ]);
      close(client_list[nclient].pipe_downward[WRITE]);
      while ((nbytes = recv(client_fd, buf, BUFSIZ, 0)) > 0)
      {
        printf("ID %d: %s\n", getpid(), buf);
        SendMessageToPipe(buf);
        memset(buf, 0, BUFSIZ);
      }
      if (nbytes < 0)
        fprintf(stderr, "recv() failed.\n");
      break;
    }
    else
    {
      // parent
      close(client_list[nclient].pipe_upward[WRITE]);
      close(client_list[nclient].pipe_downward[READ]);
      AddClient(pid);
      close(client_fd);
    }
  }
  if (client_fd > 0)
    close(client_fd);
  close(socket_fd);
  return 0;
}
