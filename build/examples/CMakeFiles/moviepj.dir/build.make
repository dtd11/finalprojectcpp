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
CMAKE_SOURCE_DIR = /home/asdf/openai-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/asdf/openai-cpp/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/moviepj.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/CMakeFiles/moviepj.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/moviepj.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/moviepj.dir/flags.make

examples/CMakeFiles/moviepj.dir/moviepj.cpp.o: examples/CMakeFiles/moviepj.dir/flags.make
examples/CMakeFiles/moviepj.dir/moviepj.cpp.o: ../examples/moviepj.cpp
examples/CMakeFiles/moviepj.dir/moviepj.cpp.o: examples/CMakeFiles/moviepj.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/asdf/openai-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/moviepj.dir/moviepj.cpp.o"
	cd /home/asdf/openai-cpp/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/CMakeFiles/moviepj.dir/moviepj.cpp.o -MF CMakeFiles/moviepj.dir/moviepj.cpp.o.d -o CMakeFiles/moviepj.dir/moviepj.cpp.o -c /home/asdf/openai-cpp/examples/moviepj.cpp

examples/CMakeFiles/moviepj.dir/moviepj.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/moviepj.dir/moviepj.cpp.i"
	cd /home/asdf/openai-cpp/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/asdf/openai-cpp/examples/moviepj.cpp > CMakeFiles/moviepj.dir/moviepj.cpp.i

examples/CMakeFiles/moviepj.dir/moviepj.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/moviepj.dir/moviepj.cpp.s"
	cd /home/asdf/openai-cpp/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/asdf/openai-cpp/examples/moviepj.cpp -o CMakeFiles/moviepj.dir/moviepj.cpp.s

# Object files for target moviepj
moviepj_OBJECTS = \
"CMakeFiles/moviepj.dir/moviepj.cpp.o"

# External object files for target moviepj
moviepj_EXTERNAL_OBJECTS =

examples/moviepj: examples/CMakeFiles/moviepj.dir/moviepj.cpp.o
examples/moviepj: examples/CMakeFiles/moviepj.dir/build.make
examples/moviepj: /usr/lib/x86_64-linux-gnu/libcurl.so
examples/moviepj: examples/CMakeFiles/moviepj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/asdf/openai-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable moviepj"
	cd /home/asdf/openai-cpp/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/moviepj.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/moviepj.dir/build: examples/moviepj
.PHONY : examples/CMakeFiles/moviepj.dir/build

examples/CMakeFiles/moviepj.dir/clean:
	cd /home/asdf/openai-cpp/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/moviepj.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/moviepj.dir/clean

examples/CMakeFiles/moviepj.dir/depend:
	cd /home/asdf/openai-cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/asdf/openai-cpp /home/asdf/openai-cpp/examples /home/asdf/openai-cpp/build /home/asdf/openai-cpp/build/examples /home/asdf/openai-cpp/build/examples/CMakeFiles/moviepj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/moviepj.dir/depend

