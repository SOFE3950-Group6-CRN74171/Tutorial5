#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 10

int total_grade = 0;
int total_bellcurve = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;
FILE *grades_file;
FILE *bellcurve_file;

void *read_grades() {
    for (int i = 0; i < NUM_THREADS; i++) {
        int grade;
        fscanf(grades_file, "%d", &grade);
        pthread_barrier_wait(&barrier);
    }
    fclose(grades_file);
    pthread_exit(NULL);
}

void *save_bellcurve(void *arg) {
    int *grade_ptr = (int *) arg;
    int grade = *grade_ptr;
    free(grade_ptr);
    grade *= 1.50;
    pthread_mutex_lock(&mutex);
    total_grade += grade;
    total_bellcurve += grade;
    pthread_mutex_unlock(&mutex);
    fprintf(bellcurve_file, "%d\n", grade);
    pthread_barrier_wait(&barrier); // Wait for all threads to complete bell-curving
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t threads[NUM_THREADS];
    pthread_barrier_init(&barrier, NULL, NUM_THREADS + 1); // +1 for the main thread
    grades_file = fopen("grades.txt", "r");
    bellcurve_file = fopen("bellcurve.txt", "w");

    for (int i = 0; i < NUM_THREADS; i++) {
        int *grade = (int *)malloc(sizeof(int));
        fscanf(grades_file, "%d", grade);
        pthread_create(&threads[i], NULL, save_bellcurve, (void *) grade);
    }

    pthread_barrier_wait(&barrier); // Wait for all threads to start bell-curving

    pthread_create(&threads[0], NULL, read_grades, NULL);
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);

    printf("Total grade before bellcurve: %d\n", total_grade);
    printf("Class average before bellcurve: %.2f\n", (float) total_grade / NUM_THREADS);
    printf("Total bellcurved grade: %d\n", total_bellcurve);
    printf("Class average after bellcurve: %.2f\n", (float) total_bellcurve / NUM_THREADS);

    fclose(bellcurve_file);
    pthread_mutex_destroy(&mutex);

    return 0;
}
