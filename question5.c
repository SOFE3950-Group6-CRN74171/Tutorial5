/*
 * Tutorial 5 POSIX Thread Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2024, <Mostafa Abedi, Nathaniel Manoj, Calvin Reveredo>
 * All rights reserved.
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // For sleep function

#define GRADES_COUNT 10
#define BELL_CURVE_FACTOR 1.50

int grades[GRADES_COUNT];
int total_grade = 0;
float total_bellcurve = 0;
pthread_barrier_t barrier;
pthread_mutex_t mutex;

void* read_grades(void* arg) {
    FILE* file = fopen("grades.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        pthread_exit(NULL);
    }

    for (int i = 0; i < GRADES_COUNT; ++i) {
        fscanf(file, "%d", &grades[i]);
    }

    fclose(file);
    pthread_barrier_wait(&barrier);
    return NULL;
}

void* save_bellcurve(void* arg) {
    int* grade = (int*)arg;
    float bellcurved_grade = (*grade) * BELL_CURVE_FACTOR;

    // Simulate some processing time
    usleep(100000); // 100ms delay

    pthread_mutex_lock(&mutex);
    total_grade += *grade;
    total_bellcurve += bellcurved_grade;

    FILE* file = fopen("bellcurve.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }
    fprintf(file, "%.2f\n", bellcurved_grade);
    fclose(file);

    pthread_mutex_unlock(&mutex);
    pthread_barrier_wait(&barrier);
    return NULL;
}

int main() {
    pthread_t threads[GRADES_COUNT + 1];
    pthread_barrier_init(&barrier, NULL, GRADES_COUNT + 1);
    pthread_mutex_init(&mutex, NULL);

    // Create and start read_grades thread
    pthread_create(&threads[0], NULL, read_grades, NULL);

    // Create and start save_bellcurve threads
    for (int i = 0; i < GRADES_COUNT; ++i) {
        pthread_create(&threads[i + 1], NULL, save_bellcurve, &grades[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < GRADES_COUNT + 1; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Calculate class average before and after bellcurve
    float class_average_before = (float)total_grade / GRADES_COUNT;
    float class_average_after = total_bellcurve / GRADES_COUNT;

    // Print results
    printf("Total Grade: %d\n", total_grade);
    printf("Class Average Before Bellcurve: %.2f\n", class_average_before);
    printf("Class Average After Bellcurve: %.2f\n", class_average_after);

    pthread_barrier_destroy(&barrier);
    pthread_mutex_destroy(&mutex);

    return 0;
}
