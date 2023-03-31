#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include <Logger/Logger.hpp>
#include <Memory/memoire_24.h>
#include "svg/Structure.h"

void initialisationUART (void) {
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0               
    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C = (1 << UCSZ01)|(1 << UCSZ00);
}

void transmissionUART ( uint8_t donnee ) {
    while (!(UCSR0A & (1 << UDRE0))) {}
    UDR0 = donnee;
}

void ecrireMemoire(uint16_t adresse, char message[], uint8_t &taille, Memoire24CXXX memory) {
    taille = strlen(message);
    memory.ecriture(adresse, (uint8_t*)message, taille);
    _delay_ms(10);
}

void lireMemoire(Memoire24CXXX memory, uint16_t tailleTotale){
    initialisationUART();

    uint8_t reception[127];
    
    uint8_t buffer = tailleTotale%127;
    uint8_t iterations = 0;
    for(iterations; iterations * 127 < tailleTotale -127; iterations++)
    {
        
        memory.lecture(iterations * 127, reception, 127);

        for (uint16_t i = 0; i < 127; i++) {
            transmissionUART(reception[i]);
        }
    }

    memory.lecture(iterations * 127, reception, buffer);

    for (uint16_t i = 0; i < buffer; i++) {
        transmissionUART(reception[i]);
    }
}

void init(uint16_t &adresse, uint16_t &tailleTotale, uint8_t &taille, Memoire24CXXX memory){

    _delay_ms(500);
    char message[] = "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 1152 576\">\n";
    ecrireMemoire(adresse, message, taille, memory);
    tailleTotale += taille;
    adresse += taille;

    char messageRect[] = "<rect x = \"96\" y = \"48\" width = \"960\" height = \"480\" stroke = \"black\" stroke-width = \"1\" fill = \"white\" />\n";
    ecrireMemoire(adresse, messageRect, taille, memory);
    tailleTotale += taille;
    adresse += taille;

    char messageRouge[] = "<rect x = \"188\" y = \"450\" width = \"7\" height = \"7\" stroke = \"red\" stroke-width = \"1\" fill = \"red\"/>\n";
    ecrireMemoire(adresse, messageRouge, taille, memory);
    tailleTotale += taille;
    adresse += taille;
}

void ecrireRectangles(uint16_t &adresse, uint8_t& taille, uint16_t& tailleTotale, Point* points, uint8_t &nbPoints, Memoire24CXXX memory){
    uint8_t index = 1;
    for(int8_t i = 3; i > -1; i--){
        for (uint8_t j = 0; j < 8; j++){
            if (i == 3 and j == 0) {
                continue;
            }
            uint16_t x = 188 + 110 * j;
            uint16_t y = 120 + 110 * i;
            points[nbPoints++] = Point(index+1, x, y);
            char rect[110];
            sprintf(rect, "<rect x = \"%d\" y = \"%d\" width = \"7\" height = \"7\" stroke = \"black\" stroke-width = \"1\" fill = \"black\"/>\n", x, y);
            ecrireMemoire(adresse, rect, taille, memory);
            tailleTotale += taille;
            adresse += taille;
            index++;
        }
        _delay_ms(10);
    }
}

void makeCircles(Point points[], uint8_t& nbPoints, uint16_t& adresse, uint8_t& taille, uint16_t& tailleTotale, Memoire24CXXX memory) {

    for (int i = 0; i < nbPoints; i++) {
        Point point = points[i];
        int x = point.getX();
        int y = point.getY();
        char cercle[100];
        sprintf(cercle, "<circle cx = \"%d\" cy = \"%d\" r = \"10\" stroke = \"black\" stroke-width = \"2\" fill = \"gray\" />\n", x, y);
        ecrireMemoire(adresse, cercle, taille, memory);
        tailleTotale += taille;
        adresse += taille;
    }
}

Point trouverPoint(Point points[], int indice) {
    return points[indice - 1];
}

void trouverPointsVisites(uint8_t* indicesVisites, Point points[], Point pointsVisites[], uint8_t nVisites)
{
    for (uint8_t i = 0; i < nVisites; i++) {
        Point pointVisite = trouverPoint(points, indicesVisites[i]);
        pointsVisites[i] = pointVisite;
    }

    for (uint8_t i = 0; i < nVisites; i++) {
        Point point = pointsVisites[i];
    }
}

int main(){
    uint16_t tailleTotale = 0;
    uint16_t adresse = 0;
    uint8_t taille = 0;
    uint8_t nbPoints = 0;
    Memoire24CXXX memory;

    Point points[32];
    Point pointsVisites[8];
    uint8_t indicesVisites[] = { 32, 20, 6, 4, 13, 19, 22, 12 };
    uint8_t nVisites = sizeof(indicesVisites) / sizeof(uint8_t);

    points[nbPoints++] = Point(1, 188, 450);

    init(adresse, tailleTotale, taille, memory);

    ecrireRectangles(adresse, taille, tailleTotale, points, nbPoints, memory);

    trouverPointsVisites(indicesVisites, points, pointsVisites, nVisites);

    makeCircles(pointsVisites, nVisites, adresse, taille, tailleTotale, memory);

    char messageFin[] = "</svg>";
    ecrireMemoire(adresse, messageFin, taille, memory);
    tailleTotale += taille;
    adresse += taille;

    _delay_ms(1000);

    lireMemoire(memory, tailleTotale);
}