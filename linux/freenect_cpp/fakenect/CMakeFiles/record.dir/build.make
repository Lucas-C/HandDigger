# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /opt/libfreenect

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /opt/HandDigger/freenect_cpp

# Include any dependencies generated for this target.
include fakenect/CMakeFiles/record.dir/depend.make

# Include the progress variables for this target.
include fakenect/CMakeFiles/record.dir/progress.make

# Include the compile flags for this target's objects.
include fakenect/CMakeFiles/record.dir/flags.make

fakenect/CMakeFiles/record.dir/record.c.o: fakenect/CMakeFiles/record.dir/flags.make
fakenect/CMakeFiles/record.dir/record.c.o: /opt/libfreenect/fakenect/record.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/HandDigger/freenect_cpp/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object fakenect/CMakeFiles/record.dir/record.c.o"
	cd /opt/HandDigger/freenect_cpp/fakenect && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/record.dir/record.c.o   -c /opt/libfreenect/fakenect/record.c

fakenect/CMakeFiles/record.dir/record.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/record.dir/record.c.i"
	cd /opt/HandDigger/freenect_cpp/fakenect && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /opt/libfreenect/fakenect/record.c > CMakeFiles/record.dir/record.c.i

fakenect/CMakeFiles/record.dir/record.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/record.dir/record.c.s"
	cd /opt/HandDigger/freenect_cpp/fakenect && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /opt/libfreenect/fakenect/record.c -o CMakeFiles/record.dir/record.c.s

fakenect/CMakeFiles/record.dir/record.c.o.requires:
.PHONY : fakenect/CMakeFiles/record.dir/record.c.o.requires

fakenect/CMakeFiles/record.dir/record.c.o.provides: fakenect/CMakeFiles/record.dir/record.c.o.requires
	$(MAKE) -f fakenect/CMakeFiles/record.dir/build.make fakenect/CMakeFiles/record.dir/record.c.o.provides.build
.PHONY : fakenect/CMakeFiles/record.dir/record.c.o.provides

fakenect/CMakeFiles/record.dir/record.c.o.provides.build: fakenect/CMakeFiles/record.dir/record.c.o
.PHONY : fakenect/CMakeFiles/record.dir/record.c.o.provides.build

# Object files for target record
record_OBJECTS = \
"CMakeFiles/record.dir/record.c.o"

# External object files for target record
record_EXTERNAL_OBJECTS =

bin/record: fakenect/CMakeFiles/record.dir/record.c.o
bin/record: lib/libfreenect.so.0.0.1
bin/record: /usr/lib/libusb-1.0.so
bin/record: fakenect/CMakeFiles/record.dir/build.make
bin/record: fakenect/CMakeFiles/record.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../bin/record"
	cd /opt/HandDigger/freenect_cpp/fakenect && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/record.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
fakenect/CMakeFiles/record.dir/build: bin/record
.PHONY : fakenect/CMakeFiles/record.dir/build

fakenect/CMakeFiles/record.dir/requires: fakenect/CMakeFiles/record.dir/record.c.o.requires
.PHONY : fakenect/CMakeFiles/record.dir/requires

fakenect/CMakeFiles/record.dir/clean:
	cd /opt/HandDigger/freenect_cpp/fakenect && $(CMAKE_COMMAND) -P CMakeFiles/record.dir/cmake_clean.cmake
.PHONY : fakenect/CMakeFiles/record.dir/clean

fakenect/CMakeFiles/record.dir/depend:
	cd /opt/HandDigger/freenect_cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/libfreenect /opt/libfreenect/fakenect /opt/HandDigger/freenect_cpp /opt/HandDigger/freenect_cpp/fakenect /opt/HandDigger/freenect_cpp/fakenect/CMakeFiles/record.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : fakenect/CMakeFiles/record.dir/depend

