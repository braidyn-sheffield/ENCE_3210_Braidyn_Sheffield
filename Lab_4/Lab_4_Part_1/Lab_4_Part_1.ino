/*
* An Arduino program that takes in four analog voltages and a reference voltage
* and simulates converting them to binary using a SAR ADC.
*/

#define VREF 3.0 // Reference voltage
#define NUMBITS 14 // Size of the array of bits to hold the converted binary values
#define NUMVOLTAGES 4 // Size of the array that holds the test voltages 

float gTestVoltages[NUMVOLTAGES] = {0.42, 0.83, 1.65, 2.752}; // Test voltages
int gBits[NUMBITS]; // Empty array that holds the converted analog voltages

void setup() 
{
  Serial.begin(9600); // Initialize serial communication

  Serial.println("Simulating a 14-bit SAR ADC with four test voltages."); // Printing that we are simulating
  
  for (int i = 0; i < NUMVOLTAGES; i++) // For loop that will iterate over the test voltages
  {
    float gThreshold = VREF / 2;  // Start with MSB test
    float step = VREF / 4;  // Next step is half of MSB test voltage

    // Printing formating for the test
    Serial.print("Analog Voltage: "); 
    Serial.print(gTestVoltages[i]);
    Serial.print(" | Binary Output: ");

    for (int j = 0; j < NUMBITS; j++) // For loop that iterates over the 14 binary bits
    {
      if (gTestVoltages[i] >= gThreshold)  // If input voltage is higher, set bit to 1
      {
        gBits[j] = 1;
        gThreshold += step;  // Move up
      } 
      else
      {
        gBits[j] = 0;
        gThreshold -= step;  // Move down
      }

      step /= 2;  // Reduce step size for next bit

      Serial.print(gBits[j]); // Print current binary digit of conversion
    }

    Serial.print(" | Reconstructed Voltage: ");
    Serial.print(gThreshold - step);  // Final DAC output
    Serial.println(" ");
  }
}

void loop() 
{

}

