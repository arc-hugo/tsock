#ifndef PARAMS_H
#define PARAMS_H

#define NOT_SET -1
#define SOURCE_PUITS 0
#define CLIENT_SERVEUR 1
#define TCP 0
#define UDP 1
#define SOURCE 0
#define PUITS 1
#define CLIENT 0
#define SERVEUR 1

typedef struct Parametre {
   short mode;
   short protocole;
   short source_puits;
   short client_serveur;
   int nb_message;
   int taille;
} Parametre;

int get_params(Parametre* params, int argc, char** argv);

#endif
