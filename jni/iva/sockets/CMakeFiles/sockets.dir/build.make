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
include sockets/CMakeFiles/sockets.dir/depend.make

# Include the progress variables for this target.
include sockets/CMakeFiles/sockets.dir/progress.make

# Include the compile flags for this target's objects.
include sockets/CMakeFiles/sockets.dir/flags.make

sockets/CMakeFiles/sockets.dir/Igmp.cpp.o: sockets/CMakeFiles/sockets.dir/flags.make
sockets/CMakeFiles/sockets.dir/Igmp.cpp.o: sockets/Igmp.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object sockets/CMakeFiles/sockets.dir/Igmp.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sockets.dir/Igmp.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/sockets/Igmp.cpp

sockets/CMakeFiles/sockets.dir/Igmp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sockets.dir/Igmp.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/sockets/Igmp.cpp > CMakeFiles/sockets.dir/Igmp.cpp.i

sockets/CMakeFiles/sockets.dir/Igmp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sockets.dir/Igmp.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/sockets/Igmp.cpp -o CMakeFiles/sockets.dir/Igmp.cpp.s

sockets/CMakeFiles/sockets.dir/Igmp.cpp.o.requires:
.PHONY : sockets/CMakeFiles/sockets.dir/Igmp.cpp.o.requires

sockets/CMakeFiles/sockets.dir/Igmp.cpp.o.provides: sockets/CMakeFiles/sockets.dir/Igmp.cpp.o.requires
	$(MAKE) -f sockets/CMakeFiles/sockets.dir/build.make sockets/CMakeFiles/sockets.dir/Igmp.cpp.o.provides.build
.PHONY : sockets/CMakeFiles/sockets.dir/Igmp.cpp.o.provides

sockets/CMakeFiles/sockets.dir/Igmp.cpp.o.provides.build: sockets/CMakeFiles/sockets.dir/Igmp.cpp.o
.PHONY : sockets/CMakeFiles/sockets.dir/Igmp.cpp.o.provides.build

sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.o: sockets/CMakeFiles/sockets.dir/flags.make
sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.o: sockets/IgmpSender.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sockets.dir/IgmpSender.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/sockets/IgmpSender.cpp

sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sockets.dir/IgmpSender.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/sockets/IgmpSender.cpp > CMakeFiles/sockets.dir/IgmpSender.cpp.i

sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sockets.dir/IgmpSender.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/sockets/IgmpSender.cpp -o CMakeFiles/sockets.dir/IgmpSender.cpp.s

sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.o.requires:
.PHONY : sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.o.requires

sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.o.provides: sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.o.requires
	$(MAKE) -f sockets/CMakeFiles/sockets.dir/build.make sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.o.provides.build
.PHONY : sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.o.provides

sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.o.provides.build: sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.o
.PHONY : sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.o.provides.build

sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.o: sockets/CMakeFiles/sockets.dir/flags.make
sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.o: sockets/IgmpPcap.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sockets.dir/IgmpPcap.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/sockets/IgmpPcap.cpp

sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sockets.dir/IgmpPcap.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/sockets/IgmpPcap.cpp > CMakeFiles/sockets.dir/IgmpPcap.cpp.i

sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sockets.dir/IgmpPcap.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/sockets/IgmpPcap.cpp -o CMakeFiles/sockets.dir/IgmpPcap.cpp.s

sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.o.requires:
.PHONY : sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.o.requires

sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.o.provides: sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.o.requires
	$(MAKE) -f sockets/CMakeFiles/sockets.dir/build.make sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.o.provides.build
.PHONY : sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.o.provides

sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.o.provides.build: sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.o
.PHONY : sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.o.provides.build

sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o: sockets/CMakeFiles/sockets.dir/flags.make
sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o: sockets/NetworkInformation_linux.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/sockets/NetworkInformation_linux.cpp

sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/sockets/NetworkInformation_linux.cpp > CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.i

sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/sockets/NetworkInformation_linux.cpp -o CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.s

sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o.requires:
.PHONY : sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o.requires

sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o.provides: sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o.requires
	$(MAKE) -f sockets/CMakeFiles/sockets.dir/build.make sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o.provides.build
.PHONY : sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o.provides

sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o.provides.build: sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o
.PHONY : sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o.provides.build

sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.o: sockets/CMakeFiles/sockets.dir/flags.make
sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.o: sockets/NetworkInformation.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sockets.dir/NetworkInformation.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/sockets/NetworkInformation.cpp

sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sockets.dir/NetworkInformation.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/sockets/NetworkInformation.cpp > CMakeFiles/sockets.dir/NetworkInformation.cpp.i

sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sockets.dir/NetworkInformation.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/sockets/NetworkInformation.cpp -o CMakeFiles/sockets.dir/NetworkInformation.cpp.s

sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.o.requires:
.PHONY : sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.o.requires

sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.o.provides: sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.o.requires
	$(MAKE) -f sockets/CMakeFiles/sockets.dir/build.make sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.o.provides.build
.PHONY : sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.o.provides

sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.o.provides.build: sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.o
.PHONY : sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.o.provides.build

sockets/CMakeFiles/sockets.dir/Socket.cpp.o: sockets/CMakeFiles/sockets.dir/flags.make
sockets/CMakeFiles/sockets.dir/Socket.cpp.o: sockets/Socket.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object sockets/CMakeFiles/sockets.dir/Socket.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sockets.dir/Socket.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/sockets/Socket.cpp

sockets/CMakeFiles/sockets.dir/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sockets.dir/Socket.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/sockets/Socket.cpp > CMakeFiles/sockets.dir/Socket.cpp.i

sockets/CMakeFiles/sockets.dir/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sockets.dir/Socket.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/sockets/Socket.cpp -o CMakeFiles/sockets.dir/Socket.cpp.s

sockets/CMakeFiles/sockets.dir/Socket.cpp.o.requires:
.PHONY : sockets/CMakeFiles/sockets.dir/Socket.cpp.o.requires

sockets/CMakeFiles/sockets.dir/Socket.cpp.o.provides: sockets/CMakeFiles/sockets.dir/Socket.cpp.o.requires
	$(MAKE) -f sockets/CMakeFiles/sockets.dir/build.make sockets/CMakeFiles/sockets.dir/Socket.cpp.o.provides.build
.PHONY : sockets/CMakeFiles/sockets.dir/Socket.cpp.o.provides

sockets/CMakeFiles/sockets.dir/Socket.cpp.o.provides.build: sockets/CMakeFiles/sockets.dir/Socket.cpp.o
.PHONY : sockets/CMakeFiles/sockets.dir/Socket.cpp.o.provides.build

sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.o: sockets/CMakeFiles/sockets.dir/flags.make
sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.o: sockets/SocketCtx.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sockets.dir/SocketCtx.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketCtx.cpp

sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sockets.dir/SocketCtx.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketCtx.cpp > CMakeFiles/sockets.dir/SocketCtx.cpp.i

sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sockets.dir/SocketCtx.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketCtx.cpp -o CMakeFiles/sockets.dir/SocketCtx.cpp.s

sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.o.requires:
.PHONY : sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.o.requires

sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.o.provides: sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.o.requires
	$(MAKE) -f sockets/CMakeFiles/sockets.dir/build.make sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.o.provides.build
.PHONY : sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.o.provides

sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.o.provides.build: sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.o
.PHONY : sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.o.provides.build

sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.o: sockets/CMakeFiles/sockets.dir/flags.make
sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.o: sockets/SocketRaw.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sockets.dir/SocketRaw.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketRaw.cpp

sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sockets.dir/SocketRaw.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketRaw.cpp > CMakeFiles/sockets.dir/SocketRaw.cpp.i

sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sockets.dir/SocketRaw.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketRaw.cpp -o CMakeFiles/sockets.dir/SocketRaw.cpp.s

sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.o.requires:
.PHONY : sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.o.requires

sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.o.provides: sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.o.requires
	$(MAKE) -f sockets/CMakeFiles/sockets.dir/build.make sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.o.provides.build
.PHONY : sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.o.provides

sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.o.provides.build: sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.o
.PHONY : sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.o.provides.build

sockets/CMakeFiles/sockets.dir/SocketException.cpp.o: sockets/CMakeFiles/sockets.dir/flags.make
sockets/CMakeFiles/sockets.dir/SocketException.cpp.o: sockets/SocketException.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object sockets/CMakeFiles/sockets.dir/SocketException.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sockets.dir/SocketException.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketException.cpp

sockets/CMakeFiles/sockets.dir/SocketException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sockets.dir/SocketException.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketException.cpp > CMakeFiles/sockets.dir/SocketException.cpp.i

sockets/CMakeFiles/sockets.dir/SocketException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sockets.dir/SocketException.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketException.cpp -o CMakeFiles/sockets.dir/SocketException.cpp.s

sockets/CMakeFiles/sockets.dir/SocketException.cpp.o.requires:
.PHONY : sockets/CMakeFiles/sockets.dir/SocketException.cpp.o.requires

sockets/CMakeFiles/sockets.dir/SocketException.cpp.o.provides: sockets/CMakeFiles/sockets.dir/SocketException.cpp.o.requires
	$(MAKE) -f sockets/CMakeFiles/sockets.dir/build.make sockets/CMakeFiles/sockets.dir/SocketException.cpp.o.provides.build
.PHONY : sockets/CMakeFiles/sockets.dir/SocketException.cpp.o.provides

sockets/CMakeFiles/sockets.dir/SocketException.cpp.o.provides.build: sockets/CMakeFiles/sockets.dir/SocketException.cpp.o
.PHONY : sockets/CMakeFiles/sockets.dir/SocketException.cpp.o.provides.build

sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.o: sockets/CMakeFiles/sockets.dir/flags.make
sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.o: sockets/SocketTCP.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sockets.dir/SocketTCP.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketTCP.cpp

sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sockets.dir/SocketTCP.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketTCP.cpp > CMakeFiles/sockets.dir/SocketTCP.cpp.i

sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sockets.dir/SocketTCP.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketTCP.cpp -o CMakeFiles/sockets.dir/SocketTCP.cpp.s

sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.o.requires:
.PHONY : sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.o.requires

sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.o.provides: sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.o.requires
	$(MAKE) -f sockets/CMakeFiles/sockets.dir/build.make sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.o.provides.build
.PHONY : sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.o.provides

sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.o.provides.build: sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.o
.PHONY : sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.o.provides.build

sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.o: sockets/CMakeFiles/sockets.dir/flags.make
sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.o: sockets/SocketUDP.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sockets.dir/SocketUDP.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketUDP.cpp

sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sockets.dir/SocketUDP.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketUDP.cpp > CMakeFiles/sockets.dir/SocketUDP.cpp.i

sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sockets.dir/SocketUDP.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketUDP.cpp -o CMakeFiles/sockets.dir/SocketUDP.cpp.s

sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.o.requires:
.PHONY : sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.o.requires

sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.o.provides: sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.o.requires
	$(MAKE) -f sockets/CMakeFiles/sockets.dir/build.make sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.o.provides.build
.PHONY : sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.o.provides

sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.o.provides.build: sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.o
.PHONY : sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.o.provides.build

sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.o: sockets/CMakeFiles/sockets.dir/flags.make
sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.o: sockets/SocketWrapper.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andre/workspace/eadcel_2536/jni/iva/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.o"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sockets.dir/SocketWrapper.cpp.o -c /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketWrapper.cpp

sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sockets.dir/SocketWrapper.cpp.i"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketWrapper.cpp > CMakeFiles/sockets.dir/SocketWrapper.cpp.i

sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sockets.dir/SocketWrapper.cpp.s"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andre/workspace/eadcel_2536/jni/iva/sockets/SocketWrapper.cpp -o CMakeFiles/sockets.dir/SocketWrapper.cpp.s

sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.o.requires:
.PHONY : sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.o.requires

sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.o.provides: sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.o.requires
	$(MAKE) -f sockets/CMakeFiles/sockets.dir/build.make sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.o.provides.build
.PHONY : sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.o.provides

sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.o.provides.build: sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.o
.PHONY : sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.o.provides.build

# Object files for target sockets
sockets_OBJECTS = \
"CMakeFiles/sockets.dir/Igmp.cpp.o" \
"CMakeFiles/sockets.dir/IgmpSender.cpp.o" \
"CMakeFiles/sockets.dir/IgmpPcap.cpp.o" \
"CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o" \
"CMakeFiles/sockets.dir/NetworkInformation.cpp.o" \
"CMakeFiles/sockets.dir/Socket.cpp.o" \
"CMakeFiles/sockets.dir/SocketCtx.cpp.o" \
"CMakeFiles/sockets.dir/SocketRaw.cpp.o" \
"CMakeFiles/sockets.dir/SocketException.cpp.o" \
"CMakeFiles/sockets.dir/SocketTCP.cpp.o" \
"CMakeFiles/sockets.dir/SocketUDP.cpp.o" \
"CMakeFiles/sockets.dir/SocketWrapper.cpp.o"

# External object files for target sockets
sockets_EXTERNAL_OBJECTS =

sockets/libsockets.a: sockets/CMakeFiles/sockets.dir/Igmp.cpp.o
sockets/libsockets.a: sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.o
sockets/libsockets.a: sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.o
sockets/libsockets.a: sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o
sockets/libsockets.a: sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.o
sockets/libsockets.a: sockets/CMakeFiles/sockets.dir/Socket.cpp.o
sockets/libsockets.a: sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.o
sockets/libsockets.a: sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.o
sockets/libsockets.a: sockets/CMakeFiles/sockets.dir/SocketException.cpp.o
sockets/libsockets.a: sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.o
sockets/libsockets.a: sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.o
sockets/libsockets.a: sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.o
sockets/libsockets.a: sockets/CMakeFiles/sockets.dir/build.make
sockets/libsockets.a: sockets/CMakeFiles/sockets.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libsockets.a"
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && $(CMAKE_COMMAND) -P CMakeFiles/sockets.dir/cmake_clean_target.cmake
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sockets.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sockets/CMakeFiles/sockets.dir/build: sockets/libsockets.a
.PHONY : sockets/CMakeFiles/sockets.dir/build

sockets/CMakeFiles/sockets.dir/requires: sockets/CMakeFiles/sockets.dir/Igmp.cpp.o.requires
sockets/CMakeFiles/sockets.dir/requires: sockets/CMakeFiles/sockets.dir/IgmpSender.cpp.o.requires
sockets/CMakeFiles/sockets.dir/requires: sockets/CMakeFiles/sockets.dir/IgmpPcap.cpp.o.requires
sockets/CMakeFiles/sockets.dir/requires: sockets/CMakeFiles/sockets.dir/NetworkInformation_linux.cpp.o.requires
sockets/CMakeFiles/sockets.dir/requires: sockets/CMakeFiles/sockets.dir/NetworkInformation.cpp.o.requires
sockets/CMakeFiles/sockets.dir/requires: sockets/CMakeFiles/sockets.dir/Socket.cpp.o.requires
sockets/CMakeFiles/sockets.dir/requires: sockets/CMakeFiles/sockets.dir/SocketCtx.cpp.o.requires
sockets/CMakeFiles/sockets.dir/requires: sockets/CMakeFiles/sockets.dir/SocketRaw.cpp.o.requires
sockets/CMakeFiles/sockets.dir/requires: sockets/CMakeFiles/sockets.dir/SocketException.cpp.o.requires
sockets/CMakeFiles/sockets.dir/requires: sockets/CMakeFiles/sockets.dir/SocketTCP.cpp.o.requires
sockets/CMakeFiles/sockets.dir/requires: sockets/CMakeFiles/sockets.dir/SocketUDP.cpp.o.requires
sockets/CMakeFiles/sockets.dir/requires: sockets/CMakeFiles/sockets.dir/SocketWrapper.cpp.o.requires
.PHONY : sockets/CMakeFiles/sockets.dir/requires

sockets/CMakeFiles/sockets.dir/clean:
	cd /home/andre/workspace/eadcel_2536/jni/iva/sockets && $(CMAKE_COMMAND) -P CMakeFiles/sockets.dir/cmake_clean.cmake
.PHONY : sockets/CMakeFiles/sockets.dir/clean

sockets/CMakeFiles/sockets.dir/depend:
	cd /home/andre/workspace/eadcel_2536/jni/iva && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andre/workspace/eadcel_2536/jni/iva /home/andre/workspace/eadcel_2536/jni/iva/sockets /home/andre/workspace/eadcel_2536/jni/iva /home/andre/workspace/eadcel_2536/jni/iva/sockets /home/andre/workspace/eadcel_2536/jni/iva/sockets/CMakeFiles/sockets.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sockets/CMakeFiles/sockets.dir/depend

