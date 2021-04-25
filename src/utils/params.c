#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include <utils/params.h>
#include <utils/message.h>

int get_params(Parametre *params, int argc, char **argv) {
   int c;
   params->mode = SOURCE_PUITS;
   params->protocole = TCP;
   params->client_serveur = NOT_SET;
   params->source_puits = NOT_SET;
   params->nb_message = NOT_SET;
   params->taille = NOT_SET;

   while ((c = getopt(argc, argv, "creupn:l:s")) != -1) {
      switch (c) {
         case 'c':
            params->mode = CLIENT_SERVEUR;
            break;
         case 'r':
            if (params->client_serveur == SERVEUR)
               error();
            params->client_serveur = CLIENT;
            break;
         case 'e':
            if (params->client_serveur == CLIENT)
               error();
            params->client_serveur = SERVEUR;
            break;
         case 'u':
            params->protocole = UDP;
            break;
         case 'p':
            if (params->source_puits == SOURCE)
               error();
            params->source_puits = PUITS;
            break;
         case 's':
            if (params->source_puits == PUITS)
               error();
            params->source_puits = SOURCE;
            break;
         case 'n':
            params->nb_message = atoi(optarg);
            break;
         case 'l':
            if (atoi(optarg) < 6) {
               printf("La longueur des messages doit être au moins de 6 caractères\n");
               return 1;
            }
            params->taille = atoi(optarg);
            break;
         default:
            error();
      }
   }

   return 0;
}
