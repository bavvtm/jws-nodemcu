void handleDraw() {
  if(
    infoConfig.UIS_INFO_1 == 0
    and infoConfig.UIS_INFO_2 == 0
    and infoConfig.UIS_INFO_3 == 0
  ) {
    drawMode(0);
  }

  if(infoConfig.UIS_INFO_1 == 1 and infoMode == 1) {
    drawMode(1);
  }
  else if(infoConfig.UIS_INFO_2 == 1 and infoMode == 2) {
    drawMode(2);
  }
  else if(infoConfig.UIS_INFO_3 == 1 and infoMode == 3) {
    drawMode(3);
  }
  else {
    ++infoMode;
  }
}

void drawMode(int i)
{
  Disp.loop();
  char *namaMasjid = infoConfig.UI_NM;
  char *info1 = infoConfig.UI_INFO_1;
  char *info2 = infoConfig.UI_INFO_2;
  char *info3 = infoConfig.UI_INFO_3;

  if (drwMode == 0)
  {
    drawPrayerTime();
    drawClock();
  }
  else if (drwMode == 1)
  {
    drawTextBottomMarque(8, settingsConfig.MARQUE_SPEED, DWDATE, false);
    drawClock();
  }
  else if (drwMode == 2)
  {
    if(infoConfig.UIS_NM == 1) {
      drawTextBottomMarque(8, settingsConfig.MARQUE_SPEED, namaMasjid, false);
      drawClock();
    }
    else {
      ++drwMode;
    }
  }
  else if(drwMode == 3) {
    if(i == 0) {
      ++drwMode;
    }
    else if(i == 1) {
      drawTextBottomMarque(8, settingsConfig.MARQUE_SPEED, info1, true);
      drawClock();
    }
    else if(i == 2) {
      drawTextBottomMarque(8, settingsConfig.MARQUE_SPEED, info2, true);
      drawClock();
    }
    else if(i == 3) {
      drawTextBottomMarque(8, settingsConfig.MARQUE_SPEED, info3, true);
      drawClock();
    }
  }
}

void drawClock()
{
  RtcDateTime now = Rtc.GetDateTime();
  Disp.setFont(EMSans8x16);

  if(now.Hour() == 59 and now.Second() == 59) {
    BuzzerShort();
    Disp.clear();
  }
  Disp.drawFilledRect(41, 16, 0, 0, 0); // Blank Fill
  Disp.drawText(0, 0, fixedTime(now.Hour()));
  Disp.drawText(18, 0, SH);
  Disp.drawText(23, 0, fixedTime(now.Minute()));
}

void drawPrayerTime()
{
  int width = int(Disp.width());
  static uint8_t x;
  static uint8_t separator = 0;
  static uint8_t s = 0;

  static uint16_t lsRn;
  uint16_t Tmr = millis();
  uint8_t c = 41;

  if ((Tmr - lsRn) > 20)
  {
    if (s == 0 and x < width)
    {
      x++;
      lsRn = Tmr;
    }

    // wipe Out
    if (s == 1 and x > 0)
    {
      x--;
      lsRn = Tmr;
    }
  }

  // Fix bug stuck in asyar
  if ((Tmr - lsRn) < -100)
  {
    if (s == 0 and x < width)
    {
      x++;
      lsRn = Tmr;
    }

    // wipe Out
    if (s == 1 and x > 0)
    {
      x--;
      lsRn = Tmr;
    }
  }

  if (x == width)
  {
    s = 1;
  }

  if (x == 0 and s == 1)
  {
    ++separator;
    s = 0;
  }

  if (separator == 8)
  {
    separator = 0;
    ++drwMode;
  }

  drawPrayer(separator);
  Disp.drawFilledRect(x + c, 0, 126, 16, 0);
  Swap = true;
}

void drawTextBottomMarque(int y, uint8_t kecepatan, char *data, boolean isInfoMarque)
{
  static uint32_t lsRn;
  static uint32_t x;
  uint32_t Tmr = millis();

  int width = Disp.width();
  int fullScroll = (Disp.textWidth(data)/2) + width;

  if ((Tmr - lsRn) > kecepatan)
  {
    lsRn = millis();
    if (x == fullScroll)
    {
      x = 0;
      if(isInfoMarque) {
        ++infoMode;
      }
      ++drwMode;
      return;
    }
    else if (x < fullScroll)
    {
      ++x;
    }
  }

  if (x == 1)
  {
    drawTanggal();
  }
  Disp.setFont(Font4x6);
  Disp.drawText(width - x, y, data);
  Swap = true;
}

void drawPrayer(int separator)
{
  Disp.setFont(Font4x6);
  Disp.drawText(42, 0, prayerName[separator]);
  Disp.drawText(42, 8, fixedPrayerTimes(prayerScheduleH[separator], prayerScheduleM[separator]));
}

void drawTanggal()
{
  RtcDateTime now = Rtc.GetDateTime();
  Disp.setFont(Font4x6);

  String day = String(now.Day());
  String month = String(now.Month());
  String year = String(now.Year());

  if (dayOld < now.Day())
  {
    updatePrayerSchedule();
  }

  Disp.drawText(42, 0, day + "-" + month + "-" + year);
}