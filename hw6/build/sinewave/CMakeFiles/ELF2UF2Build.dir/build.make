# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/michael/northwesternCourses/mech433/pico/pico-examples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/michael/northwesternCourses/mech433/pico/pico-examples

# Utility rule file for ELF2UF2Build.

# Include any custom commands dependencies for this target.
include sinewave/CMakeFiles/ELF2UF2Build.dir/compiler_depend.make

# Include the progress variables for this target.
include sinewave/CMakeFiles/ELF2UF2Build.dir/progress.make

sinewave/CMakeFiles/ELF2UF2Build: sinewave/CMakeFiles/ELF2UF2Build-complete

sinewave/CMakeFiles/ELF2UF2Build-complete: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-install
sinewave/CMakeFiles/ELF2UF2Build-complete: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-mkdir
sinewave/CMakeFiles/ELF2UF2Build-complete: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-download
sinewave/CMakeFiles/ELF2UF2Build-complete: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-update
sinewave/CMakeFiles/ELF2UF2Build-complete: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-patch
sinewave/CMakeFiles/ELF2UF2Build-complete: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-configure
sinewave/CMakeFiles/ELF2UF2Build-complete: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-build
sinewave/CMakeFiles/ELF2UF2Build-complete: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/michael/northwesternCourses/mech433/pico/pico-examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'ELF2UF2Build'"
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave && /usr/bin/cmake -E make_directory /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave/CMakeFiles
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave && /usr/bin/cmake -E touch /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave/CMakeFiles/ELF2UF2Build-complete
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave && /usr/bin/cmake -E touch /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-done

sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-build: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/michael/northwesternCourses/mech433/pico/pico-examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Performing build step for 'ELF2UF2Build'"
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/elf2uf2 && $(MAKE)

sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-configure: sinewave/elf2uf2/tmp/ELF2UF2Build-cfgcmd.txt
sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-configure: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/michael/northwesternCourses/mech433/pico/pico-examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Performing configure step for 'ELF2UF2Build'"
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/elf2uf2 && /usr/bin/cmake -DCMAKE_MAKE_PROGRAM:FILEPATH=/usr/bin/gmake "-GUnix Makefiles" /home/michael/northwesternCourses/mech433/pico/pico-sdk/tools/elf2uf2
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/elf2uf2 && /usr/bin/cmake -E touch /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-configure

sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-download: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-source_dirinfo.txt
sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-download: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/michael/northwesternCourses/mech433/pico/pico-examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "No download step for 'ELF2UF2Build'"
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave && /usr/bin/cmake -E echo_append
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave && /usr/bin/cmake -E touch /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-download

sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-install: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/michael/northwesternCourses/mech433/pico/pico-examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'ELF2UF2Build'"
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/elf2uf2 && /usr/bin/cmake -E echo_append

sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/michael/northwesternCourses/mech433/pico/pico-examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'ELF2UF2Build'"
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave && /usr/bin/cmake -Dcfgdir= -P /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave/elf2uf2/tmp/ELF2UF2Build-mkdirs.cmake
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave && /usr/bin/cmake -E touch /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-mkdir

sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-patch: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-update
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/michael/northwesternCourses/mech433/pico/pico-examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'ELF2UF2Build'"
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave && /usr/bin/cmake -E echo_append
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave && /usr/bin/cmake -E touch /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-patch

sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-update: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/michael/northwesternCourses/mech433/pico/pico-examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No update step for 'ELF2UF2Build'"
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave && /usr/bin/cmake -E echo_append
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave && /usr/bin/cmake -E touch /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-update

ELF2UF2Build: sinewave/CMakeFiles/ELF2UF2Build
ELF2UF2Build: sinewave/CMakeFiles/ELF2UF2Build-complete
ELF2UF2Build: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-build
ELF2UF2Build: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-configure
ELF2UF2Build: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-download
ELF2UF2Build: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-install
ELF2UF2Build: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-mkdir
ELF2UF2Build: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-patch
ELF2UF2Build: sinewave/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-update
ELF2UF2Build: sinewave/CMakeFiles/ELF2UF2Build.dir/build.make
.PHONY : ELF2UF2Build

# Rule to build all files generated by this target.
sinewave/CMakeFiles/ELF2UF2Build.dir/build: ELF2UF2Build
.PHONY : sinewave/CMakeFiles/ELF2UF2Build.dir/build

sinewave/CMakeFiles/ELF2UF2Build.dir/clean:
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave && $(CMAKE_COMMAND) -P CMakeFiles/ELF2UF2Build.dir/cmake_clean.cmake
.PHONY : sinewave/CMakeFiles/ELF2UF2Build.dir/clean

sinewave/CMakeFiles/ELF2UF2Build.dir/depend:
	cd /home/michael/northwesternCourses/mech433/pico/pico-examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/michael/northwesternCourses/mech433/pico/pico-examples /home/michael/northwesternCourses/mech433/pico_assignments/hw5/sinewave /home/michael/northwesternCourses/mech433/pico/pico-examples /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave /home/michael/northwesternCourses/mech433/pico/pico-examples/sinewave/CMakeFiles/ELF2UF2Build.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sinewave/CMakeFiles/ELF2UF2Build.dir/depend
