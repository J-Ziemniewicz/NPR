#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv [])
{
    
    void *context = zmq_ctx_new();
    void *publisher = zmq_socket(context, ZMQ_SUB);
    zmq_connect(publisher, "tcp://unixlab.cs.put.poznan.pl:6005");
    zmq_setsockopt (publisher, ZMQ_SUBSCRIBE, "", 0);

    
    for(int request_nbr = 0; request_nbr != 3; request_nbr++) {
        char buffer[50];
        zmq_recv(publisher,buffer,50,0);
        printf("Received message: %s\n",buffer);
    }
    zmq_close(publisher);
    zmq_ctx_destroy(context);
    return 0;
}
