

/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CRINGBUFFER.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
#include <iostream>
using namespace std;

//Own Include Files
#include "CRingBuffer.h"

//Method Implementations

CRingBuffer::CRingBuffer(uint16_t size)
{
	cout << "just created buffer having size " << size << endl;

	m_fillLevel = 0;
	m_readIdx = 0;
	m_writeIdx = 0;

	//Todo: check range
	m_size = size;

	m_pBuffer = new uint8_t[size];
}


CRingBuffer::~CRingBuffer()
{
	delete[] m_pBuffer;
}

RC_t CRingBuffer::read(uint8_t& data)
{
	if (m_fillLevel > 0)
	{
		data = m_pBuffer[m_readIdx++];

		m_readIdx %= m_size;
		m_fillLevel--;

		return RC_SUCCESS;
	}
	else
	{
		return RC_BUFFERUNDERFLOW;
	}

}

RC_t CRingBuffer::write(uint8_t data)
{
	if (m_fillLevel < m_size)
	{
		m_pBuffer[m_writeIdx++] = data;

		m_writeIdx %= m_size;
		m_fillLevel++;

		return RC_SUCCESS;
	}
	else
	{
		return RC_BUFFERUNDERFLOW;
	}
}

RC_t CRingBuffer::clear()
{
	m_fillLevel = 0;
	m_readIdx = 0;
	m_writeIdx = 0;

	return RC_SUCCESS;
}

uint16_t CRingBuffer::getFillLevel() const {
    return m_fillLevel;
}

// Method to get the remaining free space in the buffer
uint16_t CRingBuffer::getFreeSpace() const {
    return static_cast<uint16_t>(m_size - m_fillLevel - 1);
}

RC_t CRingBuffer::readPackage(CRingBuffer& dataBuffer, uint16_t packageSize) {
    RC_t result = RC_SUCCESS;

/*    // Get the available space in the destination buffer
    uint16_t freeSpace = dataBuffer.getFreeSpace();

    // Check if there's enough space in the destination buffer
    if (freeSpace < packageSize) {
        // Not enough space to read the full package
        return RC_INSUFFICIENT_SPACE;
    }*/

    // Read data from the ring buffer and write it to the destination buffer
    uint16_t bytesRead = 0;
    while (bytesRead < packageSize && getFillLevel() > 0) {

        uint8_t data;
        result = read(data);


        if (result != RC_SUCCESS) {
            // Error reading data from the ring buffer
        	cout << "Date has not been read properly" << endl;
            return result;
        }

        // Write the data to the destination buffer
        result = dataBuffer.write(data);

        if (result != RC_SUCCESS) {
            // Error writing data to the destination buffer
        	cout << "Date has not been read properly" << endl;

            return result;
        }

/*        RC_t result1 = dataBuffer.read(data);

        if(result1 == RC_SUCCESS){
        	cout << "Data Read from temp data buffer" << endl;
        	cout << data << endl;
        }*/

        bytesRead++;
    }

    return RC_SUCCESS;
}




