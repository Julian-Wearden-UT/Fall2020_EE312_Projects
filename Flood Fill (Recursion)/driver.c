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
#include "driver.h"


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
            floodFill(&userRow, &userCol, &numCols, &numRows, &userChar, pixelInfo);		//Find and change pixels affected by flood fill
            iterateFill(image, pixelInfo, &numRows, &numCols);		//Store char value from array of pixels to image 2D array
            showFill(image, &numRows, &numCols);			//Print newest iteration of image to screen
	    for(int i = numRows; i >=  0; --i){
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

void floodFill(int *userRow, int *userCol, int *numCols, int *numRows, char *userChar, StackEntry *pixelInfo[]){\
    //Store character being filled in appropriate variables
    char newColor;
    char oldColor;
    newColor = *userChar;
    oldColor = pixelInfo[*userRow][*userCol].color;
    int currentRow = pixelInfo[*userRow][*userCol].row;
    int currentColumn = pixelInfo[*userRow][*userCol].col;

    // Do flood fill
    floodFillRecursive(currentRow, currentColumn, *numCols, *numRows, oldColor, newColor, pixelInfo);
}

void floodFillRecursive(int currentRow, int currentColumn, int numCols, int numRows, char oldColor, char newColor, StackEntry *pixelInfo[]){
    // Base cases
    //If currentRow or currentColumn being checked are out of bounds
    if ( (currentColumn < 0 || currentColumn >= numCols) || (currentRow < 0 || currentRow >= numRows) ){
        return;
    }
    //If pixel isn't color that's being filled
    if (pixelInfo[currentRow][currentColumn].color != oldColor){
        return;
    }
    //If pixel has already been filled
    if (pixelInfo[currentRow][currentColumn].color == newColor){
        return;
    }

    //General case
    //Assign pixel with user color
    pixelInfo[currentRow][currentColumn].color = newColor;

    //Recurse through next pixel
    //North
    floodFillRecursive(currentRow -1, currentColumn, numCols, numRows, oldColor, newColor, pixelInfo);
    //East
    floodFillRecursive(currentRow, currentColumn + 1, numCols, numRows, oldColor, newColor, pixelInfo);
    //South
    floodFillRecursive(currentRow + 1, currentColumn, numCols, numRows, oldColor, newColor, pixelInfo);
    //West
    floodFillRecursive(currentRow, currentColumn - 1, numCols, numRows, oldColor, newColor, pixelInfo);
    //NorthEast
    floodFillRecursive(currentRow - 1 , currentColumn + 1, numCols, numRows, oldColor, newColor, pixelInfo);
    //SouthEast
    floodFillRecursive(currentRow + 1, currentColumn + 1, numCols, numRows, oldColor, newColor, pixelInfo);
    //SouthWest
    floodFillRecursive(currentRow + 1, currentColumn - 1, numCols, numRows, oldColor, newColor, pixelInfo);
    //NorthWest
    floodFillRecursive(currentRow - 1, currentColumn - 1, numCols, numRows, oldColor, newColor, pixelInfo);

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





