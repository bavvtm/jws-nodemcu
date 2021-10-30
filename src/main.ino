#include <Arduino.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "FS.h"
#include <LittleFS.h>
#include <DMDESP.h>
#include <fonts/Font4x6.h>
#include <fonts/EMSans8x16.h>
#include <fonts/SystemFont5x7.h>
#include <RtcDS3231.h>
#include <Ticker.h>
#include <PrayerTimes.h>

#define DISPLAYS_WIDE 3
#define DISPLAYS_HIGH 1

DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);
RtcDS3231<TwoWire> Rtc(Wire);
AsyncWebServer server(80);
// AsyncWebSocket ws("/ws"); if you need to add webpage, use websocket :)
Ticker ticker;

struct PrayerConfig
{
  float L_LA;
  float L_LO;
  int L_TZ;
  int L_FA;
  int L_FE;
};

struct PrayerCompare
{
  int COR_IMSAK;
  int COR_SHUBUH;
  int COR_TERBIT;
  int COR_DZUHUR;
  int COR_ASHAR;
  int COR_TERBENAM;
  int COR_MAGHRIB;
  int COR_ISYA;
};

struct InfoConfig
{
  int UIS_NM;
  int UIS_INFO_1;
  int UIS_INFO_2;
  int UIS_INFO_3;
  char UI_NM[100];
  char UI_INFO_1[512];
  char UI_INFO_2[512];
  char UI_INFO_3[512];
};

struct SettingConfig
{
  char WIFI_SSID[512];
  char WIFI_PASSWORD[512];
  char USERNAME[512];
  char PASSWORD[512];
  int BRIGHTNESS;
  int MARQUE_SPEED;
};

PrayerConfig prayerConfig;
PrayerCompare prayerCompare;
InfoConfig infoConfig;
SettingConfig settingsConfig;

// Variables
const int buzzer = 3;
String SH = ":";
int drwMode = 0;
int infoMode = 1;
int dayOld = 0;
boolean Swap;
float lunarY = 354.367068f;
static char *prayerName[] = {"IMSAK", "SHUBUH", "TERBIT", "DZUHUR", "ASHAR", "TERBENAM", "MAGHRIB", "ISYA'"};
static char *dayName[] = {"AHAD", "SENIN", "SELASA", "RABU", "KAMIS", "JUM'AT", "SABTU"};
static char *hijrName[] = {"MUHARRAM", "SHAFAR", "RAB.ULA", "RAB.TSANI", "JUM.ULA", "JUM.TSANI", "RAJAB", "SYA'BAN", "RAMADHAN", "SYAWAL", "DZULQA'DAH", "DZULHIJJAH" };
static char *javaDay[] = { "WAGE", "KLIWON", "LEGI", "PAHING", "PON" };

// declaration
int prayerScheduleH[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int prayerScheduleM[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t   hD = 0;
uint8_t   hM = 0;
uint16_t  hY = 0;
char *DWDATE = "";
double times[sizeof(TimeName) / sizeof(char *)];

void setup() {
  Serial.begin(115200);

  // Buzzer
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  // Conf
  if (!LittleFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }

  int rtn = I2C_ClearBus(); // clear the I2C bus first before calling Wire.begin()
  if (rtn != 0) {
    Serial.println(F("I2C bus error. Could not clear"));
    if (rtn == 1) {
      Serial.println(F("SCL clock line held low"));
    } else if (rtn == 2) {
      Serial.println(F("SCL clock line held low by slave clock stretch"));
    } else if (rtn == 3) {
      Serial.println(F("SDA data line held low"));
    }
  } else { // bus clear, re-enable Wire, now can start Wire Arduino master
    Wire.begin(5, 4);
  }

  // RTC
  Rtc.Begin();

  // Config
  loadPrayerConfig();
  loadPrayerCompareConfig();
  loadConfig();
  loadSettingsConfig();

  // Server
  wifiInit();
  serverInit();

  // Disp
  Disp.start();
  Disp.setBrightness(settingsConfig.BRIGHTNESS);

  ticker.attach(0.8, flip);
  ticker.attach(1, flip);

  updatePrayerSchedule();
}

void loop() {
  Swap = false;
  handleDraw();

  if (drwMode > 3)
  {
    drwMode = 0;
  }

  if (infoMode > 3)
  {
    infoMode = 1;
  }

  if (Swap)
  {
    Disp.swapBuffers();
  }
}

// ****** Server
void wifiInit() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(settingsConfig.WIFI_SSID, settingsConfig.WIFI_PASSWORD);
}

void serverInit() {
  attachRoute();

  server.begin();
}