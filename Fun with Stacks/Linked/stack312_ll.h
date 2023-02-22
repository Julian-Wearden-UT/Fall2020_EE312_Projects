//stack312_ll.h
//Add documentation including Pre and Post conditions for functions

#include <stdio.h>
#include <stdbool.h>

typedef struct Pixel {
   int row;
   int col;
   char color;
} Pixel;

typedef Pixel StackEntry;

typedef struct StackNode {
   StackEntry pixel;
   struct StackNode *next;
} StackNode;
   
typedef struct Stack312 {
   struct StackNode *top;
} Stack312;

//Precondition: Passing a pointer to stack of type Stack312
//Postcondition: Top of stack points to null
void makeStack(Stack312 *sp);

//Precondition: Stack has been initialized
//Postcondition: Returns new node for Pixel
StackNode* createNode(Pixel pixelInfo);

//Precondition: Grid array is of size 25x25 = 625 (or insignificant enough to fill all of memory)
//Postcondition: Always returns false
bool isFull(Stack312 s);

//Precondition: Stack has been initialized
//Postcondition: Returns true if stack is empty
bool isEmpty(Stack312 s);

//Precondition: Stack is not full
//Postcondition: Pushes StackEntry to top of stack
void push(StackEntry e,Stack312 *sp);

//Precondition: Stack is not empty
//PostCondition: Returns Pixel (StackEntry) popped from stack
StackEntry pop(Stack312 *sp);

