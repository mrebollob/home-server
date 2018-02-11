#include <ESP8266WiFi.h>

const char* ssid = "***";
const char* password = "***";
const int relayPin = D1;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare relay
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  String status;
  if (req.indexOf("/open") != -1){
    openRelay();
    status = "OPEN";
  }else{
    Serial.println("404");
    status = "ERROR";
  }

  client.flush();

  String s = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n";
  s += "{\"status\": \"" + status + "\"}";
  
  client.print(s);
  delay(1000);
  closeRelay();
  Serial.println("Client disonnected");
}

void openRelay(){
  Serial.println("OPEN");
  digitalWrite(relayPin, HIGH);
}

void closeRelay(){
  digitalWrite(relayPin, LOW);
  Serial.println("CLOSED");
}
  

