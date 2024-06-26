# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /root/lsm/sorting/CMakeFiles /root/lsm/sorting//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /root/lsm/sorting/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Main

# Build rule for target.
Main: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Main
.PHONY : Main

# fast build rule for target.
Main/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Main.dir/build.make CMakeFiles/Main.dir/build
.PHONY : Main/fast

#=============================================================================
# Target rules for targets named Learn

# Build rule for target.
Learn: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Learn
.PHONY : Learn

# fast build rule for target.
Learn/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Learn.dir/build.make CMakeFiles/Learn.dir/build
.PHONY : Learn/fast

#=============================================================================
# Target rules for targets named Test

# Build rule for target.
Test: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Test
.PHONY : Test

# fast build rule for target.
Test/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Test.dir/build.make CMakeFiles/Test.dir/build
.PHONY : Test/fast

#=============================================================================
# Target rules for targets named DataSize

# Build rule for target.
DataSize: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 DataSize
.PHONY : DataSize

# fast build rule for target.
DataSize/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DataSize.dir/build.make CMakeFiles/DataSize.dir/build
.PHONY : DataSize/fast

#=============================================================================
# Target rules for targets named Parallel

# Build rule for target.
Parallel: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Parallel
.PHONY : Parallel

# fast build rule for target.
Parallel/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Parallel.dir/build.make CMakeFiles/Parallel.dir/build
.PHONY : Parallel/fast

#=============================================================================
# Target rules for targets named Utility

# Build rule for target.
Utility: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Utility
.PHONY : Utility

# fast build rule for target.
Utility/fast:
	$(MAKE) $(MAKESILENT) -f utility/CMakeFiles/Utility.dir/build.make utility/CMakeFiles/Utility.dir/build
.PHONY : Utility/fast

dataSize.o: dataSize.cpp.o
.PHONY : dataSize.o

# target to build an object file
dataSize.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DataSize.dir/build.make CMakeFiles/DataSize.dir/dataSize.cpp.o
.PHONY : dataSize.cpp.o

dataSize.i: dataSize.cpp.i
.PHONY : dataSize.i

# target to preprocess a source file
dataSize.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DataSize.dir/build.make CMakeFiles/DataSize.dir/dataSize.cpp.i
.PHONY : dataSize.cpp.i

dataSize.s: dataSize.cpp.s
.PHONY : dataSize.s

# target to generate assembly for a file
dataSize.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/DataSize.dir/build.make CMakeFiles/DataSize.dir/dataSize.cpp.s
.PHONY : dataSize.cpp.s

learn.o: learn.cpp.o
.PHONY : learn.o

# target to build an object file
learn.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Learn.dir/build.make CMakeFiles/Learn.dir/learn.cpp.o
.PHONY : learn.cpp.o

learn.i: learn.cpp.i
.PHONY : learn.i

# target to preprocess a source file
learn.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Learn.dir/build.make CMakeFiles/Learn.dir/learn.cpp.i
.PHONY : learn.cpp.i

learn.s: learn.cpp.s
.PHONY : learn.s

# target to generate assembly for a file
learn.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Learn.dir/build.make CMakeFiles/Learn.dir/learn.cpp.s
.PHONY : learn.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Main.dir/build.make CMakeFiles/Main.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Main.dir/build.make CMakeFiles/Main.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Main.dir/build.make CMakeFiles/Main.dir/main.cpp.s
.PHONY : main.cpp.s

parallel.o: parallel.cpp.o
.PHONY : parallel.o

# target to build an object file
parallel.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Parallel.dir/build.make CMakeFiles/Parallel.dir/parallel.cpp.o
.PHONY : parallel.cpp.o

parallel.i: parallel.cpp.i
.PHONY : parallel.i

# target to preprocess a source file
parallel.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Parallel.dir/build.make CMakeFiles/Parallel.dir/parallel.cpp.i
.PHONY : parallel.cpp.i

parallel.s: parallel.cpp.s
.PHONY : parallel.s

# target to generate assembly for a file
parallel.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Parallel.dir/build.make CMakeFiles/Parallel.dir/parallel.cpp.s
.PHONY : parallel.cpp.s

test.o: test.cpp.o
.PHONY : test.o

# target to build an object file
test.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Test.dir/build.make CMakeFiles/Test.dir/test.cpp.o
.PHONY : test.cpp.o

test.i: test.cpp.i
.PHONY : test.i

# target to preprocess a source file
test.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Test.dir/build.make CMakeFiles/Test.dir/test.cpp.i
.PHONY : test.cpp.i

test.s: test.cpp.s
.PHONY : test.s

# target to generate assembly for a file
test.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Test.dir/build.make CMakeFiles/Test.dir/test.cpp.s
.PHONY : test.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... DataSize"
	@echo "... Learn"
	@echo "... Main"
	@echo "... Parallel"
	@echo "... Test"
	@echo "... Utility"
	@echo "... dataSize.o"
	@echo "... dataSize.i"
	@echo "... dataSize.s"
	@echo "... learn.o"
	@echo "... learn.i"
	@echo "... learn.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... parallel.o"
	@echo "... parallel.i"
	@echo "... parallel.s"
	@echo "... test.o"
	@echo "... test.i"
	@echo "... test.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

