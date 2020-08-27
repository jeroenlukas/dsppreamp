/*
 * File:   i2c_simplifier.c
 * Author: Jeroen
 *
 * Created on August 13, 2020, 7:59 PM
 */


#include "xc.h"
#include "mcc_generated_files/mcc.h"

#include "i2c_simplifier.h"

#define SLAVE_I2C_GENERIC_RETRY_MAX     10

void i2c_simple_write(uint8_t device_address, int length, uint8_t * data)
{
    //uint8_t     writeBuffer[2];
    //uint8_t     *pD;
    uint16_t    counter, time_out;
    //uint8_t     chunkNo, chunkSize; // chunkSize is size WITHOUT two address bytes
 
    I2C1_MESSAGE_STATUS status;// = I2C1_MESSAGE_PENDING;

   // bytesRemaining = length;
    
    //chunkNo = 0;
    
    //pD = pData;
    time_out = 0;
    while(status != I2C1_MESSAGE_FAIL)
    {
        I2C1_MasterWrite(  data,
                                        length,
                                        device_address >> 1,
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
        if (time_out == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        else
            time_out++;
    
    }
    /*
    
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
    }*/
}

void i2c_simple_write_one_byte(uint8_t device_address, uint8_t data)
{
    i2c_simple_write(device_address, 1, &data);
}


