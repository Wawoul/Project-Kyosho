#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define rcPin6 4   // Pin 4 Connected to CH6 of Transmitter;
#define PIN 5      // LED Pin
#define N_LEDS 4

int ch6 = 0;  // Receiver Channel 5 PPM value

////////////////
// CH6 Range
// Left most - 995 (745 - 1245)
// Mid - 1498 (1248 - 1748)
// Far Right - 1986 (1736 - 2235)
///////////////

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(rcPin6, INPUT);
 
  strip.begin();
  //strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(10);
}

void loop() {
  ch6 = pulseIn(rcPin6, HIGH, 20000);  // (Pin, State, Timeout)
  if (ch6 >= 745 && ch6 <= 1245) {
    for (int i = 0; i < N_LEDS; ++i)
      {
      strip.setPixelColor(i, 255, 0, 0); //RED
      }
      strip.show();
    }else

  if (ch6 >= 1246 && ch6 <= 1748) {
    for (int i = 0; i < N_LEDS; ++i)
      {
      strip.setPixelColor(i, 0, 255, 0); //Green
      }
      strip.show();
    }else

  if (ch6 >= 1736 && ch6 <= 2235) {
    for (int i = 0; i < N_LEDS; ++i)
      {
      strip.setPixelColor(i, 0, 0, 255); //Blue
      }
      strip.show();
    }

}
