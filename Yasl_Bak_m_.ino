#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad
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

// Donanım tanımlamaları
#define BUZZER A1
#define LED_ILAC A3
#define LED_YEMEK A4
#define LED_YARDIM A2
#define SERVO_PIN 5

Servo servo;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(BUZZER, OUTPUT);
  pinMode(LED_ILAC, OUTPUT);
  pinMode(LED_YEMEK, OUTPUT);
  pinMode(LED_YARDIM, OUTPUT);

  servo.attach(SERVO_PIN);
  servo.write(0);  // Başlangıç pozisyonu

  lcd.setCursor(0, 0);
  lcd.print("Menuye Hosgeldin!");
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    lcd.clear();
    lcd.setCursor(0, 0);

    // Hepsini önce kapat
    digitalWrite(LED_ILAC, LOW);
    digitalWrite(LED_YEMEK, LOW);
    digitalWrite(LED_YARDIM, LOW);
    noTone(BUZZER);

    switch (key) {
      case '1':
        lcd.print("ILAC SAATI!");
        digitalWrite(LED_ILAC, HIGH);
        tone(BUZZER, 1000, 300);
        break;

      case '2':
        lcd.print("YEMEK ZAMANI!");
        digitalWrite(LED_YEMEK, HIGH);
        tone(BUZZER, 1500, 300);
        break;

      case '3':
        lcd.print("YARDIM CAGIR!");
        digitalWrite(LED_YARDIM, HIGH);
        tone(BUZZER, 700, 1000);
        break;

      case 'A':
        lcd.print("Kutu Aciliyor");
        servo.write(90);
        delay(1000);
        servo.write(0);
        break;

      case '*':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Temizlendi");
        break;

      case '#':
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menuye donuldu");
        break;

      default:
        lcd.print("Gecersiz Tus");
        break;
    }

    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Menuye Hosgeldin!");
  }
}
