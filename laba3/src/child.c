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
#include <math.h>

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

int main() {
    int fd = shm_open(MEMORY_NAME, O_EXCL | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    check_error(fd == -1, "Can't open shared memory file");
    if (ftruncate(fd, MEMORY_SIZE) == -1) {
        printf("File is too large");
    }
    res *addr = mmap(NULL, MEMORY_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    check_error(addr == (void*)-1, "Mmap error");
    addr->size = 0;

    char c;
    bool not_end = true;
    float nmbr = 0;
    float result = 0;
    float first = 0;
    int k = 0;
    float dot = 0;
    int count = 0;
    float numbers[100];

    do {
        if (not_end) {
            if (c <= '9' && c >= '0') {
                if (nmbr != 0 && (floor(nmbr) != nmbr)) {
                    if (c == '0') {
                        k += 1;
                        nmbr += 0;
                    }
                    else {
                        dot = c - '0';
                        nmbr = (nmbr + 0.1) + (dot / pow(10, k + 1));
                    }
                }
                else {
                    nmbr = nmbr * 10 + c - '0';
                }
            }
            if (c == '.') {
                nmbr = nmbr - 0.1;
            }
            if (c == ' ' || c == '\n' || c == EOF) {
                numbers[count] = nmbr;
                nmbr = 0;
                count++;
                if (c == '\n' || c == EOF) {
                    first = numbers[0];
                    for (int i = 1; i < count; i++) {
                        if (numbers[i] == 0) {
                            addr->data[addr->size++] = -1;
                        }
                        result = first / numbers[i];
                        first = result;
                    }
                    first = 0;
                    count = 0;
                }
            }
        }
        if (c == '\n' || c == EOF) {
            addr->data[addr->size++] = result;
            result = 0;
            k = 0;
            dot = 0;
            not_end = true;
        }
    } while((scanf("%c", &c)) > 0);

    return 0;
}