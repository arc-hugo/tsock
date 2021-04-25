#include <stdlib.h>
#include <stdio.h>

#include <utils/message.h>

void error (){
   printf("usage: cmd  [-c -e|-c -r][-p|-s][-n ##]\n");
   exit(1);
}

// Construit une chaine de caractères en répétant un même motif sur une certaine longueur
void construire_sous_message (char * message, char motif, int taille){
   for (int i = 0; i < taille; i++)
      *(message+i) = motif;
}

void construire_message (char * message, int taille, char motif, int num) {
   sprintf(message, "%5d", num);
   construire_sous_message(message+5, motif, taille-5);
}

void afficher_message (char * message, int taille, Parametre params, int num){
   if (params.mode == SOURCE_PUITS) {
      if (params.source_puits == SOURCE) {
         printf("SOURCE: Envoi n°%d (%d) [", num, taille);
      } else {
         printf("PUITS: Réception n°%d (%d) [", num, taille);
      }
   } else {
      if (params.client_serveur == CLIENT) {
         printf("CLIENT: Réception n°%d (%d) [", num, taille);
      } else {
         printf("SERVEUR: Envoi n°%d (%d) [", num, taille);
      }
   }
   for(int i = 0; i < taille; i++)
      printf("%c",message[i]);
   printf("]\n");
}
