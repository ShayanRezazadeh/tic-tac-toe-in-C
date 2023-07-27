#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/* options */
int show_numbers = 1;
int difficulty = 0; // {0 easy, 1 normal}
/* options */

unsigned Lines = 0;

/* Data Types */
typedef char Board[3][3];
typedef unsigned Coordinate[2];
/* Data Types */

void printboard(Board);
void get_user_decision(char*);
void setBoard(Coordinate, Board, char);
int isallnumc(char);
int isallnumcoordinate(char*);
void check_flags(unsigned, char**);
void get_user_coordinate(Coordinate, char, Board);
void compute_coordinate(Coordinate, Board, unsigned);
int check_for_winner(Board, unsigned);
void play();
void clearlines(unsigned);
void curmoveup(unsigned);
void curmovedown(unsigned);
void eraseline(unsigned);
void clearlines(unsigned);
void curbegofline();

void compute_coordinate(Coordinate coordinate, Board board, unsigned moves) {
    if (difficulty == 0) {
        fflush(stdout);
        do {
            srand(time(NULL));
            coordinate[0] = rand()%3; coordinate[1] = rand()%3;
            usleep(1000000);
        }while (board[coordinate[0]][coordinate[1]] != 0);
    }
    else if (difficulty == 1) {


    }
}




int main(unsigned argc, char** argv){
    check_flags(argc, argv);
    play();
    return 0;
}



void printboard(char board[3][3]){
    if (show_numbers) {puts("  1  2  3"); Lines++;}
    for (unsigned i=0; i<3; i++){
        if (show_numbers) {printf("%u ",i+1);}
        for (unsigned j=0; j<3; j++){
            if (board[i][j] == 88 || board[i][j] == 79) {
                printf("%c  ", board[i][j]);
            }
            else{
                printf("-  ");
            }
        }
        printf("\n");
        Lines++;
    }
}

void get_user_decision(char *user_decision){
    char* input = (char*)malloc(25);
    printf("Which one do you choose? (X or O)\n");
    Lines++;
    while (1){
        printf("I want to be: ");
        fgets(input, 25, stdin);
        if (input[0] > 97){input[0] -= 32;}
        if ((input[0] != 'X' && input[0] != 'O') || strlen(input) > 2){curmoveup(1);printf("--- Invalid input ---");fflush(stdout);usleep(1500000);curbegofline();eraseline(0);continue;}
        break;
    }
    Lines++;
    clearlines(Lines); Lines = 0;
    user_decision[0] = input[0];
    free(input);
}

void setBoard(Coordinate coordinate, Board board, char by) {
    board[coordinate[0]][coordinate[1]] = by;
}

int isallnumc(char c) {
    if (c < 48 || c > 57) {
        return 0;
    }
    return 1;
}
int isallnumcoordinate(char *str) {
    for (int i=0; i<strlen(str); i++) {
        if (!isallnumc(str[i]) && str[i] != 32 && str[i] != 10) {
            return 0;
        }
    }
    return 1;
}

void check_flags(unsigned argc, char** argv) {
    if (argc == 1 || argc >= 2 && strcmp(argv[1],"play") != 0) {
        puts("Usage: ttt play <options>\n\nOption\t\tDescription\n -n\t\tDon't show board's coordinates");
        exit(0);
    }
    for (unsigned i=2; i<argc; i++) {
        if (!strcmp(argv[i],"-n")) {
            show_numbers = 0;
        }

        else {
            printf("Invalid option [ \"%s\" ]\n", argv[i]);
            exit(1);
        }
    }
}

void get_user_coordinate(Coordinate user_coordinate, char user, Board board) {
    char input[3][25]= {{0},{0},{0}};
    while (1) {
        printf("place %c on: ",user);
        fgets(input[0], 25, stdin);
        Lines++;
        if (isallnumcoordinate(input[0])) {
            unsigned i=0;
            for (unsigned j=1; j<=2; j++) {
                unsigned index = 0;
                for (i; i<strlen(input[0])-1; i++) {
                    if (isallnumc(input[0][i])) {
                        input[j][index] = input[0][i];
                    }else if (input[0][i] == 32){
                        i++;
                        break;
                    }
                }
            }
            if (!(strlen(input[1]) < 1 && strlen(input[2]) < 1)) {
                user_coordinate[1] = atoi(input[1])-1;
                user_coordinate[0] = atoi(input[2])-1;
                if (user_coordinate[0] < 3 && user_coordinate[1] < 3 && user_coordinate[0] >=0 && user_coordinate[1] >= 0 && board[user_coordinate[0]][user_coordinate[1]] == 0) {
                    break;
                }
            }
        }
        curmoveup(1);printf("--- Invalid input ---");fflush(stdout);usleep(1500000);curbegofline();eraseline(0);continue;
    }
}


int check_for_winner(Board board, unsigned moves){
    char winner;
    for (unsigned y = 0; y < 3; y++) {
        winner = (board[0][y] != 0)? board[0][y]:'N';
        for (unsigned x = 0; x < 3; x++) {
            if (board[x][y] != winner) {
                break;
            }else if (board[x][y] == winner && x == 2) {
                return winner;
            }
        }
    }

    for (unsigned x = 0; x < 3; x++) {
        winner = (board[x][0] != 0)? board[x][0]:'N';
        for (unsigned y = 0; y < 3; y++) {
            if (board[x][y] != winner) {
                break;
            }else if (board[x][y] == winner && y == 2) {
                return winner;
            }
        }
    }

    if (board[0][0] == 0 ) {return (moves == 9)? (0):(-5);}
    winner = board[0][0];
    for (unsigned x = 0; x < 3;) {
        for (unsigned y = 0; y < 3;) {
            x++;y++;
            if (board[x][y] != winner) {
                break;
            }else if (board[x][y] == winner && y == 2) {
                return winner;
            }
        }
    }

    if (board[2][0] == 0 ) {return (moves == 9)? (0):(-5);}
    winner = board[2][0];
    for (unsigned x = 2; x < 3 && x >= 0;) {
        for (unsigned y = 0; y < 3;) {
            x--;y++;
            if (board[x][y] != winner) {
                x = 3;
                break;
            }else if (board[x][y] == winner && y == 2) {
                return winner;
            }
        }
    }


    return (moves == 9)? (0):(-5);
}

void play() {
    Board board = {{0},{0},{0}};
    char user,system;
    Coordinate coordinate;
    unsigned next; // 0 -> system       1 -> user
    unsigned moves=0;
    get_user_decision(&user);
    (user == 'X')? (system='O',next=1) : (system='X', next=0);// X starts first
    printf("=====  START =====\n");
    Lines++;
    while (1)  {
        printboard(board);
        eraseline(0);
        if (moves >= 5) {
            int winner = check_for_winner(board,moves);
            if (winner == 0) {
                puts("\n===== Game Tied (draw)=====");
                exit(0);
            }
            else if (winner > 0) {
                if (winner == user) {
                    puts("\n===== YOU WON =====\nCongratulation ! you defeated me");
                    exit(0);
                }
                else if (winner == system){
                    puts("\n===== You Lose =====\nComputer defeated you\nBetter luck next time");
                    exit(0);
                }
            }
        }
        if (next == 1) {
            get_user_coordinate(coordinate, user, board);
            setBoard(coordinate,board,user);
            next = 0;
            (show_numbers)?clearlines(5):clearlines(4);

        }
        else if (next == 0) {
            printf("--- MY turn --- (Computing the best move )   ");
            compute_coordinate(coordinate, board, moves);
            setBoard(coordinate, board, system);
            next = 1;
            (show_numbers)?clearlines(4):clearlines(3);
        }

        moves++;
    }
}
void curmoveup(unsigned lines) {printf("\x1B[%uA", lines);}
void curmovedown(unsigned lines) {printf("\x1B[%uB", lines);}
void eraseline(unsigned mode) {printf("\x1B[%uK \r", mode);}
void clearlines(unsigned lines) {
    for (unsigned i=0; i<lines; ++i) {
        curmoveup(1);
        eraseline(0);
    }
}
void curbegofline(){printf("\x1B[0G");} // place cursor at the beginnig of the line