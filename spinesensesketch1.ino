/*
  Analog input, analog output, serial output
 
 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.
 
 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground
 
 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
 
 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogSensor1 = A0;  // Analog input pin that the potentiometer is attached to
const int ledPin1 = 9; // Analog output pin that the LED is attached to

const int analogSensor2 = A1;  // Analog input pin that the potentiometer is attached to
const int ledPin2 = 10; // Analog output pin that the LED is attached to

const int analogSensor3 = A2;  // Analog input pin that the potentiometer is attached to
const int ledPin3 = 11; // Analog output pin that the LED is attached to

const int buzzerPin = 12;
const int buttonPin = 2;
const int sensorBendValue = 2;
const long warningTime = 5000;

int sensorValue1 = 0;        // value read from the pot
int sensorValue2 = 0;        // value read from the pot
int sensorValue3 = 0;        // value read from the pot
int ledState1 = LOW; 
int ledState2 = LOW; 
int ledState3 = LOW; 
int buzzerState = LOW; 
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
int callibrationSensor1 = 0;
int callibrationSensor2 = 0;
int callibrationSensor3 = 0;
int buttonState = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  pinMode(ledPin1, OUTPUT); 
  pinMode(ledPin2, OUTPUT); 
  pinMode(ledPin3, OUTPUT); 
  pinMode(buzzerPin, OUTPUT);  
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the analog in value:
  sensorValue1 = analogRead(analogSensor1);  
  sensorValue2 = analogRead(analogSensor2);            
  sensorValue3 = analogRead(analogSensor3);              
  buttonState = digitalRead(buttonPin);
  
  currentMillis = millis();
  
  if (buttonState == HIGH) {
     callibrationSensor1 = sensorValue1;
     callibrationSensor2 = sensorValue2;  
     callibrationSensor3 = sensorValue3;  
   
     previousMillis = currentMillis;  
  }
  
  buzzerState = LOW;
  if (sensorValue1 < callibrationSensor1 - sensorBendValue) {
      ledState1 = HIGH;
      if(currentMillis - previousMillis >= warningTime) {
        Serial.println("FIX POSTURE NOW!!!!");
        buzzerState = HIGH;
      } 
  } else {
      ledState1 = LOW;
  }
  
    if (sensorValue2 < callibrationSensor2 - sensorBendValue) {
      ledState2 = HIGH;
      if(currentMillis - previousMillis >= warningTime) {
        //Serial.println("FIX POSTURE NOW!!!!");
        buzzerState = HIGH;
      } 
  } else {
      ledState2 = LOW;
  }
  
    if (sensorValue3 < callibrationSensor3 - sensorBendValue) {
      ledState3 = HIGH;
      if(currentMillis - previousMillis >= warningTime) {
        //Serial.println("FIX POSTURE NOW!!!!");
        buzzerState = HIGH;
      } 
  } else {
      ledState3 = LOW;
  }
  
  if (ledState1 == LOW && ledState2 == LOW && ledState3 == LOW) {
     previousMillis = currentMillis; 
  }
  
    // set the LED with the ledState1 of the variable:
   digitalWrite(ledPin1, ledState1);
   digitalWrite(ledPin2, ledState2);
   digitalWrite(ledPin3, ledState3);
   digitalWrite(buzzerPin, buzzerState);   

  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.println(sensorValue3);      

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(100);                     
}
