/*
* Program that searches through an array of 50
* random elements and finds the second maximum
* integer. Then writes the results to the memory
* location just after the array ends
*/

// Creating an array of 50 random integers
int intArray[50] = {
  45, 23, 89, 12, 67, 34, 90, 21, 54, 78,
  12, 43, 66, 87, 33, 45, 91, 15, 74, 83,
  42, 29, 56, 88, 65, 11, 53, 77, 31, 85,
  92, 17, 44, 62, 70, 36, 50, 80, 95, 37,
  19, 46, 25, 68, 32, 71, 39, 22, 58, 99
};

void setup() {
  // Beginning connection between the board and the console
  Serial.begin(9600);

  // Creating variables for the largest value and the second largest value
  int largest_value = 0;
  int sec_largest_value = 0;

// For loop that will iterate over the values of the array
for (int i = 1; i < 50; i++)
{
  // Creating a variable of the current value that the for loop is at
  int curr_val = intArray[i];
  // Checks whether the current value is larger than the second largest value
  if (curr_val > sec_largest_value)
  {
    // Checking if the current value is less than the largest value
    if (curr_val < largest_value)
    {
      // If it is, it changes the value of the second largest value variable
      sec_largest_value = curr_val;
    }
    else
    {
      // If it is not, it makes the second largest value the value of the largest number
      sec_largest_value = largest_value;
      // 
      largest_value = curr_val;
    }
  }

}
Serial.println("");
Serial.print("Largest Value: ");
Serial.println(largest_value);
Serial.print("Second Largest Value: ");
Serial.println(sec_largest_value);


int *result_location = &intArray[50]; // Memory location just after the array
*result_location = sec_largest_value; // Store the second largest value
Serial.print(*result_location);
}

void loop() {

}
