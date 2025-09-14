#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
enum winState { WIN, DRAW, CONTINUE };
uint8_t m;

int main() {
    printf("Welcome to Tip-toe!\n");
    printf("Enter N for an N x N board: ");
    scanf("%d", &m);
    printf("Player 1 is X and Player 2 is O\n");

    uint8_t *board = (uint8_t *)malloc(m * m * sizeof(uint8_t));
    board[m][m];
    resetBoard();
    uint8_t x, y;
    do
    {
       printf("player 1\nEnter location x y");
       scanf("%d %d", &x, &y);
       enum winState result = game_logic();
    } while (condition);

    printf("player 1\nEnter location x y");
    scanf("%d %d", &x, &y) 
    enum winState result = game_logic();
    x=y=0;
    return 0;
}// copilot is a bad

void gameplay(){

}


bool rowCheck(char c){
    for (uint8_t i = 0; i < m; i++)
    {   bool win = true;
        for (uint8_t j = 0; j < m; j++)
        {if (board[i][j] != bigChar(c))
            { win = false; }
        }
        if (win)
        { return true; }
    }
    return false;
} // check rows for a win
bool columnCheck(char c){
    for (uint8_t j = 0; j < m; j++)
    {   bool win = true;
        for (uint8_t i = 0; i < m; i++)
        {if (board[i][j] != bigChar(c))
            { win = false; }
        }
        if (win)
        { return true; }
    }
    return false;
} // check columns for a win

bool diagonalCheck(char c){
    bool win = true;
    for (uint8_t i = 0; i < m; i++)
    {if (board[i][i] != bigChar(c))
        { win = false; }
    }
    if (win)
    { return true; }
    win = true;
    for (uint8_t i = 0; i < m; i++)
    {if (board[i][m - i - 1] != bigChar(c))
        { win = false; }
    }
    return win;
} // check diagonals for a win

char bigChar(char d){  
    if (d >= 'a' && d <= 'z')
    { // return uppercase
        return d + ('A' - 'a');}
    return d;
}

void drawBoard(){
     printf("   Current Board:\n  ");
    for (uint8_t j = 0; j < m; j++)
        { printf("  %d ", j);}
        printf("\n  ");
    for (size_t i = 0; i < m; i++)
    {printf("----");}
    printf("-\n");

    for (uint8_t i = 0; i < m; i++)
    {   printf("%d ", i);
        for (uint8_t j = 0; j < m; j++)
        {printf("| %c ", board[i][j]);}
        printf("|\n  ");
        for (uint8_t k = 0; k < m; k++)
        {printf("----");}
        printf("-\n");
        // draw the board
    }}

void resetBoard(){
    for (uint8_t i = 0; i < m; i++)
    {   for (uint8_t j = 0; j < m; j++)
        {board[i][j] = ' ';
        }
    }
} // reset the board to empty

void addToBoard(char c, uint8_t x, uint8_t y){
    board[x][y] = bigChar(c);
} // add a character to the board

bool isValidMove(uint8_t x, uint8_t y){
    if (x >= m || y >= m)
    { return false; }
    if (board[x][y] != ' ')
    { return false; }
    return true;
} // check if the move is valid

enum winState game_logic(char c, uint8_t x, uint8_t y){
    addToBoard(c, x, y);
    drawBoard();
    if (rowCheck(c) || columnCheck(c) || diagonalCheck(c))
    { return WIN; }
    for (uint8_t i = 0; i < m; i++)
    {   for (uint8_t j = 0; j < m; j++)
        {if (board[i][j] == ' ')
            { return CONTINUE; }
        }
    }
    return DRAW;
} // main game logic

void writeFile(){
    FILE *f = fopen("gamelog.txt", "a+");
    if (f == NULL)
    {   printf("Error opening file!\n");
        exit(1);
    }getTime()
    fprintf(f, "Game Log:%s\n", time);
    for (uint8_t i = 0; i < m; i++)
    {   for (uint8_t j = 0; j < m; j++)
        {fprintf(f, "| %c ", board[i][j]);}
        fprintf(f, "|\n");
        for (uint8_t k = 0; k < m; k++)
        {fprintf(f, "----");}
        fprintf(f, "-\n");
    }
    fclose(f);
} // write the game log to a file

char time[26];
void getTime(){
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", t);
} // get the current time