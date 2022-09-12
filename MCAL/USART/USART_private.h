#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

#define UDR (*(volatile u8 *)(0x2C))
#define UCSRA (*(volatile u8 *)(0x2B))
#define UCSRB (*(volatile u8 *)(0x2A))
#define UCSRC (*(volatile u8 *)(0x40))
#define UBRRL (*(volatile u8 *)(0x29))
#define UBRRH (*(volatile u8 *)(0x40))

#define MPCM 0
#define U2X 1
#define PE 2
#define DOR 3
#define FE 4
#define UDRE 5
#define TXC 6
#define RXC 7

#define TXB8 0
#define RXB8 1
#define UCSZ2 2
#define TXEN 3
#define RXEN 4
#define UDRIE 5
#define TXCIE 6
#define RXCIE 7

#define UCPOL 0
#define UCSZ0 1
#define UCSZ1 2
#define USBS 3
#define UPM0 4
#define UPM1 5
#define UMSEL 6
#define URSEL 7

#define USART_NO_PARITY 0
#define USART_EVEN_PARITY 1
#define USART_ODD_PARITY 2

#define USART_DATA_5BIT 0
#define USART_DATA_6BIT 1
#define USART_DATA_7BIT 2
#define USART_DATA_8BIT 3
#define USART_DATA_9BIT 4

#define USART_STOP_1BIT 0
#define USART_STOP_2BIT 1

#define USART_SYNCHRONOUS 0
#define USART_ASYNCHRONOUS 1

#define USART_NORMAL_SPEED 0
#define USART_DOUBLE_SPEED 1

#define USART_RISING_EDGE 0
#define USART_FALLING_EDGE 1

#define USART_BAUD_2400 0
#define USART_BAUD_4800 1
#define USART_BAUD_9600 2
#define USART_BAUD_14400 3
#define USART_BAUD_19200 4
#define USART_BAUD_28800 5
#define USART_BAUD_38400 6
#define USART_BAUD_57600 7
#define USART_BAUD_76800 8
#define USART_BAUD_115200 9
#define USART_BAUD_230400 10
#define USART_BAUD_250000 11
#define USART_BAUD_500000 12

#define USART_EMPTY 0
#define USART_TX_COMPLETE 1
#define USART_RX_COMPLETE 2

#define NULL 0

#define USART_EMPTY_ISR __vector_14
#define USART_TX_COMPLETE_ISR __vector_15
#define USART_RX_COMPLETE_ISR __vector_13

#endif