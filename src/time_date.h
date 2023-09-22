#include <WiFi.h>
#include <Wire.h>
#include <WiFiUdp.h>
#include "RTClib.h"
#include <time.h>
#include <NTPClient.h>

RTC_DS3231 rtc;             // RTC-Instanz
WiFiUDP udp;                // WiFiUDP-Instanz 
NTPClient timeClient(udp,"de.pool.ntp.org", 7200);  // NTPClient-Instanz

void synchronizeRTC()
{
  // Mit NTP-Server verbinden
    timeClient.begin();

  // RTC-Zeit mit NTP_Server synchronisieren
    if (timeClient.update())
    {
    rtc.adjust(timeClient.getEpochTime());
    }

  // Verbindung schließen
    timeClient.end();
}

void start_RTC()
{
    Wire.begin();
    rtc.begin();

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void ac_time(int *Y, int *M, int *D, int *h, int *m, int *s)
{
    DateTime now = rtc.now();

    *Y = now.year();
    *M = now.month();
    *D = now.day();
    *h = now.hour();
    *m = now.minute();
    *s = now.second();
}