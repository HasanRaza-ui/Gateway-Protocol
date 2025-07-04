/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CRINGBUFFER.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CRINGBUFFER_H
#define CRINGBUFFER_H

#include "global.h"

class CRingBuffer {
private:
	uint8_t* m_pBuffer;
	uint16_t m_size;
	uint16_t m_readIdx;
	uint16_t m_writeIdx;
	uint16_t m_fillLevel;
public:

    CRingBuffer(uint16_t size = 10);
    ~CRingBuffer();

    RC_t read(uint8_t& data);
    RC_t write(uint8_t data);
    RC_t clear();
    uint16_t getFillLevel() const;
    uint16_t getFreeSpace() const;
    RC_t readPackage(CRingBuffer& dataBuffer, uint16_t packageSize);

};
/********************
**  CLASS END
*********************/
#endif /* CRINGBUFFER_H */
