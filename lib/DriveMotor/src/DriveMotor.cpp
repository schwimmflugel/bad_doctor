
#include <Constants.h>
#include <Arduino.h>
#include <DriveMotor.h>

DriveMotor::DriveMotor(){};


DriveMotor::DriveMotor(byte fwd_pin, byte rev_pin, byte fwd_channel, byte rev_channel, bool flip_direction /* = false */){
    _fwd_pin = fwd_pin;
    _rev_pin = rev_pin;
    _fwd_channel = fwd_channel;
    _rev_channel = rev_channel;
    _flip_direction = flip_direction;

    ledcAttachPin(_fwd_pin, _fwd_channel);
    ledcAttachPin(_rev_pin, _rev_channel);
    ledcSetup(_fwd_channel, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(_rev_channel,  PWM_FREQ, PWM_RESOLUTION);

    //setSpeed(0,0, STOP);


}


void DriveMotor::setSpeed(byte speed, byte direction, byte orientation /* = RIGHT_SIDE_UP */ ){

    //Flip motor direction to correct for wiring polarity differences
    if( _flip_direction == true){
        if(direction == FORWARD){direction = REVERSE;}
        else if (direction == REVERSE){direction = FORWARD;}    
    }

    //Flip motor direction to adjust for orientation (CW to CCW)
    //Correction for Left<->Right side swapping is done in Drive.cpp
    if(orientation == UPSIDE_DOWN){
        if(direction == FORWARD){direction = REVERSE;}
        else if (direction == REVERSE){direction = FORWARD;}    
    }

    //max ~220;
    //speed = 10;
    //direction = REVERSE;


    if(direction == STOP){
        ledcWrite(_fwd_channel, 0);
        ledcWrite(_rev_channel, 0);
    }
    else if( direction == FORWARD){
        //Serial.print("Forward:");
        //Serial.println(speed);
        ledcWrite(_fwd_channel, speed);
        ledcWrite(_rev_channel, 0);
    }
    else if( direction == REVERSE ){
        //Serial.print("Forward:");
        //Serial.println(speed);
        ledcWrite(_rev_channel, speed);
        ledcWrite(_fwd_channel, 0);
    }

}



