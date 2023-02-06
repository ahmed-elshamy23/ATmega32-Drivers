#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER2_private.h"
#include "TIMER2_config.h"
#include "TIMER2_interface.h"

static void (*callbackOverflow)() = NULL;
static void (*callbackCompareMatch)() = NULL;

void TIMER2_voidInit()
{
#if TIMER2_MODE == TIMER2_NORMAL_MODE
    CLR_BIT(TCCR2, WGM20);
    CLR_BIT(TCCR2, WGM21);
#elif TIMER2_MODE == TIMER2_PHASE_CORRECT_PWM_MODE
    SET_BIT(TCCR2, WGM20);
    CLR_BIT(TCCR2, WGM21);
#elif TIMER2_MODE == TIMER2_CTC_MODE
    CLR_BIT(TCCR2, WGM20);
    SET_BIT(TCCR2, WGM21);
#elif TIMER2_MODE == TIMER2_ASYNCHRONOUS_MODE
    SET_BIT(ASSR, AS2);
#else
    SET_BIT(TCCR2, WGM20);
    SET_BIT(TCCR2, WGM21);
#endif

#if OC2_MODE == OC2_DISCONNECTED
    CLR_BIT(TCCR2, COM20);
    CLR_BIT(TCCR2, COM21);
#elif OC2_MODE == OC2_TOGGLE
    SET_BIT(TCCR2, COM20);
    CLR_BIT(TCCR2, COM21);
    SET_BIT(DDRD, OC2_PIN);
#elif OC2_MODE == OC2_NON_INVERTING
    CLR_BIT(TCCR2, COM20);
    SET_BIT(TCCR2, COM21);
    SET_BIT(DDRD, OC2_PIN);
#else
    SET_BIT(TCCR2, COM20);
    SET_BIT(TCCR2, COM21);
    SET_BIT(DDRD, OC2_PIN);
#endif
}

void TIMER2_voidDelay(f32 delayTime)
{
    f32 tickTime;
#if TIMER2_PRESCALER == TIMER2_PRESCALER_1
    tickTime = 1.0f / CLOCK;
#elif TIMER2_PRESCALER == TIMER2_PRESCALER_8
    tickTime = 8.0f / CLOCK;
#elif TIMER2_PRESCALER == TIMER2_PRESCALER_32
    tickTime = 32.0f / CLOCK;
#elif TIMER2_PRESCALER == TIMER2_PRESCALER_64
    tickTime = 64.0f / CLOCK;
#elif TIMER2_PRESCALER == TIMER2_PRESCALER_128
    tickTime = 128.0f / CLOCK;
#elif TIMER2_PRESCALER == TIMER2_PRESCALER_256
    tickTime = 256.0f / CLOCK;
#else
    tickTime = 1024.0f / CLOCK;
#endif
    f32 overflowTime = 256 * tickTime;
    if (delayTime >= overflowTime)
    {
        u32 numOfOverflows = delayTime / overflowTime, c = 0;
        f32 fraction = delayTime - numOfOverflows * overflowTime;
        TIMER2_voidSetTimerValue(0);
        while (c < numOfOverflows)
        {
            TIMER2_voidStart();
            while (!GET_BIT(TIFR, TOV2))
                ;
            TIMER2_voidStop();
            SET_BIT(TIFR, TOV2);
            c++;
        }
        if (fraction)
        {
            TIMER2_voidSetTimerValue(256 - 256 * (fraction / 10));
            TIMER2_voidStart();
            while (!GET_BIT(TIFR, TOV2))
                ;
            TIMER2_voidStop();
            SET_BIT(TIFR, TOV2);
        }
    }
    else
    {
        TIMER2_voidSetTimerValue((overflowTime - delayTime) / tickTime);
        TIMER2_voidStart();
        while (!GET_BIT(TIFR, TOV2))
            ;
        TIMER2_voidStop();
        SET_BIT(TIFR, TOV2);
    }
}

void TIMER2_voidGeneratePWM(f32 dutyCycle)
{
#if OC2_MODE == OC2_NON_INVERTING
    TIMER2_voidSetCompareValue(dutyCycle * 256 - 1);
#else
    TIMER2_voidSetCompareValue((1 - dutyCycle) * 256 - 1);
#endif
    SET_BIT(DDRD, OC2_PIN);
    TIMER2_voidStart();
}

void TIMER2_voidSetCompareValue(u8 compareValue)
{
    OCR2 = compareValue;
}

void TIMER2_voidSetTimerValue(u8 timerValue)
{
#if TIMER2_MODE == TIMER2_ASYNCHRONOUS_MODE
    while (GET_BIT(ASSR, TCN2UB))
        ;
#endif
    TCNT2 = timerValue;
}

u8 TIMER2_u8GetTimerValue()
{
    return TCNT2;
}

void TIMER2_voidInterruptEnable(u8 interrupt)
{
    switch (interrupt)
    {
    case TIMER2_OVERFLOW:
        SET_BIT(TIMSK, TOIE2);
        break;
    default:
        SET_BIT(TIMSK, OCIE2);
    }
}

void TIMER2_voidInterruptDisable(u8 interrupt)
{
    switch (interrupt)
    {
    case TIMER2_OVERFLOW:
        CLR_BIT(TIMSK, TOIE2);
        break;
    default:
        CLR_BIT(TIMSK, OCIE2);
    }
}

void TIMER2_voidStart()
{
#if TIMER2_PRESCALER == TIMER2_PRESCALER_1
    SET_BIT(TCCR2, CS20);
    CLR_BIT(TCCR2, CS21);
    CLR_BIT(TCCR2, CS22);
#elif TIMER2_PRESCALER == TIMER2_PRESCALER_8
    CLR_BIT(TCCR2, CS20);
    SET_BIT(TCCR2, CS21);
    CLR_BIT(TCCR2, CS22);
#elif TIMER2_PRESCALER == TIMER2_PRESCALER_32
    SET_BIT(TCCR2, CS20);
    SET_BIT(TCCR2, CS21);
    CLR_BIT(TCCR2, CS22);
#elif TIMER2_PRESCALER == TIMER2_PRESCALER_64
    CLR_BIT(TCCR2, CS20);
    CLR_BIT(TCCR2, CS21);
    SET_BIT(TCCR2, CS22);
#elif TIMER2_PRESCALER == TIMER2_PRESCALER_128
    SET_BIT(TCCR2, CS20);
    CLR_BIT(TCCR2, CS21);
    SET_BIT(TCCR2, CS22);
#elif TIMER2_PRESCALER == TIMER2_PRESCALER_256
    CLR_BIT(TCCR2, CS20);
    SET_BIT(TCCR2, CS21);
    SET_BIT(TCCR2, CS22);
#else
    SET_BIT(TCCR2, CS20);
    SET_BIT(TCCR2, CS21);
    SET_BIT(TCCR2, CS22);
#endif
}

void TIMER2_voidStop()
{
    TCCR2 = 0;
}

void TIMER2_voidSetCallback(u8 interrupt, void (*ptr)())
{
    switch (interrupt)
    {
    case TIMER2_OVERFLOW:
        callbackOverflow = ptr;
        break;
    default:
        callbackCompareMatch = ptr;
    }
}

void TIMER2_OVERFLOW_ISR()
{
    if (callbackOverflow != NULL)
    {
        callbackOverflow();
    }
}

void TIMER2_COMPARE_MATCH_ISR()
{
    if (callbackCompareMatch != NULL)
    {
        callbackCompareMatch();
    }
}