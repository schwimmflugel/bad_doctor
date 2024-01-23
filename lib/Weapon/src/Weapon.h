#ifndef WEAPAON_H
#define WEAPON_H


#include <Arduino.h>
#include <Constants.h>


class Weapon{

    public:
        Weapon();
        void setState(bool run, bool overcurrent_override = false);
        void readWeaponCurrent();



    private:
        
        uint32_t weapon_mAmp;
        uint32_t start_cooldown;
        uint32_t last_analog_read_time;
        bool inCooldownState = false;

        


};

#endif



