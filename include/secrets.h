//
// Created by Yuri Moiseyenko on 2025-12-20.
//
#ifndef ARDUINO_SECRETS_H
#define ARDUINO_SECRETS_H

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifdef IOT_DEVICE_ID
const char DEVICE_LOGIN_NAME[]  = TOSTRING(IOT_DEVICE_ID);
#else
const char DEVICE_LOGIN_NAME[]  = "DEVICE_NAME";
#endif

#ifdef WIFI_SSID
const char SSID[]               = TOSTRING(WIFI_SSID);
#else
const char SSID[]               = "WIFI_SSID";
#endif

#ifdef WIFI_PASSWORD
const char PASS[]               = TOSTRING(WIFI_PASSWORD);
#else
const char PASS[]               = "WIFI_PASSWORD";
#endif

#ifdef IOT_DEVICE_PASSWORD
const char DEVICE_KEY[]         = TOSTRING(IOT_DEVICE_PASSWORD);
#else
const char DEVICE_KEY[]         = "DEVICE_KEY";
#endif

#endif // ARDUINO_SECRETS_H
