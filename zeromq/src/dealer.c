/*
 * dealer.c
 *
 *  Created on: Dec 3, 2017
 *      Author: dennis
 */


#include "zhelpers.h"

void *context;
void *dealer;
int receivedCount = 0;
int sentCount = 0;

void SendMessage(char*);
char* ReadMessage();

int main(void)
{
	// Socket to talk to server
	context = zmq_ctx_new();
    dealer = zmq_socket(context, ZMQ_DEALER);
    zmq_connect(dealer, "tcp://192.168.0.10:61615");

    int total = 0;
    while (1)
    {
        // send handshake message to server
        SendMessage("Sup");

        // receive the response
        char *workload = ReadMessage();
        //int rc = strcmp(workload, "Dude");
        free(workload);
        /*
        if(rc == 0)
        {
        	printf("messages matched");
        }
        */

        if (total == 3)
        {
            printf("Sent %d messages", total);
            break;
        }

        total++;
        //  sleep for one second
        //s_sleep(1000);
    }

    /*
     * This code demonstrates sending and receiving in any order
    // send handshake message to server
    SendMessage("sup");

    // receive the response
    char *receivedMsg = ReadMessage();
    //int rc = strcmp(*receivedMsg, "Registered");
    int rc = 0;
    free(receivedMsg);

    // if the response is good, go into read mode for a few seconds
	if(rc == 0)
    {
    	printf("messages matched\n");
    	SendMessage("READ MODE");
    	//int total = 0;
    	while(1)
    	{
    		// do a little work
    		s_sleep(1000);

    		// try to read a message
    		printf("Calling ReadMessage\n");
    		char *msg = ReadMessage();
    		free(msg);
    	    //char *receivedMsg = ReadMessage();
    	    //int rc = strcmp(*receivedMsg, "Done");
    	    //free(receivedMsg);

    		// do a little more work
    		s_sleep(1000);

    		// exit after X times
            if (receivedCount == 4)
            {
                printf("Exiting read mode\n");
                break;
            }
            //total++;
    	}

        // exit read mode and send a few more messages
        SendMessage("One");
        SendMessage("Two");
        SendMessage("Three");
    }
    */

    zmq_close(dealer);
    zmq_ctx_destroy(context);
    return 0;
}

//  Send msg to server router socket
void SendMessage(char* msg)
{
    s_sendmore(dealer, "");
    s_sendmore(dealer, "VM Client");
    s_send(dealer, msg);
	sentCount++;
	printf("sent msg %d : %s\n", sentCount, msg);
}

// receive msg from server
char* ReadMessage()
{
    // receive msg from server
    char* delimeter = s_recv(dealer);
    size_t delSize = strlen(delimeter);
    printf("delSize: %zu\n", delSize);
    printf("delValue: %s\n", delimeter);
    //free(delimeter);     //  Envelope delimiter

	char *msg = s_recv(dealer);
    receivedCount++;
    printf("received msg %d : %s\n", receivedCount, msg);
    return msg;
}


#if 0
// install and include czmq

	// Do I want to use the high level API or no?
	// thinking no - the high level api is a little confusing

	int rc;

	// open dealer socket
    //  Prepare our context and sockets
    void *context = zmq_ctx_new ();
    void *dealer  = zmq_socket (context, ZMQ_DEALER);
    //zmq_bind (backend,  "tcp://*:5560");
    zmq_connect(dealer, "tcp://localhost:5559");

	//  Test send and receive of multi-frame message
	msg = zmsg_new();
	assert(msg);
	rc = zmsg_addmem(msg, "", 1); // empty frame for delimiter - size of 0 or 1?
	assert(rc == 0);
	rc = zmsg_addmem(msg, "Frame1", 6); // message to send
	assert(rc == 0);

    rc = zmsg_send(&msg, dealer); // is dealer right here?
    assert(rc == 0);
#endif
