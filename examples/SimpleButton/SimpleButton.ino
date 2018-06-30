// KintoForIoT - Arduino library for prototyping connected devices with Kinto
// Copyright Julien Lebunetel 2018
// MIT License
//
// Just send the button status to Kinto

// We need a WiFi connection
#include <ESP8266WiFi.h>
#include <WiFiManager.h>   //https://github.com/tzapu/WiFiManager

// Kinto library
#include <KintoForIoT.h>

#define SERVER "http://.../v1"
#define LOGIN  "login"
#define PASS   "password"

// button data object
Button button;

void setup() {
  // initializing the button
  button.begin(5, HIGH); // GPI05 = D1

  // connecting the button to Kinto
  button.connect(SERVER, LOGIN, PASS, "button");

  // connecting to a WiFi network
  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP8266");
}

void loop() {
  // reading the button status
  button.read();

  // sending button status to Kinto only if
  // it has changed since last call of read()
  if (button.hasChanged()) {
    button.post();
  }

  // wait a little ...
  delay(10);
}
