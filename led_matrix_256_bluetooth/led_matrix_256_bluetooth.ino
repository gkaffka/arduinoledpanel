#include <FastLED.h>
#define NUM_LEDS 256
#define DATA_PIN 6
#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
CRGB leds[NUM_LEDS];
boolean fill=false;
boolean demo = false;
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
            demo = false;
            if(c=='@') clearScreen();
            else if(c=='d') demo = true;
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
    if(demo)runDemo();
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

void runDemo(){
  toad();
  mario();
  for(int i=0;i<7;i++){
    star(i);
  }
  delay(1000);
   clearScreen();
}

void toad(){  
    leds[getRealLedCoordinate(0,0)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(0,1)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(0,2)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(0,3)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(0,4)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(0,11)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(0,12)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(0,13)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(0,14)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(0,15)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(1,0)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(1,1)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(1,2)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(1,5)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(1,6)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(1,7)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(1,8)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(1,9)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(1,10)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(1,12)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(1,13)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(1,14)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(1,15)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(2,0)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(2,1)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(2,3)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(2,4)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(2,5)] = CRGB(153,42,34);
    leds[getRealLedCoordinate(2,6)] = CRGB(153,42,34);
    leds[getRealLedCoordinate(2,7)] = CRGB(153,42,34);
    leds[getRealLedCoordinate(2,8)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(2,9)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(2,10)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(2,14)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(2,15)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(3,0)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(3,1)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(3,2)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(3,3)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(3,4)] = CRGB(153,42,34);
    leds[getRealLedCoordinate(3,5)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(3,6)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(3,7)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(3,8)] = CRGB(153,42,34);
    leds[getRealLedCoordinate(3,9)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(3,10)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(3,12)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(3,13)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(3,15)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(4,0)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(4,1)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(4,2)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(4,3)] = CRGB(153,42,34);
    leds[getRealLedCoordinate(4,4)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(4,5)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(4,6)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(4,7)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(4,8)] = CRGB(153,42,34);
    leds[getRealLedCoordinate(4,9)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(4,11)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(4,12)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(4,13)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(4,14)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(4,15)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(5,0)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(5,1)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(5,2)] = CRGB(153,42,34);
    leds[getRealLedCoordinate(5,3)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(5,4)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(5,5)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(5,6)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(5,7)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(5,8)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(5,9)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(5,11)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(5,12)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(5,13)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(5,14)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(5,15)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(6,0)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(6,1)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(6,2)] = CRGB(153,42,34);
    leds[getRealLedCoordinate(6,3)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(6,4)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(6,5)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(6,6)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(6,7)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(6,8)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(6,9)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(6,13)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(6,14)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(6,15)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(7,0)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(7,1)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(7,2)] = CRGB(153,42,34);
    leds[getRealLedCoordinate(7,3)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(7,4)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(7,5)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(7,6)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(7,7)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(7,8)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(7,9)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(7,11)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(7,12)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(7,13)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(7,14)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(7,15)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(8,0)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(8,1)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(8,2)] = CRGB(153,42,34);
    leds[getRealLedCoordinate(8,3)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(8,4)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(8,5)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(8,6)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(8,7)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(8,8)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(8,9)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(8,11)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(8,12)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(8,13)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(8,14)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(8,15)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(9,0)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(9,1)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(9,2)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(9,3)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(9,4)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(9,5)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(9,6)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(9,7)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(9,8)] = CRGB(153,42,34);
    leds[getRealLedCoordinate(9,9)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(9,13)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(9,14)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(9,15)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(10,0)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(10,1)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(10,2)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(10,3)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(10,4)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(10,5)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(10,6)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(10,7)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(10,8)] = CRGB(153,42,34);
    leds[getRealLedCoordinate(10,9)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(10,11)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(10,12)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(10,13)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(10,14)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(10,15)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(11,0)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(11,1)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(11,2)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(11,3)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(11,4)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(11,5)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(11,6)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(11,7)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(11,8)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(11,9)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(11,11)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(11,12)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(11,13)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(11,14)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(11,15)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(12,0)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(12,1)] = CRGB(0,0,0);
    leds[getRealLedCoordinate(12,2)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(12,3)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(12,4)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(12,5)] = CRGB(244,67,54);
    leds[getRealLedCoordinate(12,6)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(12,7)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(12,8)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(12,9)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(12,10)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(12,12)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(12,13)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(12,15)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(13,0)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(13,1)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(13,3)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(13,4)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(13,5)] = CRGB(153,42,34);
    leds[getRealLedCoordinate(13,6)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(13,7)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(13,8)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(13,9)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(13,10)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(13,14)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(13,15)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(14,0)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(14,1)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(14,2)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(14,5)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(14,6)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(14,7)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(14,8)] = CRGB(255,255,255);
    leds[getRealLedCoordinate(14,9)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(14,10)] = CRGB(55,15,12);
    leds[getRealLedCoordinate(14,12)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(14,13)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(14,14)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(14,15)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(15,0)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(15,1)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(15,2)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(15,3)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(15,4)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(15,11)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(15,12)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(15,13)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(15,14)] = CRGB(48,109,50);
    leds[getRealLedCoordinate(15,15)] = CRGB(48,109,50);
    FastLED.show();
    delay(2000);
    clearScreen();
}

void mario(){
    leds[240] = CRGB(7, 81, 10);
    leds[239] = CRGB(7, 81, 10);
    leds[208] = CRGB(7, 81, 10);
    leds[207] = CRGB(7, 81, 10);
    leds[176] = CRGB(7, 81, 10);
    leds[175] = CRGB(7, 81, 10);
    leds[144] = CRGB(7, 81, 10);
    leds[143] = CRGB(7, 81, 10);
    leds[112] = CRGB(7, 81, 10);
    leds[111] = CRGB(7, 81, 10);
    leds[80] = CRGB(7, 81, 10);
    leds[79] = CRGB(7, 81, 10);
    leds[48] = CRGB(7, 81, 10);
    leds[47] = CRGB(7, 81, 10);
    leds[16] = CRGB(7, 81, 10);
    leds[15] = CRGB(7, 81, 10);
    leds[241] = CRGB(7, 81, 10);
    leds[238] = CRGB(7, 81, 10);
    leds[209] = CRGB(7, 81, 10);
    leds[206] = CRGB(7, 81, 10);
    leds[177] = CRGB(255,204,128);
    leds[174] = CRGB(7, 81, 10);
    leds[145] = CRGB(7, 81, 10);
    leds[142] = CRGB(7, 81, 10);
    leds[113] = CRGB(7, 81, 10);
    leds[110] = CRGB(7, 81, 10);
    leds[81] = CRGB(7, 81, 10);
    leds[78] = CRGB(7, 81, 10);
    leds[49] = CRGB(7, 81, 10);
    leds[46] = CRGB(7, 81, 10);
    leds[17] = CRGB(7, 81, 10);
    leds[14] = CRGB(7, 81, 10);
    leds[242] = CRGB(7, 81, 10);
    leds[237] = CRGB(244,67,54);
    leds[210] = CRGB(7, 81, 10);
    leds[205] = CRGB(255,204,128);
    leds[178] = CRGB(255,204,128);
    leds[146] = CRGB(7, 81, 10);
    leds[141] = CRGB(7, 81, 10);
    leds[114] = CRGB(7, 81, 10);
    leds[109] = CRGB(244,67,54);
    leds[82] = CRGB(255,204,128);
    leds[77] = CRGB(255,204,128);
    leds[50] = CRGB(255,204,128);
    leds[45] = CRGB(7, 81, 10);
    leds[18] = CRGB(7, 81, 10);
    leds[13] = CRGB(76,53,45);
    leds[243] = CRGB(7, 81, 10);
    leds[236] = CRGB(244,67,54);
    leds[211] = CRGB(7, 81, 10);
    leds[204] = CRGB(255,204,128);
    leds[179] = CRGB(255,204,128);
    leds[147] = CRGB(255,204,128);
    leds[140] = CRGB(7, 81, 10);
    leds[115] = CRGB(244,67,54);
    leds[108] = CRGB(244,67,54);
    leds[83] = CRGB(255,204,128);
    leds[76] = CRGB(255,204,128);
    leds[51] = CRGB(255,204,128);
    leds[44] = CRGB(7, 81, 10);
    leds[19] = CRGB(76,53,45);
    leds[12] = CRGB(76,53,45);
    leds[244] = CRGB(7, 81, 10);
    leds[235] = CRGB(244,67,54);
    leds[212] = CRGB(255,204,128);
    leds[203] = CRGB(255,204,128);
    leds[148] = CRGB(255,204,128);
    leds[139] = CRGB(7, 81, 10);
    leds[116] = CRGB(244,67,54);
    leds[107] = CRGB(244,67,54);
    leds[84] = CRGB(244,67,54);
    leds[75] = CRGB(255,204,128);
    leds[52] = CRGB(63,81,181);
    leds[43] = CRGB(63,81,181);
    leds[20] = CRGB(76,53,45);
    leds[11] = CRGB(76,53,45);
    leds[245] = CRGB(244,67,54);
    leds[234] = CRGB(244,67,54);
    leds[181] = CRGB(255,204,128);
    leds[149] = CRGB(255,204,128);
    leds[138] = CRGB(63,81,181);
    leds[117] = CRGB(244,67,54);
    leds[106] = CRGB(244,67,54);
    leds[85] = CRGB(63,81,181);
    leds[74] = CRGB(63,81,181);
    leds[53] = CRGB(63,81,181);
    leds[42] = CRGB(63,81,181);
    leds[21] = CRGB(76,53,45);
    leds[10] = CRGB(76,53,45);
    leds[246] = CRGB(244,67,54);
    leds[233] = CRGB(244,67,54);
    leds[214] = CRGB(255,204,128);
    leds[201] = CRGB(255,204,128);
    leds[182] = CRGB(255,204,128);
    leds[169] = CRGB(255,204,128);
    leds[150] = CRGB(255,204,128);
    leds[137] = CRGB(244,67,54);
    leds[118] = CRGB(63,81,181);
    leds[105] = CRGB(63,81,181);
    leds[86] = CRGB(255,193,7);
    leds[73] = CRGB(63,81,181);
    leds[54] = CRGB(63,81,181);
    leds[41] = CRGB(63,81,181);
    leds[22] = CRGB(76,53,45);
    leds[9] = CRGB(76,53,45);
    leds[247] = CRGB(244,67,54);
    leds[232] = CRGB(244,67,54);
    leds[215] = CRGB(255,204,128);
    leds[200] = CRGB(255,204,128);
    leds[183] = CRGB(255,204,128);
    leds[168] = CRGB(255,204,128);
    leds[151] = CRGB(255,204,128);
    leds[136] = CRGB(244,67,54);
    leds[119] = CRGB(244,67,54);
    leds[104] = CRGB(63,81,181);
    leds[87] = CRGB(63,81,181);
    leds[72] = CRGB(63,81,181);
    leds[55] = CRGB(63,81,181);
    leds[40] = CRGB(7, 81, 10);
    leds[23] = CRGB(7, 81, 10);
    leds[8] = CRGB(7, 81, 10);
    leds[248] = CRGB(244,67,54);
    leds[231] = CRGB(244,67,54);
    leds[216] = CRGB(255,204,128);
    leds[199] = CRGB(255,204,128);
    leds[184] = CRGB(255,204,128);
    leds[167] = CRGB(255,204,128);
    leds[152] = CRGB(255,204,128);
    leds[135] = CRGB(244,67,54);
    leds[120] = CRGB(244,67,54);
    leds[103] = CRGB(63,81,181);
    leds[88] = CRGB(63,81,181);
    leds[71] = CRGB(63,81,181);
    leds[56] = CRGB(63,81,181);
    leds[39] = CRGB(7, 81, 10);
    leds[24] = CRGB(7, 81, 10);
    leds[7] = CRGB(7, 81, 10);
    leds[249] = CRGB(244,67,54);
    leds[230] = CRGB(244,67,54);
    leds[217] = CRGB(76,53,45);
    leds[198] = CRGB(255,204,128);
    leds[185] = CRGB(255,204,128);
    leds[166] = CRGB(255,204,128);
    leds[153] = CRGB(255,204,128);
    leds[134] = CRGB(63,81,181);
    leds[121] = CRGB(63,81,181);
    leds[102] = CRGB(63,81,181);
    leds[89] = CRGB(255,193,7);
    leds[70] = CRGB(63,81,181);
    leds[57] = CRGB(63,81,181);
    leds[38] = CRGB(63,81,181);
    leds[25] = CRGB(76,53,45);
    leds[6] = CRGB(76,53,45);
    leds[250] = CRGB(244,67,54);
    leds[229] = CRGB(244,67,54);
    leds[218] = CRGB(76,53,45);
    leds[197] = CRGB(76,53,45);
    leds[186] = CRGB(76,53,45);
    leds[165] = CRGB(255,204,128);
    leds[154] = CRGB(255,204,128);
    leds[133] = CRGB(244,67,54);
    leds[122] = CRGB(244,67,54);
    leds[101] = CRGB(244,67,54);
    leds[90] = CRGB(63,81,181);
    leds[69] = CRGB(63,81,181);
    leds[58] = CRGB(63,81,181);
    leds[37] = CRGB(63,81,181);
    leds[26] = CRGB(76,53,45);
    leds[5] = CRGB(76,53,45);
    leds[251] = CRGB(7, 81, 10);
    leds[228] = CRGB(244,67,54);
    leds[219] = CRGB(76,53,45);
    leds[196] = CRGB(255,204,128);
    leds[187] = CRGB(255,204,128);
    leds[164] = CRGB(76,53,45);
    leds[155] = CRGB(7, 81, 10);
    leds[132] = CRGB(244,67,54);
    leds[123] = CRGB(244,67,54);
    leds[100] = CRGB(244,67,54);
    leds[91] = CRGB(244,67,54);
    leds[68] = CRGB(255,204,128);
    leds[59] = CRGB(63,81,181);
    leds[36] = CRGB(63,81,181);
    leds[27] = CRGB(76,53,45);
    leds[4] = CRGB(76,53,45);
    leds[252] = CRGB(7, 81, 10);
    leds[227] = CRGB(7, 81, 10);
    leds[220] = CRGB(7, 81, 10);
    leds[195] = CRGB(76,53,45);
    leds[188] = CRGB(76,53,45);
    leds[163] = CRGB(76,53,45);
    leds[156] = CRGB(7, 81, 10);
    leds[131] = CRGB(7, 81, 10);
    leds[124] = CRGB(244,67,54);
    leds[99] = CRGB(244,67,54);
    leds[92] = CRGB(255,204,128);
    leds[67] = CRGB(255,204,128);
    leds[60] = CRGB(255,204,128);
    leds[35] = CRGB(7, 81, 10);
    leds[28] = CRGB(76,53,45);
    leds[3] = CRGB(76,53,45);
    leds[253] = CRGB(7, 81, 10);
    leds[226] = CRGB(7, 81, 10);
    leds[221] = CRGB(7, 81, 10);
    leds[194] = CRGB(7, 81, 10);
    leds[189] = CRGB(7, 81, 10);
    leds[162] = CRGB(7, 81, 10);
    leds[157] = CRGB(7, 81, 10);
    leds[130] = CRGB(7, 81, 10);
    leds[125] = CRGB(7, 81, 10);
    leds[98] = CRGB(244,67,54);
    leds[93] = CRGB(255,204,128);
    leds[66] = CRGB(255,204,128);
    leds[61] = CRGB(255,204,128);
    leds[34] = CRGB(7, 81, 10);
    leds[29] = CRGB(7, 81, 10);
    leds[2] = CRGB(76,53,45);
    leds[254] = CRGB(7, 81, 10);
    leds[225] = CRGB(7, 81, 10);
    leds[222] = CRGB(7, 81, 10);
    leds[193] = CRGB(7, 81, 10);
    leds[190] = CRGB(7, 81, 10);
    leds[161] = CRGB(7, 81, 10);
    leds[158] = CRGB(7, 81, 10);
    leds[129] = CRGB(7, 81, 10);
    leds[126] = CRGB(7, 81, 10);
    leds[97] = CRGB(7, 81, 10);
    leds[94] = CRGB(7, 81, 10);
    leds[65] = CRGB(7, 81, 10);
    leds[62] = CRGB(7, 81, 10);
    leds[33] = CRGB(7, 81, 10);
    leds[30] = CRGB(7, 81, 10);
    leds[1] = CRGB(7, 81, 10);
    leds[255] = CRGB(7, 81, 10);
    leds[224] = CRGB(7, 81, 10);
    leds[223] = CRGB(7, 81, 10);
    leds[192] = CRGB(7, 81, 10);
    leds[191] = CRGB(7, 81, 10);
    leds[160] = CRGB(7, 81, 10);
    leds[159] = CRGB(7, 81, 10);
    leds[128] = CRGB(7, 81, 10);
    leds[127] = CRGB(7, 81, 10);
    leds[96] = CRGB(7, 81, 10);
    leds[95] = CRGB(7, 81, 10);
    leds[64] = CRGB(7, 81, 10);
    leds[63] = CRGB(7, 81, 10);
    leds[32] = CRGB(7, 81, 10);
    leds[31] = CRGB(7, 81, 10);
    leds[0] = CRGB(7, 81, 10);
    FastLED.show();
    delay(2000);
    clearScreen();
  }
void star(int i){
    leds[240] = CRGB(14,18,41);
    leds[239] = CRGB(14,18,41);
    leds[208] = CRGB(14,18,41);
    leds[207] = CRGB(14,18,41);
    leds[176] = CRGB(14,18,41);
    leds[175] = CRGB(14,18,41);
    leds[144] = CRGB(14,18,41);
    leds[143] = CRGB(14,18,41);
    leds[112] = CRGB(14,18,41);
    leds[111] = CRGB(14,18,41);
    leds[80] = CRGB(14,18,41);
    leds[79] = CRGB(14,18,41);
    leds[48] = CRGB(14,18,41);
    leds[47] = CRGB(14,18,41);
    leds[16] = CRGB(14,18,41);
    leds[15] = CRGB(14,18,41);
    leds[241] = CRGB(14,18,41);
    leds[238] = CRGB(14,18,41);
    leds[209] = CRGB(14,18,41);
    leds[206] = CRGB(14,18,41);
    leds[177] = CRGB(14,18,41);
    leds[142] = CRGB(14,18,41);
    leds[113] = CRGB(14,18,41);
    leds[110] = CRGB(14,18,41);
    leds[81] = CRGB(14,18,41);
    leds[78] = CRGB(14,18,41);
    leds[49] = CRGB(14,18,41);
    leds[46] = CRGB(14,18,41);
    leds[242] = CRGB(14,18,41);
    leds[237] = CRGB(14,18,41);
    leds[210] = CRGB(14,18,41);
    leds[205] = CRGB(14,18,41);
    leds[178] = CRGB(14,18,41);
    leds[146] = CRGB(255,193,7);
    leds[114] = CRGB(14,18,41);
    leds[109] = CRGB(14,18,41);
    leds[82] = CRGB(14,18,41);
    leds[77] = CRGB(14,18,41);
    leds[18] = CRGB(255,193,7);
    leds[243] = CRGB(14,18,41);
    leds[236] = CRGB(14,18,41);
    leds[211] = CRGB(14,18,41);
    leds[204] = CRGB(14,18,41);
    leds[179] = CRGB(14,18,41);
    leds[147] = CRGB(255,193,7);
    leds[140] = CRGB(255,193,7);
    leds[108] = CRGB(14,18,41);
    leds[51] = CRGB(255,193,7);
    leds[44] = CRGB(255,193,7);
    leds[19] = CRGB(255,193,7);
    leds[244] = CRGB(14,18,41);
    leds[235] = CRGB(14,18,41);
    leds[212] = CRGB(14,18,41);
    leds[203] = CRGB(14,18,41);
    leds[180] = CRGB(14,18,41);
    leds[148] = CRGB(255,193,7);
    leds[139] = CRGB(255,193,7);
    leds[116] = CRGB(255,193,7);
    leds[84] = CRGB(255,193,7);
    leds[75] = CRGB(255,193,7);
    leds[52] = CRGB(255,193,7);
    leds[43] = CRGB(255,193,7);
    leds[245] = CRGB(14,18,41);
    leds[234] = CRGB(14,18,41);
    leds[213] = CRGB(14,18,41);
    leds[202] = CRGB(14,18,41);
    leds[181] = CRGB(14,18,41);
    leds[149] = CRGB(255,193,7);
    leds[138] = CRGB(255,193,7);
    leds[117] = CRGB(255,193,7);
    leds[106] = CRGB(255,193,7);
    leds[85] = CRGB(255,193,7);
    leds[74] = CRGB(255,193,7);
    leds[53] = CRGB(255,193,7);
    leds[42] = CRGB(255,193,7);
    leds[10] = CRGB(14,18,41);
    leds[246] = CRGB(14,18,41);
    leds[233] = CRGB(14,18,41);
    leds[214] = CRGB(14,18,41);
    leds[169] = CRGB(255,193,7);
    leds[150] = CRGB(255,193,7);
    leds[137] = CRGB(255,193,7);
    leds[118] = CRGB(255,193,7);
    leds[105] = CRGB(255,193,7);
    leds[86] = CRGB(255,193,7);
    leds[73] = CRGB(255,193,7);
    leds[54] = CRGB(255,193,7);
    leds[22] = CRGB(14,18,41);
    leds[9] = CRGB(14,18,41);
    leds[247] = CRGB(14,18,41);
    leds[200] = CRGB(255,193,7);
    leds[183] = CRGB(255,193,7);
    leds[168] = CRGB(255,193,7);
    leds[104] = CRGB(255,193,7);
    leds[87] = CRGB(255,193,7);
    leds[72] = CRGB(255,193,7);
    leds[55] = CRGB(255,193,7);
    leds[23] = CRGB(14,18,41);
    leds[8] = CRGB(14,18,41);
    leds[231] = CRGB(255,193,7);
    leds[216] = CRGB(255,193,7);
    leds[199] = CRGB(255,193,7);
    leds[184] = CRGB(255,193,7);
    leds[167] = CRGB(255,193,7);
    leds[152] = CRGB(255,193,7);
    leds[135] = CRGB(255,193,7);
    leds[120] = CRGB(255,193,7);
    leds[103] = CRGB(255,193,7);
    leds[88] = CRGB(255,193,7);
    leds[71] = CRGB(255,193,7);
    leds[39] = CRGB(14,18,41);
    leds[24] = CRGB(14,18,41);
    leds[7] = CRGB(14,18,41);
    leds[249] = CRGB(14,18,41);
    leds[198] = CRGB(255,193,7);
    leds[185] = CRGB(255,193,7);
    leds[166] = CRGB(255,193,7);
    leds[102] = CRGB(255,193,7);
    leds[89] = CRGB(255,193,7);
    leds[70] = CRGB(255,193,7);
    leds[57] = CRGB(255,193,7);
    leds[25] = CRGB(14,18,41);
    leds[6] = CRGB(14,18,41);
    leds[250] = CRGB(14,18,41);
    leds[229] = CRGB(14,18,41);
    leds[218] = CRGB(14,18,41);
    leds[165] = CRGB(255,193,7);
    leds[154] = CRGB(255,193,7);
    leds[133] = CRGB(255,193,7);
    leds[122] = CRGB(255,193,7);
    leds[101] = CRGB(255,193,7);
    leds[90] = CRGB(255,193,7);
    leds[69] = CRGB(255,193,7);
    leds[58] = CRGB(255,193,7);
    leds[26] = CRGB(14,18,41);
    leds[5] = CRGB(14,18,41);
    leds[251] = CRGB(14,18,41);
    leds[228] = CRGB(14,18,41);
    leds[219] = CRGB(14,18,41);
    leds[196] = CRGB(14,18,41);
    leds[187] = CRGB(14,18,41);
    leds[155] = CRGB(255,193,7);
    leds[132] = CRGB(255,193,7);
    leds[123] = CRGB(255,193,7);
    leds[100] = CRGB(255,193,7);
    leds[91] = CRGB(255,193,7);
    leds[68] = CRGB(255,193,7);
    leds[59] = CRGB(255,193,7);
    leds[36] = CRGB(255,193,7);
    leds[4] = CRGB(14,18,41);
    leds[252] = CRGB(14,18,41);
    leds[227] = CRGB(14,18,41);
    leds[220] = CRGB(14,18,41);
    leds[195] = CRGB(14,18,41);
    leds[188] = CRGB(14,18,41);
    leds[156] = CRGB(255,193,7);
    leds[131] = CRGB(255,193,7);
    leds[124] = CRGB(255,193,7);
    leds[92] = CRGB(255,193,7);
    leds[67] = CRGB(255,193,7);
    leds[60] = CRGB(255,193,7);
    leds[35] = CRGB(255,193,7);
    leds[253] = CRGB(14,18,41);
    leds[226] = CRGB(14,18,41);
    leds[221] = CRGB(14,18,41);
    leds[194] = CRGB(14,18,41);
    leds[189] = CRGB(14,18,41);
    leds[157] = CRGB(255,193,7);
    leds[130] = CRGB(255,193,7);
    leds[98] = CRGB(14,18,41);
    leds[61] = CRGB(255,193,7);
    leds[34] = CRGB(255,193,7);
    leds[29] = CRGB(255,193,7);
    leds[254] = CRGB(14,18,41);
    leds[225] = CRGB(14,18,41);
    leds[222] = CRGB(14,18,41);
    leds[193] = CRGB(14,18,41);
    leds[190] = CRGB(14,18,41);
    leds[158] = CRGB(255,193,7);
    leds[126] = CRGB(14,18,41);
    leds[97] = CRGB(14,18,41);
    leds[94] = CRGB(14,18,41);
    leds[65] = CRGB(14,18,41);
    leds[30] = CRGB(255,193,7);
    leds[255] = CRGB(14,18,41);
    leds[224] = CRGB(14,18,41);
    leds[223] = CRGB(14,18,41);
    leds[192] = CRGB(14,18,41);
    leds[191] = CRGB(14,18,41);
    leds[128] = CRGB(14,18,41);
    leds[127] = CRGB(14,18,41);
    leds[96] = CRGB(14,18,41);
    leds[95] = CRGB(14,18,41);
    leds[64] = CRGB(14,18,41);
    leds[63] = CRGB(14,18,41);
    leds[32] = CRGB(14,18,41);
    if(i==1) {
        leds[151] = CRGB(255,193,7);
        leds[153] = CRGB(255,193,7);
        leds[136] = CRGB(0,0,0);
        leds[134] = CRGB(0,0,0);
        leds[119] = CRGB(0,0,0);
        leds[121] = CRGB(0,0,0);
     } else if(i==2){
        leds[151] = CRGB(255,193,7);
        leds[153] = CRGB(255,193,7);
        leds[136] = CRGB(255,193,7);
        leds[134] = CRGB(255,193,7);
        leds[119] = CRGB(0,0,0);
        leds[121] = CRGB(0,0,0);
      } else if(i==3){
        leds[151] = CRGB(255,193,7);
        leds[153] = CRGB(255,193,7);
        leds[136] = CRGB(255,193,7);
        leds[134] = CRGB(255,193,7);
        leds[119] = CRGB(255,193,7);
        leds[121] = CRGB(255,193,7);
      } else if(i==4){
        leds[151] = CRGB(255,193,7);
        leds[153] = CRGB(255,193,7);
        leds[136] = CRGB(255,193,7);
        leds[134] = CRGB(255,193,7);
        leds[119] = CRGB(0,0,0);
        leds[121] = CRGB(0,0,0);
      } else if(i==5) {
        leds[151] = CRGB(255,193,7);
        leds[153] = CRGB(255,193,7);
        leds[136] = CRGB(0,0,0);
        leds[134] = CRGB(0,0,0);
        leds[119] = CRGB(0,0,0);
        leds[121] = CRGB(0,0,0);
      } else {
        leds[151] = CRGB(0,0,0);
        leds[153] = CRGB(0,0,0);
        leds[136] = CRGB(0,0,0);
        leds[134] = CRGB(0,0,0);
        leds[119] = CRGB(0,0,0);
        leds[121] = CRGB(0,0,0);
        } 
    FastLED.show();
    delay(90);
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
