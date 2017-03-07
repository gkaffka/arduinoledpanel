#include <FastLED.h>
#define NUM_LEDS 256
#define DATA_PIN 6
#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
CRGB leds[NUM_LEDS];
boolean fill=false;
int i=0;
void setup() {
 FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
 BTserial.begin(38400);   
 Serial.begin(38400);
}

void loop() {
  char received[15];
    while (BTserial.available()>0){  
        char c = BTserial.read();
        if(i<15){
            if(c=='@') clearScreen();
            else if(c=='$') fill = true;
            else{
                received[i] = c;
                Serial.println(i);
                if(i==14)parseValues(received);
                i++;
             }
         }
    }
    i=0;
    
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
    }
    FastLED.show();
  }

void drawPixel(int p, int r, int g, int b){
  leds[p] = CRGB(r ,g, b);
  FastLED.show();
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

