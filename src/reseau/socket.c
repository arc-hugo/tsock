/* libraire standard */
#include <stdlib.h>
/* entrées/sorties */
#include <stdio.h>
/* constantes relatives aux domaines, types et protocoles */
#include <sys/socket.h>
/* memset et memcpy */
#include <string.h>
/* errno */
#include <errno.h>

#include <reseau/socket.h>

// Initialise le socket Transport selon le protocole choisi
int sock_init (int protocole) {
   int sock;
   // Configuration selon UDP
   if (protocole == 1){
      if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
         perror("échec de création du socket");
         exit(errno);
      }
      // Configuration selon TCP
   } else {
      if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
         perror("échec de création du socket");
         exit(errno);
      }
   }
   return sock;
}

// Configure la source selon l'adresse de l'hôte destinataire
void set_source (struct hostent ** hp, struct sockaddr_in * adr, char * host, int protocole, int sock) {
   if ((*hp = gethostbyname(host)) == NULL){
      perror("erreur gethostbyname()");
      exit(errno);
   }
   memcpy((char*)&(adr->sin_addr.s_addr), (*hp)->h_addr_list[0], (*hp)->h_length);
   // Configuration supplémentaire si l'on utilise TCP
   if (protocole == 0){
      if (connect(sock, (struct sockaddr *) adr, sizeof(*adr)) == -1){
         perror("erreur connect()");
         exit(errno);
      }
   }
}

// Configure le puits selon le socket Transport
void set_puits (struct sockaddr_in * adr, int sock, struct sockaddr_in * adr_em, int * plg_adr, int protocole){
   adr->sin_addr.s_addr = INADDR_ANY;
   if(bind(sock, (struct sockaddr *) adr, sizeof(*adr)) == -1){
      perror("erreur bind()");
      exit(errno);
   }
   if (getsockname(sock, (struct sockaddr *) adr_em, (socklen_t *) plg_adr) == -1) {
      perror("erreur getsockname()");
      exit(errno);
   }
   if (protocole == 0) {
      if (listen(sock, 1) == -1){
         perror("erreur listen()");
         exit(errno);
      }
   }
}
