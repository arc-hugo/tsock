# tsock
## Description
Mini projet d'application CLI de transmission de messages par protocole de transmission TCP/UDP en C.  
Le programme une fois lancé peut adopter deux comportement :
- **SOURCE**: envoi des données par TCP/UDP à un puits désigné.
- **PUITS**: reçoit les données par TCP/UDP d'une source.

## Installation
### Prérequis
- Système d'exploitation UNIX
- Compilateur GCC
- CMake version >= 3.0

### Procédure
Lancer les commandes suivante sur votre terminal  
```bash
git clone https://github.com/arc-hugo/tsock
cd tsock
mkdir build && cd build/
cmake ..
make install
```

## Utilisation
### Mode SOURCE
Pour utiliser le mode SOURCE, le programme doit être lancé de cette façon :
````bash
tsock -s [-options] hôte port
````
### Mode PUITS
Pour utiliser le mode PUITS, le programme doit être lancé de cette façon :
````bash
tsock -p [-options] port
````

### Options
Dans chaque mode, il est possible d'ajouter des options :
- `-u` permet d'utiliser le protocole UDP plutôt que TCP.
- `-n ##` permet d'indiquer un nombre de messages à transmettre (par défaut 10 pour la source et infini pour le puits).
- `-l ##` permet d'indiquer un nombre de caractères à envoyer par message aavec un minimum de 6 (30 par défaut).
