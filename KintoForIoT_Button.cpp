// KintoForIoT - Arduino library for prototyping connected devices with Kinto
// Copyright Julien Lebunetel 2018
// MIT License

// include Arduino core library
#include "Arduino.h"

// include this library's description file
#include "KintoForIoT_Button.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Button::Button()
       :Data()
{

};


// Public Methods //////////////////////////////////////////////////////////////
// Functions available in KintoForIoT sketches, this library, and other libraries

bool Button::read()
{
  if (isLocal()) {
    write(digitalRead(_pin));
  }
  return _status;
}


void Button::write(bool status)
{
  _previousStatus = _status;
  _status = status;
}


void Button::get()
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


void Button::post()
{
  if (isOn()) {
    Data::write("status", "on");
  }
  else {
    Data::write("status", "off");
  }

  Data::post();
};


void Button::begin(int pin, bool defaultStatus)
{
  _pin = pin;
  _status = defaultStatus;
  _previousStatus = defaultStatus;
  _defaultStatus = defaultStatus;
  pinMode(_pin, INPUT);
  Data::setLocal();
};


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library
