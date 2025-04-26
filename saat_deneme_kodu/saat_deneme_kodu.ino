#include <DS1302.h>

// DS1302 pin tanımları
const int RST_PIN = 8;
const int DAT_PIN = 7;
const int CLK_PIN = 6;

DS1302 rtc(RST_PIN, DAT_PIN, CLK_PIN);

void setup() {
  Serial.begin(9600);

  rtc.writeProtect(false);
  rtc.halt(false);

  // 🔥 Burada saat ve tarihi ayarlıyoruz:
  Time t(2025, 4, 26, 19, 23, 0, 0); 
  // (Yıl, Ay, Gün, Saat, Dakika, Saniye, Haftanın günü (0=Pazar))

  rtc.time(t);

  Serial.println("Saat ve Tarih Ayarlandi!");
}

void loop() {
  Time t = rtc.time();

  Serial.print("Saat: ");
  Serial.print(t.hr);
  Serial.print(":");
  Serial.print(t.min);
  Serial.print(":");
  Serial.print(t.sec);

  Serial.print(" Tarih: ");
  Serial.print(t.date);
  Serial.print("/");
  Serial.print(t.mon);
  Serial.print("/");
  Serial.print(t.yr);

  Serial.println();

  delay(1000);
}
