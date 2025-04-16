#ifndef NETWORKING_BASE_H
#define NETWORKING_BASE_H

#include <arduino.h>

class NetworkingBase {
private:
    Stream * wifi_ptr;
    Stream * ethernet_ptr;
public:
    NetworkingBase(  );
    const Stream * network() const; // does this mean wifi and ether need to be public?
    ~NetworkingBase();
};

#endif