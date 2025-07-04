
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPORTFACTORY.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files


//Own Include Files
#include "CPortFactory.h"
#include "CentralErrorHandler.h"


//Method Implementations



CPort* CPortFactory::createCanPort(CCanPort::port_t port,
		uint32_t baudrate, uint16_t bufferSizeRx, uint16_t bufferSizeTx, uint16_t packageSize)
{
	return new CCanPort(port, baudrate, bufferSizeRx, bufferSizeTx, packageSize);
}

CPort* CPortFactory::createUartPort(CUartPort::port_t port,
		uint32_t baudrate, uint8_t bits, CUartPort::parity_t parity,
		uint8_t stopbits, uint16_t bufferSizeRx, uint16_t bufferSizeTx, uint16_t packageSize)
{
	return new CUartPort(port, baudrate, bits, parity,stopbits, bufferSizeRx, bufferSizeTx, packageSize);
}

CPort* CPortFactory::createPort(port_t port)
{
    static int asclinCount = 0;
    static int cannCount = 0;

    // Check if the maximum number of ports has been exceeded
    CentralErrorHandler errorHandler;
    errorHandler.checkMaxPorts(asclinCount, cannCount);

    switch (port)
    {
    case UART:
        asclinCount++;
        return createUartPort();
    case CAN:
        cannCount++;
        return createCanPort();
    default:
        /* Some error handling */
        break;
    }

    return nullptr;
}

