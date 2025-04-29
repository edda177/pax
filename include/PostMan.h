#ifndef POSTMAN_H
#define POSTMAN_H

#include "networking_base.h"
#include <Arduino.h>
//#include <WiFiS3.h>

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

    String createJSON(const String &temperature, const String &occupancyStatus, const String &airQuality);
    String createHTTPHeader(const String &jsonPayload);
};

#endif // POSTMAN_H