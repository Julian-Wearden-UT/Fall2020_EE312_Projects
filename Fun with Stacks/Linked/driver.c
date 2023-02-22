//driver.c
//
//EE 312


/* Student information for project:
 *
 * Replace <NAME> with your name.
 *
 * On my honor, Julian Wearden, this programming project is my own work
 * and I have not provided this code to any other student.
 *
 * Name: Julian Wearden
 * email address: juliwramos@gmail.com
 * UTEID: jfw864
 * Section 5 digit ID: 16020
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack312_ll.h"

//Function declarations
void countArraySize(char fname[], int *numRows, int *numCols);
void transferFile(char fname[], char *image[], int *numRows, int *numCols);
void createPixels(int *numRows, int *numCols, char *image[], StackEntry *pixelInfo[]);
void userInput(int *userRow, int *userCol, char *userChar, int *numRows, int *numCols);
void floodFill(int *userRow, int *userCol, int *numCols, int *numRows, char *userChar, StackEntry *pixelInfo[], Stack312 *theStack);
bool neighborEast(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows);
bool neighborWest(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows);
bool neighborNorth(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows);
bool neighborSouth(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows);
bool neighborNorthEast(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows);
bool neighborSouthEast(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows);
bool neighborSouthWest(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows);
bool neighborNorthWest(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows);
void showFill(char *image[], int *numRows, int *numCols);
void iterateFill(char *image[], StackEntry *pixelInfo[], int *numRows, int *numCols);


int main (int argc, char* argv[]){
    char fName[80];
    strcpy(fName, argv[1]);	//Copy filename entered through command line to variable fName
    const int MAX_ROWS = 26;	//We will only ever have 25 rows max. 1 more for good measure.

    char *image[MAX_ROWS];	//Pointer to image 2D array
    int numRows;		//Will hold number of rows
    int numCols;		//Will hold number of columns
    countArraySize(fName, &numRows, &numCols);		//Counts size of the array in text file
    transferFile(fName, image, &numRows, &numCols);	//Transfers characters in text file to 2D array image
    showFill(image, &numRows, &numCols);		//Prints initial image to screen

    StackEntry *pixelInfo[numRows];			//Array of pixels that holds row, col, color of each pixel
    int userRow;					//Will hold row inputted by user
    int userCol;					//Will hold column inputted by user
    char userChar;					//Will hold color inputted by user
    while(1){
        userInput(&userRow, &userCol, &userChar, &numRows, &numCols);	//Get input values from user
        if ( (userRow == -1) || (userCol == -1) ){			//If user inputs -1 for row or column end program
            break;
        }
        else{
            createPixels(&numRows, &numCols, image, pixelInfo);		//Store values in image 2D array to array of pixels
            Stack312 theStack;
            makeStack(&theStack);					//Initialize the stack
            floodFill(&userRow, &userCol, &numCols, &numRows, &userChar, pixelInfo, &theStack);		//Find and change pixels affected by flood fill 
            iterateFill(image, pixelInfo, &numRows, &numCols);		//Store char value from array of pixels to image 2D array
            showFill(image, &numRows, &numCols);			//Print newest iteration of image to screen
	    for(int i =numRows; i >=  0; --i){
        	free(pixelInfo[i]);
            }
        }
    }

    //Free up dynamically allocated memory for image 2D array
    for (int i = numRows; i >= 0; --i){
        free(image[i]);
    }
}



void countArraySize(char fname[], int *numRows, int *numCols){		//Counts size of 2D array in text file (Finds number of rows and columns)
    FILE* fp;			//Pointer to file
    char currentCharacter;  //Stores current character
    *numRows = 1;		//Number of rows starts at one since loop looks for \n
    *numCols = 0;
    fp = fopen(fname, "r");
    //Assumes text file does not end with empty line
    while(1){
        currentCharacter = fgetc(fp);
        if(currentCharacter == EOF){
            break;
        }
        if(currentCharacter == '\n'){
            (*numRows)++;
        }
        else if ((currentCharacter != '\n') && (currentCharacter != '\r') && (*numRows == 1)){
            (*numCols)++;
        }
    }
    fclose(fp);
}

void transferFile(char fname[], char *image[], int *numRows, int *numCols) {    //Transfers grid in text file to 2d array image

    for (int i = 0; i <= *numRows; ++i) {           //Dynamically allocate memory for 2d array
        image[i] = (char*)malloc((*numCols+1) * sizeof(char));
	memset(image[i], 0, ( (*numCols+1)*sizeof(char)));
    }
    FILE *fp;
    fp = fopen(fname, "r");

    char nextCharacter;
    char currentCharacter;
    int checkEOF;
    nextCharacter = fgetc(fp);
    for (int i = 0; i < *numRows; i++){         //For loops iterate through each character in file and put them in image array
        for(int j = 0; j <= *numCols; j++) {
            currentCharacter = nextCharacter;
            image[i][j] = currentCharacter;
            checkEOF = fgetc(fp);
            nextCharacter = checkEOF;
            if (checkEOF == EOF){break;}        //Ends when EOF is found
        }
        if (checkEOF == EOF){break;}
    }

    fclose(fp);
}

void userInput(int *userRow, int *userCol, char *userChar, int *numRows, int *numCols){
    int valid = 0;
    while(valid == 0){
        printf("Enter a row: ");
        scanf("%d", &(*userRow));       //Get row from user (assumes value entered is an int)
        if((-1 > *userRow) || (*userRow > (*numRows - 1))){     //Checks to make sure row entered is within bounds of 2d array
            printf("Input is invalid.\n");
            valid = 0;
        }
        else{
            valid = 1;
        }
    }

    valid = 0;
    while(valid == 0){
        printf("Enter a column: ");
        scanf("%d", &(*userCol));       //Get column from user (assumes value entered is an int)
        if((-1 > *userCol) || (*userCol > (*numCols - 1))){     //Checks to make sure column entered is within bounds of 2d array
            printf("Input is invalid.\n");
            valid = 0;
        }
        else{
            valid = 1;
        }
    }

    printf("Enter a color: ");
    scanf(" %c", &(*userChar));     //Assumes user enters a single, valid char
    printf("\n");
}

void createPixels(int *numRows, int *numCols, char *image[], StackEntry *pixelInfo[]){
    for(int i = 0; i <= *numRows; ++i){      //Dynamically allocate space for array of pixels
        pixelInfo[i] = (StackEntry*)malloc((*numCols+1) * sizeof(StackEntry));
	memset(pixelInfo[i], 0, ( (*numCols+1)*sizeof(StackEntry) ));
    }

    for (int i = 0; i < *numRows; i++){     //Transfer info from image 2d array to pixelInfo array
        for (int j = 0; j < *numCols; j++){
           pixelInfo[i][j].col = j;
           pixelInfo[i][j].row = i;
           pixelInfo[i][j].color = image[i][j];
        }
    }
}

void floodFill(int *userRow, int *userCol, int *numCols, int *numRows, char *userChar, StackEntry *pixelInfo[], Stack312 *theStack){\
    push(pixelInfo[*userRow][*userCol], theStack);      //Push initial pixel to stack
    char newColor;
    char oldColor;
    newColor = *userChar;
    oldColor = pixelInfo[*userRow][*userCol].color;     //Store character being filled
    pixelInfo[*userRow][*userCol].color = newColor;     //Change color of initial pixel to user color

    int currentRow;
    int currentColumn;
    StackEntry currentPixel;                            //Holds current pixel being checked
    if (oldColor != newColor){
        while (!isEmpty(*theStack)) {                   //Do until stack is empty
            currentPixel = pop(theStack);               //Pop pixel to be checked from stack
            currentRow = currentPixel.row;              //Retrieve info from popped pixel
            currentColumn = currentPixel.col;
            push(pixelInfo[currentRow][currentColumn], theStack);   //Push pixel back to stack for use later

            //Check all the neighbors of the current pixel
            //If a pixel of the same type is found, change it to user entered color and push it to stack for use later
            if (neighborEast(currentRow, currentColumn, oldColor, pixelInfo, *numCols, *numRows)) {
                pixelInfo[currentRow][currentColumn + 1].color = newColor;
                push(pixelInfo[currentRow][currentColumn + 1], theStack);
            } else if (neighborWest(currentRow, currentColumn, oldColor, pixelInfo, *numCols, *numRows)) {
                pixelInfo[currentRow][currentColumn - 1].color = newColor;
                push(pixelInfo[currentRow][currentColumn - 1], theStack);
            } else if (neighborNorth(currentRow, currentColumn, oldColor, pixelInfo, *numCols, *numRows)) {
                pixelInfo[currentRow - 1][currentColumn].color = newColor;
                push(pixelInfo[currentRow - 1][currentColumn], theStack);
            } else if (neighborSouth(currentRow, currentColumn, oldColor, pixelInfo, *numCols, *numRows)) {
                pixelInfo[currentRow + 1][currentColumn].color = newColor;
                push(pixelInfo[currentRow + 1][currentColumn], theStack);
            } else if (neighborNorthEast(currentRow, currentColumn, oldColor, pixelInfo, *numCols, *numRows)) {
                pixelInfo[currentRow - 1][currentColumn + 1].color = newColor;
                push(pixelInfo[currentRow - 1][currentColumn + 1], theStack);
            } else if (neighborSouthEast(currentRow, currentColumn, oldColor, pixelInfo, *numCols, *numRows)) {
                pixelInfo[currentRow + 1][currentColumn + 1].color = newColor;
                push(pixelInfo[currentRow + 1][currentColumn + 1], theStack);
            } else if (neighborSouthWest(currentRow, currentColumn, oldColor, pixelInfo, *numCols, *numRows)) {
                pixelInfo[currentRow + 1][currentColumn - 1].color = newColor;
                push(pixelInfo[currentRow + 1][currentColumn - 1], theStack);
            } else if (neighborNorthWest(currentRow, currentColumn, oldColor, pixelInfo, *numCols, *numRows)) {
                pixelInfo[currentRow - 1][currentColumn - 1].color = newColor;
                push(pixelInfo[currentRow - 1][currentColumn - 1], theStack);
            } else {
                pop(theStack);  //If no neighbor is found, pop a new value from the stack
            }

        }
    }
}

//All neighbor functions below return true if a neighbor of the same color is found. False otherwise.
bool neighborEast(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows){
    if ( (currentColumn+1 < 0 || currentColumn+1 >= numCols) || (currentRow < 0 || currentRow >= numRows) ){        //Make sure neighbor being checked is in bounds of array
        return false;
    }
    else if (pixelInfo[currentRow][currentColumn+1].color == oldColor){
        return true;
    }
    else return false;
}
bool neighborWest(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows){
    if ( (currentColumn-1 < 0 || currentColumn-1 >= numCols) || (currentRow < 0 || currentRow >= numRows) ){
        return false;
    }
    else if (pixelInfo[currentRow][currentColumn-1].color == oldColor){
        return true;
    }
    else return false;
}
bool neighborNorth(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows){
    if ( (currentColumn < 0 || currentColumn >= numCols) || (currentRow-1 < 0 || currentRow-1 >= numRows) ){
        return false;
    }
    else if (pixelInfo[currentRow-1][currentColumn].color == oldColor){
        return true;
    }
    else return false;
}
bool neighborSouth(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows){
    if ( (currentColumn < 0 || currentColumn >= numCols) || (currentRow+1 < 0 || currentRow+1 >= numRows) ){
        return false;
    }
    else if (pixelInfo[currentRow+1][currentColumn].color == oldColor){
        return true;
    }
    else return false;
}
bool neighborNorthEast(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows){
    if ( (currentColumn+1 < 0 || currentColumn+1 >= numCols) || (currentRow-1 < 0 || currentRow-1 >= numRows) ){
        return false;
    }
    else if (pixelInfo[currentRow-1][currentColumn+1].color == oldColor){
        return true;
    }
    else return false;
}
bool neighborSouthEast(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows){
    if ( (currentColumn+1 < 0 || currentColumn+1 >= numCols) || (currentRow+1 < 0 || currentRow+1 >= numRows) ){
        return false;
    }
    else if (pixelInfo[currentRow+1][currentColumn+1].color == oldColor){
        return true;
    }
    else return false;
}
bool neighborSouthWest(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows){
    if ( (currentColumn-1 < 0 || currentColumn-1 >= numCols) || (currentRow+1 < 0 || currentRow+1 >= numRows) ){
        return false;
    }
    else if (pixelInfo[currentRow+1][currentColumn-1].color == oldColor){
        return true;
    }
    else return false;
}
bool neighborNorthWest(int currentRow, int currentColumn, char oldColor, StackEntry *pixelInfo[], int numCols, int numRows){
    if ( (currentColumn-1 < 0 || currentColumn-1 >= numCols) || (currentRow-1 < 0 || currentRow-1 >= numRows) ){
        return false;
    }
    else if (pixelInfo[currentRow-1][currentColumn-1].color == oldColor){
        return true;
    }
    else return false;
}

void iterateFill(char *image[], StackEntry *pixelInfo[], int *numRows, int *numCols){   //Transfer values from pixel array to image 2d array
    for (int i = 0; i < *numRows; i++){
        for (int j = 0; j < *numCols; j++){
            image[i][j] = pixelInfo[i][j].color;
        }
    }
}

void showFill(char *image[], int *numRows, int *numCols){   //Print image 2d array to screen
    for(int i = 0; i < *numRows; i++){
        for(int j = 0; j < *numCols; j++){
            char val = image[i][j];
            printf ("%c", val);
        }
        printf("\n");
    }
    printf("\n");
}





