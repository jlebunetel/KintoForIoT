// KintoForIoT - Arduino library for prototyping connected devices with Kinto
// Copyright Julien Lebunetel 2018
// MIT License
//
// Turn on and off an LED status using the state of a remote Button.
// Use the sketch "SimpleButton.ino" for the remote Button.

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
  // initializing the led only
  // do not initialize the button, it's a remote one
  led.begin(16); // GPI016 = D0

  // connecting the button to Kinto only
  // do not connect the led, it's a local one
  button.connect(SERVER, LOGIN, PASS, "button");

  // connecting to a WiFi network
  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP8266");
}

void loop() {
  // retrieve button status from Kinto
  button.get();

  // change led status if the button
  // has changed since last call of read()
  if (button.hasChanged()) {
    if (button.isOn()) {
      led.on();
    }
    else {
      led.off();
    }
  }

  // wait a little ...
  delay(1000);
}
