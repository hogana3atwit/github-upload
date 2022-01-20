#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 
  
int g = 0;     // this is a global variable
  
void *enterHere(void *args) { 
    unsigned long int *myID = (unsigned long int *) args; 
  
    static int s = 0;   // this is a static variable

    int k = 0;		// this is a local variable
  
    printf("Thread ID: %ld,   (Static: %d)   (Global: %d)   (Local: %d)\n", *myID, ++s, ++g, ++k); 
} 
  
int main() { 
    int i; 
    pthread_t tid; 
  
    for (i = 0; i < 3; i++) 
        pthread_create(&tid, NULL, enterHere, (void *)&tid); 


    printf("All threads share the data segment where the global and static variables are stored in! \n");
  
    pthread_exit(NULL);		// this or pthread_join()
    return 0; 
} 
