// We need a WiFi connection
#include <ESP8266WiFi.h>
#include <WiFiManager.h>   //https://github.com/tzapu/WiFiManager

// Kinto library
#include <KintoForIoT.h>

#define SERVER "http://.../v1"
#define LOGIN  "login"
#define PASS   "password"

const int buttonPin = 5;      // GPIO5 = D1
int buttonState = 0;          // variable for reading the pushbutton status
int buttonPreviousState = 0;  // variable for storing the pushbutton previous status

Data data;

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  // initialize serial communication
  Serial.begin(115200);

  // initialize data
  data.connect(SERVER, LOGIN, PASS, "button");

  // connecting to a WiFi network
  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP8266");
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is just pressed. If it is, the buttonState is LOW:
  if (buttonState == LOW && buttonPreviousState == HIGH) {
    data.write("status", "on");
    data.post();
    buttonPreviousState = LOW;
  }

  // check if the pushbutton is just released. If it is, the buttonState is HIGH:
  if (buttonState == HIGH && buttonPreviousState == LOW) {
    data.write("status", "off");
    data.post();
    buttonPreviousState = HIGH;
  }

  // wait a little ...
  delay(500);
}
