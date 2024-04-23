#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <Update.h>

#include "personalserver.h"

PersonalServer ps(120); // Set Config Portal Timeout

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  ps.checkConfigPortalRequest();
}