
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPORT.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
using namespace std;


//Own Include Files
#include "CPort.h"
#include <iostream>


//Method Implementations



CPort::CPort(uint16_t txSize, uint16_t rxSize, uint16_t packageSize) : m_ringBufferTx(txSize), m_ringBufferRx(rxSize), m_packageSize(packageSize)
{
	m_occupied = true;
}



RC_t CPort::writeByteStream(string const& data)
{
	RC_t result = RC_ERROR;

	for (uint16_t i = 0; i < data.length(); i++)
	{
		result = m_ringBufferTx.write(data[i]);

		if (RC_SUCCESS != result) return RC_ERROR;
	}

	//Fire TX interrupt
	portTx_isr();

	return result;


}

RC_t CPort::readByteStream(string &data)
{
	string dataFromDriver="";

	RC_t result = RC_ERROR;
	do
	{
		uint8_t ldata = 0;
		result = m_ringBufferRx.read(ldata);
		if (RC_SUCCESS == result)
		{
			dataFromDriver += (char)ldata;
		}
	} while (RC_SUCCESS == result);

	data = dataFromDriver;

	return RC_SUCCESS;
}

RC_t CPort::portTx_isr() {
	RC_t result = RC_SUCCESS;

	//uint8_t data;
	CRingBuffer tempBuffer(20);
	while (m_ringBufferTx.getFillLevel() > 0 && result == RC_SUCCESS) {
		// Read data from m_ringBufferTx and write it to the temporary buffer
		result = m_ringBufferTx.readPackage(tempBuffer, 8); // Assuming package size is 8 bytes

		if (result == RC_SUCCESS) {
			// Transmit the package using writePackage_hw
			result = writePackage_hw(tempBuffer);
		}
	}

    // Todo: error handling to be added later
    return result;
}


RC_t CPort::portRx_isr()
{
    //Todo: real error handling to be added later
    RC_t result = RC_ERROR;
    CRingBuffer tempBuffer(20);
    do
    {
        // Create a temporary CRingBuffer object to hold the received data


        // Call readPackage_hw with the temporary CRingBuffer object
        result = readPackage_hw(tempBuffer);
        if (RC_SUCCESS == result)
        {
            // Read data from the temporary buffer and write it to m_ringBufferRx
            uint8_t data;
            while (tempBuffer.read(data) == RC_SUCCESS)
            {
                m_ringBufferRx.write(data);
            }
        }
    } while (RC_SUCCESS == result);

    return RC_SUCCESS;
}

bool CPort::isOccupied() const {
    return m_occupied;
}

