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
CMAKE_SOURCE_DIR = /home/blade_master/minidb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/blade_master/minidb/build

# Include any dependencies generated for this target.
include CMakeFiles/minidb.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/minidb.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/minidb.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/minidb.dir/flags.make

CMakeFiles/minidb.dir/main.cpp.o: CMakeFiles/minidb.dir/flags.make
CMakeFiles/minidb.dir/main.cpp.o: ../main.cpp
CMakeFiles/minidb.dir/main.cpp.o: CMakeFiles/minidb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/blade_master/minidb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/minidb.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minidb.dir/main.cpp.o -MF CMakeFiles/minidb.dir/main.cpp.o.d -o CMakeFiles/minidb.dir/main.cpp.o -c /home/blade_master/minidb/main.cpp

CMakeFiles/minidb.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minidb.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blade_master/minidb/main.cpp > CMakeFiles/minidb.dir/main.cpp.i

CMakeFiles/minidb.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minidb.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blade_master/minidb/main.cpp -o CMakeFiles/minidb.dir/main.cpp.s

CMakeFiles/minidb.dir/database_manager.cpp.o: CMakeFiles/minidb.dir/flags.make
CMakeFiles/minidb.dir/database_manager.cpp.o: ../database_manager.cpp
CMakeFiles/minidb.dir/database_manager.cpp.o: CMakeFiles/minidb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/blade_master/minidb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/minidb.dir/database_manager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minidb.dir/database_manager.cpp.o -MF CMakeFiles/minidb.dir/database_manager.cpp.o.d -o CMakeFiles/minidb.dir/database_manager.cpp.o -c /home/blade_master/minidb/database_manager.cpp

CMakeFiles/minidb.dir/database_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minidb.dir/database_manager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blade_master/minidb/database_manager.cpp > CMakeFiles/minidb.dir/database_manager.cpp.i

CMakeFiles/minidb.dir/database_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minidb.dir/database_manager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blade_master/minidb/database_manager.cpp -o CMakeFiles/minidb.dir/database_manager.cpp.s

CMakeFiles/minidb.dir/error_reporter.cpp.o: CMakeFiles/minidb.dir/flags.make
CMakeFiles/minidb.dir/error_reporter.cpp.o: ../error_reporter.cpp
CMakeFiles/minidb.dir/error_reporter.cpp.o: CMakeFiles/minidb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/blade_master/minidb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/minidb.dir/error_reporter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minidb.dir/error_reporter.cpp.o -MF CMakeFiles/minidb.dir/error_reporter.cpp.o.d -o CMakeFiles/minidb.dir/error_reporter.cpp.o -c /home/blade_master/minidb/error_reporter.cpp

CMakeFiles/minidb.dir/error_reporter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minidb.dir/error_reporter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blade_master/minidb/error_reporter.cpp > CMakeFiles/minidb.dir/error_reporter.cpp.i

CMakeFiles/minidb.dir/error_reporter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minidb.dir/error_reporter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blade_master/minidb/error_reporter.cpp -o CMakeFiles/minidb.dir/error_reporter.cpp.s

CMakeFiles/minidb.dir/output_formatter.cpp.o: CMakeFiles/minidb.dir/flags.make
CMakeFiles/minidb.dir/output_formatter.cpp.o: ../output_formatter.cpp
CMakeFiles/minidb.dir/output_formatter.cpp.o: CMakeFiles/minidb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/blade_master/minidb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/minidb.dir/output_formatter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minidb.dir/output_formatter.cpp.o -MF CMakeFiles/minidb.dir/output_formatter.cpp.o.d -o CMakeFiles/minidb.dir/output_formatter.cpp.o -c /home/blade_master/minidb/output_formatter.cpp

CMakeFiles/minidb.dir/output_formatter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minidb.dir/output_formatter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blade_master/minidb/output_formatter.cpp > CMakeFiles/minidb.dir/output_formatter.cpp.i

CMakeFiles/minidb.dir/output_formatter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minidb.dir/output_formatter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blade_master/minidb/output_formatter.cpp -o CMakeFiles/minidb.dir/output_formatter.cpp.s

CMakeFiles/minidb.dir/sql_parser.cpp.o: CMakeFiles/minidb.dir/flags.make
CMakeFiles/minidb.dir/sql_parser.cpp.o: ../sql_parser.cpp
CMakeFiles/minidb.dir/sql_parser.cpp.o: CMakeFiles/minidb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/blade_master/minidb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/minidb.dir/sql_parser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minidb.dir/sql_parser.cpp.o -MF CMakeFiles/minidb.dir/sql_parser.cpp.o.d -o CMakeFiles/minidb.dir/sql_parser.cpp.o -c /home/blade_master/minidb/sql_parser.cpp

CMakeFiles/minidb.dir/sql_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minidb.dir/sql_parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blade_master/minidb/sql_parser.cpp > CMakeFiles/minidb.dir/sql_parser.cpp.i

CMakeFiles/minidb.dir/sql_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minidb.dir/sql_parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blade_master/minidb/sql_parser.cpp -o CMakeFiles/minidb.dir/sql_parser.cpp.s

CMakeFiles/minidb.dir/query_executor.cpp.o: CMakeFiles/minidb.dir/flags.make
CMakeFiles/minidb.dir/query_executor.cpp.o: ../query_executor.cpp
CMakeFiles/minidb.dir/query_executor.cpp.o: CMakeFiles/minidb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/blade_master/minidb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/minidb.dir/query_executor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minidb.dir/query_executor.cpp.o -MF CMakeFiles/minidb.dir/query_executor.cpp.o.d -o CMakeFiles/minidb.dir/query_executor.cpp.o -c /home/blade_master/minidb/query_executor.cpp

CMakeFiles/minidb.dir/query_executor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minidb.dir/query_executor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/blade_master/minidb/query_executor.cpp > CMakeFiles/minidb.dir/query_executor.cpp.i

CMakeFiles/minidb.dir/query_executor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minidb.dir/query_executor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/blade_master/minidb/query_executor.cpp -o CMakeFiles/minidb.dir/query_executor.cpp.s

# Object files for target minidb
minidb_OBJECTS = \
"CMakeFiles/minidb.dir/main.cpp.o" \
"CMakeFiles/minidb.dir/database_manager.cpp.o" \
"CMakeFiles/minidb.dir/error_reporter.cpp.o" \
"CMakeFiles/minidb.dir/output_formatter.cpp.o" \
"CMakeFiles/minidb.dir/sql_parser.cpp.o" \
"CMakeFiles/minidb.dir/query_executor.cpp.o"

# External object files for target minidb
minidb_EXTERNAL_OBJECTS =

minidb: CMakeFiles/minidb.dir/main.cpp.o
minidb: CMakeFiles/minidb.dir/database_manager.cpp.o
minidb: CMakeFiles/minidb.dir/error_reporter.cpp.o
minidb: CMakeFiles/minidb.dir/output_formatter.cpp.o
minidb: CMakeFiles/minidb.dir/sql_parser.cpp.o
minidb: CMakeFiles/minidb.dir/query_executor.cpp.o
minidb: CMakeFiles/minidb.dir/build.make
minidb: CMakeFiles/minidb.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/blade_master/minidb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable minidb"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minidb.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/minidb.dir/build: minidb
.PHONY : CMakeFiles/minidb.dir/build

CMakeFiles/minidb.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/minidb.dir/cmake_clean.cmake
.PHONY : CMakeFiles/minidb.dir/clean

CMakeFiles/minidb.dir/depend:
	cd /home/blade_master/minidb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/blade_master/minidb /home/blade_master/minidb /home/blade_master/minidb/build /home/blade_master/minidb/build /home/blade_master/minidb/build/CMakeFiles/minidb.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/minidb.dir/depend
