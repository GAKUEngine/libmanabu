#include <manabu.h>

#include <stdlib.h>
using namespace std;

#define BOOST_TEST_DYN_LINK 
#define BOOST_TEST_MODULE emojidex_test
#include <boost/test/unit_test.hpp>


///////////////////////////////////////////////////////////////////////////////
// Basic tests
///////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(basic_suite)
	// Check that this client is for version 1 of the api
	BOOST_AUTO_TEST_CASE(api_version) {
		Manabu::Manabu manabu = Manabu::Manabu();
		BOOST_CHECK_EQUAL(manabu.apiVersion, 1);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(connectivity_suite)
	// Check that the [test] server is running
	BOOST_AUTO_TEST_CASE(server_status) {
		Manabu::Manabu manabu = Manabu::Manabu();
		BOOST_CHECK_EQUAL(manabu.connect(), true);
		BOOST_CHECK_EQUAL(manabu.connect("http", "localhost", 9000), true);
	}

	// Check that the [test] admin user can authenticate
	BOOST_AUTO_TEST_CASE(auth_success) {
		Manabu::Manabu manabu = Manabu::Manabu();
		manabu.connect("http", "localhost", 9000);
		BOOST_CHECK_EQUAL(manabu.authenticate("admin", "123456"), true);
	}

	// Check that a bad authentication fails gracefully
	BOOST_AUTO_TEST_CASE(auth_failure) {
		Manabu::Manabu manabu = Manabu::Manabu();
		manabu.connect("http", "localhost", 9000);
		BOOST_CHECK_EQUAL(manabu.authenticate("admin", "9999"), false);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(student_suite)
	// Check that the student
	BOOST_AUTO_TEST_CASE(student_save_update_delete) {
		Manabu::Manabu manabu = Manabu::Manabu();
		manabu.connect("http", "localhost", 9000);
		manabu.authenticate("admin", "123456");

		Manabu::Student student = Manabu::Student(manabu.transactor);
		BOOST_CHECK_EQUAL(student.gender, Manabu::UNKNOWN); // Initial state

		student = Manabu::Student(manabu.transactor, "エンジン", "学", 1999, 9, 1);
		BOOST_CHECK_EQUAL(student.save(), true); // Initial save
		BOOST_CHECK_EQUAL(student.surname, "エンジン");

		student.name = "";
		BOOST_CHECK_EQUAL(student.save(), false); // Validation error

		student.name = "学";
		student.middleName = "Flux";
		BOOST_CHECK_EQUAL(student.save(true), true); // Update
		BOOST_CHECK_EQUAL(student.middleName, "Flux");

		BOOST_CHECK_EQUAL(student.remove(), true); // Remove
	}
BOOST_AUTO_TEST_SUITE_END()
