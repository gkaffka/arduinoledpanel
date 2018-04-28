#include <FastLED.h>
#define NUM_LEDS 256
#define DATA_PIN 8
#include <SoftwareSerial.h>
CRGB leds[NUM_LEDS];
boolean fill=false;
boolean demo = false;
int ledMatch[256] = {} ;
int i=0;

int counter =0;

int startRed =255;
int startBlue =20;
int startGreen =0;

int endRed =20;
int endBlue =255;
int endGreen =0;

int redTemp =255;
int blueTemp =20;
int greenTemp =0;


void setup() {
 FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  
 Serial.begin(38400); 
 randomSeed(analogRead(0));
}

void loop() {
  for(int i=0;i<256;i++){
     int r = random(0, 175);
     int g = random(0, 175);
     int b = random(0, 175);
     redTemp = r;
     blueTemp = b;
     greenTemp = g;
     
     if(r ==b){
        ledMatch[i] = 1;
     }
     if(shouldPaint(i)){
         drawPixel(i,startBlue,endGreen,startRed);
     } else {
       drawPixel(i,startRed,startGreen,startBlue);
      }
  }
  delay(10);
FastLED.show();
shouldReset();

}
boolean shouldPaint(int i){
    return !ledMatch[i]==1; 
}

boolean shouldReset(){
  for(int i=0;i<255;i++){
    if(ledMatch[i]==0)
        return false;
  }
  startRed = redTemp;
  startBlue = blueTemp;
  startGreen = greenTemp;
  clearScreen();
}
 

void fillScreen(int r, int g, int b){
  for(int i=0;i<NUM_LEDS;i++){
    leds[i] = CRGB(r, g, b);
    }
    FastLED.show();
  }

void clearScreen(){
  for(int i=0;i<NUM_LEDS;i++){
    leds[i] = CRGB(0, 0, 0);
    ledMatch[i] =0;
    }
    FastLED.show();
  }

void drawPixel(int p, int r, int g, int b){
  leds[p] = CRGB(r ,g, b);
 }

void parseValues(char velues[]){
  char p [4];
  char r [4];
  char g [4];
  char b [4];
  int param=0;
  int pi =0;
  int ri =0;
  int gi =0;
  int bi =0;
 for(int i=0;i<15;i++){
  if(velues[i]==',') param++;
  if(param==0){
    p[pi] = velues[i];
    pi++;
    } else if(param == 1){
        if(velues[i]!=','){
          r[ri] = velues[i];
          ri++;
        }
   } else if(param == 2){
      if(velues[i]!=','){
        g[gi] = velues[i];
        gi++;
      }
   } else if(param == 3){
      if(velues[i]!=','){     
        b[bi] = velues[i];
        bi++;
      }
    }
 }
 p[3] = '\0';
 r[3] = '\0';
 g[3] = '\0';
 b[3] = '\0';
 if(fill){
    fillScreen(atoi(r),atoi(g),atoi(b));
    fill = false;
    }
 else
    drawPixel(atoi(p),atoi(r),atoi(g),atoi(b));
}

int getRealLedCoordinate(int x, int y) {
        y = 15 - y;
        x = 15 - x;
        if (y == 0)
            return x;
        else if (y == 1)
            return 31 - x;
        else if (y == 2)
            return x + 32;
        else if (y == 3)
            return 63 - x;
        else if (y == 4)
            return x + 64;
        else if (y == 5)
            return 95 - x;
        else if (y == 6)
            return x + 96;
        else if (y == 7)
            return 127 - x;
        else if (y == 8)
            return x + 128;
        else if (y == 9)
            return 159 - x;
        else if (y == 10)
            return x + 160;
        else if (y == 11)
            return 191 - x;
        else if (y == 12)
            return x + 192;
        else if (y == 13)
            return 223 - x;
        else if (y == 14)
            return x + 224;
        else if (y == 15)
            return 255 - x;
        else
            return 0;
    }
