//ESP8266 with MFM meter 

#include <ModbusRTU.h>
#include <SoftwareSerial.h>


float InttoFloat(uint16_t Data0,uint16_t Data1) {
  float x;
  unsigned long *p;
  p = (unsigned long*)&x;
  *p = (unsigned long)Data0 << 16 | Data1; //Big-endian
  return(x);
}
SoftwareSerial S(D3, D2);


ModbusRTU mb;

bool cbWrite(Modbus::ResultCode event, uint16_t transactionId, void* data) {
  Serial.printf_P("Request result: 0x%02X, Mem: %d\n", event, ESP.getFreeHeap());
  return true;
}

void setup() {
pinMode(D4, OUTPUT);
  Serial.begin(9600);
  S.begin(9600, SWSERIAL_8N1);
  mb.begin(&S,D4); // RE/DE connected to D0 of ESP8266
  mb.master();
}

uint16_t val[2];
void loop() {

  if (!mb.slave()) {
      digitalWrite(D4, HIGH);  // Enable RS485 transmitter for sending request
    mb.readHreg(10, 400133, val, 2, cbWrite); // Slave id is 1 and register address is 3926 and 
      digitalWrite(D4, LOW); 
    //we are reading 2 bytes from the register and saving in val
    while(mb.slave()) { // Check if transaction is active
      mb.task();
      delay(100);
    }
    Serial.println("Register Values ");
    Serial.println(val[0]);
    Serial.println(val[1]);
  float voltage= InttoFloat(val[1],val[0]);
  Serial.println("Voltage= ");
  Serial.print(voltage);
  Serial.println("V");

      }
  delay(500);
  
}
