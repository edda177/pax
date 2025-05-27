#include "Backend.h"
#include <Arduino.h>
#include <WiFiS3.h>
#include <ArduinoJson.h>
#include <string_view>
#include <array>
#include <cstdint>
#include <algorithm>

// HTTP header constants
constexpr const char* CONTENT_TYPE_JSON = "Content-Type: application/json\r\n";
constexpr const char* ACCEPT_JSON = "Accept: application/json\r\n";
constexpr const char* USER_AGENT_HEADER = "User-Agent: Arduino/1.0\r\n";

// Composed headers
constexpr const char* JSON_HEADERS =
    "Content-Type: application/json\r\n"
    "Accept: application/json\r\n"
    "User-Agent: Arduino/1.0\r\n";

constexpr const char* ACCEPT_HEADERS =
    "Accept: application/json\r\n"
    "User-Agent: Arduino/1.0\r\n";

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

bool Backend::construct_path(String* dest, std::string_view endpoint, std::string_view subpath, std::string_view query) {
    if (!dest) {
        return false;
    }

    // Calculate maximum possible length
    size_t max_len = 256;  // Reasonable max path length
    size_t needed_len = 0;
    
    // Add lengths of all components
    if (!m_server_info.server_api_path.empty()) {
        needed_len += m_server_info.server_api_path.length() + 1;  // +1 for potential slash
    }
    if (!endpoint.empty()) {
        needed_len += endpoint.length() + 1;  // +1 for potential slash
    }
    if (!subpath.empty()) {
        needed_len += subpath.length() + 1;  // +1 for potential slash
    }
    if (!query.empty()) {
        needed_len += query.length();
    }
    
    // Check if path would be too long
    if (needed_len > max_len) {
        return false;
    }
    
    // Reserve space in destination
    dest->reserve(needed_len);
    dest->remove(0);  // Clear the string
    
    // Start with API path if not empty
    if (!m_server_info.server_api_path.empty()) {
        *dest = m_server_info.server_api_path.data();
        if (!dest->endsWith("/")) {
            *dest += "/";
        }
    }
    
    // Add endpoint if provided
    if (!endpoint.empty()) {
        // If endpoint starts with slash, use it directly
        if (endpoint[0] == '/') {
            *dest += endpoint.data();
        } else {
            // Otherwise ensure we have a slash
            if (!dest->endsWith("/")) {
                *dest += "/";
            }
            *dest += endpoint.data();
        }
    }
    
    // Add subpath if provided
    if (!subpath.empty()) {
        // If subpath starts with slash, use it directly
        if (subpath[0] == '/') {
            *dest += subpath.data();
        } else {
            // Otherwise ensure we have a slash
            if (!dest->endsWith("/")) {
                *dest += "/";
            }
            *dest += subpath.data();
        }
    }
    
    // Add query if provided
    if (!query.empty()) {
        *dest += query.data();
    }
    
    return true;
}

bool Backend::begin() {
    // Set root certificate for SSL
    if (m_server_info.server_cert.empty()) {
        Serial.println(F("Backend: Error - Server certificate is empty"));
        return false;
    }
    
    Serial.println(F("Backend: Setting SSL certificate..."));
    m_client.setCACert(m_server_info.server_cert.data());
    
    // Connect to server with retries
    Serial.print(F("Backend: Connecting to "));
    Serial.print(m_server_info.server_base_url.data());
    Serial.print(F(":"));
    Serial.println(m_server_info.server_port);
    
    const size_t max_retries = 3;
    const time_t retry_delay = 1000;
    
    for (size_t i = 0; i < max_retries; i++) {
        if (m_client.connect(m_server_info.server_base_url.data(), m_server_info.server_port)) {
            // Wait for connection to stabilize
            delay(500);
            if (m_client.connected()) {
                Serial.println(F("Backend: Successfully connected to server"));
                break;
            }
        }
        
        if (i < max_retries - 1) {
            Serial.print(F("Backend: Connection attempt "));
            Serial.print(i + 1);
            Serial.print(F(" failed, retrying in "));
            Serial.print(retry_delay);
            Serial.println(F("ms..."));
            delay(retry_delay);
        } else {
            Serial.println(F("Backend: Error - Failed to connect to server after all retries"));
            return false;
        }
    }
    
    // Get JWT token if we don't have one
    if (!m_has_token) {
        Serial.println(F("Backend: No JWT token, attempting login..."));
        if (!login_jwt()) {
            Serial.println(F("Backend: Error - Failed to get JWT token"));
            return false;
        }
        Serial.println(F("Backend: Successfully obtained JWT token"));
    }
    
    return true;
}

// Helper function to make HTTP requests
HttpResponse Backend::make_http_request(HttpMethod method, std::string_view path, 
                                      std::string_view headers, std::string_view body) {
    HttpResponse response = {-1, "", false};
    
    // Convert method to string
    const char* method_str;
    switch (method) {
        case HttpMethod::GET:    method_str = "GET"; break;
        case HttpMethod::POST:   method_str = "POST"; break;
        case HttpMethod::PATCH:  method_str = "PATCH"; break;
        case HttpMethod::HEAD:   method_str = "HEAD"; break;
        default: 
            response.body = "Invalid HTTP method";
            return response;
    }
    
    // Ensure we have a valid connection before sending request
    if (!ensure_connection()) {
        response.body = "No valid connection for HTTP request";
        Serial.println(F("Backend: Error - No valid connection for HTTP request"));
        return response;
    }
    
    // Verify connection is still valid
    if (!m_client.connected()) {
        response.body = "Lost connection before sending request";
        Serial.println(F("Backend: Error - Lost connection before sending request"));
        return response;
    }
    
    // Construct request
    char request_buffer[1024];
    int content_length = body.empty() ? 0 : body.length();
    
    // Ensure path starts with a slash
    String path_str = path.data();
    if (!path_str.startsWith("/")) {
        path_str = "/" + path_str;
    }
    
    // Print request details before sending
    Serial.print(F("Backend: HTTP Request:\n"));
    Serial.print(F("  "));
    Serial.print(method_str);
    Serial.print(F(" "));
    Serial.print(path_str);
    Serial.println(F(" HTTP/1.1"));
    Serial.print(F("  Host: "));
    Serial.println(m_server_info.server_base_url.data());
    Serial.print(F("  "));
    Serial.println(headers.data());
    Serial.print(F("  Connection: close\n"));
    if (content_length > 0) {
        Serial.print(F("  Content-Length: "));
        Serial.println(content_length);
    }
    Serial.println();
    
    // Construct the request with proper line endings and headers
    int written = snprintf(request_buffer, sizeof(request_buffer),
        "%s %s HTTP/1.1\r\n"
        "Host: %.*s\r\n"
        "%.*s"  // Additional headers
        "Connection: close\r\n"
        "%s"  // Content-Length header if body exists
        "\r\n"  // Empty line to separate headers from body
        "%.*s", // Body if exists
        method_str,
        path_str.c_str(),
        static_cast<int>(m_server_info.server_base_url.length()), m_server_info.server_base_url.data(),
        static_cast<int>(headers.length()), headers.data(),
        content_length > 0 ? "Content-Length: " + String(content_length) + "\r\n" : "",
        static_cast<int>(body.length()), body.data());
    
    if (written >= sizeof(request_buffer)) {
        response.body = "Request buffer overflow";
        Serial.println(F("Backend: Error - Request buffer overflow"));
        return response;
    }
    
    // Send request
    size_t bytes_written = m_client.print(request_buffer);
    if (bytes_written == 0) {
        response.body = "Failed to write request to client";
        Serial.println(F("Backend: Error - Failed to write request to client"));
        return response;
    }
    
    // Verify connection is still valid after sending
    if (!m_client.connected()) {
        response.body = "Lost connection after sending request";
        Serial.println(F("Backend: Error - Lost connection after sending request"));
        return response;
    }
    
    // Wait for initial response with timeout
    Serial.println(F("Backend: Waiting for response..."));
    const unsigned long response_timeout = 5000;  // 5 second timeout
    const unsigned long start_time = millis();
    bool response_started = false;
    
    while (millis() - start_time < response_timeout) {
        if (m_client.available()) {
            response_started = true;
            break;
        }
        delay(50);  // Small delay to prevent tight loop
    }
    
    if (!response_started) {
        response.body = "No response received within timeout";
        Serial.println(F("Backend: Error - No response received within timeout"));
        Serial.print(F("Backend: Connection status: "));
        Serial.println(m_client.connected() ? "connected" : "disconnected");
        return response;
    }
    
    // Read response with timeout
    unsigned long timeout = millis() + response_timeout;
    char buffer[512];
    int bytesRead;
    int totalBytesRead = 0;
    int contentLength = -1;
    bool foundContentLength = false;
    String status_line;
    bool got_status_line = false;
    
    // First pass: read headers
    while (millis() < timeout) {
        if (m_client.available()) {
            bytesRead = m_client.readBytesUntil('\n', buffer, sizeof(buffer) - 1);
            buffer[bytesRead] = '\0';
            
            // Extract status code from first line
            if (!got_status_line) {
                status_line = String(buffer);
                if (status_line.indexOf("HTTP/1.1") == 0) {
                    response.status_code = status_line.substring(9, 12).toInt();
                    got_status_line = true;
                    Serial.print(F("Backend: Response status: "));
                    Serial.println(status_line);
                } else {
                    response.body = "Invalid HTTP response: " + status_line;
                    Serial.print(F("Backend: Error - Invalid HTTP response: "));
                    Serial.println(status_line);
                    return response;
                }
            }
            
            // Look for Content-Length header
            if (!foundContentLength && strncmp(buffer, "Content-Length:", 14) == 0) {
                contentLength = atoi(buffer + 15);
                foundContentLength = true;
            }
            
            // Check for end of headers
            if (bytesRead <= 2 && (buffer[0] == '\r' || buffer[0] == '\n')) {
                break;
            }
            
            totalBytesRead += bytesRead;
        }
        delay(10);
    }
    
    if (!got_status_line) {
        response.body = "Failed to get HTTP status line";
        Serial.println(F("Backend: Error - Failed to get HTTP status line"));
        return response;
    }
    
    // Second pass: read body if needed
    if (foundContentLength && contentLength > 0) {
        Serial.println(F("Backend: Reading response body..."));
        int bodyBytesRead = 0;
        unsigned long body_timeout = millis() + response_timeout;
        
        while (bodyBytesRead < contentLength && millis() < body_timeout) {
            if (m_client.available()) {
                bytesRead = m_client.readBytes(buffer, min(sizeof(buffer) - 1, contentLength - bodyBytesRead));
                buffer[bytesRead] = '\0';
                response.body += String(buffer);
                bodyBytesRead += bytesRead;
            }
            delay(10);
        }
        
        if (bodyBytesRead < contentLength) {
            response.body += "\nWarning: Incomplete body received";
            Serial.println(F("Backend: Warning - Incomplete body received"));
            Serial.print(F("Backend: Connection status: "));
            Serial.println(m_client.connected() ? "connected" : "disconnected");
        }
    }
    
    response.success = response.status_code >= 200 && response.status_code < 300;
    return response;
}

bool Backend::check_server_connection() {
    if (!m_client.connected()) {
        Serial.println(F("Backend: Not connected to server"));
        return false;
    }
    
    HttpResponse response = make_http_request(HttpMethod::HEAD, m_server_info.server_api_path, "", "");
    return response.success;
}

bool Backend::ensure_connection() {
    if (m_client.connected()) {
        return true;
    }
    
    // Try to reconnect with retries
    const size_t max_retries = 3;
    const time_t retry_delay = 1000;
    
    for (size_t i = 0; i < max_retries; i++) {
        if (m_client.connect(m_server_info.server_base_url.data(), m_server_info.server_port)) {
            // Wait for connection to stabilize
            delay(500);
            if (m_client.connected()) {
                Serial.println(F("Backend: Successfully reconnected to server"));
                break;
            }
        }
        
        if (i < max_retries - 1) {
            Serial.print(F("Backend: Reconnection attempt "));
            Serial.print(i + 1);
            Serial.print(F(" failed, retrying in "));
            Serial.print(retry_delay);
            Serial.println(F("ms..."));
            delay(retry_delay);
        } else {
            Serial.println(F("Backend: Error - Failed to reconnect to server after all retries"));
            return false;
        }
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
    
    String path;
    if (!construct_path(&path, m_server_info.endpoints.rooms)) {
        Serial.println(F("Backend: Failed to construct path"));
        return false;
    }
    
    HttpResponse response = make_authenticated_request(HttpMethod::GET, path.c_str(), ACCEPT_HEADERS, "");
    
    if (!response.success) {
        if (response.status_code == 401) {
            Serial.println(F("Backend: Token validation failed - Unauthorized"));
            m_has_token = false;
        } else {
            Serial.print(F("Backend: Token validation failed - Unexpected status: "));
            Serial.println(response.status_code);
        }
        return false;
    }
    
    return true;
}

bool Backend::login_jwt() {
    // Create JSON payload
    StaticJsonDocument<512> doc;
    doc["email"] = m_server_info.jwt_user.data();
    doc["password"] = m_server_info.jwt_pass.data();
    
    String json;
    serializeJson(doc, json);
    
    // Try with relative path first
    String path;
    if (!construct_path(&path, m_server_info.endpoints.auth, m_server_info.auth.login)) {
        Serial.println(F("Backend: Failed to construct relative path"));
        return false;
    }
    
    Serial.println(F("Backend: Sending JWT login request..."));
    Serial.print(F("Backend: Request URL (relative): "));
    Serial.println(path);
    Serial.print(F("Backend: Server URL: "));
    Serial.println(m_server_info.server_base_url.data());
    
    HttpResponse response = make_http_request(HttpMethod::POST, path.c_str(),
        JSON_HEADERS,
        json.c_str());
    
    // If relative path fails, try absolute path
    if (!response.success && response.status_code == 400) {
        Serial.println(F("Backend: Relative path failed, trying absolute path..."));
        
        // Construct path components
        String path_components;
        path_components.reserve(256);
        
        // Add API path if not empty
        if (!m_server_info.server_api_path.empty()) {
            String api_path = m_server_info.server_api_path.data();
            // Remove leading and trailing slashes from API path
            while (api_path.startsWith("/")) {
                api_path.remove(0, 1);
            }
            while (api_path.endsWith("/")) {
                api_path.remove(api_path.length() - 1);
            }
            if (!api_path.isEmpty()) {
                path_components += "/";
                path_components += api_path;
            }
        }
        
        // Add auth endpoint
        String auth_endpoint = m_server_info.endpoints.auth.data();
        // Remove leading and trailing slashes from auth endpoint
        while (auth_endpoint.startsWith("/")) {
            auth_endpoint.remove(0, 1);
        }
        while (auth_endpoint.endsWith("/")) {
            auth_endpoint.remove(auth_endpoint.length() - 1);
        }
        if (!auth_endpoint.isEmpty()) {
            path_components += "/";
            path_components += auth_endpoint;
        }
        
        // Add login endpoint
        String login_endpoint = m_server_info.auth.login.data();
        // Remove leading and trailing slashes from login endpoint
        while (login_endpoint.startsWith("/")) {
            login_endpoint.remove(0, 1);
        }
        while (login_endpoint.endsWith("/")) {
            login_endpoint.remove(login_endpoint.length() - 1);
        }
        if (!login_endpoint.isEmpty()) {
            path_components += "/";
            path_components += login_endpoint;
        }
        
        // Ensure path starts with a slash
        if (!path_components.startsWith("/")) {
            path_components = "/" + path_components;
        }
        
        Serial.print(F("Backend: Request path: "));
        Serial.println(path_components);
        Serial.print(F("Backend: Full request details:\n"));
        Serial.print(F("  Method: POST\n"));
        Serial.print(F("  Host: "));
        Serial.println(m_server_info.server_base_url.data());
        Serial.print(F("  Path: "));
        Serial.println(path_components);
        Serial.print(F("  Headers:\n"));
        Serial.print(F("    Content-Type: application/json\n"));
        Serial.print(F("    Accept: application/json\n"));
        Serial.print(F("    Connection: close\n"));
        Serial.print(F("    Content-Length: "));
        Serial.println(json.length());
        
        response = make_http_request(HttpMethod::POST, path_components.c_str(),
            JSON_HEADERS,
            json.c_str());
    }
    
    if (!response.success) {
        if (response.status_code == 401) {
            Serial.println(F("Backend: Error - Invalid credentials (401 Unauthorized)"));
        } else {
            Serial.print(F("Backend: Error - Unexpected status code: "));
            Serial.println(response.status_code);
            Serial.print(F("Backend: Response details:\n"));
            Serial.print(F("  Status: "));
            Serial.println(response.status_code);
            Serial.print(F("  Success: "));
            Serial.println(response.success ? "true" : "false");
            Serial.print(F("  Body length: "));
            Serial.println(response.body.length());
        }
        m_has_token = false;
        return false;
    }
    
    // Parse JSON response
    StaticJsonDocument<512> response_doc;
    DeserializationError error = deserializeJson(response_doc, response.body);
    
    if (error) {
        Serial.print(F("Backend: JSON parse error: "));
        Serial.println(error.c_str());
        return false;
    }
    
    if (response_doc.containsKey("token")) {
        const char* token = response_doc["token"].as<const char*>();
        m_server_info.set_jwt_token(std::string_view(token));
        m_has_token = true;
        Serial.println(F("Backend: Successfully parsed and stored JWT token"));
        return true;
    }
    
    Serial.println(F("Backend: Error - No token in response"));
    Serial.print(F("Backend: Response keys: "));
    for (JsonPair kv : response_doc.as<JsonObject>()) {
        Serial.print(kv.key().c_str());
        Serial.print(F(" "));
    }
    Serial.println();
    return false;
}

void Backend::update_room_id(uint32_t room_id) {
    m_server_info.room_id = room_id;
    String endpoint = String(m_server_info.endpoints.rooms.data()) + "/" + String(room_id);
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
    
    // Create JSON payload
    StaticJsonDocument<512> doc;
    doc["temperature"] = temperature;
    doc["activity"] = activity;
    doc["air_quality"] = air_quality;
    
    String json;
    serializeJson(doc, json);
    
    String path;
    if (!construct_path(&path, m_server_info.endpoints.rooms, 
                       String(m_server_info.room_id).c_str())) {
        Serial.println(F("Backend: Failed to construct path"));
        return false;
    }
    
    HttpResponse response = make_authenticated_request(HttpMethod::PATCH, path.c_str(), 
        JSON_HEADERS, json.c_str());
    
    if (!response.success) {
        if (response.status_code == 401) {
            Serial.println(F("Backend: Update failed - Unauthorized"));
            m_has_token = false;
        } else if (response.status_code == 404) {
            Serial.println(F("Backend: Update failed - Room not found"));
            m_has_room_id = false;
            update_room_id(0);
        } else {
            Serial.print(F("Backend: Update failed - Unexpected status: "));
            Serial.println(response.status_code);
            Serial.print(F("Backend: Response body: "));
            Serial.println(response.body);
        }
        return false;
    }
    
    return true;
}

bool Backend::get_room_config() {
    if (!m_has_token) {
        return false;
    }
    
    // Ensure we have a valid connection
    if (!ensure_connection()) {
        return false;
    }
    
    String path;
    if (!construct_path(&path, m_server_info.endpoints.config, m_server_info.uuid.data())) {
        Serial.println(F("Backend: Failed to construct path"));
        return false;
    }
    
    HttpResponse response = make_authenticated_request(HttpMethod::GET, path.c_str(), ACCEPT_HEADERS, "");
    
    // Parse JSON response
    StaticJsonDocument<512> doc;
    DeserializationError error;
    
    switch (response.status_code) {
        case 200:  // Success
            error = deserializeJson(doc, response.body);
            if (error) {
                Serial.print(F("Backend: JSON parse error: "));
                Serial.println(error.c_str());
                update_room_id(0);
                return true;  // Still return true as this is valid for unconfigured UUID
            }
            
            if (doc.containsKey("room_id")) {
                update_room_id(doc["room_id"].as<uint32_t>());
            } else {
                update_room_id(0);
            }
            return true;
            
        case 404:  // Not Found - Valid for unconfigured UUID
            Serial.println(F("Backend: Room not found - Valid for unconfigured UUID"));
            update_room_id(0);
            return true;
            
        case 401:  // Unauthorized
            Serial.println(F("Backend: Config request failed - Unauthorized"));
            m_has_token = false;
            return false;
            
        default:  // Any other status code is an error
            Serial.print(F("Backend: Config request failed - Unexpected status: "));
            Serial.println(response.status_code);
            Serial.print(F("Backend: Response body: "));
            Serial.println(response.body);
            return false;
    }
}

// Helper function to make authenticated HTTP requests
HttpResponse Backend::make_authenticated_request(HttpMethod method, std::string_view path, 
                                               std::string_view headers, std::string_view body) {
    if (!m_has_token || m_server_info.jwt_token.empty()) {
        Serial.println(F("Backend: Error - No valid token for authenticated request"));
        return {-1, "Error: No valid token", false};
    }
    
    // Add Authorization header
    char auth_header[256];
    int auth_written = snprintf(auth_header, sizeof(auth_header),
        "Authorization: Bearer %.*s\r\n",
        static_cast<int>(m_server_info.jwt_token.length()), m_server_info.jwt_token.data());
    
    if (auth_written >= sizeof(auth_header)) {
        Serial.println(F("Backend: Error - Auth header buffer overflow"));
        return {-1, "Error: Auth header buffer overflow", false};
    }
    
    // Combine headers
    String combined_headers = String(auth_header) + headers.data();
    
    return make_http_request(method, path, combined_headers.c_str(), body);
}


