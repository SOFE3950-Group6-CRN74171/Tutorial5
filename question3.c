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

#define NUM_STUDENTS 5

struct Student {
    char name[50];
    int student_id;
    int grade;
};

void *bellcurve(void *arg) {
    struct Student *student = (struct Student *) arg;
    student->grade *= 1.50;
    printf("Student Name: %s, ID: %d, Bellcurved Grade: %d\n", student->name, student->student_id, student->grade);
    pthread_exit(NULL);
}

int main(void)
{
    struct Student students[NUM_STUDENTS];

    printf("Enter information for %d students:\n", NUM_STUDENTS);
    for (int i = 0; i < NUM_STUDENTS; i++) {
        printf("Student %d Name: ", i + 1);
        scanf("%s", students[i].name);
        printf("Student %d ID: ", i + 1);
        scanf("%d", &students[i].student_id);
        printf("Student %d Grade: ", i + 1);
        scanf("%d", &students[i].grade);
    }

    pthread_t threads[NUM_STUDENTS];
    for (int i = 0; i < NUM_STUDENTS; i++) {
        if (pthread_create(&threads[i], NULL, bellcurve, (void *) &students[i])) {
            fprintf(stderr, "Error creating thread for student %d\n", i + 1);
            return 1;
        }
    }

    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
