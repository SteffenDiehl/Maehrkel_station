#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include <time.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void start_display(){
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;); // Don't proceed, loop forever
    }
     // Show initial display buffer contents on the screen --
     // the library initializes this with an Adafruit splash screen.
    display.display();
}
void timer_output(unsigned long time){
    int hours = time / 3600000;
    int minutes = (time - hours*3600000)/60000;
    int seconds = (time - hours*3600000 - minutes*60000)/1000;
    display.setTextSize(2);
    display.printf("%2i:%2i:%2i\n", hours, minutes, seconds);
}
void display_Anzeige(int *m, int *p, int *p_max, int *t, unsigned long *t1, unsigned long *t2, unsigned long *t3, unsigned long *t4, unsigned long *t5, int *h, int *min, int *s, int *D, int *M, int *Y, String *fix_timer_name, int *wi_fi, int *t_out, unsigned long *ti, int *t_pause, int *t_anz){
    struct tm timeinfo;
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setFont();
    display.setTextSize(1);
    switch(*m){
        case 1://kein Timer aktiv
            *p_max = 2;
            switch (*p)
            {
            case 1: 
                display.setCursor(0,10);
                display.printf("Date: %2i.%2i.%4i\n", *D, *M, *Y);
                display.printf("Time: %2i:%2i:%2i\n", *h, *min, *s);
                display.setTextSize(2);
                display.println("new Timer");
                display.setTextSize(1);
                display.println("WiFi");
                break;
            default:
                display.setTextSize(3);
                display.println("Error");
                break;
            }
            break;
        default://Start und Standby Bildschirm
            display.setCursor(1, 10);
            display.setTextSize(2);
            display.setCursor(35, 5);
            display.printf("Event\n  Horizon\n");
            display.setTextSize(1);
            display.printf("         von\n");
            display.printf("    Team Buiskuit");
            break;
        }
    display.display();
}