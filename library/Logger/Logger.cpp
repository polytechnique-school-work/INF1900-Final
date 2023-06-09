#include "Logger.hpp"

void Logger::transmitUSART(uint8_t data) {
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}
bool Logger::isInit = false;
void Logger::init() {
    // 2400 bauds
    // Format des trames: 8 bits, 1 stop bits, sans parité
    if (Logger::isInit) return;
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0); // Receiver enable RXEN0 : 1
    // UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
    Logger::isInit = true;
}

void Logger::transmitMessage(const char* message) {
    for (const char* ptr = message; *ptr != '\0'; ++ptr) {
        Logger::transmitUSART(*ptr);
    }
}

void Logger::log(Priority priority, const char* message, bool skipLine) {
    Logger::format(priority, message, skipLine);
}

void Logger::log(Priority priority, const uint16_t number, bool skipLine) {
    char message[5];
    sprintf(message, "%u", number);
    Logger::format(priority, message, skipLine);
}

void Logger::log(Priority priority, const char* message, const uint16_t number) {
    char num[128];
    sprintf(num, "%s: %u", message, number);
    Logger::format(priority, num, true);
}

void Logger::format(Priority priority, const char* message, bool skipLine) {
    // S'assurer que le logger est init.
    Logger::init();
    const char* prefix = priority == Priority::ERROR ? "[E]: " : "[I]: ";
    char fullMessage[128];
    sprintf(fullMessage, "%s %s%s", prefix, message, skipLine ? "\n" : "");
    Logger::transmitMessage(fullMessage);
}