# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/AtulBajpai/Development/JumpTrading/orderbook

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/AtulBajpai/Development/JumpTrading/orderbook/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/matchengine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/matchengine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/matchengine.dir/flags.make

CMakeFiles/matchengine.dir/main.cpp.o: CMakeFiles/matchengine.dir/flags.make
CMakeFiles/matchengine.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/AtulBajpai/Development/JumpTrading/orderbook/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/matchengine.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/matchengine.dir/main.cpp.o -c /Users/AtulBajpai/Development/JumpTrading/orderbook/main.cpp

CMakeFiles/matchengine.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matchengine.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/AtulBajpai/Development/JumpTrading/orderbook/main.cpp > CMakeFiles/matchengine.dir/main.cpp.i

CMakeFiles/matchengine.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matchengine.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/AtulBajpai/Development/JumpTrading/orderbook/main.cpp -o CMakeFiles/matchengine.dir/main.cpp.s

CMakeFiles/matchengine.dir/engine.cpp.o: CMakeFiles/matchengine.dir/flags.make
CMakeFiles/matchengine.dir/engine.cpp.o: ../engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/AtulBajpai/Development/JumpTrading/orderbook/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/matchengine.dir/engine.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/matchengine.dir/engine.cpp.o -c /Users/AtulBajpai/Development/JumpTrading/orderbook/engine.cpp

CMakeFiles/matchengine.dir/engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matchengine.dir/engine.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/AtulBajpai/Development/JumpTrading/orderbook/engine.cpp > CMakeFiles/matchengine.dir/engine.cpp.i

CMakeFiles/matchengine.dir/engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matchengine.dir/engine.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/AtulBajpai/Development/JumpTrading/orderbook/engine.cpp -o CMakeFiles/matchengine.dir/engine.cpp.s

CMakeFiles/matchengine.dir/feed_handler.cpp.o: CMakeFiles/matchengine.dir/flags.make
CMakeFiles/matchengine.dir/feed_handler.cpp.o: ../feed_handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/AtulBajpai/Development/JumpTrading/orderbook/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/matchengine.dir/feed_handler.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/matchengine.dir/feed_handler.cpp.o -c /Users/AtulBajpai/Development/JumpTrading/orderbook/feed_handler.cpp

CMakeFiles/matchengine.dir/feed_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matchengine.dir/feed_handler.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/AtulBajpai/Development/JumpTrading/orderbook/feed_handler.cpp > CMakeFiles/matchengine.dir/feed_handler.cpp.i

CMakeFiles/matchengine.dir/feed_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matchengine.dir/feed_handler.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/AtulBajpai/Development/JumpTrading/orderbook/feed_handler.cpp -o CMakeFiles/matchengine.dir/feed_handler.cpp.s

# Object files for target matchengine
matchengine_OBJECTS = \
"CMakeFiles/matchengine.dir/main.cpp.o" \
"CMakeFiles/matchengine.dir/engine.cpp.o" \
"CMakeFiles/matchengine.dir/feed_handler.cpp.o"

# External object files for target matchengine
matchengine_EXTERNAL_OBJECTS =

matchengine: CMakeFiles/matchengine.dir/main.cpp.o
matchengine: CMakeFiles/matchengine.dir/engine.cpp.o
matchengine: CMakeFiles/matchengine.dir/feed_handler.cpp.o
matchengine: CMakeFiles/matchengine.dir/build.make
matchengine: CMakeFiles/matchengine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/AtulBajpai/Development/JumpTrading/orderbook/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable matchengine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/matchengine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/matchengine.dir/build: matchengine

.PHONY : CMakeFiles/matchengine.dir/build

CMakeFiles/matchengine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/matchengine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/matchengine.dir/clean

CMakeFiles/matchengine.dir/depend:
	cd /Users/AtulBajpai/Development/JumpTrading/orderbook/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/AtulBajpai/Development/JumpTrading/orderbook /Users/AtulBajpai/Development/JumpTrading/orderbook /Users/AtulBajpai/Development/JumpTrading/orderbook/cmake-build-debug /Users/AtulBajpai/Development/JumpTrading/orderbook/cmake-build-debug /Users/AtulBajpai/Development/JumpTrading/orderbook/cmake-build-debug/CMakeFiles/matchengine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/matchengine.dir/depend

