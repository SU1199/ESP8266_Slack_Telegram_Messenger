#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#ifndef STASSID
#define STASSID "Joshi"
#define STAPSK  "#helloworld1024"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

String botId = "your-bot-id";
String message = "your message";

String url = "/services/TQ5QCPE8G/BPT1AAYD8/xQKvjSVy4KdfYc5NHbgVMQfw";
const char* host = "hooks.slack.com";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "C1 0D 53 49 D2 3E E5 2B A2 61 D5 9E 6F 99 0D 3D FD 8B B2 B3";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClientSecure client;
  client.setFingerprint(fingerprint);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (Serial.available())
  {
    int state = Serial.parseInt();
    if (state == 1)
    {
      Serial.println("requesting)";
      client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "User-Agent: ArduinoIoT/1.0\r\n" +
                   "Connection: close\r\n" +
                   "Content-Type: application/json\r\n" +
                   "Content-Length: 24\r\n\r\n" +
                   "{\"text\":\"Hello, World!\"}"
                  );
      Serial.println(client.readString());
    }
  }

}
