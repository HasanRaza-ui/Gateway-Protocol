#ifndef CENTRAL_ERROR_HANDLER_H
#define CENTRAL_ERROR_HANDLER_H

#include <iostream>
#include <exception>

class CentralErrorHandler {
public:
    void terminate();
    void handlePortError();
    void handleNullPointerError();
    void handleOccupiedPortError();
    void checkMaxPorts(int asclinCount, int cannCount);
};

#endif // CENTRAL_ERROR_HANDLER_H
