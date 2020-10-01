#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <Windows.h>
#include <io.h>

#include "message.h"
#include "io.h"


int main(int argc, char** argv)
{
  WSADATA wsadata;
  SOCKADDR_IN server_addr;
  SOCKET socket_obj;
  char* msg, * lastch;
  HANDLE thread;

  if (argc != 3)
  {
    fprintf(stderr, "Usage: devichat [ipaddress] [port]\n");
    return 1;
  }

  if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
  {
    fprintf(stderr, "WSAStartup() failed.\n");
    return 1;
  }
  if ((socket_obj = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
  {
    fprintf(stderr, "socket() failed.\n");
    return 1;
  }
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  server_addr.sin_port = htons(atoi(argv[2]));

  if (connect(socket_obj, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
  {
    fprintf(stderr, "connect() failed.\n");
    return 1;
  }

  if (!(thread = CreateThread(NULL, 0, recv_msg, &socket_obj, 0, NULL)))
  {
    fprintf(stderr, "CreateThread() failed.\n");
    return 1;
  }
  Sleep(1000);

  while ((msg = readall(STDIN_FILENO)))
  {
    lastch = &msg[strlen(msg) - 1];
    *(lastch--) = 0;
    if (!strcmp(msg, "\n"))
      continue;
    if (*lastch == '\n')
      *lastch = '\0';
    if (send(socket_obj, msg, strlen(msg), 0) < 0)
    {
      fprintf(stderr, "send() failed.\n");
      break;
    }
  }
  WaitForSingleObject(thread, INFINITE);
  if (closesocket(socket_obj) == SOCKET_ERROR)
  {
    fprintf(stderr, "closesocket() failed.\n");
    WSACleanup();
    return 1;
  }
  WSACleanup();
  return 0;
}
