/*
* A program that turns on and off a red, green, and blue LED
* in a sequence that is toggled on and off by the use of a 
* push button.
*/

// Defining Macros for LED's and button
#define REDLED 9
#define GREENLED 10
#define BLUELED 11
#define BUTTON 2

// Creating a variable that will track whether the sequence is on or off
volatile bool sequenceToggle = false;

void setup() 
{
  // Setting the modes of the pins for the LED's and the button
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(BLUELED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonToggle, FALLING); // ISR to toggle whether the sequence is on or off
}

void loop() 
{
  if (sequenceToggle == true) // Checks the variable to see if the sequence should be running or not
  {
    // Sequence of LED's turning on and off
    digitalWrite(REDLED, HIGH);
    delay(200);
    digitalWrite(GREENLED, HIGH);
    delay(200);
    digitalWrite(BLUELED, HIGH);
    delay(200);
    digitalWrite(REDLED, LOW);
    delay(200);
    digitalWrite(GREENLED, LOW);
    delay(200);
    digitalWrite(BLUELED, LOW);
    delay(200);
  }
  else
  {
    // Ensuring if the sequence is off, all of the LED's are off
    digitalWrite(REDLED, LOW);
    digitalWrite(GREENLED, LOW);
    digitalWrite(BLUELED, LOW);
  }
}

void buttonToggle() // ISR that toggles whether the sequence runs or not
{
  sequenceToggle = !sequenceToggle; // Inverts the value of the sequenceToggle variable
}