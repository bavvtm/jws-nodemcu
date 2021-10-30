void loadPrayerConfig()
{
  File configFile = LittleFS.open("/prayerconfig.json", "r");
  if (!configFile)
  {
    Serial.println("Failed Open Config file");
  }

  size_t size = configFile.size();
  if (size > 1024)
  {
    Serial.println("Config Size To Large");
  }

  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error)
  {
    Serial.println("Failed Parse Config File");
    return;
  }

  prayerConfig.L_LA = doc["latitude"].as<float>();
  prayerConfig.L_LO = doc["longitude"].as<float>();
  prayerConfig.L_TZ = doc["timezone"].as<int>();
  prayerConfig.L_FA = doc["fajr_angle"].as<int>();
  prayerConfig.L_FE = doc["isha_angle"].as<int>();

  configFile.close();
}

void loadPrayerCompareConfig()
{
  File configFile = LittleFS.open("/prayercompare.json", "r");
  if (!configFile)
  {
    Serial.println("Failed Open Config file");
  }

  size_t size = configFile.size();
  if (size > 1024)
  {
    Serial.println("Config Size To Large");
  }

  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error)
  {
    Serial.println("Failed Parse Config File");
    return;
  }

  prayerCompare.COR_IMSAK = doc["imsak"].as<int>();
  prayerCompare.COR_SHUBUH = doc["shubuh"].as<int>();
  prayerCompare.COR_TERBIT = doc["terbit"].as<int>();
  prayerCompare.COR_DZUHUR = doc["dzuhur"].as<int>();
  prayerCompare.COR_ASHAR = doc["ashar"].as<int>();
  prayerCompare.COR_TERBENAM = doc["terbenam"].as<int>();
  prayerCompare.COR_MAGHRIB = doc["maghrib"].as<int>();
  prayerCompare.COR_ISYA = doc["isya"].as<int>();

  configFile.close();
}

void loadConfig()
{
  File configFile = LittleFS.open("/infoconfig.json", "r");
  if (!configFile)
  {
    Serial.println("Failed Open Config file");
  }

  size_t size = configFile.size();
  if (size > 1024)
  {
    Serial.println("Config Size To Large");
  }

  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error)
  {
    Serial.println("Failed Parse Config File");
    return;
  }

  infoConfig.UIS_NM = doc["s_mosque_name"].as<int>();
  infoConfig.UIS_INFO_1 = doc["s_info_1"].as<int>();
  infoConfig.UIS_INFO_2 = doc["s_info_2"].as<int>();
  infoConfig.UIS_INFO_3 = doc["s_info_3"].as<int>();
  strlcpy(infoConfig.UI_NM, doc["mosque_name"], sizeof(infoConfig.UI_NM));
  strlcpy(infoConfig.UI_INFO_1, doc["info_1"], sizeof(infoConfig.UI_INFO_1));
  strlcpy(infoConfig.UI_INFO_2, doc["info_2"], sizeof(infoConfig.UI_INFO_2));
  strlcpy(infoConfig.UI_INFO_3, doc["info_3"], sizeof(infoConfig.UI_INFO_3));

  configFile.close();
}

void loadSettingsConfig()
{
  File configFile = LittleFS.open("/settingsconfig.json", "r");
  if (!configFile)
  {
    Serial.println("Failed Open Config file");
  }

  size_t size = configFile.size();
  if (size > 1024)
  {
    Serial.println("Config Size To Large");
  }

  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error)
  {
    Serial.println("Failed Parse Config File");
    return;
  }

  strlcpy(settingsConfig.WIFI_SSID, doc["wifi_name"], sizeof(settingsConfig.WIFI_SSID));
  strlcpy(settingsConfig.WIFI_PASSWORD, doc["wifi_password"], sizeof(settingsConfig.WIFI_PASSWORD));
  strlcpy(settingsConfig.USERNAME, doc["login_username"], sizeof(settingsConfig.USERNAME));
  strlcpy(settingsConfig.PASSWORD, doc["login_password"], sizeof(settingsConfig.PASSWORD));
  settingsConfig.MARQUE_SPEED = doc["marque_speed"].as<int>();
  settingsConfig.BRIGHTNESS = doc["brightness"].as<int>();

  configFile.close();
}