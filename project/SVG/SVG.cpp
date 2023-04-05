#include "Structures.hpp"

void SVG::ecrireMemoire(char message[]) {
    taille = strlen(message);
    memory->ecriture(adresse, (uint8_t*)message, taille);
    adresse += taille;
    tailleTotale += taille;
    _delay_ms(10);
}

// void lireMemoire(Memoire24CXXX memory, uint16_t tailleTotale){
//     initialisationUART();

//     uint8_t reception[127];
    
//     uint8_t buffer = tailleTotale%127;
//     uint8_t iterations = 0;
//     for(iterations; iterations * 127 < tailleTotale -127; iterations++)
//     {
        
//         memory.lecture(iterations * 127, reception, 127);

//         for (uint16_t i = 0; i < 127; i++) {
//             transmissionUART(reception[i]);
//         }
//     }

//     memory.lecture(iterations * 127, reception, buffer);

//     for (uint16_t i = 0; i < buffer; i++) {
//         transmissionUART(reception[i]);
//     }
// }

void SVG::init(){

    _delay_ms(500);
    char message[] = "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 115 58\">\n";
    ecrireMemoire(message);

    char messageRect[] = "<rect x = \"10\" y = \"5\" width = \"96\" height = \"48\" stroke = \"black\" stroke-width = \"1\" fill = \"white\" />\n";
    ecrireMemoire(messageRect);

    char messageRouge[] = "<rect x = \"19\" y = \"45\" width = \"1\" height = \"1\" stroke = \"red\" stroke-width = \".2\" fill = \"red\"/>\n";
    ecrireMemoire(messageRouge);
}

void SVG::ecrireRectangles(){
    for(uint8_t i = 0; i < nbPoints; i++){
        if(points[i].getIndex() == 1)
            continue;
        char rect[110];
        sprintf(rect, "<rect x = \"%d\" y = \"%d\" width = \"1\" height = \"1\" stroke = \"black\" stroke-width = \".2\" fill = \"black\"/>\n", points[i].getX(), points[i].getY());
        ecrireMemoire(rect);
        _delay_ms(10);
    }
}

void SVG::makeCircles() {
    for(uint8_t i = 0; i < nVisites; i++){
        char cercle[100];
        sprintf(cercle, "<circle cx = \"%d\" cy = \"%d\" r = \"1.5\" stroke = \"black\" stroke-width = \".2\" fill = \"gray\" />\n", pointsVisites[i].getX(), pointsVisites[i].getY());
        ecrireMemoire(cercle);
    }
}

void SVG::makePolygon() {
    char polygone[60] = "<polygon points= \"";
    for(uint8_t i = 0; i < nContour; i++){
        char coordonnees[10];
        sprintf(coordonnees, "%d, %d ", pointsContour[i].getX(), pointsContour[i].getY());
        strcat(polygone, coordonnees);
    }
    ecrireMemoire(polygone);

    char polyParams[] ="\" fill = \"rgba(0, 255, 0, 0.25)\" stroke = \"black\" stroke-width = \"1\" />";
    ecrireMemoire(polyParams);
}

void SVG::trouverPointsVisites()
{
    for (uint8_t i = 0; i < nVisites; i++) {
        Point pointVisite = points[indicesVisites[i]-1];
        pointsVisites[i] = pointVisite;
    }
}

void SVG::sortArray(Cosinus cosinus[], uint8_t& nCosinus) {
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

void SVG::algorithmeGraham() {
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
    
    sortArray(cosinus, nCosinus);


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
        nContour++;
    }

}

void SVG::ecrireSVGMemoire(){

    init();

    ecrireRectangles();

    trouverPointsVisites();

    makeCircles();

    algorithmeGraham();

    makePolygon();

    char messageFin[] = "</svg>";
    ecrireMemoire(messageFin);

}