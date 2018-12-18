/*
 ============================================================================
 Name        : messaging.c
 Author      : Dennis Moore
 Description : Code for handling 0mq messages and sockets
 ============================================================================
 */

#include "messaging.h"

const char serv_addr[] = "tcp://192.168.0.16:61615";

// caller needs to handle deleting the socket(by calling closeConnection())
zsock_t * openConnection()
{
	// CZMQ code to create a dealer socket and connect to server
	zsock_t *sock = zsock_new_dealer(serv_addr);
	assert(sock);
	return sock;
}

void closeConnection(zsock_t *sock)
{
	zsock_destroy(&sock);
}

void sendMsg(zmsg_t *msg, zsock_t *sock)
{
	int8_t rc = zmsg_send(&msg, sock); // frees and nullifies msg
	assert(rc == 0);
	assert(msg == NULL);
}

// caller needs to free the msg when done
zmsg_t * readMsg(zsock_t *sock)
{
	zmsg_t *msg = zmsg_new();
	msg = zmsg_recv(sock); // wait for reply with blocking recv call(returns NULL if interrupted)
	assert(msg);
	return msg;
}

// caller needs to free the msg
zmsg_t * createMsg(char *inMsg[], uint8_t size)
{
	zmsg_t *msg = zmsg_new();
	assert(msg);
	uint8_t i;
	for(i = 0; i < size; i++)
	{
		zmsg_addstr(msg, inMsg[i]);
	}

	return msg;
}