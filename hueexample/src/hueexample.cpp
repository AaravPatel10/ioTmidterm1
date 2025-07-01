/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "IoTClassroom_CNM.h"
#include "Button.h"
#include "hue.h"
#include "Encoder.h"
Button hueButton(S4);
Encoder myEnc(D9,D8);
SYSTEM_MODE(MANUAL); //control logging into classroom router
//SYSTEM_THREAD(ENABLED); Caution - will allow code to execute before fully connected
bool onOFF;
int hueBr;
int position;
int lastPosition;
const int BULB=3; 
int hueB;

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
}

void loop() {
  position = myEnc.read()/4;
   Serial.printf("position %i\n",position);
  if(position != lastPosition){
    lastPosition = position;
    Serial.println(position);
    setHue(BULB,onOFF,HueRainbow[6],position);
  }


  if(hueButton.isClicked()){
onOFF = !onOFF;
  setHue(BULB,onOFF,HueRainbow[6],position);
  }
  
  {
  position = myEnc.read()/4;
    if(position > 50){
    position = 50;
    (position < 0);
    position = 0;
    Serial.println(position);
    setHue(BULB,onOFF,HueRainbow[6],position);
  }


  Serial.printf("Setting color of bulb %i to color %0i\n",BULB,HueRainbow[1]);

  
  }
}
