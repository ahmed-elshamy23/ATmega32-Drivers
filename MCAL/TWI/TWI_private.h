#ifndef TWI_PRIVATE_H
#define TWI_PRIVATE_H

#include "STD_TYPES.h"

#define TWBR (*(volatile u8 *)(0x20))
#define TWCR (*(volatile u8 *)(0x56))
#define TWSR (*(volatile u8 *)(0x21))
#define TWDR (*(volatile u8 *)(0x23))
#define TWAR (*(volatile u8 *)(0x22))

#define TWI_PRESCALER_1 1
#define TWI_PRESCALER_4 4
#define TWI_PRESCALER_16 16
#define TWI_PRESCALER_64 64

#define TWI_GENERAL_CALL_ENABLE 0
#define TWI_GENERAL_CALL_DISABLE 1

#define TWIE 0
#define TWEN 2
#define TWWC 3
#define TWSTO 4
#define TWSTA 5
#define TWEA 6
#define TWINT 7

#define TWPS0 0
#define TWPS1 1
#define TWS3 3
#define TWS4 4
#define TWS5 5
#define TWS6 6
#define TWS7 7

#define NULL 0

#define TWGCE 0

#define WRITE_BIT 0
#define READ_BIT 1

#define TWI_ISR __vector_19

#endif