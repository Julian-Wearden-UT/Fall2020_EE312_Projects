//driver.h
//

#ifndef STACK312LL_DRIVER_H
#define STACK312LL_DRIVER_H

#endif //STACK312LL_DRIVER_H


#include <stdio.h>
#include <stdbool.h>

typedef struct Pixel {
    int row;
    int col;
    char color;
} Pixel;

typedef Pixel StackEntry;

//Counts size of 2D array in text file (Finds number of rows and columns)
void countArraySize(char fname[], int *numRows, int *numCols);

//Transfers grid in text file to 2d array image
void transferFile(char fname[], char *image[], int *numRows, int *numCols);

//Creates array of Pixel structs from 2d array image
void createPixels(int *numRows, int *numCols, char *image[], StackEntry *pixelInfo[]);

//Accepts user input as an int and ensures user row and column are valid
void userInput(int *userRow, int *userCol, char *userChar, int *numRows, int *numCols);

//Main flood fill function. Defines necessary variables and calls recursive function
void floodFill(int *userRow, int *userCol, int *numCols, int *numRows, char *userChar, StackEntry *pixelInfo[]);

//Applies flood fill recursively, changing the necessary pixels
void floodFillRecursive(int currentRow, int currentColumn, int numCols, int numRows, char oldColor, char newColor, StackEntry *pixelInfo[]);

//Print image 2d array to screen
void showFill(char *image[], int *numRows, int *numCols);

//Transfer values from pixel array to image 2d array
void iterateFill(char *image[], StackEntry *pixelInfo[], int *numRows, int *numCols);