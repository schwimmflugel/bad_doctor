#include <Constants.h>
#include <Arduino.h>
#include <Drive.h>
#include <SystemCoordinator.h>
#include <Wire.h>
#include "ICM42688.h"

SystemCoordinator::SystemCoordinator(){
    Drive drive;
    Weapon weapon;
    if(IMU_ENABLE){ICM42688 imu(Wire, 0x68);}
}

void SystemCoordinator::begin(){

    if( IMU_ENABLE == true){
        int status = imu.begin();
        if (status < 0) {
            Serial.println("IMU initialization unsuccessful");
            Serial.println("Check IMU wiring or try cycling power");
            Serial.print("Status: ");
            Serial.println(status);
            imu_functional = false;
        }
        else{
            imu_functional = true;
            Serial.println("Successfully Initiated IMU");
        }
    }
    else{
        Serial.println("IMU was not initialized - Change IMU_ENABLE to change");
        imu_functional = false;
    }
}

void SystemCoordinator::packetParse(byte* inputPacket, byte len){
    control_values values;
    int orientation;

    /*
    for( int i = 0; i < len; i++){
      Serial.println(inputPacket[i]);
    }
    */

    values.L_thumb_x = inputPacket[0];
    values.L_thumb_y = inputPacket[1];
    values.R_thumb_x = inputPacket[2];
    values.R_thumb_y = inputPacket[3];
    values.button_vals = inputPacket[4];
    values.trigger_vals = inputPacket[5];

    if(imu_functional == true){
        if( imu.getAGT() < 0 ){
            orientation = RIGHT_SIDE_UP; //If error reading accel, default to RIGHT_SIDE_UP
        }
        else{
            float accel_z = imu.accZ(); //read accel_z
            Serial.print("Accel Z Value: ");
            Serial.println(accel_z);
            if( accel_z > 0 ){ orientation = RIGHT_SIDE_UP; }
            else{ orientation = UPSIDE_DOWN; }
        }
    }
    else{ //If imu failed to initiate
        orientation = RIGHT_SIDE_UP; //default to RIGHT_SIDE_UP if no accel data
    } 

    //drive.direction(values.L_thumb_x, values.L_thumb_y, orientation);
    drive.two_stick_drive(values.L_thumb_y, values.R_thumb_y, orientation);

    //Control for weapon motor
    if( ((values.trigger_vals >> 1) & 0b00000011) == 2){
        bool override_val = (((values.trigger_vals >> 3) & 0b00000011) == 2 ); //Override safety with Left side trigger
        weapon.setState(HIGH, override_val);
    }
    else{
        weapon.setState(LOW);
    }

}

bool SystemCoordinator::watchdog(){
    uint32_t present_time = millis();
    if( present_time - last_packet_time > _timeout_time){
        byte blank_packet[] = {127, 127, 127, 127, 0, 0};
        packetParse(blank_packet, PACKET_LENGTH);
        feedWatchdog();
        return true;
    }
    return false;
}

void SystemCoordinator::feedWatchdog(){
    //Serial.println("Fed Watchdog");
    last_packet_time = millis();
}

//Tasks to run every cycle
void SystemCoordinator::runTasks(){
    weapon.readWeaponCurrent();
}
