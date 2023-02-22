// life.h
// -- EE 312 Project 2

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
 *///
// Created by priebe on 9/5/2018.
//

#ifndef UNTITLED1_LIFE_H
#define UNTITLED1_LIFE_H

#endif //UNTITLED1_LIFE_H

void populateWorld(char fname[], char *grid[], int *numRows, int *numCols);

void showWorld(char *grid[], int numRows, int numCols);

void iterateGeneration(char *grid[], int numRows, int numCols);

int calculateNeighbors(char *grid[], int x, int y, int numRows, int numCols);

char deadOrAlive(int neighbors, char home);
