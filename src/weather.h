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
    }
}