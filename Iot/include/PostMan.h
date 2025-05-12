#ifndef POSTMAN_H
#define POSTMAN_H

#include "networking_base.h"
#include <Arduino.h>

class PostMan
{
public:
    PostMan(const char *server, const char *endpoint, uint16_t port, NetworkingBase* connection);
    bool sendPost(const String &temperature, const String &occupancyStatus, const String &airQuality);

private:
    const char *server;
    const char *endpoint;
    uint16_t port;
    NetworkingBase* m_connection;

    String createHTTPHeaderWithJSON(const String &jsonPayload);
    String createJSON(const String &temperature, const String &occupancyStatus, const String &airQuality);
};

#endif // POSTMAN_H