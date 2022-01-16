#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#define N_DINNING_PHILOSOPHERS 5
#define SHOW_INTENTION true
#define SECONDS_TO_WAIT_BEFORE_HALT 30


struct _philosopher {
    unsigned short id;
    pthread_mutex_t* left_hashi;
    pthread_mutex_t* right_hashi;
    char* name;
};


typedef struct _philosopher phil_t;


int eat_status[N_DINNING_PHILOSOPHERS];
bool halt = false;


void init_mutexes(pthread_mutex_t mutexes[], int n) {
    for (int i = 0 ; i < n ; ++i) { pthread_mutex_init(&mutexes[i], NULL); }
}


void destroy_mutexes(pthread_mutex_t mutexes[], int n) {
    for (int i = 0 ; i < n ; ++i) { pthread_mutex_destroy(&mutexes[i]); };
}


void init_philosophers(int n, phil_t phils[], pthread_mutex_t hashis[]) {
    char* names[] = {"Aristotle", "Plato", "Socrates", "Democritus", "Descartes"};
    for (int i = 0 ; i < n ; ++i) {
        (phils + i)->id = i;
        (phils + i)->name = names[i];
        (phils + i)->left_hashi = &hashis[i == 0 ? n-1 : i-1];
        (phils + i)->right_hashi = &hashis[i];
    }
}


void eat(int time_eating, phil_t* philosopher) {
    printf(" %s is eating :)\n\n", philosopher->name);
    eat_status[philosopher->id] += 1;
    sleep(time_eating);
    printf(" %s stopped eating.\n\n", philosopher->name);
    return ;
}


void think(int time_thinking, phil_t* phil) {
    printf(" %s is thinking -_- (...)\n\n", phil->name);
    sleep(time_thinking);
}


void* timer(void* p) {
    sleep(SECONDS_TO_WAIT_BEFORE_HALT);
    halt = true;
}


void show_eat_status(phil_t *philosophers, int n) {
    for (int i = 0 ; i < n ; ++i) {
        printf(
            " %s eated %d times.\n\n",
            (philosophers + i)->name,
            eat_status[(philosophers + i)->id]
        );
    }
} 