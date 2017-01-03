#include <SoftwareSerial.h>
#include <Wire.h>
//SoftwareSerial BTSerial(2, 3); // 接收腳, 傳送腳
/* Input for motorA:
   IN1      IN2      Action
   LOW      LOW      Motor Stop
   HIGH     LOW      Motor moves forward  
   LOW      HIGH     Motor moves backward
   HIGH     HIGH     Motor Stop
*/   
const int motorIn1 = 8;//左輪
const int motorIn2 = 9;
const int motorIn3 = 10;//右輪      
const int motorIn4 = 11;  

int state = 0;
int value;


const int DELAY = 1000;
void leftforward()
{
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, HIGH);
  }

void rightforward()
{
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, HIGH);
  }

void leftbackward()
{
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  }

void rightbackward()
 {
  digitalWrite(motorIn3, HIGH);
  digitalWrite(motorIn4, LOW);
  }

void Stop()
{
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, LOW);
  }

  void receiveEvent(int howMany) {
    value = Wire.read();
    Serial.println(value);
    switch(value)
    {
      case 'w':
        if(state==0){
          state=1;
          leftforward();
          rightforward();
        }else{
          state=0;
          Stop();
        }  
        break;
        
      case 's':
        if(state==0){
          state=1;
          leftbackward();
          rightbackward();
        }else{
          state=0;
          Stop();
        }  
        break;
        
      case 'a':
        if(state==0){
          state=1;
          rightforward();
          leftbackward();
        }else{
          state=0;
          Stop();
        }          
        break;
        
      case 'd':
        if(state==0){
          state=1;
          leftforward();
          rightbackward();
        }else{
          state=0;
          Stop();
        }          
        break;
        
      default:
        Stop();
        break;
      }
    
}

void setup()  
{
  //BTSerial.begin(9600);

  Wire.begin(8);
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(115200); // start serial for output
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);    
  
}

void loop()
{ 
  delay(100);
}

