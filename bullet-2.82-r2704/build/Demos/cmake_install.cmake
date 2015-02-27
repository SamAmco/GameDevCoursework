# Install script for directory: C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/Demos

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/BULLET_PHYSICS")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/HelloWorld/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/OpenGL/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/BasicDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/RaytestDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/FractureDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/Benchmarks/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/Box2dDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/CollisionInterfaceDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/ConcaveDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/ConstraintDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/RollingFrictionDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/ConvexDecompositionDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/InternalEdgeDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/GimpactTestDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/GyroscopicDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/FeatherstoneMultiBodyDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/GenericJointDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/SerializeDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/SoftDemo/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/VectorAdd_OpenCL/cmake_install.cmake")
  include("C:/Users/SamAmco/Documents/Visual Studio 2013/bullet-2.82-r2704/build/Demos/VoronoiFractureDemo/cmake_install.cmake")

endif()

