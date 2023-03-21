#define F_CPU 8000000UL
#include "Writer.hpp"
#include <Logger/Logger.hpp>
#include <util/delay.h>
int main() {
    Writer writer;
    writer.receive();
}