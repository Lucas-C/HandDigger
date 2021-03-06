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
include examples/CMakeFiles/glview.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/glview.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/glview.dir/flags.make

examples/CMakeFiles/glview.dir/glview.c.o: examples/CMakeFiles/glview.dir/flags.make
examples/CMakeFiles/glview.dir/glview.c.o: /opt/libfreenect/examples/glview.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/HandDigger/freenect_cpp/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/glview.dir/glview.c.o"
	cd /opt/HandDigger/freenect_cpp/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/glview.dir/glview.c.o   -c /opt/libfreenect/examples/glview.c

examples/CMakeFiles/glview.dir/glview.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glview.dir/glview.c.i"
	cd /opt/HandDigger/freenect_cpp/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /opt/libfreenect/examples/glview.c > CMakeFiles/glview.dir/glview.c.i

examples/CMakeFiles/glview.dir/glview.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glview.dir/glview.c.s"
	cd /opt/HandDigger/freenect_cpp/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /opt/libfreenect/examples/glview.c -o CMakeFiles/glview.dir/glview.c.s

examples/CMakeFiles/glview.dir/glview.c.o.requires:
.PHONY : examples/CMakeFiles/glview.dir/glview.c.o.requires

examples/CMakeFiles/glview.dir/glview.c.o.provides: examples/CMakeFiles/glview.dir/glview.c.o.requires
	$(MAKE) -f examples/CMakeFiles/glview.dir/build.make examples/CMakeFiles/glview.dir/glview.c.o.provides.build
.PHONY : examples/CMakeFiles/glview.dir/glview.c.o.provides

examples/CMakeFiles/glview.dir/glview.c.o.provides.build: examples/CMakeFiles/glview.dir/glview.c.o
.PHONY : examples/CMakeFiles/glview.dir/glview.c.o.provides.build

# Object files for target glview
glview_OBJECTS = \
"CMakeFiles/glview.dir/glview.c.o"

# External object files for target glview
glview_EXTERNAL_OBJECTS =

bin/glview: examples/CMakeFiles/glview.dir/glview.c.o
bin/glview: lib/libfreenect.so.0.0.1
bin/glview: /usr/lib/libGLU.so
bin/glview: /usr/lib/libGL.so
bin/glview: /usr/lib/libSM.so
bin/glview: /usr/lib/libICE.so
bin/glview: /usr/lib/libX11.so
bin/glview: /usr/lib/libXext.so
bin/glview: /usr/lib/libglut.so
bin/glview: /usr/lib/libXmu.so
bin/glview: /usr/lib/libXi.so
bin/glview: /usr/lib/libusb-1.0.so
bin/glview: examples/CMakeFiles/glview.dir/build.make
bin/glview: examples/CMakeFiles/glview.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../bin/glview"
	cd /opt/HandDigger/freenect_cpp/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glview.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/glview.dir/build: bin/glview
.PHONY : examples/CMakeFiles/glview.dir/build

examples/CMakeFiles/glview.dir/requires: examples/CMakeFiles/glview.dir/glview.c.o.requires
.PHONY : examples/CMakeFiles/glview.dir/requires

examples/CMakeFiles/glview.dir/clean:
	cd /opt/HandDigger/freenect_cpp/examples && $(CMAKE_COMMAND) -P CMakeFiles/glview.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/glview.dir/clean

examples/CMakeFiles/glview.dir/depend:
	cd /opt/HandDigger/freenect_cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/libfreenect /opt/libfreenect/examples /opt/HandDigger/freenect_cpp /opt/HandDigger/freenect_cpp/examples /opt/HandDigger/freenect_cpp/examples/CMakeFiles/glview.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/glview.dir/depend

