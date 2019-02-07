#include <libmanabu.h>

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
		BOOST_CHECK_EQUAL(manabu.connect("http", "localhost", 9000), true);
	}

	// Check that the [test] admin user can authenticate
	BOOST_AUTO_TEST_CASE(auth_status) {
		Manabu::Manabu manabu = Manabu::Manabu();
		manabu.connect("http", "localhost", 9000);
		BOOST_CHECK_EQUAL(manabu.authenticate("admin", "123456"), true);
	}
BOOST_AUTO_TEST_SUITE_END()
