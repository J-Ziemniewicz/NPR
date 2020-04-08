#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 5

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_prod, cond_kons = PTHREAD_COND_INITIALIZER;

// Konsument wypisuje wszystko co stworzył producent, czyli dwa razy liczby od 0 do 99

int buf[MAX];
int buf_prod = 0, buf_kons =0;

void* prod(void *p){
   int i;
   pthread_mutex_lock(&mut);
   for (i=0;i<100;i++){
      while((buf_prod +1) % MAX == buf_kons ) pthread_cond_wait(&cond_prod,&mut);
      // printf(" index %d\n",buf_prod);
      buf[buf_prod] = i;
      pthread_cond_signal(&cond_kons);
      buf_prod = (buf_prod + 1) % MAX;
   }
   pthread_mutex_unlock(&mut);
}

void* kons(void *p){
   int i;
   pthread_mutex_lock(&mut);
   for (i=0;i<100;i++){
      while(buf_prod == buf_kons ) pthread_cond_wait(&cond_kons,&mut);
      printf("%d\n", buf[buf_kons]);
      pthread_cond_signal(&cond_prod);
      buf_kons = (buf_kons + 1) % MAX;
   }
   pthread_mutex_unlock(&mut);
}

int main(){
   pthread_t pth1, pth2, pth3, pth4;
   pthread_create(&pth1, NULL, prod, NULL);
   pthread_create(&pth2, NULL, prod, NULL);
   pthread_create(&pth3, NULL, kons, NULL);
   pthread_create(&pth4, NULL, kons, NULL);
   pthread_join(pth1, NULL);
   pthread_join(pth2, NULL);
   pthread_join(pth3, NULL);
   pthread_join(pth4, NULL);
}
