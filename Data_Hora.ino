#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>

#define InterfaceLCD 1
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
LiquidCrystal lcd(9, 8, 4, 5, 6, 7);//RS E D4 D5 D6 D7

void setup ()
{
  Serial.begin(57600);
  if (! rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning())
  {
    Serial.println("RTC is NOT running!");
    // ajusta para data e hora de compilacao
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // Ajusta para uma data definida por voce
    //rtc.adjust(DateTime(2017, 12, 27, 11, 14, 0));
  }
  lcd.begin(16, 2);
  delay(2000);
}

void loop ()
{
  if (InterfaceLCD == 1)
    showLCD();
  else
    showSerial();
  Serial.println();
  delay(3000);
}
void showLCD()
{
  DateTime now = rtc.now();
  // ano = now.year();
  lcd.clear();
  //mostra a data
  lcd.print(now.year());
  lcd.write('/');
  lcd.print(now.month());
  lcd.write('/');
  lcd.print(now.day());
  //Mostra as horas
  lcd.setCursor(1, 2);
  lcd.print(now.hour());
  lcd.write('/');
  lcd.print(now.minute());
  lcd.write('/');
  lcd.print(now.second());
}
void showSerial()
{
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}