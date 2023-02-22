/* mathStuff.c

Programmer: 
 * EE312  10/14/2020
 * On my honor, Julian Wearden, this programming project is my own work
 * and I have not provided this code to any other student.
 *
 * Name: Julian Wearden
 * email address: juliwramos@gmail.com
 * UTEID: jfw864
 * Section 5 digit ID: 16020
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//**********  Function Prototypes  ******************

//function isPrime
//input parameter - positive integer
//returns true if the number is prime, otherwise false
//

bool isPrime (int number);

//function isPrimeHelper
//input parameter - positive integer greater that 2. Counter starting at 2
//returns true if the number is prime, otherwise false
bool isPrimeHelper (int number, int count);


//function printPrimes
//input parameter - positive integer
//Uses the isPrime method to print a list of prime numbers between 1 and n. 

void printPrimes (int n);


//function findFibo
//input parameter - positive integer
//returns the nth fibonacci number where
//Fib(0) -> 0 
//Fib(1) -> 1 
//Fib(N) -> Fib(N-2) + Fib(N-1)

int findFibo (int n);


//function findFactors
//input parameter - positive integer
//prints the prime factors of the given number to standard output (cout)
//example output: 52=2*2*13 (or 52=1*2*2*13) or 13=prime

void findFactors (int number);

//function findFactorsHelper
//input parameter - positive, non-prime integer greater than 1. Divisor starting at 2
//prints the prime factors of the given number to standard output when number is not prime
void findFactorsHelper(int number, int divisor);


//******************  MAIN  *****************************

int main () {
    
    
    int testNum;
    
    //test for the isPrime function
    printf("Enter a test number - ");
    scanf("%d",&testNum);

    if (isPrime(testNum))
       printf("%d is prime\n",testNum);
    else
       printf("%d is not prime.\n", testNum);

     printf("\n");

    //test for printing primes
    printf("Enter n to print the prime numbers between 1 and n: ");
    scanf("%d",&testNum);

    printPrimes(testNum);

    printf("\n");
    printf("\n");

    //test for Fibonacci number finder
    printf("Which Fibonacci number? ");
    scanf("%d",&testNum);

    printf("The %d Fibonacci number is : %d", testNum, findFibo(testNum));

    printf("\n");
    printf("\n");

    //test for prime factors
    printf("Factor what number? ");
    scanf("%d",&testNum);

    findFactors(testNum);

    printf("\n");
    
    return 0;
}




//function isPrime
//input parameter - positive integer
//returns true if the number is prime, otherwise false
//

bool isPrime (int number) {
   const int START_DIVISOR = 2; //HINT: You may want a helper function

   //YOUR CODE GOES HERE
   //Edge cases 2 is prime, and 1 is not prime
   if (number <= START_DIVISOR){
       if (number == 2){
           return true;
       }
       else if (number == 1 || number == 0){
           return false;
       }
   }
   //Call recursive function to find if number is prime
   return isPrimeHelper(number, START_DIVISOR);

}

//function isPrimeHelper
//input parameter - positive integer greater that 2. Counter starting at 2
//returns true if the number is prime, otherwise false
bool isPrimeHelper(int number, int count){
    //Found value number is divisible by with no remainder
    if (number % count == 0){
        return false;
    }
    //No numbers were found
    else if (count * count > number){
        return true;
    }
    //Check next value against number
    return isPrimeHelper(number, count + 1);
}


//function printPrimes
//input parameter - positive integer
//Uses the isPrime method to print a list of prime numbers between 1 and n. 

void printPrimes (int n) {
   //YOUR CODE GOES HERE
   //Edge case if n is 1, return nothing
   if (n == 1){
   }
   //Prime number between 1 and n found
   else if(isPrime(n) == true) {
       printPrimes(n-1);
       printf("%d ", n);
   }
   //Number is not prime
   else{
       printPrimes(n-1);
   }
} 


//function findFibo
//input parameter - positive integer
//returns the nth fibonacci number where
//Fib(0) -> 0 
//Fib(1) -> 1 
//Fib(N) -> Fib(N-2) + Fib(N-1)

int findFibo (int n) {
    
   //YOUR CODE GOES HERE
   // Fib(0) -> 0 and Fib(1)->1 Cases
   if(n <= 1){
       return n;
   }
   //For values greater than 1 find fibonacci
   return (findFibo(n-1) + findFibo(n-2));
}


//function findFactors
//input parameter - positive integer
//prints the prime factors of the given number to standard output (cout)
//example output: 52=2*2*13 (or 52=1*2*2*13) or 13=prime

void findFactors (int number) {
    const int START_DIVISOR = 2; //HINT: You may want a helper function
   //YOUR CODE GOES HERE
   //Edge case if number is 1 return nothing
   if (number == 1){
    }
   //If number itself is prime
   else if (isPrime(number)){
       printf("%d=", number);
       printf("prime");
    }
   //Finds prime factors
   else {
       printf("%d=", number);
       findFactorsHelper(number, START_DIVISOR);
    }


}

//function findFactorsHelper
//input parameter - positive, non-prime integer greater than 1. Divisor starting at 2
//prints the prime factors of the given number to standard output when number is not prime
void findFactorsHelper(int number, int divisor){
    //Last prime number
    if (number < divisor * divisor){
        printf("%d", number);
    }
    //A prime factor is found
    else if (isPrime(divisor) && (number % divisor == 0)){
        printf("%d*", divisor);
        findFactorsHelper(number/divisor, divisor);
    }
    //Prime factor not found, check next value
    else{
        findFactorsHelper(number, divisor + 1);
    }

}
    
