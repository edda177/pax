#ifndef POSTMAN_H
#define POSTMAN_H

#include "networking_base.h"
#include <string_view>
#include <array>
#include <Arduino.h>

struct ServerInfo {
    std::string_view server_base_url;    //!< base url of the server
    uint16_t server_port;                //!< port of the server
    std::string_view server_api_path;    //!< path to the api
    std::string_view rooms_base;         //!< base path for rooms (e.g. "/rooms")
    std::string_view config_endpoint;    //!< path snippet for getting room id
    std::string_view jwt_endpoint;       //!< path for JWT authentication
    std::string_view jwt_user;           //!< JWT authentication username/email
    std::string_view jwt_pass;           //!< JWT authentication password
    std::string_view uuid;               //!< uuid for the room (128 bit with dashes)
    uint32_t room_id;                    //!< room id for the room (up to 4 bytes)
    
    // Buffer and view for constructed room endpoint
    std::array<char, 32> room_endpoint_buffer;  //!< Buffer for room endpoint construction
    std::string_view room_endpoint;             //!< View of current room endpoint
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

    /**
     * @brief Send HTTP request and handle response
     * @param request The HTTP request to send
     * @return true if successful, false otherwise
     */
    bool sendRequest(const String &request);

    /**
     * @brief Get JWT token from server
     * @return true if successful, false otherwise
     */
    bool getJwtToken();

    /**
     * @brief Check if the PostMan has a valid JWT token
     * @return true if the PostMan has a valid JWT token, false otherwise
     */
    bool has_token() const { return m_has_token; }

private:
    const ServerInfo m_server_info;
    NetworkingBase* m_connection;
    String m_jwt_token;  // Store the JWT token
    bool m_has_token;    // Track if we have a valid token

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
     * @brief Create JSON payload for JWT login
     * @return String JSON payload
     */
    String createJwtLoginJSON();
};

#endif // POSTMAN_H