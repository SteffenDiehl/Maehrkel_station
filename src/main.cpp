#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_BusIO_Register.h>
#include <charge.h>
#include <display.h>
#include <safety.h>
#include <webbrowser.h>
#include <weather.h>
#include <time_date.h>

int current_hour = 0;
int current_min = 0;
int current_sec = 0;
int current_day = 0;
int current_month = 0;
int current_year = 0;

int status = 2;

String main_Date = "";
String main_Time = "";

void setup(){
    Serial.begin(115200);
    setup_webbrwoser(&current_hour, &current_min, &current_sec, &current_day, &current_month, &current_year, &status);
    setup_display();
}
void loop(){
    main_Date = String(current_day) + ":" + String(current_month) + ":" + String(current_year);
    main_Time = formatDigits(current_hour) + ":" + formatDigits(current_min) + ":" + formatDigits(current_sec);
    get_time_date(&current_hour, &current_min, &current_sec, &current_day, &current_month, &current_year);
    set_date_time();
    display_output(main_Date, main_Time, status);
    delay(500);
}