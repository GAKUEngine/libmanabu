cmake_minimum_required(VERSION 3.12)

if(BUILD_TESTS)
	project(LIBMANABU_TEST)

	find_package(Boost COMPONENTS
		unit_test_framework REQUIRED)
	include_directories(
		${Boost_INCLUDE_DIRS}
		${PROJECT_BINARY_DIR}
		${PROJECT_SOURCE_DIR}../src
	)

	add_executable(libmanabu_spec
		${PROJECT_SOURCE_DIR}/libmanabu_spec.cpp
	)
	target_link_libraries(libmanabu_spec
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
		manabu
	)

	enable_testing()
	add_test(
		NAME libmanabu_spec
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMAND libmanabu_spec
	)
endif(BUILD_TESTS)
