#include <TimerOne.h>
#include <ros.h>
#include <auv_test/ThVoltMsg.h>
const char MotorPin1 = 9;
const char BrakePin1 = 6;
const char DirPin1 = 11;
const char MotorPin2 = 10;
const char BrakePin2 = 8;
const char DirPin2 = 12;
short int readflag=0;
short int firstread=1;
int dutyNum1,dutyNum2;
float dutyCycle;
long lastping=0;
//-----------------------------------------ROS
ros::NodeHandle nh;
int th1,th2;
int prevth1,prevth2;
char cmdid;
void messageCb( const auv_test::ThVoltMsg& tmp){
digitalWrite(13, HIGH-digitalRead(13)); // blink the led
//Serial.println("Hello");
th1 = tmp.thvolt1;
th2 = tmp.thvolt2;
cmdid = tmp.cmd;
readflag=1;
lastping=0;
}
ros::Subscriber<auv_test::ThVoltMsg> sub("Thvolt", messageCb );
//--------------------------------------
void callback(){
if(lastping>500)
{
digitalWrite(BrakePin1, HIGH);
digitalWrite(BrakePin2, HIGH);
noInterrupts();
Timer1.pwm(9,dutyNum1);
Timer1.pwm(10,dutyNum2 );
interrupts();
}
else
lastping++;
}
void setup() {
Serial.begin(9600);
Serial.println("Hello");
pinMode(BrakePin1, OUTPUT);
pinMode(DirPin1, OUTPUT);
digitalWrite(BrakePin1, LOW);
digitalWrite(DirPin1, LOW);
pinMode(BrakePin2, OUTPUT);
pinMode(DirPin2, OUTPUT);
digitalWrite(BrakePin2, LOW);
digitalWrite(DirPin2, LOW); //Tperiod = 10000; // in micro seconds
//-------
pinMode(13, OUTPUT);
nh.initNode();
nh.subscribe(sub);
prevth1=th1;
prevth2=th2;
//-----
utyCycle=50;
Timer1.initialize(10000);
Timer1.attachInterrupt(callback);
dutyNum1 = (unsigned int)(dutyCycle*1023/100);
dutyNum2 = (unsigned int)(dutyCycle*1023/100);
Serial.print("Duty Cycle ");
Serial.println(dutyCycle);
Serial.print("Duty Number ");
Serial.println(dutyNum1);
Serial.println(dutyNum2);
Timer1.pwm(MotorPin1, dutyNum1);
Timer1.pwm(MotorPin2, dutyNum2);//(dutyCycle / 100) * 1023);// (dutyCycle / 100)
* 1023
}
void loop()
{
nh.spinOnce();
if(readflag){
readflag=0;
if(firstread){
delay(400);
if(th1<0){
digitalWrite(DirPin1,HIGH);
noInterrupts();
Timer1.pwm(11,dutyNum1 );
interrupts();
}
if(th2<0){
digitalWrite(DirPin2,HIGH);
noInterrupts();
Timer1.pwm(12,dutyNum2 );
interrupts();
}
firstread=0;
}
else{
if((th1>0)&&(prevth1<0)){ // for checking sign change
delay(500);
digitalWrite(DirPin1, LOW);
noInterrupts();
Timer1.pwm(11,dutyNum1 );
interrupts(); }
else if((th2>0)&&(prevth2<0)){
delay(500);
digitalWrite(DirPin2, LOW);
noInterrupts();
Timer1.pwm(12,dutyNum2 );
interrupts(); }
if((th1<0)&&(prevth1>0)){
delay(500);
digitalWrite(DirPin1, HIGH);
noInterrupts();
Timer1.pwm(11,dutyNum1 );
interrupts();
}
else if((th2<0)&&(prevth2>0)){
delay(500);
digitalWrite(DirPin2, HIGH);
noInterrupts();
Timer1.pwm(12,dutyNum2 );
interrupts();
}
}
if(cmdid==0x13){
digitalWrite(BrakePin1, HIGH);
noInterrupts();
Timer1.pwm(9,dutyNum1 );
interrupts(); }
else if(cmdid==0x14){
digitalWrite(BrakePin2, HIGH);
noInterrupts();
Timer1.pwm(10,dutyNum2 );
interrupts(); }
else if(cmdid==0x10){
dutyNum1 = (unsigned int)(abs(th1)*1023/100);
noInterrupts();
Timer1.pwm(9,dutyNum1 );
interrupts();
prevth1= th1;
}
else if(cmdid==0x11){
dutyNum2 = (unsigned int)(abs(th2)*1023/100);
noInterrupts();
Timer1.pwm(10,dutyNum2 );
interrupts();
prevth2= th2;
}
else if(cmdid==0x12){
dutyNum1 = (int)(abs(th1)*(1023/100));//Serial.println("Nello1");
dutyNum2 = (int)(abs(th2)*(1023/100));//Serial.println("Hello2");
noInterrupts();
Timer1.pwm(9,dutyNum1 );
Timer1.pwm(10,dutyNum2 );
interrupts();
prevth1= th1;
prevth2= th2;
}
delay(80);
}
//delay(500);
}
