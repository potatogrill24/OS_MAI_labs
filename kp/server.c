#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

#define PIPE_READ 0
#define PIPE_WRITE 1
#define MAX_PLAYERS 10
#define MAX_ATTEMPTS 5

typedef struct {
    int fd[2];
    char word[4];
} Player;

char* generateWord() { //функция для генерации рандомного слова
    srand(time(NULL));
    char* word = (char*)malloc(5 * sizeof(char));
    for (int i = 0; i < 4; i++) {
        word[i] = 'a' + rand() % 26;
    }
    word[4] = '\0';
    return word;
}

int main() {
    int numPlayers;
    int numConnectedPlayers = 0;
    Player players[MAX_PLAYERS];

    printf("Введите количество игроков (максимум %d): ", MAX_PLAYERS);
    scanf("%d", &numPlayers);
    numConnectedPlayers = numPlayers;

    if (numPlayers > MAX_PLAYERS) {
        printf("Превышено максимальное количество игроков\n");
        return 1;
    }
    else {
        printf("Итак, будут играть %d игроков\n", numPlayers);
    }

    printf("\n");
    char* word = generateWord();
    printf("Загаданное слово - %s\n", word);
    printf("Загадано слово из 4 букв, ваша задача угадать его, все просто!\n");
    printf("Все игроки ходят по очереди, всего будет 5 попыток, если за 5 попыток никто так и не угадает слово,\n");
    printf("то это будет означать проигрыш. Успехов!\n");
    bool first_iter = true;
    int number_to_exit[5] = {-1, -1, -1, -1, -1};
    int i;

    for (i = 0; i < MAX_ATTEMPTS; i++) {
        int j;
        int k;

        if (!first_iter) {
            printf("Желает ли кто-то выйти из игры? (-1, если никто): ");
            scanf("%d", &number_to_exit[i]);
            if (!(number_to_exit[i] > 0 && number_to_exit[i] <= numPlayers) && number_to_exit[i] != -1) {
                printf("Нет такого игрока\n");
            }
            if (number_to_exit[i] != -1 && (number_to_exit[i] > 0 && number_to_exit[i] <= numPlayers)){
                numConnectedPlayers -= 1;
                printf("Осталось игроков: %d\n", numConnectedPlayers);
            }
        }

        if (numConnectedPlayers == 0) {
            printf("Все игроки ливнули\n");
            return 1;
        }

        for (j = 1; j <= numPlayers; j++) {
            if (j != number_to_exit[0] && j != number_to_exit[1] && j != number_to_exit[2] && j != number_to_exit[3] && j != number_to_exit[4]) {
                printf("Игрок %d делает ход: ", j);
                scanf("%s", players[j].word);
            }
        }

        for (k = 1; k <= numPlayers; k++) {
            first_iter = false;
            if (k != number_to_exit[0] && k != number_to_exit[1] && k != number_to_exit[2] && k != number_to_exit[3] && k != number_to_exit[4]) {
                if (pipe(players[k].fd) == -1 ) {
                    perror("pipe");
                    break;
                }
                int pid;
                pid = fork();
                if (pid == -1) {
                    printf("Не удалось создать нового игрока\n");
                    break;
                }
                else if (pid == 0) {
                    close(players[k].fd[PIPE_READ]);
                    if (dup2(players[k].fd[PIPE_WRITE], STDOUT_FILENO) == -1) {
                        perror("dup2");
                        exit(1);
                    }
                    close(players[k].fd[PIPE_WRITE]);
                    execl("./user", "./user", word, players[k].word, NULL);
                    perror("execl");
                    return 1;
                }
                else {
                    close(players[k].fd[PIPE_WRITE]);
                    char buffer[100];
                    ssize_t bytesRead = read(players[k].fd[PIPE_READ], buffer, sizeof(buffer));
                    if (bytesRead == -1) {
                        perror("read");
                        exit(1);
                    }
                    int bulls = atoi(buffer);
                    char *stat_2 = buffer;
                    while (*stat_2 != ' ') {
                        stat_2++;
                    }
                    stat_2++;
                    int cows = atoi(stat_2);
                    printf("Попытка игрока %d::: Быки: %d, Коровы: %d\n", k, bulls, cows);
                    if (bulls == 4) {
                        printf("Игрок %d победил!\n", k);
                        return 0;
                    }
                    if (i == MAX_ATTEMPTS - 1) {
                        printf("\n");
                        printf("К сожалению вы проиграли( Никто не смог угадать слово\n");
                        return 0;
                    }
                    wait(NULL);
                }
            }
            
        }
    }
}







    