#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define SDA_PIN 21   // GPIO pin for I2C data line (SDA)
#define SCL_PIN 22  // GPIO pin for I2C clock line (SCL)

#define SEALEVELPRESSURE_HPA (1013.25) // Adjust this value to the current sea level pressure in your area if needed

Adafruit_BMP280 bmp; // I2C

unsigned long delayTime;

void setup_Sensor() {
    Serial.println(F("BMP280 test"));

    bool status;

    // Initialize I2C communication with specified GPIO pins
    Wire.begin(SDA_PIN, SCL_PIN);

    // Default settings
    status = bmp.begin(0x76);  
    if (!status) {
        Serial.println("Could not find a valid BMP280 sensor, check wiring!");
        while (1);
    }

    Serial.println("-- Default Test --");
    delayTime = 1000;

    Serial.println();
}

void check_Sensor() {
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.println();
}