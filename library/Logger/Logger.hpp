#pragma once
#include <avr/io.h>
#include "string.h"
#include <stdio.h>

//#define DEBUG // à mettre en commentaire ou non au besoin

enum class Priority {INFO, ERROR};
class Logger {
private:
    static void transmitUSART(uint8_t data);
    static void transmitMessage(const char* message);
    static void format(Priority priority, const char* message, bool skipLine=true);
    static bool isInit;
public:
    static void init();
    static void log(Priority priority, const char* message, bool skipLine=true);
    static void log(Priority priority, const int number, bool skipLine=true);
};

#ifdef DEBUG
# define DEBUG_PRINT(x) Logger::init(); \
                        Logger::log(Priority::INFO, x) // ou par RS-232

#else

# define DEBUG_PRINT(x) do {} while (0) // code mort

#endif
