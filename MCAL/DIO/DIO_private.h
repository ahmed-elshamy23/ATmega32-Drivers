#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

#define PORTA_REG *((volatile u8 *)(0x3B))
#define DDRA_REG *((volatile u8 *)(0x3A))
#define PINA_REG *((volatile u8 *)(0x39))

#define PORTB_REG *((volatile u8 *)(0x38))
#define DDRB_REG *((volatile u8 *)(0x37))
#define PINB_REG *((volatile u8 *)(0x36))

#define PORTC_REG *((volatile u8 *)(0x35))
#define DDRC_REG *((volatile u8 *)(0x34))
#define PINC_REG *((volatile u8 *)(0x33))

#define PORTD_REG *((volatile u8 *)(0x32))
#define DDRD_REG *((volatile u8 *)(0x31))
#define PIND_REG *((volatile u8 *)(0x30))

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1

#define ALL_INPUT 0
#define ALL_OUTPUT 0xFF

#endif