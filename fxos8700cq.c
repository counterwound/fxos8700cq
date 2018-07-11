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
#include "fxos8700cq.h"

void AGStandby(uint32_t ui32SlaveAddress)
{
    uint8_t ui8Register[1];
    I2CAGReceive(ui32SlaveAddress, AG_CTRL_REG1, ui8Register, sizeof(ui8Register));
    ui8Register[0] &= ~(0B00000001);
    I2CAGSend(ui32SlaveAddress, AG_CTRL_REG1, ui8Register, sizeof(ui8Register));
}

void AGActive(uint32_t ui32SlaveAddress)
{
    uint8_t ui8Register[1];
    I2CAGReceive(ui32SlaveAddress, AG_CTRL_REG1, ui8Register, sizeof(ui8Register));
    ui8Register[0] |= 0B00000001;
    I2CAGSend(ui32SlaveAddress, AG_CTRL_REG1, ui8Register, sizeof(ui8Register));
}

void AGAccelRange(uint32_t ui32SlaveAddress,tAccelRange tAFSR)
{
    uint8_t ui8Register[1];
    I2CAGReceive(ui32SlaveAddress, AG_XYZ_DATA_CFG, ui8Register, sizeof(ui8Register));
    ui8Register[0] &= ~(0B00000011);
    ui8Register[0] |= tAFSR;
    I2CAGSend(ui32SlaveAddress, AG_XYZ_DATA_CFG, ui8Register, sizeof(ui8Register));
}

void AGOutputDataRate(uint32_t ui32SlaveAddress, tOutputDataRate tODR)
{
    uint8_t ui8Register[1];
    I2CAGReceive(ui32SlaveAddress, AG_CTRL_REG1, ui8Register, sizeof(ui8Register));
    ui8Register[0] &= ~(0B00111000);
    ui8Register[0] |= (tODR << 3 );
    I2CAGSend(ui32SlaveAddress, AG_CTRL_REG1, ui8Register, sizeof(ui8Register));
}

void AGHybridMode(uint32_t ui32SlaveAddress, tHybridMode tHM)
{
    uint8_t ui8Register[1];
    I2CAGReceive(ui32SlaveAddress, AG_M_CTRL_REG1, ui8Register, sizeof(ui8Register));
    ui8Register[0] &= ~(0B00000011);
    ui8Register[0] |= tHM;
    I2CAGSend(ui32SlaveAddress, AG_M_CTRL_REG1, ui8Register, sizeof(ui8Register));
}

void AGGetData(uint32_t ui32SlaveAddress, tDataType tDT, tRawData *tRD )
{
    uint8_t ui8Register[13];
    I2CAGReceive(ui32SlaveAddress, AG_STATUS, ui8Register, sizeof(ui8Register));

    if (ACCEL_DATA == tDT)
    {
        // copy the 14 bit accelerometer byte data into 16 bit words
        tRD->x = (int16_t)((ui8Register[1] << 8) | (ui8Register[2] >> 2));
        tRD->y = (int16_t)((ui8Register[3] << 8) | (ui8Register[4] >> 2));
        tRD->z = (int16_t)((ui8Register[5] << 8) | (ui8Register[6] >> 2));
    }
    else if (MAG_DATA == tDT)
    {
        // copy the magnetometer byte data into 16 bit words
        tRD->x = (int16_t)((ui8Register[7]  << 8) | ui8Register[8] );
        tRD->y = (int16_t)((ui8Register[9]  << 8) | ui8Register[10]);
        tRD->z = (int16_t)((ui8Register[11] << 8) | ui8Register[12]);
    }
    else
    {
        // put dummy data if no matches occur
        tRD->x = -1;
        tRD->y = -1;
        tRD->z = -1;
    }
}
