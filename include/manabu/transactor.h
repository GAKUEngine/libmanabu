#ifndef _MANABU_TRANSACTOR_H_
#define _MANABU_TRANSACTOR_H_

#include <msgpack.hpp>

#include <string>
#include <unordered_map>
using namespace std;

namespace Manabu
{
	//! Performs transactions with a GAKU server through the standard API
	class Transactor
	{
	private:
		// ↓↓↓Internal Sub-Helpers↓↓↓
		//! Convert a character to hex for URL encoding
		string hex(unsigned int c); 
		//! Convert a string to an encoded URL
		string url_encode(const string& str);
		// ↑↑↑Internal Sub-Helpers↑↑↑

		// ↓↓↓Internal Helpers↓↓↓
		//! Generate a query string from an unordered_map of arguments
		string generateQueryString(const unordered_map<string, string>& query);
		//! Generate an HTTP request from an unordered_map (optionally; set a specific HTTP status code to check for)
		string request(const string& requestname, const string& endpoint, const unordered_map<string, string>& query, int* status);
		//! Generate an HTTP request from a string (optionally; set a specific HTTP status code to check for)
		string request(const string& requestname, const string& endpoint, const string& query, int* status);
		// ↑↑↑Internal Helpers↑↑↑

		//! If an Authenticator is active the credentials will be updated dynamically
		string authToken;
		bool authTokenSet;

	protected:
		string protocol;
		string host;
		unsigned int port;
		string prefix;
		bool connectionActive;

	public:
		//! Initialize the Transactor with a connection to a server
		Transactor(const string protocol = "http", const string host = "localhost", unsigned int port = 9000, const string prefix = "api/v1");

		//! Get a blanked query hash instance
		unordered_map<string, string> queryTemplate(bool defaults = true);

		//! HTTP(S) Get with a query hash
		string GET(const string& endpoint, const unordered_map<string, string>& query = {{"", ""}}, int* status = NULL);
		//! Post with a query hash
		string POST(const string& endpoint, const unordered_map<string, string>& query = {{"", ""}}, int* status = NULL);
		//! Delete with a query hash
		string DELETE(const string& endpoint, const unordered_map<string, string>& query = {{"", ""}}, int* status = NULL);
		//! Patch with a query hash
		string PATCH(const string& endpoint, const unordered_map<string, string>& query = {{"", ""}}, int* status = NULL);

		//! Set the auth_token value and sets the authTokenSet flag to true
		//! (!) This is usually not called by hand - an Authenticator will usually call this automatically.
		void setAuthToken(const string token);
		//! Clears the auth_token and sets the authTokenSet flag to false
		void clearAuthToken();
	};
}

#endif // _MANABU_TRANSACTOR_H_
