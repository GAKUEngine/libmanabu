#include "transactor.h"

#include <curl/curl.h>
#include <sstream>
#include <iostream>
using namespace std;

namespace
{
	size_t writeMemoryCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
	{
		const size_t realsize = size * nmemb;
		((string*)userdata)->append(ptr, realsize);
		return realsize;
	}
}

Manabu::Transactor::Transactor(const string protocol, const string host, unsigned int port, const string prefix)
{
	this->protocol = protocol;
	this->host = host;
	this->port = port;
	this->prefix = prefix;
	this->authToken = "";
	this->authTokenSet = false;
}

unordered_map<string, string> Manabu::Transactor::queryTemplate(bool defaults)
{
	unordered_map<string, string> q;

	if (defaults) {
		// TODO add defaults
		/*if (Settings::token != "")
			q["auth_token"] = Settings::token;*/
	}

	return q;
}

string Manabu::Transactor::generateQueryString(const unordered_map<string, string>& query)
{
	std::stringstream buffer;
	msgpack::pack(buffer, query);
	return buffer.str();
}

string Manabu::Transactor::hex(unsigned int c)
{
    std::ostringstream stm ;
    stm << '%' << std::hex << std::uppercase << c ;
    return stm.str() ;
}

string Manabu::Transactor::url_encode(const string& str)
{
    static const string unreserved = "0123456789"
                                            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                            "abcdefghijklmnopqrstuvwxyz"
                                            "-_.~/" ;
    string result ;

    for (unsigned char c : str) {
        if (unreserved.find(c) != string::npos) result += c ;
        else result += hex(c) ;
    }

    return result ;
}

string Manabu::Transactor::request(const string& verb, const string& endpoint, const unordered_map<string, string>& query, int* status)
{
	return this->request(verb, endpoint, generateQueryString(query), status);
}

string Manabu::Transactor::request(const string& verb, const string& endpoint, const string& query, int* status)
{
	CURL *curl;
	CURLcode res;
	string response = "";

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	stringstream url_stream;
	url_stream << this->protocol << "://" << this->host << ":" << to_string(this->port) << "/" << this->prefix << url_encode(endpoint);

	if (curl) {
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "charset: utf-8");
		headers = curl_slist_append(headers, "Content-Type: application/msgpack");
		headers = curl_slist_append(headers, "Accept: application/msgpack");
		if (this->authTokenSet)
			headers = curl_slist_append(headers, ("Authorization: " + this->authToken).c_str());

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libmanabu/1.0");

		curl_easy_setopt(curl, CURLOPT_URL, url_stream.str().c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, verb.c_str());

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)query.length());

		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);


		/*const std::string& CACertPath = Manabu::getCACertPath();
		if	(!CACertPath.empty())
			curl_easy_setopt(curl, CURLOPT_CAINFO, CACertPath.c_str());*/

		// Send it!
		res = curl_easy_perform(curl);

		// Check response
		if(res != CURLE_OK)
		{
			// TODO: handle this in some way other than just a cerr
			cerr << curl_easy_strerror(res) << endl;
		} else
			this->connectionActive = true;

		// Check for a specific status code
		if (status != NULL) {
			// TODO: handle this properly
			res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, status);
		}

		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	return response;
}

string Manabu::Transactor::GET(const string& endpoint, const unordered_map<string, string>& query, int* status)
{
	return request("GET", endpoint, query, status);
}

string Manabu::Transactor::POST(const string& endpoint, const unordered_map<string, string>& query, int* status)
{
	return request("POST", endpoint, query, status);
}

string Manabu::Transactor::DELETE(const string& endpoint, const unordered_map<string, string>& query, int* status)
{
	return request("DELETE", endpoint, query, status);
}

string Manabu::Transactor::PATCH(const string& endpoint, const unordered_map<string, string>& query, int* status)
{
	return request("PATCH", endpoint, query, status);
}

void Manabu::Transactor::setAuthToken(const string token)
{
	this->authToken = token;
	this->authTokenSet = true;
}

void Manabu::Transactor::clearAuthToken()
{
	this->authToken = "";
	this->authTokenSet = false;
}
