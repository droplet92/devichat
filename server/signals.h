#ifndef __SIGNALS_H__
#define __SIGNALS_H__

#include <signal.h>

#define SIGBROADCAST  SIGUSR1
#define SIGSEND       SIGUSR2

void RegisterHandlers();
void Terminate(int signum);
void Wait(int signum);

#endif