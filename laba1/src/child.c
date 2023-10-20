#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define buf_size 100

int main() {
    int c;
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
                            result = -1;
                            write(STDOUT_FILENO, &result, sizeof(result));
                        }
                        result = first / numbers[i];
                        first = result;
                    }
                    not_end = false;
                    first = 0;
                    count = 0;
                }
            }
        }
        if (c == '\n' || c == EOF) {
            write(STDOUT_FILENO, &result, sizeof(result));
            result = 0;
            k = 0;
            dot = 0;
            not_end = true;
        }
    } while((read(STDIN_FILENO, &c, sizeof(char))) > 0);

    return 0;
}