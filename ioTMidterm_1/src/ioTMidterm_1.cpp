/* 
 * Project ioTMidterm_1
 * Author: Aarav Patel
 * Date: 6/30/25
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "neopixel.h"
#include "Encoder.h"
#include "IoTClassroom_CNM.h"
#include "Button.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

//photoDiode
const int DIODE =  A5;
int diodeState;
//neoPixel
const int PIXELCOUNT = 2;      
const int PIN = D0;             
Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1, WS2812B);



//Oled
void OLED(void);
const int OLED_RESET=-1;
Adafruit_SSD1306 display(OLED_RESET);

//Encoder
Encoder myEnc(D9,D8);
//Buttons
Button hueButton(A2);
Button wemButton(A1);
Button huechanger(S0);
Button wemoChanger(S4);
Button hueColorChanger(S1);
bool onOFF;
bool wemoOnOFF;
//Hue
int lastPosition;
int BULB;
int position;
int color = 0;
//Wemo
 int MYWEMO ; 


SYSTEM_MODE(MANUAL);
void setup() {
//photoDiode
pinMode(DIODE,INPUT);


//neoPixel
 pixel.begin();             
  //pixel.setBrightness(100);    
  pixel.show(); 


//Oled 
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.display(); 
  display.clearDisplay();   



  //Wifi
  Serial.begin(9600);
  waitFor(Serial.isConnected,15000);

  WiFi.on();
  WiFi.clearCredentials();
  WiFi.setCredentials("IoTNetwork");
  
  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf(".");
  }
  Serial.printf("\n\n");

  onOFF = true;
  wemoOnOFF = true;
}

void loop() {
//Phodiode
diodeState = analogRead(DIODE);
 if(diodeState >= 30){
  pixel.begin();             
  pixel.setBrightness(0);    
  pixel.show(); 
}

if(diodeState <=30){
  pixel.begin();             
  pixel.setBrightness(100);    
  pixel.show(); 
}
Serial.printf("diodeState = %i\n",diodeState);

//neoPixel  ` 
pixel.setPixelColor(1,red);  
pixel.setPixelColor(0,red);  
    pixel.show();                            
    delay(100);  


  //Oled
   OLED();  


    //Hue
  position = myEnc.read()/4;
  if(position != lastPosition){
    lastPosition = position;
    Serial.println(position);
    setHue(BULB,onOFF,HueRainbow[color%7],position);
    Serial.printf("Setting color of bulb %i to color %0i\n",BULB,HueRainbow[color%7]);
    Serial.printf("position %i\n",position);
  }


  if(hueButton.isClicked()){
onOFF = !onOFF;
  setHue(BULB%6 + 1,onOFF,HueRainbow[color%7],position);
  Serial.printf("Turning on hue# %i\n",BULB%6+1);
  }
  
if(huechanger.isClicked()){
BULB++;
Serial.printf("Switching to bulb %i\n",BULB%6 + 1);
Serial.printf("Turning off bulb %i\n",BULB%6 +1);
}

if(hueColorChanger.isClicked()){
  color++;
   setHue(BULB%6 + 1,onOFF,HueRainbow[color%7],position);
   Serial.printf("color is %i\n",color);
    display.setTextSize(0.5);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.printf("Turning on bulb %i\n",BULB%6+1);
  display.printf("Turning off bulb# %i\n",BULB%6+1);
  display.display();
  display.clearDisplay();
}
if(color > 7){
  color = 0;
}


 // Wemo 
   if(wemButton.isClicked()){
    wemoOnOFF = !wemoOnOFF;
    Serial.printf("Turning on Wemo# %i\n",MYWEMO%6);
    wemoWrite(MYWEMO,wemoOnOFF);
    Serial.printf("Turning off Wemo# %i\n",MYWEMO%6);
    wemoWrite(MYWEMO,wemoOnOFF);
     display.setTextSize(0.5);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.printf("Turning on Wemo# %i\n",MYWEMO%6);
  display.printf("Turning off Wemo# %i\n",MYWEMO%6);
  display.display();
  display.clearDisplay();
   }
   if(MYWEMO > 6){
    MYWEMO = 0;
   }
    if(wemoChanger.isClicked()){
MYWEMO++;

Serial.printf("Switching to wemo %i\n",MYWEMO%6);
}    

}
void OLED(){
  display.setTextSize(0.5);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.printf("Setting color of bulb %i to color %0i\n",BULB,HueRainbow[color%7]);
  display.printf("position %i\n",position);
  display.printf("Switching to bulb %i\n",BULB%6 + 1);
  display.printf("color is %i\n",color);
  display.printf("Switching to wemo %i\n",MYWEMO%6);
  display.printf("diodeState = %i\n",diodeState);
  display.display();
  display.clearDisplay();
  delay(1000);
}
