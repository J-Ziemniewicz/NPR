#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>

int main (int argc, char *argv [])
{
    char *push = "Jan Ziemniewicz";
    clock_t t;
    double cpu_time_used;
    void *context = zmq_ctx_new();
    void *pusher = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(pusher, "tcp://unixlab.cs.put.poznan.pl:6005");
    

    for(int request_nbr = 0; request_nbr != 3; request_nbr++) {
        
        t = clock();
        zmq_send(pusher, push, strlen(push), 0);
        t = clock() - t;
         cpu_time_used = ((double) t) / CLOCKS_PER_SEC;
        printf("Received message: %f\n",cpu_time_used);
    }
    zmq_close(pusher);
    zmq_ctx_destroy(context);
    return 0;
}