Void setup () {
Serial.begin (9600); 
} 
Void loop () {
if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    Serial.print("Received: ");
    Serial.println(receivedChar);
}
}
