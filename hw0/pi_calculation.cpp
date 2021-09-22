#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <chrono>
double pi = 0.0;
int NUM_OF_INTERVALS, NUM_OF_THREADS;
pthread_mutex_t mutex;
typedef std::chrono::high_resolution_clock Clock;
void* Pi(void* args) {
    int start;
    double h, sum, x;
    h = 1.0 / (double)NUM_OF_INTERVALS;
    sum = 0.0;
    start = *(int*)args;
    for (int i = start; i < NUM_OF_INTERVALS; i=i+NUM_OF_THREADS)
    {
        x = h * ((double)i - 0.5);
        sum += (4.0 / (1.0 + x * x));
    }
    pthread_mutex_lock(&mutex);
    pi += h * sum;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char *argv[]) {
    //std::cin >> NUM_OF_INTERVALS >> NUM_OF_THREADS;
    char *a = argv[1];
    char *b = argv[2];
    NUM_OF_INTERVALS = atoi(a);
    NUM_OF_THREADS = atoi(b);
    auto startTime = Clock::now();
    //NUM_OF_INTERVALS = 100000;
    //NUM_OF_THREADS = 2;
    pthread_t threads[NUM_OF_THREADS];
    int i;
    int threadArgs[NUM_OF_THREADS];
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < NUM_OF_THREADS; i++) {
    	threadArgs[i] = i;
    }
    for (i = 0; i < NUM_OF_THREADS; i++) {
    	pthread_create(&threads[i], NULL, Pi, &threadArgs[i]);
    }
    for (i = 0; i < NUM_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    auto stopTime = Clock::now();
    std::cout << pi << std::endl;
    std::cout << "Elapsed time: " << std::chrono::duration<double>(stopTime - startTime).count() << " s" << std::endl;
    return 0;
}
