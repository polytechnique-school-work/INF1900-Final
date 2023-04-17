// #include "Structures.hpp"

// void SVG::ecrireMemoire(char* message) {
//     taille = strlen(message);
//     memory->ecriture(adresse, (uint8_t*)message, taille);
//     adresse += taille;
//     tailleTotale += taille;
//     _delay_ms(10);
// }

// uint16_t SVG::calculAire(){
//     uint16_t tableauX[nContour];
//     uint16_t tableauY[nContour];

//     for(uint8_t i = 0; i < nContour; i++){
//         tableauX[i] = pointsContour[i].getX();
//         tableauY[i] = pointsContour[i].getY();
//     }

//     float total = 0;
//     for (uint8_t i = 0; i < nContour -1; i++){
//         total += tableauX[i] * tableauY[i+1];
//     }
//     total += tableauX[nContour-1] * tableauY[0];
//     for (uint8_t i = 0; i < nContour -1; i++){
//         total -= tableauY[i] * tableauX[i+1];
//     }
//     total -= tableauY[nContour-1] * tableauX[0];

//     if(total < 0){
//         total *= -1;
//     }

//     return (total/2);
// }

// void SVG::init(){

//     _delay_ms(500);
//     {
//         char* message = "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\"
//         viewBox=\"0 0 115 58\">\n"; ecrireMemoire(message);
//     }

//     {constexpr char* style = "<style> .small { font: 2px sans-serif; }</style>";
//     ecrireMemoire(style);}

//     {char* equipe = "<text x=\"10\" y=\"4\" fill=\"blue\" class = \"small\"> section01 -- équipe
//     020304 -- Crazy Frog </text>"; ecrireMemoire(equipe);}

//     {char* messageRect = "<rect x = \"10\" y = \"5\" width = \"96\" height = \"48\" stroke =
//     \"black\" stroke-width = \".2\" fill = \"white\" />\n"; ecrireMemoire(messageRect);}

//     {char* messageRouge = "<rect x = \"19\" y = \"45\" width = \"1\" height = \"1\" stroke =
//     \"red\" stroke-width = \".2\" fill = \"red\"/>\n"; ecrireMemoire(messageRouge);}
// }

// void SVG::ecrireRectangles(){
//     for(uint8_t i = 0; i < nbPoints; i++){
//         if(points[i].getIndex() == 1)
//             continue;
//         char rect[110];
//         sprintf(rect, "<rect x = \"%d\" y = \"%d\" width = \"1\" height = \"1\" stroke =
//         \"black\" stroke-width = \".2\" fill = \"black\"/>\n", points[i].getX(),
//         points[i].getY()); ecrireMemoire(rect); _delay_ms(10);
//     }
// }

// void SVG::makeCircles() {
//     for(uint8_t i = 0; i < nVisites; i++){
//         char cercle[100];
//         sprintf(cercle, "<circle cx = \"%d\" cy = \"%d\" r = \"1.5\" stroke = \"black\"
//         stroke-width = \".2\" fill = \"gray\" />\n", pointsVisites[i].getX(),
//         pointsVisites[i].getY()); ecrireMemoire(cercle);
//     }
// }

// void SVG::makePolygon() {
//     {char polygone[60] = "<polygon points= \"";
//     for(uint8_t i = 0; i < nContour; i++){
//         char coordonnees[10];
//         sprintf(coordonnees, "%d, %d ", pointsContour[i].getX(), pointsContour[i].getY());
//         strcat(polygone, coordonnees);
//     }
//     ecrireMemoire(polygone);}

//     {char* polyParams ="\" fill = \"rgba(0, 255, 0, 0.25)\" stroke = \"black\" stroke-width =
//     \".2\" />\n"; ecrireMemoire(polyParams);}

//     {char polyText[85];
//     uint16_t area = calculAire();
//     sprintf(polyText, "<text x=\"10\" y=\"56\" fill=\"blue\" class=\"small\" > Aire: %d pouces
//     carrés </text>", area); ecrireMemoire(polyText);}
// }

// void SVG::trouverPointsVisites()
// {
//     for (uint8_t i = 0; i < nVisites; i++) {
//         Point pointVisite = points[indicesVisites[i]-1];
//         pointsVisites[i] = pointVisite;
//     }
// }

// void SVG::sortArray(Cosinus cosinus[], uint8_t& nCosinus) {
//     for (uint8_t i = 1; i < nCosinus - 1; i++) {
//         for (uint8_t j = 0; j < nCosinus - 1; j++) {
//             if (cosinus[j + 1].getCos() < cosinus[j].getCos()) {
//                 Cosinus temp = cosinus[j + 1];
//                 cosinus[j + 1] = cosinus[j];
//                 cosinus[j] = temp;
//             }
//         }
//     }

//     for (uint8_t i = 1; i < nCosinus - 1; i++) {
//         for (uint8_t j = 0; j < nCosinus - 1; j++) {
//             if (cosinus[j + 1].getCos() == cosinus[j].getCos()) {
//                 float longueur1 = Vector(points[cosinus[j].getIndex() + 1].getX(), 450 -
//                 points[cosinus[j].getIndex() + 1].getY()).getNorme(); float longueur2 =
//                 Vector(points[cosinus[j + 1].getIndex() + 1].getX(), 450 - points[cosinus[j +
//                 1].getIndex() + 1].getY()).getNorme(); if (longueur1 > longueur2) {
//                     Cosinus temp = cosinus[j + 1];
//                     cosinus[j + 1] = cosinus[j];
//                     cosinus[j] = temp;
//                 }
//             }
//         }
//     }
// }

// void SVG::algorithmeGraham() {
//     Point pointMinimum(0, 105, 5);
//     for (uint8_t i = 0; i < nVisites; i++) {
//         Point point = pointsVisites[i];
//         bool plusBas = point.getY() > pointMinimum.getY();
//         bool plusGauche = (point.getY() == pointMinimum.getY()) && (point.getX() <
//         pointMinimum.getX()); if (plusBas || plusGauche) {
//             pointMinimum = point;
//         }
//     }

//     Cosinus cosinus[8];
//     uint8_t nCosinus = 0;

//     Vector vecteurs[8];
//     uint8_t nVecteurs = 0;

//     for (uint8_t i = 0; i < nVisites; i++) {
//         Point point = pointsVisites[i];
//         if (point == pointMinimum) {
//             cosinus[nCosinus] = Cosinus(point.getIndex(), 0.0);
//             nCosinus++;
//             vecteurs[nVecteurs] = Vector();
//             nVecteurs++;
//             continue;
//         }
//         Vector vecteur(point.getX() - pointMinimum.getX(), point.getY() - pointMinimum.getY());
//         vecteurs[nVecteurs] = vecteur;
//         nVecteurs++;
//         cosinus[nCosinus] = Cosinus(point.getIndex(), vecteur.getACos());
//         nCosinus++;
//     }

//     sortArray(cosinus, nCosinus);

//     int8_t iteration = 2;
//     while (iteration < nCosinus) {
//         int8_t indice1 = cosinus[iteration - 2].getIndex();
//         Point point1 = points[indice1 - 1];
//         int8_t indice2 = cosinus[iteration - 1].getIndex();
//         Point point2 = points[indice2 - 1];
//         int8_t indice3 = cosinus[iteration].getIndex();
//         Point point3 = points[indice3 - 1];

//         float direction = (point2.getX() - point1.getX()) * (point1.getY() - point3.getY()) -
//         ((point1.getY() - point2.getY()) * (point3.getX() - point1.getX())); if (direction < 0) {
//             for (uint8_t i = iteration; i < nCosinus; i++) {
//                 cosinus[i - 1] = cosinus[i];
//             }
//             nCosinus--;
//             nVisites--;
//             iteration--;
//             continue;
//         }
//         iteration++;
//     }

//     for (int i = 0; i < nCosinus; i++) {
//         pointsContour[i] = points[cosinus[i].getIndex() - 1];
//         nContour++;
//     }

// }

// void SVG::ecrireSVGMemoire(){

//     init();

//     ecrireRectangles();

//     trouverPointsVisites();

//     makeCircles();

//     algorithmeGraham();

//     makePolygon();

//     {char* messageFin = "</svg>";
//     ecrireMemoire(messageFin);}

// }