
#include <Wire.h>
#include <WiFiUdp.h>
#include "RTClib.h"
#include <time.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void get_time_date(int *c_hour, int *c_min, int *c_sec, int *c_day, int *c_month, int *c_year) {
  timeClient.update();
  String formattedTime = timeClient.getFormattedTime();

  // Parse the formatted time string (HH:MM:SS format)
  int colon1 = formattedTime.indexOf(':');
  int colon2 = formattedTime.lastIndexOf(':');

  // Extract hour, minute, and second as integers
  *c_hour = formattedTime.substring(0, colon1).toInt();
  *c_hour += 1;
  *c_min = formattedTime.substring(colon1 + 1, colon2).toInt();
  *c_sec = formattedTime.substring(colon2 + 1).toInt();

  unsigned long epochTime = timeClient.getEpochTime();
  time_t time_t_epochTime = static_cast<time_t>(epochTime); // Convert to time_t
  struct tm *timeinfo;
  timeinfo = gmtime(&time_t_epochTime);

  *c_year = timeinfo->tm_year + 1900;  // Years since 1900
  *c_month = timeinfo->tm_mon + 1;     // Months since January (0-11)
  *c_day = timeinfo->tm_mday; 
}