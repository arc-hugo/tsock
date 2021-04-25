#ifndef SOCKET_H
#define SOCKET_H

/* structures retournées par les fonctions de gestion de la base de données du réseau */
#include <netdb.h>

int sock_init(int protocole);
void set_source (struct hostent ** hp, struct sockaddr_in * adr, char * host, int protocole, int sock);
void set_puits (struct sockaddr_in * adr, int sock, struct sockaddr_in * adr_em, int * plg_adr, int protocole);

#endif
