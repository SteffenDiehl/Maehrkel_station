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
    display.setRotation(3);
    display.setCursor(20, 20);
    display.setTextColor(BLACK);
    display.fillRect(0, 0, 320, 40, DARKGREEN);
    display.setCursor(12, 12);
    display.setTextSize(3.5);
    display.println("Maehrkel_Station");
    display.fillRect(0, 40, 320, 200, GREEN);
    display.setTextSize(2.8);
    display.setCursor(0, 50);
    display.println(" IP:     192.168.43.55");
    display.println(" Date:   14.03.2024");
    display.println(" Time:   15:22");
    display.println(" Status: Stop");
    display.println(" Humid:  52,3");
    display.println(" Temp:   23,2");
//     display.println(" IP:");
//     display.println(" Date:");
//     display.println(" Time:");
//     display.println(" Status:");
//     display.println(" Humid:");
//     display.println(" Temp:");
//     display.setCursor(108, 50);
//     display.println("192.168.178.26");// Die gewünschte IP-Adresse //IP-Smartphone 192.168.43.68 // IP-Fritzbox 192.168.178.26
}
void display_output(String cDate, String cTime, int cStatus, float cHumidity, float cTemp){
    display.fillRect(100, 65, 220, 100, GREEN);
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