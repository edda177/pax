#ifndef NETWORKING_BASE_H
#define NETWORKING_BASE_H

class NetworkingBase {
public:
    virtual void connect() = 0;
    virtual void poll() = 0;
    virtual ~NetworkingBase() = default;
};

#endif
