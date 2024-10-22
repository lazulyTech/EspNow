//
// Created by Eisuke Kato on 24/10/22.
//

#include "EspNow.h"
#include <esp_now.h>

esp_now_peer_info_t EspNow::peerInfo;
void (*EspNow::on_sent_callback)(const uint8_t*, esp_now_send_status_t);
void (*EspNow::on_recv_callback)(const uint8_t*, const uint8_t*, int);


void _OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {

    if (EspNow::on_sent_callback != NULL) {
        EspNow::on_sent_callback(mac_addr, status);
    }
}

void _OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
    
    if (EspNow::on_recv_callback != NULL) {
        EspNow::on_recv_callback(mac_addr, incomingData, len);
    }
}

EspNow::EspNow(){
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    } else {
        Serial.println("Successful initializing ESP-NOW");
    }
}

void EspNow::Init(Role _role, uint32_t structSize){
        role = _role;
        this->structSize = structSize;
        if(role == SENDER || role == MEMBER){
            esp_now_register_send_cb(_OnDataSent);
            peerInfo.channel = 0;
            peerInfo.encrypt = false;
        }
        if(role == RECEIVER || role == MEMBER){
            esp_now_register_recv_cb(_OnDataRecv);
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

void EspNow::set_SentCallback(void (*Callback)(const uint8_t*, esp_now_send_status_t)) {
    on_sent_callback = Callback;
}

void EspNow::set_RecvCallback(void (*Callback)(const uint8_t*, const uint8_t*, int)) {
    on_recv_callback = Callback;
}

bool EspNow::send(const uint8_t* address, uint8_t* message) {
    if(role == SENDER || role == MEMBER){
        esp_err_t result;
        result = esp_now_send(address, message, structSize);
        return (result == ESP_OK);
    } else {
        return false;
    }
}

