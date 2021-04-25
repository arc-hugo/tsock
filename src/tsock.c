/* libraire standard */
#include <stdlib.h>
/* entrées/sorties */
#include <stdio.h>
/* constantes et structures propres au domaine INTERNET */
#include <netinet/in.h>

#include <utils/message.h>
#include <utils/params.h>
#include <reseau/source.h>
#include <reseau/puits.h>

int main (int argc, char **argv) {
   Parametre params;
   /* Port choisi */
   int port;

   int ret = get_params(&params, argc, argv);
   /* Gestion des arguments commençant par un - */
   if ((params.mode == SOURCE_PUITS && params.source_puits != SOURCE && params.source_puits != PUITS) ||
      (params.mode == CLIENT_SERVEUR && params.client_serveur != CLIENT && params.client_serveur != SERVEUR) ||
      ret != 0) {
      error();
   }

   /* Récupération du numéro de port */
   port = atoi(argv[argc-1]);
   port = htons(port);

   if (params.mode == SOURCE_PUITS && params.source_puits == SOURCE)
      ret = source(params, argv[argc-2], port);
   else if (params.mode == SOURCE_PUITS && params.source_puits == PUITS)
      ret = puits(params, port);

   return 0;
}
