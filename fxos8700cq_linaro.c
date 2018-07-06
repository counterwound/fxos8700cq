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
#include "fxos8700cq_linaro.h"

void I2CAGReceive(uint32_t ui32SlaveAddress, uint8_t ui32SlaveRegister, uint8_t *pReceiveData, uint8_t ui8NumBytes)
{

}

//sends an I2C command to the specified slave
void I2CAGSend(uint8_t ui32SlaveAddress, uint8_t ui8NumArgs, ...)
{

}
