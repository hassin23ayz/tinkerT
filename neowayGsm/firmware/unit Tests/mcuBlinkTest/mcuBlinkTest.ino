//test the RGB led of the board which is connected with 13 14 15 
void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, OUTPUT); //blue
  pinMode(14, OUTPUT); //red
  pinMode(15, OUTPUT); //gree
}

// the loop function runs over and over again forever
void loop() 
{
  digitalWrite(13, HIGH);
  delay(1000);  
  digitalWrite(13, LOW);   
  digitalWrite(14, HIGH);   
  delay(1000);                
  digitalWrite(14, LOW);
  digitalWrite(15, HIGH);  
  delay(1000);
  digitalWrite(15, LOW);            
}
