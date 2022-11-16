#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <Adafruit_NeoPixel.h>

// Var wifi
const char    *ssid = "your wifi";
const char    *password = "your wifi passwords";

const char    *a_ssid = "RGB testy";
const char    *a_password = "1234567890";

AsyncWebServer server(80);

// Var led
int           pin = 27;                  // Data GPIO
int           pixelFormat = NEO_GRB + NEO_KHZ800;
uint16_t      pixelNumber = 360;        // Total Number of Pixels

unsigned long timePrevious = 0;         // Previous Time Millis
unsigned long timeCurrent = 0;          // Current Time Millis
uint16_t      patternStep = 0;          // Current pattern step, set to 0 by switching pattern
int           patternDelay = 50;        // Delay Pattern Interval (ms)

// legacy
int           pixelQueue = 0;           // Pattern Pixel Queue
int           pixelCycle = 0;           // Pattern Pixel Cycle
uint16_t      pixelCurrent = 0;         // Pattern Current Pixel Number



Adafruit_NeoPixel strip(pixelNumber, pin, pixelFormat);

int           patternCurrent = 0;       // Current Pattern Number
bool          powerSwitch = 0;
bool          toShutdown = 0;

// Initialize Pattern Parameters
#define PARAM_SIZE    5
#define RAINBOW_RANGE 256
#define FIRE_NUMBER   30
#define FIRE_RADIUS   10

#define PAT_FILL      0
#define PAT_BLINK     1
#define PAT_LIGHT     2
//#define PAT_BLK_RAIN  3 //Legacy
#define PAT_WIPE      4
#define PAT_POLICE    5
#define PAT_SNAKE     6
#define PAT_FIREWORK  7



uint32_t      pattern0[PARAM_SIZE] = {50, strip.Color(127, 127, 127), 0};
uint32_t      pattern1[PARAM_SIZE] = {50, strip.Color(127, 127, 127), 3, 0};
uint32_t      pattern2[PARAM_SIZE] = {50, strip.Color(255, 255, 255), 100};
uint32_t      pattern3[PARAM_SIZE] = {50, 3, 256, 100};                         // Legacy
uint32_t      pattern4[PARAM_SIZE] = {30, strip.Color(127, 127, 127), 0};
uint32_t      pattern5[PARAM_SIZE] = {500, strip.Color(255, 0, 0), strip.Color(0, 0, 255)};
uint32_t      pattern6[PARAM_SIZE] = {50, strip.Color(127, 127, 127), 5, 12, 0};
uint32_t      pattern7[PARAM_SIZE] = {80, strip.Color(127, 127, 127), 2, 6, 0};

uint16_t      arrayfirework[FIRE_RADIUS][FIRE_NUMBER];

uint32_t*     arrayParameters[] = {pattern0, pattern1, pattern2, pattern3, pattern4, pattern5, pattern6, pattern7};


void setup()
{
  //----------------------------------------------------Serial
  Serial.begin(115200);
  Serial.println("\n");

  //----------------------------------------------------SPIFFS
  initSPIFFS();
  //----------------------------------------------------WIFI
  initWifi();
  //initAccessPoint();
  //----------------------------------------------------SERVER
  initServer();
  //----------------------------------------------------RGB
  strip.begin();
  strip.show();
}

void loop()
{
  if(powerSwitch){
    // Check if time is expired
    timeCurrent = millis();    
    if(timeCurrent - timePrevious >= patternDelay) {
      timePrevious = timeCurrent;

      // Update current pattern
      switch (patternCurrent) {
        case PAT_WIPE:
          colorWipe();
          break;
        case PAT_LIGHT:
          light();
          break;
        case PAT_BLINK:
          blink();
          break;
        case PAT_POLICE:
          police();
          break;
        case PAT_SNAKE:
          snake();
          break;
        case PAT_FIREWORK:
          firework();
          break;
        default:
          colorFlat();
          break;
      }
    }
  }
  if(toShutdown){
    strip.fill(strip.Color(0, 0, 0));
    strip.show();
    toShutdown = 0;
  }
}
