#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- OLED I2C ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Joystick pins ---
#define JOY_X  34
#define JOY_Y  35
#define JOY_SW 15

// --- LED pins ---
#define LED_GREEN 26
#define LED_RED   27

// --- Game settings ---
#define GRID 8
#define COLS (SCREEN_WIDTH / GRID)   // 16
#define ROWS (SCREEN_HEIGHT / GRID)  // 8
#define MAX_LEN 60

// --- Snake state ---
int snakeX[MAX_LEN], snakeY[MAX_LEN];
int snakeLen;
int dirX, dirY;
int foodX, foodY;
int score;
bool gameOver;

void spawnFood() {
  foodX = random(0, COLS);
  foodY = random(0, ROWS);
}

void resetGame() {
  snakeLen = 3;
  dirX = 1; dirY = 0;
  score = 0;
  gameOver = false;
  for (int i = 0; i < snakeLen; i++) {
    snakeX[i] = COLS / 2 - i;
    snakeY[i] = ROWS / 2;
  }
  spawnFood();
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
}

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(JOY_SW, INPUT_PULLUP);

  // Start I2C OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true); // halt if display not found
  }

  // Splash screen
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(25, 20);
  display.println("SNAKE GAME");
  display.setCursor(15, 36);
  display.println("Move joystick!");
  display.display();
  delay(2000);

  randomSeed(analogRead(0));
  resetGame();
}

void readJoystick() {
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);

  if (x < 1000 && dirX == 0) { dirX = -1; dirY =  0; } // left
  if (x > 3000 && dirX == 0) { dirX =  1; dirY =  0; } // right
  if (y < 1000 && dirY == 0) { dirX =  0; dirY = -1; } // up
  if (y > 3000 && dirY == 0) { dirX =  0; dirY =  1; } // down
}

void moveSnake() {
  // Shift body
  for (int i = snakeLen - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }
  // Move head
  snakeX[0] += dirX;
  snakeY[0] += dirY;

  // Wrap around edges
  snakeX[0] = (snakeX[0] + COLS) % COLS;
  snakeY[0] = (snakeY[0] + ROWS) % ROWS;

  // Ate food?
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    if (snakeLen < MAX_LEN) snakeLen++;
    score++;
    spawnFood();
    digitalWrite(LED_GREEN, HIGH);
    delay(80);
    digitalWrite(LED_GREEN, LOW);
  }

  // Hit itself?
  for (int i = 1; i < snakeLen; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameOver = true;
    }
  }
}

void drawGame() {
  display.clearDisplay();

  // Draw food
  int fx = foodX * GRID + 2;
  int fy = foodY * GRID + 2;
  display.drawPixel(fx,   fy,   SSD1306_WHITE);
  display.drawPixel(fx+2, fy,   SSD1306_WHITE);
  display.drawPixel(fx+1, fy+1, SSD1306_WHITE);
  display.drawPixel(fx,   fy+2, SSD1306_WHITE);
  display.drawPixel(fx+2, fy+2, SSD1306_WHITE);

  // Draw snake
  for (int i = 0; i < snakeLen; i++) {
    int px = snakeX[i] * GRID;
    int py = snakeY[i] * GRID;
    if (i == 0)
      display.fillRect(px+1, py+1, GRID-2, GRID-2, SSD1306_WHITE); // head
    else
      display.drawRect(px+1, py+1, GRID-2, GRID-2, SSD1306_WHITE); // body
  }

  // Score
  display.setCursor(90, 0);
  display.print("S:");
  display.print(score);

  display.display();
}

void showGameOver() {
  digitalWrite(LED_RED, HIGH);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(25, 18);
  display.println("GAME OVER!");
  display.setCursor(30, 32);
  display.print("Score: ");
  display.println(score);
  display.setCursor(8, 48);
  display.println("Push btn to restart");
  display.display();

  // Wait for joystick button press
  while (digitalRead(JOY_SW) == HIGH) {
    delay(50);
  }
  digitalWrite(LED_RED, LOW);
  resetGame();
}

void loop() {
  if (gameOver) {
    showGameOver();
    return;
  }

  readJoystick();
  moveSnake();
  drawGame();

  delay(150); // game speed — lower number = faster snake
}