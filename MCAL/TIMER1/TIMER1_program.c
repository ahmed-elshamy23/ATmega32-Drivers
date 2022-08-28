#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "TIMER1_config.h"
#include "TIMER1_private.h"
#include "TIMER1_interface.h"

void (*callbackCapture)(void) = NULL;
void (*callbackCompareA)(void) = NULL;
void (*callbackCompareB)(void) = NULL;
void (*callbackOverflow)(void) = NULL;

void TIMER1_voidInit()
{
#if TIMER1_MODE == TIMER1_NORMAL_MODE
    CLR_BIT(TCCR1A, COM1A0);
    CLR_BIT(TCCR1A, COM1A1);
    CLR_BIT(TCCR1A, COM1B0);
    CLR_BIT(TCCR1A, COM1B1);
    CLR_BIT(TCCR1A, WGM10);
    CLR_BIT(TCCR1A, WGM11);
    CLR_BIT(TCCR1B, WGM12);
    CLR_BIT(TCCR1B, WGM13);
#elif TIMER1_MODE == TIMER1_CTC_MODE
#if TIMER1_TOP == TOP_OCR
    CLR_BIT(TCCR1A, WGM10);
    CLR_BIT(TCCR1A, WGM11);
    SET_BIT(TCCR1B, WGM12);
    CLR_BIT(TCCR1B, WGM13);
#elif TIMER1_TOP == TOP_ICR
    CLR_BIT(TCCR1A, WGM10);
    CLR_BIT(TCCR1A, WGM11);
    SET_BIT(TCCR1B, WGM12);
    SET_BIT(TCCR1B, WGM13);
#endif
#if OC1A_MODE == OC1A_TOGGLE
    SET_BIT(TCCR1A, COM1A0);
    CLR_BIT(TCCR1A, COM1A1);
#elif OC1A_MODE == OC1A_CLEAR
    CLR_BIT(TCCR1A, COM1A0);
    SET_BIT(TCCR1A, COM1A1);
#elif OC1A_MODE == OC1A_SET
    SET_BIT(TCCR1A, COM1A0);
    SET_BIT(TCCR1A, COM1A1);
#endif
#if OC1B_MODE == OC1B_TOGGLE
    SET_BIT(TCCR1A, COM1B0);
    CLR_BIT(TCCR1A, COM1B1);
#elif OC1B_MODE == OC1A_CLEAR
    CLR_BIT(TCCR1A, COM1B0);
    SET_BIT(TCCR1A, COM1B1);
#elif OC1B_MODE == OC1B_SET
    SET_BIT(TCCR1A, COM1B0);
    SET_BIT(TCCR1A, COM1B1);
#endif
#elif TIMER1_MODE == TIMER1_PWM_MODE
#if TIMER1_TOP == TOP_8BIT
    SET_BIT(TCCR1A, WGM10);
    CLR_BIT(TCCR1A, WGM11);
    CLR_BIT(TCCR1B, WGM12);
    CLR_BIT(TCCR1B, WGM13);
#elif TIMER1_TOP == TOP_9BIT
    CLR_BIT(TCCR1A, WGM10);
    SET_BIT(TCCR1A, WGM11);
    CLR_BIT(TCCR1B, WGM12);
    CLR_BIT(TCCR1B, WGM13);
#elif TIMER1_TOP == TOP_10BIT
    SET_BIT(TCCR1A, WGM10);
    SET_BIT(TCCR1A, WGM11);
    CLR_BIT(TCCR1B, WGM12);
    CLR_BIT(TCCR1B, WGM13);
#elif TIMER1_TOP == TOP_ICR
    CLR_BIT(TCCR1A, WGM10);
    SET_BIT(TCCR1A, WGM11);
    CLR_BIT(TCCR1B, WGM12);
    SET_BIT(TCCR1B, WGM13);
#elif TIMER1_TOP == TOP_OCR
    SET_BIT(TCCR1A, WGM10);
    SET_BIT(TCCR1A, WGM11);
    CLR_BIT(TCCR1B, WGM12);
    SET_BIT(TCCR1B, WGM13);
#endif
#if OC1A_MODE == OC1A_NONINVERTING
    SET_BIT(TCCR1A, COM1A0);
    SET_BIT(TCCR1A, COM1A1);
#elif OC1A_MODE == OC1A_INVERTING
    CLR_BIT(TCCR1A, COM1A0);
    SET_BIT(TCCR1A, COM1A1);
#endif
#if OC1B_MODE == OC1B_NONINVERTING
    SET_BIT(TCCR1A, COM1B0);
    SET_BIT(TCCR1A, COM1B1);
#elif OC1B_MODE == OC1B_INVERTING
    CLR_BIT(TCCR1A, COM1B0);
    SET_BIT(TCCR1A, COM1B1);
#endif
#elif TIMER1_MODE == TIMER1_FAST_PWM_MODE
#if TIMER1_TOP == TOP_8BIT
    SET_BIT(TCCR1A, WGM10);
    CLR_BIT(TCCR1A, WGM11);
    SET_BIT(TCCR1B, WGM12);
    CLR_BIT(TCCR1B, WGM13);
#elif TIMER1_TOP == TOP_9BIT
    CLR_BIT(TCCR1A, WGM10);
    SET_BIT(TCCR1A, WGM11);
    SET_BIT(TCCR1B, WGM12);
    CLR_BIT(TCCR1B, WGM13);
#elif TIMER1_TOP == TOP_10BIT
    SET_BIT(TCCR1A, WGM10);
    SET_BIT(TCCR1A, WGM11);
    SET_BIT(TCCR1B, WGM12);
    CLR_BIT(TCCR1B, WGM13);
#elif TIMER1_TOP == TOP_ICR
    CLR_BIT(TCCR1A, WGM10);
    SET_BIT(TCCR1A, WGM11);
    SET_BIT(TCCR1B, WGM12);
    SET_BIT(TCCR1B, WGM13);
#elif TIMER1_TOP == TOP_OCR
    SET_BIT(TCCR1A, WGM10);
    SET_BIT(TCCR1A, WGM11);
    SET_BIT(TCCR1B, WGM12);
    SET_BIT(TCCR1B, WGM13);
#endif
#if OC1A_MODE == OC1A_NONINVERTING
    CLR_BIT(TCCR1A, COM1A0);
    SET_BIT(TCCR1A, COM1A1);
#elif OC1A_MODE == OC1A_INVERTING
    SET_BIT(TCCR1A, COM1A0);
    SET_BIT(TCCR1A, COM1A1);
#elif OC1A_MODE == OC1A_TOGGLE
    SET_BIT(TCCR1A, COM1A0);
    CLR_BIT(TCCR1A, COM1A1);
#endif
#if OC1B_MODE == OC1B_NONINVERTING
    CLR_BIT(TCCR1A, COM1B0);
    SET_BIT(TCCR1A, COM1B1);
#elif OC1B_MODE == OC1B_INVERTING
    SET_BIT(TCCR1A, COM1B0);
    SET_BIT(TCCR1A, COM1B1);
#endif
#else
#if TIMER1_TOP == TOP_ICR
    CLR_BIT(TCCR1A, WGM10);
    CLR_BIT(TCCR1A, WGM11);
    CLR_BIT(TCCR1B, WGM12);
    SET_BIT(TCCR1B, WGM13);
#elif TIMER1_TOP == TOP_OCR
    SET_BIT(TCCR1A, WGM10);
    CLR_BIT(TCCR1A, WGM11);
    CLR_BIT(TCCR1B, WGM12);
    SET_BIT(TCCR1B, WGM13);
#endif
#if OC1A_MODE == OC1A_NONINVERTING
    SET_BIT(TCCR1A, COM1A0);
    SET_BIT(TCCR1A, COM1A1);
#elif OC1A_MODE == OC1A_INVERTING
    CLR_BIT(TCCR1A, COM1A0);
    SET_BIT(TCCR1A, COM1A1);
#elif OC1A_MODE == OC1A_TOGGLE
    SET_BIT(TCCR1A, COM1A0);
    CLR_BIT(TCCR1A, COM1A1);
#endif
#if OC1B_MODE == OC1B_NONINVERTING
    SET_BIT(TCCR1A, COM1B0);
    SET_BIT(TCCR1A, COM1B1);
#elif OC1B_MODE == OC1B_INVERTING
    CLR_BIT(TCCR1A, COM1B0);
    SET_BIT(TCCR1A, COM1B1);
#endif
#endif
}

void TIMER1_voidDelay(f32 delayTime)
{
    f64 tickTime = 0;
#if TIMER1_PRESCALER == TIMER1_PRESCALER_1
    tickTime = 1.0f / CLOCK;
#elif TIMER1_PRESCALER == TIMER1_PRESCALER_8
    tickTime = 8.0f / CLOCK;
#elif TIMER1_PRESCALER == TIMER1_PRESCALER_64
    tickTime = 64.0f / CLOCK;
#elif TIMER1_PRESCALER == TIMER1_PRESCALER_256
    tickTime = 256.0f / CLOCK;
#elif TIMER1_PRESCALER == TIMER1_PRESCALER_1024
    tickTime = 1024.0f / CLOCK;
#endif
    f64 overflowTime = 65536 * tickTime;
    if (delayTime >= overflowTime)
    {
        u32 numOfOverflows = delayTime / overflowTime, c = 0;
        f32 fraction = delayTime - numOfOverflows * overflowTime;
        TIMER1_voidSetTimerValue(0);
        while (c < numOfOverflows)
        {
            TIMER1_voidStart();
            while (!GET_BIT(TIFR, TOV1))
                ;
            TIMER1_voidStop();
            SET_BIT(TIFR, TOV1);
            c++;
        }
        if (fraction)
        {
            TIMER1_voidSetTimerValue(65536 - 65536 * (fraction / 10));
            TIMER1_voidStart();
            while (!GET_BIT(TIFR, TOV1))
                ;
            TIMER1_voidStop();
            SET_BIT(TIFR, TOV1);
        }
    }
    else
    {
        TIMER1_voidSetTimerValue((overflowTime - delayTime) / tickTime);
        TIMER1_voidStart();
        while (!GET_BIT(TIFR, TOV1))
            ;
        TIMER1_voidStop();
        SET_BIT(TIFR, TOV1);
    }
}

void TIMER1_voidGeneratePWM(u8 compareUnit, u32 frequency, f32 dutyCycle)
{
    u32 timerFrequency = CLOCK / TIMER1_PRESCALER;
    u16 topValue = 0;
#if TIMER1_TOP == TOP_8BIT
    topValue = 255;
#elif TIMER1_TOP == TOP_9BIT
    topValue = 511;
#elif TIMER1_TOP == TOP_10BIT
    topValue = 1023;
#endif
#if TIMER1_MODE == TIMER1_FAST_PWM_MODE
#if TIMER1_TOP == TOP_OCR || TIMER1_TOP == TOP_ICR
    topValue = timerFrequency / frequency;
    TIMER1_voidSetTopValue(topValue);
#endif
#if OC1A_MODE == OC1A_NONINVERTING
    TIMER1_voidSetCompareValue(compareUnit, (dutyCycle * (topValue + 1)) - 1);
#else
    TIMER1_voidSetCompareValue(compareUnit, ((1 - dutyCycle) * (topValue + 1)) - 1);
#endif
#else
#if TIMER1_TOP == TOP_OCR || TIMER1_TOP == TOP_ICR
    topValue = timerFrequency / (2 * frequency);
    TIMER1_voidSetTopValue(topValue);
#endif
#if OC1A_MODE == OC1A_INVERTING
    TIMER1_voidSetCompareValue(compareUnit, (dutyCycle * topValue) - 1);
#else
    TIMER1_voidSetCompareValue(compareUnit, ((1 - dutyCycle) * topValue) - 1);
#endif
#endif
    TIMER1_voidStart();
}

void TIMER1_voidEdgeSelectICU(u8 edge)
{
    switch (edge)
    {
    case RISING_EDGE:
        SET_BIT(TCCR1B, ICES1);
        break;
    default:
        CLR_BIT(TCCR1B, ICES1);
    }
}

void TIMER1_voidEnableNoiseCancelerICU()
{
    SET_BIT(TCCR1B, ICNC1);
}

void TIMER1_voidDisableNoiseCancelerICU()
{
    CLR_BIT(TCCR1B, ICNC1);
}

u16 TIMER1_u16ReadICR()
{
    return ICR1;
}

void TIMER1_voidSetTimerValue(u16 timerValue)
{
    TCNT1 = timerValue;
}

u16 TIMER1_u16GetTimerValue()
{
    return TCNT1;
}

void TIMER1_voidSetCompareValue(u8 compareUnit, u16 compareValue)
{
    switch (compareUnit)
    {
    case COMP_A:
        OCR1A = compareValue;
        break;
    default:
        OCR1B = compareValue;
    }
}

void TIMER1_voidSetTopValue(u16 value)
{
#if TIMER1_TOP == TOP_OCR
    OCR1A = value;
#elif TIMER1_TOP == TOP_ICR
    ICR1 = value;
#endif
}

void TIMER1_voidStart()
{
#if TIMER1_PRESCALER == TIMER1_PRESCALER_1
    SET_BIT(TCCR1B, CS10);
    CLR_BIT(TCCR1B, CS11);
    CLR_BIT(TCCR1B, CS12);
#elif TIMER1_PRESCALER == TIMER1_PRESCALER_8
    CLR_BIT(TCCR1B, CS10);
    SET_BIT(TCCR1B, CS11);
    CLR_BIT(TCCR1B, CS12);
#elif TIMER1_PRESCALER == TIMER1_PRESCALER_64
    SET_BIT(TCCR1B, CS10);
    SET_BIT(TCCR1B, CS11);
    CLR_BIT(TCCR1B, CS12);
#elif TIMER1_PRESCALER == TIMER1_PRESCALER_256
    CLR_BIT(TCCR1B, CS10);
    CLR_BIT(TCCR1B, CS11);
    SET_BIT(TCCR1B, CS12);
#elif TIMER1_PRESCALER == TIMER1_PRESCALER_1024
    SET_BIT(TCCR1B, CS10);
    CLR_BIT(TCCR1B, CS11);
    SET_BIT(TCCR1B, CS12);
#elif TIMER1_PRESCALER == TIMER1_PRESCALER_EXT_FALLING_EDGE
    CLR_BIT(TCCR1B, CS10);
    SET_BIT(TCCR1B, CS11);
    SET_BIT(TCCR1B, CS12);
#else
    SET_BIT(TCCR1B, CS10);
    SET_BIT(TCCR1B, CS11);
    SET_BIT(TCCR1B, CS12);
#endif
}

void TIMER1_voidStop()
{
    TCNT1 = 0;
}

void TIMER1_voidInterruptEnable(u8 interrupt)
{
    switch (interrupt)
    {
    case OVF_INTERRUPT:
        SET_BIT(TIMSK, TOIE1);
        break;
    case COMP_B_INTERRUPT:
        SET_BIT(TIMSK, OCIE1B);
        break;
    case COMP_A_INTERRUPT:
        SET_BIT(TIMSK, OCIE1A);
        break;
    default:
        SET_BIT(TIMSK, TICIE1);
    }
}

void TIMER1_voidInterruptDisable(u8 interrupt)
{
    switch (interrupt)
    {
    case OVF_INTERRUPT:
        CLR_BIT(TIMSK, TOIE1);
        break;
    case COMP_B_INTERRUPT:
        CLR_BIT(TIMSK, OCIE1B);
        break;
    case COMP_A_INTERRUPT:
        CLR_BIT(TIMSK, OCIE1A);
        break;
    default:
        CLR_BIT(TIMSK, TICIE1);
    }
}

void TIMER1_voidSetCallbackOVF(void (*ptr)())
{
    callbackOverflow = ptr;
}

void TIMER1_voidSetCallbackCAPT(void (*ptr)())
{
    callbackCapture = ptr;
}

void TIMER1_voidSetCallbackCOMPA(void (*ptr)())
{
    callbackCompareA = ptr;
}

void TIMER1_voidSetCallbackCOMPB(void (*ptr)())
{
    callbackCompareB = ptr;
}

void TIMER1_CAPTURE_ISR()
{
    if (callbackCapture != NULL)
    {
        callbackCapture();
    }
}

void TIMER1_COMP_A_ISR()
{
    if (callbackCompareA != NULL)
    {
        callbackCompareA();
    }
}

void TIMER1_COMP_B_ISR()
{
    if (callbackCompareB != NULL)
    {
        callbackCompareB();
    }
}

void TIMER1_OVERFLOW_ISR()
{
    if (callbackOverflow != NULL)
    {
        callbackOverflow();
    }
}