#ifndef DRIVEMOTOR_H
#define DRIVEMOTOR_H

#include <Arduino.h>
#include <Constants.h>


class DriveMotor{
    
    public:
        DriveMotor();
        DriveMotor(byte fwd_pin, byte rev_pin, byte fwd_channel, byte rev_channel, bool flip_direction = false);
        void setSpeed(byte speed, byte direction, byte orientation = RIGHT_SIDE_UP);


    private:
        byte _fwd_pin;
        byte _rev_pin;
        byte _fwd_channel;
        byte _rev_channel;
        byte _speed;
        byte _direction;
        bool _flip_direction;

        const uint16_t pwmFreq = 25000; //Hz
        const byte resolution = 8; //bits [0-254]

};


#endif