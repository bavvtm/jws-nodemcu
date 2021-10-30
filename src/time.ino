void updatePrayerSchedule()
{
  RtcDateTime now = Rtc.GetDateTime();
  int year = now.Year();
  int month = now.Month();
  int day = now.Day();

  hijrDateCalculation(year, month, day, 0);

  // RRM
  char locBuff[20];
  static char out[45];
  sprintf(out, "%s %s, %02d-%02d-%04d %02d %s %dH\0", dayName[now.DayOfWeek()], javaDay[javaTimeCalculation() % 5], now.Day(), now.Month(), now.Year(), hD, hijrName[hM], hY);
  DWDATE = out;

  // handler update
  dayOld = day;

  set_calc_method(Karachi);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(prayerConfig.L_FA);
  set_isha_angle(prayerConfig.L_FE);

  get_prayer_times(year, month, day, prayerConfig.L_LA, prayerConfig.L_LO, prayerConfig.L_TZ, times);

  for (int i = 0; i < sizeof(times) / sizeof(double); i++)
  {
    int hours, minutes;
    get_float_time_parts(times[i], hours, minutes);

    if (i < 8)
    {
      prayerScheduleH[i + 1] = hours;
      if (i == 0)
      {
        prayerScheduleM[i + 1] = minutes + prayerCompare.COR_SHUBUH;
      }
      if (i == 1)
      {
        prayerScheduleM[i + 1] = minutes + prayerCompare.COR_TERBIT;
      }
      if (i == 2)
      {
        prayerScheduleM[i + 1] = minutes + prayerCompare.COR_DZUHUR;
      }
      if (i == 3)
      {
        prayerScheduleM[i + 1] = minutes + prayerCompare.COR_ASHAR;
      }
      if (i == 4)
      {
        prayerScheduleM[i + 1] = minutes + prayerCompare.COR_TERBENAM;
      }
      if (i == 5)
      {
        prayerScheduleM[i + 1] = minutes + prayerCompare.COR_MAGHRIB;
      }
      if (i == 6)
      {
        prayerScheduleM[i + 1] = minutes + prayerCompare.COR_ISYA;
      }
    }

    prayerScheduleH[0] = prayerScheduleH[1];
    prayerScheduleM[0] = (prayerScheduleM[1] - 10) + prayerCompare.COR_IMSAK;
  }
}

int javaTimeCalculation()
{
  RtcDateTime now = Rtc.GetDateTime();
  int d = now.Day();
  int m = now.Month();
  int y = now.Year();
  int hb[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
  int ht = (y - 1970) * 365 - 1;
  int hs = hb[m - 1] + d;
  int kab = 0;
  int i;
  if (y % 4 == 0)
  {
    if (m > 2)
    {
      hs++;
    }
  }
  for (i = 1970; i < y; i++)
  {
    if (i % 4 == 0)
    {
      kab++;
    }
  }
  return (ht + hs + kab);
}

// Hijr Date Calculation
long Days(uint16_t Y, uint8_t M, uint8_t D)
{
  if (M < 3)
  {
    Y -= 1;
    M += 12;
  }
  Y = Y - 2000;
  long ndays = floor(365.25 * Y) + floor(30.6001 * (M + 1)) + floor(Y / 100) + floor(Y / 400) + D + 196;
  //long ndays= d1 + d2 - A + B + D + 196;
  return ndays;
}

long DaysHijri(uint16_t Y, uint8_t M, uint8_t D)
{
  Y = Y - 1420;
  long hari = floor(29.5 * M - 28.999) + floor(lunarY * Y) + D;
  return hari;
}

void hijrDateCalculation(uint16_t Y, uint8_t M, uint8_t D, uint8_t cor)
{
  long nday = Days(Y, M, D) + cor;

  long tahun = floor(nday / lunarY) + 1420;
  long bulan = 1;
  long harike = 1;
  while (DaysHijri(tahun, bulan, 1) <= nday)
  {
    tahun++;
  };
  tahun--;
  while (DaysHijri(tahun, bulan, 1) <= nday)
  {
    bulan++;
  };
  bulan--;
  harike = 1 + nday - DaysHijri(tahun, bulan, 1);
  if (bulan == 13)
  {
    bulan = 12;
    harike += 29;
  };

  hD = harike;
  hM = bulan;
  hY = tahun;
}