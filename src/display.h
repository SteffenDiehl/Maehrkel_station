#include <Arduino_GFX_Library.h>

#define TFT_SCK    18
#define TFT_MOSI   23
#define TFT_MISO   19
#define TFT_CS     22
#define TFT_DC     21
#define TFT_RESET  17

Arduino_ESP32SPI bus = Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
Arduino_ILI9341 display = Arduino_ILI9341(&bus, TFT_RESET);
String myStatus[] = {"RUN", "GO HOME", "STOP"};

void setup_display()
{
    display.begin();
    display.setRotation(1);
    display.setCursor(20, 20);
    display.setTextColor(BLACK);
    display.fillRect(0, 0, 320, 40, DARKGREEN);
    display.setCursor(12, 12);
    display.setTextSize(3.5);
    display.println("Maehrkel_Station");
    display.fillRect(0, 40, 320, 200, GREEN);
    display.setTextSize(2.8);
    display.setCursor(0, 50);
    display.println(" IP:");
    display.println(" Date:");
    display.println(" Time:");
    display.println(" Status:");
    display.println(" Humidity:");
    display.println(" Temperature:");
    display.setCursor(108, 50);
    display.println(WiFi.localIP());
}
void display_output(String cDate, String cTime, int cStatus){
    int cHumidity = 0;
    int cTemp = 0;
    display.fillRect(100, 65, 220, 50, GREEN);
    display.setCursor(108, 66);
    display.println(cDate);
    display.setCursor(108, 82);
    display.println(cTime);
    display.setCursor(108, 98);
    display.println(myStatus[cStatus]);
    display.setCursor(108, 114);
    display.println(cHumidity);
    display.setCursor(108, 130);
    display.println(cTemp);
}