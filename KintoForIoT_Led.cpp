// KintoForIoT - Arduino library for prototyping connected devices with Kinto
// Copyright Julien Lebunetel 2018
// MIT License

// include Arduino core library
#include "Arduino.h"

// include this library's description file
#include "KintoForIoT_Led.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Led::Led()
    :Data()
{

};


// Public Methods //////////////////////////////////////////////////////////////
// Functions available in KintoForIoT sketches, this library, and other libraries

void Led::get()
{
  Data::get();

  char status[10];
  Data::read("status", status);

  if (strcmp(status, "on") == 0) {
    on();
  }
  else {
    off();
  }
};


void Led::post()
{
  if (_status) {
    Data::write("status", "on");
  }
  else {
    Data::write("status", "off");
  }

  Data::post();
};


void Led::begin(int pin, bool defaultValue)
{
  _pin = pin;
  _defaultValue = defaultValue;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _defaultValue);
  Data::setLocal();
};


void Led::on()
{
  if (isLocal()) {
    digitalWrite(_pin, !_defaultValue);
  }
  write(HIGH);
};


void Led::off()
{
  if (isLocal()) {
    digitalWrite(_pin, _defaultValue);
  }
  write(LOW);
};


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library
