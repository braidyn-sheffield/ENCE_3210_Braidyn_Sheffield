/*
* A program that contains a function that computes
* twice the square of a given integer and computes 
* that for an array of integers from 0 to 511
*/

#define ELEMENTS_COUNT 512 // Macro for the size of the array

int results[ELEMENTS_COUNT]; // Initializing the empty array

int twiceTheSquare(int number) // Function that will compute twice the square of a given number
{
  number = 2 * (number * number);

  return number;
}

void setup() 
{
  Serial.begin(9600); // Initializing serial communication

  for(int i = 0; i< ELEMENTS_COUNT; i++) // For loop that will iterate over each element in the array
  {
    results[i] = twiceTheSquare(i); // Calling the function for each value of i and placing the result in the array

    Serial.print(i); // Printing the results to the console
    Serial.print(" : ");
    Serial.println(results[i]);
  }
}

void loop() 
{

}
 /*
 * This code does not work, because we either run out of memory on the board,
 * or run out of values for the range of values for every data type
 */