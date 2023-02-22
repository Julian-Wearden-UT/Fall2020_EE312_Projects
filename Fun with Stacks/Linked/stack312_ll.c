//stack312_ll.c
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
#include "stack312_ll.h"


//Initializes Stack
void makeStack(Stack312 *sp){
    sp->top = NULL;
}

//Creates new node for stack
StackNode* createNode(StackEntry pixelInfo){
    StackNode* stackNode = (StackNode*)malloc(sizeof(StackNode));
    stackNode->pixel = pixelInfo;
    stackNode->next = NULL;
    return stackNode;
}

//Always returns false since stack will never be full given constraints
bool isFull(Stack312 s){
    return false;
}

//Checks if stack is Empty
bool isEmpty(Stack312 s){
    if (s.top == NULL){
        return true;
    }
    else return false;
}

//Creates node from stack entry and pushes it to stack
void push(StackEntry e,Stack312 *sp){
    if (!isFull(*sp)){         //Make sure stack is not full
        StackNode *stackNode = createNode(e);
        stackNode->next = sp->top;
        sp->top = stackNode;
    }
}

//Pops stack entry node from stack
StackEntry pop(Stack312 *sp){
    StackNode* temp = sp->top;
    sp->top = temp->next;
    StackEntry popped = temp->pixel;
    free(temp);

    return popped;
}
