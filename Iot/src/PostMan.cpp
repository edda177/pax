#include "../include/PostMan.h"

PostMan::PostMan(const char *serverURL, const char *endpoint, uint16_t port, Stream *stream)
    : serverURL{serverURL}, endpoint{endpoint}, port{port}, m_stream{stream} {}

/**
 * @brief Create the JSON payload that passes sensor data and fetches the current date and time.
 * @param temperature
 * @param occupancyStatus
 * @param airQuality
 * @return String
 */
String PostMan::createJSON(const String &temperature, const String &occupancyStatus, const String &airQuality)
{
    String json = "{\n";
    json += "  \"temperature\": \"" + temperature + "\",\n";
    json += "  \"motion\": \"" + occupancyStatus + "\",\n";
    json += "  \"air_quality\": \"" + airQuality + "\"\n";
    json += "}";
    return json;
}

/**
 * @brief Create HTTP POST request header for the given JSON payload.
 * @param jsonPayload The JSON data to be sent.
 * @return String - The full HTTP POST request header.
 */
String PostMan::createHTTPHeader(const String &json)
{
    String httpRequest = "";
    httpRequest += "POST " + String(endpoint) + " HTTP/1.1\r\n";
    httpRequest += "Host: " + String(serverURL) + "\r\n";
    httpRequest += "Content-Type: application/json\r\n";
    httpRequest += "Content-Length: " + String(json.length()) + "\r\n";
    httpRequest += "Connection: close\r\n\r\n";
    return httpRequest;
}

/**
 * @brief Establish a connection and send the HTTP POST request with the JSON payload constructed from the parameters.
 * @param temperature
 * @param occupancyStatus
 * @param airQuality
 * @return true = succesful transmission to server endpoint
 * @return false = failure to send to server endpoint
 */
bool PostMan::sendPost(const String &temperature, const String &occupancyStatus, const String &airQuality, NetworkingBase &network)
{
    String json = createJSON(temperature, occupancyStatus, airQuality);

    if (network.ready_for_traffic())
    {
        // Construct the HTTP POST request header.
        String httpRequest = createHTTPHeader(json);

        // Adds the json content behind the HTTP header
        httpRequest += json;

        if (!network.current_client()->connect(serverURL, port))
        {
            Serial.println("TCP connection failed.");
            return false;
        }

        // Send the request.
        network.current_client()->print(httpRequest);

        // wait for—and read—the response
        unsigned long start = millis();
        while (network.current_client()->connected() && millis() - start < timeout_SendPost)
        {
            while (network.current_client()->available())
            {
                char c = network.current_client()->read();
                Serial.write(c);
            }
        }

        // Read the server response.
        String response = "";
        while (m_stream->available())
        {
            response += static_cast<char>(m_stream->read());
        }
        network.current_client()->stop();
        return true;
    }
    else
    {
        return false;
    }
}