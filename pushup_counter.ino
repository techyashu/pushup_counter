#include "TM1637.h"
#define echoPin  6
#define trigPin  5
#define resetPin 4

#define CLK 2//pins definitions for TM1637 and can be changed to other ports       
#define DIO 3
TM1637 tm1637(CLK,DIO);

float duration; //micro second
float d_cm;
long numDisplay=100;
boolean x = false;

float counterPushUp=0;

void setup()
{  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  //
  pinMode(resetPin,INPUT_PULLUP);
  tm1637.init();
  tm1637.set(7);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}
void loop()
{
   // tm1637.display(0,);
    //tm1637.display(1,); 
    //tm1637.display(2,);
    if(digitalRead(resetPin)==0){
//    trigUp=false;
    x=false;
    counterPushUp=0;
  }
   // generate pusle trigger
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  // receive, convert time (us) to cm
  duration = pulseIn(echoPin,HIGH);
  d_cm = duration * 0.034/2.;
  

if((d_cm<=10)&&(x==true))
{
  counterPushUp+=1;
  x=false;
}

if((d_cm>10)&&(x==false))
{
    x=true;
}


  
  Serial.println(counterPushUp);
   int i =counterPushUp;
    if(i>999)tm1637.display(0, i/1000);     // print thousands digit
    if(i>99)tm1637.display(1, i/100 % 10); // print hundreds digit
    if(i>9)tm1637.display(2, i/10 % 10);  // print tens digit
    tm1637.display(3, i% 10);      // print ones digit
   delay(50);
    
  
}
