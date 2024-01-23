#ifndef RADIO_H
#define RADIO_H

#include <Arduino.h>
#include <Constants.h>
#include <esp_now.h>
#include <WiFi.h>


class Radio{

    public:
        Radio();
        void begin();
        bool isDataReady(byte* packetToFill);


    private:
        static byte _packet_storage[PACKET_LENGTH];
        static bool _data_ready;

        esp_now_peer_info_t peerInfo;
        static void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);


};



#endif