#define F_CPU 16000000UL // Clock speed of MCU, 16 MHz for Arduino Uno
#define BAUD 9600
#define MY_UBRR F_CPU/16/BAUD-1
#define USART_CMD_BUFFER 32 // Maximum USART command char length

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

// Function to receive a string over USART
void USART_ReceiveString(char* buffer, unsigned char max_length) {
    unsigned char receivedChar;
    unsigned char charCount = 0;

    // Manually clear the buffer
    for (unsigned char i = 0; i < max_length; i++) {
        buffer[i] = 0;
    }

    do {
        while (!(UCSR0A & (1<<RXC0)));  // Wait for data to be received
        receivedChar = UDR0; // Get and return received data from buffer

        // Check for termination character or max length
        if (receivedChar != '\n' && charCount < (max_length - 1)) {
            buffer[charCount++] = receivedChar;
        }

    } while (receivedChar != '\n' && charCount < (max_length - 1));

    buffer[charCount] = '\0'; // Null-terminate the string
}

void USART_Print(const char* str) {
    while (*str) {
        USART_Transmit(*str++);
    }
}

int main(void) {
    USART_Init(MY_UBRR); // Initialize USART with baud rate

    while (1) {
        USART_Print("Hello AVR developer! Please type a command: "); // Request input

        char receivedCommand[USART_CMD_BUFFER];  // Buffer for the received string
        USART_ReceiveString(receivedCommand, USART_CMD_BUFFER); // Receive a string from USART
        
        /* Execute MCU actions here based on receivedCommand */

        // Echo back the received string for testing
        USART_Print("\r\nYou typed: ");
        USART_Print(receivedCommand);
        USART_Print("\r\n");
    }
    
    return 0; // Never reached
}