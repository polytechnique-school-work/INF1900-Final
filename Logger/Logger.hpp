#pragma once
#include <avr/io.h>
#include "string.h"

enum class Priority {INFO, ERROR};
class Logger {
private:
    static void transmitUSART(uint8_t data);
    static void transmitMessage(const char* message);
public:
    static void init();
    static void log(Priority priority, const char* message);
};