#include "func.h"
#define MAXIMUM 12

void thread_create(pthread_t* thread, const pthread_attr_t* attr, void *(*start)(void *), void* arg) {
    if (pthread_create(thread, attr, start, arg) != 0) {
        perror("create thread\n");
        exit(-1);
    }
}

void* thread_func(void* arg) {
    int start = *((int*) arg);
    int i, j;
    for (i = start; i <= (strlen(def) - res_len); i += max_threads) {
        for (j = 0; j < res_len; j++) {
            if (def[i + j] != res[j]) {
                break;
            }
        }
        if (j == res_len) {
            // printf("Вхождение на позиции %d\n", i);
            match_count++;
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Некорректный ввод аргументов\n");
        return 1;
    }

    def = argv[1];
    res = argv[2];
    res_len = strlen(res);
    max_threads = atoi(argv[3]);
    if (max_threads > MAXIMUM) {
        printf("Нельзя вводить больше потоков, чем допустимо\n");
        return 1;
    }

    pthread_t* threads = (pthread_t*)malloc(max_threads * sizeof(pthread_t));
    int* thread_args = (int*)malloc(max_threads * sizeof(int));

    int i;
    for (i = 0; i < max_threads; i++) {
        thread_args[i] = i;
        thread_create(&threads[i], NULL, thread_func, &thread_args[i]);
    }

    // int s_time = clock();
    for (i = 0; i < max_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Общее количество совпадений: %d\n", match_count);

    // printf("Время выполнения программы с использованием %d потоков составило %f с\n", max_threads, (float)(clock() - s_time)/CLOCKS_PER_SEC);

    free(thread_args);
    free(threads);
    return 0;
}