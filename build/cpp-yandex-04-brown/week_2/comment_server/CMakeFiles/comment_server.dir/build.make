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
include cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/depend.make

# Include the progress variables for this target.
include cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/progress.make

# Include the compile flags for this target's objects.
include cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/flags.make

cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/comment_server.cpp.o: cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/flags.make
cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/comment_server.cpp.o: ../cpp-yandex-04-brown/week_2/comment_server/comment_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dolotov-e/cpp-yandex-coursera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/comment_server.cpp.o"
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/comment_server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/comment_server.dir/comment_server.cpp.o -c /home/dolotov-e/cpp-yandex-coursera/cpp-yandex-04-brown/week_2/comment_server/comment_server.cpp

cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/comment_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/comment_server.dir/comment_server.cpp.i"
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/comment_server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dolotov-e/cpp-yandex-coursera/cpp-yandex-04-brown/week_2/comment_server/comment_server.cpp > CMakeFiles/comment_server.dir/comment_server.cpp.i

cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/comment_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/comment_server.dir/comment_server.cpp.s"
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/comment_server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dolotov-e/cpp-yandex-coursera/cpp-yandex-04-brown/week_2/comment_server/comment_server.cpp -o CMakeFiles/comment_server.dir/comment_server.cpp.s

# Object files for target comment_server
comment_server_OBJECTS = \
"CMakeFiles/comment_server.dir/comment_server.cpp.o"

# External object files for target comment_server
comment_server_EXTERNAL_OBJECTS =

cpp-yandex-04-brown/week_2/bin/comment_server: cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/comment_server.cpp.o
cpp-yandex-04-brown/week_2/bin/comment_server: cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/build.make
cpp-yandex-04-brown/week_2/bin/comment_server: cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dolotov-e/cpp-yandex-coursera/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/comment_server"
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/comment_server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/comment_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/build: cpp-yandex-04-brown/week_2/bin/comment_server

.PHONY : cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/build

cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/clean:
	cd /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/comment_server && $(CMAKE_COMMAND) -P CMakeFiles/comment_server.dir/cmake_clean.cmake
.PHONY : cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/clean

cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/depend:
	cd /home/dolotov-e/cpp-yandex-coursera/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dolotov-e/cpp-yandex-coursera /home/dolotov-e/cpp-yandex-coursera/cpp-yandex-04-brown/week_2/comment_server /home/dolotov-e/cpp-yandex-coursera/build /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/comment_server /home/dolotov-e/cpp-yandex-coursera/build/cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cpp-yandex-04-brown/week_2/comment_server/CMakeFiles/comment_server.dir/depend

