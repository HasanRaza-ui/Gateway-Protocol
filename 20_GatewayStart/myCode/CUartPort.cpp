
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CUARTPORT.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
#include <iostream>
using namespace std;

//Own Include Files
#include "CUartPort.h"
#include "CRingBuffer.h"

//Method Implementations



CUartPort::CUartPort(port_t port, uint32_t baudrate, uint8_t bits,
		parity_t parity, uint8_t stopbits, uint16_t bufferSizeRx,
		uint16_t bufferSizeTx, uint16_t packageSize) : CPort(bufferSizeTx, bufferSizeRx, packageSize)
{

}

/*RC_t CUartPort::writeByte_hw(uint8_t data)
{
	cout << "Just wrote to UART hardware: " << data << endl;
	return RC_SUCCESS;
}*/

RC_t CUartPort::readByte_hw(uint8_t &data)
{
	static uint8_t fakeData = 'a';
	static uint16_t counter = 0;

	counter++;

	if (counter >= 20) return RC_NODATA;

	data = fakeData++;

	cout << "Just read from UART hardware: " << data << endl;

	return RC_SUCCESS;
}


RC_t CUartPort::writePackage_hw(CRingBuffer& dataBuffer) {
    RC_t result = RC_SUCCESS;

    // Loop through each byte in the ring buffer and write it to UART hardware
    for (size_t i = 0; i < dataBuffer.getFillLevel(); ++i) {
    	uint8_t byte;
        result = dataBuffer.read(byte); // Read one byte from the ring buffer
        if (result != RC_SUCCESS) {
            return result; // Return if reading from buffer fails
        }

        // Write the byte to UART hardware
        cout << "Just wrote to UART hardware: " << byte << endl;
    }

    return RC_SUCCESS;
}


RC_t CUartPort::readPackage_hw(CRingBuffer& dataBuffer) {

    uint8_t byte;
    RC_t result;

    // Read one byte from UART hardware
    result = readByte_hw(byte);

    // Check if data was successfully read
    if (result == RC_SUCCESS) {
        // Write the byte into the provided CRingBuffer
        result = dataBuffer.write(byte);
        if (result != RC_SUCCESS) {
            // If writing to the buffer fails, return the error
            return result;
        }
    }

    return result;
}


uint16_t CUartPort::getDriverPackageSize() {
	return m_packageSize;
}


