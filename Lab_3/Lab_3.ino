/*
* A program that has two tasks running simulaneously and one main task running in
* in the foreground. One of the background tasks will blink the green LED at 1 Hz, 
* and the second background task is reading the current value of a button and 
* controlling an LED at 10 Hz. The foreground task is printing a message to the console
* using the timer from the first background task every three seconds.
*/

// Defining Macros for LED's, Button and timer compare values
#define GREENLED 4
#define REDLED 5
#define BUTTON 2
#define TIMER1_COMPARE_VALUE 62500 // Compare value for timer 1 to make the ISR happen at 1 Hz
#define TIMER2_COMPARE_VALUE 156   // Compare value for timer 2 to make the ISR happen at 100 Hz


int gCounter = 0; // Counter that is used for the output to the console
int gTimerCounter = 0; // Counter that is used to make timer 2 from 100 Hz to 10 Hz
bool buttonState = false;   // Stores the button state
volatile int gISRFlag1 = 0; // Flag set by Timer1 ISR
volatile int gISRFlag2 = 0; // Flag set by Timer2 ISR

void setup() 
{  
  Serial.begin(9600); // Initialize serial communication

  // Initialize I/Os
  pinMode(GREENLED, OUTPUT);
  pinMode(REDLED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP); 

  noInterrupts();               // Disable interrupts during configuration

  // Initialize Timer1 (1 Hz for Green LED and counter)
  TCCR1A = 0;                   // Clear Timer1 Control Register A
  TCCR1B = 0;                   // Clear Timer1 Control Register B
  OCR1A = TIMER1_COMPARE_VALUE; // Set compare match register for 1 Hz
  TCCR1B |= (1 << WGM12);       // Configure Timer1 in CTC mode
  TCCR1B |= (1 << CS12);        // Set prescaler to 256
  TIMSK1 |= (1 << OCIE1A);      // Enable Timer1 compare interrupt

  // Initialize Timer2 (100 Hz for button state checking)
  // The button state will be slowed down using a global counter
  TCCR2A = 0;                   // Clear Timer2 Control Register A
  TCCR2B = 0;                   // Clear Timer2 Control Register B
  OCR2A = TIMER2_COMPARE_VALUE; // Set compare match register for 100 Hz
  TCCR2A |= (1 << WGM21);       // Configure Timer2 in CTC mode
  // Set prescaler to 1024
  TCCR2B |= (1 << CS22);        
  TCCR2B |= (1 << CS21);
  TCCR2B |= (1 << CS20);
  TIMSK2 |= (1 << OCIE2A);      // Enable Timer2 compare interrupt

  interrupts(); // Enable all interrupts
}

void loop() 
{
  
  if (gISRFlag1) // Checks for the flag for Timer 1. Happens at a frequency of 1 Hz
  {
    gISRFlag1 = 0; // Reset Timer 1 flag
    gCounter++;    // Increment the counter
    digitalWrite(GREENLED, !digitalRead(GREENLED)); // Toggle green LED on and off
    
    if (gCounter == 3) // Checks if three seconds have elapsed for the foreground task
    {
      Serial.println("This message was brought to you by Timer 1"); // Print the message to the console
      gCounter = 0; // Reset the counter for the foreground task
    }
  }

  if (gISRFlag2) // Checks for the flag for Timer 2. Happens at a 100 Hz frequency
  {
    gTimerCounter++; // Increases the timer counter. This is used to slow down the clock from 100 Hz to 10 Hz
    if (gTimerCounter == 10) // Checks if the timer counter has reached 10. This is at a 10 Hz frequency
    {
      gTimerCounter = 0; // Resets timer counter
      buttonState = digitalRead(BUTTON); // Reads value of the button
      digitalWrite(REDLED, buttonState); // Turns red LED on or off depending on the state of the button
    }
  }
}

ISR(TIMER1_COMPA_vect) // Timer1 ISR (1 Hz for Green LED and message to console)
{
  gISRFlag1 = 1; // Set flag for the main loop
}


ISR(TIMER2_COMPA_vect) // Timer2 ISR (100 Hz for button checking)
{
  gISRFlag2 = 1; // Set flag for the main loop
}
