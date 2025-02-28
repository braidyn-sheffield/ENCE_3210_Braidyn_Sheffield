/*
* An Arduino based fan-controller. The system reads the current temperature using a temperature
* sensor, an LED that its PWM value is adjusted to simulate fan speed, and two push buttons. The
* two push buttons control turning the fan on and off and adjusting the sensitivity of the fan 
* speed with respect to the temperature. 100 samples are gathered every five seconds and the average
* is calculated to get a more reliable value. Timer 2 is used to get the temperature every 50 ms and 
* the value is added to an array which is used to calculate the average temperature. 
*/

// Import the required libraries
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 8 // Pin for Temperature Sensor
#define FAN 9 // Fan speed that is simulated using the brightness of an LED
#define FAN_ON_OFF 4 // Button that will turn the fan on and off
#define FAN_SENSITIVITY_BUTTON 2 // Button that will control the sensitivity of the fan
#define NUM_SAMPLES 100 // Size of the temperature array
#define TIMER2_COMPARE_VALUE 3125 // Compare value for Timer 2 (50ms)

OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.
DeviceAddress insideThermometer; // Array to hold the device address


int gFanSensitivity = 1; // Variable that will control the sensitivity of the fan
int gFanState = 0; // Variable that will track the state of the fan
float gTemperatures[NUM_SAMPLES] = {}; // Array to keep track of the 100 tempuratures
volatile bool gNewTempReady = false; // Flag that is triggered by Timer 1 ISR
float gAverageTemp = 0; // Variable that tracks the average temperature of the 100 samples


void setup() 
{
  Serial.begin(9600); // Initialize serial communication

  // Set all sensors and buttons as inputs or outputs
  pinMode(FAN, OUTPUT);
  pinMode(FAN_ON_OFF, INPUT);
  pinMode(FAN_SENSITIVITY_BUTTON, INPUT);

  // Temperature sensor setup
  sensors.begin(); 
  if (!sensors.getAddress(insideThermometer, 0)) 
  {
    Serial.println("Error: Temperature sensor not found!");
  } 
  else 
  {
    sensors.setResolution(insideThermometer, 9);
    Serial.println("Temperature sensor detected!");
  }

  // Timer 2 setup
  noInterrupts();  // Disable interrupts
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = TIMER2_COMPARE_VALUE; // 50ms interval (16MHz clock / 256 prescaler / 50ms)
  TCCR2B |= (1 << WGM12); // CTC Mode
  TCCR2B |= (1 << CS12);  // 256 prescaler
  TIMSK2 |= (1 << OCIE1A); // Enable interrupt
  interrupts();  // Enable interrupts

  for (int i = 0; i < NUM_SAMPLES; i++) // Set initial values for temperature array
  {
    gTemperatures[i] = 25.0; // Assume 25°C initial value
  }

}

void loop() 
{
  if (digitalRead(FAN_ON_OFF) == HIGH) // If the on off button is pressed...
  {
    delay(100); // Delay for debouncing
    gFanState = !gFanState; // Toggle the state of the fan
  }
  if (digitalRead(FAN_SENSITIVITY_BUTTON) == HIGH) // If the sensitivity button is pressed...
  {
    delay(100); // Delay for debouncing
    gFanSensitivity++; // Increase the sensitivity
    if (gFanSensitivity >= 4) // If the sensitivity is above or equal to 4...
    {
      gFanSensitivity = 1; // Reset it to 1
    }
  }

  if (gNewTempReady == true) // If Timer 2 has triggered...
  {
    gNewTempReady = false; // Reset the Timer 2 flag

     // Get new temperature
    sensors.requestTemperatures();
    float newTempValue = sensors.getTempC(insideThermometer);

    // Shift all temperatures inside the array to the right
    for (int i = NUM_SAMPLES - 1; i > 0; i--) 
    {
      gTemperatures[i] = gTemperatures[i - 1];
    }

    // Calculate the new average temeprature
    gAverageTemp = getAverageTemperature();
    
    gTemperatures[0] = newTempValue; // Insert the new temperature into the array
  }

  fanSpeed(); // Calling the external function that controls the speed of the fan

}

ISR(TIMER2_COMPA_vect) // Timer to set a flag to read a new temperature value
{
  gNewTempReady = true; // Set the flag to true
}

float getAverageTemperature() // External function that computes the average temperature of the latest 100 readings
{
  float tempSum = 0; // Variable to track sum

  for (int i = 0; i < NUM_SAMPLES; i++) // Iterate over the values
  {
    tempSum += gTemperatures[i]; // Get the sum of the past 100 temperatures
  }
  gAverageTemp = tempSum / NUM_SAMPLES; // Calculate the average temperaure

  return gAverageTemp; // Return the average temperature
}

void fanSpeed()
{
  if (gFanState == 0) // If the state of the fan is zero...
  {
    analogWrite(FAN, 0); // Turn off the fan
    return; // Exit the function
  }

  // Creates a new variable for the PWM of the LED that will control the brightness of it
  // to simulate the fan speed as well as calls on a function to turn the temperature to a
  // PWM value
  int PWMValue = TemperaturetoPWM(gAverageTemp, gFanSensitivity); 
  analogWrite(FAN, PWMValue); // Turn the LED on to the specified PWM value
}

int TemperaturetoPWM(float averageTemperature, int sensitivity) // External function to convert the temperature to a PWM value
{
  int PWMValue; // Create a variable to set the PWM value

  // State machine that is reliant on the sensitivity selected. Maps the temperature to different sets of PWM values
  // depending on what sensitivity is selected
  switch(sensitivity){ 
    case 1:
      PWMValue = map(averageTemperature, 25, 40, 50, 150);
      break;
    case 2:
      PWMValue = map(averageTemperature, 22, 35, 100, 200);
      break;
    case 3:
      PWMValue = map(averageTemperature, 20, 30, 150, 255);
      break;
  }

  return constrain(PWMValue, 0, 255); // Returns the PWM value and contrains it to 0 to 255 
}