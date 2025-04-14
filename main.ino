#include "wifi.h"

Wifi net;

void setup() {
    net.connect();
}

void loop() {
    net.poll();
}
