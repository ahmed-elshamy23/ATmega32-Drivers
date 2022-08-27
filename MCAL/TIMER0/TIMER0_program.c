#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER0_config.h"
#include "TIMER0_interface.h"
#include "TIMER0_private.h"

void (*callbackOVF)(void) = NULL;
void (*callbackCOMP)(void) = NULL;

void TIMER0_voidInit()
{
#if TIMER0_MODE == NORMAL_MODE || TIMER0_MODE == COUNTER_MODE
    CLR_BIT(TCCR0, WGM00);
    CLR_BIT(TCCR0, WGM01);
    CLR_BIT(TCCR0, COM00);
    CLR_BIT(TCCR0, COM01);
#elif TIMER0_MODE == CTC_MODE
    CLR_BIT(TCCR0, WGM00);
    SET_BIT(TCCR0, WGM01);

#if OC0_MODE == OC0_TOGGLE
    SET_BIT(TCCR0, COM00);
    CLR_BIT(TCCR0, COM01);
#elif OC0_MODE == OC0_CLEAR
    CLR_BIT(TCCR0, COM00);
    SET_BIT(TCCR0, COM01);
#else
    SET_BIT(TCCR0, COM00);
    SET_BIT(TCCR0, COM01);
#endif

#elif TIMER0_MODE == FAST_PWM_MODE
    SET_BIT(TCCR0, WGM00);
    SET_BIT(TCCR0, WGM01);

#if OC0_MODE == OC0_INVERTING
    SET_BIT(TCCR0, COM00);
    SET_BIT(TCCR0, COM01);
#else
    CLR_BIT(TCCR0, COM00);
    SET_BIT(TCCR0, COM01);
#endif

#elif TIMER0_MODE == PWM_MODE
    SET_BIT(TCCR0, WGM00);
    CLR_BIT(TCCR0, WGM01);

#if OC0_MODE == OC0_INVERTING
    SET_BIT(TCCR0, COM00);
    SET_BIT(TCCR0, COM01);
#else
    CLR_BIT(TCCR0, COM00);
    SET_BIT(TCCR0, COM01);
#endif

#endif
}

void TIMER0_voidStart()
{
#if TIMER0_PRESCALER == 1
    SET_BIT(TCCR0, CS00);
    CLR_BIT(TCCR0, CS01);
    CLR_BIT(TCCR0, CS02);
#elif TIMER0_PRESCALER == 8
    CLR_BIT(TCCR0, CS00);
    SET_BIT(TCCR0, CS01);
    CLR_BIT(TCCR0, CS02);
#elif TIMER0_PRESCALER == 64
    SET_BIT(TCCR0, CS00);
    SET_BIT(TCCR0, CS01);
    CLR_BIT(TCCR0, CS02);
#elif TIMER0_PRESCALER == 256
    CLR_BIT(TCCR0, CS00);
    CLR_BIT(TCCR0, CS01);
    SET_BIT(TCCR0, CS02);
#elif TIMER0_PRESCALER == 1024
    SET_BIT(TCCR0, CS00);
    CLR_BIT(TCCR0, CS01);
    SET_BIT(TCCR0, CS02);
#elif TIMER0_PRESCALER == EXT_FALLING_EDGE
    CLR_BIT(TCCR0, CS00);
    SET_BIT(TCCR0, CS01);
    SET_BIT(TCCR0, CS02);
#else
    SET_BIT(TCCR0, CS00);
    SET_BIT(TCCR0, CS01);
    SET_BIT(TCCR0, CS02);
#endif
}

void TIMER0_voidStop()
{
    TCCR0 = 0;
}

void TIMER0_voidInterruptEnable(u8 interruptMode)
{
    switch (interruptMode)
    {
    case (OVERFLOW):
        SET_BIT(TIMSK, TOIE);
        break;
    case (COMPARE_MATCH):
        SET_BIT(TIMSK, OCIE);
    }
}

void TIMER0_voidSetCallbackOVF(void (*ptr)())
{
    callbackOVF = ptr;
}

void TIMER0_voidSetCallbackCOMP(void (*ptr)())
{
    callbackCOMP = ptr;
}

void TIMER0_OVERFLOW_ISR()
{
    if (callbackOVF != NULL)
    {
        callbackOVF();
    }
}

void TIMER0_COMP_ISR()
{
    if (callbackCOMP != NULL)
    {
        callbackCOMP();
    }
}

void TIMER0_voidSetTimerValue(u8 timerValue)
{
    TCNT0 = timerValue;
}

void TIMER0_voidSetCompareValue(u8 compareValue)
{
    OCR0 = compareValue;
}

u8 TIMER0_voidGetTimerValue()
{
    return TCNT0;
}

void TIMER0_voidDelay(f32 delayTime)
{
    f32 tickTime = 0;
#if TIMER0_PRESCALER == 1
    tickTime = 1.0f / CLOCK;
#elif TIMER0_PRESCALER == 8
    tickTime = 8.0f / CLOCK;
#elif TIMER0_PRESCALER == 64
    tickTime = 64.0f / CLOCK;
#elif TIMER0_PRESCALER == 256
    tickTime = 256.0f / CLOCK;
#elif TIMER0_PRESCALER == 1024
    tickTime = 1024.0f / CLOCK;
#endif
    f32 overflowTime = 256 * tickTime;
    if (delayTime >= overflowTime)
    {
        u8 numOfOverflows = delayTime / overflowTime, c = 0;
        f32 fraction = delayTime - numOfOverflows * overflowTime;
        TIMER0_voidSetTimerValue(0);
        while (c < numOfOverflows)
        {
            TIMER0_voidStart();
            while (!GET_BIT(TIFR, TOV0))
                ;
            TIMER0_voidStop();
            SET_BIT(TIFR, TOV0);
            c++;
        }
        if (fraction)
        {
            TIMER0_voidSetTimerValue(256 - 256 * (fraction / 10));
            TIMER0_voidStart();
            while (!GET_BIT(TIFR, TOV0))
                ;
            TIMER0_voidStop();
            SET_BIT(TIFR, TOV0);
        }
    }
    else
    {
        TIMER0_voidSetTimerValue((overflowTime - delayTime) / tickTime);
        TIMER0_voidStart();
        while (!GET_BIT(TIFR, TOV0))
            ;
        TIMER0_voidStop();
        SET_BIT(TIFR, TOV0);
    }
}

void TIMER0_voidGeneratePWM(f32 dutyCycle)
{
#if TIMER0_MODE == FAST_PWM_MODE

#if OC0_MODE == OC0_NONINVERTING
    TIMER0_voidSetCompareValue((dutyCycle * 256) - 1);
#else
    TIMER0_voidSetCompareValue(((1 - dutyCycle) * 256) - 1);
#endif

#else
#if OC0_MODE == OC0_NONINVERTING
    TIMER0_voidSetCompareValue((dutyCycle * 255) - 1);
#else
    TIMER0_voidSetCompareValue(((1 - dutyCycle) * 255) - 1);
#endif

#endif
    TIMER0_voidStart();
}