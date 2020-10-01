#include "message.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "client.h"
#include "signals.h"

extern int client_fd;


void SendMessageToPipe(char* msg)
{
  write(client_list[nclient].pipe_upward[WRITE], msg, strlen(msg));
  kill(getppid(), SIGBROADCAST);
}

void BroadcastMessage(int signum)
{
  char buf[BUFSIZ] = {0};
  for (size_t i = 0; i < nclient; ++i)
  {
    if (read(client_list[i].pipe_upward[READ], buf, BUFSIZ) != -1)
      break;
  }
  for (size_t i = 0; i < nclient; ++i)
  {
    write(client_list[i].pipe_downward[WRITE], buf, strlen(buf));
    kill(client_list[i].pid, SIGSEND);
  }
}
 
void SendMessage(int signum)
{
  char buf[BUFSIZ] = {0};
  read(client_list[nclient].pipe_downward[READ], buf, BUFSIZ);
  send(client_fd, buf, strlen(buf), 0);
}
