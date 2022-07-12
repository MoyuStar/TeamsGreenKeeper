#include <USBComposite.h>
#define LED0 PC13
#define GPIO_IN PB0
#define GPIO_OUT PA7
#define interval 500
#define MoveTiming (10 * 1000 / interval)

USBHID HID;
HIDMouse mouse(HID);
int CNT = 0;
int RUN = 0;
int buttonLast;
unsigned long nextTime;


void setup(){
  pinMode(LED0, OUTPUT);
  pinMode(GPIO_IN, INPUT_PULLUP);
  pinMode(GPIO_OUT, OUTPUT);
  digitalWrite(GPIO_OUT, LOW);
  buttonLast = digitalRead(GPIO_IN);
  HID.begin(HID_MOUSE);
  while (!USBComposite);
  nextTime = millis();

}

void loop(){  
  if (buttonLast!=digitalRead(GPIO_IN)){
    RUN++;
    buttonLast = digitalRead(GPIO_IN);
    }

  if (RUN %4 == 0){
    if (millis() - nextTime >= interval){
      nextTime += interval;
      CNT ++ ;
      digitalWrite(LED0,!digitalRead(LED0));
      if (CNT == MoveTiming){
        mouse.move(-2,0);
        delay(10);
        mouse.move(2,0); 
        CNT = 0;
        }    
      }  
   }
   else{
    digitalWrite(LED0,HIGH);
    nextTime = millis();
   }
  }
