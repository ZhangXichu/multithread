# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/xichuz/workspace/multithread

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xichuz/workspace/multithread/build

# Include any dependencies generated for this target.
include CMakeFiles/assignment2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/assignment2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/assignment2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/assignment2.dir/flags.make

CMakeFiles/assignment2.dir/assignment2.cpp.o: CMakeFiles/assignment2.dir/flags.make
CMakeFiles/assignment2.dir/assignment2.cpp.o: ../assignment2.cpp
CMakeFiles/assignment2.dir/assignment2.cpp.o: CMakeFiles/assignment2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xichuz/workspace/multithread/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/assignment2.dir/assignment2.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/assignment2.dir/assignment2.cpp.o -MF CMakeFiles/assignment2.dir/assignment2.cpp.o.d -o CMakeFiles/assignment2.dir/assignment2.cpp.o -c /home/xichuz/workspace/multithread/assignment2.cpp

CMakeFiles/assignment2.dir/assignment2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assignment2.dir/assignment2.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xichuz/workspace/multithread/assignment2.cpp > CMakeFiles/assignment2.dir/assignment2.cpp.i

CMakeFiles/assignment2.dir/assignment2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assignment2.dir/assignment2.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xichuz/workspace/multithread/assignment2.cpp -o CMakeFiles/assignment2.dir/assignment2.cpp.s

# Object files for target assignment2
assignment2_OBJECTS = \
"CMakeFiles/assignment2.dir/assignment2.cpp.o"

# External object files for target assignment2
assignment2_EXTERNAL_OBJECTS =

assignment2: CMakeFiles/assignment2.dir/assignment2.cpp.o
assignment2: CMakeFiles/assignment2.dir/build.make
assignment2: CMakeFiles/assignment2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xichuz/workspace/multithread/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable assignment2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/assignment2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/assignment2.dir/build: assignment2
.PHONY : CMakeFiles/assignment2.dir/build

CMakeFiles/assignment2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/assignment2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/assignment2.dir/clean

CMakeFiles/assignment2.dir/depend:
	cd /home/xichuz/workspace/multithread/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xichuz/workspace/multithread /home/xichuz/workspace/multithread /home/xichuz/workspace/multithread/build /home/xichuz/workspace/multithread/build /home/xichuz/workspace/multithread/build/CMakeFiles/assignment2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/assignment2.dir/depend
