/*
* A program that detects when two different buttons are pressed and
* calculates the difference between the two of them. The difference is 
* shown on two LED's
*/

// Macros for the LED's and the buttons
#define REDLED 5
#define GREENLED 4
#define BUTTON2 3
#define BUTTON1 2

volatile int gButtonTracker = 0; // Variable that tracks the difference between the buttons

void setup() 
{
  Serial.begin(9600); // Initialize serial communication

  // Setting the LED's and the buttons as inputs and outputs.
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON1, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON2), button1Toggle, FALLING); // ISR that detects when button2 has been pressed
  attachInterrupt(digitalPinToInterrupt(BUTTON1), button2Toggle, FALLING); // ISR that detects when button2 has been pressed
}

void loop() 
{
  // Print the current value of the difference between the two buttons on the console
  Serial.print("Button Tracker: ");
  Serial.println(gButtonTracker);

  // If-else ladder that turns on the respective LED depending on the value of the button tracker
  if (gButtonTracker == 0) // If the button presses are equal, both LED's are turned on
  {
    digitalWrite(GREENLED, HIGH);
    digitalWrite(REDLED, HIGH);
  }
  else if (gButtonTracker < 1) // If button two has been pressed more, the green LED turns on
  {
    digitalWrite(GREENLED, HIGH);
    digitalWrite(REDLED, LOW);
  }
  if (gButtonTracker > 1) // If button one has been pressed more, the red LED turns on
  {
    digitalWrite(GREENLED, LOW);
    digitalWrite(REDLED, HIGH);
  }
  delay(150); // Delay to help with debouncing the buttons
}

void button1Toggle() // Button 1 ISR that will increment the value of the button tracker
{
  gButtonTracker++;
}

void button2Toggle() // Button 2 ISR that will decrease the value of the button tracker
{
  gButtonTracker--;
}