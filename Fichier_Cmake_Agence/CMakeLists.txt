cmake_minimum_required(VERSION 3.10)

project(Agence)

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
    src/moteur.cpp
    src/xml_parser.cpp
    src/client.cpp
    src/main.cpp
)

# Déclaration de l'exécutable Agence
add_executable(Agence ${SOURCES})

# Liaison des bibliothèques au projet Agence
target_link_libraries(Agence ${Boost_LIBRARIES} ${SFML_LIBRARIES})
