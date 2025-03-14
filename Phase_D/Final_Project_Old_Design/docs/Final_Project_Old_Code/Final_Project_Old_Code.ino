// Definitions
// Temperature Sensor #1    
    int temp1;
    float temp1Volt;
    float temp1C;
    float temp1F;
    
// Temperature Sensor #2   
    int temp2;
    float temp2Volt;
    float temp2C;
    float temp2F;
   
// Humidity Sensor    
    int humidity;
    float humidityVolt;
    float RH;
    
// Presure Sensor         
    int pressure;
    float pressureVolt;
    float psi;
    
// Accelerometer X  
    int accelX;
    float accelXVolt;
    float accelXG;
    
// Accelerometer Z
    int accelZ;
    float accelZVolt;
    float accelZG;
    
// Time keeper 
// The time stamp used when recording data points
    uint32_t timeStamp = 0;     
    
void setup() {
// put your setup code here, to run once:

      Serial.begin(9600);

// setup the LED Visual Display
      pinMode(3, OUTPUT);  //Arduino on
      pinMode(4, OUTPUT);  //Internal Temp
      pinMode(5, OUTPUT);  //External Temp
      pinMode(6, OUTPUT);  //Humidity
      pinMode(7, OUTPUT);  //Pressure
      pinMode(9, OUTPUT);  //Accels

// turn on Arduino LED
      digitalWrite(3, HIGH);  // Leave on while power is on 

// Print Column Headers
      Serial.println("Time,Temp1F,Temp2F,RH,Pres,AccX,AccZ");
}

void loop() { 
//   put your main code here, to run repeatedly:

//   Turn script running leds OFF at beginning of loop
     digitalWrite(4, LOW);
     digitalWrite(5, LOW);
     digitalWrite(6, LOW);
     digitalWrite(7, LOW);
     digitalWrite(9, LOW);
     
     delay(500);  //Amount of time between samples (milliseconds)
     
// Log the time
     timeStamp = millis();
     Serial.print(timeStamp);       
             
     temp1 = analogRead(A0);
     temp1Volt = temp1*(5.0/1023);
     temp1C = (temp1Volt - 0.5)/(0.01);
     temp1F = (temp1C*(9.0/5.0) + 32);
     Serial.print(",");    
     Serial.print(temp1F, 2);
     digitalWrite(4, HIGH);
 
     temp2 = analogRead(A1);
     temp2Volt = temp2*(5.0/1023);
     temp2C = (temp2Volt - 0.5)/(0.01);
     temp2F = (temp2C*(9.0/5.0) + 32);
     Serial.print(",");    
     Serial.print(temp2F, 2);
     digitalWrite(5, HIGH);
    
     humidity = analogRead(A2);
     humidityVolt = humidity*(5.0/1023);
     RH = (((humidityVolt/5.0)-0.16)/0.0062);
     Serial.print(",");    
     Serial.print(RH, 2);
     digitalWrite(6, HIGH);

     pressure = analogRead(A3);
     pressureVolt = pressure*(5.0/1023);
     psi = (pressureVolt-0.5)*(15.0/4.0); 
     Serial.print(",");    
     Serial.print(psi, 2);
     digitalWrite(7, HIGH);
     
     accelX = analogRead(A4);
     accelXVolt = accelX*(5.0/1023);
     accelXG = (accelXVolt - (3.3/2))/(0.330);
     Serial.print(",");    
     Serial.print(accelXG,3);

     accelZ = analogRead(A5);
     accelZVolt = accelZ*(5.0/1023);
     accelZG = (accelZVolt - (3.3/2))/(0.330);
     Serial.print(",");    
     Serial.print(accelZG,3);
     digitalWrite(9, HIGH);
     
     Serial.println();

}

