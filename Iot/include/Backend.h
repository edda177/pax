//! @file Backend.h
//! Functions for communicating with the backend server

#ifndef PAX_BACKEND_H
#define PAX_BACKEND_H

#include <string_view>
#include <array>
#include <cstdint>
#include <WiFiS3.h>
#include "certificates.h"

struct ServerInfo {
    std::string_view server_base_url;    //!< base url of the server
    uint16_t server_port;                //!< port of the server

    std::string_view server_cert = root_cert;  //!< server certificate from PROGMEM

    std::string_view server_api_path;    //!< path to the api
    std::string_view rooms_base;         //!< base path for rooms (e.g. "/rooms")
    std::string_view config_endpoint;    //!< path snippet for getting room id
    std::string_view jwt_endpoint;       //!< path for JWT authentication
    std::string_view jwt_user;           //!< JWT authentication username/email
    std::string_view jwt_pass;           //!< JWT authentication password
    std::string_view uuid;               //!< uuid for the room (128 bit with dashes)
    uint32_t room_id;                    //!< room id for the room (up to 4 bytes)
    
    //! Buffer and view for constructed room endpoint
    std::array<char, 64> room_endpoint_buffer;  //!< Buffer for room endpoint construction
    std::string_view room_endpoint = room_endpoint_buffer.data();             //!< View of current room endpoint
    std::array<char, 256> jwt_token_buffer;      //!< Buffer for JWT token
    std::string_view jwt_token = jwt_token_buffer.data();                 //!< View of current JWT token

    #ifdef SERVER //! If we have defines for the values, use them
    ServerInfo() : server_base_url(SERVER), server_port(SERVER_PORT), server_api_path(API_PATH), rooms_base(ROOMS_BASE), config_endpoint(CONFIG_ENDPOINT), jwt_endpoint(JWT_ENDPOINT), jwt_user(JWT_USER), jwt_pass(JWT_PASS), uuid(UUID), room_id(ROOM_ID) {}
    #else
    ServerInfo() : room_endpoint_buffer(), jwt_token_buffer() {}
    #endif // 

    ServerInfo(std::string_view url, uint16_t port) : server_base_url(url), server_port(port) {}

    void set_jwt_token(std::string_view token);
    void set_room_endpoint(std::string_view endpoint);

    //! Check if the server info is properly configured
    bool is_configured() const {
        return !server_base_url.empty() && 
               server_port != 0 && 
               !server_cert.empty() && 
               !server_api_path.empty() && 
               !jwt_endpoint.empty() && 
               !jwt_user.empty() && 
               !jwt_pass.empty() && 
               !uuid.empty();
    }
};

class Backend {
public:
    //! Construct a new Backend object
    //! @param server_info Server configuration information
    Backend(ServerInfo& server_info);

    //! Initialize the backend connection
    //! @return true if successful, false otherwise
    bool begin();

    //! Login to get JWT token
    //! @return true if successful, false otherwise
    bool login_jwt();

    //! Update the room ID in the server info
    //! @param room_id The room ID to set
    void update_room_id(uint32_t room_id);

    //! Send room state update to server
    //! @param temperature Current room temperature
    //! @param activity Current room activity status
    //! @param air_quality Current room air quality
    //! @return true if successful, false otherwise
    bool send_update_room_state(float temperature, bool activity, float air_quality);

    //! Get room configuration from server
    //! @return true if successful, false otherwise
    bool get_room_config();

    //! Check if we have a valid JWT token (internal state only)
    //! @return true if we have a token, false otherwise
    bool has_token() const { return m_has_token; }

    //! Check if we have a valid room ID (internal state only)
    //! @return true if we have a room ID, false otherwise
    bool has_room_id() const { return m_has_room_id; }

    //! Check if the backend is properly configured (internal state only)
    //! @return true if all required configuration is present, false otherwise
    bool is_configured() const { return m_server_info.is_configured(); }

    //! Check if we have an active connection to the server (internal state only)
    //! @return true if connected, false otherwise
    bool is_connected() { return m_client.connected(); }

    //! Check if we can reach the server (makes server contact)
    //! @return true if server is reachable, false otherwise
    bool check_server_connection();

    //! Try to reconnect if connection is down (makes server contact)
    //! @return true if connection is established, false otherwise
    bool ensure_connection();

    //! Check if current JWT token is still valid (makes server contact)
    //! @return true if token is valid, false otherwise
    bool verify_token_validity();

    //! Get the current JWT token
    //! @return string_view of the current JWT token
    std::string_view jwt_token() const { return m_server_info.jwt_token; }

    //! Get the current room endpoint
    //! @return string_view of the current room endpoint
    std::string_view room_endpoint() const { return m_server_info.room_endpoint; }

private:
    ServerInfo& m_server_info;  //!< Server configuration information
    WiFiSSLClient m_client;     //!< SSL client for server communication
    bool m_has_token = false;   //!< Whether we have a valid JWT token
    bool m_has_room_id = false; //!< Whether we have a valid room ID
};

#endif // PAX_BACKEND_H