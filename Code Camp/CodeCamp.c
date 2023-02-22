#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

// CodeCamp.c -- EE 312 Project 1

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



/* Determine the hamming distance between two int arrays.
   pre: aList != null, bList != null, aList.length == bList.length == len
   post: return hamming distance between the two arrays of ints.
   Neither parameter should be altered by this function.
*/

int hammingDistance(int aList[], int bList[], int len) {
    // EE 312 Students: put your code here
    int hamDistance = 0;
    for(int i = 0; i < len; i++){
        if(aList[i] != bList[i]){     //Compare i-th item in lists to see if they math
            hamDistance++;            //If they don't match, add 1 to hamDistance
        }
    }
    return hamDistance;
}

/* Determine if two ints have the same last digit.
   Note that the last digit of 0 is 0 and the last digit of -12 is 2.
   post: return true if num1 and num2 have the same last digit, false otherwise.
*/

bool lastDigit(int num1, int num2) {
    // EE 312 Students: put your code here
    if((abs(num1) % 10) == (abs(num2) % 10)){   //Take absolute value to factor for negative numbers. Modulous 10 to get digit in 10ths place.
        return true;                            //If equal return true
    }
    else{
        return false;                           //If not equal return false
    }
}

/* Determine the sum of the positive integers less than 1000 that are multiples of 3 or 5 (or both).
   post: return the sum of the integers from 1 to 1000 that are multiples of 3 or 5 or both.
*/

int sum3or5Multiples() {
    // EE 312 Students: put your code here
    int sumOfIntegers;
    for(int i = 0; i < 1000; i++){          //Iterate through numbers 0-1000
        if((i % 3) == 0 || (i % 5) == 0){   //Check if i-th number is a multiple of 3 or 5
            sumOfIntegers += i;             //Add i-th number to total sum if it is a multiple of 3 or 5
        }
    }
    return sumOfIntegers;
}

/* Reverse the digits of an integer. Return the reversed number if it is in the range of type int, 0 otherwise.
   post: return num with digits reversed if the reverse can be stored as an int, 0 otherwise.
*/

int reverseInt(int num) {
    // EE 312 Students: put your code here
    int reverse;
    int storedReverse;

    while (num != 0) {
        storedReverse = reverse;                            //Store current reverse for use in Equation 2 to check for overflow.
        reverse = (reverse * 10) + (num % 10);              //Equation 1. Move the right most bit one place to the left to prevent overriding. Take right most bit of num and insert to reverse.

        if((reverse - (num % 10))/10 != storedReverse){     //Equation 2. Check for overflow. Rewrite Equation 1 to make sure it is all still equal and ensure no overflow occured.
            return 0;                                       //If overflow occured, return 0
        }

        num = num / 10;                                     //Get rid of left most bit in num since it has already been accounted for in reverse
    }
    return reverse;
}
