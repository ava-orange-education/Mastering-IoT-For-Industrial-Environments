void setup() {
 Serial.begin(9600); // Initialize serial communication at 9600 baud
}
Void loop(){ 
digitalWrite(13,HIGH);
Serial.println(“LED is ON”); 
delay(1000);
digitalWrite(13,LOW);
Serial.println(“LED is OFF”); 
delay(1000);
}
