// KintoForIoT - Arduino library for prototyping connected devices with Kinto
// Copyright Julien Lebunetel 2018
// MIT License

// ensure this library description is only included once
#ifndef KintoForIoT_Data
#define KintoForIoT_Data

// buffers' size
#define JSON_BUFFER_SIZE 512
#define PROPERTY_BUFFER_SIZE 100
#define URL_BUFFER_SIZE 300

// include description files for other libraries used
#include <ArduinoJson.h>   //https://github.com/bblanchon/ArduinoJson

// library interface description
class Data
{
  // user-accessible "public" interface
  public:
    Data();
    void connect(char* server, char* token, char* secret, char* collection);
    void read(char* key, char* value);
    void write(char* key, char* value);
    void get();
    void post();
    void setLocal() { _local = true; };
    bool isLocal() { return _local; };
    bool isConnected() { return _connected; };

  // library-accessible "private" interface
  private:
    char _server[PROPERTY_BUFFER_SIZE];
    char _token[PROPERTY_BUFFER_SIZE];
    char _secret[PROPERTY_BUFFER_SIZE];
    char _collection[PROPERTY_BUFFER_SIZE];
    char _json[JSON_BUFFER_SIZE];
    bool _local = false;
    bool _connected = false;
};

#endif
