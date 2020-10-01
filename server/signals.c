#include "signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "client.h"
#include "signals.h"
#include "message.h"


void RegisterHandlers()
{
  signal(SIGINT, Terminate);
  signal(SIGTERM, Terminate);
  signal(SIGCHLD, Wait);
  signal(SIGBROADCAST, BroadcastMessage);
  signal(SIGSEND, SendMessage);
}

void Terminate(int signum)
{
  exit(0);
}

void Wait(int signum)
{
  char buf[BUFSIZ];
  pid_t pid = wait(NULL);
  RemoveClient(pid);
  for (size_t i = 0; i < nclient; ++i)
  {
    sprintf(buf, "SERVER: client(%d) is disconnected.", pid);
    write(client_list[i].pipe_downward[WRITE], buf, strlen(buf));
    kill(client_list[i].pid, SIGSEND);
  }
}
