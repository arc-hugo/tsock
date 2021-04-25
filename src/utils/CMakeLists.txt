# Version requise de CMake
cmake_minimum_required(VERSION 3.0)
# Nom de projet
project(utils)

# Ajout des fichiers sources
set(SRC
   message.c
   params.c
)

# Ajout de la librairie
add_library(utils ${SRC})

# Installation dans lib et include
install(TARGETS utils DESTINATION ${TSOCK_INSTALL_LIB_DIR})
