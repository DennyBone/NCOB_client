/*
 ============================================================================
 Name        : registration.c
 Author      : Dennis Moore
 Description : Code for handling robot registration
 ============================================================================
 */

#include <czmq.h>
#include <string.h>
#include "registration.h"
#include "messaging.h"

int8_t registerNewBot(const char *botName, const char *sockName)
{
	int8_t retVal = -1;

	// create registration message
	const char *msg[3] = {"Register", botName, sockName};
	zmsg_t *reg_msg = zmsg_new();
	reg_msg = createMsg(msg, 3);

	// send registration message
	sendMsg(reg_msg, dealer_sock);

	// read server response
	zmsg_t *returnMsg = zmsg_new();
	returnMsg = readMsg(dealer_sock);
	char *reg_str = zmsg_popstr(returnMsg);

	// check if reg was successful; print out msg if so
	if(strcmp(reg_str, "0") == 0)
    {
        puts("Registration was successful");
        retVal = 0;
    }

	// clean up
	zstr_free(&reg_str);
	zmsg_destroy(&returnMsg);
	return retVal;
}
