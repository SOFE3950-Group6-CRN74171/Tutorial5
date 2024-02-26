/*
 * Tutorial 5 POSIX Thread Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2024, <Mostafa Abedi, Nathaniel Manoj, Calvin Reveredo>
 * All rights reserved.
 *
*/
#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_STUDENTS 10

int total_grade = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void class_total(int grade) {
    pthread_mutex_lock(&mutex);
    total_grade += grade;
    pthread_mutex_unlock(&mutex);
}

void *student_thread(void *arg) {
    int grade = *((int *) arg);
    class_total(grade);
    pthread_exit(NULL);
}

int main(void)
{
    int grades[NUM_STUDENTS];

    printf("Enter grades for %d students:\n", NUM_STUDENTS);
    for (int i = 0; i < NUM_STUDENTS; i++) {
        printf("Student %d: ", i + 1);
        scanf("%d", &grades[i]);
    }

    pthread_t threads[NUM_STUDENTS];
    for (int i = 0; i < NUM_STUDENTS; i++) {
        if (pthread_create(&threads[i], NULL, student_thread, (void *) &grades[i])) {
            fprintf(stderr, "Error creating thread for student %d\n", i + 1);
            return 1;
        }
    }

    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Total grade: %d\n", total_grade);

    return 0;
}

