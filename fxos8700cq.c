/*
 * fxos8700cq.c
 *
 *  Created on: Apr 23, 2018
 *      Author: brandon.dixon
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_i2c.h"
#include "driverlib/i2c.h"
#include "inc/hw_memmap.h"
#include "fxos8700cq.h"

uint32_t I2CAGReceive(uint32_t ui32Base, uint32_t ui32SlaveAddress, uint8_t ui32SlaveRegister)
{
    //specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(ui32Base, ui32SlaveAddress, false);

    //specify register to be read
    I2CMasterDataPut(ui32Base, ui32SlaveRegister);

    //send control byte and register address byte to slave device
    I2CMasterControl(ui32Base, I2C_MASTER_CMD_BURST_SEND_START);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(ui32Base));

    //specify that we are going to read from slave device
    I2CMasterSlaveAddrSet(ui32Base, ui32SlaveAddress, true);

    //send control byte and read from the register we
    //specified
    I2CMasterControl(ui32Base, I2C_MASTER_CMD_SINGLE_RECEIVE);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(ui32Base));

    //return data pulled from the specified register
    return I2CMasterDataGet(ui32Base);
}

//sends an I2C command to the specified slave
void I2CAGSend(uint32_t ui32Base, uint8_t ui32SlaveAddress, uint8_t ui8NumArgs, ...)
{
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(ui32Base, ui32SlaveAddress, false);

    //stores list of variable number of arguments
    va_list listArguments;

    //specifies the va_list to "open" and the last fixed argument
    //so listArguments knows where to start looking
    va_start(listArguments, ui8NumArgs);

    //put data to be sent into FIFO
    I2CMasterDataPut(ui32Base, va_arg(listArguments, uint32_t));

    //if there is only one argument, we only need to use the
    //single send I2C function
    if( 1 == ui8NumArgs )
    {
        //Initiate send of data from the MCU
        I2CMasterControl(ui32Base, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(ui32Base));

        //"close" variable argument list
        va_end(listArguments);
    }

    //otherwise, we start transmission of multiple bytes on the I2C bus
    else
    {
        //Initiate send of data from the MCU
        I2CMasterControl(ui32Base, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(ui32Base));

        //send ui8NumArgs-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        uint8_t ui8Counter;
        for(ui8Counter = 1; ui8Counter < (ui8NumArgs - 1); ui8Counter++)
        {
            //put next piece of data into I2C FIFO
            I2CMasterDataPut(ui32Base, va_arg(listArguments, uint32_t));

            //send next data that was just placed into FIFO
            I2CMasterControl(ui32Base, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while(I2CMasterBusy(ui32Base));
        }

        //put last piece of data into I2C FIFO
        I2CMasterDataPut(ui32Base, va_arg(listArguments, uint32_t));

        //send next data that was just placed into FIFO
        I2CMasterControl(ui32Base, I2C_MASTER_CMD_BURST_SEND_FINISH);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(ui32Base));

        //"close" variable args list
        va_end(listArguments);
    }
}

void AGStandby(uint32_t ui32Base, uint32_t ui32SlaveAddress)
{
    uint8_t ui8Register;
    ui8Register = I2CAGReceive(ui32Base, ui32SlaveAddress, AG_CTRL_REG1);
    ui8Register &= ~(0B00000001);
    I2CAGSend(ui32Base, ui32SlaveAddress, 2, AG_CTRL_REG1, ui8Register);
}

void AGActive(uint32_t ui32Base, uint32_t ui32SlaveAddress)
{
    uint8_t ui8Register;
    ui8Register = I2CAGReceive(ui32Base, ui32SlaveAddress, AG_CTRL_REG1);
    ui8Register |= 0B00000001;
    I2CAGSend(ui32Base, ui32SlaveAddress, 2, AG_CTRL_REG1, ui8Register);
}
void AGAccelRange(uint32_t ui32Base, uint32_t ui32SlaveAddress,tAccelRange tAFSR)
{
    uint8_t ui8Register;
    ui8Register = I2CAGReceive(ui32Base, ui32SlaveAddress, AG_XYZ_DATA_CFG);
    ui8Register &= ~(0B00000011);
    ui8Register |= tAFSR;
    I2CAGSend(ui32Base, ui32SlaveAddress, 2, AG_XYZ_DATA_CFG, ui8Register);
}

void AGOutputDataRate(uint32_t ui32Base, uint32_t ui32SlaveAddress, tOutputDataRate tODR)
{
    uint8_t ui8Register;
    ui8Register = I2CAGReceive(ui32Base, ui32SlaveAddress, AG_CTRL_REG1);
    ui8Register &= ~(0B00111000);
    ui8Register |= (tODR << 3 );
    I2CAGSend(ui32Base, ui32SlaveAddress, 2, AG_CTRL_REG1, ui8Register);
}
