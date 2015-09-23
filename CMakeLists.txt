cmake_minimum_required(VERSION 3.0.0)
project(cmarathon)

# Command line options.
SET(WITH_MESOS "/usr" CACHE STRING "Mesos installation directory")
SET(MESOS_INSTALLATION_DIR ${WITH_MESOS})
MESSAGE("Mesos installation directory set to: " ${MESOS_INSTALLATION_DIR})

OPTION(INTEGRATION_TESTS "Enable compilation of integration tests." OFF)

# Compiler things.
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
    message(STATUS "Error: ${CMAKE_CXX_COMPILER} has no C++11 support")
endif()

# Some libs needs to be compiled position indepenedent.
IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )


# Untar libs.
execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf boost-1.53.0.tar.gz
    COMMAND ${CMAKE_COMMAND} -E tar xzf glog-0.3.3.tar.gz
    COMMAND ${CMAKE_COMMAND} -E tar xzf protobuf-2.5.0.tar.gz
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty
)

execute_process(
    COMMAND ./configure
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glog-0.3.3
)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glog-0.3.3/src)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/boost-1.53.0/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/protobuf-2.5.0/src)


# Add message proto files.
#add_library(messages STATIC ${ProtoSources} ${ProtoHeaders})



link_directories(${MESOS_INSTALLATION_DIR}/lib/)

include_directories(
    ./
    ../
    include/
    ${MESOS_INSTALLATION_DIR}/include
    ${CMAKE_BINARY_DIR}/
)

set(CMARATHON_SOURCES
    src/main.cpp
)

add_executable(cmarathon ${CMARATHON_SOURCES})
target_link_libraries(cmarathon mesos)

