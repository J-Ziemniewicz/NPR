#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 5

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int buf[MAX];
int prod_buf = 0, kons_buf = 0;

void* prod(void *p){
   int index = 0;
   int i;
   pthread_mutex_lock(&mut);
   for (i=0;i<100;i++){
      while((prod_buf +1) % MAX == kons_buf ) pthread_cond_wait(&cond,&mut);
      buf[prod_buf] = i;
      pthread_cond_signal(&cond);
      prod_buf = (prod_buf+1)%MAX;       
   }
   pthread_mutex_unlock(&mut);
}

void* kons(void *p){
   int index1 = 0;
   int i;
   pthread_mutex_lock(&mut);
   for (i=0;i<100;i++){      
      while(prod_buf == kons_buf) pthread_cond_wait(&cond,&mut);
      printf("%d\n", buf[kons_buf]);
      pthread_cond_signal(&cond);
      kons_buf = (kons_buf + 1) % MAX;
   
   }
   pthread_mutex_unlock(&mut);
}

int main(){
   pthread_t pth1, pth2;
   printf("test\n");
   pthread_create(&pth1, NULL, prod, NULL);
   pthread_create(&pth2, NULL, kons, NULL);
   pthread_join(pth1, NULL);
   pthread_join(pth2, NULL);
}
