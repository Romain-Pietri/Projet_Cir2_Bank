cmake_minimum_required(VERSION 3.10)

project(Serveur)

# Ajout de la bibliothèque Boost
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Ajout de la bibliothèque SFML
find_package(SFML 2.5 REQUIRED graphics window system)
include_directories(${SFML_INCLUDE_DIR})

# Ajout de la bibliothèque RapidXml
include_directories(RapidXml)

# Ajout des fichiers sources
set(SOURCES
    src/serveur.cpp
    src/xml_parser.cpp
)

# Déclaration de l'exécutable Serveur
add_executable(Serveur ${SOURCES})

# Liaison des bibliothèques au projet Serveur
target_link_libraries(Serveur ${Boost_LIBRARIES} ${SFML_LIBRARIES})
