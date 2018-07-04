//*****************************************************************************
// fxos8700cq.h - Prototypes for the FXOS8700CQ Peripheral
//
//  Created on: Apr 23, 2018
//      Author: Brandon Dixon
//
//*****************************************************************************

#ifndef FXOS8700CQ_H_
#define FXOS8700CQ_H_

//*****************************************************************************
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//*****************************************************************************

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
// Register addreses
//*****************************************************************************
#define AG_STATUS           0x00
#define AG_DR_STATUS        0x00
#define AG_F_STATUS         0x00
#define AG_OUT_X_MSB        0x01
#define AG_OUT_X_LSB        0x02
#define AG_OUT_Y_MSB        0x03
#define AG_OUT_Y_LSB        0x04
#define AG_OUT_Z_MSB        0x05
#define AG_OUT_Z_LSB        0x06
#define AG_F_SETUP          0x09
#define AG_TRIG_CFG         0x0A
#define AG_SYSMOD           0x0B
#define AG_INT_SOURCE       0x0C
#define AG_WHO_AM_I         0x0D
#define AG_XYZ_DATA_CFG     0x0E
#define AG_HP_FILTER_CUTOFF 0x0F
#define AG_PL_STATUS        0x10
#define AG_PL_CFG           0x11
#define AG_PL_COUNT         0x12
#define AG_PL_BF_ZCOMP      0x13
#define AG_P_L_THS_REG      0x14
#define AG_A_FFMT_CFG       0x15
#define AG_A_FFMT_SRC       0x16
#define AG_A_FFMT_THS       0x17
#define AG_A_FFMT_COUNT     0x18
#define AG_TRANSIENT_CFG    0x1D
#define AG_TRANSIENT_SRC    0x1E
#define AG_TRANSIENT_THS    0x1F
#define AG_TRANSIENT_COUNT  0x20
#define AG_PULSE_CFG        0x21
#define AG_PULSE_SRC        0x22
#define AG_PULSE_THSX       0x23
#define AG_PULSE_THSY       0x24
#define AG_PULSE_THSZ       0x25
#define AG_PULSE_TMLT       0x26
#define AG_PULSE_LTCY       0x27
#define AG_PULSE_WIND       0x28
#define AG_ASLP_COUNT       0x29
#define AG_CTRL_REG1        0x2A
#define AG_CTRL_REG2        0x2B
#define AG_CTRL_REG3        0x2C
#define AG_CTRL_REG4        0x2D
#define AG_CTRL_REG5        0x2E
#define AG_OFF_X            0x2F
#define AG_OFF_Y            0x30
#define AG_OFF_Z            0x31
#define AG_M_DR_STATUS      0x32
#define AG_M_OUT_X_MSB      0x33
#define AG_M_OUT_X_LSB      0x34
#define AG_M_OUT_Y_MSB      0x35
#define AG_M_OUT_Y_LSB      0x36
#define AG_M_OUT_Z_MSB      0x37
#define AG_M_OUT_Z_LSB      0x38
#define AG_CMP_OUT_X_MSB    0x39
#define AG_CMP_OUT_X_LSB    0x3A
#define AG_CMP_OUT_Y_MSB    0x3B
#define AG_CMP_OUT_Y_LSB    0x3C
#define AG_CMP_OUT_Z_MSB    0x3D
#define AG_CMP_OUT_Z_LSB    0x3E
#define AG_M_OFF_X_MSB      0x3F
#define AG_M_OFF_X_LSB      0x40
#define AG_M_OFF_Y_MSB      0x41
#define AG_M_OFF_Y_LSB      0x42
#define AG_M_OFF_Z_MSB      0x43
#define AG_M_OFF_Z_LSB      0x44
#define AG_MAX_X_MSB        0x45
#define AG_MAX_X_LSB        0x46
#define AG_MAX_Y_MSB        0x47
#define AG_MAX_Y_LSB        0x48
#define AG_MAX_Z_MSB        0x49
#define AG_MAX_Z_LSB        0x4A
#define AG_MIN_X_MSB        0x4B
#define AG_MIN_X_LSB        0x4C
#define AG_MIN_Y_MSB        0x4D
#define AG_MIN_Y_LSB        0x4E
#define AG_MIN_Z_MSB        0x4F
#define AG_MIN_Z_LSB        0x50
#define AG_TEMP             0x51
#define AG_M_THS_CFG        0x52
#define AG_M_THS_SRC        0x53
#define AG_M_THS_X_MSB      0x54
#define AG_M_THS_X_LSB      0x55
#define AG_M_THS_Y_MSB      0x56
#define AG_M_THS_Y_LSB      0x57
#define AG_M_THS_Z_MSB      0x58
#define AG_M_THS_Z_LSB      0x59
#define AG_M_THS_COUNT      0x5A
#define AG_M_CTRL_REG1      0x5B
#define AG_M_CTRL_REG2      0x5C
#define AG_M_CTRL_REG3      0x5D
#define AG_M_INT_SRC        0x5E
#define AG_A_VECM_CFG       0x5F
#define AG_A_VECM_THS_MSB   0x60
#define AG_A_VECM_THS_LSB   0x61
#define AG_A_VECM_CNT       0x62
#define AG_A_VECM_INITX_MSB 0x63
#define AG_A_VECM_INITX_LSB 0x64
#define AG_A_VECM_INITY_MSB 0x65
#define AG_A_VECM_INITY_LSB 0x66
#define AG_A_VECM_INITZ_MSB 0x67
#define AG_A_VECM_INITZ_LSB 0x68
#define AG_M_VECM_CFG       0x69
#define AG_M_VECM_THS_MSB   0x6A
#define AG_M_VECM_THS_LSB   0x6B
#define AG_M_VECM_CNT       0x6C
#define AG_M_VECM_INITX_MSB 0x6D
#define AG_M_VECM_INITX_LSB 0x6E
#define AG_M_VECM_INITY_MSB 0x6F
#define AG_M_VECM_INITY_LSB 0x70
#define AG_M_VECM_INITZ_MSB 0x71
#define AG_M_VECM_INITZ_LSB 0x72
#define AG_A_FFMT_THS_X_MSB 0x73
#define AG_A_FFMT_THS_X_LSB 0x74
#define AG_A_FFMT_THS_Y_MSB 0x75
#define AG_A_FFMT_THS_Y_LSB 0x76
#define AG_A_FFMT_THS_Z_MSB 0x77
#define AG_A_FFMT_THS_Z_LSB 0x78

//*****************************************************************************
// Functions
//*****************************************************************************

// Set initial input parameters
typedef enum
{
    AFSR_2G,
    AFSR_4G,
    AFSR_8G
} tAccelRange;

typedef enum
{
    ODR_800HZ,
    ODR_400HZ,
    ODR_200HZ,
    ODR_100HZ,
    ODR_50HZ,
    ODR_12_5HZ,
    ODR_6_25HZ,
    ODR_1_56HZ
} tOutputDataRate;

typedef enum
{
    ACCEL_ONLY,
    MAG_ONLY,
    ACCEL_AND_MAG = 3
} tHybridMode;

typedef enum
{
    ACCEL_DATA,
    MAG_DATA
} tDataType;

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
} tRawData;

// I2C General Send and receive functions
void I2CAGReceive(uint32_t ui32SlaveAddress, uint8_t ui32SlaveRegister,
                    uint8_t *pReceiveData, uint8_t ui8NumBytes);
void I2CAGSend(uint8_t ui32SlaveAddress, uint8_t ui8NumArgs, ...);

// FXOS8700CQ functions
void AGStandby(uint32_t ui32SlaveAddress);
void AGActive(uint32_t ui32SlaveAddress);
void AGAccelRange(uint32_t ui32SlaveAddress, tAccelRange tAFSR);
void AGOutputDataRate(uint32_t ui32SlaveAddress, tOutputDataRate tODR);
void AGHybridMode(uint32_t ui32SlaveAddress, tHybridMode tHM);
void AGGetData(uint32_t ui32SlaveAddress, tDataType tDT, tRawData *tRD );

//*****************************************************************************
// Mark the end of the C bindings section for C++ compilers.
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif /* FXOS8700CQ_H_ */
