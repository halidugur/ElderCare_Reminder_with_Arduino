#include <Wire.h>
#include <DS1302.h>
#include <LiquidCrystal_I2C.h>

// RTC pinleri
#define RST_PIN 8
#define DAT_PIN 7
#define CLK_PIN 6

DS1302 rtc(RST_PIN, DAT_PIN, CLK_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD I2C adresi 0x27, ekran 16x2

void setup() {
  Serial.begin(9600);

  rtc.writeProtect(false);
  rtc.halt(false);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Saat & Tarih Hazir!");
}

void loop() {
  Time t = rtc.time();

  // Saat kısmı
  lcd.setCursor(0, 0);
  if (t.hr < 10) lcd.print("0");
  lcd.print(t.hr);
  lcd.print(":");
  if (t.min < 10) lcd.print("0");
  lcd.print(t.min);
  lcd.print(":");
  if (t.sec < 10) lcd.print("0");
  lcd.print(t.sec);

  // Tarih kısmı
  lcd.setCursor(0, 1);
  if (t.date < 10) lcd.print("0");
  lcd.print(t.date);
  lcd.print("/");
  if (t.mon < 10) lcd.print("0");
  lcd.print(t.mon);
  lcd.print("/");
  lcd.print(t.yr);

  delay(1000);  // Her saniye ekranı güncelle
}
