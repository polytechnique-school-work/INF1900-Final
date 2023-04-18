#include "Structures.hpp"
#define DIVISOR 0xEDB88320

uint16_t SVG::calculAire() {
    uint16_t tableauX[nContour];
    uint16_t tableauY[nContour];

    for (uint8_t i = 0; i < nContour; i++) {
        tableauX[i] = pointsContour[i].getX();
        tableauY[i] = pointsContour[i].getY();
    }

    float total = 0;
    for (uint8_t i = 0; i < nContour - 1; i++) {
        total += tableauX[i] * tableauY[i + 1];
    }
    total += tableauX[nContour - 1] * tableauY[0];
    for (uint8_t i = 0; i < nContour - 1; i++) {
        total -= tableauY[i] * tableauX[i + 1];
    }
    total -= tableauY[nContour - 1] * tableauX[0];

    if (total < 0) {
        total *= -1;
    }

    return (total / 2);
}

void SVG::transmettreMessage(const char message[]) {
    for (uint8_t i = 0; i < strlen(message); i++) {
        char octet = message[i];
        crc        = crc ^ octet;
        for (int k = 8; k; k--) {
            if (crc & 1) {
                crc = (crc >> 1) ^ DIVISOR;
            } else {
                crc = (crc >> 1);
            }
        }
        if (clock->getTimestamp() > previousTimestamp + 5) {
            if (color == Color::OFF) {
                light->setLight(Color::GREEN);
                color = Color::GREEN;
            } else {
                light->setLight(Color::OFF);
                color = Color::OFF;
            }
            previousTimestamp = clock->getTimestamp();
        }
        Logger::transmitUSART(octet);
    }
}

void SVG::init() {

    {
        char message[] = "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\" "
                         "viewBox=\"0 0 115 58\">\n";
        transmettreMessage(message);
    }

    {
        char message[] = "<style> .small { font: 2px sans-serif; }</style>\n";
        transmettreMessage(message);
    }

    {
        char message[] = "<text x=\"10\" y=\"4\" fill=\"blue\" class = \"small\"> section01 -- "
                         "equipe 020304 -- Crazy Frog </text>\n";
        transmettreMessage(message);
    }

    {
        char message[] = "<rect x = \"10\" y = \"5\" width = \"96\" height = \"48\" stroke = "
                         "\"black\" stroke-width = \".2\" fill = \"white\" />\n";
        transmettreMessage(message);
    }

    {
        char message[] = "<rect x = \"19\" y = \"45\" width = \"1\" height = \"1\" stroke = "
                         "\"red\" stroke-width = \".2\" fill = \"red\"/>\n";
        transmettreMessage(message);
    }
}

void SVG::ecrireRectangles() {

    for (uint8_t i = 0; i < nbPoints; i++) {
        if (points[i].getIndex() == 1) continue;
        char message[110];
        sprintf(message,
                "<rect x = \"%d\" y = \"%d\" width = \"1\" height = \"1\" stroke = \"black\" "
                "stroke-width = \".2\" fill = \"black\"/>\n",
                points[i].getX(), points[i].getY());
        transmettreMessage(message);
        _delay_ms(10);
    }
}

void SVG::makeCircles() {
    for (uint8_t i = 0; i < nVisites; i++) {
        char message[100];
        sprintf(message,
                "<circle cx = \"%d\" cy = \"%d\" r = \"1.5\" stroke = \"black\" stroke-width = "
                "\".2\" fill = \"gray\" />\n",
                pointsVisites[i].getX(), pointsVisites[i].getY());
        transmettreMessage(message);
    }
}

void SVG::makePolygon() {
    {
        char message[60] = "<polygon points= \"";
        for (uint8_t i = 0; i < nContour; i++) {
            char coordonnees[10];
            sprintf(coordonnees, "%d, %d ", pointsContour[i].getX(), pointsContour[i].getY());
            strcat(message, coordonnees);
        }
        transmettreMessage(message);
    }

    {
        char message[] =
            "\" fill = \"rgba(0, 255, 0, 0.25)\" stroke = \"black\" stroke-width = \".2\" />\n";
        transmettreMessage(message);
    }

    {
        char message[85];
        uint16_t area = calculAire();
        sprintf(message,
                "<text x=\"10\" y=\"56\" fill=\"blue\" class=\"small\" > Aire: %d pouces carres "
                "</text>",
                area);
        transmettreMessage(message);
    }
}

void SVG::trouverPointsVisites() {
    for (uint8_t i = 0; i < nVisites; i++) {
        Point pointVisite = points[indicesVisites[i] - 1];
        pointsVisites[i]  = pointVisite;
    }
}

void SVG::sortArray(Cosinus cosinus[], uint8_t& nCosinus) {
    for (uint8_t i = 1; i < nCosinus - 1; i++) {
        for (uint8_t j = 0; j < nCosinus - 1; j++) {
            if (cosinus[j + 1].getCos() < cosinus[j].getCos()) {
                Cosinus temp   = cosinus[j + 1];
                cosinus[j + 1] = cosinus[j];
                cosinus[j]     = temp;
            }
        }
    }

    for (uint8_t i = 1; i < nCosinus - 1; i++) {
        for (uint8_t j = 0; j < nCosinus - 1; j++) {
            if (cosinus[j + 1].getCos() == cosinus[j].getCos()) {
                float longueur1 = Vector(points[cosinus[j].getIndex() + 1].getX(),
                                         450 - points[cosinus[j].getIndex() + 1].getY())
                                      .getNorme();
                float longueur2 = Vector(points[cosinus[j + 1].getIndex() + 1].getX(),
                                         450 - points[cosinus[j + 1].getIndex() + 1].getY())
                                      .getNorme();
                if (longueur1 > longueur2) {
                    Cosinus temp   = cosinus[j + 1];
                    cosinus[j + 1] = cosinus[j];
                    cosinus[j]     = temp;
                }
            }
        }
    }
}

void SVG::algorithmeGraham() {
    Point pointMinimum(0, 105, 5);
    for (uint8_t i = 0; i < nVisites; i++) {
        Point point  = pointsVisites[i];
        bool plusBas = point.getY() > pointMinimum.getY();
        bool plusGauche =
            (point.getY() == pointMinimum.getY()) && (point.getX() < pointMinimum.getX());
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
        Point point1   = points[indice1 - 1];
        int8_t indice2 = cosinus[iteration - 1].getIndex();
        Point point2   = points[indice2 - 1];
        int8_t indice3 = cosinus[iteration].getIndex();
        Point point3   = points[indice3 - 1];

        float direction = (point2.getX() - point1.getX()) * (point1.getY() - point3.getY()) -
                          ((point1.getY() - point2.getY()) * (point3.getX() - point1.getX()));
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

void SVG::transmitSVG() {

    init();

    for (int8_t i = 3; i > -1; i--) {
        for (uint8_t j = 0; j < 8; j++) {
            uint8_t x          = 19 + 11 * j;
            uint8_t y          = 12 + 11 * i;
            points[nbPoints++] = Point(j + (3 - i) * 8 + 1, x, y);
        }
    }

    ecrireRectangles();

    trouverPointsVisites();

    makeCircles();

    algorithmeGraham();

    makePolygon();

    {
        char message[] = "</svg>";
        transmettreMessage(message);
    }
}