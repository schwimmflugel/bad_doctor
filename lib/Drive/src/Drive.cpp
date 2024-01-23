#include <Constants.h>
#include <Arduino.h>
#include <Drive.h>
#include <DriveMotor.h>


Drive::Drive(): leftMotor(42, 41, 0, 1, true), rightMotor(5, 4, 2, 3, false){}
//Programming note:  called a member initialization list, and it is used in the constructor 
//of a class to initialize the member variables before the body of the constructor is executed.

void Drive::direction(byte x, byte y, byte orientation){
    int16_t int_x = x;
    int16_t int_y = y;

    int16_t leftMotorSpeed;
    int16_t rightMotorSpeed;

    int_x -= 127; //adjust 127 center value being 0
    int_y -= 127;

    //If bot is flipped, motors must rotate the opposite direction 
    //to go forward and Right<->Left are swapped now
    if(orientation == RIGHT_SIDE_UP){
        leftMotorSpeed = int_y + int_x;
        rightMotorSpeed = int_y - int_x;
    }
    else if(orientation == UPSIDE_DOWN){
        leftMotorSpeed = int_y - int_x;
        rightMotorSpeed = int_y + int_x;
    }

    byte left_speed = constrain(((abs(leftMotorSpeed) * 2) -1), 0, 255);
    byte right_speed = constrain(((abs(rightMotorSpeed) * 2) -1), 0, 255);

    if(leftMotorSpeed < 0){leftMotor.setSpeed(left_speed, REVERSE, orientation);}
    else{leftMotor.setSpeed(left_speed, FORWARD, orientation);}

    if(rightMotorSpeed < 0){rightMotor.setSpeed(right_speed, REVERSE, orientation);}
    else{rightMotor.setSpeed(right_speed, FORWARD, orientation);}

}

void Drive::two_stick_drive(byte left, byte right, byte orientation){

    //swapping values here because joystick assignement is wrong
    int16_t leftMotorSpeed = right;
    int16_t rightMotorSpeed = left;

    leftMotorSpeed -= 127; //adjust 127 center value being 0
    rightMotorSpeed -= 127;

    //If bot is flipped, Left is now right, right is left
    if(orientation == UPSIDE_DOWN){
        int16_t temp = leftMotorSpeed;
        leftMotorSpeed = rightMotorSpeed;
        rightMotorSpeed = temp;
    }

    byte left_speed = constrain(((abs(leftMotorSpeed) * 2) -1), 0, 255);
    byte right_speed = constrain(((abs(rightMotorSpeed) * 2) -1), 0, 255);

    if(leftMotorSpeed < 0){leftMotor.setSpeed(left_speed, REVERSE, orientation);}
    else{leftMotor.setSpeed(left_speed, FORWARD, orientation);}

    if(rightMotorSpeed < 0){rightMotor.setSpeed(right_speed, REVERSE, orientation);}
    else{rightMotor.setSpeed(right_speed, FORWARD, orientation);}

}


