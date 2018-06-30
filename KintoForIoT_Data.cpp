// KintoForIoT - Arduino library for prototyping connected devices with Kinto
// Copyright Julien Lebunetel 2018
// MIT License

// include Arduino core library
#include "Arduino.h"

// include this library's description file
#include "KintoForIoT_Data.h"

// include description files for other libraries used
#include <ArduinoJson.h>   //https://github.com/bblanchon/ArduinoJson
#include "ESP8266HTTPClient.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Data::Data()
{
  strcpy(_server, "");
  strcpy(_token, "");
  strcpy(_secret, "");
  strcpy(_collection, "");
  strcpy(_json, "{}");
};

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in KintoForIoT sketches, this library, and other libraries

void Data::connect(char* server, char* token, char* secret, char* collection)
{
  strcpy(_server, server);
  strcpy(_token, token);
  strcpy(_secret, secret);
  strcpy(_collection, collection);
  _connected = true;
};


void Data::read(char* key, char* value)
{
  // By design, the parser needs to alter the input string.
  // We work on a copy to keep _properties unaltered.
  char json[JSON_BUFFER_SIZE];
  strcpy(json, _json);

  DynamicJsonBuffer jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(json);

  if (data.success()) {
    JsonVariant property = data[String(key)];
    if (property.success()) {
      strcpy(value, property.as<char*>());
    }
    else {
      #ifdef DEBUG
        Serial.print(key);
        Serial.println(" does not exists");
      #endif
      strcpy(value, "");
    }
  }
  else {
    #ifdef DEBUG
      Serial.println("parseObject() failed");
    #endif
    strcpy(value, "");
  }
};


void Data::write(char* key, char* value)
{
  // By design, the parser needs to alter the input string.
  // We work on a copy to keep _properties unaltered.
  char json[JSON_BUFFER_SIZE];
  strcpy(json, _json);

  DynamicJsonBuffer jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(json);
  if (data.success()) {
    data[key] = value;
    data.printTo(_json);
  }
  #ifdef DEBUG
    Serial.println(_json);
  #endif
};


void Data::get()
{
  if (!isConnected()) { return; }

  String jsonMessageBuffer;

  char url[URL_BUFFER_SIZE] = "";
  strcat(url, _server);
  strcat(url, "/buckets/default/collections/");
  strcat(url, _collection);
  strcat(url, "/records?_limit=1");
  #ifdef DEBUG
    Serial.println(url);
  #endif

  HTTPClient http;
  http.begin(url);
  http.addHeader("Accept", "application/json");
  http.setAuthorization(_token, _secret);
  int httpCode = http.GET();
  if (httpCode > 0 ) {
    // HTTP header has been send and Server response header has been handled

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      jsonMessageBuffer = http.getString();
      #ifdef DEBUG
        Serial.println(jsonMessageBuffer);
      #endif

      DynamicJsonBuffer jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(jsonMessageBuffer);

      // Test if parsing succeeds.
      if (root.success()) {
        JsonObject& data = root["data"][0];
        if (data.success()) {
          size_t n = data.printTo(_json, sizeof(_json));
          #ifdef DEBUG
            Serial.println(_json);
          #endif
        }
        else {
          #ifdef DEBUG
            Serial.println("data does not exist");
          #endif
        }
      }
      else {
        #ifdef DEBUG
          Serial.println("parseObject() failed");
        #endif
      }
    }
  }
  else {
    #ifdef DEBUG
      Serial.println(httpCode);   //Print HTTP return code
    #endif
  }
  http.end();
};


void Data::post()
{
  if (!isConnected()) { return; }
  
  DynamicJsonBuffer jsonBufferRoot;
  JsonObject& root = jsonBufferRoot.createObject();
  root["data"] = RawJson(_json);
  char output[JSON_BUFFER_SIZE];
  size_t n = root.printTo(output, sizeof(output));
  #ifdef DEBUG
    Serial.println(output);
  #endif

  char url[URL_BUFFER_SIZE] = "";
  strcat(url, _server);
  strcat(url, "/buckets/default/collections/");
  strcat(url, _collection);
  strcat(url, "/records");
  #ifdef DEBUG
    Serial.println(url);
  #endif

  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  http.setAuthorization(_token, _secret);
  int httpCode = http.POST(output);
  #ifdef DEBUG
    String payload = http.getString(); //Get the response payload
    Serial.println(httpCode);          //Print HTTP return code
    Serial.println(payload);           //Print request response payload
  #endif
  http.end();  //Close connection
};

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library
