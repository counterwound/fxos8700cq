//*****************************************************************************
// fxos8700cq_linaro.c - Prototypes for the FXOS8700CQ Peripheral
//
//  Created on: Jul 5, 2018
//      Author: Brandon Dixon
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include "fxos8700cq_proc.h"

void I2CAGReceive(uint32_t ui32SlaveAddress, uint8_t ui32SlaveRegister,
             uint8_t *pReceiveData, uint8_t ui8NumBytes)
{
    //specify that we are reading from an I2C device
    int file;
    file = open("/dev/i2c-1", O_RDWR);

    //specify that we are writing (a register address) to the
    //slave device
    ioctl(file, I2C_SLAVE, ui32SlaveAddress);

    //return block data pulled from the specified register
    i2c_smbus_read_i2c_block_data(file, ui32SlaveRegister,ui8NumBytes,pReceiveData);

    //close the handler used to read from device
    close(file);
}

//sends an I2C command to the specified slave
void I2CAGSend(uint8_t ui32SlaveAddress, uint8_t ui8NumArgs, ...)
{
  printf("Transmit!\n");
}
