#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

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

struct Point {
  int x;
  int y;
};

#define MAX_LENGTH 32
Point snake[MAX_LENGTH];
int snakeLength = 1;
char direction = 'R';
Point star = {5, 1};
bool playing = false;
unsigned long lastMoveTime = 0;
int score = 0;

void resetGame() {
  snakeLength = 1;
  snake[0] = {0, 0};
  direction = 'R';
  score = 0;
  star = {random(0, 16), random(0, 2)};
  lcd.clear();
  lcd.setCursor(star.x, star.y);
  lcd.print("*");
}

void moveSnake() {
  Point newHead = snake[0];
  if (direction == 'U') newHead.y--;
  else if (direction == 'D') newHead.y++;
  else if (direction == 'L') newHead.x--;
  else if (direction == 'R') newHead.x++;

  if (newHead.x < 0 || newHead.x >= 16 || newHead.y < 0 || newHead.y >= 2) {
    playing = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Game Over!");
    lcd.setCursor(0, 1);
    lcd.print("Skor: ");
    lcd.print(score);
    return;
  }

  for (int i = 0; i < snakeLength; i++) {
    if (snake[i].x == newHead.x && snake[i].y == newHead.y) {
      playing = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Game Over!");
      lcd.setCursor(0, 1);
      lcd.print("Skor: ");
      lcd.print(score);
      return;
    }
  }

  for (int i = snakeLength; i > 0; i--) {
    snake[i] = snake[i - 1];
  }
  snake[0] = newHead;
  if (newHead.x == star.x && newHead.y == star.y) {
    snakeLength++;
    if (snakeLength > MAX_LENGTH) snakeLength = MAX_LENGTH;
    score++;
    star = {random(0, 16), random(0, 2)};
  } else {
    Point tail = snake[snakeLength];
    lcd.setCursor(tail.x, tail.y);
    lcd.print(" ");
  }

  lcd.setCursor(star.x, star.y);
  lcd.print("*");

  for (int i = 0; i < snakeLength; i++) {
    lcd.setCursor(snake[i].x, snake[i].y);
    lcd.print("O");
  }
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SNAKE BASLAT: D");
  randomSeed(analogRead(0));
}

void loop() {
  char key = keypad.getKey();
  if (key == 'D') {
    if (!playing) {
      resetGame();
      playing = true;
      delay(500);
    } else {
      playing = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Oyun Durdu.");
      delay(1000);
      lcd.clear();
    }
  }
  if (!playing) return;

  if (key == '2') direction = 'U';
  else if (key == '4') direction = 'L';
  else if (key == '6') direction = 'R';
  else if (key == '8') direction = 'D';

  if (millis() - lastMoveTime > 500) {
    moveSnake();
    lastMoveTime = millis();
  }
}
