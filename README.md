# Projet de robotique INF1900

## Attention
Le programme serieViaUSB doit être installé à l'emplacement `/usr/bin` pour que l'exécution se fasse sans problèmes.

## Fonctionnement

Plusieurs commandes sont disponibles pour simplifier l'utilisation.

### 🐧 Install
Permet de compiler la librairie et le projet de façon propre. Ensuite, installe le programme dans le robot.
```sh
./robot.sh install
```

### 🐞 Debug
Permet de compiler la librairie et le projet de façon propre. Ensuite, installe le programme dans le robot. 
Finalement, démarre le programme `serieViaUSB` pour ainsi recevoir les informations provenant du robot.
```sh
./robot.sh debug
```

### 🧽 Clean
Permet de retirer tous les fichiers inutiles présents dans la librairie ET dans le projet.
```sh
./robot.sh clean
```

## Les différents modules

### 🚨 ExternInterrupt

```
Module permettant de gérer des intéruptions externes.
```
Documentation : [Cliquez](/library/ExternInterrupt/README.md)

### 💡 Light

```
Module permettant de gérer les lumières.
```
Documentation : [Cliquez](/library/Light/README.md)
### 🗒️ Logger

```
Module permettant d'écrire simplement des logs dans le programme. 
Elles seront envoyés à l'ordinateur à l'aide du programme serieViaUSB
```
Documentation : [Cliquez](/library/Logger/README.md)
### 📝 Memory

```
Module permettant de gérer l'écriture et la lecture en mémoire.
```
Documentation : [Cliquez](/library/Memory/README.md)
### 📡 PWM

```
Module permettant de générer un signal de PWM.
```
Documentation : [Cliquez](/library/PWM/README.md)
### ⏰ Timer

```
Module permettant de gérer des timers.
```
Documentation : [Cliquez](/library/Timer/README.md)
### ⚙️ Wheel

```
Module permettant de gérer les roues du robot.
```
Documentation : [Cliquez](/library/Wheel/README.md)

### 🥫 Can

```
Module permettant de convertir des données analogiques en données numériques.
```
Documentation : [Cliquez](/library/Can/README.md)
