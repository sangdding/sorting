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
CMAKE_SOURCE_DIR = /root/lsm/sorting

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/lsm/sorting

# Include any dependencies generated for this target.
include CMakeFiles/DataSize.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DataSize.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DataSize.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DataSize.dir/flags.make

CMakeFiles/DataSize.dir/dataSize.cpp.o: CMakeFiles/DataSize.dir/flags.make
CMakeFiles/DataSize.dir/dataSize.cpp.o: dataSize.cpp
CMakeFiles/DataSize.dir/dataSize.cpp.o: CMakeFiles/DataSize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/lsm/sorting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DataSize.dir/dataSize.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DataSize.dir/dataSize.cpp.o -MF CMakeFiles/DataSize.dir/dataSize.cpp.o.d -o CMakeFiles/DataSize.dir/dataSize.cpp.o -c /root/lsm/sorting/dataSize.cpp

CMakeFiles/DataSize.dir/dataSize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DataSize.dir/dataSize.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/lsm/sorting/dataSize.cpp > CMakeFiles/DataSize.dir/dataSize.cpp.i

CMakeFiles/DataSize.dir/dataSize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DataSize.dir/dataSize.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/lsm/sorting/dataSize.cpp -o CMakeFiles/DataSize.dir/dataSize.cpp.s

# Object files for target DataSize
DataSize_OBJECTS = \
"CMakeFiles/DataSize.dir/dataSize.cpp.o"

# External object files for target DataSize
DataSize_EXTERNAL_OBJECTS =

DataSize: CMakeFiles/DataSize.dir/dataSize.cpp.o
DataSize: CMakeFiles/DataSize.dir/build.make
DataSize: /usr/lib/x86_64-linux-gnu/libtbb.so.12.5
DataSize: utility/libUtility.a
DataSize: /usr/lib/gcc/x86_64-linux-gnu/11/libgomp.so
DataSize: /usr/lib/x86_64-linux-gnu/libpthread.a
DataSize: CMakeFiles/DataSize.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/lsm/sorting/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DataSize"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DataSize.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DataSize.dir/build: DataSize
.PHONY : CMakeFiles/DataSize.dir/build

CMakeFiles/DataSize.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DataSize.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DataSize.dir/clean

CMakeFiles/DataSize.dir/depend:
	cd /root/lsm/sorting && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/lsm/sorting /root/lsm/sorting /root/lsm/sorting /root/lsm/sorting /root/lsm/sorting/CMakeFiles/DataSize.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DataSize.dir/depend

