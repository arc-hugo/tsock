/* libraire standard */
#include <stdlib.h>
/* entrées/sorties */
#include <stdio.h>
/* gestion des erreurs */
#include <errno.h>
/* memset et memcpy */
#include <string.h>

#include <utils/message.h>
#include <reseau/socket.h>
#include <reseau/puits.h>

int puits(Parametre params, int port) {
   /* Socket (et socket local) attribué par l'API*/
   int sock, local_sock;
   /* Adresse du programme destinataire */
   struct sockaddr_in adr, adr_em;
   /* Plage de l'adresse de l'emetteur (TCP) */
   int plg_adr;

   /* Adresse de stockage des messages */
   char * message;
   /* Taille réelle des messages */
   int mtaille;

   /* Attribution de mémoire à la structure d'adresse internet */
   memset((char*)&adr, 0, sizeof(adr));
   /* Configuration de l'adresse internet */
   adr.sin_family = AF_INET;
   adr.sin_port = port;

   /* Construction du socket */
   sock = sock_init(params.protocole);

   /* Configuration de l'adresse selon si notre programme est un puits ou une source */
   set_puits(&adr, sock, &adr_em, &plg_adr, params.protocole);

   /* Attribution mémoire au message à transmettre/réceptionner */
   if (params.taille == NOT_SET)
      params.taille = 30;
   message = malloc(params.taille*sizeof(char));

   /* Affichage les informations d'envoi/réception */
   printf("PUITS: lg_mesg_lu=%d, port=%d", params.taille, port);
   if (params.nb_message == NOT_SET)
      printf(", nb_receptions=infini");
   else
      printf(", nb_receptions=%d",params.nb_message);
   if (params.protocole == 1)
      printf(", TP=udp\n");
   else
      printf(", TP=tcp\n");
   printf("PUITS: socket\n");

   /* Il utilise UDP */
   if (params.protocole == UDP){
      if (params.nb_message == NOT_SET){
         /* Si le nombre de messsage est infini, on les réceptionne jusqu'à l'interruption du programme */
         int i = 1;
         while(1) {
            if ((mtaille = recvfrom(sock, message, params.taille, 0, NULL, NULL)) != -1)
               afficher_message(message, mtaille, params, i);
            else {
               perror("erreur recvfrom()");
               exit(errno);
            }
            i++;
         }
         /* Sinon on réceptionne le nombre défini par l'utilisateur */
      } else {
         for(int i = 0; i < params.nb_message; i++)
            if ((mtaille = recvfrom(sock, message, params.taille, 0, NULL, NULL)) != -1)
               afficher_message(message, mtaille, params, i+1);
            else {
               perror("erreur recvfrom()");
               exit(errno);
            }
      }
      /* Sinon il utilise TCP */
   } else {
      /* On construit le socket local de la connexion reçue */
      if ((local_sock = accept(sock, (struct sockaddr *) &adr_em, (socklen_t *) &plg_adr)) == -1){
         perror("erreur accept()");
         exit(errno);
      }
      /* Si le nombre de messages est infini, les réception jusqu'à l'interruption de la source */
      if (params.nb_message == -1) {
         int i = 1;
         while ((mtaille = recv(local_sock, message, params.taille, 0)) > 0) {
            afficher_message(message, mtaille, params, i);
            i++;
         }
         if (mtaille == -1) {
            perror("erreur recv()");
            exit(errno);
         }
         /* Sinon on réceptionne le nombre prédéfini et l'on interrompt la connexion */
      } else {
         for(int i = 0; i < params.nb_message; i++)
            if ((mtaille = recv(local_sock, message, params.taille, 0)) > 0)
               afficher_message(message, mtaille, params, i+1);
            else if (mtaille == -1) {
               perror("erreur recv()");
               exit(errno);
            }
      }
      /* Fermeture de la connexion du socket local */
      if (shutdown(local_sock, 0) == -1){
         perror("erreur shutdown()");
         exit(errno);
      }
   }
   printf("PUITS: fin\n");

   return 0;
}
