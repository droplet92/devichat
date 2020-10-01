#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#define READ  0
#define WRITE 1

void SendMessageToPipe(char* msg);
void BroadcastMessage(int signum);
void SendMessage(int signum);

#endif