#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  dht.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  float nem = dht.readHumidity();
  float sicaklik = dht.readTemperature();

  lcd.setCursor(0, 0);
  lcd.print("Sicaklik: ");
  lcd.print(sicaklik);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Nem: ");
  lcd.print(nem);
  lcd.print("%");

  delay(2000);
}
