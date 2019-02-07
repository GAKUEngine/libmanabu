cmake_minimum_required(VERSION 3.12)

find_program(CMAKE_C_COMPILER NAMES $ENV{CC} gcc PATHS ENV PATH NO_DEFAULT_PATH)
find_program(CMAKE_CXX_COMPILER NAMES $ENV{CXX} g++ PATHS ENV PATH NO_DEFAULT_PATH)

project(libmanabu CXX)

# Generate version header
set(MANABU_LIB_VERSION_MAJOR 0)
set(MANABU_LIB_VERSION_MINOR 1)
set(MANABU_LIB_VERSION_PATCH 0)
set(MANABU_LIB_VERSION "${MANABU_LIB_VERSION_MAJOR}.${MANABU_LIB_VERSION_MINOR}.${MANABU_LIB_VERSION_PATCH}")
configure_file(${PROJECT_SOURCE_DIR}/src/version.h.in ${PROJECT_SOURCE_DIR}/src/version.h @ONLY)

set(BUILD_TESTS true)
set(BUILD_DYNAMIC true)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${LIBMANABU_INCLUDE_DIRS})

# Generate dynamic library
find_package(Boost REQUIRED
	system
	filesystem
	date_time
	)
find_package(OpenSSL)
find_package(CURL)

set(LIBMANABU_DYNAMIC_LIB_TARGET manabu)
set(LIBMANABU_CXX_FILES
	${PROJECT_SOURCE_DIR}/src/libmanabu.cpp
	${PROJECT_SOURCE_DIR}/src/manabu/transactor.cpp
	${PROJECT_SOURCE_DIR}/src/manabu/authenticator.cpp
)

set(LIBMANABU_LINK_LIBRARIES
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
	${Boost_DATE_TIME_LIBRARY}
	${OPENSSL_LIBRARIES}
	${CURL_LIBRARIES}
	msgpackc
)

if(BUILD_DYNAMIC)
  add_library(${LIBMANABU_DYNAMIC_LIB_TARGET} SHARED ${LIBMANABU_CXX_FILES})
  target_link_libraries(${LIBMANABU_DYNAMIC_LIB_TARGET} ${LIBMANABU_LINK_LIBRARIES})
  set_target_properties(${LIBMANABU_DYNAMIC_LIB_TARGET}
    PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE
  )
endif(BUILD_DYNAMIC)

# Specs
add_subdirectory(${PROJECT_SOURCE_DIR}/spec)
enable_testing()

# Generate static library
set(MANABU_STATIC_LIB_TARGET static)
set(STATIC_LIB_NAME libmanabu_static)

add_library(${MANABU_STATIC_LIB_TARGET} ${LIBMANABU_CXX_FILES})
target_link_libraries(${MANABU_STATIC_LIB_TARGET} ${LIBMANABU_LINK_LIBRARIES})

set_target_properties(${MANABU_STATIC_LIB_TARGET}
	PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
	OUTPUT_NAME ${STATIC_LIB_NAME}
)
