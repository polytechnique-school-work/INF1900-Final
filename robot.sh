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
    echo -e "\e[32mSuppression de l'ensemble des fichiers inutiles.\e[0m"
else 
    echo -e "\e[31mArgument invalide : utilisez 'debug', 'install', 'music' ou 'clean'.\e[0m"
    exit 1
fi

