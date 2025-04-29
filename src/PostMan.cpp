#include "../include/PostMan.h"

PostMan::PostMan(const char *server, const char *endpoint, uint16_t port, NetworkingBase* connection)
    : server{server}, endpoint{endpoint}, port{port}, m_connection { connection } {}

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
    json += "  \"air_quality\": \"" + airQuality + "\",\n";
    json += "}";
    return json;
}

/**
 * @brief Establish a connection and send the HTTP POST request with the JSON payload constructed from the parameters.
 * @param temperature
 * @param occupancyStatus
 * @param airQuality
 * @return true = succesful transmission to server endpoint
 * @return false = failure to send to server endpoint
 */
bool PostMan::sendPost(const String &temperature, const String &occupancyStatus, const String &airQuality)
{
    String json = createJSON(temperature, occupancyStatus, airQuality);

    if ( m_connection->ready_for_traffic() ) 
    {
        
        Client* client = m_connection->current_client();
        // Construct the HTTP POST request header.
        String httpRequest = createHTTPHeader(json);

        // Adds the json content behind the HTTP header
        httpRequest += json;

        // Send the request.
        client->print(httpRequest);

        // Wait for a response (with a timeout of 5 seconds).
        unsigned long timeout = millis();
        while (client->available() == 0)
        {
            m_connection->current_client()->setTimeout(5000);
        }

        // Read the server response.
        String response = "";
        while (client->available())
        {
            response += static_cast<char>(client->read());
        }
        return true;
    }
    else
    {
        return false;
    }
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
    httpRequest += "Host: " + String(server) + "\r\n";
    httpRequest += "Content-Type: application/json\r\n";
    httpRequest += "Content-Length: " + String(json.length()) + "\r\n";
    httpRequest += "Connection: close\r\n\r\n";
    httpRequest += json;
    return httpRequest;
}