#include "Writer.hpp"
#include <Logger/Logger.hpp>
unsigned char Writer::receiveUSART() {
    /* Wait for data to be received */
    while (!(UCSR0A & (1 << RXC0)))
        ;
    /* Get and return received data from buffer */
    return UDR0;
}

void Writer::initReceiveUSART() {
    // 2400 bauds
    // Format des trames: 8 bits, 1 stop bits, sans parité
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

void Writer::receive() {

    Memoire24CXXX memoire24CXXX;

    this->initReceiveUSART();
    uint8_t data[255];

    data[0] = this->receiveUSART();
    data[1] = this->receiveUSART();

    uint8_t size = (data[0] << 8) | data[1];

    for (uint8_t i = 2; i < size; i++) {
        data[i] = this->receiveUSART();
        _delay_ms(5);
    }

    for (uint8_t i = 0; i < size; i++) {
        memoire24CXXX.ecriture(i, data[i]);
        _delay_ms(5);
    }
}
