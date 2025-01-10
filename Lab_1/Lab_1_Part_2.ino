double cosValues[361];


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 1; i < 361; i++)
  {
    double radians = i * (PI/180);
    cosValues[i] = cos(radians);
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(cosValues[i]);
  }


}

void loop() {
  // put your main code here, to run repeatedly:

}
