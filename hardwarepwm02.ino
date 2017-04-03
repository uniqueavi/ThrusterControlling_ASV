unsigned int Tperiod;
unsigned int Dcycle;
unsigned int HT,LT,i;
unsigned char buf[10];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello");
  pinMode(13, OUTPUT);
  Tperiod = 10000; // in micro seconds
}

void loop()
{
  
   noofbyte=Serial.available();  
   if(noofbyte){
     for(i=0;i<noofbyte;i++)
        buf[i]=Serial.read();
      Dcycle = atoi(buf); 
   }
        
  HT = (unsigned int)(Tperiod*Dcycle/100);
  LT = Tperiod - HT;
  
  digitalWrite(13, HIGH);
  delayMicroseconds(HT);
  digitalWrite(13, LOW);
  delayMicroseconds(LT);
}
