//*****************************************************************************
// fxos8700cq_tiva.h - Prototypes for the FXOS8700CQ Peripheral
//
//  Created on: Jul 4, 2018
//      Author: Brandon Dixon
//
//*****************************************************************************

#ifndef FXOS8700CQ_TIVA_H_
#define FXOS8700CQ_TIVA_H_

//*****************************************************************************
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//*****************************************************************************

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
// Functions
//*****************************************************************************

// I2C General Send and receive functions
void I2CAGReceive(uint32_t ui32SlaveAddress, uint8_t ui32SlaveRegister,
                    uint8_t *pReceiveData, uint8_t ui8NumBytes);
void I2CAGSend(uint8_t ui32SlaveAddress, uint8_t ui8NumArgs, ...);

//*****************************************************************************
// Mark the end of the C bindings section for C++ compilers.
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif /* FXOS8700CQ_TIVA_H_ */
