//*****************************************************************************
// fxos8700cq.c - Prototypes for the FXOS8700CQ Peripheral
//
//  Created on: Apr 23, 2018
//      Author: Brandon Dixon
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_i2c.h"
#include "driverlib/i2c.h"
#include "inc/hw_memmap.h"
#include "fxos8700cq.h"

void I2AGReceive(uint32_t ui32SlaveAddress, uint8_t ui32SlaveRegister,
             uint8_t *pReceiveData, uint8_t ui8NumBytes)
{
    //specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(I2C0_BASE, ui32SlaveAddress, false);

    //specify register to be read
    I2CMasterDataPut(I2C0_BASE, ui32SlaveRegister);

    //send control byte and register address byte to slave device
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(I2C0_BASE));

    //specify that we are going to read from slave device
    I2CMasterSlaveAddrSet(I2C0_BASE, ui32SlaveAddress, true);

    //if there is only one argument, we only need to use the
    //single send I2C function
    if( 1 == ui8NumBytes )
    {
        //send control byte and read from the register we
        //specified
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

        //wait for MCU to finish transaction
        while(I2CMasterBusy(I2C0_BASE));

        //return data pulled from the specified register
        pReceiveData[0] = I2CMasterDataGet(I2C0_BASE);
    }
    else
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));

        //return data pulled from the specified register
        pReceiveData[0] = I2CMasterDataGet(I2C0_BASE);

        uint8_t ui8Counter;
        for (ui8Counter = 1; ui8Counter < (ui8NumBytes - 1); ui8Counter++ )
        {
            //Initiate send of data from the MCU
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);

            // Wait until MCU is done transferring.
            while(I2CMasterBusy(I2C0_BASE));

            //return data pulled from the specified register
            pReceiveData[ui8Counter] = I2CMasterDataGet(I2C0_BASE);
        }

        //Initiate send of data from the MCU
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));

        //return data pulled from the specified register
        pReceiveData[ui8Counter] = I2CMasterDataGet(I2C0_BASE);
    }
}

//sends an I2C command to the specified slave
void I2CAGSend(uint8_t ui32SlaveAddress, uint8_t ui8NumArgs, ...)
{
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(I2C0_BASE, ui32SlaveAddress, false);

    //stores list of variable number of arguments
    va_list listArguments;

    //specifies the va_list to "open" and the last fixed argument
    //so listArguments knows where to start looking
    va_start(listArguments, ui8NumArgs);

    //put data to be sent into FIFO
    I2CMasterDataPut(I2C0_BASE, va_arg(listArguments, uint32_t));

    //if there is only one argument, we only need to use the
    //single send I2C function
    if( 1 == ui8NumArgs )
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));

        //"close" variable argument list
        va_end(listArguments);
    }

    //otherwise, we start transmission of multiple bytes on the I2C bus
    else
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));

        //send ui8NumArgs-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        uint8_t ui8Counter;
        for(ui8Counter = 1; ui8Counter < (ui8NumArgs - 1); ui8Counter++)
        {
            //put next piece of data into I2C FIFO
            I2CMasterDataPut(I2C0_BASE, va_arg(listArguments, uint32_t));

            //send next data that was just placed into FIFO
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while(I2CMasterBusy(I2C0_BASE));
        }

        //put last piece of data into I2C FIFO
        I2CMasterDataPut(I2C0_BASE, va_arg(listArguments, uint32_t));

        //send next data that was just placed into FIFO
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C0_BASE));

        //"close" variable args list
        va_end(listArguments);
    }
}

void AGStandby(uint32_t ui32SlaveAddress)
{
    uint8_t ui8Register[1];
    I2AGReceive(ui32SlaveAddress, AG_CTRL_REG1, ui8Register, sizeof(ui8Register));
    ui8Register[0] &= ~(0B00000001);
    I2CAGSend(ui32SlaveAddress, 2, AG_CTRL_REG1, ui8Register[0]);
}

void AGActive(uint32_t ui32SlaveAddress)
{
    uint8_t ui8Register[1];
    I2AGReceive(ui32SlaveAddress, AG_CTRL_REG1, ui8Register, sizeof(ui8Register));
    ui8Register[0] |= 0B00000001;
    I2CAGSend(ui32SlaveAddress, 2, AG_CTRL_REG1, ui8Register[0]);
}
void AGAccelRange(uint32_t ui32SlaveAddress,tAccelRange tAFSR)
{
    uint8_t ui8Register[1];
    I2AGReceive(ui32SlaveAddress, AG_XYZ_DATA_CFG, ui8Register, sizeof(ui8Register));
    ui8Register[0] &= ~(0B00000011);
    ui8Register[0] |= tAFSR;
    I2CAGSend(ui32SlaveAddress, 2, AG_XYZ_DATA_CFG, ui8Register[0]);
}

void AGOutputDataRate(uint32_t ui32SlaveAddress, tOutputDataRate tODR)
{
    uint8_t ui8Register[1];
    I2AGReceive(ui32SlaveAddress, AG_CTRL_REG1, ui8Register, sizeof(ui8Register));
    ui8Register[0] &= ~(0B00111000);
    ui8Register[0] |= (tODR << 3 );
    I2CAGSend(ui32SlaveAddress, 2, AG_CTRL_REG1, ui8Register[0]);
}

void AGHybridMode(uint32_t ui32SlaveAddress, tHybridMode tHM)
{
    uint8_t ui8Register[1];
    I2AGReceive(ui32SlaveAddress, AG_M_CTRL_REG1, ui8Register, sizeof(ui8Register));
    ui8Register[0] &= ~(0B00000011);
    ui8Register[0] |= tHM;
    I2CAGSend(ui32SlaveAddress, 2, AG_M_CTRL_REG1, ui8Register[0]);
}

void AGGetData(uint32_t ui32SlaveAddress, tDataType tDT, tRawData *tRD )
{
    uint8_t ui8Register[13];
    I2AGReceive(ui32SlaveAddress, AG_STATUS, ui8Register, sizeof(ui8Register));

    if (ACCEL_DATA == tDT)
    {
        // copy the 14 bit accelerometer byte data into 16 bit words
        tRD->x = (int16_t)(((ui8Register[1] << 8) | ui8Register[2]))>> 2;
        tRD->y = (int16_t)(((ui8Register[3] << 8) | ui8Register[4]))>> 2;
        tRD->z = (int16_t)(((ui8Register[5] << 8) | ui8Register[6]))>> 2;
    }
    else if (MAG_DATA == tDT)
    {
        // copy the magnetometer byte data into 16 bit words
        tRD->x = (ui8Register[7] << 8) | ui8Register[8];
        tRD->y = (ui8Register[9] << 8) | ui8Register[10];
        tRD->z = (ui8Register[11] << 8) | ui8Register[12];
    }
    else
    {
        // put dummy data if no matches occur
        tRD->x = -1;
        tRD->y = -1;
        tRD->z = -1;
    }
}
