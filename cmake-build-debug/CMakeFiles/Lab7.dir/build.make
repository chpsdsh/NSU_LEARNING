# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.3.3\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.3.3\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Programming\NSU_LEARNING

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Programming\NSU_LEARNING\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Lab7.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Lab7.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab7.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab7.dir/flags.make

CMakeFiles/Lab7.dir/Lab7/main.c.obj: CMakeFiles/Lab7.dir/flags.make
CMakeFiles/Lab7.dir/Lab7/main.c.obj: C:/Programming/NSU_LEARNING/Lab7/main.c
CMakeFiles/Lab7.dir/Lab7/main.c.obj: CMakeFiles/Lab7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Programming\NSU_LEARNING\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Lab7.dir/Lab7/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Lab7.dir/Lab7/main.c.obj -MF CMakeFiles\Lab7.dir\Lab7\main.c.obj.d -o CMakeFiles\Lab7.dir\Lab7\main.c.obj -c C:\Programming\NSU_LEARNING\Lab7\main.c

CMakeFiles/Lab7.dir/Lab7/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/Lab7.dir/Lab7/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Programming\NSU_LEARNING\Lab7\main.c > CMakeFiles\Lab7.dir\Lab7\main.c.i

CMakeFiles/Lab7.dir/Lab7/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/Lab7.dir/Lab7/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Programming\NSU_LEARNING\Lab7\main.c -o CMakeFiles\Lab7.dir\Lab7\main.c.s

# Object files for target Lab7
Lab7_OBJECTS = \
"CMakeFiles/Lab7.dir/Lab7/main.c.obj"

# External object files for target Lab7
Lab7_EXTERNAL_OBJECTS =

Lab7.exe: CMakeFiles/Lab7.dir/Lab7/main.c.obj
Lab7.exe: CMakeFiles/Lab7.dir/build.make
Lab7.exe: CMakeFiles/Lab7.dir/linkLibs.rsp
Lab7.exe: CMakeFiles/Lab7.dir/objects1.rsp
Lab7.exe: CMakeFiles/Lab7.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Programming\NSU_LEARNING\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Lab7.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Lab7.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab7.dir/build: Lab7.exe
.PHONY : CMakeFiles/Lab7.dir/build

CMakeFiles/Lab7.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Lab7.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Lab7.dir/clean

CMakeFiles/Lab7.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Programming\NSU_LEARNING C:\Programming\NSU_LEARNING C:\Programming\NSU_LEARNING\cmake-build-debug C:\Programming\NSU_LEARNING\cmake-build-debug C:\Programming\NSU_LEARNING\cmake-build-debug\CMakeFiles\Lab7.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Lab7.dir/depend

