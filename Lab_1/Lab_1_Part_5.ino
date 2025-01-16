/*
* A program that iterates over a given array and 
* detects whether a pattern has occured. If it has
* occured, the green LED turns on for a short period
* of time. If the program reaches the end of the array
* and there has been no occurences of the pattern,
* then the red LED turns on. The number of occurences
* of the pattern is tracked and printed to the console
* at the end of the program.
*/

// Initializing the Macros for the LED's and the size of the array
#define GREENLED 4
#define REDLED 5
#define ELEMENTS_COUNT 12

// Initializing the array to be checked, the pattern array, and the 
// variable for the number of occurences
int gEntries[ELEMENTS_COUNT] = {1, 2, 3, 4, 1, 2, 3, 5, 6, 1, 3, 3};
int gPattern[] = {1, 2, 3};
int gNumberOfOccurences = 0;

void setup() 
{
  // Setting LED pins to an output
  pinMode(GREENLED, OUTPUT);
  pinMode(REDLED, OUTPUT);
  
  // Initializing serial communication and the variable to track where
  // in the pattern we currently are
  Serial.begin(9600);
  int placeInPattern = 0;

  // For loop to itterate over the elements in the array and check for the
  // pattern. If the pattern is found, it increments the placeInPattern variable.
  for (int i = 0; i < ELEMENTS_COUNT; i++)
  {
    if ((gEntries[i] == gPattern[0]) && (placeInPattern == 0))
    {
      placeInPattern++;
    }
    else if ((gEntries[i] == gPattern[1]) && (placeInPattern == 1))
    {
      placeInPattern++;
    }
    else if ((gEntries[i] == gPattern[2]) && (placeInPattern == 2))
    {
      placeInPattern++;
      digitalWrite(GREENLED, HIGH);
      gNumberOfOccurences++;
    }
    else
    {
      // If the pattern is broken, resets the placeholder variable and turns the green LED off
      placeInPattern = 0;
      digitalWrite(GREENLED, LOW);
    }
    delay(250); // A small delay that allows for visualization of the program working
    

  }
  // Checks if the number of occurences is 0. If so, it turns the red LED off
  if (gNumberOfOccurences == 0)
  {
    digitalWrite(REDLED, HIGH);
  }
  // Prints the number of occurences to the console
  Serial.println(gNumberOfOccurences);
}

void loop() 
{

}
