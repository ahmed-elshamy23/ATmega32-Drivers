#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"

static usart_stack s;
static void (*callbackEmpty)() = NULL;
static void (*callbackTxComplete)() = NULL;
static void (*callbackRxComplete)() = NULL;

void USART_voidInit()
{
    SET_BIT(UCSRC, URSEL);
#if USART_MODE == USART_ASYNCHRONOUS
    CLR_BIT(UCSRC, UMSEL);
    CLR_BIT(UCSRC, UCPOL);
#else
    SET_BIT(UCSRC, UMSEL);
#if USART_CLOCK_MODE == USART_RISING_EDGE
    CLR_BIT(UCSRC, UCPOL);
#else
    SET_BIT(UCSRC, UCPOL);
#endif
#endif

#if USART_PARITY == USART_NO_PARITY
    CLR_BIT(UCSRC, UPM0);
    CLR_BIT(UCSRC, UPM1);
#elif USART_PARITY == USART_EVEN_PARITY
    CLR_BIT(UCSRC, UPM0);
    SET_BIT(UCSRC, UPM1);
#else
    SET_BIT(UCSRC, UPM0);
    SET_BIT(UCSRC, UPM1);
#endif

#if USART_STOP_BITS == USART_STOP_1BIT
    CLR_BIT(UCSRC, USBS);
#else
    SET_BIT(UCSRC, USBS);
#endif

#if USART_DATA_BITS == USART_DATA_5BIT
    CLR_BIT(UCSRC, UCSZ0);
    CLR_BIT(UCSRC, UCSZ1);
    CLR_BIT(UCSRB, UCSZ2);
#elif USART_DATA_BITS == USART_DATA_6BIT
    SET_BIT(UCSRC, UCSZ0);
    CLR_BIT(UCSRC, UCSZ1);
    CLR_BIT(UCSRB, UCSZ2);
#elif USART_DATA_BITS == USART_DATA_7BIT
    CLR_BIT(UCSRC, UCSZ0);
    SET_BIT(UCSRC, UCSZ1);
    CLR_BIT(UCSRB, UCSZ2);
#elif USART_DATA_BITS == USART_DATA_8BIT
    SET_BIT(UCSRC, UCSZ0);
    SET_BIT(UCSRC, UCSZ1);
    CLR_BIT(UCSRB, UCSZ2);
#else
    SET_BIT(UCSRC, UCSZ0);
    SET_BIT(UCSRC, UCSZ1);
    SET_BIT(UCSRB, UCSZ2);
#endif

#if USART_SPEED == USART_NORMAL_SPEED
    CLR_BIT(UCSRA, U2X);
#else
    SET_BIT(UCSRA, U2X);
#endif

#if USART_BAUD_RATE == USART_BAUD_2400
    UBRRL = 207;
#elif USART_BAUD_RATE == USART_BAUD_4800
    UBRRL = 103;
#elif USART_BAUD_RATE == USART_BAUD_9600
    UBRRL = 51;
#elif USART_BAUD_RATE == USART_BAUD_14400
    UBRRL = 34;
#elif USART_BAUD_RATE == USART_BAUD_19200
    UBRRL = 25;
#elif USART_BAUD_RATE == USART_BAUD_28800
    UBRRL = 16;
#elif USART_BAUD_RATE == USART_BAUD_38400
    UBRRL = 12;
#elif USART_BAUD_RATE == USART_BAUD_57600
    UBRRL = 8;
#elif USART_BAUD_RATE == USART_BAUD_76800
    UBRRL = 6;
#elif USART_BAUD_RATE == USART_BAUD_115200
    UBRRL = 3;
#elif USART_BAUD_RATE == USART_BAUD_230400
    UBRRL = 1;
#elif USART_BAUD_RATE == USART_BAUD_250000
    UBRRL = 1;
#elif USART_BAUD_RATE == USART_BAUD_500000
    UBRRL = 0;
#endif

    SET_BIT(UCSRB, TXEN);
    SET_BIT(UCSRB, RXEN);
}

void USART_voidSendData(u16 data)
{
    while (!GET_BIT(UCSRA, UDRE))
        ;
    if (data <= 255)
        CLR_BIT(UCSRB, TXB8);
    else
        SET_BIT(UCSRB, TXB8);
    UDR = (u8)data;
}

void USART_voidSendString(u8 *string)
{
    u8 i = 0;
    while (string[i] != '\0')
    {
        USART_voidSendData(string[i]);
        i++;
    }
}

void USART_voidReceiveString(u8 *string, u8 terminateCharacter)
{
    u8 i = 0;
    string[i] = USART_voidReceiveData();
    while (string[i] != terminateCharacter)
    {
        i++;
        string[i] = USART_voidReceiveData();
    }
    string[i] = '\0';
}

void USART_voidSendStringWithChecksum(u8 *string)
{
    u8 i = 0;
    u16 sum = 0;
    while (string[i] != '\0')
    {
        sum += string[i];
        USART_voidSendData(string[i]);
        _delay_ms(300);
        i++;
    }
    USART_voidSendData((u8)sum);
    USART_voidSendData((u8)(sum >> 8));
}

u8 USART_voidReceiveStringWithChecksum(u8 *string, u8 terminateCharacter)
{
    u8 i = 0;
    u16 calculatedSum = 0, receivedSum;
    string[i] = USART_voidReceiveData();
    calculatedSum += string[i];
    while (string[i] != terminateCharacter)
    {
        i++;
        string[i] = USART_voidReceiveData();
        calculatedSum += string[i];
    }
    string[i] = '\0';
    receivedSum += USART_voidReceiveData();
    receivedSum += (USART_voidReceiveData() << 8);
    if (receivedSum == calculatedSum)
        return 1;
    else
        return 0;
}

u16 USART_voidReceiveData()
{
    while (!GET_BIT(UCSRA, RXC))
        ;
    return (GET_BIT(UCSRB, RXB8) << 8) + UDR;
}

void USART_voidInterruptEnable(u8 interrupt)
{
    switch (interrupt)
    {
    case USART_EMPTY:
        SET_BIT(UCSRB, UDRIE);
        break;
    case USART_TX_COMPLETE:
        SET_BIT(UCSRB, TXCIE);
        break;
    case USART_RX_COMPLETE:
        SET_BIT(UCSRB, RXCIE);
        break;
    }
}

void USART_voidInterruptDisable(u8 interrupt)
{
    switch (interrupt)
    {
    case USART_EMPTY:
        CLR_BIT(UCSRB, UDRIE);
        break;
    case USART_TX_COMPLETE:
        CLR_BIT(UCSRB, TXCIE);
        break;
    case USART_RX_COMPLETE:
        CLR_BIT(UCSRB, RXCIE);
        break;
    }
}

void USART_voidSetCAllback(u8 interrupt, void (*ptr)())
{
    switch (interrupt)
    {
    case USART_EMPTY:
        callbackEmpty = ptr;
        break;
    case USART_TX_COMPLETE:
        callbackTxComplete = ptr;
        break;
    case USART_RX_COMPLETE:
        callbackRxComplete = ptr;
        break;
    }
}

void USART_EMPTY_ISR()
{
    if (callbackEmpty != NULL)
    {
        callbackEmpty();
    }
}

void USART_TX_COMPLETE_ISR()
{
    if (callbackTxComplete != NULL)
    {
        callbackTxComplete();
    }
}

void USART_RX_COMPLETE_ISR()
{
    if (callbackRxComplete != NULL)
    {
        callbackRxComplete();
    }
}

void initStack(usart_stack *s)
{
    u8 i;
    for (i = 0; i < STACK_SIZE; i++)
        s->arr[i] = 0;
    s->sp = -1;
}

u8 stackPush(usart_stack *s, u8 data)
{
    if (s->sp == STACK_SIZE - 1)
        return 1;
    else
    {
        s->sp++;
        s->arr[s->sp] = data;
        return 0;
    }
}

u8 stackPop(usart_stack *s)
{
    if (s->sp == -1)
    {
        return -1;
    }
    else
        s->sp--;
    return s->arr[s->sp + 1];
}