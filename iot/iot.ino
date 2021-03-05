#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* ssid = "Realme1";
const char* password = "123456789";

ESP8266WebServer server(80);  
String page = "";
int relayPin1 = D0;
int relayPin2 = D1;
void setup(void)
{
  page = "<h1>IOT Bulb</h1><h3>Bulb 1</h3><p><a href=\"On1\"><button>ON</button></a>&nbsp;<a href=\"Off1\"><button>OFF</button></a></p><br><h3>Bulb 2</h3><p><a href=\"On2\"><button>ON</button></a>&nbsp;<a href=\"Off2\"><button>OFF</button></a></p>";
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  digitalWrite(relayPin1, HIGH);
  digitalWrite(relayPin2, HIGH);
   
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); 
  Serial.println("");
 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/On1", [](){
    server.send(200, "text/html", page);
    digitalWrite(relayPin1, LOW);
    delay(1000);
  });
  server.on("/Off1", [](){
    server.send(200, "text/html", page);
    digitalWrite(relayPin1, HIGH);
    delay(1000); 
  });
  server.on("/On2", [](){
    server.send(200, "text/html", page);
    digitalWrite(relayPin2, LOW);
    delay(1000);
  });
  server.on("/Off2", [](){
    server.send(200, "text/html", page);
    digitalWrite(relayPin2, HIGH);
    delay(1000); 
  });
  server.begin();
}
 
void loop(void)
{
  server.handleClient();
}
