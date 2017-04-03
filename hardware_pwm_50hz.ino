#include <TimerOne.h>
 
void setup() 
{

  pinMode(13, OUTPUT);    
  
  Timer1.initialize(10000); 
  Timer1.attachInterrupt( timerIsr ); 
}
 
void loop()
{
  // Main code loop
}
 
void timerIsr()
{
    // generating pwm
    digitalWrite( 13, digitalRead( 13 ) ^ 1 );
}
