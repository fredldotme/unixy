cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME unixy)

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)
project(${PROJECT_NAME} VERSION 0.1 LANGUAGES C)

set(NO_SYSTEM_FRAMEWORK "" CACHE STRING "Path containing nosystem.framework")
set(YAML_BUILD_SHARED_LIBS OFF)
set(YAML_CPP_BUILD_TOOLS OFF)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-cxa-atexit")

add_library(${PROJECT_NAME}
    SHARED

    unixy.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

find_library(NOSYSTEM REQUIRED NAMES nosystem PATHS ${NO_SYSTEM_FRAMEWORK} CMAKE_FIND_ROOT_PATH_BOTH)
message("NOSYSTEM: ${NOSYSTEM}")

include_directories(${PROJECT_NAME}
    ${NOSYSTEM}/Headers
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${NOSYSTEM}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    FRAMEWORK TRUE
    MACOSX_FRAMEWORK_IDENTIFIER me.fredl.unixy
    MACOSX_FRAMEWORK_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${PROJECT_VERSION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    XCODE_ATTRIBUTE_SKIP_INSTALL "Yes"
)
