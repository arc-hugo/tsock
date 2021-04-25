# Version requise de CMake
cmake_minimum_required(VERSION 3.0)
# Nom de projet
project(tsock)

# Ajout des sous-dossiers
add_subdirectory(utils)
add_subdirectory(reseau)

# Ajout des fichiers sources
set(SRC tsock.c)

# Commandes d'installation
add_executable(tsock ${SRC})
target_link_libraries(tsock utils reseau)
install(TARGETS tsock DESTINATION ${TSOCK_INSTALL_BIN_DIR})
