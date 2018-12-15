/*
 ============================================================================
 Name        : main.c
 Author      : Dennis Moore
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "registration.h"
#include "messaging.h"

zsock_t *dealer_sock;

int main(void)
{
	// right now only open one dealer socket; later on I may need to manage a socket pool
	dealer_sock = openConnection();

	//register a new robot with the server
	int8_t rc = registerNewBot("NCOBot", "socket_0");
	/*
	//check if reg was successful
	if(rc < 0) //reg failed, try again
	{
		registerNewBot("NCOBot", "socket_0");
	}
	*/

	closeConnection(dealer_sock);

	return EXIT_SUCCESS;
}
