#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

String id = "sensor 1";

int prevstate = LOW;
String d;
String data;

const char* ssid = "server1";
const char* password = "qwertyuiop";
String host = "http://10.10.10.1/feed?";

WiFiClient client;
HTTPClient http;

IPAddress ip (10, 10, 10, 32);
IPAddress gateway (10, 10, 10, 1);
IPAddress subnet (255, 255, 255, 0);


void setup() {
  pinMode(2, INPUT);
  Serial.begin(115200);
  ESP.eraseConfig();
  WiFi.persistent(false);
  Serial.println("SET ESP IN STA MODE");
  WiFi.mode(WIFI_STA);
  Serial.println("- connecting to wifi");
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
  Serial.println(".");
  Serial.println("- wifi connected");
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void readdata(){
  
  int currentstate = digitalRead(2);
  if(prevstate != currentstate){
    if(currentstate == HIGH){
      d = "high";
      data = "ID=";
      data += String(id);
      data += "&state=";
      data += String(d);
      http.begin(host);
      http.addHeader("content-type","application/x-www-form-urlencoded");
      http.POST(data);
      http.writeToStream(&Serial);
      http.end();
      Serial.println("data stream: "+data);
    }else{
      d = "low";
      data = "ID=";
      data += String(id);
      data += "&state=";
      data += String(d);
      http.begin(host);
      http.addHeader("content-type","application/x-www-form-urlencoded");
      http.POST(data);
      http.writeToStream(&Serial);
      http.end();
      Serial.println("data stream: "+data);
    }
  }prevstate = currentstate;
}
void loop () {
  readdata();

}
