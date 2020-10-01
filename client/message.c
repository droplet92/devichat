#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "io.h"

void* recv_msg(void* socket_fd)
{
  char* msg;
  while (1)
  {
    while ((msg = readall(*(int*)socket_fd)))
    {
      write(STDOUT_FILENO, ">> ", 3);
      write(STDOUT_FILENO, msg, strlen(msg));
      write(STDOUT_FILENO, "\n", 1);
      free(msg);
    }
  }
  return NULL;
}