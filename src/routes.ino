void attachRoute()
{
  // APIs Route
  APIsRoute();
}

// ******
void APIsRoute()
{
  /** GET Methods */
  server.on("/api/restart", HTTP_GET, [](AsyncWebServerRequest *request)
            { ESP.restart(); });

  server.on("/api/infoconfig.json", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/infoconfig.json", "application/json"); });

  server.on("/api/settingsconfig.json", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/settingsconfig.json", "application/json"); });

  server.on("/api/prayercompare.json", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/prayercompare.json", "application/json"); });

  server.on("/api/prayerconfig.json", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/prayerconfig.json", "application/json"); });

  /** POST Methods */
  server.on(
      "/api/login",
      HTTP_POST,
      [](AsyncWebServerRequest *request)
      {
        int params = request->params();
        String username = "";
        String password = "";

        for (int i = 0; i < params; i++)
        {
          AsyncWebParameter *p = request->getParam(i);
          if (p->name().equals("username"))
          {
            username = p->value();
          }
          else if (p->name().equals("password"))
          {
            password = p->value();
          }
        }

        if (username.equals(String(settingsConfig.USERNAME)) && password.equals(String(settingsConfig.PASSWORD)))
        {
          String resp = "{\"status\":true,\"url\":\"/api/login\",\"message\":\"Login Success\"}";
          request->send(200, "application/json", resp);
        }
        else
        {
          String resp = "{\"status\":false,\"url\":\"/api/login\",\"message\":\"Login Failure\"}";
          request->send(200, "application/json", resp);
        }
      });

  server.on(
      "/api/set_info",
      HTTP_POST,
      [](AsyncWebServerRequest *request)
      {
        int params = request->params();
        int UIS_NM = infoConfig.UIS_NM;
        int UIS_INFO_1 = infoConfig.UIS_INFO_1;
        int UIS_INFO_2 = infoConfig.UIS_INFO_2;
        int UIS_INFO_3 = infoConfig.UIS_INFO_3;
        char *UI_NM = infoConfig.UI_NM;
        char *UI_INFO_1 = infoConfig.UI_INFO_1;
        char *UI_INFO_2 = infoConfig.UI_INFO_2;
        char *UI_INFO_3 = infoConfig.UI_INFO_3;

        for (int i = 0; i < params; i++)
        {
          AsyncWebParameter *p = request->getParam(i);
          if (p->name().equals("show_mosque_name"))
          {
            UIS_NM = p->value().toInt();
          }
          else if (p->name().equals("show_info_1"))
          {
            UIS_INFO_1 = p->value().toInt();
          }
          else if (p->name().equals("show_info_2"))
          {
            UIS_INFO_2 = p->value().toInt();
          }
          else if (p->name().equals("show_info_3"))
          {
            UIS_INFO_3 = p->value().toInt();
          }
          else if (p->name().equals("text_mosque_name"))
          {
            char buf[100];
            p->value().toCharArray(buf, 100);
            UI_NM = buf;
          }
          else if (p->name().equals("text_info_1"))
          {
            char buf[512];
            p->value().toCharArray(buf, 512);
            UI_INFO_1 = buf;
          }
          else if (p->name().equals("text_info_2"))
          {
            char buf[512];
            p->value().toCharArray(buf, 512);
            UI_INFO_2 = buf;
          }
          else if (p->name().equals("text_info_3"))
          {
            char buf[512];
            p->value().toCharArray(buf, 512);
            UI_INFO_3 = buf;
          }
        }

        DynamicJsonDocument doc(1024);
        doc["s_mosque_name"] = UIS_NM;
        doc["s_info_1"] = UIS_INFO_1;
        doc["s_info_2"] = UIS_INFO_2;
        doc["s_info_3"] = UIS_INFO_3;
        doc["mosque_name"] = UI_NM;
        doc["info_1"] = UI_INFO_1;
        doc["info_2"] = UI_INFO_2;
        doc["info_3"] = UI_INFO_3;

        File configFile = LittleFS.open("/infoconfig.json", "w");
        if (!configFile)
        {
          Serial.println("Failed Open Config file");
        }
        serializeJson(doc, configFile);
        configFile.close();
        loadConfig();

        String resp = "{\"status\":true,\"url\":\"/api/set_info\",\"message\":\"Success set info\"}";
        request->send(200, "application/json", resp);
        BuzzerShort();
      });

  server.on(
      "/api/set_settings",
      HTTP_POST,
      [](AsyncWebServerRequest *request)
      {
        int params = request->params();
        char *WIFI_SSID = settingsConfig.WIFI_SSID;
        char *WIFI_PASSWORD = settingsConfig.WIFI_PASSWORD;
        char *USERNAME = settingsConfig.USERNAME;
        char *PASSWORD = settingsConfig.PASSWORD;
        int BRIGHTNESS = settingsConfig.BRIGHTNESS;
        int MARQUE_SPEED = settingsConfig.MARQUE_SPEED;

        for (int i = 0; i < params; i++)
        {
          AsyncWebParameter *p = request->getParam(i);
          if (p->name().equals("brightness"))
          {
            BRIGHTNESS = p->value().toInt();
          }
          else if (p->name().equals("marque_speed"))
          {
            MARQUE_SPEED = p->value().toInt();
          }
          else if (p->name().equals("wifi_ssid"))
          {
            char buf[512];
            p->value().toCharArray(buf, 512);
            WIFI_SSID = buf;
          }
          else if (p->name().equals("wifi_password"))
          {
            char buf[512];
            p->value().toCharArray(buf, 512);
            WIFI_PASSWORD = buf;
          }
          else if (p->name().equals("login_username"))
          {
            char buf[512];
            p->value().toCharArray(buf, 512);
            USERNAME = buf;
          }
          else if (p->name().equals("login_password"))
          {
            char buf[512];
            p->value().toCharArray(buf, 512);
            PASSWORD = buf;
          }
        }

        DynamicJsonDocument doc(1024);
        doc["wifi_name"] = WIFI_SSID;
        doc["wifi_password"] = WIFI_PASSWORD;
        doc["login_username"] = USERNAME;
        doc["login_password"] = PASSWORD;
        doc["brightness"] = BRIGHTNESS;
        doc["marque_speed"] = MARQUE_SPEED;

        File configFile = LittleFS.open("/settingsconfig.json", "w");
        if (!configFile)
        {
          Serial.println("Failed Open Config file");
        }
        serializeJson(doc, configFile);
        configFile.close();
        loadConfig();
        Disp.setBrightness(BRIGHTNESS);

        String resp = "{\"status\":true,\"url\":\"/api/set_settings\",\"message\":\"Success set setting\"}";
        request->send(200, "application/json", resp);
        BuzzerShort();
      });

  // Set prayer config
  server.on(
      "/api/set_prayer_config",
      HTTP_POST,
      [](AsyncWebServerRequest *request) {
        int params = request->params();
        float L_LA = prayerConfig.L_LA;
        float L_LO = prayerConfig.L_LO;
        int L_TZ = prayerConfig.L_TZ;
        int L_FA = prayerConfig.L_FA;
        int L_FE = prayerConfig.L_FE;

        for (int i = 0; i < params; i++)
        {
          AsyncWebParameter *p = request->getParam(i);
          if (p->name().equals("latitude"))
          {
            L_LA = p->value().toFloat();
          }
          else if (p->name().equals("longitude"))
          {
            L_LO = p->value().toFloat();
          }
          else if (p->name().equals("timezone"))
          {
            L_TZ = p->value().toInt();
          }
          else if (p->name().equals("fajr_angle"))
          {
            L_FA = p->value().toInt();
          }
          else if (p->name().equals("isha_angle"))
          {
            L_FE = p->value().toInt();
          }
        }

        DynamicJsonDocument doc(1024);
        doc["latitude"] = L_LA;
        doc["longitude"] = L_LO;
        doc["timezone"] = L_TZ;
        doc["fajr_angle"] = L_FA;
        doc["isha_angle"] = L_FE;

        File configFile = LittleFS.open("/prayerconfig.json", "w");
        if (!configFile)
        {
          Serial.println("Failed Open Config file");
        }
        serializeJson(doc, configFile);
        configFile.close();
        loadConfig();
        updatePrayerSchedule();

        String resp = "{\"status\":true,\"url\":\"/api/set_prayer_config\",\"message\":\"Success set prayer location config\"}";
        request->send(200, "application/json", resp);
        BuzzerShort();
      });

  // Set prayer time comparation
  server.on(
      "/api/set_prayer_comparation",
      HTTP_POST,
      [](AsyncWebServerRequest *request) {
        int params = request->params();
        int COR_IMSAK = prayerCompare.COR_IMSAK;
        int COR_SHUBUH = prayerCompare.COR_SHUBUH;
        int COR_TERBIT = prayerCompare.COR_TERBIT;
        int COR_DZUHUR = prayerCompare.COR_DZUHUR;
        int COR_ASHAR = prayerCompare.COR_ASHAR;
        int COR_TERBENAM = prayerCompare.COR_TERBENAM;
        int COR_MAGHRIB = prayerCompare.COR_MAGHRIB;
        int COR_ISYA = prayerCompare.COR_ISYA;

        for (int i = 0; i < params; i++)
        {
          AsyncWebParameter *p = request->getParam(i);
          if (p->name().equals("imsak"))
          {
            COR_IMSAK = p->value().toInt();
          }
          else if (p->name().equals("shubuh"))
          {
            COR_SHUBUH = p->value().toInt();
          }
          else if (p->name().equals("terbit"))
          {
            COR_TERBIT = p->value().toInt();
          }
          else if (p->name().equals("dzuhur"))
          {
            COR_DZUHUR = p->value().toInt();
          }
          else if (p->name().equals("ashar"))
          {
            COR_ASHAR = p->value().toInt();
          }
          else if (p->name().equals("terbenam"))
          {
            COR_TERBENAM = p->value().toInt();
          }
          else if (p->name().equals("maghrib"))
          {
            COR_MAGHRIB = p->value().toInt();
          }
          else if (p->name().equals("isya"))
          {
            COR_ISYA = p->value().toInt();
          }
        }

        DynamicJsonDocument doc(1024);
        doc["imsak"] = COR_IMSAK;
        doc["shubuh"] = COR_SHUBUH;
        doc["terbit"] = COR_TERBIT;
        doc["dzuhur"] = COR_DZUHUR;
        doc["ashar"] = COR_ASHAR;
        doc["terbenam"] = COR_TERBENAM;
        doc["maghrib"] = COR_MAGHRIB;
        doc["isya"] = COR_ISYA;

        File configFile = LittleFS.open("/prayercompare.json", "w");
        if (!configFile)
        {
          Serial.println("Failed Open Config file");
        }
        serializeJson(doc, configFile);
        configFile.close();
        loadConfig();
        updatePrayerSchedule();

        String resp = "{\"status\":true,\"url\":\"/api/set_prayer_comparation\",\"message\":\"Success set prayer time comparation\"}";
        request->send(200, "application/json", resp);
        BuzzerShort();
      });

  // Set Waktu
  server.on(
      "/api/set_time",
      HTTP_POST,
      [](AsyncWebServerRequest *request)
      {
        int second = 0;
        int minute = 0;
        int hour = 0;
        int day = 0;
        int month = 0;
        int year = 0;

        int params = request->params();
        for (int i = 0; i < params; i++)
        {
          AsyncWebParameter *p = request->getParam(i);
          if (p->name().equals("second"))
          {
            second = p->value().toInt();
          }
          else if (p->name().equals("minute"))
          {
            minute = p->value().toInt();
          }
          else if (p->name().equals("hour"))
          {
            hour = p->value().toInt();
          }
          else if (p->name().equals("day"))
          {
            day = p->value().toInt();
          }
          else if (p->name().equals("month"))
          {
            month = p->value().toInt();
          }
          else if (p->name().equals("year"))
          {
            year = p->value().toInt();
          }
        }

        RtcDateTime now = Rtc.GetDateTime();
        if (second == 0)
        {
          second = now.Second();
        }
        if (minute == 0)
        {
          minute = now.Minute();
        }
        if (hour == 0)
        {
          hour = now.Hour();
        }
        if (day == 0)
        {
          day = now.Day();
        }
        if (month == 0)
        {
          month = now.Month();
        }
        if (year == 0)
        {
          year = now.Year();
        }
        Rtc.SetDateTime(RtcDateTime(year, month, day, hour, minute, second));

        String resp = "{\"status\":true,\"url\":\"/api/set_time\",\"message\":\"Success set clock\"}";
        request->send(200, "application/json", resp);
        BuzzerShort();
      });
}