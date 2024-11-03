#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_hello(void *arg) {
    int thread_id = *(int *)arg;
    printf("Hello from thread %d\n", thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    int thread_ids[2];

    for (int i = 0; i < 2; i++) {
        thread_ids[i] = i;
        int ret = pthread_create(&threads[i], NULL, print_hello, &thread_ids[i]);
        if (ret != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            exit(1);
        }
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished.\n");
    return 0;
}
