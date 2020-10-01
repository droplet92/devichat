#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


char* readall(int socket)
{
    char buf[BUFSIZ] = {0};
    char* res = NULL;
    void* pres = NULL;
    size_t len = 0;
    ssize_t nbytes = 0;
    do
    {
        len += (nbytes = read(socket, buf, sizeof(buf)));
        pres = realloc(res, len + sizeof(buf));
        if (!pres)
            return NULL;
        res = (char*)pres;
        strcpy(res, buf);
    } while (nbytes == sizeof(buf));
    return res;
}
