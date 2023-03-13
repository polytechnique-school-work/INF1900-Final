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
elif [ "$1" = "clean" ]; then
    cd library
    make clean
    cd ../project
    make clean
    echo -e "\e[32mSuppression de l'ensemble des fichiers inutiles.\e[0m"
else 
    echo -e "\e[31mArgument invalide : utilisez 'debug', 'install' ou 'clean'.\e[0m"
    exit 1
fi

