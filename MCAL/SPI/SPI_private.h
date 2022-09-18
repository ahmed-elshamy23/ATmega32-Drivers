#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

#include "STD_TYPES.h"

#define SPCR (*(u8 *)(0x2D))
#define SPSR (*(u8 *)(0x2E))
#define SPDR (*(u8 *)(0x2F))

#define SCK_PIN 7
#define MISO_PIN 6
#define MOSI_PIN 5
#define SS_PIN 4

#define SPR0 0
#define SPR1 1
#define CPHA 2
#define CPOL 3
#define MSTR 4
#define DORD 5
#define SPE 6
#define SPIE 7

#define SPI2X 0
#define WCOL 6
#define SPIF 7

#define SPI_MASTER 0
#define SPI_SLAVE 1

#define SPI_DATA_ORDER_LSB 0
#define SPI_DATA_ORDER_MSB 1

#define SPI_POLARITY_RISING 0
#define SPI_POLARITY_FALLING 1

#define SPI_SAMPLE_LEADING 0
#define SPI_SAMPLE_TRAILING 1

#define SPI_PRESCALER_2 2
#define SPI_PRESCALER_4 4
#define SPI_PRESCALER_8 8
#define SPI_PRESCALER_16 16
#define SPI_PRESCALER_32 32
#define SPI_PRESCALER_64 64
#define SPI_PRESCALER_128 128

#define NULL 0

#define SPI_ISR __vector_12

#endif