//life_driver.c
//
//Life Driver program
//Roger Priebe 9/5/2018
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

//This file is a driver program for the life.c module.
//This program must work with your implementations life.h and life.c
//Do not change the function definitions for populateWorld, showWorld or
//iterateGeneration.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "life.h"


int main(int argc, char *argv[]) {
   //Store command line arguments in variables
   char fName[80];
   strcpy(fName, argv[1]);	//Store text file name in fName
   const int numGenerations = atoi(argv[2]);	//Store number of generations
    
   const int MAX_ROWS = 80; //we want the world to fit on one screen

   //array of strings that will hold the grid
   char *world[MAX_ROWS];
   int numRows;
   int numCols;

   populateWorld(fName, world, &numRows, &numCols); //Find the number of columns and rows. Convert grid to * and .

   showWorld(world, numRows, numCols);  //Print initial generation

   for (int iteration = 0; iteration < numGenerations; iteration++) {

     // code to clear screen goes here
     system("clear");

     iterateGeneration(world, numRows, numCols); //Apply rules to world for next generation

     showWorld(world, numRows, numCols); //Print generation
  }

   for(int i = 0; i < numRows; i++){
        free(world[i]);		//Free dynamically allocated memory for grid
  }

  return 0;
}

