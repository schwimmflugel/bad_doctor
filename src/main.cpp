#include <Arduino.h>
#include <Radio.h>
#include <Constants.h>
#include <SystemCoordinator.h>
#include <esp_task_wdt.h>

Radio radio;
SystemCoordinator systemCoordinator;

byte dataPacket[PACKET_LENGTH];


void setup() {

  // Enable the watchdog timer with a timeout of 5 seconds
  //esp_task_wdt_init(5, true);

  // Register the current task to be monitored by the watchdog timer
  //esp_task_wdt_add(NULL);

  // put your setup code here, to run once:
  Serial.begin(57600);
  radio.begin();
  systemCoordinator.begin();
  Serial.println(WiFi.macAddress());

  ledcAttachPin(LED_BLUE_PIN, 0);
  ledcAttachPin(LED_RED_PIN, 1);
  
}

void loop() {
  if(radio.isDataReady(dataPacket)){

    systemCoordinator.feedWatchdog();//Update radio watchdog that packet has been received

    systemCoordinator.packetParse(dataPacket, PACKET_LENGTH); //Pass data to systems
  }

  if(systemCoordinator.watchdog()){
    //Serial.println("No radio data received");    
  }

  systemCoordinator.runTasks();

  // Reset the master watchdog timer to prevent a timeout
  //esp_task_wdt_reset();
}




