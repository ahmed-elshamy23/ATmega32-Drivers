#ifndef WDT_INTERFACE_H
#define WDT_INTERFACE_H

#include "STD_TYPES.h"

void WDT_voidEnable();
void WDT_voidDisable();

void WDT_voidRefresh();

void WDT_voidSleep(u8 prescaler);

#endif