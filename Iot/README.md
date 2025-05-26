# CC 2025 Kusten är Klar PAX Sensor

**SUVX24 Contributors:** Jennifer Gott, Sabina Stawbrink, Oscar Asserlund, Erik Dahl, Johan Modin

[Projektplan](https://github.com/Kusten-ar-klar-Chas-Challenge-2025/pax/blob/main/PROJEKTPLAN.md)  
En godkänd plan av skolans ledning som är grunden till projektet.

## Beskrivning

En sammanställning av

**SUVX24 Authors:** Jennifer Gott, Sabina Stawbrink, Oscar Asserlund, Erik Dahl, Johan Modin

### Komponenter

|**Komponent**|**I/O Pin**|**Beskrivning**|
|---------------|---------------|-----------|
| **Arduino Uno Rev4 Mini** || Microkontroller för inkoppling |
| **PIR-sensor HC-SR501** |**2**| Används för att detektera rörelse i rummet |
| **Temp-sensor DS18B20** | **6** | Används för temperaturmätning i rummet |
| **Luftkvalitets-sensor SPG30**  | **SDA(A4) / SCL(A5)** | Används för att  mäta luftkvaliteten i rummet |
| **Internet Interface Config Pin** | **7** | Används för att indikera val av nätverks interface |

#### To build the Arduino code you need to configure wifi

Create the file `arduino_secrets.h` in the `/include` folder
This file will not be tracked/uploaded by git/github
Copy the content below and change SSID, password and URL and IPAddress to your values.
Currently running on local server with IPAddress and port 8080

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
