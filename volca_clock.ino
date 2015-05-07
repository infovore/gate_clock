#include <Encoder.h>

Encoder myEnc(5, 6);      // Encoder on pins 5/6

const int ledPin =  13;   // pin for the LED that blinks at tempo
const int pulsePin = 11;  // pin for the gate pulse out
const int potPin = 15;    // pin for swing potentiometer in

int ledState = LOW;
int pulseState = LOW;

float tempo = 120.0;      // in bpm
int swing = 0;            // percentage
long oldPosition = -999;

long pulseDuration = 50;  // how long is the pulse in ms?

long blinkInterval;
long pulseInterval;
long blinkOffInterval;
long pulseOffInterval;
long nextBlink;
long nextPulse;

void setup() {
  pinMode(ledPin, OUTPUT);      
  pinMode(pulsePin, OUTPUT);      
  updateIntervals();

  Serial.begin(9600);
  Serial.println(tempo);
}

void loop()
{
  // read swing from potentiometer
  int newSwingVal = analogRead(potPin);
  newSwingVal = map(newSwingVal, 0, 1023, 0, 100);

  if(newSwingVal != swing) {
    swing = newSwingVal;
    Serial.println(swing);
  }

  // read encoder and update tempo if necessary
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

  // now work out whether or not to blink / pulse
  //
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
  // first, calculate the interval between flashes in ms
  blinkInterval = 60 * 1000 / tempo;

  // pulse interval is half that, because the Volca syncs on a quaver beat.
  pulseInterval = blinkInterval / 2;

  blinkOffInterval = blinkInterval - pulseDuration;
  pulseOffInterval = pulseInterval - pulseDuration;
}

