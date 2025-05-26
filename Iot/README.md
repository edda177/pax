# Chas Challenge 2025 Kusten är Klar PAX Sensor

**SUVX24 Contributors:** Jennifer Gott, Sabina Stawbrink, Oscar Asserlund, Erik Dahl, Johan Modin

[Projektplan](https://github.com/Kusten-ar-klar-Chas-Challenge-2025/pax/blob/main/PROJEKTPLAN.md)

## Beskrivning

En sammanställning av våran IoT-kontrollenhet, dess funktionalitet och design.

**SUVX24 Authors:** Jennifer Gott, Sabina Stawbrink, Oscar Asserlund, Erik Dahl, Johan Modin

#### Komponenter

### PIR-sensor

- **Pin**: 2
- **Beskrivning**: HC-SR501, används för att detektera rörelse i rummet.

### Temp-sensor

- **Pin**:
- **Beskrivning**: DHT11, används för temperaturmätning i rummet.

### Luft-sensor

- **Pin**:
- **Beskrivning**: SPG30, MOX-gas sensor som mäter luftkvaliteten i rummet, mäter VOC och väte (H₂) vilket används för att beräkna eCO₂ värdet.

#### To build the Arduino code you need to configure wifi

Create the file `arduino_secrets.h` in the `/include` folder
This file will not be tracked/uploaded by git/github
Copy the content below and change SSID, password and URL and IPAddress to your values.

```
#ifndef ARDUINO_SECRETS_H
#define ARDUINO_SECRETS_H

#define SECRET_SSID "wifi"
#define SECRET_PASS "password"
#define SERVER_URL "url"
#define SERVER_ENDPOINT "/post"
#define SERVER_PORT 8080
struct ServerConfig {
    IPAddress ip;
    uint16_t port;
};
const ServerConfig SERVER = { IPAddress(192, 0, 0, 0), SERVER_PORT};


#endif
```
