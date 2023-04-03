#include "detection.hpp"

// // Dès le début du mode détection, le robot fait prendre la couleur ambrée à sa DEL. 

// Il attend ensuite qu’on lui 
// indique dans quelle orientation il a été placé. S’il pointe vers le haut de la table, il faudra appuyer sur le bouton 
// Interrupt. S’il pointe vers la droite, sur le bouton blanc.

// // Pour signifier qu’il a bien compris, le robot mettra sa DEL en vert lorsqu’on lui dit qu’il pointe vers 
// le haut de la table, et en rouge pour la droite. La DEL garde cette couleur pendant 2 secondes puis s’éteint.

// // Le robot se met ensuite à la recherche du poteau. Dès qu’il le détecte, il se dirige vers celui-ci et 
// s’arrête lorsqu’il se trouve à proximité (entre 10 et 15 cm). Évidemment, si le poteau se trouvait déjà à une 
// distance située entre 10 et 15 cm (poteau voisin), le robot n’a pas à effectuer de déplacement. 

//Le robot émet ensuite une série de trois sons aigus. Les sons et les pauses qui les séparent sont tous d’une durée de 
// 300 millisecondes. 

//Finalement, le robot fait clignoter sa DEL en couleur ambrée à 2 Hz et se met en attente.

// // L’ évaluateur prend le poteau et le place sur un nouveau point. Il place ensuite le centre de rotation du 
// robot sur le point qui vient d’être libéré du poteau. Il oriente le robot vers le haut de la table. 

//L’évaluateur appuie alors sur le bouton Interrupt pour indiquer au robot d’arrêter de faire clignoter sa DEL et de chercher le 
// nouvel emplacement du poteau.

// // De 5 à 8 poteaux seront ainsi présentés au robot pour être détectés. Lorsqu’il aura jugé que c’est suffisant, 
// l’évaluateur gardera le poteau dans ses mains avant d’appuyer sur le bouton Interrupt. 

//Ensuite, dans sa procédure 
// de détection de poteau, le robot devra pouvoir déterminer qu’il n’y a plus de poteau sur la table pouvant être 
// détectés. Dès qu’il arrive à cette conclusion, le robot arrête de bouger et émet un son grave pendant 2 secondes. 
// Il fait ensuite clignoter sa DEL en rouge à 2 Hz.

LightManager lm(&DDRA, &PORTA, PORTA0, PORTA1); 


void RoutineDetection::loopSound()
{
    SoundPlayer sp;
    sp.init();

    for (int i = 0; i<3; i++)
    {
        sp.playSound(45);
        _delay_ms(300);
        sp.reset();
        _delay_ms(300);
    }
}

void RoutineDetection::sonGrave(uint8_t note)
{
    SoundPlayer sp;
    sp.init();
    sp.playSound(note);
    _delay_ms(1000);
    sp.reset();
}

void RoutineDetection::flashRed()
{
    while(true)
    {
        lm.setLight(Color::AMBER);
        _delay_ms(250);
        lm.setLight(Color::OFF);
        _delay_ms(250);
    }
}

void RoutineDetection::flashAmber()
{

    while(true)
    {
        for (int k = 0; k <12; k ++) {
        lm.setLight(Color::AMBER);
        }
        lm.setLight(Color::OFF);
        _delay_ms(250);
    }
}

void RoutineDetection::executeRoutine()
{
    RoutineSteps routineSteps;
    ExternInterrupt bouton;

    switch(routineSteps)
    {
        case RoutineSteps::START:
            //1.Light Amber
            while (true)
            {
            lm.setLight(Color::AMBER);

            if (bouton.getInterruptCount(Button::FIRST)>0)
            {
                bouton.getInterruptCount(Button::FIRST)=0;
                routineSteps = RoutineSteps::INT_CLICKED;
            }

            else if (bouton.getInterruptCount(Button::SECOND)>0)
            {
                bouton.getInterruptCount(Button::SECOND);
                routineSteps = RoutineSteps::WHITE_CLICKED;
            }
            }

        case RoutineSteps::INT_CLICKED:
            //orienté vers le haut
            lm.setLight(Color::GREEN);

        case RoutineSteps::WHITE_CLICKED:
            //orienté vers la droite
            lm.setLight(Color::RED);

        case RoutineSteps::FIND_STICK:
            //fonction de Gab
            break;

        case RoutineSteps::FOUND_STICK:
            //5. 3 sons aigus: son (300 ms), pause(300ms) 3x
            loopSound();
            //se dirige vers
            break;

        case RoutineSteps::WAIT:
            //6.clignoter led ambrée à 2Hz -> 2 tours par seconde
            flashAmber();
            //Jusqu'à temps qu'on pèse sur interrupt
            break;

        case RoutineSteps::NO_STICK:
            sonGrave(45); // hello frogini 10:0 AM
            flashRed();
            break;
    }
}