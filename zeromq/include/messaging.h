#ifndef MESSAGING
#define MESSAGING

#include <czmq.h>
#include <stdint.h>
#include <string.h>

zsock_t * openConnection();
void closeConnection(zsock_t *sock);
void sendMsg(zmsg_t *msg, zsock_t *sock);
zmsg_t * readMsg(zsock_t *sock);
zmsg_t * createMsg(const char *inMsg[], uint8_t size);

extern const char serv_addr[];
extern zsock_t *dealer_sock;

#endif