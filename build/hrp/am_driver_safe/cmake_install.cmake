# Install script for directory: /home/alberto/Documents/catkin_ws/src/hrp/am_driver_safe

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/alberto/Documents/catkin_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/am_driver_safe/srv" TYPE FILE FILES
    "/home/alberto/Documents/catkin_ws/src/hrp/am_driver_safe/srv/TifCmd.srv"
    "/home/alberto/Documents/catkin_ws/src/hrp/am_driver_safe/srv/turnOfLoopCmd.srv"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/am_driver_safe/cmake" TYPE FILE FILES "/home/alberto/Documents/catkin_ws/build/hrp/am_driver_safe/catkin_generated/installspace/am_driver_safe-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/alberto/Documents/catkin_ws/devel/include/am_driver_safe")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/alberto/Documents/catkin_ws/devel/share/roseus/ros/am_driver_safe")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/alberto/Documents/catkin_ws/devel/share/common-lisp/ros/am_driver_safe")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/alberto/Documents/catkin_ws/devel/share/gennodejs/ros/am_driver_safe")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/alberto/Documents/catkin_ws/devel/lib/python2.7/dist-packages/am_driver_safe")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/alberto/Documents/catkin_ws/devel/lib/python2.7/dist-packages/am_driver_safe")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/alberto/Documents/catkin_ws/build/hrp/am_driver_safe/catkin_generated/installspace/am_driver_safe.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/am_driver_safe/cmake" TYPE FILE FILES "/home/alberto/Documents/catkin_ws/build/hrp/am_driver_safe/catkin_generated/installspace/am_driver_safe-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/am_driver_safe/cmake" TYPE FILE FILES
    "/home/alberto/Documents/catkin_ws/build/hrp/am_driver_safe/catkin_generated/installspace/am_driver_safeConfig.cmake"
    "/home/alberto/Documents/catkin_ws/build/hrp/am_driver_safe/catkin_generated/installspace/am_driver_safeConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/am_driver_safe" TYPE FILE FILES "/home/alberto/Documents/catkin_ws/src/hrp/am_driver_safe/package.xml")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/am_driver_safe/am_driver_safe_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/am_driver_safe/am_driver_safe_node")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/am_driver_safe/am_driver_safe_node"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/am_driver_safe" TYPE EXECUTABLE FILES "/home/alberto/Documents/catkin_ws/devel/lib/am_driver_safe/am_driver_safe_node")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/am_driver_safe/am_driver_safe_node" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/am_driver_safe/am_driver_safe_node")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/am_driver_safe/am_driver_safe_node"
         OLD_RPATH "/home/alberto/Documents/catkin_ws/devel/lib:/opt/ros/kinetic/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/am_driver_safe/am_driver_safe_node")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/am_driver_safe" TYPE FILE FILES
    "/home/alberto/Documents/catkin_ws/src/hrp/am_driver_safe/launch/automower.launch"
    "/home/alberto/Documents/catkin_ws/src/hrp/am_driver_safe/launch/automower_hrp.launch"
    "/home/alberto/Documents/catkin_ws/src/hrp/am_driver_safe/launch/el_cheapo.launch"
    "/home/alberto/Documents/catkin_ws/src/hrp/am_driver_safe/launch/automower_rab.launch"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/am_driver_safe/config" TYPE FILE FILES
    "/home/alberto/Documents/catkin_ws/src/hrp/am_driver_safe/config/31.7_Main-App-P2_H585920_161123-152100_Debug.json"
    "/home/alberto/Documents/catkin_ws/src/hrp/am_driver_safe/config/31.7_Main-App-P2_master_build-542_Debug.json"
    "/home/alberto/Documents/catkin_ws/src/hrp/am_driver_safe/config/31.7_Main-App-P2_master_build-609_Debug.json"
    "/home/alberto/Documents/catkin_ws/src/hrp/am_driver_safe/config/31.7_Main-App-P2-Debug_release-10.20.json"
    "/home/alberto/Documents/catkin_ws/src/hrp/am_driver_safe/config/31.7_P2_Main_App-Certified_master_build_285-Debug.json"
    "/home/alberto/Documents/catkin_ws/src/hrp/am_driver_safe/config/31.9_Main-App-P0-Debug_h502899_170904-134048.json"
    "/home/alberto/Documents/catkin_ws/src/hrp/am_driver_safe/config/automower_hrp.json"
    )
endif()

