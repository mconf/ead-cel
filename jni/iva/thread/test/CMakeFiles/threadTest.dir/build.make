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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/andre/workspace/eadcel_2536/jni/iva

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andre/workspace/eadcel_2536/jni/iva

# Include any dependencies generated for this target.
include thread/test/CMakeFiles/threadTest.dir/depend.make

# Include the progress variables for this target.
include thread/test/CMakeFiles/threadTest.dir/progress.make

# Include the compile flags for this target's objects.
include thread/test/CMakeFiles/threadTest.dir/flags.make

thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o: thread/test/CMakeFiles/threadTest.dir/flags.make
thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o: thread/test/gtest_ConditionVariable.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_ConditionVariable.cpp

thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_ConditionVariable.cpp > CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.i

thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_ConditionVariable.cpp -o CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.s

thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o.requires:
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o.requires

thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o.provides: thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o.requires
	$(MAKE) -f thread/test/CMakeFiles/threadTest.dir/build.make thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o.provides.build
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o.provides

thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o.provides.build: thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o.provides.build

thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.o: thread/test/CMakeFiles/threadTest.dir/flags.make
thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.o: thread/test/gtest_main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/threadTest.dir/gtest_main.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_main.cpp

thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threadTest.dir/gtest_main.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_main.cpp > CMakeFiles/threadTest.dir/gtest_main.cpp.i

thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threadTest.dir/gtest_main.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_main.cpp -o CMakeFiles/threadTest.dir/gtest_main.cpp.s

thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.o.requires:
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.o.requires

thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.o.provides: thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.o.requires
	$(MAKE) -f thread/test/CMakeFiles/threadTest.dir/build.make thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.o.provides.build
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.o.provides

thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.o.provides.build: thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.o
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.o.provides.build

thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o: thread/test/CMakeFiles/threadTest.dir/flags.make
thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o: thread/test/gtest_Microseconds.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Microseconds.cpp

thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Microseconds.cpp > CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.i

thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Microseconds.cpp -o CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.s

thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o.requires:
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o.requires

thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o.provides: thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o.requires
	$(MAKE) -f thread/test/CMakeFiles/threadTest.dir/build.make thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o.provides.build
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o.provides

thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o.provides.build: thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o.provides.build

thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o: thread/test/CMakeFiles/threadTest.dir/flags.make
thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o: thread/test/gtest_Milliseconds.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Milliseconds.cpp

thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Milliseconds.cpp > CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.i

thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Milliseconds.cpp -o CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.s

thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o.requires:
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o.requires

thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o.provides: thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o.requires
	$(MAKE) -f thread/test/CMakeFiles/threadTest.dir/build.make thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o.provides.build
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o.provides

thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o.provides.build: thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o.provides.build

thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o: thread/test/CMakeFiles/threadTest.dir/flags.make
thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o: thread/test/gtest_Mutex.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Mutex.cpp

thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threadTest.dir/gtest_Mutex.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Mutex.cpp > CMakeFiles/threadTest.dir/gtest_Mutex.cpp.i

thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threadTest.dir/gtest_Mutex.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Mutex.cpp -o CMakeFiles/threadTest.dir/gtest_Mutex.cpp.s

thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o.requires:
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o.requires

thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o.provides: thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o.requires
	$(MAKE) -f thread/test/CMakeFiles/threadTest.dir/build.make thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o.provides.build
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o.provides

thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o.provides.build: thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o.provides.build

thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o: thread/test/CMakeFiles/threadTest.dir/flags.make
thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o: thread/test/gtest_Seconds.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Seconds.cpp

thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threadTest.dir/gtest_Seconds.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Seconds.cpp > CMakeFiles/threadTest.dir/gtest_Seconds.cpp.i

thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threadTest.dir/gtest_Seconds.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Seconds.cpp -o CMakeFiles/threadTest.dir/gtest_Seconds.cpp.s

thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o.requires:
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o.requires

thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o.provides: thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o.requires
	$(MAKE) -f thread/test/CMakeFiles/threadTest.dir/build.make thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o.provides.build
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o.provides

thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o.provides.build: thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o.provides.build

thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.o: thread/test/CMakeFiles/threadTest.dir/flags.make
thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.o: thread/test/gtest_Thread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/threadTest.dir/gtest_Thread.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Thread.cpp

thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threadTest.dir/gtest_Thread.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Thread.cpp > CMakeFiles/threadTest.dir/gtest_Thread.cpp.i

thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threadTest.dir/gtest_Thread.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Thread.cpp -o CMakeFiles/threadTest.dir/gtest_Thread.cpp.s

thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.o.requires:
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.o.requires

thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.o.provides: thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.o.requires
	$(MAKE) -f thread/test/CMakeFiles/threadTest.dir/build.make thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.o.provides.build
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.o.provides

thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.o.provides.build: thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.o
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.o.provides.build

thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.o: thread/test/CMakeFiles/threadTest.dir/flags.make
thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.o: thread/test/gtest_Timer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/threadTest.dir/gtest_Timer.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Timer.cpp

thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threadTest.dir/gtest_Timer.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Timer.cpp > CMakeFiles/threadTest.dir/gtest_Timer.cpp.i

thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threadTest.dir/gtest_Timer.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/thread/test/gtest_Timer.cpp -o CMakeFiles/threadTest.dir/gtest_Timer.cpp.s

thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.o.requires:
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.o.requires

thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.o.provides: thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.o.requires
	$(MAKE) -f thread/test/CMakeFiles/threadTest.dir/build.make thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.o.provides.build
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.o.provides

thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.o.provides.build: thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.o
.PHONY : thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.o.provides.build

# Object files for target threadTest
threadTest_OBJECTS = \
"CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o" \
"CMakeFiles/threadTest.dir/gtest_main.cpp.o" \
"CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o" \
"CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o" \
"CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o" \
"CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o" \
"CMakeFiles/threadTest.dir/gtest_Thread.cpp.o" \
"CMakeFiles/threadTest.dir/gtest_Timer.cpp.o"

# External object files for target threadTest
threadTest_EXTERNAL_OBJECTS =

thread/test/threadTest: thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o
thread/test/threadTest: thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.o
thread/test/threadTest: thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o
thread/test/threadTest: thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o
thread/test/threadTest: thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o
thread/test/threadTest: thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o
thread/test/threadTest: thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.o
thread/test/threadTest: thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.o
thread/test/threadTest: thread/libthread.a
thread/test/threadTest: thread/test/CMakeFiles/threadTest.dir/build.make
thread/test/threadTest: thread/test/CMakeFiles/threadTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable threadTest"
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threadTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
thread/test/CMakeFiles/threadTest.dir/build: thread/test/threadTest
.PHONY : thread/test/CMakeFiles/threadTest.dir/build

thread/test/CMakeFiles/threadTest.dir/requires: thread/test/CMakeFiles/threadTest.dir/gtest_ConditionVariable.cpp.o.requires
thread/test/CMakeFiles/threadTest.dir/requires: thread/test/CMakeFiles/threadTest.dir/gtest_main.cpp.o.requires
thread/test/CMakeFiles/threadTest.dir/requires: thread/test/CMakeFiles/threadTest.dir/gtest_Microseconds.cpp.o.requires
thread/test/CMakeFiles/threadTest.dir/requires: thread/test/CMakeFiles/threadTest.dir/gtest_Milliseconds.cpp.o.requires
thread/test/CMakeFiles/threadTest.dir/requires: thread/test/CMakeFiles/threadTest.dir/gtest_Mutex.cpp.o.requires
thread/test/CMakeFiles/threadTest.dir/requires: thread/test/CMakeFiles/threadTest.dir/gtest_Seconds.cpp.o.requires
thread/test/CMakeFiles/threadTest.dir/requires: thread/test/CMakeFiles/threadTest.dir/gtest_Thread.cpp.o.requires
thread/test/CMakeFiles/threadTest.dir/requires: thread/test/CMakeFiles/threadTest.dir/gtest_Timer.cpp.o.requires
.PHONY : thread/test/CMakeFiles/threadTest.dir/requires

thread/test/CMakeFiles/threadTest.dir/clean:
	cd /home/andre/workspace/eadcel_2536/jni/iva/thread/test && $(CMAKE_COMMAND) -P CMakeFiles/threadTest.dir/cmake_clean.cmake
.PHONY : thread/test/CMakeFiles/threadTest.dir/clean

thread/test/CMakeFiles/threadTest.dir/depend:
	cd /home/andre/workspace/eadcel_2536/jni/iva && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andre/workspace/eadcel_2536/jni/iva /home/andre/workspace/eadcel_2536/jni/iva/thread/test /home/andre/workspace/eadcel_2536/jni/iva /home/andre/workspace/eadcel_2536/jni/iva/thread/test /home/andre/workspace/eadcel_2536/jni/iva/thread/test/CMakeFiles/threadTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : thread/test/CMakeFiles/threadTest.dir/depend

