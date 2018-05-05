cmake_minimum_required(VERSION 3.2)

project (TradeParser LANGUAGES CXX)
set (TARGET TradeParser)

set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# TradeParser version
#
set(TradeParser_VERSION_MAJOR 1)
set(TradeParser_VERSION_MINOR 0)
set(TradeParser_VERSION_PATCH 0)
set(TradeParser_VERSION ${TradeParser_VERSION_MAJOR}.${TradeParser_VERSION_MINOR}.${TradeParser_VERSION_PATCH})
MESSAGE (STATUS "Version is ${TradeParser_VERSION}")

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set (CMAKE_BUILD_TYPE Release 
         CACHE STRING "Choose the type of build : None Debug Release RelWithDebInfo MinSizeRel Coverage."
         FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif(NOT CMAKE_BUILD_TYPE)
message(STATUS "Build Type is ${CMAKE_BUILD_TYPE}")

# OPTIONS
#
option(TradeParser_USE_GTEST "Use GTest (fixme turn off if you want to install)" ON)
option(TradeParser_USE_BENCHMARK "Use Benchmark (fixme turn off if you want to install)" ON)


# Guard against in-source builds and bad build-type strings
#
include(ConfigSafeGuards)
include(ConfigGitRevision)

# Set c++ compiler flags for GNU
#
if((CMAKE_CXX_COMPILER_ID MATCHES GNU) OR (CMAKE_CXX_COMPILER_ID MATCHES Clang))
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -Wconversion -Wall -Wextra -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()


set (CMAKE_INSTALL_PREFIX ./${TradeParser_VERSION}/${CMAKE_BUILD_TYPE})

#include modules
include(ConfigCppCheck)
include(ConfigClangFormat)
include(ConfigClangTidy)
include(InstallRequiredSystemLibraries)


#include packages
find_package(cppcheck REQUIRED)
find_package(clang-format REQUIRED)
find_package(clang-tidy REQUIRED)
find_package(Doxygen REQUIRED)


# TradeParser testing framework (gtest)
#
if(${TradeParser_USE_GTEST})
    include(CTest)
    find_package(GTest REQUIRED)
    enable_testing()
    add_subdirectory(${CMAKE_SOURCE_DIR}/test/)
endif()

# TradeParser benchmark framework (gbenchmark)
#
if (${TradeParser_USE_BENCHMARK})
    find_package(GBenchmark REQUIRED)
    add_subdirectory(benchmark)
endif()

add_subdirectory(doc/doxygen)


include_directories(${CMAKE_SOURCE_DIR}/include
)
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${CMAKE_MODULE_PATH}/version_hpp.in"
  "${CMAKE_SOURCE_DIR}/include/version.hpp"
  )

file (GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
#link_directories( )
add_executable(TradeParser ${SOURCES})
target_link_libraries(${TARGET})

INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION include
        COMPONENT headers FILES_MATCHING PATTERN "*.hpp")
INSTALL(TARGETS TradeParser DESTINATION bin COMPONENT applications)

SET(CPACK_PACKAGE_DESCRIPTION "${CMAKE_PROJECT_NAME}")
SET(CPACK_PACKAGE_VERSION_MAJOR "${TradeParser_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${TradeParser_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${TradeParser_VERSION_PATCH}")
SET(CPACK_PACKAGE_VENDOR "Vinit")
SET(CPACK_PACKAGE_CONTACT "vineetmhapsekar@yahoo.co.in")
SET(CPACK_GENERATOR "TGZ")
SET(CPACK_SOURCE_GENERATOR "TGZ")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "${CMAKE_INSTALL_PREFIX}")
SET(CPACK_SOURCE_IGNORE_FILES "build")
SET(CPACK_STRIP_FILES "bin/TradeParser")
SET(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${TradeParser_VERSION}")
SET(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_SOURCE_DIR}/build;TradeParser;ALL;/;"
                        "${CMAKE_SOURCE_DIR}/build;benchmark;ALL;/"
                        "${CMAKE_SOURCE_DIR}/build;test;ALL;/")
SET(CPACK_SET_DESTDIR ON)
include (CPack)


