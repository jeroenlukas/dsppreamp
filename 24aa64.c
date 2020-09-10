/*
 * File:   24aa64.c
 * Author: Jeroen
 *
 * Created on August 15, 2020, 8:21 PM
 */


#include "xc.h"
#include <stdint.h>
#include "config.h"
#include "i2c_simplifier.h"
#include "mcc_generated_files/mcc.h"
#include "24aa64.h"


#define SLAVE_I2C_GENERIC_RETRY_MAX     10

/*void eeprom_write_one_byte(uint16_t address, uint8_t value)
{
    uint8_t i2c_data[3];
    i2c_data[0] = (address >> 8) & 0xFF; // Address high byte
    i2c_data[1] = (address >> 0) & 0xFF; // Address low byte
    i2c_data[2] = value; // Data
    //i2c_simple_write(I2C_ADDRESS_EEPROM_WRITE, 3, i2c_data);
}

uint8_t eeprom_read_one_byte(uint16_t address)
{
    uint8_t i2c_data[3];
    
    return 1;
    // ...
}*/

uint8_t eeprom_read_model_parameter(uint8_t model_id, uint8_t parameter)
{
   return eeprom_read_one_byte(EEPROM_MODEL_START + (model_id * EEPROM_MODEL_SIZE) + parameter);
}

void eeprom_write_one_byte(uint16_t data_address, uint8_t value)
{
    
    /*uint8_t         sourceData[16] = {  0xA0, 0xA1, 0xA2, 0xA3, 
                                        0xA4, 0xA5, 0xA6, 0xA7, 
                                        0xA8, 0xA9, 0xAA, 0xAB, 
                                        0xAC, 0xAD, 0xAE, 0xAF }; 
    uint8_t         *pData;
    uint16_t        nCount;

    
    uint8_t         *pD;*/
    uint8_t         writeBuffer[3];
    uint16_t        counter, timeOut;

    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;

    //dataAddress = 0x10;             // starting EEPROM address 
    //pD = sourceData;                // initialize the source of the data
    //nCount = 16;                    // number of bytes to write

    //for (counter = 0; counter < nCount; counter++)
    //{

        // build the write buffer first
        // starting address of the EEPROM memory
        writeBuffer[0] = (data_address >> 8);                // high address
        writeBuffer[1] = (uint8_t)(data_address);            // low low address

        // data to be written
        writeBuffer[2] = value; //*pD++;

        // Now it is possible that the slave device will be slow.
        // As a work around on these slaves, the application can
        // retry sending the transaction
        timeOut = 0;
        while(status != I2C1_MESSAGE_FAIL)
        {
            // write one byte to EEPROM (3 is the number of bytes to write)
            I2C1_MasterWrite(  writeBuffer,
                                    3,
                                    I2C_ADDRESS_EEPROM,
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
       //     break;
        }
//        dataAddress++;

    //}
}

 #define MCHP24AA512_RETRY_MAX  100  // define the retry count
//#define MCHP24AA512_ADDRESS    0x50 // slave device address

uint8_t eeprom_read_one_byte(uint16_t address)
{
    I2C1_MESSAGE_STATUS status;
    uint8_t     writeBuffer[3];
    uint8_t pData[2];
    uint16_t    timeOut;
    uint16_t    counter;
    uint8_t     *pD, ret;

    pD = pData;

    //for (counter = 0; counter < nCount; counter++)
    {

        // build the write buffer first
        // starting address of the EEPROM memory
        writeBuffer[0] = (address >> 8);                // high address
        writeBuffer[1] = (uint8_t)(address);            // low low address

        // Now it is possible that the slave device will be slow.
        // As a work around on these slaves, the application can
        // retry sending the transaction
        timeOut = 0;
        while(status != I2C1_MESSAGE_FAIL)
        {
            // write one byte to EEPROM (2 is the count of bytes to write)
            I2C1_MasterWrite(   writeBuffer,
                                    2,
                                    I2C_ADDRESS_EEPROM,
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
            if (timeOut == MCHP24AA512_RETRY_MAX)
                break;
            else
                timeOut++;
        }

        if (status == I2C1_MESSAGE_COMPLETE)
        {

            // this portion will read the byte from the memory location.
            timeOut = 0;
            while(status != I2C1_MESSAGE_FAIL)
            {
                // write one byte to EEPROM (2 is the count of bytes to write)
                I2C1_MasterRead(    pD,
                                        1,
                                        I2C_ADDRESS_EEPROM,
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
                if (timeOut == MCHP24AA512_RETRY_MAX)
                    break;
                else
                    timeOut++;
            }
        }

        // exit if the last transaction failed
        if (status == I2C1_MESSAGE_FAIL)
        {
            ret = 0;
           // break;
        }

       // pD++;
       // address++;

    }
    return pData[0];
}


uint8_t eeprom_read_multi(uint16_t address, uint8_t *pData, uint16_t nCount)
{
    I2C1_MESSAGE_STATUS status;
    uint8_t     writeBuffer[3];
    uint16_t    timeOut;
    uint16_t    counter;
    uint8_t     *pD, ret;

    pD = pData;

    for (counter = 0; counter < nCount; counter++)
    {

        // build the write buffer first
        // starting address of the EEPROM memory
        writeBuffer[0] = (address >> 8);                // high address
        writeBuffer[1] = (uint8_t)(address);            // low low address

        // Now it is possible that the slave device will be slow.
        // As a work around on these slaves, the application can
        // retry sending the transaction
        timeOut = 0;
        while(status != I2C1_MESSAGE_FAIL)
        {
            // write one byte to EEPROM (2 is the count of bytes to write)
            I2C1_MasterWrite(   writeBuffer,
                                    2,
                                    I2C_ADDRESS_EEPROM,
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
            if (timeOut == MCHP24AA512_RETRY_MAX)
                break;
            else
                timeOut++;
        }

        if (status == I2C1_MESSAGE_COMPLETE)
        {

            // this portion will read the byte from the memory location.
            timeOut = 0;
            while(status != I2C1_MESSAGE_FAIL)
            {
                // write one byte to EEPROM (2 is the count of bytes to write)
                I2C1_MasterRead(    pD,
                                        1,
                                        I2C_ADDRESS_EEPROM,
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
                if (timeOut == MCHP24AA512_RETRY_MAX)
                    break;
                else
                    timeOut++;
            }
        }

        // exit if the last transaction failed
        if (status == I2C1_MESSAGE_FAIL)
        {
            ret = 0;
            break;
        }

        pD++;
        address++;

    }
    return (ret);

}


uint16_t dataAddress;
uint8_t         sourceData[16] = {  0xA0, 0xA1, 0xA2, 0xA3, 
                                    0xA4, 0xA5, 0xA6, 0xA7, 
                                    0xA8, 0xA9, 0xAA, 0xAB, 
                                    0xAC, 0xAD, 0xAE, 0xAF }; 

void eeprom_write_multi(uint16_t data_address, uint8_t *pData, uint16_t nCount)
{
    uint8_t         writeBuffer[3];
    uint8_t         *pD;
    uint16_t        counter, timeOut;

    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;

    //dataAddress = 0x10;             // starting EEPROM address 
    pD = sourceData;                // initialize the source of the data
    nCount = 16;                    // number of bytes to write

    for (counter = 0; counter < nCount; counter++)
    {

        // build the write buffer first
        // starting address of the EEPROM memory
        writeBuffer[0] = (dataAddress >> 8);                // high address
        writeBuffer[1] = (uint8_t)(dataAddress);            // low low address

        // data to be written
        writeBuffer[2] = *pD++;

        // Now it is possible that the slave device will be slow.
        // As a work around on these slaves, the application can
        // retry sending the transaction
        timeOut = 0;
        while(status != I2C1_MESSAGE_FAIL)
        {
            // write one byte to EEPROM (3 is the number of bytes to write)
            I2C1_MasterWrite(  writeBuffer,
                                    3,
                                    I2C_ADDRESS_EEPROM,
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
            break;
        }
        dataAddress++;

    }
}