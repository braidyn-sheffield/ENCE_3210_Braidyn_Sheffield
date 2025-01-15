/*
* Program that uses an array of integers,
* converts that integer into radians, and
* then prints the cosine value of each radian
* to the console
*/

#define ELEMENTS_COUNT 361 // Macro for the number of elements in the array

double gcosValues[ELEMENTS_COUNT]; // Creating the array


void setup() {

  Serial.begin(9600); // Initializing serial communication
  for (int i = 1; i < ELEMENTS_COUNT; i++) // For  loop that will iterate over each element in the array
  {
    double radians = i * (PI/180); // Converting each integer into radians
    gcosValues[i] = cos(radians); // Placing those radians into the array
    Serial.print(i); // Printing the integer onto the console
    Serial.print(" : "); 
    Serial.println(gcosValues[i]); // Printing the cosine of each radian value to the console
  }


}

void loop() {

}
