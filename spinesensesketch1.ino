/*
SpineSense

Gilad Oved
7-28-15 
*/

// constants
const int analogSensor1 = A0;  // pin of the first sensor
const int ledPin1 = 9; // pin of the first sensor's led

const int analogSensor2 = A1;  // pin of the second sensor
const int ledPin2 = 10; // pin of the second sensor's led

const int analogSensor3 = A2;  // pin of the third sensor
const int ledPin3 = 11; // pin of the third sensor's led

const int buzzerPin = 12; //pin of the buzzer
const int buttonPin = 2; //pin of the callibration button



//Adjust these constants to demo
const int sensor1BendValue = 20; //maximum amount before the first sensor recognizes it as a bad posture
const int sensor2BendValue = 20; //maximum amount before the second sensor recognizes it as a bad posture
const int sensor3BendValue = 20; //maximum amount before the third sensor recognizes it as a bad posture
const long warningTime = 5000; //number of milliseconds the led light is one before causing a warning
const int lowerRangeSensor1 = 400;  // the lower range of the raw sensor data
const int upperRangeSensor1 = 900;  // the upper range of the raw sensor data
const int lowerRangeSensor2 = 400;  // the lower range of the raw sensor data
const int upperRangeSensor2 = 900;  // the upper range of the raw sensor data
const int lowerRangeSensor3 = 400;  // the lower range of the raw sensor data
const int upperRangeSensor3 = 900;  // the upper range of the raw sensor data



//global variables
int sensorRaw1 = 0;
int sensorRaw2 = 0;
int sensorRaw3 = 0;
int sensorValue1 = 0;     // value read from the first sensor
int sensorValue2 = 0;     // value read from the second sensor
int sensorValue3 = 0;     // value read from the third sensor
int ledState1 = LOW;   //the state of the first led    
int ledState2 = LOW;   //the state of the second led
int ledState3 = LOW;   //the state of the third led
int buzzerState = LOW;  //the state of the buzzer
unsigned long previousMillis = 0; //helper variable to help keep track of time passed
unsigned long currentMillis = 0; //keeps track of the current time
int callibrationSensor1 = 0;  //callibration value for first sensor
int callibrationSensor2 = 0;  //callibration value for second sensor
int callibrationSensor3 = 0;  //callibration value for third sensor
int buttonState = 0;   //state of the callibration button

void setup() {
  // initialize serial communications:
  Serial.begin(9600); 
  //initialize the digital pins (leds, buzzer and button)
  pinMode(ledPin1, OUTPUT); 
  pinMode(ledPin2, OUTPUT); 
  pinMode(ledPin3, OUTPUT); 
  pinMode(buzzerPin, OUTPUT);  
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the sensor values (flex and button):
  sensorRaw1 = analogRead(analogSensor1);  
  sensorRaw2 = analogRead(analogSensor2);            
  sensorRaw3 = analogRead(analogSensor3);              
  buttonState = digitalRead(buttonPin);
  
  sensorValue1 = map(sensorRaw1, lowerRangeSensor1, upperRangeSensor1, 0, 100);
  sensorValue2 = map(sensorRaw2, lowerRangeSensor2, upperRangeSensor2, 0, 100);
  sensorValue3 = map(sensorRaw3, lowerRangeSensor3, upperRangeSensor3, 0, 100);
  
  //update the current time
  currentMillis = millis();
  
  //check if the callibrate button was pressed
  if (buttonState == HIGH) {
    //update the callibrate values for all the sensors
     callibrationSensor1 = sensorValue1;
     callibrationSensor2 = sensorValue2;  
     callibrationSensor3 = sensorValue3;  
  }
  
  //default the buzzer state to off
  buzzerState = LOW;
  if (sensorValue1 - callibrationSensor1 > sensor1BendValue) { //checks for bad posture
      ledState1 = HIGH; //turns the coorisponding led on
      if(currentMillis - previousMillis >= warningTime) { //checks to see if warning time has passed
        buzzerState = HIGH;    //turn on the buzzer after warning time has passed
      } 
  } else {  //good posture
      ledState1 = LOW;  //turn the led off
  }
  
    if (sensorValue2 - callibrationSensor2 > sensor2BendValue) { //checks for bad posture
        ledState2 = HIGH; //turns the coorisponding led on
        if(currentMillis - previousMillis >= warningTime) { //checks to see if warning time has passed
          buzzerState = HIGH;    //turn on the buzzer after warning time has passed
        } 
    } else {  //good posture
        ledState2 = LOW;  //turn the led off
    }
  
    if (sensorValue3 - callibrationSensor3 > sensor3BendValue) { //checks for bad posture
        ledState3 = HIGH; //turns the coorisponding led on
        if(currentMillis - previousMillis >= warningTime) { //checks to see if warning time has passed
          buzzerState = HIGH;    //turn on the buzzer after warning time has passed
        } 
    } else {  //good posture
        ledState3 = LOW;  //turn the led off
    }
  
    //if all the lights are off, set the previous time to the current time
    if (ledState1 == LOW && ledState2 == LOW && ledState3 == LOW) {
       previousMillis = currentMillis; 
    }
  
     // set the LEDs and buzzers
     digitalWrite(ledPin1, ledState1);
     digitalWrite(ledPin2, ledState2);
     digitalWrite(ledPin3, ledState3);
     digitalWrite(buzzerPin, buzzerState);   

    // print sensor data
    Serial.print("sensor = " );                       
    Serial.println(sensorValue3);      

    // wait 50 milliseconds before the next loop
    delay(50);                     
}
