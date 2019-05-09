cmake_minimum_required(VERSION 3.10)

find_program(CMAKE_C_COMPILER NAMES $ENV{CC} gcc PATHS ENV PATH NO_DEFAULT_PATH)
find_program(CMAKE_CXX_COMPILER NAMES $ENV{CXX} g++ PATHS ENV PATH NO_DEFAULT_PATH)

project(libmanabu CXX)

# Generate version header
set(MANABU_LIB_VERSION_MAJOR 0)
set(MANABU_LIB_VERSION_MINOR 1)
set(MANABU_LIB_VERSION_PATCH 0)
set(MANABU_LIB_VERSION "${MANABU_LIB_VERSION_MAJOR}.${MANABU_LIB_VERSION_MINOR}.${MANABU_LIB_VERSION_PATCH}")
configure_file(${PROJECT_SOURCE_DIR}/src/version.h.in ${PROJECT_SOURCE_DIR}/include/manabu/version.h @ONLY)

option(BUILD_TESTS "Build library tests/specs" ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${LIBMANABU_INCLUDE_DIRS})

if(MSYS)
  if(EXISTS ${PROJECT_SOURCE_DIR}/opt/boost)
    set(BOOST_ROOT ${PROJECT_SOURCE_DIR}/opt/boost/)
  elseif(EXISTS ${PROJECT_SOURCE_DIR}/../boost)
    set(BOOST_ROOT ${PROJECT_SOURCE_DIR}/../boost/)
  endif()
  include_directories(AFTER /mingw64/include/)
  link_directories(AFTER /mingw64/lib/)
endif(MSYS)

set(CURL_LIBRARY "-lcurl")

# Generate dynamic library
find_package(Boost REQUIRED
  system
  filesystem
  date_time
)
find_package(OpenSSL)
find_package(CURL)
find_package(msgpack)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(LIB_NAME manabu)

#set(LIBMANABU_DYNAMIC_LIB_TARGET manabu)
set(LIBMANABU_CXX_FILES
  ${PROJECT_SOURCE_DIR}/src/manabu.cpp
  ${PROJECT_SOURCE_DIR}/src/manabu/transactor.cpp
  ${PROJECT_SOURCE_DIR}/src/manabu/authenticator.cpp
  ${PROJECT_SOURCE_DIR}/src/manabu/student.cpp
)

set(LIBMANABU_HEADER_FILES
  ${PROJECT_SOURCE_DIR}/include/manabu.h
  ${PROJECT_SOURCE_DIR}/include/manabu/version.h
  ${PROJECT_SOURCE_DIR}/include/manabu/transactor.h
  ${PROJECT_SOURCE_DIR}/include/manabu/authenticator.h
  ${PROJECT_SOURCE_DIR}/include/manabu/student.h
)

set(LIBMANABU_LINK_LIBRARIES
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_DATE_TIME_LIBRARY}
  ${OPENSSL_LIBRARIES}
  ${CURL_LIBRARIES}
  msgpackc
)

# Generate dynamic library
add_library(manabu SHARED ${LIBMANABU_CXX_FILES})
target_link_libraries(manabu ${LIBMANABU_LINK_LIBRARIES})
target_include_directories(manabu
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
set_target_properties(manabu
  PROPERTIES
  POSITION_INDEPENDENT_CODE TRUE
  OUTPUT_NAME ${LIB_NAME}
  #PUBLIC_HEADER "${LIBMANABU_HEADER_FILES}"
)

# Generate static library
add_library(manabu_static ${LIBMANABU_CXX_FILES})
target_link_libraries(manabu_static ${LIBMANABU_LINK_LIBRARIES})
target_include_directories(manabu_static
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
set_target_properties(manabu_static
  PROPERTIES
  POSITION_INDEPENDENT_CODE TRUE
  OUTPUT_NAME ${LIB_NAME}
  #PUBLIC_HEADER ${LIBMANABU_HEADER_FILES}
)

# Specs
if(${BUILD_TESTS})
  add_subdirectory(${PROJECT_SOURCE_DIR}/spec)
  enable_testing()
endif(${BUILD_TESTS})

# Install Headers
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# Install Libs
install(
  TARGETS manabu manabu_static
  EXPORT ManabuConfig
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  #PUBLIC_HEADER DESTINATION include
)
export(TARGETS
    manabu manabu_static
  FILE "${CMAKE_CURRENT_BINARY_DIR}/ManabuConfig.cmake"
)
include(GNUInstallDirs)
install(EXPORT
  ManabuConfig
  DESTINATION "${CMAKE_INSTALL_DATADIR}/manabu/cmake"
)
