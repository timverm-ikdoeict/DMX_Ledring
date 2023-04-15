#include <Arduino.h>
#include <FastLED.h>
#include <DMXSerial.h>

// How many leds in your strip?
#define NUM_LEDS 16

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 5
//#define CLOCK_PIN 13


// Define the array of leds
CRGB leds[NUM_LEDS];
// first DMX channel
#define DMXSTART 463
// number of DMX channels used
#define DMXLENGTH 3

byte r,g,b;
CRGB currentColor=CRGB::DarkBlue;

void setup() { 
  DMXSerial.init(DMXProbe);
  DMXSerial.maxChannel(DMXLENGTH); // after 3 channels, the onUpdate will be called when new data arrived.

    // Uncomment/edit one of the following lines for your leds arrangement.
    // ## Clockless types ##
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    // FastLED.addLeds<SM16703, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1829, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1812, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS1904, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS2903, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<WS2852, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<GS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<SK6812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<SK6822, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<APA106, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<PL9823, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<SK6822, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2813, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2811_400, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<GE8822, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<LPD1886, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<LPD1886_8BIT, DATA_PIN, RGB>(leds, NUM_LEDS);
    // ## Clocked (SPI) types ##
    // FastLED.addLeds<LPD6803, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2803, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    // FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
}

void receiveDMXcolor(){
  if (DMXSerial.receive()) {
    r = DMXSerial.read(DMXSTART+0);
    g = DMXSerial.read(DMXSTART+1);
    b = DMXSerial.read(DMXSTART+2);
    currentColor=CRGB( r, g, b);
  } 
}

const int delay_between_blinks=6000;


const byte amount=32;//the leds of the ring will fade from bright (color controlled by DMX) to black in steps of 32. 
const int delay_between_blink_steps=8;//total duration of blink, including fade, is 128*(this setting). 8*128=1024 milliseconds

long lastBlink=millis();

void loop() { 
  
  // Turn the LED on, then pause
  for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = currentColor;
  FastLED.show();
  
  //fade the leds out, starting on top and bottom of the ring
  //this implementation is fixed for a ledring of 16 leds
  if(millis()-lastBlink>delay_between_blinks){
    lastBlink=millis();
    for (int i = 0; i < 128; i++){
      leds[7].fadeToBlackBy(amount);
      leds[15].fadeToBlackBy(amount);
      if(i>8){
        leds[6].fadeToBlackBy(amount);
        leds[8].fadeToBlackBy(amount);
        leds[0].fadeToBlackBy(amount);
        leds[14].fadeToBlackBy(amount);
      }
      if(i>16){
        leds[5].fadeToBlackBy(amount);
        leds[9].fadeToBlackBy(amount);
        leds[1].fadeToBlackBy(amount);
        leds[13].fadeToBlackBy(amount);
      }
      if(i>24){
        leds[4].fadeToBlackBy(amount);
        leds[10].fadeToBlackBy(amount);
        leds[2].fadeToBlackBy(amount);
        leds[12].fadeToBlackBy(amount);
      }
      if(i>32){
        leds[3].fadeToBlackBy(amount);
        leds[11].fadeToBlackBy(amount);
      }
      FastLED.show();
      delay(8);
      receiveDMXcolor();
    }
  }

  receiveDMXcolor();
}