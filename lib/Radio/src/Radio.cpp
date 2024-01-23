#include <Constants.h>
#include <Arduino.h>
#include <Radio.h>

#include <esp_now.h>
#include <WiFi.h>

// Define static member variables
byte Radio::_packet_storage[PACKET_LENGTH];
bool Radio::_data_ready = false;

Radio::Radio(){
    _data_ready = false;
}

void Radio::begin(){

    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for recv CB to
    // get recv packer info
     esp_now_register_recv_cb(OnDataRecv);
    
}

// Define the callback function outside the class
void Radio::OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  
    //Serial.print("Bytes received: ");
    //Serial.println(len);

    /*
    for(int i = 0; i < len; i++){
        Serial.println(incomingData[i]);
    }
    */

    if (len != PACKET_LENGTH){
        //Packet is incorrect
        Serial.println("Incorrect Packet Length Received");
        _data_ready = false;
        return;
    }

    memcpy(&_packet_storage, incomingData, PACKET_LENGTH);
    _data_ready = true;

}

//Fill in the packet if data is ready, Return True if completed or False if no data
bool Radio::isDataReady(byte* packetToFill){
    if( _data_ready ){
        memcpy(packetToFill, &_packet_storage, PACKET_LENGTH);
        _data_ready = false;
        return true;
    }
    return false;
}


 
