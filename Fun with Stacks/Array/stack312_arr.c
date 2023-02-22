//stack312_arr.c
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
#include <stdlib.h>
#include "stack312_arr.h"

//Initializes Stack with pointer to -1
void makeStack(Stack312 *sp){
    sp->top = -1;
}

//Returns true if stack pointer is greater than maximum number of elements constraint
bool isFull(Stack312 s){
    if(s.top == MAX_ELEMENTS-1){
        return true;
    }
    else{
        return false;
    }
}

//Checks if pointer of stack is -1 and therefore empty
bool isEmpty(Stack312 s){
    if (s.top == -1){
        return true;
    }
    else{
        return false;
    }
}

//Pushes new value to array stack
void push(StackEntry e, Stack312 *sp){
    (sp->top)++;
    sp->elements[sp->top]=e;
}

//Pops top value in stack
StackEntry pop(Stack312 *sp){
    StackEntry popped = sp->elements[sp->top];
    (sp->top)--;
    return popped;
}
