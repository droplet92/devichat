#include "client.h"
#include <stdio.h>
#include <string.h>

struct client client_list[MAX_CLIENT] = {0};
size_t nclient = 0;
int client_fd = 0;

static void printAllClients()
{
  puts("=========================");
  for (size_t i = 0; i < nclient; ++i)
  {
    printf("%d, ID %d\n", i + 1, client_list[i].pid);
  }
  if (!nclient)
    puts("no clients");
  puts("=========================");
}


void AddClient(pid_t pid)
{
  client_list[nclient++].pid = pid;
  printf("new client(%d) is connected.\n", pid);
  printAllClients();
}

void RemoveClient(pid_t pid)
{
  for (size_t i = 0; i < MAX_CLIENT; ++i)
  {
    if (client_list[i].pid == pid)
    {
      memcpy(&client_list[i], &client_list[i + 1],
            sizeof(client_list[0]) * (MAX_CLIENT - i - 1));
      --nclient;
      printf("client(%d) is disconnected.\n", pid);
      printAllClients();
      break;
    }
  }
}