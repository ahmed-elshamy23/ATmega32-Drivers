#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_private.h"
#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"

static void (*callback)() = NULL;

void SPI_voidInit()
{
#if SPI_DATA_ORDER == SPI_DATA_ORDER_LSB
    SET_BIT(SPCR, DORD);
#else
    CLR_BIT(SPCR, DORD);
#endif

#if SPI_MODE == SPI_MASTER
    SET_BIT(SPCR, MSTR);
    SET_BIT(DDRB_REG, MOSI_PIN);
    SET_BIT(DDRB_REG, SCK_PIN);
    SET_BIT(DDRB_REG, SS_PIN);
#else
    CLR_BIT(SPCR, MSTR);
    CLR_BIT(DDRB_REG, MISO_PIN);
#endif

#if SPI_POLARITY_MODE == SPI_POLARITY_FALLING
    SET_BIT(SPCR, CPOL);
#else
    CLR_BIT(SPCR, CPOL);
#endif

#if SPI_PHASE_MODE == SPI_SAMPLE_LEADING
    CLR_BIT(SPCR, CPHA);
#else
    SET_BIT(SPCR, CPHA);
#endif

#if SPI_PRESCALER == SPI_PRESCALER_2
    SET_BIT(SPSR, SPI2X);
    CLR_BIT(SPCR, SPR1);
    CLR_BIT(SPCR, SPR0);
#elif SPI_PRESCALER == SPI_PRESCALER_4
    CLR_BIT(SPSR, SPI2X);
    CLR_BIT(SPCR, SPR1);
    CLR_BIT(SPCR, SPR0);
#elif SPI_PRESCALER == SPI_PRESCALER_8
    SET_BIT(SPSR, SPI2X);
    CLR_BIT(SPCR, SPR1);
    SET_BIT(SPCR, SPR0);
#elif SPI_PRESCALER == SPI_PRESCALER_16
    CLR_BIT(SPSR, SPI2X);
    CLR_BIT(SPCR, SPR1);
    SET_BIT(SPCR, SPR0);
#elif SPI_PRESCALER == SPI_PRESCALER_32
    SET_BIT(SPSR, SPI2X);
    SET_BIT(SPCR, SPR1);
    CLR_BIT(SPCR, SPR0);
#elif SPI_PRESCALER == SPI_PRESCALER_64
    CLR_BIT(SPSR, SPI2X);
    SET_BIT(SPCR, SPR1);
    CLR_BIT(SPCR, SPR0);
#elif SPI_PRESCALER == SPI_PRESCALER_128
    CLR_BIT(SPSR, SPI2X);
    SET_BIT(SPCR, SPR1);
    SET_BIT(SPCR, SPR0);
#endif

    SET_BIT(PORTB_REG, SS_PIN);
    SET_BIT(SPCR, SPE);
}

void SPI_voidSendData(u8 data)
{
#if SPI_MODE == SPI_MASTER
    CLR_BIT(PORTB_REG, SS_PIN);
#endif
    SPDR = data;
    while (!GET_BIT(SPSR, SPIF))
        ;
    SPDR;
    SET_BIT(PORTB_REG, SS_PIN);
}

u8 SPI_u8ReceiveData()
{
    while (!GET_BIT(SPSR, SPIF))
        ;
    return SPDR;
}

void SPI_voidSendString(u8 *string)
{
    u8 i = 0;
    while (string[i] != '\0')
    {
        SPI_voidSendData(string[i]);
        i++;
    }
}

void SPI_voidReceiveString(u8 *string, u8 terminateCharacter)
{
    u8 i = 0;
    string[i] = SPI_voidReceiveData();
    while (string[i] != terminateCharacter)
    {
        i++;
        string[i] = SPI_voidReceiveData();
    }
    string[i] = '\0';
}

void SPI_voidInterruptEnable()
{
    SET_BIT(SPCR, SPIE);
}

void SPI_voidInterruptDisable()
{
    CLR_BIT(SPCR, SPIE);
}

void SPI_voidSetCallback(void (*ptr)())
{
    callback = ptr;
}

void SPI_ISR()
{
    if (callback != NULL)
    {
        callback();
    }
}