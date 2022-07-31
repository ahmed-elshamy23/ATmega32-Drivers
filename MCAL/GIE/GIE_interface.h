#ifndef GIE_INTERFACE_H
#define GIE_INTERFACE_H

#define SREG *((volatile u8 *)(0x5F))
#define GENERAL_INTERRUPT 7

void GIE_voidEnable();
void GIE_voidDisable();

#endif