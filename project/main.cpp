#include <Timer/TimerManager.hpp>
#include <Logger/Logger.hpp>

int main() {
    // Permet de générer un timer de 0.1 * 50 secondes (donc 5 secondes).
    TimerManager::runTimer(50);

    Logger::init();
    while(true) {
    // On regarde si le timer est terminé ET si la vérification
    // a déjà été effectuée (pour éviter de log plusieurs fois).
    if(TimerManager::isDone() && !TimerManager::isChecked()) {
        Logger::log(Priority::INFO,"Le timer est terminé.");
    }
   }
}