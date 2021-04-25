/* libraire standard */
#include <stdlib.h>
/* entrées/sorties */
#include <stdio.h>
/* constantes et structures propres au domaine UNIX */
#include <sys/un.h>
/* constantes et structures propres au domaine INTERNET */
#include <netinet/in.h>
/* gestion des erreurs */
#include <errno.h>
/* memset et memcpy */
#include <string.h>

#include <utils/message.h>
#include <reseau/socket.h>
#include <reseau/source.h>

int source (Parametre params, char* host, int port) {
   /* Socket (et socket local) attribué par l'API*/
   int sock;
   /* Adresse du programme destinataire */
   struct sockaddr_in adr;
   /* Adresse de l'hôte destiataire */
   struct hostent * hp;
   /* Adresse de stockage des messages */
   char * message;

   /* Attribution de mémoire à la structure d'adresse internet */
   memset((char*)&adr, 0, sizeof(adr));
   /* Configuration de l'adresse internet */
   adr.sin_family = AF_INET;
   adr.sin_port = port;

   /* Construction du socket */
   sock = sock_init(params.protocole);

   /* Configuration de l'adresse du destinataire */
   set_source(&hp, &adr, host, params.protocole, sock);

   /* Attribution mémoire au message à transmettre/réceptionner */
   if (params.taille == NOT_SET)
      params.taille = 30;
   message = malloc(params.taille*sizeof(char));

   /* Affichage les informations d'envoi/réception */
   if (params.nb_message == NOT_SET)
      params.nb_message = 10;
   printf("SOURCE: lg_mesg_emis=%d, port=%d, nb_envois=%d", params.taille,port, params.nb_message);
   if (params.protocole == UDP)
      printf(", TP=udp, dest=%s\n",host);
   else
      printf(", TP=tcp, dest=%s\n",host);
   printf("SOURCE: socket\n");

   /* On génére les X messages selon leur numéro d'envoie */
   char motif = 'a';
   for (int i = 1; i < params.nb_message+1; i++){
      construire_message(message, params.taille, motif, i);
      if (motif == 'z')
         motif = 'a';
      else
         motif++;
      /* Utilisation de sendto() si UDP ou send() si TCP */
      if (params.protocole == 1){
         if (sendto(sock, message, params.taille, 0,(struct sockaddr *) &adr, sizeof(adr)) < 0) {
            char * err = malloc(100*sizeof(char));
            sprintf(err, "erreur sendto() (n°%d)", i);
            perror(err);
            exit(errno);
         }
         afficher_message(message, params.taille, params, i);
      } else {
         if ((send(sock, message, params.taille, 0)) < 0) {
            char * err = malloc(100*sizeof(char));
            sprintf(err, "erreur send() (n°%d)", i);
            perror(err);
            exit(errno);
         }
         afficher_message(message, params.taille, params, i);
      }
   }
   /* Si on utilise TCP, un éteint la connexion après la fin de nos envois */
   if (params.protocole == 0) {
      if (shutdown(sock, 1) == -1){
         perror("erreur shutdown()");
         exit(errno);
      }
   }
   printf("SOURCE: fin\n");
   return 0;
}

