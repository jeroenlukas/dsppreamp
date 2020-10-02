#include "SigmaStudioFW.h"

void SIGMA_WRITE_SAFELOAD(uint8_t safeLoadReg, uint16_t address, uint32_t data)
{
    uint16_t slar[5] = { 2069, 2070, 2071, 2072, 2073 }; // Safeload address registers
    uint16_t sldr[5] = { 2064, 2065, 2066, 2067, 2068 }; // Safeload data registers    
    uint8_t slcc[2] = {0,60};
    
    uint8_t addr_broken[2];    
    addr_broken[0] = (address >> 8) & 0xFF;
    addr_broken[1] = (address) & 0xFF;
    
    uint8_t data_broken[5];
    data_broken[0] = 0;
    data_broken[1] = (data >> 24) & 0xFF;
    data_broken[2] = (data >> 16) & 0xFF;
    data_broken[3] = (data >> 8) & 0xFF;
    data_broken[4] = (data) & 0xFF;
    
    SIGMA_WRITE_REGISTER_BLOCK(0x68, slar[safeLoadReg], 2, addr_broken); // Write the safeload ADDRESS (2 bytes)
    __delay_us(100);
    //__delay_ms(1);
    SIGMA_WRITE_REGISTER_BLOCK(0x68, sldr[safeLoadReg], 5, data_broken); // Write the safeload DATA
    __delay_us(100);
    //__delay_ms(1);
    SIGMA_WRITE_REGISTER_BLOCK(0x68, 2076, 2, slcc); // Flip IST bit
    
}

// count <= 5 !
void SIGMA_WRITE_SAFELOAD_MULTI(uint8_t count, uint16_t address[], uint32_t data[])
{
    uint16_t slar[5] = { 2069, 2070, 2071, 2072, 2073 }; // Safeload address registers
    uint16_t sldr[5] = { 2064, 2065, 2066, 2067, 2068 }; // Safeload data registers    
    uint8_t slcc[2] = {0,60};
    
    uint8_t addr_broken[2];    
    uint8_t data_broken[5];
    
    for(int i = 0; i < count; i++)
    {
        addr_broken[0] = (address[i] >> 8) & 0xFF;
        addr_broken[1] = (address[i]) & 0xFF;    

        data_broken[0] = 0;
        data_broken[1] = (data[i] >> 24) & 0xFF;
        data_broken[2] = (data[i] >> 16) & 0xFF;
        data_broken[3] = (data[i] >> 8) & 0xFF;
        data_broken[4] = (data[i]) & 0xFF;

        SIGMA_WRITE_REGISTER_BLOCK(0x68, slar[i], 2, addr_broken); // Write the safeload ADDRESS (2 bytes)
        __delay_us(100);
        //__delay_ms(1);
        SIGMA_WRITE_REGISTER_BLOCK(0x68, sldr[i], 5, data_broken); // Write the safeload DATA
    }
    __delay_us(100);
    //__delay_ms(1);
    SIGMA_WRITE_REGISTER_BLOCK(0x68, 2076, 2, slcc); // Flip IST bit
    
}

void SIGMA_WRITE_REGISTER_BLOCK(int devAddress, int memAddress, int length, ADI_REG_TYPE *pData )
{
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
