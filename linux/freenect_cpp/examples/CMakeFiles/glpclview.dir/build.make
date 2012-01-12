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
include examples/CMakeFiles/glpclview.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/glpclview.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/glpclview.dir/flags.make

examples/CMakeFiles/glpclview.dir/glpclview.c.o: examples/CMakeFiles/glpclview.dir/flags.make
examples/CMakeFiles/glpclview.dir/glpclview.c.o: /opt/libfreenect/examples/glpclview.c
	$(CMAKE_COMMAND) -E cmake_progress_report /opt/HandDigger/freenect_cpp/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/glpclview.dir/glpclview.c.o"
	cd /opt/HandDigger/freenect_cpp/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/glpclview.dir/glpclview.c.o   -c /opt/libfreenect/examples/glpclview.c

examples/CMakeFiles/glpclview.dir/glpclview.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glpclview.dir/glpclview.c.i"
	cd /opt/HandDigger/freenect_cpp/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /opt/libfreenect/examples/glpclview.c > CMakeFiles/glpclview.dir/glpclview.c.i

examples/CMakeFiles/glpclview.dir/glpclview.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glpclview.dir/glpclview.c.s"
	cd /opt/HandDigger/freenect_cpp/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /opt/libfreenect/examples/glpclview.c -o CMakeFiles/glpclview.dir/glpclview.c.s

examples/CMakeFiles/glpclview.dir/glpclview.c.o.requires:
.PHONY : examples/CMakeFiles/glpclview.dir/glpclview.c.o.requires

examples/CMakeFiles/glpclview.dir/glpclview.c.o.provides: examples/CMakeFiles/glpclview.dir/glpclview.c.o.requires
	$(MAKE) -f examples/CMakeFiles/glpclview.dir/build.make examples/CMakeFiles/glpclview.dir/glpclview.c.o.provides.build
.PHONY : examples/CMakeFiles/glpclview.dir/glpclview.c.o.provides

examples/CMakeFiles/glpclview.dir/glpclview.c.o.provides.build: examples/CMakeFiles/glpclview.dir/glpclview.c.o
.PHONY : examples/CMakeFiles/glpclview.dir/glpclview.c.o.provides.build

# Object files for target glpclview
glpclview_OBJECTS = \
"CMakeFiles/glpclview.dir/glpclview.c.o"

# External object files for target glpclview
glpclview_EXTERNAL_OBJECTS =

bin/glpclview: examples/CMakeFiles/glpclview.dir/glpclview.c.o
bin/glpclview: lib/libfreenect_sync.so.0.0.1
bin/glpclview: /usr/lib/libGLU.so
bin/glpclview: /usr/lib/libGL.so
bin/glpclview: /usr/lib/libSM.so
bin/glpclview: /usr/lib/libICE.so
bin/glpclview: /usr/lib/libX11.so
bin/glpclview: /usr/lib/libXext.so
bin/glpclview: /usr/lib/libglut.so
bin/glpclview: /usr/lib/libXmu.so
bin/glpclview: /usr/lib/libXi.so
bin/glpclview: lib/libfreenect.so.0.0.1
bin/glpclview: /usr/lib/libusb-1.0.so
bin/glpclview: examples/CMakeFiles/glpclview.dir/build.make
bin/glpclview: examples/CMakeFiles/glpclview.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../bin/glpclview"
	cd /opt/HandDigger/freenect_cpp/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glpclview.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/glpclview.dir/build: bin/glpclview
.PHONY : examples/CMakeFiles/glpclview.dir/build

examples/CMakeFiles/glpclview.dir/requires: examples/CMakeFiles/glpclview.dir/glpclview.c.o.requires
.PHONY : examples/CMakeFiles/glpclview.dir/requires

examples/CMakeFiles/glpclview.dir/clean:
	cd /opt/HandDigger/freenect_cpp/examples && $(CMAKE_COMMAND) -P CMakeFiles/glpclview.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/glpclview.dir/clean

examples/CMakeFiles/glpclview.dir/depend:
	cd /opt/HandDigger/freenect_cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/libfreenect /opt/libfreenect/examples /opt/HandDigger/freenect_cpp /opt/HandDigger/freenect_cpp/examples /opt/HandDigger/freenect_cpp/examples/CMakeFiles/glpclview.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/glpclview.dir/depend
