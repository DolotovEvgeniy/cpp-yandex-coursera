# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dolotov-e/cpp-yandex-coursera

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dolotov-e/cpp-yandex-coursera/build

# Include any dependencies generated for this target.
include cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/depend.make

# Include the progress variables for this target.
include cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/progress.make

# Include the compile flags for this target's objects.
include cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/flags.make

cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/main.cpp.o: cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/flags.make
cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/main.cpp.o: ../cpp-yandex-04-brown/week_2/stats_aggregator/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dolotov-e/cpp-yandex-coursera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/main.cpp.o"
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/stats_aggregator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stats_aggregator.dir/main.cpp.o -c /home/dolotov-e/cpp-yandex-coursera/cpp-yandex-04-brown/week_2/stats_aggregator/main.cpp

cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stats_aggregator.dir/main.cpp.i"
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/stats_aggregator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dolotov-e/cpp-yandex-coursera/cpp-yandex-04-brown/week_2/stats_aggregator/main.cpp > CMakeFiles/stats_aggregator.dir/main.cpp.i

cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stats_aggregator.dir/main.cpp.s"
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/stats_aggregator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dolotov-e/cpp-yandex-coursera/cpp-yandex-04-brown/week_2/stats_aggregator/main.cpp -o CMakeFiles/stats_aggregator.dir/main.cpp.s

cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/stats_aggregator.cpp.o: cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/flags.make
cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/stats_aggregator.cpp.o: ../cpp-yandex-04-brown/week_2/stats_aggregator/stats_aggregator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dolotov-e/cpp-yandex-coursera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/stats_aggregator.cpp.o"
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/stats_aggregator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stats_aggregator.dir/stats_aggregator.cpp.o -c /home/dolotov-e/cpp-yandex-coursera/cpp-yandex-04-brown/week_2/stats_aggregator/stats_aggregator.cpp

cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/stats_aggregator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stats_aggregator.dir/stats_aggregator.cpp.i"
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/stats_aggregator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dolotov-e/cpp-yandex-coursera/cpp-yandex-04-brown/week_2/stats_aggregator/stats_aggregator.cpp > CMakeFiles/stats_aggregator.dir/stats_aggregator.cpp.i

cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/stats_aggregator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stats_aggregator.dir/stats_aggregator.cpp.s"
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/stats_aggregator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dolotov-e/cpp-yandex-coursera/cpp-yandex-04-brown/week_2/stats_aggregator/stats_aggregator.cpp -o CMakeFiles/stats_aggregator.dir/stats_aggregator.cpp.s

cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/stats_aggregator_test.cpp.o: cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/flags.make
cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/stats_aggregator_test.cpp.o: ../cpp-yandex-04-brown/week_2/stats_aggregator/stats_aggregator_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dolotov-e/cpp-yandex-coursera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/stats_aggregator_test.cpp.o"
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/stats_aggregator && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stats_aggregator.dir/stats_aggregator_test.cpp.o -c /home/dolotov-e/cpp-yandex-coursera/cpp-yandex-04-brown/week_2/stats_aggregator/stats_aggregator_test.cpp

cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/stats_aggregator_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stats_aggregator.dir/stats_aggregator_test.cpp.i"
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/stats_aggregator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dolotov-e/cpp-yandex-coursera/cpp-yandex-04-brown/week_2/stats_aggregator/stats_aggregator_test.cpp > CMakeFiles/stats_aggregator.dir/stats_aggregator_test.cpp.i

cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/stats_aggregator_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stats_aggregator.dir/stats_aggregator_test.cpp.s"
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/stats_aggregator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dolotov-e/cpp-yandex-coursera/cpp-yandex-04-brown/week_2/stats_aggregator/stats_aggregator_test.cpp -o CMakeFiles/stats_aggregator.dir/stats_aggregator_test.cpp.s

# Object files for target stats_aggregator
stats_aggregator_OBJECTS = \
"CMakeFiles/stats_aggregator.dir/main.cpp.o" \
"CMakeFiles/stats_aggregator.dir/stats_aggregator.cpp.o" \
"CMakeFiles/stats_aggregator.dir/stats_aggregator_test.cpp.o"

# External object files for target stats_aggregator
stats_aggregator_EXTERNAL_OBJECTS =

cpp-yandex-04-brown/week_2/bin/stats_aggregator: cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/main.cpp.o
cpp-yandex-04-brown/week_2/bin/stats_aggregator: cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/stats_aggregator.cpp.o
cpp-yandex-04-brown/week_2/bin/stats_aggregator: cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/stats_aggregator_test.cpp.o
cpp-yandex-04-brown/week_2/bin/stats_aggregator: cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/build.make
cpp-yandex-04-brown/week_2/bin/stats_aggregator: cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dolotov-e/cpp-yandex-coursera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../bin/stats_aggregator"
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/stats_aggregator && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stats_aggregator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/build: cpp-yandex-04-brown/week_2/bin/stats_aggregator

.PHONY : cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/build

cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/clean:
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/stats_aggregator && $(CMAKE_COMMAND) -P CMakeFiles/stats_aggregator.dir/cmake_clean.cmake
.PHONY : cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/clean

cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/depend:
	cd /home/dolotov-e/cpp-yandex-coursera/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dolotov-e/cpp-yandex-coursera /home/dolotov-e/cpp-yandex-coursera/cpp-yandex-04-brown/week_2/stats_aggregator /home/dolotov-e/cpp-yandex-coursera/build /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/stats_aggregator /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cpp-yandex-04-brown/week_2/stats_aggregator/CMakeFiles/stats_aggregator.dir/depend

