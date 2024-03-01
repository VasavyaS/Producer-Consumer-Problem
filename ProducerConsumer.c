#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int* buffer;
int buffer_size;
int read_index = 0;
int write_index = 0;
int counter = 0;
int user_def = 20;

/*Declaring Semaphores */
sem_t mutex;
sem_t empty;
sem_t full;

int data;

void* producer(void* arg) {
    while (counter<user_def) {
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[write_index] = counter;
        write_index = (write_index + 1) % buffer_size;
        counter++;
        sem_post(&mutex);
        sem_post(&full);
    }
}

void* consumer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);
        int data = buffer[read_index];
        int data_counter = counter;
        read_index = (read_index + 1) % buffer_size;
        sem_post(&mutex);
        sem_post(&empty);
	  sleep(1);								// to give different consumers a chance
        printf("Consumer %d: Consumed %d \n", id, data);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <num_consumers> <limit>\n", argv[0]);
        return 1;
    }

    int num_consumers = atoi(argv[1]);
    user_def = atoi(argv[2]);	

    printf("Enter buffer size: ");
    scanf("%d", &buffer_size);

    buffer = (int*) malloc(buffer_size * sizeof(int));

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, buffer_size);
    sem_init(&full, 0, 0);

    pthread_t prod_tid;
    pthread_create(&prod_tid, NULL, &producer, NULL);

    pthread_t cons_tids[num_consumers];
    int cons_ids[num_consumers];
    for (int i = 0; i < num_consumers; i++) {
        cons_ids[i] = i;
        pthread_create(&cons_tids[i], NULL, &consumer, &cons_ids[i]);
    }

    pthread_join(prod_tid, NULL);
    for (int i = 0; i < num_consumers; i++) {
        pthread_join(cons_tids[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    free(buffer);

    return 0;
}

