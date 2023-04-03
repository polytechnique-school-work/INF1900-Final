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
    char message[] = "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 115 58\">\n";
    ecrireMemoire(adresse, message, taille, memory);
    tailleTotale += taille;
    adresse += taille;

    char messageRect[] = "<rect x = \"10\" y = \"5\" width = \"96\" height = \"48\" stroke = \"black\" stroke-width = \"1\" fill = \"white\" />\n";
    ecrireMemoire(adresse, messageRect, taille, memory);
    tailleTotale += taille;
    adresse += taille;

    char messageRouge[] = "<rect x = \"19\" y = \"45\" width = \"1\" height = \"1\" stroke = \"red\" stroke-width = \"1\" fill = \"red\"/>\n";
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
            uint8_t x = 19 + 11 * j;
            uint8_t y = 12 + 11 * i;
            points[nbPoints++] = Point(index+1, x, y);
            char rect[110];
            sprintf(rect, "<rect x = \"%d\" y = \"%d\" width = \"1\" height = \"1\" stroke = \"black\" stroke-width = \"1\" fill = \"black\"/>\n", x, y);
            ecrireMemoire(adresse, rect, taille, memory);
            tailleTotale += taille;
            adresse += taille;
            index++;
        }
        _delay_ms(10);
    }
}

void makeCircles(Point points[], uint8_t& nbPoints, uint16_t& adresse, uint8_t& taille, uint16_t& tailleTotale, Memoire24CXXX memory) {

    for (uint8_t i = 0; i < nbPoints; i++) {
        Point point = points[i];
        uint8_t x = point.getX();
        uint8_t y = point.getY();
        char cercle[100];
        sprintf(cercle, "<circle cx = \"%d\" cy = \"%d\" r = \"1\" stroke = \"black\" stroke-width = \"2\" fill = \"gray\" />\n", x, y);
        ecrireMemoire(adresse, cercle, taille, memory);
        tailleTotale += taille;
        adresse += taille;
    }
}

void makePolygon(Point points[], int numPoints, uint16_t& adresse, uint8_t& taille, uint16_t& tailleTotale, Memoire24CXXX memory) {
   
    char polygone[60];
    strcat(polygone, "<polygon points= \"");
    for (uint8_t i = 0; i < numPoints; i++) {
        Point point = points[i];
        uint8_t x = point.getX();
        uint8_t y = point.getY();
        char coordonnees[10];
        sprintf(coordonnees, "%d, %d ", x, y);
        strcat(polygone, coordonnees);
    }
    ecrireMemoire(adresse, polygone, taille, memory);
    tailleTotale += taille;
    adresse += taille;

    char polyParams[] ="\" fill = \"rgba(0, 255, 0, 0.25)\" stroke = \"black\" stroke-width = \"1\" />";
    ecrireMemoire(adresse, polyParams, taille, memory);
    tailleTotale += taille;
    adresse += taille;
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

void sortArray(Cosinus cosinus[], Point points[], uint8_t& nCosinus) {
    for (uint8_t i = 1; i < nCosinus - 1; i++) {
        for (uint8_t j = 0; j < nCosinus - 1; j++) {
            if (cosinus[j + 1].getCos() < cosinus[j].getCos()) {
                Cosinus temp = cosinus[j + 1];
                cosinus[j + 1] = cosinus[j];
                cosinus[j] = temp;
            }
        }
    }

    for (uint8_t i = 1; i < nCosinus - 1; i++) {
        for (uint8_t j = 0; j < nCosinus - 1; j++) {
            if (cosinus[j + 1].getCos() == cosinus[j].getCos()) {
                float longueur1 = Vector(points[cosinus[j].getIndex() + 1].getX(), 450 - points[cosinus[j].getIndex() + 1].getY()).getNorme();
                float longueur2 = Vector(points[cosinus[j + 1].getIndex() + 1].getX(), 450 - points[cosinus[j + 1].getIndex() + 1].getY()).getNorme();
                if (longueur1 > longueur2) {
                    Cosinus temp = cosinus[j + 1];
                    cosinus[j + 1] = cosinus[j];
                    cosinus[j] = temp;
                }
            }
        }
    }
}

void algorithmeGraham(Point pointsVisites[], Point points[], uint8_t& nVisites, Point pointsContour[]) {
    Point pointMinimum(0, 105, 5);
    for (uint8_t i = 0; i < nVisites; i++) {
        Point point = pointsVisites[i];
        bool plusBas = point.getY() > pointMinimum.getY();
        bool plusGauche = (point.getY() == pointMinimum.getY()) && (point.getX() < pointMinimum.getX());
        if (plusBas || plusGauche) {
            pointMinimum = point;
        }
    }

    Cosinus cosinus[8];
    uint8_t nCosinus = 0;

    Vector vecteurs[8];
    uint8_t nVecteurs = 0;

    for (uint8_t i = 0; i < nVisites; i++) {
        Point point = pointsVisites[i];
        if (point == pointMinimum) {
            cosinus[nCosinus] = Cosinus(point.getIndex(), 0.0);
            nCosinus++;
            vecteurs[nVecteurs] = Vector();
            nVecteurs++;
            continue;
        }
        Vector vecteur(point.getX() - pointMinimum.getX(), point.getY() - pointMinimum.getY());
        vecteurs[nVecteurs] = vecteur;
        nVecteurs++;
        cosinus[nCosinus] = Cosinus(point.getIndex(), vecteur.getACos());
        nCosinus++;
    }

    sortArray(cosinus, points, nCosinus);


    int8_t iteration = 2;
    while (iteration < nCosinus) {
        int8_t indice1 = cosinus[iteration - 2].getIndex();
        Point point1 = points[indice1 - 1];
        int8_t indice2 = cosinus[iteration - 1].getIndex();
        Point point2 = points[indice2 - 1];
        int8_t indice3 = cosinus[iteration].getIndex();
        Point point3 = points[indice3 - 1];

        float direction = (point2.getX() - point1.getX()) * (point1.getY() - point3.getY()) - ((point1.getY() - point2.getY()) * (point3.getX() - point1.getX()));
        if (direction < 0) {
            for (uint8_t i = iteration; i < nCosinus; i++) {
                cosinus[i - 1] = cosinus[i];
            }
            nCosinus--;
            nVisites--;
            iteration--;
            continue;
        }
        iteration++;
    }

    for (int i = 0; i < nCosinus; i++) {
        pointsContour[i] = points[cosinus[i].getIndex() - 1];
    }

}

int main(){
    Logger logger;
    logger.init();
    initialisationUART();
    uint16_t tailleTotale = 0;
    uint16_t adresse = 0;
    uint8_t taille = 0;
    uint8_t nbPoints = 0;
    Memoire24CXXX memory;

    Point points[32];
    Point pointsVisites[8];
    uint8_t indicesVisites[] = { 8, 9, 26, 30, 16};
    uint8_t nVisites = sizeof(indicesVisites) / sizeof(uint8_t);

    points[nbPoints++] = Point(1, 19, 45);

    init(adresse, tailleTotale, taille, memory);

    ecrireRectangles(adresse, taille, tailleTotale, points, nbPoints, memory);

    trouverPointsVisites(indicesVisites, points, pointsVisites, nVisites);

    makeCircles(pointsVisites, nVisites, adresse, taille, tailleTotale, memory);

    Point pointsContour[8];

    algorithmeGraham(pointsVisites, points, nVisites, pointsContour);

    makePolygon(pointsContour, nVisites, adresse, taille, tailleTotale, memory);

    char messageFin[] = "</svg>";
    ecrireMemoire(adresse, messageFin, taille, memory);
    tailleTotale += taille;
    adresse += taille;

    _delay_ms(1000);

    lireMemoire(memory, tailleTotale);
    return 0;
}