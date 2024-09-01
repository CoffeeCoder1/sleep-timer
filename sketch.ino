#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#include <Adafruit_NeoPixel.h>
//#include <RTClib.h>
#include <TM1637.h>

// 0X3C+SA0 - 0x3C or 0x3D
#define DISPLAY_I2C_ADDRESS 0x3C
#define OLED_RST_PIN -1

// 4-digit display constants
const int CLK = 15;
const int DIO = 14;

// What pin are the NeoPixels connected to?
#define LED_PIN 1
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 1

// Declare an object for the OLED
SSD1306AsciiWire oled;

// Declare an object for the real time clock
//RTC_DS1307 rtc;

// Declare an object for the 4-digit display
TM1637 tm(CLK, DIO);

// Declare an object for the NeoPixel
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Hours that you want to sleep
const int SLEEP_HOURS = 1;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);

  // Set up i2c
  Wire.begin();
  Wire.setClock(400000L);

#if OLED_RST_PIN >= 0
  oled.begin(&Adafruit128x64, DISPLAY_I2C_ADDRESS, OLED_RST_PIN);
#else // OLED_RST_PIN >= 0
  oled.begin(&Adafruit128x64, DISPLAY_I2C_ADDRESS);
#endif // OLED_RST_PIN >= 0

  oled.setFont(System5x7);
  oled.clear();
  oled.println("Initializing...");

  strip.begin();
  strip.setPixelColor(0, 255, 255, 0);
  strip.show(); // Initialize LEDs

  // Set up 4-digit display
  tm.init();
  tm.set(BRIGHT_TYPICAL);

  // Clear OLED and LEDs
  strip.setPixelColor(0, 0, 0, 0);
  strip.show();
  oled.clear();
}

unsigned int counter = 3600 * SLEEP_HOURS;

void loop() {
  //DateTime now = rtc.now(); // Get the time from the RTC
  delay(1000);

  tm.display(0, (counter / 36000) % 10);
  tm.display(1, (counter / 3600) % 10);
  tm.display(2, (counter % 3600) / 600 % 10);
  tm.display(3, (counter % 3600) / 60 % 10);

  if (counter != 0) {
    counter -= 1;
  } else {
    // Wake up light
    strip.setPixelColor(0, 255, 255, 255);
    strip.show();
  }
}