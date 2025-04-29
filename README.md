# Chas Challenge 2025
## Projektgrupp 2 Extended

### Gruppmedlemmar: 
**SUVX24:** Jennifer Gott, Sabina Stawbrink, Oscar Asserlund, Erik Dahl, Johan Modin  
**FMWX24:** Hannah Bärlin, Hanna Kindholm, Tova Hansen  
**FJSX24:** Alice Eriksson, Phithai Lai, Dennis Granheimer, Rhiannon Brönnimann  

[Projektplan](https://github.com/Kusten-ar-klar-Chas-Challenge-2025/pax/blob/main/PROJEKTPLAN.md)


#### To build the Arduino code you need to configure wifi

Create the file `arduino_secrets.h` in the `/include` folder
This file will not be tracked/uploaded by git/github
Copy the content below and change SSID, password and URL to your local values.

```
#ifndef ARDUINO_SECRETS_H
#define ARDUINO_SECRETS_H

#define SECRET_SSID "wifi"
#define SECRET_PASS "password"
#define SERVER_URL "url"
#define SERVER_ENDPOINT "/post"
#define SERVER_PORT 80

#endif
```