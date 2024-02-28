#define F_CPU 16000000UL // Clock speed of MCU, 16 MHz for Arduino Uno
#define BAUD 9600
#define MY_UBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

void USART_Init(unsigned int ubrr) {
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    // Enable receiver and transmitter
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    // Set frame format: 8data, 2stop bit
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit(unsigned char data) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1<<UDRE0)));
    // Put data into buffer, sends the data
    UDR0 = data;
}

unsigned char USART_Receive(void) {
    // Wait for data to be received
    while (!(UCSR0A & (1<<RXC0)));
    // Get and return received data from buffer
    return UDR0;
}

void USART_Print(const char* str) {
    while (*str) {
        USART_Transmit(*str++);
    }
}

// unsigned char USART_Receive(void) {
//     // Wait for data to be received
//     USART_Print("\r\nBeffore RXC0 check\r\n");
//     while (!(UCSR0A & (1<<RXC0)));
//     USART_Print("\r\nAfter RXC0 check\r\n");
//     unsigned char received = UDR0;
//     USART_Transmit(received); // Echo back what was received
//     return received;
// }

int main(void) {
    unsigned char receivedChar;

    USART_Init(MY_UBRR); // Initialize USART with baud rate

    while (1) {
        USART_Print("Hello AVR developer! Please type a character: "); // Request input
        
        receivedChar = USART_Receive(); // Wait for and receive a character
        
        // Echo back the received character
        USART_Print("\r\nYou typed: ");
        USART_Transmit(receivedChar);
        USART_Print("\r\n");
        
        _delay_ms(1000); // Add a delay before the next prompt
    }
    
    return 0; // Never reached
}