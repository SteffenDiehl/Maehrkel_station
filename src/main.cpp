#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_BusIO_Register.h>
#include <charge.h>
#include <display.h>
#include <safety.h>
#include <webbrowser.h>
#include <weather.h>
#include <time_date.h>
#include <timer.h>
#include <light.h>

int current_hour = 0;
int current_min = 0;
int current_sec = 0;
int current_day = 0;
int current_month = 0;
int current_year = 0;

int current_now_hour = 0;
int current_now_min = 0;
int current_now_timer_hour = 0;
int current_now_timer_min = 0;
int current_timer_now = 0; //0 = stop, 1 = running

int current_start1_hour = 0;
int current_start1_min = 0;
int current_timer1 = 0; //0 = stop, 1 = running

int current_start2_hour = 0;
int current_start2_min = 0;
int current_timer2 = 0; //0 = stop, 1 = running

int current_mowtime_hour = 1;
int current_mowtime_min = 30;

int status = 2;

String main_Date = "";
String main_Time = "";

void setup(){
    Serial.begin(115200);
    setup_webbrowser(
        &current_hour, &current_min, &current_sec,
        &current_day, &current_month, &current_year,
        &status,
        &current_mowtime_hour, &current_mowtime_min,
        &current_now_hour, &current_now_min, &current_now_timer_hour, &current_now_timer_min,
        &current_timer_now,
        &current_start1_hour, &current_start1_min, &current_timer1,
        &current_start2_hour, &current_start2_min, &current_timer2);

    setup_timer(
        &current_hour, &current_min, &current_sec,
        &current_day, &current_month, &current_year,
        &status,
        &current_mowtime_hour, &current_mowtime_min,
        &current_now_hour, &current_now_min, &current_now_timer_hour, &current_now_timer_min,
        &current_timer_now,
        &current_start1_hour, &current_start1_min, &current_timer1,
        &current_start2_hour, &current_start2_min, &current_timer2);
    setup_display();
    setup_Light();
}
void loop(){
    main_Date = String(current_day) + ":" + String(current_month) + ":" + String(current_year);
    main_Time = formatDigits(current_hour) + ":" + formatDigits(current_min) + ":" + formatDigits(current_sec);
    get_time_date(&current_hour, &current_min, &current_sec, &current_day, &current_month, &current_year);
    check_timer();
    set_date_time();
    set_Light(status);
    display_output(main_Date, main_Time, status);
    delay(500);
}