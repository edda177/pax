#include "Backend.h"
#include <Arduino.h>
#include <WiFiS3.h>
#include <ArduinoJson.h>
#include <string_view>
#include <array>
#include <cstdint>
#include <algorithm>

//! Set the JWT token in the buffer
void ServerInfo::set_jwt_token(std::string_view token) {
    size_t len = std::min(token.size(), jwt_token_buffer.size() - 1);
    std::copy(token.begin(), token.begin() + len, jwt_token_buffer.begin());
    jwt_token_buffer[len] = '\0';
    jwt_token = std::string_view(jwt_token_buffer.data(), len);
}

//! Set the room endpoint in the buffer
void ServerInfo::set_room_endpoint(std::string_view endpoint) {
    size_t len = std::min(endpoint.size(), room_endpoint_buffer.size() - 1);
    std::copy(endpoint.begin(), endpoint.begin() + len, room_endpoint_buffer.begin());
    room_endpoint_buffer[len] = '\0';
    room_endpoint = std::string_view(room_endpoint_buffer.data(), len);
}

Backend::Backend(ServerInfo& server_info) : m_server_info(server_info) {}

bool Backend::begin() {
    // Set root certificate for SSL
    m_client.setCACert(m_server_info.server_cert.data());
    
    // Connect to server
    if (!m_client.connect(m_server_info.server_base_url.data(), m_server_info.server_port)) {
        return false;
    }
    
    // Get JWT token if we don't have one
    if (!m_has_token) {
        return login_jwt();
    }
    
    return true;
}

bool Backend::check_server_connection() {
    if (!m_client.connected()) {
        return false;
    }
    
    // Try a simple HEAD request to check server availability
    String request = "HEAD " + String(m_server_info.server_api_path.data()) + " HTTP/1.1\r\n";
    request += "Host: " + String(m_server_info.server_base_url.data()) + "\r\n";
    request += "Authorization: Bearer " + String(m_server_info.jwt_token.data()) + "\r\n";
    request += "\r\n";
    
    m_client.print(request);
    
    // Read response
    String response = "";
    while (m_client.available()) {
        response += (char)m_client.read();
    }
    
    return response.indexOf("200 OK") != -1;
}

bool Backend::ensure_connection() {
    if (m_client.connected()) {
        return true;
    }
    
    // Try to reconnect
    if (!m_client.connect(m_server_info.server_base_url.data(), m_server_info.server_port)) {
        return false;
    }
    
    // If we have a token, verify it's still valid
    if (m_has_token) {
        return verify_token_validity();
    }
    
    return true;
}

bool Backend::verify_token_validity() {
    if (!m_has_token) {
        return false;
    }
    
    // Try a simple GET request to verify token
    String request = "GET " + String(m_server_info.server_api_path.data()) + String(m_server_info.server_api_path.data()) + " HTTP/1.1\r\n";
    request += "Host: " + String(m_server_info.server_base_url.data()) + "\r\n";
    request += "Authorization: Bearer " + String(m_server_info.jwt_token.data()) + "\r\n";
    request += "\r\n";
    
    m_client.print(request);
    
    // Read status line
    String status_line = "";
    while (m_client.available()) {
        char c = m_client.read();
        if (c == '\n') {
            break;
        }
        status_line += c;
    }
    
    // Check if we got a valid status line
    std::string_view status_view(status_line.c_str(), status_line.length());
    if (status_view.substr(0, 8) != "HTTP/1.1") {
        return false;
    }
    
    // Extract status code
    int status_code = std::stoi(std::string(status_view.substr(9, 3)));
    
    // Skip headers
    while (m_client.available()) {
        String line = m_client.readStringUntil('\n');
        if (line == "\r") {  // Empty line marks end of headers
            break;
        }
    }
    
    // Read response body
    String response = "";
    while (m_client.available()) {
        response += (char)m_client.read();
    }
    
    // Handle different status codes
    switch (status_code) {
        case 200:  // Success - Token is valid
            return true;
            
        case 401:  // Unauthorized
            m_has_token = false;  // Clear token as it's invalid
            return false;
            
        default:  // Any other status code is an error
            return false;
    }
}

bool Backend::login_jwt() {
    // Construct POST request for JWT token
    String request = "POST " + String(m_server_info.server_api_path.data()) + String(m_server_info.jwt_endpoint.data()) + " HTTP/1.1\r\n";
    request += "Host: " + String(m_server_info.server_base_url.data()) + "\r\n";
    request += "Content-Type: application/json\r\n";
    
    // Create JSON payload
    StaticJsonDocument<200> doc;
    doc["email"] = m_server_info.jwt_user.data();
    doc["password"] = m_server_info.jwt_pass.data();
    
    String json;
    serializeJson(doc, json);
    
    request += "Content-Length: " + String(json.length()) + "\r\n";
    request += "\r\n";
    request += json;
    
    // Send request
    m_client.print(request);
    
    // Read status line
    String status_line = "";
    while (m_client.available()) {
        char c = m_client.read();
        if (c == '\n') {
            break;
        }
        status_line += c;
    }
    
    // Check if we got a valid status line
    std::string_view status_view(status_line.c_str(), status_line.length());
    if (status_view.substr(0, 8) != "HTTP/1.1") {
        return false;
    }
    
    // Extract status code
    int status_code = std::stoi(std::string(status_view.substr(9, 3)));
    
    // Skip headers
    while (m_client.available()) {
        String line = m_client.readStringUntil('\n');
        if (line == "\r") {  // Empty line marks end of headers
            break;
        }
    }
    
    // Read response body
    String response = "";
    while (m_client.available()) {
        response += (char)m_client.read();
    }
    
    // Parse JSON response (if needed)
    JsonDocument response_doc;
    DeserializationError error;
    JsonObject obj;
    
    // Handle different status codes
    switch (status_code) {
        case 200:  // Success
            error = deserializeJson(response_doc, response);
            
            if (error) {
                return false;
            }
            
            obj = response_doc.as<JsonObject>();
            if (obj.containsKey("token")) {
                const char* token = obj["token"].as<const char*>();
                m_server_info.set_jwt_token(std::string_view(token));
                m_has_token = true;
                return true;
            }
            return false;
            
        case 401:  // Unauthorized - Invalid credentials
            m_has_token = false;
            return false;
            
        default:  // Any other status code is an error
            return false;
    }
}

void Backend::update_room_id(uint32_t room_id) {
    m_server_info.room_id = room_id;
    String endpoint = String(m_server_info.rooms_base.data()) + "/" + String(room_id);
    m_server_info.set_room_endpoint(std::string_view(endpoint.c_str(), endpoint.length()));
    m_has_room_id = true;
}

bool Backend::send_update_room_state(float temperature, bool activity, float air_quality) {
    if (!m_has_token || !m_has_room_id) {
        return false;
    }
    
    // Ensure we have a valid connection
    if (!ensure_connection()) {
        return false;
    }
    
    // Construct PATCH request
    String request = "PATCH " + String(m_server_info.server_api_path.data()) + String(m_server_info.room_endpoint.data()) + "/state HTTP/1.1\r\n";
    request += "Host: " + String(m_server_info.server_base_url.data()) + "\r\n";
    request += "Authorization: Bearer " + String(m_server_info.jwt_token.data()) + "\r\n";
    request += "Content-Type: application/json\r\n";
    
    // Create JSON payload
    StaticJsonDocument<200> doc;
    doc["temperature"] = temperature;
    doc["activity"] = activity;
    doc["air_quality"] = air_quality;
    
    String json;
    serializeJson(doc, json);
    
    request += "Content-Length: " + String(json.length()) + "\r\n";
    request += "\r\n";
    request += json;
    
    // Send request
    m_client.print(request);
    
    // Read status line
    String status_line = "";
    while (m_client.available()) {
        char c = m_client.read();
        if (c == '\n') {
            break;
        }
        status_line += c;
    }
    
    // Check if we got a valid status line
    std::string_view status_view(status_line.c_str(), status_line.length());
    if (status_view.substr(0, 8) != "HTTP/1.1") {
        return false;
    }
    
    // Extract status code
    int status_code = std::stoi(std::string(status_view.substr(9, 3)));
    
    // Skip headers
    while (m_client.available()) {
        String line = m_client.readStringUntil('\n');
        if (line == "\r") {  // Empty line marks end of headers
            break;
        }
    }
    
    // Read response body
    String response = "";
    while (m_client.available()) {
        response += (char)m_client.read();
    }
    
    // Handle different status codes
    switch (status_code) {
        case 200:  // Success
            return true;
            
        case 401:  // Unauthorized
            m_has_token = false;  // Clear token as it's invalid
            return false;
            
        case 404:  // Not Found - Room might have been deleted
            m_has_room_id = false;
            update_room_id(0);
            return false;
            
        default:  // Any other status code is an error
            return false;
    }
}

bool Backend::get_room_config() {
    if (!m_has_token) {
        return false;
    }
    
    // Ensure we have a valid connection
    if (!ensure_connection()) {
        return false;
    }
    
    // Construct GET request
    String request = "GET " + String(m_server_info.server_api_path.data()) + String(m_server_info.config_endpoint.data()) + "?uuid=" + String(m_server_info.uuid.data()) + " HTTP/1.1\r\n";
    request += "Host: " + String(m_server_info.server_base_url.data()) + "\r\n";
    request += "Authorization: Bearer " + String(m_server_info.jwt_token.data()) + "\r\n";
    request += "\r\n";
    
    // Send request
    m_client.print(request);
    
    // Read status line
    String status_line = "";
    while (m_client.available()) {
        char c = m_client.read();
        if (c == '\n') {
            break;
        }
        status_line += c;
    }
    
    // Check if we got a valid status line
    std::string_view status_view(status_line.c_str(), status_line.length());
    if (status_view.substr(0, 8) != "HTTP/1.1") {
        return false;
    }
    
    // Extract status code
    int status_code = std::stoi(std::string(status_view.substr(9, 3)));
    
    // Skip headers
    while (m_client.available()) {
        String line = m_client.readStringUntil('\n');
        if (line == "\r") {  // Empty line marks end of headers
            break;
        }
    }
    
    // Read response body
    String response = "";
    while (m_client.available()) {
        response += (char)m_client.read();
    }
    
    // Parse JSON response (if needed)
    JsonDocument doc;
    DeserializationError error;
    JsonObject obj;
    
    // Handle different status codes
    switch (status_code) {
        case 200:  // Success
            error = deserializeJson(doc, response);
            
            if (error) {
                // If JSON parsing fails but we got 200, it might be an empty response
                // which is valid for an unconfigured UUID
                update_room_id(0);  // Set room_id to 0 for unconfigured UUID
                return true;
            }
            
            // If we have a valid JSON object with room_id, update it
            obj = doc.as<JsonObject>();
            if (obj.containsKey("room_id")) {
                update_room_id(obj["room_id"].as<uint32_t>());
            } else {
                update_room_id(0);  // Set room_id to 0 if no room_id in response
            }
            return true;
            
        case 404:  // Not Found - Valid response for unconfigured UUID
            update_room_id(0);  // Set room_id to 0 for unconfigured UUID
            return true;
            
        case 401:  // Unauthorized
            m_has_token = false;  // Clear token as it's invalid
            return false;
            
        default:  // Any other status code is an error
            return false;
    }
}


