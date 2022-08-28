#ifndef TIMER1_INTERFACE_H
#define TIMER1_INTERFACE_H

#include "STD_TYPES.h"
#include "TIMER1_private.h"

void TIMER1_voidInit();

void TIMER1_voidDelay(f32 delayTime);

void TIMER1_voidGeneratePWM(u8 compareUnit, u32 frequency, f32 dutyCycle);

void TIMER1_voidEdgeSelectICU(u8 edge);

void TIMER1_voidEnableNoiseCancelerICU();

void TIMER1_voidDisableNoiseCancelerICU();

u16 TIMER1_u16ReadICR();

void TIMER1_voidSetTimerValue(u16 timerValue);

u16 TIMER1_u16GetTimerValue();

void TIMER1_voidSetCompareValue(u8 compareUnit, u16 compareValue);

void TIMER1_voidSetTopValue(u16 value);

void TIMER1_voidStart();

void TIMER1_voidStop();

void TIMER1_voidInterruptEnable(u8 interrupt);

void TIMER1_voidInterruptDisable(u8 interrupt);

void TIMER1_voidSetCallbackOVF(void (*ptr)());

void TIMER1_voidSetCallbackCAPT(void (*ptr)());

void TIMER1_voidSetCallbackCOMPA(void (*ptr)());

void TIMER1_voidSetCallbackCOMPB(void (*ptr)());

void TIMER1_CAPTURE_ISR() __attribute__((signal));

void TIMER1_COMP_A_ISR() __attribute__((signal));

void TIMER1_COMP_B_ISR() __attribute__((signal));

void TIMER1_OVERFLOW_ISR() __attribute__((signal));

#endif