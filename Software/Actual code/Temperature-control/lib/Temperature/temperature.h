#pragma once
// for ESP32 NODEMCU
#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <SPI.h>
#include <Wire.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <GyverMAX6675.h>
#include "GyverPID.h"
#include <GyverPortal.h>


// Pinii modulului MAX6675K
#define CLK_PIN 14
#define DATA_PIN 12
#define CS_PIN 15

#define NTC_PIN 39

#define NTC_A 0.001129148  // thermistor equation parameters
#define NTC_B 0.000234125
#define NTC_C 0.0000000876741

#define VCC 3.3              // NodeMCU on board 3.3v vcc
#define NTC_R2 9970          // 10k ohm series resistor
#define ADC_RESOLUTION 4096  // 12-bit adc

// PID
#define NUMBER_OF_TEMP_VALUE 200  // on graph
#define KP_VALUE 0.1
#define KI_VALUE 0.05
#define KD_VALUE 0.01
#define PERIOD_VALUE 20
#define MIN_PID_VALUE 0
#define MAX_PID_VALUE 1

// FLAGS
#define START_FLAG_INDEX 0

class Data : public GyverPID
{
    Data();
    float readKTemp();
    float readNTCTemp();
};



#endif  // CONFIG_H