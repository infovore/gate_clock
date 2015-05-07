#include <Encoder.h>

Encoder myEnc(5, 6);

const int ledPin =  13;      // the number of the LED pin
const int pulsePin =  11;      // the number of the LED pin

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
int pulseState = LOW;             // ledState used to set the LED

float tempo = 120.0;
long oldPosition = -999;

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.

long pulseDuration = 50;

long blinkInterval;
long pulseInterval;
long blinkOffInterval;
long pulseOffInterval;


long nextBlink;
long nextPulse;

void setup() {
  // set the digital pin as output:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      
    pinMode(pulsePin, OUTPUT);      
      Serial.println(tempo);
  updateIntervals();
}

void loop()
{
  // here is where you'd put code that needs to be running all the time.
  
  long newPosition = myEnc.read();
  if(newPosition > oldPosition) {
    tempo = tempo + 0.5;
    
    updateIntervals();

    Serial.println(tempo);
  }
  
  if(newPosition < oldPosition) {
    tempo = tempo - 0.5;

    updateIntervals();

    Serial.println(tempo);
  }
  
  oldPosition = newPosition;
  
  long currentTime = millis();
  
  if (currentTime > nextBlink) {
    if (digitalRead(ledPin)) {
      digitalWrite(ledPin, LOW);
      nextBlink = currentTime + blinkOffInterval;
     } else {
       digitalWrite(ledPin, HIGH);
       nextBlink = currentTime + pulseDuration;
     }
  }
  
  if (currentTime > nextPulse) {
    if (digitalRead(pulsePin)) {
      digitalWrite(pulsePin, LOW);
      nextPulse = currentTime + pulseOffInterval;
     } else {
       digitalWrite(pulsePin, HIGH);
       nextPulse = currentTime + pulseDuration;
     }
  }
} 

void updateIntervals() {
    blinkInterval = 60 * 1000 / tempo;
    pulseInterval = blinkInterval / 2;
    blinkOffInterval = blinkInterval - pulseDuration;
    pulseOffInterval = pulseInterval - pulseDuration;
}

