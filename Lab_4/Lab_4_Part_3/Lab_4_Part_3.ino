/*
* An Arduino Program that is a simulated solar charge controller that switches the power input
* of a microprocessor between a solar panel and a battery. The solar panel is simulated by reading 
* the value of a potentiometer and the battery voltage is simulated and tracked within the code.
* Once the battery starts charging, it does not stop charging until it is fully charged.
*/

// Importing all required libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Setup
#define SCREEN_WIDTH   128 // OLED display width, in pixels
#define SCREEN_HEIGHT  32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SOLAR_PIN A0 // Voltage of solar panel. Simulated by potentiometer value
#define INCREASE_BATTERY 3 // Push button that will increase the voltage of the battery
#define DECREASE_BATTERY 4 // Push button that will decrease the voltage of the battery
#define LED 9 // LED to indicate that the solar panel is charging the battery

#define SOLAR_PANEL_THRESHOLD 2.5 // Threshold where the power to the microprocessor is changed
#define BATTERY_FULL_CHARGE 4.7 // Voltage when the battery is fully charged

float gBatteryVoltage = 3.5; // Initial value of the charge of the battery
int gBatteryChargeStatus = 0; // Status on whether the battery is charging or not

// Enumerate that creates the states of the state machine
enum Charge_State {
  SOLARPANELCHARGE,
  BATTERYCHARGE
};

Charge_State currentState = SOLARPANELCHARGE; // Start in the state where the solar panel is charging

void setup() 
{
  Serial.begin(9600); // Initialize serial communication

  // Set all input and output pins 
  pinMode(SOLAR_PIN, INPUT);
  pinMode(INCREASE_BATTERY, INPUT);
  pinMode(DECREASE_BATTERY, INPUT);
  pinMode(LED, OUTPUT);

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display(); // Show initial display buffer contents on the screen
  delay(500); // Pause for 1 second

  display.clearDisplay(); // Clear the buffer

}

void loop() 
{
  float solarVoltage = (analogRead(SOLAR_PIN) / 1023.0) * 5.0; // Reading the voltage of the solar panel from the potentiometer
  
  switch(currentState){
    case SOLARPANELCHARGE: // State where the solar panel is supplying power to the microprocessor
      checkButtons(); // Calls function that checks on if the buttons are pressed
      displayOLED(solarVoltage); // Displays voltages and charging source on the OLED

      digitalWrite(LED, gBatteryChargeStatus); // Control's the LED based on whether the battery is charging

      if (solarVoltage > gBatteryVoltage) // If the solar panel is outputting a higher voltage than the battery...
      {
        gBatteryChargeStatus = 1; // Change battery charge varibale to one
      }
      else if (gBatteryVoltage >= BATTERY_FULL_CHARGE) // If the battery is fully charged...
      {
        gBatteryChargeStatus = 0; // Change battery charge varibale to zero
      }

      if (solarVoltage < 2.5) // If the voltage of solar panel goes below 2.5V...
      {
        currentState = BATTERYCHARGE; // Change to the state where the battery is supplying power
      }

      break;
    
    case BATTERYCHARGE: // State where the battery is supplying power to the microprocessor
      checkButtons(); // Calls function that checks the push
      displayOLED(solarVoltage); // Displays voltages and charging source on the OLED

      digitalWrite(LED, gBatteryChargeStatus); // Control's the LED based on whether the battery is charging

      if (solarVoltage > gBatteryVoltage) // If the solar panel is outputting a higher voltage than the battery...
      {
        gBatteryChargeStatus = 1; // Change battery charge varibale to one
      }
      else if (gBatteryVoltage >= BATTERY_FULL_CHARGE) // If the battery is fully charged...
      {
        gBatteryChargeStatus = 0; // Change battery charge varibale to zero
      }

      if (solarVoltage > 2.5) // If the voltage of solar panel is greater than 2.5V...
      {
        currentState = SOLARPANELCHARGE; // Change to the state where the solar panel is supplying power
      }


      break;
  }
}

void checkButtons() // External funciton to check states of push buttons
{
  if (digitalRead(INCREASE_BATTERY) == HIGH) // If battery voltage increase button is pressed...
  {
    gBatteryVoltage += 0.1; // Increase the battery voltage by 0.1
    delay(100); // Wait 0.1 seconds for debouncing 
  }
  else if (digitalRead(DECREASE_BATTERY) == HIGH) // If battery voltage decrease button is pressed...
  {
    gBatteryVoltage -= 0.1; // Decrease the battery voltage by 0.1
    delay(100); // Wait 0.1 seconds for debouncing
  }
}

void displayOLED(float solarVoltage) // External function that displays the voltages and the power source on the OLED
{
  display.clearDisplay(); // Only clear once at the beginning

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  // Display Solar Voltage
  display.setCursor(0, 0);
  display.print("Solar: ");
  display.print(solarVoltage);
  display.print("V");

  // Display Battery Voltage
  display.setCursor(0, 10);
  display.print("Battery: ");
  display.print(gBatteryVoltage);
  display.print("V");

  // Display Power Source
  display.setCursor(0, 20);
  display.print("Power: ");
  if (currentState == SOLARPANELCHARGE)
  {
    display.print("Solar Panel");
  }
  else
  {
    display.print("Battery");
  }

  display.display(); // Refresh the OLED after printing everything
}