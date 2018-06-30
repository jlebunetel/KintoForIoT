// KintoForIoT - Arduino library for prototyping connected devices with Kinto
// Copyright Julien Lebunetel 2018
// MIT License

// ensure this library description is only included once
#ifndef KintoForIoT_Button
#define KintoForIoT_Button

// include library parts
#include "KintoForIoT_Data.h"

// library interface description
class Button : public Data
{
  // user-accessible "public" interface
  public:
    Button();
    bool read();
    void write(bool status);
    void get();
    void post();
    void begin(int pin, bool defaultStatus);
    void begin(int pin) { begin(pin, LOW); };
    void on() { write(!_defaultStatus); };
    void off() { write(_defaultStatus); };
    bool isOn() { return (_status != _defaultStatus); };
    bool isOff() { return (_status == _defaultStatus); };
    bool hasChanged() { return (_status != _previousStatus); };
    bool isJustOn() { return (hasChanged() && isOn()); };
    bool isJustOff() { return (hasChanged() && isOff()); };

  // library-accessible "private" interface
  private:
    int _pin = 0;
    bool _status = LOW;
    bool _previousStatus = LOW;
    bool _defaultStatus = LOW;
};

#endif
