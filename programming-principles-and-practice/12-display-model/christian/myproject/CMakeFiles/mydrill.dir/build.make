# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/christian/ProjektePrivat/CppLerngruppe/Kapitel12/drill1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/christian/ProjektePrivat/CppLerngruppe/Kapitel12/drill1

# Include any dependencies generated for this target.
include CMakeFiles/mydrill.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mydrill.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mydrill.dir/flags.make

CMakeFiles/mydrill.dir/firstexample.cpp.o: CMakeFiles/mydrill.dir/flags.make
CMakeFiles/mydrill.dir/firstexample.cpp.o: firstexample.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/christian/ProjektePrivat/CppLerngruppe/Kapitel12/drill1/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/mydrill.dir/firstexample.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mydrill.dir/firstexample.cpp.o -c /home/christian/ProjektePrivat/CppLerngruppe/Kapitel12/drill1/firstexample.cpp

CMakeFiles/mydrill.dir/firstexample.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mydrill.dir/firstexample.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/christian/ProjektePrivat/CppLerngruppe/Kapitel12/drill1/firstexample.cpp > CMakeFiles/mydrill.dir/firstexample.cpp.i

CMakeFiles/mydrill.dir/firstexample.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mydrill.dir/firstexample.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/christian/ProjektePrivat/CppLerngruppe/Kapitel12/drill1/firstexample.cpp -o CMakeFiles/mydrill.dir/firstexample.cpp.s

CMakeFiles/mydrill.dir/firstexample.cpp.o.requires:
.PHONY : CMakeFiles/mydrill.dir/firstexample.cpp.o.requires

CMakeFiles/mydrill.dir/firstexample.cpp.o.provides: CMakeFiles/mydrill.dir/firstexample.cpp.o.requires
	$(MAKE) -f CMakeFiles/mydrill.dir/build.make CMakeFiles/mydrill.dir/firstexample.cpp.o.provides.build
.PHONY : CMakeFiles/mydrill.dir/firstexample.cpp.o.provides

CMakeFiles/mydrill.dir/firstexample.cpp.o.provides.build: CMakeFiles/mydrill.dir/firstexample.cpp.o

# Object files for target mydrill
mydrill_OBJECTS = \
"CMakeFiles/mydrill.dir/firstexample.cpp.o"

# External object files for target mydrill
mydrill_EXTERNAL_OBJECTS =

mydrill: CMakeFiles/mydrill.dir/firstexample.cpp.o
mydrill: CMakeFiles/mydrill.dir/build.make
mydrill: CMakeFiles/mydrill.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable mydrill"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mydrill.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mydrill.dir/build: mydrill
.PHONY : CMakeFiles/mydrill.dir/build

CMakeFiles/mydrill.dir/requires: CMakeFiles/mydrill.dir/firstexample.cpp.o.requires
.PHONY : CMakeFiles/mydrill.dir/requires

CMakeFiles/mydrill.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mydrill.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mydrill.dir/clean

CMakeFiles/mydrill.dir/depend:
	cd /home/christian/ProjektePrivat/CppLerngruppe/Kapitel12/drill1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/christian/ProjektePrivat/CppLerngruppe/Kapitel12/drill1 /home/christian/ProjektePrivat/CppLerngruppe/Kapitel12/drill1 /home/christian/ProjektePrivat/CppLerngruppe/Kapitel12/drill1 /home/christian/ProjektePrivat/CppLerngruppe/Kapitel12/drill1 /home/christian/ProjektePrivat/CppLerngruppe/Kapitel12/drill1/CMakeFiles/mydrill.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mydrill.dir/depend

