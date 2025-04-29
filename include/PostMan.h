#ifndef POSTMAN_H
#define POSTMAN_H

#include "networking_base.h"
#include <Arduino.h>

class PostMan
{
public:
    PostMan(const char *serverURL, const char *endpoint, uint16_t port, Stream *stream);
    bool sendPost(const String &temperature, const String &occupancyStatus, const String &airQuality);
    bool sendPost(const String &temperature, const String &occupancyStatus, const String &airQuality, NetworkingBase &network);

private:
    const char *serverURL;
    const char *endpoint;
    uint16_t port;
    Stream *m_stream;
    static constexpr int timeout_SendPost = 5000;

    String createJSON(const String &temperature, const String &occupancyStatus, const String &airQuality);
    String createHTTPHeader(const String &jsonPayload);
};

#endif // POSTMAN_H