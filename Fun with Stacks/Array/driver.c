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
#include <string.h>
#include "stack312_arr.h"

//Function declarations (Note to grader: If it matters, I put these here instead of a separate .h file because of the "Turn In" instructions on canvas)
char getNextEquation(FILE *fp, Stack312 *theStackint, char currentCharacter);
char checkMissing(char openingCharacter, char currentCharacter);
char missingEmpty(char currentCharacter);
char missingClose(Stack312 *theStack);

int main(int argc, char* argv[]){
    char fName[80];
    strcpy(fName, argv[1]);          //Copy filename entered through command line to variable fName
    FILE *fp;                        //Pointer to file
    fp = fopen(fName, "r");    //Opens file as readable
    int checkEOF = 1;                //Flag to check for end of file

    Stack312 theStack;
    makeStack(&theStack);           //Initialize/Make the Stack
    char missingVal = '\0';         //Will store missing char, if any
    StackEntry currentCharacter;    //Stores character being read from file

    while(checkEOF == 1) {
        currentCharacter = fgetc(fp);   //Extracts first character from file
        while(currentCharacter != '\n' && currentCharacter != '\r' && currentCharacter != EOF){
            printf("%c", currentCharacter); //Print equation character by character
            if (missingVal != '(' && missingVal != ')' && missingVal != '<' && missingVal != '>' && missingVal != '[' && missingVal != ']') {   //Run only if we haven't already found an invalid expression
                missingVal = getNextEquation(fp, &theStack, currentCharacter);      //Returns missing character
            }
            currentCharacter = fgetc(fp);       //Get next character from file
            if(currentCharacter == EOF){        //If we've reached end of file, switch flag to kill while loop
                checkEOF = 0;
            }
        }

        //Check if any leftover values in stack require closing "], ), or >"
        if (!isEmpty(theStack) && missingVal == '\0') {
            missingVal = missingClose(&theStack);
        }

        //If no errors found
        if (missingVal == '\0'){
            printf(" === valid expression\n");
        }
        //If equation is missing a character
        else{
            printf(" === missing %c\n", missingVal);
        }


        //Clear stack for next equation
        while(!isEmpty(theStack)){
            pop(&theStack);
        }
        missingVal = '\0';  //Reset missingVal to null for next loop
    }
    fclose(fp);     //Close the file
}

char getNextEquation(FILE *fp, Stack312 *theStack, char currentCharacter) {
    char missing;   //Stores missing character
    if (currentCharacter == '(' || currentCharacter == '<' || currentCharacter == '[') {    //Push all "opening" characters to stack
        push(currentCharacter, theStack);
        return '\0';
    }
    else if (currentCharacter == ')' || currentCharacter == '>' || currentCharacter == ']') {    //Compare "closing" character to stack to see if there is a match
        if (!isEmpty(*theStack)) {                     //Compare top of stack to closing
            StackEntry openingCharacter;
            openingCharacter = pop(theStack);
            missing = checkMissing(openingCharacter, currentCharacter);
            return missing;
        } else {                                        //If stack is empty and we are missing an opening
            missing = missingEmpty(currentCharacter);
            return missing;
        }
    }
    return '\0';
}

//Takes top character from stack and current character being checked and returns the missing character, if they don't match
char checkMissing(char openingCharacter, char currentCharacter){
    if (openingCharacter !='(' && currentCharacter == ')'){
        return '(';
    }
    else if (openingCharacter !='<' && currentCharacter == '>'){
        return '<';
    }
    else if (openingCharacter !='[' && currentCharacter == ']'){
        return '[';
    }
    else {
        return '\0';    //Return null if it is valid
    }
}

//Only ran when stack is empty
//Given a loose closing character, return it's equivalent opening character
char missingEmpty(char currentCharacter){
    if (currentCharacter == ')'){
        return '(';
    }
    else if (currentCharacter == '>'){
        return '<';
    }
    else if (currentCharacter == ']'){
        return '[';
    }
    else {
        return '\0';
    }
}

//If leftover opening characters in stack, return it's equivalent closing character
char missingClose(Stack312 *theStack){
    char currentCharacter;
    if(!isEmpty(*theStack)){
        currentCharacter = pop(theStack);
        if (currentCharacter == '('){
            return ')';
        }
        if (currentCharacter == '<'){
            return '>';
        }
        if (currentCharacter == '['){
            return ']';
        }
	else {return '\0';}
    }
    else{
        return '\0';
    }
}








