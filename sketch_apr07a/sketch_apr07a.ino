int ledPin=2;
void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(23,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(2,HIGH);
  delay(500);
  
  
  digitalWrite(2,LOW);


  digitalWrite(5,HIGH);
  delay(500);
  
  
  digitalWrite(5,LOW);

  digitalWrite(23,HIGH);
  delay(500);
  
  
  
  digitalWrite(2,LOW);
  digitalWrite(5,LOW);
  digitalWrite(23,LOW);
  delay(500);

  digitalWrite(2,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(23,HIGH);
  delay(500);

  digitalWrite(2,LOW);
  digitalWrite(5,LOW);
  digitalWrite(23,LOW);
  delay(500);

  digitalWrite(2,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(23,HIGH);
  delay(500);

  digitalWrite(2,LOW);
  digitalWrite(5,LOW);
  digitalWrite(23,LOW);
  delay(500);

  digitalWrite(2,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(23,HIGH);
  delay(500);

  digitalWrite(2,LOW);
  digitalWrite(5,LOW);
  digitalWrite(23,LOW);

  delay(500);

 for (int i = 0; i <= 10; i++) {
    digitalWrite(2,HIGH);
  delay(100);
  
  
  digitalWrite(2,LOW);


  digitalWrite(5,HIGH);
  delay(100);
  
  
  digitalWrite(5,LOW);

  digitalWrite(23,HIGH);
  delay(100);

   digitalWrite(23,LOW);
  }
   


  

}
