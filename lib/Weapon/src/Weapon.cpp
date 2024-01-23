#include <Constants.h>
#include <Arduino.h>
#include <Weapon.h>

Weapon::Weapon(){
    pinMode(WEAPON_PIN, OUTPUT);
    digitalWrite(WEAPON_PIN, LOW);
}

void Weapon::setState(bool run, bool overcurrent_override){
    if( WEAPON_ENABLE == false){
        Serial.println("Weapon disabled - No run");
        digitalWrite(WEAPON_PIN, LOW);
        return;
    }

    if( inCooldownState == true){
        Serial.println("Still cooling weapon down...");
        if( overcurrent_override == false){ //Break here normally, but if override is enabled then bypass safety
            return;
        }
    }

    //if(run == HIGH){Serial.println("WEAPON ON");}
    //else{Serial.println("WEAPON DISABLED");}

    digitalWrite(WEAPON_PIN, run);
}

void Weapon::readWeaponCurrent(){

    if(inCooldownState == true){
        if( millis() - start_cooldown >= WEAPON_COOLDOWN_TIME){
            Serial.println("Exiting weapon cooldown.");
            inCooldownState = false; //Exit cooldown state if it's been long enough
        }
        else{
            return; //exit if still within cooldown time 
        }
    }

    uint32_t current_time = millis();

    if( current_time - last_analog_read_time < WEAPON_READ_FREQ){
        return; //Exit if it's too early to read the next sample
    }

    last_analog_read_time = current_time;

    uint32_t data_sum = 0;

    for( int i = 0; i < WEAPON_CURRENT_SAMPLE_COUNT; i++ ){
        data_sum += analogRead(WEAPON_ADC_PIN);
        //Serial.print("Data_sum: ");
        //Serial.println(data_sum);
    }

    uint32_t volt = data_sum / WEAPON_CURRENT_SAMPLE_COUNT;
    
    /*
    Serial.print("Data Sum: ");
    Serial.print(data_sum);
    Serial.print("    Volt: ");
    Serial.println(volt);
    */

    //weapon_mAmp = ((((volt/4095.0)*3.3)/50)/0.030)*1000
    // divide by gain of 50, divide by resistance of 30mOhms, multiply by 1000 to get mAmps
    // measured_volt * 0.5371 is the scaling factor
    weapon_mAmp = ((volt*5371)/10000);
    //float weapon_mAmpf = volt * 0.5371;

    //Serial.print("Weapon Current: ");
    //Serial.print(weapon_mAmp);
    //Serial.print(" / ");
    //Serial.println(weapon_mAmpf);

    if( weapon_mAmp > MAX_WEAPON_CURRENT ){
        setState(LOW);
        inCooldownState = true;
        start_cooldown = millis();
    }


}