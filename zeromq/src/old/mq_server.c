//  Hello World server, CZMQ simple example

#include <czmq.h>
#include <string.h>

int main (void)
{
    printf ("binding server…\n");

    zsock_t *dealer_sock = zsock_new_rep("tcp://*:61615");
    //assert(dealer_sock);
    puts("server socket created");

    // wait for reply with blocking recv call(returns NULL if interrupted)
    zmsg_t *reg_msg = zmsg_new();
    assert(reg_msg);
    puts("message created");
    reg_msg = zmsg_recv(dealer_sock);
    printf ("msg: %s\n", zmsg_popstr(reg_msg));
    //zmsg_destroy(&reg_msg);
    //char *reg_str = zmsg_popstr(reg_msg);

    // create and send reg message with czmq
    zmsg_addstr(reg_msg, "world");
    int8_t rc = zmsg_send(&reg_msg, dealer_sock); // frees and nullifies reg_msg
    puts("sent msg");
    assert(rc == 0);
    assert(reg_msg == NULL);

    //zstr_free(&reg_str);
    zmsg_destroy(&reg_msg);

    zsock_destroy(&dealer_sock);

    return 0;
}