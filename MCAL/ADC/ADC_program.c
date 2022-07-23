#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "ADC_config.h"
#include "ADC_interface.h"
#include "GIE_interface.h"
#include <util/delay.h>

void (*callback)() = NULL;

void ADC_voidInit(u8 channel)
{
    SET_BIT(ADCSRA, ADEN);
#if PRESCALER == 2
    CLR_BIT(ADCSRA, ADPS0);
    CLR_BIT(ADCSRA, ADPS1);
    CLR_BIT(ADCSRA, ADPS2);
#elif PRESCALER == 4
    CLR_BIT(ADCSRA, ADPS0);
    SET_BIT(ADCSRA, ADPS1);
    CLR_BIT(ADCSRA, ADPS2);
#elif PRESCALER == 8
    SET_BIT(ADCSRA, ADPS0);
    SET_BIT(ADCSRA, ADPS1);
    CLR_BIT(ADCSRA, ADPS2);
#elif PRESCALER == 16
    CLR_BIT(ADCSRA, ADPS0);
    CLR_BIT(ADCSRA, ADPS1);
    SET_BIT(ADCSRA, ADPS2);
#elif PRESCALER == 32
    SET_BIT(ADCSRA, ADPS0);
    CLR_BIT(ADCSRA, ADPS1);
    SET_BIT(ADCSRA, ADPS2);
#elif PRESCALER == 64
    CLR_BIT(ADCSRA, ADPS0);
    SET_BIT(ADCSRA, ADPS1);
    SET_BIT(ADCSRA, ADPS2);
#else
    SET_BIT(ADCSRA, ADPS0);
    SET_BIT(ADCSRA, ADPS1);
    SET_BIT(ADCSRA, ADPS2);
#endif
    switch (channel)
    {
    case ADC0:
        CLR_BIT(ADMUX, MUX0);
        CLR_BIT(ADMUX, MUX1);
        CLR_BIT(ADMUX, MUX2);
        break;
    case ADC1:
        SET_BIT(ADMUX, MUX0);
        CLR_BIT(ADMUX, MUX1);
        CLR_BIT(ADMUX, MUX2);
        break;
    case ADC2:
        CLR_BIT(ADMUX, MUX0);
        SET_BIT(ADMUX, MUX1);
        CLR_BIT(ADMUX, MUX2);
        break;
    case ADC3:
        SET_BIT(ADMUX, MUX0);
        SET_BIT(ADMUX, MUX1);
        CLR_BIT(ADMUX, MUX2);
        break;
    case ADC4:
        CLR_BIT(ADMUX, MUX0);
        CLR_BIT(ADMUX, MUX1);
        SET_BIT(ADMUX, MUX2);
        break;
    case ADC5:
        SET_BIT(ADMUX, MUX0);
        CLR_BIT(ADMUX, MUX1);
        SET_BIT(ADMUX, MUX2);
        break;
    case ADC6:
        CLR_BIT(ADMUX, MUX0);
        SET_BIT(ADMUX, MUX1);
        SET_BIT(ADMUX, MUX2);
        break;
    case ADC7:
        SET_BIT(ADMUX, MUX0);
        SET_BIT(ADMUX, MUX1);
        SET_BIT(ADMUX, MUX2);
    }
#if REFERENCE == AREF
    CLR_BIT(ADMUX, REFS0);
    CLR_BIT(ADMUX, REFS1);
#elif REFERENCE == AVCC
    SET_BIT(ADMUX, REFS0);
    CLR_BIT(ADMUX, REFS1);
#else
    SET_BIT(ADMUX, REFS0);
    SET_BIT(ADMUX, REFS1);
#endif
#if ADC_ADJUST == LEFT_ADJUST
    SET_BIT(ADMUX, ADLAR);
#endif
#if ADC_MODE == AUTO_TRIGGER
    SET_BIT(ADCSRA, ADATE);
#if AUTO_TRIGGER_MODE == FREE_RUNNING
    CLR_BIT(SFIOR, ADTS0);
    CLR_BIT(SFIOR, ADTS1);
    CLR_BIT(SFIOR, ADTS2);
#elif AUTO_TRIGGER_MODE == ANALOG_COMPARATOR
    SET_BIT(SFIOR, ADTS0);
    CLR_BIT(SFIOR, ADTS1);
    CLR_BIT(SFIOR, ADTS2);
#elif AUTO_TRIGGER_MODE == EXIT0
    CLR_BIT(SFIOR, ADTS0);
    SET_BIT(SFIOR, ADTS1);
    CLR_BIT(SFIOR, ADTS2);
#elif AUTO_TRIGGER_MODE == TIMER0_MATCH
    SET_BIT(SFIOR, ADTS0);
    SET_BIT(SFIOR, ADTS1);
    CLR_BIT(SFIOR, ADTS2);
#elif AUTO_TRIGGER_MODE == TIMER0_OVERFLOW
    CLR_BIT(SFIOR, ADTS0);
    CLR_BIT(SFIOR, ADTS1);
    SET_BIT(SFIOR, ADTS2);
#elif AUTO_TRIGGER_MODE == TIMER1_MATCH
    SET_BIT(SFIOR, ADTS0);
    CLR_BIT(SFIOR, ADTS1);
    SET_BIT(SFIOR, ADTS2);
#elif AUTO_TRIGGER_MODE == TIMER1_OVERFLOW
    CLR_BIT(SFIOR, ADTS0);
    SET_BIT(SFIOR, ADTS1);
    SET_BIT(SFIOR, ADTS2);
#else
    SET_BIT(SFIOR, ADTS0);
    SET_BIT(SFIOR, ADTS1);
    SET_BIT(SFIOR, ADTS2);
#endif
#endif
}

void ADC_voidStartConversion()
{
    SET_BIT(ADCSRA, ADSC);
}

u16 ADC_u16GetResult()
{
    u16 result = 0;
    if (GET_BIT(ADCSRA, ADATE) && AUTO_TRIGGER_MODE == FREE_RUNNING)
        while (!GET_BIT(ADCSRA, ADIF))
            ;
#if ADC_ADJUST == RIGHT_ADJUST
    result = ADCLH;
#else
    result = (ADCLH >> 6);
#endif
    SET_BIT(ADCSRA, ADIF);
    return result;
}

void ADC_voidInterruptEnable()
{
    GIE_voidEnable();
    SET_BIT(ADCSRA, ADIE);
}

void ADC_voidSetCallback(void (*ptr)())
{
    callback = ptr;
}

void __vector_16(void)
{
    if (callback != NULL)
    {
        callback();
    }
}