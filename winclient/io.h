#ifndef __IO_H__
#define __IO_H__

#include <WinSock2.h>

char* readall(int filedes);
char* recvall(SOCKET socket);

#endif
