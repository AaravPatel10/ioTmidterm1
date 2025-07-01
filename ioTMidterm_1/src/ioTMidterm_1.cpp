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
#include "Colors.h"
#include "Encoder.h"
#include "IoTClassroom_CNM.h"
#include "Button.h"

Encoder myEnc(D9,D8);
//buttons
Button hueButton(A2);
Button wemButton(A1);
Button huechanger(S0);
Button wemoChanger(S4);
Button hueColorChanger(S1);
bool onOFF;
bool wemoOnOFF;
//hue
int lastPosition;
int BULB;
int position;
//wemu
 int MYWEMO ; 


SYSTEM_MODE(MANUAL);
void setup() {
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
    //hue code
  position = myEnc.read()/4;
  if(position != lastPosition){
    lastPosition = position;
    Serial.println(position);
    setHue(BULB,onOFF,HueRainbow[color%7],position);
    Serial.printf("Setting color of bulb %i to color %0i\n",BULB,HueRainbow[1]);
    Serial.printf("position %i\n",position);
  }


  if(hueButton.isClicked()){
onOFF = !onOFF;
  setHue(BULB%6 + 1,onOFF,HueRainbow[color%7],position);
  }
  
if(huechanger.isClicked()){
BULB++;
Serial.printf("Switching to bulb %i\n",BULB%6 + 1);
}

if(hueColorChanger.isClicked()){
   setHue(BULB%6 + 1,onOFF,HueRainbow[color%7],position);
   color++;
}



 // wemo code
   if(wemButton.isClicked()){
    wemoOnOFF = !wemoOnOFF;
    Serial.printf("Turning on Wemo# %i\n",MYWEMO%6);
    wemoWrite(MYWEMO,wemoOnOFF);
    Serial.printf("Turning off Wemo# %i\n",MYWEMO%6);
    wemoWrite(MYWEMO,wemoOnOFF);
   }
    if(wemoChanger.isClicked()){
MYWEMO++;
Serial.printf("Switching to wemo %i\n",MYWEMO%6);
}    

}
