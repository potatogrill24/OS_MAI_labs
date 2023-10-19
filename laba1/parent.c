#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#define max_size 255

void check_error(bool expression, char* message) {
    if (expression) {
        write(STDOUT_FILENO, message, strlen(message) * sizeof(char));
        write(STDOUT_FILENO, "\n", 1);
        exit(-1);
    }
}

int main (int argc, char* argv[]) {
    pid_t pid;
    int pipe_1[2];
    if (argc != 2) {
        write(1, "Error: no filename\n", 20);
        exit(EXIT_FAILURE);
    }
    int fd = open(argv[1], O_RDONLY);
    check_error(fd == -1, "Can't open file");
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    else if (pid == 0) {
        close (pipe_1[0]);
        check_error(dup2(fd, STDIN_FILENO) < 0, "Error dub");
        dup2(pipe_1[1], STDOUT_FILENO);
        execl("./child", "/.child", NULL);
        perror("execl");
        return 1;
    }
    else {
        check_error((pid == -1), "Process error");
        printf("sssssss\n");
        close(pipe_1[1]);
        wait(0);
        float result;
        char answer[50];
        while ((read(pipe_1[0], &result, sizeof(float))) > 0) {
            if (result == -1) {
                write(STDOUT_FILENO, "Attempt to divide by zero\n", 27);
            }
            sprintf(answer, "%f\n", result);
            check_error(write(STDOUT_FILENO, answer, strlen(answer)) == -1, "Write error\n");
            check_error(write(STDOUT_FILENO, "\n", 1) == -1, "Write error\n");
        }
    }
    return 0;
}