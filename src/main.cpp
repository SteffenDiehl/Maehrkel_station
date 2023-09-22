#include <Arduino.h>
#include <charge.h>
#include <display.h>
#include <drive.h>
#include <safety.h>
#include <webbrowser.h>
#include <connect.h>

void setup(){
    setup_webbrwoser();

}
void loop(){
    set_date_time();
}