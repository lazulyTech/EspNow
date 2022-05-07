#include "EspNow.h"

esp_now_peer_info_t EspNow::peerInfo;

EspNow::EspNow(){
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    } else {
        Serial.println("Successful initializing ESP-NOW");
    }
}

bool EspNow::addPeer(uint8_t* address){
    if(role == SENDER || role == MEMBER){
        memcpy(peerInfo.peer_addr, address, 6);
        return (esp_now_add_peer(&peerInfo) == ESP_OK);
    } else {
        return false;
    }
}
