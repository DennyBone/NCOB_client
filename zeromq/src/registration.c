/*
 ============================================================================
 Name        : main.c
 Author      : Dennis Moore
 Description : Code for handling robot registration
 ============================================================================
 */

#include <czmq.h>
#include <string.h>

void registerNewBot(char *botName, char *sockName)
{
	char serv_addr[] = "tcp://192.168.0.16:61617";

	// CZMQ code to create a dealer socket and connect to server
	zsock_t *dealer_sock = zsock_new_dealer(serv_addr);
	assert(dealer_sock);

	// create and send reg message with czmq
	zmsg_t *reg_msg = zmsg_new();
	assert(reg_msg);
	zmsg_addstr(reg_msg, "Register");
	zmsg_addstr(reg_msg, botName);
	zmsg_addstr(reg_msg, sockName);
	int8_t rc = zmsg_send(&reg_msg, dealer_sock); // frees and nullifies reg_msg
	assert(rc == 0);
	assert(reg_msg == NULL);

	// wait for reply with blocking recv call(returns NULL if interrupted)
	reg_msg = zmsg_recv(dealer_sock);
	assert(reg_msg);
	char *reg_str = zmsg_popstr(reg_msg);

	// check if reg was successful; print out msg if so
	if(strcmp(reg_str, "0") == 0)
    {
        puts("Registration was successful");
    }
	else
	{
		//add code to retry or return gracefully
	}

	//assert(streq(reg_str, "0")); // server returns '0' on successful registration
	zstr_free(&reg_str);
	zmsg_destroy(&reg_msg);
	zsock_destroy(&dealer_sock);
}
