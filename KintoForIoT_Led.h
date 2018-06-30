// KintoForIoT - Arduino library for prototyping connected devices with Kinto
// Copyright Julien Lebunetel 2018
// MIT License

// ensure this library description is only included once
#ifndef KintoForIoT_Led
#define KintoForIoT_Led

// include library parts
#include "KintoForIoT_Data.h"

// library interface description
class Led : public Data
{
  // user-accessible "public" interface
  public:
    Led();
    bool read() { return _status; };
    void write(bool status) { _status = status; };
    void get();
    void post();
    void begin(int pin, bool defaultValue);
    void begin(int pin) { begin(pin, LOW); };
    void on();
    void off();

  // library-accessible "private" interface
  private:
    int _pin = LED_BUILTIN;
    bool _defaultValue = LOW;
    bool _status = LOW;
};

#endif
