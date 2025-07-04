
#include <iostream>
using namespace std;


#include "CCanPort.h"

CCanPort::CCanPort(port_t port, uint32_t baudrate, uint16_t bufferSizeRx, uint16_t bufferSizeTx, uint16_t packageSize) : CPort(bufferSizeTx, bufferSizeRx, packageSize)
{

}

/*RC_t CCanPort::writeByte_hw(uint8_t data)
{
	cout << "Just wrote to CAN hardware: " << data << endl;
	return RC_SUCCESS;
}*/
RC_t CCanPort::readByte_hw(uint8_t &data)
{
	static uint8_t fakeData = 'A';
	static uint16_t counter = 0;

	counter++;

	if (counter >= 20) return RC_NODATA;

	data = fakeData++;

	cout << "Just read from CAN hardware: " << data << endl;

	return RC_SUCCESS;
}


RC_t CCanPort::writePackage_hw(CRingBuffer& dataBuffer) {
    // Check if the buffer has at least 8 bytes available
/*    if (dataBuffer.getFillLevel() < 8) {
        // If not enough data is available, return an error
        return RC_ERROR;
    }*/

    uint8_t package[8];
    RC_t result;

    // Read 8 bytes from the buffer
    for (int i = 0; i < 8; ++i) {
    	result = dataBuffer.read(package[i]);
    	if((i > 1 && i < 8) && result != RC_SUCCESS){
    		package[i] = 0;
    		continue;
    	}
    	if (result != RC_SUCCESS) {
    		cout << "Data has not been read from Data Buffer" << endl;
    		// If reading from the buffer fails, return the error
    		return result;
    	}
    }

    // Simulate writing to CAN hardware
    cout << "Just wrote to CAN hardware: Package: [ ";
    for (int i = 0; i < 8; ++i) {
    	if(package[i] == 0){
    		continue;
    	}
        cout << package[i];
    }
    cout << " ]" << endl;

    return RC_SUCCESS;
}


RC_t CCanPort::readPackage_hw(CRingBuffer& dataBuffer) {
    // Check if the buffer has enough space to write 8 bytes
    if (dataBuffer.getFreeSpace() < 8) {
        // If there's not enough space in the buffer, return an error
        return RC_ERROR;
    }

    uint8_t package[8];

    // Simulate reading 8 bytes from CAN hardware
    for (int i = 0; i < 8; ++i) {
        // Simulate reading data from CAN hardware (replace this with actual hardware read)
        package[i] = 'A' + i;
    }

    // Write the package to the buffer
    for (int i = 0; i < 8; ++i) {
        // Write each byte to the buffer
        RC_t result = dataBuffer.write(package[i]);
        if (result != RC_SUCCESS) {
            // If writing to the buffer fails, return the error
            return result;
        }
    }

    // Print message indicating successful read from CAN hardware
    cout << "Just read from CAN hardware: Package: [ ";
    for (int i = 0; i < 8; ++i) {
        cout << package[i] << " ";
    }
    cout << "]" << endl;

    return RC_SUCCESS;
}


uint16_t CCanPort::getDriverPackageSize() {

	return m_packageSize;
}



