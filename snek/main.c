#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BOARDSIZE 22
#define SNEKSIZE 25
#define SNEKSPEED 300
#include "windows.h"
#include <conio.h>
//delay or Sleep^
//setconsolecursorpostion est un equivalent de gotoxy

typedef struct strPoint{ //A declarer hors du main pour le redre global.

     int X,Y;

    }point;

typedef enum enumdirection{

    haut,bas,gauche,droite

}direction;


void startMenu(); //done
void gotoxy(int col,int lin); //done
void goAndPrint(int col, int lin,char car);
void initBoard(char board[BOARDSIZE][BOARDSIZE]); //done
void initSnake(point snake[SNEKSIZE]);
void createBoard(char board[BOARDSIZE][BOARDSIZE]); //done
void showBoard(char board[BOARDSIZE][BOARDSIZE]); //done
void setNewBoard(char board[BOARDSIZE][BOARDSIZE]); //done
void spawnSnake(point snake[SNEKSIZE]); //done
direction getInput(char input); //done
void moveSnake(point snake[SNEKSIZE],char input,char board[BOARDSIZE][BOARDSIZE]); //done
void spawnTreat(char board[BOARDSIZE][BOARDSIZE]); //done
void collision(point snake[SNEKSIZE],char board[BOARDSIZE][BOARDSIZE],char *input);
void gameOver(point snake[SNEKSIZE]);
int measureSnake(point snake[SNEKSIZE]);
void growSnake (point snake[SNEKSIZE]);
void levelup(char board[BOARDSIZE][BOARDSIZE],point snake[SNEKSIZE]);
int proposeNewGame();



int main()
{
    direction input = droite;
    srand(time(NULL));
    char board[BOARDSIZE][BOARDSIZE];
    point snake[SNEKSIZE];

    startMenu();
    do{
        initBoard(board);
        initSnake(snake);
        createBoard(board);
        setNewBoard(board);
        setNewBoard(board);
        setNewBoard(board);
        showBoard(board);
        spawnSnake(snake);
        spawnTreat(board);
        input = 'd';
        do{
            input = getInput(input);
            moveSnake(snake,input,board);
            collision(snake,board,&input);
            Sleep(SNEKSPEED - (measureSnake(snake)*15));
        } while (snake[0].X != 0);
    }while(proposeNewGame() == 0);

    return 0;
}

void initBoard(char board[BOARDSIZE][BOARDSIZE]){
    int i = 0;
    int j = 0;

    for(i = 0 ; i < BOARDSIZE ; i++){
        for(j = 0 ; j < BOARDSIZE ; j++){
            board[i][j] = ' ';
        }
    }
}

void initSnake(point snake[SNEKSIZE]){

    int i=0;
    for(i=0;i<SNEKSIZE;i++){
        snake[i].X = 0;
        snake[i].Y = 0;
    }

}

void startMenu(){
    Sleep(3000);
    printf("\n");
    printf("          SNAKE\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("      PRESS TO START\n");
    printf("\n");
    printf("\n");

    system("pause");
}

void gotoxy(int col, int lin){

    COORD coord;
    coord.X = col;
    coord.Y = lin;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE) , coord);

}

void goAndPrint(int col, int lin,char car){

    gotoxy(col,lin);
    putchar(car);
    gotoxy(0,23);

}

void createBoard(char board[BOARDSIZE][BOARDSIZE]){

    int i = 0;
    int j = 0;

    for(i = 0 ; i < BOARDSIZE ; i++){
        for(j = 0 ; j < BOARDSIZE ; j++){
            if ((i == 0) || (j==0) || (i == BOARDSIZE-1) || (j == BOARDSIZE-1)) board[i][j] = '#';
        }
    }

}

void showBoard(char board[BOARDSIZE][BOARDSIZE]){
    system("cls");



    int i = 0;
    int j = 0;

    for(i = 0 ; i < BOARDSIZE ; i++){
        for(j = 0 ; j < BOARDSIZE ; j++){
            printf("%c",board[j][i]);
        }
        printf("\n");
    }

}

void setNewBoard(char board[BOARDSIZE][BOARDSIZE]){

    point newWall;
    int counter = 0;

    do{

        newWall.X = (rand() % BOARDSIZE) + 1;
        newWall.Y = (rand() % BOARDSIZE) + 1;

        if (newWall.Y == 1) newWall.Y++;
        if (board[newWall.X][newWall.Y] != '#'){

            board[newWall.X][newWall.Y] = '#';
            counter++;

        }

    }while (counter < 5);

}

void spawnSnake(point snake[SNEKSIZE]){

    int i = 0;

    for( i = 0 ; i<SNEKSIZE ; i++ ){

        snake[i].X = 0;
        snake[i].Y = 0;

    }

    snake[0].X = 3;
    snake[0].Y = 1;

    snake[1].X = 2;
    snake[1].Y = 1;

    snake[2].X = 1;
    snake[2].Y = 1;

    i = 0;

    do{
        goAndPrint(snake[i].X,snake[i].Y,'o');
        i++;
    }while (snake[i].X != 0);

    Sleep(300);

}

direction getInput(char input){

    fflush(stdin);


        if(GetAsyncKeyState(0x5A)){
            if (input != haut) return bas;
            else return haut;
        }

        if(GetAsyncKeyState(0x53)){
            if (input != bas) return haut;
            else return bas;
        }

        if(GetAsyncKeyState(0x51)){
            if (input != droite) return gauche;
            else return droite;
        }

        if(GetAsyncKeyState(0x44)){
            if (input != gauche) return droite;
            else return gauche;
        }

        switch (input){

        case 'z' :
            return haut;
            break;

        case 's' :
            return bas;
            break;

        case 'q' :
            return gauche;
            break;

        case 'd' :
            return droite;
            break;;

    }

}

void moveSnake(point snake[SNEKSIZE],char input,char board[BOARDSIZE][BOARDSIZE]){

    point oldSnek[SNEKSIZE];
    int i = 0;

    do{
        board[snake[i].X][snake[i].Y] = ' ';
        goAndPrint(snake[i].X,snake[i].Y,' ');
        oldSnek[i].X = snake[i].X;
        oldSnek[i].Y = snake[i].Y;
        i++;
    }while (snake[i].X != 0);

    switch (input){

    case bas :
        snake[0].Y--;
        break;

    case haut :
        snake[0].Y++;
        break;

    case gauche :
        snake[0].X--;
        break;

    case droite :
        snake[0].X++;
        break;

    }
    i = 1;

    do{
        snake[i] = oldSnek[i-1];
        i++;
    }while (snake[i].X != 0);

    i = 0;

    do{
        if (i!=0) board[snake[i].X][snake[i].Y] = 'o';
        goAndPrint(snake[i].X,snake[i].Y,'o');
        i++;
    }while (snake[i].X != 0);

}

void spawnTreat(char board[BOARDSIZE][BOARDSIZE]){

    int col = 0;
    int lin = 0;

    do{

        col = rand() % 21 + 1;
        lin = rand() % 21 + 1;

    }while(board[col][lin] != ' ');

    goAndPrint(col,lin,'*');
    board[col][lin] = '*';
}

int measureSnake(point snake[SNEKSIZE]){

    int i = 0;

    do{
        i++;
    }while (snake[i].X != 0);

    return i;

}
void growSnake(point snake[SNEKSIZE]){

    int i = 0;
    do{

        i++;

    }while (snake[i].X != 0);

    goAndPrint(23,3,i+'0');
    snake[i].X = 22;
    snake[i].Y = 22;

}

void gameOver(point snake[SNEKSIZE]){

    int i = 0;

    Sleep(1000);

    for(i=0;i<SNEKSIZE;i++){
        snake[i].X = 0;
        snake[i].Y = 0;
    }

    system("cls");

    printf("\n\n\n     GAME OVER\n\n\n\n\n");

    Sleep(2000);


}

void levelup(char board[BOARDSIZE][BOARDSIZE],point snake[SNEKSIZE]){

    system("cls");

    printf("\n\n   LEVEL FINISHED\n\n");
    printf("\n\n    NEW LEVEL IN\n\n");
    printf("\n\n        3\n\n");
    Sleep(300);
    printf("\n\n        2\n\n");
    Sleep(300);
    printf("\n\n        1\n\n");
    Sleep(300);

    system("cls");

    setNewBoard(board);
    showBoard(board);
    spawnSnake(snake);
}

void collision(point snake[SNEKSIZE],char board[BOARDSIZE][BOARDSIZE],char *input){

    char cell = board[snake[0].X][snake[0].Y];


    switch (cell){

        case '*' :
            growSnake(snake);
            spawnTreat(board);
            board[snake[0].X][snake[0].Y] = ' ';
            if (measureSnake(snake) == 15){
                    levelup(board,snake);0
                    *input = 'd';
            }
            break;

        case '#' :
            gameOver(snake);
            break;

        case 'o' :
            gameOver(snake);
            break;

        }
}

int proposeNewGame(){

    char input = ' ';

    do{
        system("cls");
        printf("\n\n       YOU LOST! RESTART? (Y/N)");
        fflush(stdin);
        input = getch();

    }while ((input != 'y') && (input != 'n'));

    if (input == 'y') return 0;
    else return 1;

}


