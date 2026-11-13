#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>

// & oled
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
// I2C address (usually 0x3C or 0x3D)
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

bool arr[128][64]; // keep track of pixels
byte x = 0;
byte y = 0;
bool state = false;

void setup()
{
  Serial.begin(115200);

  // I2C SDA = 8, SCL = 9
  Wire.begin(8, 9);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
  {
    Serial.println("SSD1306 allocation failed");
    while (1)
      ;
  }

  display.clearDisplay();
  display.display();
  // Serial.println("OLED initialized.");
}

void loop()
{

  if (Serial.available() >= 3)
  {
    x = Serial.read();
    y = Serial.read();
    state = Serial.read();
  }

  if (x == 255)
  {
    memset(arr, 0, sizeof(arr));
    display.clearDisplay();
    display.display();
  }
  else
  {
    arr[x][y] = state;

    if (state)
      display.drawPixel(x, y, SSD1306_WHITE);
    else
      display.drawPixel(x, y, SSD1306_BLACK);

    display.display();
  }
}