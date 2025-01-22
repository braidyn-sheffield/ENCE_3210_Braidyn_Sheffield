/*
* A program that reads a button press that calls an ISR that performs an
* operation on each element of the array and saves the result in another array
*/

// Defining Macros for the LED's, button, and the size of the array's
#define REDLED 5
#define GREENLED 4
#define BUTTON 3
#define ARRAY_SIZE 10

// Defining the two arrays. One of them being predetermined and the other being empty to
// hold the results of the ISR
int gArrayX[ARRAY_SIZE] = {5,4,8,6,7,1,3,5,8,10};
int gArrayY[ARRAY_SIZE];

void setup() 
{
  // Setting the pin modes for the LED's and the button
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON), filteringOperation, FALLING); // ISR that reads for the push of the button and calls the FilteringOperation ISR

}

void loop() 
{  

}

void filteringOperation()
{
  for (int i = 0; i < ARRAY_SIZE; i++) // For loop to iterate over the first array
  {
    gArrayY[i] = 2 * gArrayX[i] - gArrayX[i-1]; // Performs the operation and saves the result into the second array
  }
}
