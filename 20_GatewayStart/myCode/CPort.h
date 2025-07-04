/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPORT.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CPORT_H
#define CPORT_H

#include "global.h"
#include "CRingBuffer.h"
#include <string>

class CPort {
protected:
    /**@link aggregationByValue
     * @supplierCardinality 1*/
    CRingBuffer m_ringBufferTx;

    /**@link aggregationByValue
     * @supplierCardinality 1*/
    CRingBuffer m_ringBufferRx;

    uint16_t m_packageSize;

public:

    CPort(uint16_t txSize = 10, uint16_t rxSize = 10, uint16_t packageSize = 1);


    /**
     * \brief Sends one Byte to the buffer
     *
     * \param string data	: IN	Byte to be transmitted
     * \return RC_t:
     * 		 RC_SUCCESS - byte was transmitted
     * 		 RC_BUFFEROVERFLOW - in case of full buffer
     */
    RC_t writeByteStream(std::string const& data);

    /**
     * \brief Receive one Byte from the buffer
     *
     * \param string& data	: OUT	Byte received
     * \return RC_t:
     * 		 RC_SUCCESS - byte was received
     * 		 RC_BUFFERUNDERFLOW - in case of empty buffer
     */
    RC_t readByteStream(std::string& data);

    /**
     * \brief Will transmit all data from TX buffer to hardware
     * \return
     * 		RC_SUCCESS - all ok
     * 		Specific error code in case of error
     */
    RC_t portTx_isr();

    /**
     * \brief Will transmit all data from RX hardware to buffer
     * \return
     * 		RC_SUCCESS - all ok
     * 		Specific error code in case of error
     */

    RC_t portRx_isr();
    bool isOccupied() const;

private:

    bool m_occupied = false;


    /**
     * \brief Sends one Byte to the hardware
     *
     * \param uint8_t data	: IN	Byte to be transmitted
     * \return RC_t:
     * 		 RC_SUCCESS - byte was transmitted
     * 		 Device specific ErrorCode - in case of error
     */

    //		virtual RC_t writeByte_hw(uint8_t data) = 0;

    /**
     * \brief Receive one Byte from the hardware
     *
     * \param uint8_t& data	: OUT	Byte received
     * \return RC_t:
     * 		 RC_SUCCESS - byte was received
     * 		 Device specific ErrorCode - in case of error
     */

    virtual RC_t readByte_hw(uint8_t& data) = 0;


    /**
     * \brief Sends one Package to the hardware
     *
     * \return RC_t:
     * RC_SUCCESS - byte was transmitted
     * Device specific ErrorCode - in case of error
     */
    virtual RC_t writePackage_hw(CRingBuffer& dataBuffer) = 0;

    /**
     * \brief Receive one Package from the hardware
     *
     * \return RC_t:
     * RC_SUCCESS - byte was received
     * Device specific ErrorCode - in case of error
     */
    virtual RC_t readPackage_hw(CRingBuffer& dataBuffer) = 0;

    /**
     * Get the size of a package for the peripheral
     * \return packagesize in byte
     */
    virtual uint16_t getDriverPackageSize() = 0;


};
/********************
**  CLASS END
*********************/
#endif /* CPORT_H */
