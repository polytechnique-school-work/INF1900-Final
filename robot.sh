#!/bin/bash

if [ "$1" = "debug" ]; then
    echo "Exécution du script en mode débugage."
    cd library
    make build
    cd ../project
    make debug
elif [ "$1" = "install" ]; then
    echo "Exécution du script en mode installation."
    cd library
    make build
    cd ../project
    make install
elif [ "$1" = "music" ]; then
    cd music
    if [ ! $2 ]; then
        echo -e "\e[31mVous devez ajouter un argument (le nom du fichier dans le dossier music).\e[0m"
    elif [[ ! -e "$2.txt" ]]; then
        echo -e "\e[31mLe fichier $2.txt n'existe pas dans le dossier "music".\e[0m"
    else
        progmem -o "$2.ignore" "$2.txt"
        if [ $? -ne 0 ]; then
            echo -e "\e[31mUne erreur est survenue lors de l'exécution de progmem, code d'erreur: $?\e[0m"
            exit 1
        fi
        cd ../writer
        make install
        if [ $? -ne 0 ]; then
            echo -e "\e[31mUne erreur est survenue lors de l'exécution de make, code d'erreur: $?\e[0m"
            exit 1
        fi
        cd ../music
        serieViaUSB -e -f "$2.ignore"
        if [ $? -ne 0 ]; then
            echo -e "\e[31mUne erreur est survenue lors de l'exécution de serieViaUSB, code d'erreur: $?\e[0m"
            exit 1
        fi
        echo -e "\e[32mToutes les commandes ont été exécuté avec succès.\e[0m"
    fi
elif [ "$1" = "clean" ]; then
    cd library
    make clean
    cd ../project
    make clean
    cd ../music
    # Suppression des fichiers de musique générés.
    find . \( -name '*.ignore' \) -type f -delete
    echo -e "\e[32mSuppression de l'ensemble des fichiers inutiles.\e[0m"
else 
    echo -e "\e[31mArgument invalide : voici les commandes accessibles.\e[0m"
    echo -e "\e[32m'debug' \e[0m\e[33mpermet de lancer le mode de débugage\e[0m"
    echo -e "\e[37m(Exécute en débugage la compilation et lance serieViaUSB)\e[0m"
    echo ""
    echo -e "\e[32m'install' \e[0m\e[33mpermet de lancer le mode d'installation\e[0m"
    echo -e "\e[37m(Compilation du projet et installation avec le port USB)\e[0m"
    echo ""
    echo -e "\e[32m'music' <file> \e[0m\e[33mpermet d'écrire en mémoire externe\e[0m"
    echo -e "\e[37m(Fait le chemin du .txt jusqu'à l'écriture ⚠️: file sans extension)\e[0m"
    echo ""
    echo -e "\e[32m'clean' \e[0m\e[33mgrand nettoyage!\e[0m"
    echo -e "\e[37m(Retire l'ensemble des fichiers inutiles du projet)\e[0m"
    exit 1
fi

