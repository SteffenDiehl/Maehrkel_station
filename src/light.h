#include <Arduino.h>

const int LightPinR = 5;
const int LightPinG = 5;
const int LightPinB = 5;

void setup_Light() {
    pinMode(LightPinR, OUTPUT);
    pinMode(LightPinG, OUTPUT);
    pinMode(LightPinB, OUTPUT);
}

void set_Light(int cStatus) {
    if (cStatus == 0)
    {
        digitalWrite(LightPinR, HIGH);
        digitalWrite(LightPinG, LOW);
        digitalWrite(LightPinB, LOW);
    }
    else if (cStatus == 1)
    {
        digitalWrite(LightPinR, HIGH);
        digitalWrite(LightPinG, HIGH);
        digitalWrite(LightPinB, LOW);
    }
    else if (cStatus == 2)
    {
        digitalWrite(LightPinR, LOW);
        digitalWrite(LightPinG, HIGH);
        digitalWrite(LightPinB, LOW);
    }
}