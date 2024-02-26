/*
 * Tutorial 5 POSIX Thread Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2024, <Mostafa Abedi, Nathaniel Manoj, Calvin Reveredo>
 * All rights reserved.
 *
*/
#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // for sleep function

// Function to print "Hello, world!"
void *hello_world() {
    // Generate a random sleep duration between 1 and 3 seconds
    int sleep_duration = rand() % 3 + 1;
    // Sleep for the generated duration
    sleep(sleep_duration);
    printf("Hello, world!\n");
    pthread_exit(NULL);
}
// Function to print "Goodbye!"
void *goodbye() {
    // Generate a random sleep duration between 1 and 3 seconds
    int sleep_duration = rand() % 3 + 1;
    // Sleep for the generated duration
    sleep(sleep_duration);
    printf("Goodbye!\n");
    pthread_exit(NULL);
}
int main(void)
{
    srand(time(NULL));
    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, hello_world, NULL)) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }
    if (pthread_create(&thread2, NULL, goodbye, NULL)) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}
