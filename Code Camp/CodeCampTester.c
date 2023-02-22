#include<stdio.h>
#include<stdbool.h>


// CodeCampTester.c -- EE 312 Project 1 -- Tester class

/* Student information for assignment:
 * 
 * Name: Julian Wearden
 * email address: juliwramos@gmail.com
 * UTEID: jfw864
 * Section 5 digit ID: 16020
 *  
 */

//function prototypes. These will be completed in CodeCamp.c
int hammingDistance(int aList[], int bList[], int len);
int sum3or5Multiples();
bool lastDigit(int num1, int num2);
int reverseInt(int num); 
//****************************

int main() {
  
  // Julian's test 1, hammingDistance
  int h1[] = {5, 6, 7, 8, 9, 10, 0, 0};
  int h2[] = {-5, -6, -7, -8, -9, -10, 0, 1};
  int expected = 7;
  int actual = hammingDistance(h1, h2, 8);
  printf("Julian's Test 1 hamming distance: expected value: %d, actual value: %d\n", expected, actual);

  if(expected == actual)  
     printf("passed Julian's test 1, hamming distance\n\n");
  else 
     printf("**** FAILED **** Julian's test 1, hamming distance\n\n");

  // Julian's test 2, hamming distance
  int h3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  int h4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  expected = 0;
  actual = hammingDistance(h3, h4, 20);
  printf("Julian's Test 2 hamming distance: expected value: %d, actual value: %d\n", expected, actual);

  if(expected == actual)  
     printf("passed Julian's test 2, hamming distance\n\n");
  else 
     printf("**** FAILED **** Julian's test 2, hamming distance\n\n");

  // Julian's test 3, hamming distance
  int h5[50000] = {0, 1, -1, 2000000000, -2000000000};
  int h6[50000] = {0, 2000000000, -1, 2000000000, -2000000000};
  expected = 1;
  actual = hammingDistance(h5, h6, 5);
  printf("Julian's Test 3 hamming distance: expected value: %d, actual value: %d\n", expected, actual);

  if(expected == actual)  
     printf("passed Julian's test 3, hamming distance\n\n");
  else 
     printf("**** FAILED **** Julian's test 3, hamming distance\n\n");

  // Julian's test 4, last digit
  int n1 = -2609856;
  int n2 = 6;
  expected = true;
  actual = lastDigit(n1, n2);
  printf("Julian's Test 4 last digit: expected value: %d, actual value: %d\n", expected, actual);

  if(expected == actual)  
     printf("passed Julian's test 4, last digit\n\n");
  else 
     printf("**** FAILED **** Julian's test 4, last digit\n\n");

  // Julian's test 5, last digit
  n1 = 0;
  n2 = 0;
  expected = true;
  actual = lastDigit(n1, n2);
  printf("Julian's Test 5 last digit: expected value: %d, actual value: %d\n", expected, actual);

  if(expected == actual)  
    printf("passed Julian's test 5, last digit\n\n");
  else 
     printf("**** FAILED **** Julian's test 5, last digit\n\n");

  // Julian's test 6, last digit
  n1 = -111;
  n2 = 112;
  expected = false;
  actual = lastDigit(n1, n2);
  printf("Julian's Test 6 last digit: expected value: %d, actual value: %d\n", expected, actual);

  if(expected == actual)   
    printf("passed Julian's test 6, last digit\n\n");
  else 
     printf("**** FAILED **** Julian's test 6, last digit\n\n");

  // test 7, sum of multiples of 3 or 5
  expected = 233168;
  actual = sum3or5Multiples();
  printf("Test 7 sum of multiples: expected value: %d, actual value: %d\n", expected, actual);

  if(expected == actual)  
     printf("passed test 7, sum of multiples of 3 or 5\n\n");
  else 
     printf("**** FAILED **** test 7, sum of multiples of 3 or 5\n\n");

  // Julian's test 8, reverse int
  n1 = -48300097;
  expected = -79000384;
  actual = reverseInt(n1);
  printf("Julian's Test 8 reverse int: expected value: %d, actual value: %d\n", expected, actual);

  if(expected == actual)  
     printf("passed Julian's test 8, reverse int\n\n");
  else 
     printf("**** FAILED **** Julian's test 8, reverse int\n\n");

  // Julian's test 9, reverse int
  n1 = 8000;
  expected = 8;
  actual = reverseInt(n1); 
  printf("Julian's Test 9 reverse int: expected value: %d, actual value: %d\n", expected, actual);

  if(expected == actual)  
     printf("passed Julian's test 9, reverse int\n\n");
  else 
     printf("**** FAILED **** Julian's test 9, reverse int\n\n");

  // test 10, reverse int
  n1 = 2000000009;
  expected = 0;
  actual = reverseInt(n1); 
  printf("Julian's Test 10 reverse int: expected value: %d, actual value: %d\n", expected, actual);

  if(expected == actual)  
     printf("passed Julian's test 10, reverse int\n");
  else 
     printf("**** FAILED **** Julian's test 10, reverse int\n");

}


