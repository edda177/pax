/**
 * @file main.cpp
 * @brief Global variables, setup() and main() for pax IoT
 * 
 */
#include "arduino_secrets.h"
#include "measurement_state.h"
#include "Backend.h"
#include <Arduino.h>
#include <WiFiS3.h>

#ifndef SERVER
//! This is what your arduino secrets should look like
#define SECRET_SSID "your_ssid"
#define SECRET_PASS "your_password"

#define SERVER "google.com"
#define SERVER_PORT 443  // Default HTTPS port
#define API_PATH "" 
#define ROOM_STATE_ENDPOINT "/rooms"
#define CONFIG_ENDPOINT "/config"
#define JWT_ENDPOINT "/auth/login"
#define DEFAULT_UUID "00000000-0000-0000-0000-000000000000"  // Zero UUID for initial registration
#define JWT_SECRET_USER "user"
#define JWT_SECRET_PASS "password"
#endif

// Room ID storage
uint32_t room_id = 0;  // 0 indicates no room ID assigned
bool has_room_id = false;

int pir_pin = 2;
int led_pin = 3;
int temp_pin = 6; 
MeasurementState room_state(pir_pin, 60*1000, temp_pin); // pass temperature pin as 3rd argument to use sensor

// Server configuration, default constructor if SERVER is defined
ServerInfo server_info; 

Backend backend(server_info);

// Timing constants
constexpr time_t UPDATE_WAIT_TIME = 30 * 1000;  // 30 seconds
constexpr time_t ROOM_ID_RETRY_TIME = 10 * 60 * 1000;  // 10 minutes
constexpr time_t JWT_RETRY_TIME = 5 * 60 * 1000;  // 5 minutes
time_t last_update = 0;
time_t last_room_id_attempt = 0;
time_t last_jwt_attempt = 0;
constexpr uint32_t serial_baud_rate = 115200;

// System states
enum class SystemState {
    UNINITIALIZED,      // ServerInfo not fully constructed
    INITIALIZED,        // Basic initialization complete
    WIFI_CONNECTED,     // WiFi connected
    SERVER_CONNECTED,   // Connected to server (HEAD request succeeds)
    JWT_VALID,         // Has valid JWT token
    ROOM_CONFIGURED,    // Has valid room ID
    ERROR              // Error state
};

// Current system state
SystemState current_state = SystemState::UNINITIALIZED;

// Helper function to log state transitions
void log_state_transition(SystemState from, SystemState to, const char* reason = nullptr) {
    Serial.print("State transition: ");
    switch (from) {
        case SystemState::UNINITIALIZED: Serial.print("UNINITIALIZED"); break;
        case SystemState::INITIALIZED: Serial.print("INITIALIZED"); break;
        case SystemState::WIFI_CONNECTED: Serial.print("WIFI_CONNECTED"); break;
        case SystemState::SERVER_CONNECTED: Serial.print("SERVER_CONNECTED"); break;
        case SystemState::JWT_VALID: Serial.print("JWT_VALID"); break;
        case SystemState::ROOM_CONFIGURED: Serial.print("ROOM_CONFIGURED"); break;
        case SystemState::ERROR: Serial.print("ERROR"); break;
    }
    Serial.print(" -> ");
    switch (to) {
        case SystemState::UNINITIALIZED: Serial.print("UNINITIALIZED"); break;
        case SystemState::INITIALIZED: Serial.print("INITIALIZED"); break;
        case SystemState::WIFI_CONNECTED: Serial.print("WIFI_CONNECTED"); break;
        case SystemState::SERVER_CONNECTED: Serial.print("SERVER_CONNECTED"); break;
        case SystemState::JWT_VALID: Serial.print("JWT_VALID"); break;
        case SystemState::ROOM_CONFIGURED: Serial.print("ROOM_CONFIGURED"); break;
        case SystemState::ERROR: Serial.print("ERROR"); break;
    }
    if (reason) {
        Serial.print(" (");
        Serial.print(reason);
        Serial.print(")");
    }
    Serial.println();
}

// Helper function to update state
void update_state(SystemState new_state, const char* reason = nullptr) {
    if (current_state != new_state) {
        log_state_transition(current_state, new_state, reason);
        current_state = new_state;
    }
}

/**
 * @brief Attempt to get a room ID from the server
 * @return true if successful, false otherwise
 */
bool try_get_room_id() {
    if (has_room_id) {
        return true;
    }

    if (backend.get_room_config()) {
        if (server_info.room_id != 0) {
            has_room_id = true;
            Serial.print("Got room ID: ");
            Serial.println(server_info.room_id);
            return true;
        }
    }
    
    Serial.println("Failed to get room ID");
    return false;
}

void setup() {
    Serial.begin(serial_baud_rate);
    while (!Serial) {
        delay(50);
    }

    update_state(SystemState::INITIALIZED, "Serial initialized");

    //! Setting room ID to a specific number for testing
    #ifdef ROOM_OVERRIDE
    room_id = ROOM_OVERRIDE;
    has_room_id = true;
    backend.update_room_id(room_id);
    update_state(SystemState::ROOM_CONFIGURED, "Room ID override set");
    #endif

    delay(500); // extra delay to give Serial connection time
    Wire.begin();
    
    Serial.println(F("System: Initializing room state"));
    room_state.begin();
    
    Serial.println(F("System: Initializing WiFi"));
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    update_state(SystemState::WIFI_CONNECTED, "WiFi connected");
    Serial.println("\nConnected to WiFi");
    
    Serial.println(F("System: Configuring I/O pins"));
    pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, LOW);
    
    delay(100);
    
    Serial.println(F("System: Initialization complete"));
    
    // Initialize backend and get JWT token
    Serial.println(F("\nSystem: Initializing backend..."));
    if (!backend.begin()) {
        Serial.println(F("System: Warning - Failed to initialize backend"));
        last_jwt_attempt = millis();
        update_state(SystemState::ERROR, "Backend initialization failed");
    } else {
        Serial.println(F("System: Successfully initialized backend"));
        update_state(SystemState::SERVER_CONNECTED, "Backend initialized");
        
        // Verify token validity
        if (!backend.verify_token_validity()) {
            Serial.println(F("System: Warning - Token validation failed"));
            if (!backend.login_jwt()) {
                Serial.println(F("System: Warning - Failed to get new JWT token"));
                update_state(SystemState::ERROR, "JWT token validation failed");
            } else {
                update_state(SystemState::JWT_VALID, "New JWT token obtained");
            }
        } else {
            Serial.println(F("System: Token validation successful"));
            update_state(SystemState::JWT_VALID, "JWT token valid");
        }
    }
  
    // Try to get room ID on startup
    if (try_get_room_id()) {
        update_state(SystemState::ROOM_CONFIGURED, "Room ID obtained");
        // Update room state and send initial state if we have a room ID
        room_state.update_all();
        backend.send_update_room_state(
            room_state.get_temperature_float(),
            room_state.room_has_activity_bool(),
            room_state.get_air_quality_float()
        );
    } else {
        update_state(SystemState::JWT_VALID, "No room ID yet");
    }
    last_update = millis();
    last_room_id_attempt = millis();
}

void loop() {
    // read sensor data
    room_state.update_all();

    // Try to get JWT token if we don't have one
    if (!backend.has_token() && (millis() - last_jwt_attempt > JWT_RETRY_TIME)) {
        Serial.println("Attempting to get JWT token...");
        if (backend.login_jwt()) {
            Serial.println("Successfully obtained JWT token");
            update_state(SystemState::JWT_VALID, "JWT token obtained");
            // After getting token, verify it
            if (backend.verify_token_validity()) {
                Serial.println("Token validation successful");
            }
        } else {
            update_state(SystemState::ERROR, "Failed to get JWT token");
        }
        last_jwt_attempt = millis();
    }

    // Try to get room ID if we don't have one
    if (!has_room_id && (millis() - last_room_id_attempt > ROOM_ID_RETRY_TIME)) {
        Serial.println("Attempting to get room ID...");
        if (try_get_room_id()) {
            update_state(SystemState::ROOM_CONFIGURED, "Room ID obtained");
        } else {
            update_state(SystemState::JWT_VALID, "Failed to get room ID");
        }
        last_room_id_attempt = millis();
    }

    // send data to server if we have a room ID
    if (has_room_id && (millis() - last_update > UPDATE_WAIT_TIME)) {
        Serial.println("Sending data...");
        if (backend.ensure_connection()) {
            last_update = millis();
            if (backend.send_update_room_state(
                room_state.get_temperature_float(),
                room_state.room_has_activity_bool(),
                room_state.get_air_quality_float()
            )) {
                update_state(SystemState::ROOM_CONFIGURED, "Data sent successfully");
            } else {
                update_state(SystemState::ERROR, "Failed to send data");
            }
        } else {
            update_state(SystemState::ERROR, "Lost server connection");
        }
    }
}