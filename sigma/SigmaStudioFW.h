/*
 * File:			SigmaStudioFW.h
 *
 * Description:  	SigmaStudio System Framwork macro definitions. These 
 *				macros should be implemented for your system's software.
 *
 * This software is distributed in the hope that it will be useful,
 * but is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
 * CONDITIONS OF ANY KIND, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * This software may only be used to program products purchased from
 * Analog Devices for incorporation by you into audio products that 
 * are intended for resale to audio product end users. This software
 * may not be distributed whole or in any part to third parties.
 *
 * Copyright © 2008 Analog Devices, Inc. All rights reserved.
 */	
 
#include "../mcc_generated_files/mcc.h"

#ifndef __SIGMASTUDIOFW_H__
#define __SIGMASTUDIOFW_H__

#define SLAVE_I2C_GENERIC_RETRY_MAX     10
#define CHUNK_SIZE  100 // Chunk size (excluding address bytes)

/* 
 * TODO: Update for your system's data type
 */
typedef unsigned short ADI_DATA_U16;
typedef const unsigned char  ADI_REG_TYPE; // JLU: Added const


/* 
 * Parameter data format
 */
#define SIGMASTUDIOTYPE_FIXPOINT 	0
#define SIGMASTUDIOTYPE_INTEGER 	1

/* 
 * Write to a single Device register
 */
//#define SIGMA_WRITE_REGISTER( devAddress, address, dataLength, data ) {/*TODO: implement macro or define as function*/}

/* 
 * TODO: CUSTOM MACRO IMPLEMENTATION
 * Write to multiple Device registers 
 */
//void SIGMA_WRITE_REGISTER_BLOCK( devAddress, address, length, pData );// {/*TODO: implement macro or define as function*/} 

/* 
 * TODO: CUSTOM MACRO IMPLEMENTATION
 * Writes delay (in ms) 
 */
#define SIGMA_WRITE_DELAY( devAddress, length, pData ) {/*TODO: implement macro or define as function*/}

/*
 * Read device registers 
 */
#define SIGMA_READ_REGISTER( devAddress, address, length, pData ) {/*TODO: implement macro or define as function*/} 

/*
 * Set a register field's value
 */
#define SIGMA_SET_REGSITER_FIELD( regVal, fieldVal, fieldMask, fieldShift )  	{ (regVal) = (((regVal) & (~(fieldMask))) | (((fieldVal) << (fieldShift)) && (fieldMask))) }
  
/*
 * Get the value of a register field
 */
#define SIGMA_GET_REGSITER_FIELD( regVal, fieldMask, fieldShift )  	{ ((regVal) & (fieldMask)) >> (fieldShift) }
 
/* 
 * Convert a floating-point value to SigmaDSP (5.23) fixed point format 
 *    This optional macro is intended for systems having special implementation
 *    requirements (for example: limited memory size or endianness)
 */
#define SIGMASTUDIOTYPE_FIXPOINT_CONVERT( _value ) {/*TODO: IMPLEMENT MACRO*/}

/* 
 * Convert integer data to system compatible format
 *    This optional macro is intended for systems having special implementation
 *    requirements (for example: limited memory size or endianness)
 */
#define SIGMASTUDIOTYPE_INTEGER_CONVERT( _value ) {/*TODO: IMPLEMENT MACRO*/}

/* CUSTOM I2C IMPLEMENTATION */


void SIGMA_WRITE_SAFELOAD(uint8_t safeLoadReg, uint16_t address, uint32_t data);

//extern I2C1_MESSAGE_STATUS status;

void SIGMA_WRITE_REGISTER_BLOCK(int devAddress, int memAddress, int length, ADI_REG_TYPE *pData );
/*{
    uint8_t     writeBuffer[CHUNK_SIZE + 2];
    uint8_t     *pD;
    uint16_t    counter, timeOut, bytesRemaining, chunkAddress;
    uint8_t     chunkNo, chunkSize; // chunkSize is size WITHOUT two address bytes
    

    I2C1_MESSAGE_STATUS status;// = I2C1_MESSAGE_PENDING;

    bytesRemaining = length;
    
    chunkNo = 0;
    
    pD = pData;
    
    while(bytesRemaining > 0)
    {        
        if(bytesRemaining > CHUNK_SIZE)
        {
            chunkSize = CHUNK_SIZE - 0;
        }
        else chunkSize =  bytesRemaining;
        
        if(memAddress == 0x0400) chunkAddress = memAddress + ((CHUNK_SIZE * chunkNo) / 5); // program data
        else chunkAddress = memAddress + ((CHUNK_SIZE * chunkNo) / 4);
        
        // Memory address
        writeBuffer[0] = (chunkAddress >> 8);
        writeBuffer[1] = (chunkAddress & 0xFF);
        // data to be written
        for(uint8_t i = 0; i < chunkSize; i++)
        {
            writeBuffer[2+i] = *pD++;
        }
        // Now it is possible that the slave device will be slow.
        // As a work around on these slaves, the application can
        // retry sending the transaction
        timeOut = 0;
        while(status != I2C1_MESSAGE_FAIL)
        {
            // write one byte to EEPROM (3 is the number of bytes to write)
            I2C1_MasterWrite(  writeBuffer,
                                    chunkSize + 2,
                                    devAddress >> 1,
                                    &status);

            // wait for the message to be sent or status has changed.
            while(status == I2C1_MESSAGE_PENDING);

            if (status == I2C1_MESSAGE_COMPLETE)
                break;

            // if status is  I2C1_MESSAGE_ADDRESS_NO_ACK,
            //               or I2C1_DATA_NO_ACK,
            // The device may be busy and needs more time for the last
            // write so we can retry writing the data, this is why we
            // use a while loop here

            // check for max retry and skip this byte
            if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
                break;
            else
                timeOut++;
        }

        if (status == I2C1_MESSAGE_FAIL)
        {
//            break;
        }

        if(bytesRemaining > chunkSize)
            bytesRemaining -= chunkSize;
        else bytesRemaining = 0;
        
        chunkNo++;
    }
}
*/
    
    



#endif

