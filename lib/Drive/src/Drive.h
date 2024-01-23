#ifndef DRIVE_H
#define DRIVE_H

#include <Arduino.h>
#include <Constants.h>
#include <DriveMotor.h>

class Drive{
    public:
        Drive();
        void direction(byte x, byte y, byte orientation);
        void two_stick_drive(byte left, byte right, byte orientation);


    private:
        DriveMotor leftMotor;
        DriveMotor rightMotor;



};


#endif