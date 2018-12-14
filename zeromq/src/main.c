/*
 ============================================================================
 Name        : main.c
 Author      : Dennis Moore
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "registration.h"

int main(void)
{
	//register a new robot with the server
	registerNewBot("NCOBot", "socket_0");

	return EXIT_SUCCESS;
}
