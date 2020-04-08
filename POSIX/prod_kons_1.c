#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

volatile int buf;
int buf_change = 0;

void* prod(void *p){
   int i;
   pthread_mutex_lock(&mut);
   for (i=0;i<100;i++){
      while(buf_change !=0) pthread_cond_wait(&cond,&mut);
      buf = i;
      buf_change++;
      pthread_cond_signal(&cond);
   }
   pthread_mutex_unlock(&mut);
}

void* kons(void *p){
   int i;
   pthread_mutex_lock(&mut);
   for (i=0;i<100;i++){
      while(buf_change==0) pthread_cond_wait(&cond,&mut); 
      printf("%d\n", buf);
      buf_change--;
      pthread_cond_signal(&cond);
   }
   pthread_mutex_unlock(&mut);
}

int main(){
   pthread_t pth1, pth2;
   pthread_create(&pth1, NULL, prod, NULL);
   pthread_create(&pth2, NULL, kons, NULL);
   pthread_join(pth1, NULL);
   pthread_join(pth2, NULL);
}
