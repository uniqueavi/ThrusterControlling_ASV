int PIN = 13;
float dutyCycle = 0.9;
void setup()
{
    pinMode(13,OUTPUT);
    digitalWrite(13,LOW);
    
    Serial.begin(9600);
}

void loop()
{
  char letter='t';
  while(1) 
  {
    if(Serial.available()>0)
    {
    letter = Serial.read();
    
    }
    if(letter == 'N')
    {
      digitalWrite(PIN, LOW); 
      delay(1000 * (1-dutyCycle)); 
       
      digitalWrite(PIN, HIGH); 
      delay(1000 * dutyCycle); 
      
    }
    if(letter == 'F')
    {
      digitalWrite(13,LOW);
	
    }
    if(letter=='1' || letter=='2' || letter=='3' || letter =='4' || letter=='5' || letter=='6' || letter =='7' || letter =='8' || letter=='9'|| letter=='0')
    {
      dutyCycle=(atoi(&letter))*0.1;
      letter='N';
    }
}
}
