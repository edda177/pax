/**
 * @file main.cpp
 * @brief Global variables, setup() and main() for pax IoT
 * 
 */
#include "measurement_state.h"
#include "networking_base.h"
#include "PostMan.h"
#include <Arduino.h>

#ifndef SERVER
//! This is what your arduino secrets should look like
#define SECRET_SSID "your_ssid"
#define SECRET_PASS "your_password"

#define SERVER "google.com"
#define SERVER_PORT 8080
#define API_PATH "" 
#define ROOM_STATE_ENDPOINT "/room"
#define CONFIG_ENDPOINT "/device-config"
#define DEFAULT_UUID "00000000-0000-0000-0000-000000000000"  // Zero UUID for initial registration

#endif

//! If your server URL is an IP address, define SERVER_IS_IP in arduino_secrets.h
#ifdef SERVER_IS_IP
IPAddress server_ip(SERVER);
static String server_ip_str = server_ip.toString();
#define SERVER server_ip_str.c_str()
#else
static String server_ip_str = SERVER;
#endif

// Room ID storage
uint32_t room_id = UINT32_MAX;  // 0 indicates no room ID assigned
bool has_room_id = false;

int pir_pin = 2;
int led_pin = 3;
int temp_pin = 6; 
MeasurementState room_state(pir_pin, 60*1000, temp_pin); // pass temperature pin as 3rd argument to use sensor
WiFiClient wifi;
EthernetClient ether;
NetworkingBase network(&wifi, &ether);

static void update_room_id(String& room_id_string, uint32_t room_id)
{
    room_id_string = ROOM_STATE_ENDPOINT + room_id;
}
static String room_state_endpoint_composite;

// Server configuration
ServerInfo server_info = {
    .server_base_url = SERVER,
    .server_port = SERVER_PORT,
    .server_api_path = API_PATH,
    .room_state_endpoint = room_state_endpoint_composite.c_str(),
    .config_endpoint = CONFIG_ENDPOINT,
    .uuid = DEFAULT_UUID,
    .room_id = 0
};

PostMan postman(server_info, &network);

// Timing constants
constexpr time_t POSTMAN_WAIT_TIME = 30 * 1000;  // 30 seconds
constexpr time_t ROOM_ID_RETRY_TIME = 10 * 60 * 1000;  // 10 minutes
time_t last_postman_update = 0;
time_t last_room_id_attempt = 0;
constexpr uint32_t serial_baud_rate = 115200;

/**
 * @brief Attempt to get a room ID from the server
 * @return true if successful, false otherwise
 */
bool try_get_room_id() {
    if (has_room_id) {
        return true;
    }

    //! First try sending UUID if we haven't before
    if (server_info.room_id == 0) {
        if (postman.sendUuid(server_info.uuid)) {
            Serial.println("UUID sent successfully");
        } else {
            Serial.println("Failed to send UUID");
            return false;
        }
    }

    //! Then try to get room ID
    if (postman.getRoomId(server_info.room_id)) {
        if (server_info.room_id != 0) {
            has_room_id = true;
            Serial.print("Got room ID: ");
            Serial.println(server_info.room_id);
            //! Nice hack!! We update the endpoint with the room ID concatenated.
            update_room_id(room_state_endpoint_composite, room_id);
            server_info.room_state_endpoint = room_state_endpoint_composite.c_str();
            return true;
        }
    }
    
    Serial.println("Failed to get room ID");
    return false;
}

void setup()
{
    Serial.begin( serial_baud_rate );
    while (!Serial) {
        delay( 50 );
    }
    //! Setting room ID to a specific number for testing
    #ifdef ROOM_OVERRIDE
    room_id = ROOM_OVERRIDE;
    has_room_id = true;
    #endif
    //! We set the room state api endpoint by concatenating the room ID to it, e.g. /room/7
    update_room_id(room_state_endpoint_composite, room_id);
    server_info.room_state_endpoint = room_state_endpoint_composite.c_str(); //! This is because of how String works : (

    delay(500); // extra delay to give Serial connection time
    Wire.begin();
    
    Serial.println( F("System: Initializing room state") );
    room_state.begin();
    

    Serial.println( F("System: Initializing network") );
    network.begin();
    
    Serial.println( F("System: Configuring I/O pins") );
    pinMode( led_pin, OUTPUT );
    digitalWrite( led_pin, LOW );
    

    delay( 100 );
    
    Serial.println( F("System: Initialization complete") );
    
  
    // Try to get room ID on startup
    if (try_get_room_id()) {
        // Update room state and send initial state if we have a room ID
      room_state.update_all();
      postman.sendRoomState(
            room_state.get_temperature(),
            room_state.room_has_activity(),
            room_state.get_air_quality()
        );
    }
    last_postman_update = millis();
    last_room_id_attempt = millis();
}

void loop()
{
    // read sensor data
    room_state.update_all();

    // Try to get room ID if we don't have one
    if (!has_room_id && (millis() - last_room_id_attempt > ROOM_ID_RETRY_TIME)) {
        Serial.println("Attempting to get room ID...");
        try_get_room_id();
        last_room_id_attempt = millis();
    }

    // send data to server if we have a room ID
    if (has_room_id && (millis() - last_postman_update > POSTMAN_WAIT_TIME)) {
        Serial.println("Sending data...");
        network();
        delay(10);
        last_postman_update = millis();
        postman.sendRoomState(
            room_state.get_temperature(),
            room_state.room_has_activity(),
            room_state.get_air_quality()
        );
    }

    // Keep network alive
    if (millis() > 1000000) {
        network();
    }
    

}