#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

char* def;
char* res;
int res_len; 
int max_threads; 
int match_count;

void thread_create(pthread_t* thread, const pthread_attr_t* attr, void *(*start)(void *), void* arg);
void* thread_func(void* arg);