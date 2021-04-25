# Version requise de CMake
cmake_minimum_required(VERSION 3.0)

# Nom de projet
project(tsock)

# Paramètres
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Dossier d'installation (racine)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

# Chemin d'installation des fichiers utilitaires
set(TSOCK_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(TSOCK_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(TSOCK_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

# Ajout des dossier d'inclusion
include_directories(${TSOCK_INSTALL_INCLUDE_DIR})

# Ajout du sous-dossier sources
add_subdirectory(src)
