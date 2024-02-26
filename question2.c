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

#define NUM_STUDENTS 5

void *bellcurve(void *arg) {
    int *grade = (int *) arg;
    *grade *= 1.50; // Bellcurve the grade
    printf("Bellcurved grade: %d\n", *grade);
    pthread_exit(NULL);
}

int main(void)
{
    // Array to hold student grades
    int grades[NUM_STUDENTS];

    // Prompt the professor for grades
    printf("Enter grades for %d students:\n", NUM_STUDENTS);
    for (int i = 0; i < NUM_STUDENTS; i++) {
        printf("Student %d: ", i + 1);
        scanf("%d", &grades[i]);
    }

    pthread_t threads[NUM_STUDENTS];
    for (int i = 0; i < NUM_STUDENTS; i++) {
        if (pthread_create(&threads[i], NULL, bellcurve, (void *) &grades[i])) {
            fprintf(stderr, "Error creating thread for student %d\n", i + 1);
            return 1;
        }
    }

    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

