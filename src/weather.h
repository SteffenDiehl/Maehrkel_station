/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-temperature-humidity-sensor
 */

#include <DHT.h>
#define DHT_SENSOR_PIN  4 // ESP32 pin GPIO21 connected to DHT11 sensor
#define DHT_SENSOR_TYPE DHT22

DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

void setup_DHT22() {
    dht_sensor.begin(); // initialize the DHT sensor
}

void get_weather(float *humi, float *temp) {
    // read humidity
    *humi  = dht_sensor.readHumidity();
    // read temperature in Celsius
    *temp = dht_sensor.readTemperature();
    // read temperature in Fahrenheit
    //float tempF = dht_sensor.readTemperature(true);

    // check whether the reading is successful or not
    if ( isnan(*temp) || isnan(*humi)) {
    Serial.println("Failed to read from DHT sensor!");
    } else {
    Serial.print("Humidity: ");
    Serial.print(*humi);
    Serial.print("%");

    Serial.print("  |  ");

    Serial.print("Temperature: ");
    Serial.print(*temp);
    Serial.println("°C");
    //Serial.print(*tempF);
    //Serial.println("°F");
    }
    // wait a 2 seconds between readings
}


// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_BMP280.h>

// #define SDA_PIN 21   // GPIO pin for I2C data line (SDA)
// #define SCL_PIN 22  // GPIO pin for I2C clock line (SCL)

// #define SEALEVELPRESSURE_HPA (1013.25) // Adjust this value to the current sea level pressure in your area if needed

// Adafruit_BMP280 bmp; // I2C

// unsigned long delayTime;

// void setup_Sensor() {
//     Serial.println(F("BMP280 test"));

//     bool status;

//     // Initialize I2C communication with specified GPIO pins
//     Wire.begin(SDA_PIN, SCL_PIN);

//     // Default settings
//     status = bmp.begin(0x76);  
//     if (!status) {
//         Serial.println("Could not find a valid BMP280 sensor, check wiring!");
//         while (1);
//     }

//     Serial.println("-- Default Test --");
//     delayTime = 1000;

//     Serial.println();
// }

// void check_Sensor() {
//     Serial.print("Temperature = ");
//     Serial.print(bmp.readTemperature());
//     Serial.println(" *C");

//     Serial.print("Pressure = ");
//     Serial.print(bmp.readPressure() / 100.0F);
//     Serial.println(" hPa");

//     Serial.print("Approx. Altitude = ");
//     Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
//     Serial.println(" m");

//     Serial.println();
// }