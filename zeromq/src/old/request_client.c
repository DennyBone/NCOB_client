/*
 * request_client.c
 *
 *  Created on: Nov 12, 2018
 *      Author: dennis
 */


//  Hello World client, CZMQ simple example

#include <czmq.h>
#include <string.h>

int main(void)
{
    printf ("Connecting to server…\n");

    zsock_t *dealer_sock = zsock_new_req("tcp://192.168.0.16:61615");
    assert(dealer_sock);
    puts("client socket created");

    // create and send reg message with czmq
    zmsg_t *reg_msg = zmsg_new();
    assert(reg_msg);
    puts("message created");
    zmsg_addstr(reg_msg, "hello");
    int8_t rc = zmsg_send(&reg_msg, dealer_sock); // frees and nullifies reg_msg
    puts("sent msg");
    assert(rc == 0);
    assert(reg_msg == NULL);

    // wait for reply with blocking recv call(returns NULL if interrupted)
    reg_msg = zmsg_recv(dealer_sock);
    printf("received msg: %s\n", zmsg_popstr(reg_msg));
    assert(reg_msg);
    char *reg_str = zmsg_popstr(reg_msg);

    zstr_free(&reg_str);
    zmsg_destroy(&reg_msg);

    zsock_destroy(&dealer_sock);

    return 0;
}