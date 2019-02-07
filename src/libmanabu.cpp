#include "libmanabu.h"

#include <iostream>
using namespace std;

const uint8_t Manabu::Manabu::apiVersion = GAKU_API_VERSION;

Manabu::Manabu::Manabu()
{
}

Manabu::Manabu::~Manabu()
{
}

bool Manabu::Manabu::connect(const string protocol, const string host, unsigned int port, const string prefix)
{
	this->transactor = new Transactor(protocol, host, port, prefix);
	string status = this->transactor->GET("status");
	
	msgpack::object_handle moh = msgpack::unpack(status.data(), status.size());
	msgpack::object mo = moh.get();
	unordered_map<string, string> statusMap = mo.as<unordered_map<string, string>>();

	// Check the status map for if the server is running normally ["running"]
	string statusString = statusMap.at("status");
	if (statusString.compare("running") == 0) {
		return true; // Server is running normally, transactor us usable
	} // TODO: deal with other statuses as appropriate

	return false; // There was a problem obtaining a functional transactor connection to the server
}

bool Manabu::Manabu::authenticate(const string username, const string password)
{
	// Check that the transactor is valid
	if (transactor == NULL)
		return false;

	authenticator = new Authenticator(username, password, this->transactor);
	return authenticator->authenticated;
}
