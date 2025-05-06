#include <Wire.h>
#include <DS1302.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>
#include <DHT.h>

#define RST_PIN 8
#define DAT_PIN 7
#define CLK_PIN 6

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

DS1302 rtc(RST_PIN, DAT_PIN, CLK_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {26, 27, 28, 29};
byte colPins[COLS] = {22, 23, 24, 25};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

#define BUZZER A1
#define LED_ILAC A3
#define LED_YEMEK A4
#define LED_YARDIM A2
#define SERVO_PIN 5

Servo servo;
bool alarmTriggered = false;

unsigned long lastUpdateTime = 0;
int ekranDurum = 0;

void setup() {
  Serial.begin(9600);

  rtc.writeProtect(false);
  rtc.halt(false);
  dht.begin();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Sistem Basladi!");

  pinMode(BUZZER, OUTPUT);
  pinMode(LED_ILAC, OUTPUT);
  pinMode(LED_YEMEK, OUTPUT);
  pinMode(LED_YARDIM, OUTPUT);

  servo.attach(SERVO_PIN);
  servo.write(0);
  delay(500);
  servo.detach();

  delay(2000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();
  Time t = rtc.time();

  if (millis() - lastUpdateTime > ((ekranDurum == 0) ? 5000 : 2000)) {
    lcd.clear();

    if (ekranDurum == 0) {
      lcd.setCursor(0, 0);
      lcd.print("Saat: ");
      if (t.hr < 10) lcd.print("0");
      lcd.print(t.hr);
      lcd.print(":");
      if (t.min < 10) lcd.print("0");
      lcd.print(t.min);
      lcd.print(":");
      if (t.sec < 10) lcd.print("0");
      lcd.print(t.sec);

      lcd.setCursor(0, 1);
      lcd.print("Sicaklik: ");
      lcd.print(dht.readTemperature());
      lcd.print("C");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Tarih:");
      if (t.date < 10) lcd.print("0");
      lcd.print(t.date);
      lcd.print("/");
      if (t.mon < 10) lcd.print("0");
      lcd.print(t.mon);
      lcd.print("/");
      lcd.print(t.yr);

      lcd.setCursor(0, 1);
      lcd.print("Nem: ");
      lcd.print(dht.readHumidity());
      lcd.print("%");
    }

    ekranDurum = (ekranDurum + 1) % 2;
    lastUpdateTime = millis();
  }

  if (t.hr == 21 && t.min == 43 && !alarmTriggered) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ILAC ZAMANI!");
    digitalWrite(LED_ILAC, HIGH);
    tone(BUZZER, 1000, 1000);
    servo.attach(SERVO_PIN);
    servo.write(90);
    delay(1000);
    servo.write(0);
    delay(500);
    servo.detach();
    alarmTriggered = true;
    delay(1000);
  }

  if (key) {
    lcd.clear();
    lcd.setCursor(0, 0);
    digitalWrite(LED_ILAC, LOW);
    digitalWrite(LED_YEMEK, LOW);
    digitalWrite(LED_YARDIM, LOW);
    noTone(BUZZER);

    switch (key) {
      case '1':
        lcd.print("Ilac Hatirlatma");
        digitalWrite(LED_ILAC, HIGH);
        tone(BUZZER, 1000, 500);
        servo.attach(SERVO_PIN);
        servo.write(300);
        delay(10000);
        servo.write(20);
        delay(5000);
        servo.detach();
        break;
      case '2':
        lcd.print("Yemek Hatirlatma");
        digitalWrite(LED_YEMEK, HIGH);
        tone(BUZZER, 1500, 500);
        break;
      case '3':
        lcd.print("Yardim Cagrisi");
        digitalWrite(LED_YARDIM, HIGH);
        tone(BUZZER, 500, 1000);
        break;
      case 'A':
        lcd.print("Kutu Aciliyor");
        servo.attach(SERVO_PIN);
        servo.write(360);
        delay(1000);
        servo.write(20);
        delay(500);
        servo.detach();
        break;
      case '*':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ekran Temizlendi");
        break;
      case '#':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menuye Donuldu");
        break;
      default:
        lcd.print("Gecersiz Tus!");
        break;
    }
    delay(2000);
    lcd.clear();
  }

  delay(50);
}
