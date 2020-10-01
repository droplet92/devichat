#define WIN32_LEAN_AND_MEAN

#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <io.h>

#include "io.h"

DWORD WINAPI recv_msg(LPVOID lpParam)
{
  SOCKET socket_obj = *(SOCKET*)lpParam;
  char* msg;

  while (1)
  {
    while ((msg = recvall(socket_obj)))
    {
      _write(STDOUT_FILENO, ">> ", 3);
      _write(STDOUT_FILENO, msg, strlen(msg));
      _write(STDOUT_FILENO, "\n", 1);
      free(msg);
    }
  }
  return 0;
}