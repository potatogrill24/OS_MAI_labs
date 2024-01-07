#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

void countBullsAndCows(char *guess, char *target, int *bulls, int *cows) { //функция для подсчета коров и быков
    int i, j;
    *bulls = 0;
    *cows = 0;
    
    for (i = 0; i < strlen(guess); i++) {
        if (guess[i] == target[i]) {
            (*bulls)++;
        } else {
            for (j = 0; j < strlen(target); j++) {
                if (guess[i] == target[j]) {
                    (*cows)++;
                    break;
                }
            }
        }
    }
}

int main (int argc, char *argv[]) {
    int bulls, cows;
    countBullsAndCows(argv[2], argv[1], &bulls, &cows);
    dprintf(STDOUT_FILENO, "%d %d\n", bulls, cows);
    return 0;
}