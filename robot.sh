#!/bin/bash

echo $1
if [$1 = "debug"]; then
    echo "Exécution du script en mode débugage"
    cd library
    make build
    cd ../project
    make debug
elif [$1 = "clean"]; then
    cd library
    make clean
    cd ../project
    make clean
    echo "Suppression de l'ensemble des fichiers inutiles"
else 
    echo "Argument invalide : utilisez 'debug' ou 'clean'"
    exit 1
fi

