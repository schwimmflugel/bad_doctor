#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>


#define LEFT 1
#define CENTER 2
#define RIGHT 3

#define PACKET_LENGTH 6
#define FORWARD 1
#define REVERSE 2
#define STOP 3
#define RIGHT_SIDE_UP 4
#define UPSIDE_DOWN 5

#define WEAPON_PIN 34
#define WEAPON_ADC_PIN 1

#define IMU_ENABLE false
#define WEAPON_ENABLE true

#define LED_BLUE_PIN 39
#define LED_RED_PIN 38

#define PWM_FREQ 25000
#define PWM_RESOLUTION 8

static uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

static uint16_t MAX_WEAPON_CURRENT = 3500; //1.3 Amps max current
static uint16_t WEAPON_COOLDOWN_TIME = 2500; //After overcurrent, cool for 2.5 sec
static uint16_t WEAPON_READ_FREQ = 10; //Read every 10 mSec
static uint32_t WEAPON_CURRENT_SAMPLE_COUNT = 5; //How many samples to measure motor current



#endif