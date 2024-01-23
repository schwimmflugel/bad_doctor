#ifndef SYSTEMCOORDINATOR_H
#define SYSTEMCOORDINATOR_H

#include <Arduino.h>
#include <Constants.h>
#include <Drive.h>
#include "ICM42688.h"
#include <Wire.h>
#include <Weapon.h>

class SystemCoordinator{

    public:
        SystemCoordinator();
        void begin();
        void packetParse(byte* inputPacket, byte len);
        bool watchdog();
        void feedWatchdog();
        void runTasks();


    private:
        uint32_t last_packet_time;
        uint32_t _timeout_time = 1000; //watchdog timeout of 
        bool imu_functional = false;
       
        struct control_values{
            byte L_thumb_x, L_thumb_y;
            byte R_thumb_x, R_thumb_y;
            byte button_vals;
            byte trigger_vals;
        };

        Drive drive;
        ICM42688 imu;
        Weapon weapon;






};

#endif