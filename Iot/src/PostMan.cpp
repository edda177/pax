#include "../include/PostMan.h"

PostMan::PostMan(const ServerInfo &server_info, NetworkingBase* connection)
    : m_server_info{server_info}, m_connection { connection } {}

/**
 * @brief Create the JSON payload for room state data
 * @param temperature Current room temperature
 * @param occupancyStatus Current room occupancy status
 * @param airQuality Current room air quality
 * @return String JSON payload
 */
String PostMan::createRoomStateJSON(const String &temperature, const String &occupancyStatus, const String &airQuality)
{
    String json = "{\n";
    // json += "  \"temperature\": \"" + temperature + "\",\n";     // removed until backend has updated API to include temperature
    json += "  \"available\": \"" + occupancyStatus + "\",\n";
    json += "  \"air_quality\": \"" + airQuality + "\",\n";
    json += "}";
    return json;
}

/**
 * @brief Send room state update to server
 * @param temperature Current room temperature
 * @param occupancyStatus Current room occupancy status
 * @param airQuality Current room air quality
 * @return true if successful, false otherwise
 */
bool PostMan::sendRoomState(const String &temperature, const String &occupancyStatus, const String &airQuality)
{
    String json = createRoomStateJSON(temperature, occupancyStatus, airQuality);
    String httpRequest = createHTTPHeader(json, "PUT", String(m_server_info.room_state_endpoint.data()));
    return sendRequest(httpRequest);
}

/**
 * @brief Send UUID to server to get room ID
 * @param uuid Device UUID
 * @return true if successful, false otherwise
 */
bool PostMan::sendUuid(const std::string_view uuid)
{
    String json = "{\n  \"uuid\": \"" + String(uuid.data()) + "\"\n}";
    String httpRequest = createHTTPHeader(json, "POST", String(m_server_info.config_endpoint.data()));
    return sendRequest(httpRequest);
}

/**
 * @brief Get room ID from server
 * @param room_id Reference to store the room ID
 * @return true if successful, false otherwise
 */
bool PostMan::getRoomId(uint32_t &room_id)
{
    String endpoint = String(m_server_info.config_endpoint.data()) + "/" + String(m_server_info.uuid.data());
    String httpRequest = createHTTPHeader("", "GET", endpoint);
    return sendRequest(httpRequest);
}

/**
 * @brief Create HTTP header with JSON payload
 * @param jsonPayload The JSON data to be sent
 * @param method HTTP method (PUT, GET, etc.)
 * @param endpoint Target endpoint
 * @return String The full HTTP request header
 */
String PostMan::createHTTPHeader(const String &jsonPayload, const String &method, const String &endpoint)
{
    String httpRequest = "";
    httpRequest += method + " " + endpoint + " HTTP/1.1\r\n";
    httpRequest += "Host: " + String(m_server_info.server_base_url.data()) + "\r\n";
    httpRequest += "Content-Type: application/json\r\n";
    httpRequest += "Content-Length: " + String(jsonPayload.length()) + "\r\n";
    httpRequest += "Connection: close\r\n\r\n";
    httpRequest += jsonPayload;
    return httpRequest;
}

/**
 * @brief Send HTTP request and handle response
 * @param request The HTTP request to send
 * @return true if successful, false otherwise
 */
bool PostMan::sendRequest(const String &request)
{
    if (!m_connection->ready_for_traffic()) {
        return false;
    }

    Client* client = m_connection->current_client();

    // If not connected connect to Server
    if (!client->connected()) {
        if (!m_connection->connect_wifi_to_server()) {
            Serial.println("Unable to connect to server");
            return false;
        }
    }

    // Send the request
    uint16_t charsWritten = client->print(request);

    // Wait for a response (with a timeout of 5 seconds)
    unsigned long timeout = millis();
    Serial.print("Client connected: ");
    Serial.println(client->connected());
    while (client->available() == 0) {
        if (millis() - timeout > 5000) {  // 5000 ms timeout
            Serial.println("Timeout: No response from server.");
            return false;
        }
    }

    // Read the server response
    String response = "";
    while (client->available()) {
        response += static_cast<char>(client->read());
    }

    // Log server response
    if (response != "") {
        Serial.println("Server response: ");
        Serial.println(response);
    }

    return true;
}