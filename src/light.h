#include <Arduino.h>

const int LightPin = 5;

void setup_Light() {
    pinMode(LightPin, OUTPUT);
}

void set_Light(int cStatus) {
    if (cStatus == 0)
    {
        /* code */
    }
    else if (cStatus == 1)
    {
        /* code */
    }
    else if (cStatus == 2)
    {
        /* code */
    }
    digitalWrite(LightPin, HIGH);
    digitalWrite(LightPin, LOW);
}