/*
 * Utilité : Ce module permet de logger des informations en console.
 * Autheurs : Équipe 020304
 * Date de création : 4 mars 2023
 * Ports utilisés:
 *  Entrée:
 *  Sortie:
 * */
#pragma once
#include "string.h"
#include <avr/io.h>
#include <stdio.h>

// #define DEBUG // à mettre en commentaire ou non au besoin

enum class Priority { INFO, ERROR };
class Logger {
private:
    static void transmitUSART(uint8_t data);
    static void transmitMessage(const char* message);
    static void format(Priority priority, const char* message, bool skipLine = true);
    static bool isInit;

public:
    static void init();
    static void log(Priority priority, const char* message, bool skipLine = true);
    static void log(Priority priority, const uint8_t number, bool skipLine = true);
};

#ifdef DEBUG
#define DEBUG_PRINT(x) Logger::log(Priority::INFO, x)

#else

#define DEBUG_PRINT(x)                                                                             \
    do {                                                                                           \
    } while (0)

#endif
