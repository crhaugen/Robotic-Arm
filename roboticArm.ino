#include <Servo.h>
#include "IRremote.h"


struct arm
{
  Servo servo;
  int degreeMoved = 0;
};

struct arm arm1;
struct arm arm2;
struct arm arm3;
struct arm arm4;

int receiver = 12;
IRrecv irrecv(receiver);     
decode_results results;
    



void setup() 
{
  Serial.begin(9600);
 
  arm1.servo.attach(8);
  arm2.servo.attach(9); 
  arm3.servo.attach(10); 
  arm4.servo.attach(11); 
  irrecv.enableIRIn(); 
}

void moveArm(struct arm *currentArm)
{
  irrecv.resume();
  while(true)
  {
    delay(500);
    Serial.println(irrecv.decode(&results)); 
    if(irrecv.decode(&results))
    {
      switch(results.value)
      {
        
        case 0xFF22DD: 
          Serial.println("FAST BACK");
          currentArm->servo.write(currentArm->degreeMoved-=10);
          delay(10);          
          break;
          
        case 0xFFC23D: 
          Serial.println("FAST FORWARD");
          currentArm->servo.write(currentArm->degreeMoved+=10); 
          delay(10);        
          break;
  
        case 0xFFE21D: 
          Serial.println("FUNC/STOP"); 
          return;
  
        default: 
          Serial.println(" other button   ");
      }
    }
    irrecv.resume();
  }
}

void pickArm() 
{
  switch(results.value)
  {
    case 0xFF6897: 
      Serial.println("0"); 
      struct arm *armPtr = &arm1;
      moveArm(armPtr);
      break;
      
    case 0xFF30CF: 
      Serial.println("1");    
      break;
      
    case 0xFF18E7: 
      Serial.println("2");    
      break;
      
    case 0xFF7A85:
      Serial.println("3");    
      break;
  
    default: 
      Serial.println(" other button   ");
  }

  delay(500);
}

void loop() 
{
  if (irrecv.decode(&results))
  {
    pickArm(); 
    irrecv.resume(); 
  }  
}
