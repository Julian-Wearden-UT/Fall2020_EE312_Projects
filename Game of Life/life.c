//life.c
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

int calculateNeighbors(char *grid[], int x, int y, int numRows, int numCols);
char deadOrAlive(int neighbors, char home);

void populateWorld(char fname[], char *grid[], int *numRows, int *numCols){
    FILE* fp;
    char currentCharacter;
    char previousCharacter;
    *numRows = 1;		//Initialize to 1 since first row doesn't have \n
    *numCols = 0;

    // Get very first character in file for use in loop
    fp = fopen(fname, "r"); 
    previousCharacter = fgetc(fp);
    fclose(fp);
    
    // Caluculate number of rows and columns
    fp = fopen(fname, "r");
    while(1){
        currentCharacter = fgetc(fp);
        if(currentCharacter == EOF){	// Exit loop once it reaches end of file
            break;
        }
        if(previousCharacter == '\n' && (currentCharacter == '1' || currentCharacter == '0')){
            (*numRows)++;		//Add to numRows when newline is not empty
        }
        else if ((currentCharacter != '\n') && (currentCharacter != '\r') && (*numRows == 1)){
            (*numCols)++;		//Add to numCols when end of line is reached
        }

        previousCharacter = currentCharacter; //Store currentCharacter in previousCharacter to check for empty lines next loop
    }
    fclose(fp);
   

    //Dynamically Allocate Memory for grid 
    for(int i = 0; i < *numRows; i++){
        grid[i] = (char*)malloc((*numCols+1) * sizeof(char));
	memset(grid[i], 0, ((*numCols+1)*sizeof(char)));
    }

    
    fp = fopen(fname, "r");	//Reopen file to start fgetc from beginning
    
    //Convert all 1's to *'s and all 0's to .'s and store back into grid
    for (int i = 0; i < *numRows; i++){
        for(int j = 0; j <= *numCols; j++) {
            currentCharacter = fgetc(fp);
            if (currentCharacter == '1'){
                currentCharacter = '*';
            }
            else if (currentCharacter == '0'){
                currentCharacter = '.';
            }
            grid[i][j] = currentCharacter;
        }
    }

    fclose(fp);
}

void showWorld(char *grid[], int numRows, int numCols){
    //Print current status of grid character by character
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            char val = grid[i][j];
            printf ("%c", val);
        }
        printf("\n");
    }
}

void iterateGeneration(char *grid[], int numRows, int numCols){
    //Calculate what the next generation will look like
    char tempGrid[numRows][numCols]; //Create temporary grid to store next value of each character
    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols; j++){
            char home = grid[i][j];	//Store current value of grid in home
            int neighbors = calculateNeighbors(grid, j, i, numRows, numCols);	//Figure out number of neighbors for character
            char newStatus = deadOrAlive(neighbors, home); //Figure out what a character's status will be for the next generation
            tempGrid[i][j] = newStatus; //Store character's status for next generation in the temporary grid
        }
    }
    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols; j++){
            grid[i][j] = tempGrid[i][j]; //Copy all new characters from temporary grid into grid
        }
    }
}

char deadOrAlive(int neighbors, char home){
    //Used to figure out new status of character (Returns either * or .)
    char newStatus;
    if ( (neighbors == 0 || neighbors == 1) && (home == '*') ){		//Cell dies of loneliness (0-1 neighbors)
        newStatus = '.';
    }
    else if ( (neighbors == 2 || neighbors == 3) && (home == '*') ){	//Live cell lives unchanged to next generation (2-3 neighbors)
        newStatus = '*';
    }
    else if ( (neighbors == 3) && (home == '.') ){			//Cell is born (3 neighbors)
        newStatus = '*';
    }
    else if ( (neighbors >= 4) && (home == '*')){			//Cell dies of overcrowding (4+ neighbors)
        newStatus = '.';
    }
    else {
        newStatus = home;						//Otherwise, keep status
    }

    return newStatus;
}

int calculateNeighbors(char *grid[], int x, int y, int numRows, int numCols){
    //Returns number of live neighbors for a character
    int count = 0; //Number of neighbors
    for (int columnId = x-1; columnId <= (x+1); columnId++){	//For loops check all values surrounding a character
        for (int rowId = y-1; rowId <= (y+1); rowId++){
            if((!(columnId == x && rowId == y)) && (!( (columnId < 0 || columnId >= numCols) || (rowId < 0 || rowId >= numRows) )) ){	//Make sure cell being looked at isn't outside grid or isn't the current character
                char c = grid[rowId][columnId];
                    if (c == '*'){	//Only add 1 to neighbors if neighbor cell is alive
                        count++;
                    }
            }
        }
    }
    return count;
}
