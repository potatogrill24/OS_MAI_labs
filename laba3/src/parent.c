#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "stddef.h"
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>

#define MEMORY_NAME "laba4"
#define DATA_SIZE 256
#define MEMORY_SIZE 8192

void check_error(bool expression, char* message) {
    if (expression) {
        write(STDOUT_FILENO, message, strlen(message) * sizeof(char));
        write(STDOUT_FILENO, "\n", 1);
        exit(-1);
    }
}

typedef struct {
    size_t size;
    float data[DATA_SIZE];
} res;

int main (int argc, char* argv[]) {
    pid_t pid;
    FILE *fp = NULL;
    // int pipe_1[2];
    // if (pipe(pipe_1) == -1) {
    //     perror("pipe");
    //     _exit(EXIT_FAILURE);
    // }
    if (argc != 2) {
        write(1, "Wrong arguments\n", 17);
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    else if (pid == 0) {
        fp = freopen(argv[1], "r", stdin);
        check_error(fp == NULL, "Can't open file");
        // close (pipe_1[0]);
        // check_error(dup2(fd, STDIN_FILENO) < 0, "Error dub");
        // dup2(pipe_1[1], STDOUT_FILENO);
        execl("./child", "/.child", NULL);
        perror("execl");
        return 1;
    }
    else {
        // check_error((pid == -1), "Process error");
        // close(pipe_1[1]);
        wait(0);
        int fd = shm_open(MEMORY_NAME, O_RDONLY, S_IRUSR | S_IWUSR);
        check_error(fd == -1, "Can't oped shared memory file");
        res *addr = mmap(NULL, MEMORY_SIZE, PROT_READ, MAP_SHARED, fd, 0);
        check_error(addr == (void*) -1, "Mmap error");
        for (int i = 0; i < addr->size; i++) {
            if (addr->data[i] == -1) {
                printf("Attempt to divide by zero\n");
                break;
            }
            printf("%f\n", addr->data[i]);
        }
        munmap(addr, MEMORY_SIZE);
        shm_unlink(MEMORY_NAME);
        close(fd);
        // float result;
        // char answer[50];
        // while ((read(pipe_1[0], &result, sizeof(float))) > 0) {
        //     if (result == -1) {
        //         write(STDOUT_FILENO, "Attempt to divide by zero\n", 27);
        //         exit(EXIT_FAILURE);
        //     }
        //     sprintf(answer, "%f\n", result);
        //     check_error(write(STDOUT_FILENO, answer, strlen(answer)) == -1, "Write error\n");
        //     check_error(write(STDOUT_FILENO, "\n", 1) == -1, "Write error\n");
        // }
    }
    return 0;
}
