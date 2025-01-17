/*
* A program that turns on and off a red, green, and blue LED
* in a sequence that is toggled on and off by the use of a 
* push button.
*/

// Defining Macros for LED's, buttons, and the size of the arrays
#define REDLED 9
#define GREENLED 10
#define BLUELED 11
#define OPERATIONBUTTON 2
#define RESULTBUTTON 3
#define ARRAY_SIZE 10

// Defining variables that will track what operation is currently selected,
// as well as when the results button has been pressed
volatile int gOperationToggle = 0;
volatile bool gResultToggle = false;

// Arrays that hold the preset integers as well as an empty array for the results
int gFirstNumber[ARRAY_SIZE] = {4,5,7,9,6,4,5,2,6,8};
int gSecondNumber[ARRAY_SIZE] = {6,7,2,4,8,6,1,2,3,6};
int gResultArray[ARRAY_SIZE];

void setup() 
{
  // Setting the modes of the pins for the LED's and the buttons
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(BLUELED, OUTPUT);
  pinMode(OPERATIONBUTTON, INPUT_PULLUP);
  pinMode(RESULTBUTTON, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(OPERATIONBUTTON), operationButtonToggle, FALLING); // ISR that detects when the operation button has been pressed
  attachInterrupt(digitalPinToInterrupt(RESULTBUTTON), resultButtonToggle, FALLING); // ISR that detects when the result button has been pressed
}

void loop() 
{
  // If statement ladder that checks what operation is currently selected and turns on the respective LED
  if (gOperationToggle == 1)
  {
    digitalWrite(REDLED, HIGH);
    digitalWrite(GREENLED, LOW);
    digitalWrite(BLUELED, LOW);
  }
  else if (gOperationToggle == 2)
  {
    digitalWrite(REDLED, LOW);
    digitalWrite(GREENLED, HIGH);
    digitalWrite(BLUELED, LOW);
  }
  else if (gOperationToggle == 3)
  {
    digitalWrite(REDLED, LOW);
    digitalWrite(GREENLED, LOW);
    digitalWrite(BLUELED, HIGH);
  }
  // If statement that runs when the result button has been pressed
  if (gResultToggle ==true)
  {
    // Turning off all the LED's while the operation on the arrays are processing
    digitalWrite(REDLED, LOW);
    digitalWrite(GREENLED, LOW);
    digitalWrite(BLUELED, LOW);
    for (int i = 0; i < ARRAY_SIZE; i++) // For loop that wil iterate over the arrays
    {
      delay(100); // Delay for each loop to make the LED's staying off more visible

      // If statement ladder that does the respective operation based on the users selection
      if (gOperationToggle == 1)
          {
            gResultArray[i] = gFirstNumber[i] + gSecondNumber[i];
          }
      else if (gOperationToggle == 2)
          {
            gResultArray[i] = gFirstNumber[i] - gSecondNumber[i];
          }
      else if (gOperationToggle == 3)
          {
            gResultArray[i] = gFirstNumber[i] * gSecondNumber[i];
          }
    }

    // Sets the result variable to false exiting the if statement and starting the program over again
    // as well as turns the opeeration back to the default operation which is "None selected"
    gResultToggle = false;
    gOperationToggle = 0;

    // Turns all three LED's on for two seconds
    digitalWrite(REDLED, HIGH);
    digitalWrite(GREENLED, HIGH);
    digitalWrite(BLUELED, HIGH);
    delay(2000);
  }
  
}

void operationButtonToggle() // ISR that will increment the operation variable
{
  gOperationToggle++;

  if(gOperationToggle == 4) // If the operation variable goes above 3, it resets it back to one allowing the user to cycle through the operation
  {
    gOperationToggle = 1;
  }
}

void resultButtonToggle() // ISR the will change the value of the result toggle variable
{
  gResultToggle = true;
}