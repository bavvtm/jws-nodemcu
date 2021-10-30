String fixedTime(int x)
{
  String t = x < 10 ? "0" + String(x) : x > 100 ? "00"
                                                : String(x);
  return t;
}

String fixedPrayerTimes(int hours, int minutes)
{
  int h = hours;
  int m = minutes;

  if (m < 0)
  {
    h = h - 1;
    m = 60 + m;
  }

  return fixedTime(h) + ":" + fixedTime(m);
}

void flip()
{
  if (SH == " ")
  {
    SH = ":";
  }
  else if (SH == ":")
  {
    SH = " ";
  }
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;
 
  for(int i=0; i<= maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  } 
 
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void BuzzerShort() {
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(50);
}