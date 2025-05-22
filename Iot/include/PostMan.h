#ifndef POSTMAN_H
#define POSTMAN_H

#include "networking_base.h"
#include <string_view>
#include <Arduino.h>

struct ServerInfo {
    std::string_view server_base_url; //!< base url of the server
    uint16_t server_port; //!< port of the server
    std::string_view server_api_path; //!< path to the api
    std::string_view room_state_endpoint; //!< path snippet for sending room update information, send PUT to room_state_endpoint/room_id
    std::string_view config_endpoint; //!< path snippet for getting room id, send GET request to config_endpoint/uuid
    std::string_view uuid; //!< uuid for the room (128 bit with dashes)
    uint32_t room_id; //!< room id for the room (up to 4 bytes)
};

class PostMan
{
public:
    /**
     * @brief Construct a new PostMan object with ServerInfo
     * @param server_info Server configuration information
     * @param connection Network connection handler
     */
    PostMan(const ServerInfo &server_info, NetworkingBase* connection);

    /**
     * @brief Send room state update to server
     * @param temperature Current room temperature
     * @param occupancyStatus Current room occupancy status
     * @param airQuality Current room air quality
     * @return true if successful, false otherwise
     */
    bool sendRoomState(const String &temperature, const String &occupancyStatus, const String &airQuality);

    /**
     * @brief Send UUID to server to get room ID
     * @param uuid Device UUID
     * @return true if successful, false otherwise
     */
    bool sendUuid(const std::string_view uuid);

    /**
     * @brief Get room ID from server
     * @param room_id Reference to store the room ID
     * @return true if successful, false otherwise
     */
    bool getRoomId(uint32_t &room_id);

private:
    const ServerInfo m_server_info;
    NetworkingBase* m_connection;

    /**
     * @brief Create HTTP header with JSON payload
     * @param jsonPayload The JSON data to be sent
     * @param method HTTP method (PUT, GET, etc.)
     * @param endpoint Target endpoint
     * @return String The full HTTP request header
     */
    String createHTTPHeader(const String &jsonPayload, const String &method, const String &endpoint);

    /**
     * @brief Create JSON payload for room state
     * @param temperature Current room temperature
     * @param occupancyStatus Current room occupancy status
     * @param airQuality Current room air quality
     * @return String JSON payload
     */
    String createRoomStateJSON(const String &temperature, const String &occupancyStatus, const String &airQuality);

    /**
     * @brief Send HTTP request and handle response
     * @param request The HTTP request to send
     * @return true if successful, false otherwise
     */
    bool sendRequest(const String &request);
};

#endif // POSTMAN_H