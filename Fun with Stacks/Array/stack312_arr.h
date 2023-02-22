//stack_arr.h
//Add documentation including Pre and Post conditions for functions

#include <stdio.h>
#include <stdbool.h>

#define MAX_ELEMENTS 100

typedef char StackEntry;

typedef struct Stack312 {
    int top;
    StackEntry elements[MAX_ELEMENTS];
} Stack312;

//Precondition: Passing a pointer to stack of type Stack312
//Postcondition: Top of stack points to -1
void makeStack(Stack312 *sp);

//Precondition: Define maximum number of elements
//Postcondition: Returns true if pointer is greater than max elements
bool isFull(Stack312 s);

//Precondition: Stack has been initialized
//Postcondition: Returns true if stack is empty
bool isEmpty(Stack312 s);

//Precondition: Only pushes when stack is not full
//Postcondition: Pushes StackEntry to top of stack
void push(StackEntry e, Stack312 *sp);

//Precondition: Only pops when stack is not empty
//PostCondition: Returns char (StackEntry) popped from stack
StackEntry pop(Stack312 *sp);
