#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <SPIFFS.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
  #include <Hash.h>
  #include <FS.h>
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);
const char* ssid = "JustDiehlWithIt";
const char* password = "DiehlWithIt09";

IPAddress staticIP(192, 168, 178, 26); // Die gewünschte IP-Adresse
IPAddress gateway(192, 168, 178, 1);    // Das Gateway
IPAddress subnet(255, 255, 255, 0);   // Die Subnetzmaske
IPAddress dns(8, 8, 8, 8);

const char* PARAM_festerTimerName6 = "festerTimerName6";
const char* PARAM_festerTimer6 = "festerTimer6";
const char* PARAM_festerTimerName7 = "festerTimerName7";
const char* PARAM_festerTimer7 = "festerTimer7";
const char* PARAM_festerTimerName8 = "festerTimerName8";
const char* PARAM_festerTimer8 = "festerTimer8";
const char* PARAM_festerTimerName9 = "festerTimerName9";
const char* PARAM_festerTimer9 = "festerTimer9";
const char* PARAM_festerTimerName10 = "festerTimerName10";
const char* PARAM_festerTimer10 = "festerTimer10";

const char* PARAM_festeTimerNameSelect = "festeTimerNameSelect";
const char* PARAM_timerSelect = "timerSelect";

const char* PARAM_timer1value = "timer1value";
const char* PARAM_timer2value = "timer2value";
const char* PARAM_timer3value = "timer3value";
const char* PARAM_timer4value = "timer4value";
const char* PARAM_timer5value = "timer5value";


String feste_Timer_Name[10] = {"Nudeln 7min", "Kartoffeln 14min", "Steak medium", "Mittag 1h", "Mittag 30min", "-", "-", "-", "-", "-"};
unsigned long feste_Timer[10] = {420000, 840000, 90000, 3600000, 1800000, 0, 0, 0, 0, 0};

const char* PARAM_CURRENTTIME = "currentTime";
unsigned long timer_1 = 0;
unsigned long timer_2 = 0;
unsigned long timer_3 = 0;
unsigned long timer_4 = 0;
unsigned long timer_5 = 0;
unsigned long timer[5];

String Date = "";
const char* ptr_Date = Date.c_str();
int *web_year = nullptr;
int *web_month = nullptr;
int *web_day = nullptr;

String Time = "";
const char* ptr_Time = Time.c_str();
int *web_hour = nullptr;
int *web_min = nullptr;
int *web_sec = nullptr;

int *web_status = nullptr;
String web_status_color[3] = {"green", "red", "yellow"};

unsigned long _timer[5] = {0, 0, 0, 0, 0};
// <center><font size='+2' color='blue'>Cisco Packet Tracer</font></center>
// <html><body style="background-color: lightgreen;">
// <hr>Welcome to Cisco Packet Tracer. Opening doors to new opportunities. Mind Wide Open
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html><body style="background-color: lightgreen;">
  <head>
    <meta http-equiv="refresh" content="10">
    <script>
    function submitMessage() {
      alert("Saved value to ESP SPIFFS");
      setTimeout(function(){ document.location.reload(false); }, 500);   
    }
    function startMessage() {
      alert("new Timer started");
      setTimeout(function(){ document.location.reload(false); }, 500);   
    }
    function startnow() {
      alert("Maerkel starts");
      setTimeout(function(){ document.location.reload(false); }, 500);   
    }
    function stopnow() {
      alert("Maerkel stops");
      setTimeout(function(){ document.location.reload(false); }, 500);   
    }
    function gohome() {
      alert("Maerkel goes home");
      setTimeout(function(){ document.location.reload(false); }, 500);   
    }
    </script>
    <title>Maehrkel</title>
    <link rel="icon" type="image/jpg" href="/images/Merkel.jpg">
  </head>
  <body>
    <form target= "hidden-form">
      <h1>Maehrkel<small><small><small> by Daniel Becher, Benedikt Buettner, Steffen Diehl </small></small></small></h1>
      <h2>Date: %currentDate%</h2>
      <h2>Current Time: %currentTime%</h2>
  <p><img src="https://www.bundeskanzler.de/resource/image/1860510/16x9/1023/575/1f8092e18cf8a8a122753b918d3e7016/aH/bundeskanzlerin-angela-merkel-portraet-2.jpg" alt="Smiley face" style="float:right;width:800px;height:450px;"></p>
    </form>
    <br>
    <form action="/stopnow" target="hidden-form">
      <input type="submit" style = background-color:FireBrick value="Stop now" onclick="stopnow()">
    </form>
    <form action="/gohomw" target="hidden-form">
      <input type="submit" style = background-color:DarkGreen value="Go home" onclick="gohome()">
    </form>
    <br>
    <br>
    <form target= "hidden-form">
      Timer: %timer1value% seconds / %timer1left% seconds left
    </form>
    <form action="/startnow" target="hidden-form">
      <input type="submit" style = background-color:DarkOrange value="Start now" onclick="startnow()">
    </form>
    <br>
    <br>
    <form target= "hidden-form">
      <strong>Timer 1</strong>
      <br>
      Start: %timer1value% seconds
      &nbsp; &nbsp; &nbsp;
      Time till start: %timer4left% seconds
    <br>
      End: %timer2value% seconds
      &nbsp; &nbsp; &nbsp;
      Time till end: %timer4left% seconds
    </form>
    <br>
    <br>
    <form target= "hidden-form">
      <strong>Timer 2</strong>
      <br>
      Start: %timer3value% seconds
      &nbsp; &nbsp; &nbsp;
      Time till start: %timer4left% seconds
    <br>
      End: %timer4value% seconds
      &nbsp; &nbsp; &nbsp;
      Time till end: %timer4left% seconds
    </form>
    <br>

    <form action="/get" target="hidden-form">
      Start now Timer (current value %festerTimerName6%): <input type="text" name="festerTimerName6">
      <br>
      <br>
      Start Time 1 (current value %festerTimerName7%): <input type="text" name="festerTimerName7">
      End Time 1 (current value %festerTimer7% ms): <input type="number " name="festerTimer7">
      <br>
      Start Time 2 (current value %festerTimerName8%): <input type="text" name="festerTimerName8">
      End Time 2 (current value %festerTimer8% ms): <input type="number " name="festerTimer8">
      <br>
      <input type="submit" value="Submit" onclick="submitMessage()">
    </form>
    <br>
    <br>

  <form action="/start" target="hidden-form">
    Timer %currentTimer%:
    <label>festeTimerName:</label>
    <select name="festeTimerNameSelect">
    <option value="%festerTimer1%">%festerTimerName1%</option>
    <option value="%festerTimer2%">%festerTimerName2%</option>
    <option value="%festerTimer3%">%festerTimerName3%</option>
    <option value="%festerTimer4%">%festerTimerName4%</option>
    <option value="%festerTimer5%">%festerTimerName5%</option>
    <option value="%festerTimer6%">%festerTimerName6%</option>
    <option value="%festerTimer7%">%festerTimerName7%</option>
    <option value="%festerTimer8%">%festerTimerName8%</option>
    <option value="%festerTimer9%">%festerTimerName9%</option>
    <option value="%festerTimer10%">%festerTimerName10%</option>
    </select>
    <input type="submit" value="Start a new Timer" onclick="startMessage()">
  </form>
  <iframe style="display:none" name="hidden-form"></iframe>
  </body>
</html>)rawliteral";

// Replaces placeholder with stored values
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

// Replaces placeholder with stored values
String processor(const String& var){
  if(var == "festerTimerName10"){
    return feste_Timer_Name[9];
  }
  else if(var == "festerTimer10"){
    return String(feste_Timer[9]);
  }
  else if(var == "timer1value"){
    return String(timer_1/1000);
  }
  else if(var == "currentTime"){
    return Time;
  }
  else if(var == "currentDate"){
    return Date;
  }
  else if(var== "timer1left") {
      return String(timer[0]/1000);
  }
  else if(var== "currentTimer") {
      return String(1);
  }
  else if(var== "statuscolor") {
      return web_status_color[*web_status];
  }
  return String();
}

void setup_webbrwoser(int *c_hour, int *c_min, int *c_sec, int *c_day, int *c_month, int *c_year, int *c_status) {
  web_hour = c_hour;
  web_min = c_min;
  web_sec = c_sec;
  web_day = c_day;
  web_month = c_month;
  web_year = c_year;
  web_status = c_status;
  // Initialize SPIFFS
  #ifdef ESP32
    if(!SPIFFS.begin(true)){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
  #else
    if(!SPIFFS.begin()){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
  #endif

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  WiFi.config(staticIP, gateway, subnet, dns);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  server.on("/gohome", HTTP_GET, [](AsyncWebServerRequest *request){
    *web_status = 3;
  });

  server.on("/stopnow", HTTP_GET, [](AsyncWebServerRequest *request){
    *web_status = 2;
  });

  server.on("/startnow", HTTP_GET, [](AsyncWebServerRequest *request){
    *web_status = 1;
  });

  server.on("/Date", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", ptr_Date);
  });

  server.on("/Time", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", ptr_Time);
  });

  // Send a GET request to <ESP_IP>/get?festerTimerName=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    unsigned long changetimer;
    String inputMessage;
    // GET festerTimerName value on <ESP_IP>/get?festerTimerName=<inputMessage>
    if (request->hasParam(PARAM_festerTimerName6)) {
      inputMessage = request->getParam(PARAM_festerTimerName6)->value();
      if(inputMessage != ""){
        feste_Timer_Name[5] = inputMessage;
      }
    }
    // GET inputInt value on <ESP_IP>/get?inputInt=<inputMessage>
    if (request->hasParam(PARAM_festerTimer9)) {
      inputMessage = request->getParam(PARAM_festerTimer9)->value();
      if(inputMessage != ""){
        changetimer = (inputMessage.toInt())*1000;
        feste_Timer[8] = changetimer;
      }
    }
    request->send(200, "text/text", inputMessage);
  });
  server.on("/start", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("start");
    });
  server.onNotFound(notFound);
  server.begin();
}

void web_browser_end(){
  server.end();
}
String formatDigits(int number) {
  if (number < 10) {
    return "0" + String(number);
  } else {
    return String(number);
  }
}

void set_date_time() {
  String d = formatDigits(*web_day);
  String m = formatDigits(*web_month);
  Date = d + "." + m + "." + String(*web_year);
  Time = formatDigits(*web_hour) + ":" + formatDigits(*web_min) + ":" + formatDigits(*web_sec);
// Function to format a number as a two-digit string
}