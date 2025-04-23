// https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples/

#ifndef WIFI_H
#define WIFI_H

#include <WiFiS3.h>

#include "arduino_secrets.h"  //please enter your sensitive data in the Secret tab/arduino_secrets.h
#include "networking_base.h"

class Wifi : public NetworkingBase {
   private:
    const char* ssid = SECRET_SSID;
    const char* password = SECRET_PASS;
    // int keyIndex = 0;                 // your network key index number (needed only for WEP)
    int status = WL_IDLE_STATUS;
    WiFiServer server{80};

   public:
    void connect() override {
        Serial.begin(9600);
        while (!Serial) {  // wait for serial port to connect. Needed for native USB port only
        }

        // check for the WiFi module:
        if (WiFi.status() == WL_NO_MODULE) {
            Serial.println("Communication with WiFi module failed!");
            // don't continue
            while (true);
        }

        String fv = WiFi.firmwareVersion();
        if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
            Serial.println("Please upgrade the firmware");
        }

        while (status != WL_CONNECTED) {
            Serial.print("Attempting to connect to SSID: ");
            Serial.println(ssid);
            // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
            status = WiFi.begin(ssid, password);
            delay(10000);
        }

        server.begin();
        // you're connected now, so print out the status:
        print_status();
    }

    // Check for and handle incoming client connections
    void poll() override {
        WiFiClient client = server.available();
        if (client && client.connected()) {
            handle_request(client);
        }
    }

    void handle_request(WiFiClient& client) {}

    void send_sensor_response(WiFiClient& client) {}

    void print_status() {
        // print the SSID of the network you're attached to:
        Serial.print("Connected to SSID: ");
        Serial.println(WiFi.SSID());
        // print your board's IP address:
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        // print the received signal strength:
        Serial.print("Signal strength: ");
        Serial.print(WiFi.RSSI());
        Serial.println(" dBm");
    }
};

#endif