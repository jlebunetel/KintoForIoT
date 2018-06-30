// KintoForIoT - Arduino library for prototyping connected devices with Kinto
// Copyright Julien Lebunetel 2018
// MIT License
//
// Send a remote LED status using the state of a local Button.
// Use the sketch "SimpleLed.ino" for the remote LED.

// We need a WiFi connection
#include <ESP8266WiFi.h>
#include <WiFiManager.h>   //https://github.com/tzapu/WiFiManager

// Kinto library
#include <KintoForIoT.h>

#define SERVER "http://.../v1"
#define LOGIN  "login"
#define PASS   "password"

// led data object
Led led;

// button data object
Button button;

void setup() {
  // initializing the button only
  // do not initialize the led, it's a remote one
  button.begin(5, HIGH); // GPI05 = D1

  // connecting the led to Kinto only
  // do not connect the button, it's a local one
  led.connect(SERVER, LOGIN, PASS, "led");

  // connecting to a WiFi network
  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP8266");
}

void loop() {
  // reading the button status
  button.read();

  // sending led status to Kinto only if
  // it the button has changed since last call of read()
  if (button.hasChanged()) {
    if (button.isOn()) {
      led.on();
    }
    else {
      led.off();
    }
    led.post();
  }

  // wait a little ...
  delay(10);
}
