// We need a WiFi connection
#include <ESP8266WiFi.h>
#include <WiFiManager.h>   //https://github.com/tzapu/WiFiManager

// Kinto library
#include <KintoForIoT.h>

#define SERVER "http://.../v1"
#define LOGIN  "login"
#define PASS   "password"

const int ledPin =  16;  // GPI16 = D0

Data data;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);

  // initialize serial communication
  Serial.begin(115200);

  // initialize data
  data.connect(SERVER, LOGIN, PASS, "button");

  // connecting to a WiFi network
  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP8266");
}

void loop() {
  // retrieve button status on transmitter device
  data.get();

  char status[50];
  data.read("status", status);

  // if button is "on", turn on the led !
  if (strcmp(status, "on") == 0) {
    digitalWrite(ledPin, HIGH);
  }

  if (strcmp(status, "off") == 0) {
    digitalWrite(ledPin, LOW);
  }

  // wait a little ...
  delay(100);
}
