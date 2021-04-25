# Version requise de CMake
cmake_minimum_required(VERSION 3.0)
# Nom de projet
project(reseau)

# Ajout des fichiers sources
set(SRC
   socket.c
   source.c
   puits.c
   client.c
   serveur.c
)

# Ajout de la librairie
add_library(reseau ${SRC})

# Installation dans lib et include
install(TARGETS reseau DESTINATION ${TSOCK_INSTALL_LIB_DIR})
