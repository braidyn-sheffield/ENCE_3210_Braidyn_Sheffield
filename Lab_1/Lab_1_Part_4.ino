/*
* A program that find the letters R, G, and B in
* an array. If the letters are detected, it will 
* turn on that color LED, respectively. It will also 
* keep track of the number of occurences of each 
* letter in the array
*/

// Declaring Macros for all three LED's
#define REDLED 9
#define GREENLED 8
#define BLUELED 7

// Defining Macro for number of elements in the array
#define ELEMENTS_COUNT 9

// Creating a test array with nine characters inside of it
char letters[ELEMENTS_COUNT] = {'R', 'G', 'B', 'R', 'G', 'R', 'B', 'G', 'R'};

// Initializing global variables for the occurance counters
int gCountRed = 0;
int gCountBlue = 0;
int gCountGreen = 0;

void setup()
{
  Serial.begin(9600); // Initializing serial communication

  pinMode(REDLED, OUTPUT); // Setting the REDLED pin to an output
  pinMode(GREENLED, OUTPUT); // Setting the GREENLED pin the an output
  pinMode(BLUELED, OUTPUT); // Setting the BLUELED pin to an output

  for (int i = 0; i < ELEMENTS_COUNT; i++) // For loop that will traverse across all the elements in the array
  {
    if (letters[i] == 'R') // Checks if the current character is 'R'
    {
      gCountRed++; // Increments the REDLED counter

      // Turns on the REDLED for 500 ms and then turns it off
      digitalWrite(REDLED, HIGH);
      delay(500);
      digitalWrite(REDLED, LOW);
    } 
    else if (letters[i] == 'G') // Checks if the current character is 'G'
    {
      gCountGreen++; // Increments the GREENLED counter

      // Turns on the GREENLED for 500 ms and then turns it off
      digitalWrite(GREENLED, HIGH);
      delay(500);
      digitalWrite(GREENLED, LOW);
    } 
    else if (letters[i] == 'B') // Checks if the current character is 'B'
    {
      gCountBlue++; // Increments the BLUELED counter

      // Turns on the BLUELED for 500 ms and then turns it off
      digitalWrite(BLUELED, HIGH);
      delay(500);
      digitalWrite(BLUELED, LOW);
    }
  }
  // Prints the number of occurences of each letter to the console
  Serial.println("Number of Letter Occurences");
  Serial.print("R: ");
  Serial.println(gCountRed);
  Serial.print("G: ");
  Serial.println(gCountGreen);
  Serial.print("B: ");
  Serial.println(gCountBlue);

}

void loop() 
{

}
