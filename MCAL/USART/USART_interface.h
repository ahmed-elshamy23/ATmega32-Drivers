#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

#include "STD_TYPES.h"

#define STACK_SIZE 10

typedef struct usart_stack
{
    u8 arr[STACK_SIZE];
    s8 sp;
} usart_stack;

void USART_voidInit();

void USART_voidSendData(u16 data);

void USART_voidSendString(u8 *string);

void USART_voidReceiveString(u8 *string, u8 terminateCharacter);

void USART_voidSendStringWithChecksum(u8 *string);

u8 USART_voidReceiveStringWithChecksum(u8 *string, u8 terminateCharacter);

u16 USART_voidReceiveData();

void USART_voidInterruptEnable(u8 interrupt);

void USART_voidInterruptDisable(u8 interrupt);

void USART_voidSetCAllback(u8 interrupt, void (*ptr)());

void USART_EMPTY_ISR() __attribute__((signal));

void USART_TX_COMPLETE_ISR() __attribute__((signal));

void USART_RX_COMPLETE_ISR() __attribute__((signal));

void USART_initStack(usart_stack *s);

u8 USART_stackPush(usart_stack *s, u8 data);

u8 USART_stackPop(usart_stack *s);

#endif