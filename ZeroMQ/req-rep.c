
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Connecting to server…\n");
    void *context = zmq_ctx_new();
    void *requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://unixlab.cs.put.poznan.pl:5555");
    
    int index_nb = 132350;
    int request_nbr;
    for(request_nbr = 0; request_nbr != 3; request_nbr++) {
        char buffer [100];
        printf("Sending index number %d, send nb %d…\n",index_nb, request_nbr);
        zmq_send(requester,(void*)&index_nb , sizeof(index_nb), 0);
        zmq_recv(requester, buffer, 100, 0);
        printf("Received answer:\n %s\n", buffer);
    }
    zmq_close(requester);
    zmq_ctx_destroy(context);
    return 0;
}
