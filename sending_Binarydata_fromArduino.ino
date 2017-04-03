int intValue;    // an integer value (16 bits)

void setup()
{
  Serial.begin(9600);
}

void loop()
{
 char letter='a';
  while(1) 
  {
    if(Serial.available()>0)
    {
      letter = Serial.read();
    }
  }
}
  void sendBinary(int value)
{
  value = random(100); // send the two bytes 
  Serial.write(lowByte(value));  // send the low byte
  Serial.write(highByte(value)); // send the high byte
}  

