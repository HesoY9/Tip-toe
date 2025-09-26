#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hdr.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
#elif defined(__APPLE__) && defined(__MACH__)
    #include <unistd.h>
#endif // Detect OS

uint8_t m; // board size m x m
uint8_t **board; // 2D array for the board
enum winState { WIN, DRAW, CONTINUE }; // game states
uint8_t the_number = 0; // default play mode 2 players
uint8_t human_count = 0; // number of human players

void drawBoard();
void resetBoard();
void addToBoard(char c, uint8_t x, uint8_t y);
bool isValidMove(uint8_t x, uint8_t y);
enum winState game_logic(char c, uint8_t x, uint8_t y);
bool rowCheck(char c);
bool columnCheck(char c);
bool diagonalCheck(char c);
// char bigChar(char d);
void gameplay();
void writeFile();

int main() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif defined(__linux__)
        system("clear");
    #elif defined(__APPLE__) && defined(__MACH__)
        system("clear");
    #endif // Detect OS
    
    printf("Welcome to Tip-toe!\n");
    do {// the_number to decide game mode
    printf("Choose game mode:\n1. Single Player\n2. Two Players\n3. 3 Players\n4. Exit\n");
    scanf("%hhd", &the_number);
    if (the_number == 4) {
        printf("Exiting the game.\n");
        return 0;
    }
    if (the_number < 1 || the_number > 4) {
        printf("Invalid choice. Try again.\n");
    }
  } while (the_number < 1 || the_number > 4);

   do { // human_count to decide number of human players
    printf("choose how many human players (1-3): ");
    scanf("%hhd", &human_count);
    if (human_count < 1 || human_count > 3) {
        printf("Invalid number of players. Try again.\n");
    }
    } while (human_count < 1 || human_count > 3);
    if( human_count == 1 && the_number == 1) the_number = 2;
    else if( human_count == 2 && the_number == 1) the_number = 2;
    else if( human_count == 3 ) the_number = 3;

    do { // board size 3 to 10
    printf("Enter N for an N x N board: ");
    scanf("%hhd", &m);
    if (m < 3 || m > 10) {
        printf("Invalid board size. Try again.\n");
    }
    } while (m < 3 || m > 10);

    board = (uint8_t **)malloc(m * sizeof(uint8_t *));
    if (!board) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (uint8_t i = 0; i < m; i++) 
    {
        board[i] = (uint8_t *)malloc(m * sizeof(uint8_t));
        if (!board[i]) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
    }// memory allocation 

    resetBoard();
    drawBoard();
    gameplay();
    for (uint8_t i = 0; i < m; i++) {
        free(board[i]);
    }
    free(board);
    return 0;
}

void gameplay(){
    uint8_t x, y;
    enum winState result;
    writeFile();
    do {
        
        while (1) {    // Player 1 turn uses 'X'
            printf("player 1\nEnter location x y");
            scanf("%hhd %hhd", &x, &y);
            if (isValidMove(x, y)) break;
            printf("Invalid move, try again.\n");
        }
        result = game_logic('X', x, y);
        if (result == WIN) { printf("Player 1 wins!\n"); writeFile(); return; }
        if (result == DRAW) { printf("It's a draw!\n"); writeFile(); return; }
        writeFile();

        if (human_count == 2){   // player 2 turn uses 'O'  
            while (1) {
            printf("player 2\nEnter location x y");
            scanf("%hhd %hhd", &x, &y);
            if (isValidMove(x, y)) break;
            printf("Invalid move, try again.\n");
        }
        result = game_logic('O', x, y);
        if (result == WIN) { printf("Player 2 wins!\n"); writeFile(); return; }
        if (result == DRAW) { printf("It's a draw!\n"); writeFile(); return; }
        writeFile();
        }

        if( human_count == 3){    // player 3 turn uses 'Z'
        while (1) {
            printf("player 3\nEnter location x y");
            scanf("%hhd %hhd", &x, &y);
            if (isValidMove(x, y)) break;
            printf("Invalid move, try again.\n");
        }
        result = game_logic('Z', x, y);
        if (result == WIN) { printf("Player 3 wins!\n"); writeFile(); return; }
        if (result == DRAW) { printf("It's a draw!\n"); writeFile(); return; }
        writeFile();
        }

        if( human_count == the_number) continue;
            // computer turn
        for(uint8_t i = human_count; i < the_number; i++) {
        while (1) {
            uint16_t bot = rand() % 10000;
            x = ((bot / 100) % m);
            y = ((bot % 100) % m);
            printf("Computer chooses: %d %d ", x, y); 
            if (isValidMove(x, y)) {
                printf("\n");
                #if defined(_WIN32) || defined(_WIN64)
                    Sleep(2000);
                #elif defined(__linux__)
                    sleep(2);
                #elif defined(__APPLE__) && defined(__MACH__)
                    sleep(2);
                #endif // Detect OS 
                 break;
                }
            printf("Invalid!\n");   
        }
        if(i == 1) {result = game_logic('O', x, y);}
        else if(i == 2) {result = game_logic('Z', x, y);}
        
        if (result == WIN) { printf("Computer wins!\n"); writeFile(); return; }
        if (result == DRAW) { printf("It's a draw!\n"); writeFile(); return; }
        writeFile();
        }
    } while (true);
}

bool rowCheck(char c){
    for (uint8_t i = 0; i < m; i++)
    {   bool win = true;
        for (uint8_t j = 0; j < m; j++)
        { if (board[i][j] != c) { win = false; }
        }
        if (win) { return true; }
    }
    return false;
} // check rows for a win
bool columnCheck(char c){
    for (uint8_t j = 0; j < m; j++)
    {   bool win = true;
        for (uint8_t i = 0; i < m; i++)
        { if (board[i][j] != c) { win = false; }
        }
        if (win) { return true; }
    }
    return false;
} // check columns for a win

bool diagonalCheck(char c){
    bool win = true;
    for (uint8_t i = 0; i < m; i++)
    { if (board[i][i] != c) { win = false; }
    }
    if (win) { return true; }
    win = true;
    for (uint8_t i = 0; i < m; i++)
    { if (board[i][m - i - 1] != c) { win = false; }
    }
    return win;
} // check diagonals for a win

/*  needs if user inputs the character 
char bigChar(char d){  
    if (d >= 'a' && d <= 'z')
    { // return uppercase
        return d + ('A' - 'a');}
    return d;
}    */

void drawBoard(){
     #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif defined(__linux__)
        system("clear");
    #elif defined(__APPLE__) && defined(__MACH__)
        system("clear");
    #endif // Detect OS to clear screen

     printf("   Current Board:\n  ");
    for ( uint8_t j = 0; j < m; j++ )
        { printf("  %d ", j); }
        printf("\n  ");
    for ( size_t i = 0; i < m; i++ )
    { printf("----"); }
    printf("-\n");

    for ( uint8_t i = 0; i < m; i++ )
    {   printf("%d ", i);
        for (uint8_t j = 0; j < m; j++)
        { printf("| %c ", board[i][j]); }
        printf("|\n  ");
        for (uint8_t k = 0; k < m; k++ )
        { printf("----"); }
        printf("-\n\n");
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
    board[x][y] = c;
} // add a character to the board

bool isValidMove(uint8_t x, uint8_t y){
    if (x >= m || y >= m) { return false; }
    if (board[x][y] != ' ') { return false; }
    return true;
} // check if the move is valid

enum winState game_logic(char c, uint8_t x, uint8_t y){
    addToBoard(c, x, y);
    drawBoard();
    if (rowCheck(c) || columnCheck(c) || diagonalCheck(c)) { return WIN; }

    for (uint8_t i = 0; i < m; i++)
    {   for (uint8_t j = 0; j < m; j++)
        {if (board[i][j] == ' ') { return CONTINUE; }
        }
    } // continue if there are empty space, otherwise draw
    return DRAW;
} // main game logic

void writeFile(){
    FILE *f = fopen("gamelog.txt", "a+");
    if (f == NULL)
    {   printf("Error opening file!\n");
        exit(1);
    }getTime();
    fprintf(f, "Game Log:%s\n", timestamp);
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
