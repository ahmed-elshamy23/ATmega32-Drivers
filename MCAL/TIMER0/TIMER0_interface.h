#ifndef TIMER0_INTERFACE_H
#define TIMER0_INTERFACE_H

#include "STD_TYPES.h"

void TIMER0_voidInit();

void TIMER0_voidStart();

void TIMER0_voidStop();

void TIMER0_voidInterruptEnable(u8 interruptMode);

void TIMER0_voidDelay(f32 delayTime);

void TIMER0_voidSetTimerValue(u8 timerValue);

void TIMER0_voidSetCompareValue(u8 compareValue);

u8 TIMER0_voidGetTimerValue();

void TIMER0_voidGeneratePWM(f32 dutyCycle);

void TIMER0_voidSetCallbackOVF(void (*ptr)());

void TIMER0_voidSetCallbackCOMP(void (*ptr)());

void TIMER0_OVERFLOW_ISR() __attribute__((signal));

void TIMER0_COMP_ISR() __attribute__((signal));

#endif