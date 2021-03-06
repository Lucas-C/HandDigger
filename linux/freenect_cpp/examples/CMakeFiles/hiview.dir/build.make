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
include examples/CMakeFiles/hiview.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/hiview.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/hiview.dir/flags.make

examples/CMakeFiles/hiview.dir/hiview.c.o: examples/CMakeFiles/hiview.dir/flags.make
examples/CMakeFiles/hiview.dir/hiview.c.o: /opt/libfreenect/examples/hiview.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/HandDigger/freenect_cpp/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/hiview.dir/hiview.c.o"
	cd /opt/HandDigger/freenect_cpp/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/hiview.dir/hiview.c.o   -c /opt/libfreenect/examples/hiview.c

examples/CMakeFiles/hiview.dir/hiview.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hiview.dir/hiview.c.i"
	cd /opt/HandDigger/freenect_cpp/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /opt/libfreenect/examples/hiview.c > CMakeFiles/hiview.dir/hiview.c.i

examples/CMakeFiles/hiview.dir/hiview.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hiview.dir/hiview.c.s"
	cd /opt/HandDigger/freenect_cpp/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /opt/libfreenect/examples/hiview.c -o CMakeFiles/hiview.dir/hiview.c.s

examples/CMakeFiles/hiview.dir/hiview.c.o.requires:
.PHONY : examples/CMakeFiles/hiview.dir/hiview.c.o.requires

examples/CMakeFiles/hiview.dir/hiview.c.o.provides: examples/CMakeFiles/hiview.dir/hiview.c.o.requires
	$(MAKE) -f examples/CMakeFiles/hiview.dir/build.make examples/CMakeFiles/hiview.dir/hiview.c.o.provides.build
.PHONY : examples/CMakeFiles/hiview.dir/hiview.c.o.provides

examples/CMakeFiles/hiview.dir/hiview.c.o.provides.build: examples/CMakeFiles/hiview.dir/hiview.c.o
.PHONY : examples/CMakeFiles/hiview.dir/hiview.c.o.provides.build

# Object files for target hiview
hiview_OBJECTS = \
"CMakeFiles/hiview.dir/hiview.c.o"

# External object files for target hiview
hiview_EXTERNAL_OBJECTS =

bin/hiview: examples/CMakeFiles/hiview.dir/hiview.c.o
bin/hiview: lib/libfreenect.so.0.0.1
bin/hiview: /usr/lib/libGLU.so
bin/hiview: /usr/lib/libGL.so
bin/hiview: /usr/lib/libSM.so
bin/hiview: /usr/lib/libICE.so
bin/hiview: /usr/lib/libX11.so
bin/hiview: /usr/lib/libXext.so
bin/hiview: /usr/lib/libglut.so
bin/hiview: /usr/lib/libXmu.so
bin/hiview: /usr/lib/libXi.so
bin/hiview: /usr/lib/libusb-1.0.so
bin/hiview: examples/CMakeFiles/hiview.dir/build.make
bin/hiview: examples/CMakeFiles/hiview.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../bin/hiview"
	cd /opt/HandDigger/freenect_cpp/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hiview.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/hiview.dir/build: bin/hiview
.PHONY : examples/CMakeFiles/hiview.dir/build

examples/CMakeFiles/hiview.dir/requires: examples/CMakeFiles/hiview.dir/hiview.c.o.requires
.PHONY : examples/CMakeFiles/hiview.dir/requires

examples/CMakeFiles/hiview.dir/clean:
	cd /opt/HandDigger/freenect_cpp/examples && $(CMAKE_COMMAND) -P CMakeFiles/hiview.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/hiview.dir/clean

examples/CMakeFiles/hiview.dir/depend:
	cd /opt/HandDigger/freenect_cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/libfreenect /opt/libfreenect/examples /opt/HandDigger/freenect_cpp /opt/HandDigger/freenect_cpp/examples /opt/HandDigger/freenect_cpp/examples/CMakeFiles/hiview.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/hiview.dir/depend

