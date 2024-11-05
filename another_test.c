#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
typedef struct {
   int  thread_id;
   int  *address;
   
}thread_data;
// Function to be executed by each thread
void* threadFunction(void* arg) {
    thread_data* args = (thread_data*)arg;
    *(args->address) *= 2;
    printf("Hello from thread %d\n", args->thread_id);
    printf("%d\n", *(args->address));

    sleep(1); // Simulate some work being done
    return NULL;
}

int main() {
    int num_threads = 5;
    pthread_t threads[num_threads];
    thread_data thread_datas[num_threads];
    int test = 2;
    // Create threads
    for (int i = 0; i < num_threads; i++) {
        thread_datas[i].thread_id = i + 1;
        thread_datas[i].address = &test;
        if (pthread_create(&threads[i], NULL, threadFunction, &thread_datas[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Join threads
    for (int i = 0; i < num_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    printf("All threads have finished execution.\n");
    return 0;
}

