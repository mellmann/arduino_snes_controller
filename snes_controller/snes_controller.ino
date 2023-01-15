#include "GameControllers.h"

//shared pins between all controllers
const int LATCH_PIN = 9;
const int CLOCK_PIN = 8;

//individual data pin for each controller
const int DATA_PIN_0 = 10;  

SNESController controller(LATCH_PIN, CLOCK_PIN, DATA_PIN_0);


void setup() 
{
  Serial.begin(115200); //prepare serial for text output 

  controller.init(); 
}


void loop() 
{
  controller.poll();
  
  for(int i = 0; i < SNESController::NUM_OF_BUTTONS; i++) 
  {
    int n = i+1;
    if(controller.buttons[i].pressed()) {
      //Serial.println(n); // human readable
      Serial.write((char)(n));
    }

    if(controller.buttons[i].released()) {
      //Serial.println(-n); // human readable
      Serial.write((char)(-n));
    }
  }
  
  delay(50);
}
