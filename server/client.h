#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <sys/types.h>
#include <unistd.h>

#define MAX_CLIENT  10

struct client
{
  pid_t pid;
  int pipe_upward[2], pipe_downward[2];
};

extern struct client client_list[MAX_CLIENT];
extern size_t nclient;
extern int client_fd;

void AddClient(pid_t pid);
void RemoveClient(pid_t pid);

#endif