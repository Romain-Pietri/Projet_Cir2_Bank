# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/build"

# Include any dependencies generated for this target.
include CMakeFiles/Serveur.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Serveur.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Serveur.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Serveur.dir/flags.make

CMakeFiles/Serveur.dir/src/serveur.cpp.o: CMakeFiles/Serveur.dir/flags.make
CMakeFiles/Serveur.dir/src/serveur.cpp.o: /home/romain/Documents/Cours/CIR\ 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/src/serveur.cpp
CMakeFiles/Serveur.dir/src/serveur.cpp.o: CMakeFiles/Serveur.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Serveur.dir/src/serveur.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Serveur.dir/src/serveur.cpp.o -MF CMakeFiles/Serveur.dir/src/serveur.cpp.o.d -o CMakeFiles/Serveur.dir/src/serveur.cpp.o -c "/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/src/serveur.cpp"

CMakeFiles/Serveur.dir/src/serveur.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Serveur.dir/src/serveur.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/src/serveur.cpp" > CMakeFiles/Serveur.dir/src/serveur.cpp.i

CMakeFiles/Serveur.dir/src/serveur.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Serveur.dir/src/serveur.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/src/serveur.cpp" -o CMakeFiles/Serveur.dir/src/serveur.cpp.s

CMakeFiles/Serveur.dir/src/xml_parser.cpp.o: CMakeFiles/Serveur.dir/flags.make
CMakeFiles/Serveur.dir/src/xml_parser.cpp.o: /home/romain/Documents/Cours/CIR\ 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/src/xml_parser.cpp
CMakeFiles/Serveur.dir/src/xml_parser.cpp.o: CMakeFiles/Serveur.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Serveur.dir/src/xml_parser.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Serveur.dir/src/xml_parser.cpp.o -MF CMakeFiles/Serveur.dir/src/xml_parser.cpp.o.d -o CMakeFiles/Serveur.dir/src/xml_parser.cpp.o -c "/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/src/xml_parser.cpp"

CMakeFiles/Serveur.dir/src/xml_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Serveur.dir/src/xml_parser.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/src/xml_parser.cpp" > CMakeFiles/Serveur.dir/src/xml_parser.cpp.i

CMakeFiles/Serveur.dir/src/xml_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Serveur.dir/src/xml_parser.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/src/xml_parser.cpp" -o CMakeFiles/Serveur.dir/src/xml_parser.cpp.s

# Object files for target Serveur
Serveur_OBJECTS = \
"CMakeFiles/Serveur.dir/src/serveur.cpp.o" \
"CMakeFiles/Serveur.dir/src/xml_parser.cpp.o"

# External object files for target Serveur
Serveur_EXTERNAL_OBJECTS =

Serveur: CMakeFiles/Serveur.dir/src/serveur.cpp.o
Serveur: CMakeFiles/Serveur.dir/src/xml_parser.cpp.o
Serveur: CMakeFiles/Serveur.dir/build.make
Serveur: CMakeFiles/Serveur.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Serveur"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Serveur.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Serveur.dir/build: Serveur
.PHONY : CMakeFiles/Serveur.dir/build

CMakeFiles/Serveur.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Serveur.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Serveur.dir/clean

CMakeFiles/Serveur.dir/depend:
	cd "/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur" "/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur" "/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/build" "/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/build" "/home/romain/Documents/Cours/CIR 2/POO/projet/Projet_Cir2_Bank/Fichier_CMake_Serveur/build/CMakeFiles/Serveur.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Serveur.dir/depend

