#define WIN32_LEAN_AND_MEAN

#include "io.h"
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef int ssize_t;
typedef ssize_t(*get_wrapper)(void*, char*, size_t);

static ssize_t read_wrapper(void* filedes, char* buf, size_t size)
{
    return _read(*(int*)filedes, buf, size);
}

static ssize_t recv_wrapper(void* socket, char* buf, size_t size)
{
    return recv(*(SOCKET*)socket, buf, size, 0);
}

static char* getall(void* filedes, get_wrapper get_method)
{
    char buf[BUFSIZ] = {0};
    char* res = NULL;
    void* pres = NULL;
    size_t len = 0;
    ssize_t nbytes = 0;
    do
    {
        len += (nbytes = (*get_method)(filedes, buf, sizeof(buf)));
        pres = realloc(res, len + sizeof(buf));
        if (!pres)
            return NULL;
        res = (char*)pres;
        strcpy(res, buf);
    } while (nbytes == sizeof(buf));
    return res;
}


char* readall(int filedes)
{
    return getall(&filedes, read_wrapper);
}

char* recvall(SOCKET socket)
{
    return getall(&socket, recv_wrapper);
}