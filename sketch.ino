#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#include <RTClib.h>

// 0X3C+SA0 - 0x3C or 0x3D
#define DISPLAY_I2C_ADDRESS 0x3C
#define OLED_RST_PIN -1

// Declare an object for the OLED
SSD1306AsciiWire oled;

// Declare an object for the real time clock
RTC_DS1307 rtc;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);

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
}

void loop() {
  DateTime now = rtc.now(); // Get the time from the RTC
  delay(1000);
}