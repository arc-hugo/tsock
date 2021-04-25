#ifndef MESSAGE_H
#define MESSAGE_H

#include "params.h"

// Affiche un message d'erreur lorsqu'un argument nécessaire est manquant
void error();
// Construit le message entier envoyé par la source
void construire_message(char* message, int taille, char motif, int num);
// Affiche le message reçu par le puits ou envoyé par la source
void afficher_message(char* message, int taille, Parametre params, int num);

#endif
