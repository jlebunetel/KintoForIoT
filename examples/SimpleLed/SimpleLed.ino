// KintoForIoT - Arduino library for prototyping connected devices with Kinto
// Copyright Julien Lebunetel 2018
// MIT License
//
// Just turn on and off an LED from Kinto

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

void setup() {
  // initializing the led
  led.begin(16); // GPI16 = D0

  // connecting the led to Kinto
  led.connect(SERVER, LOGIN, PASS, "led");

  // connecting to a WiFi network
  WiFiManager wifiManager;
  wifiManager.autoConnect("ESP8266");
}

void loop() {
  // retrieve led status from Kinto
  led.get();

  // wait a little ...
  delay(1000);
}
