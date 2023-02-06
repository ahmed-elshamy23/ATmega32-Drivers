#ifndef TIMER2_INTERFACE_H
#define TIMER2_INTERFACE_H

#include "STD_TYPES.h"

void TIMER2_voidInit();

void TIMER2_voidDelay(f32 delayTime);

void TIMER2_voidGeneratePWM(f32 dutyCycle);

void TIMER2_voidSetCompareValue(u8 compareValue);

void TIMER2_voidSetTimerValue(u8 timerValue);

u8 TIMER2_u8GetTimerValue();

void TIMER2_voidInterruptEnable(u8 interrupt);

void TIMER2_voidInterruptDisable(u8 interrupt);

void TIMER2_voidStart();

void TIMER2_voidStop();

void TIMER2_voidSetCallback(u8 interrupt, void (*ptr)());

void TIMER2_OVERFLOW_ISR() __attribute__((signal));

void TIMER2_COMPARE_MATCH_ISR() __attribute__((signal));

#endif