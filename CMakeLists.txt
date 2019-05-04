cmake_minimum_required(VERSION 3.10)

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

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${LIBMANABU_INCLUDE_DIRS})

if(MSYS)
	if(EXISTS ${PROJECT_SOURCE_DIR}/opt/boost)
		set(BOOST_ROOT ${PROJECT_SOURCE_DIR}/opt/boost/)
	elseif(EXISTS ${PROJECT_SOURCE_DIR}/../boost)
		set(BOOST_ROOT ${PROJECT_SOURCE_DIR}/../boost/)
	endif()
	#set(BOOST_INCLUDEDIR /mingw64/include/)
	#set(BOOST_LIBDIR /mingw64/lib/)
	#set(BOOST_ROOT /mingw64/)
	include_directories(AFTER /mingw64/include/)
	link_directories(AFTER /mingw64/lib/)
endif(MSYS)

# Generate dynamic library
find_package(Boost REQUIRED
	system
	filesystem
	date_time
	)
find_package(OpenSSL)
find_package(CURL)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(LIB_NAME manabu)

set(LIBMANABU_DYNAMIC_LIB_TARGET manabu)
set(LIBMANABU_CXX_FILES
	${PROJECT_SOURCE_DIR}/src/manabu.cpp
	${PROJECT_SOURCE_DIR}/src/manabu/transactor.cpp
	${PROJECT_SOURCE_DIR}/src/manabu/authenticator.cpp
	${PROJECT_SOURCE_DIR}/src/manabu/student.cpp
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
	OUTPUT_NAME ${LIB_NAME}
  )
endif(BUILD_DYNAMIC)

# Specs
add_subdirectory(${PROJECT_SOURCE_DIR}/spec)
enable_testing()

# Generate static library
set(MANABU_STATIC_LIB_TARGET manabu_static)

add_library(${MANABU_STATIC_LIB_TARGET} ${LIBMANABU_CXX_FILES})
target_link_libraries(${MANABU_STATIC_LIB_TARGET} ${LIBMANABU_LINK_LIBRARIES})

set_target_properties(${MANABU_STATIC_LIB_TARGET}
	PROPERTIES
	POSITION_INDEPENDENT_CODE TRUE
	OUTPUT_NAME ${LIB_NAME}
)

install(
	#	TARGETS libmanabu libmanabu_static
#
#    cmake/libmanabuConfig.cmake
#    ${CMAKE_CURRENT_BINARY_DIR}/lib/libmanabu.so
#	DESTINATION
#    ${ConfigPackageLocation}
)
