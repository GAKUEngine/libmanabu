#include "authenticator.h"

#include <iostream>
using namespace std;

Manabu::Authenticator::Authenticator(const string username, const string password, Transactor *activeTransactor)
{
	this->authenticated = false;

	if (activeTransactor == NULL)
		return;

	this->transactor = activeTransactor;
	string response = this->transactor->POST("authenticate", {{"username", username}, {"password", password}});
	// TODO: handle failed authentication

	msgpack::object_handle moh = msgpack::unpack(response.data(), response.size());
	msgpack::object mo = moh.get();
	TokenContainer tokenContainer = mo.as<TokenContainer>();
	this->username = username;
	this->auth_token = tokenContainer.at("tokens").at("auth_token");
	this->refresh_token = tokenContainer.at("tokens").at("refresh_token");

	updateTransactorAuth();

	this->authenticated = true;
}

void Manabu::Authenticator::updateTransactorAuth()
{
	this->transactor->username = this->username;
	this->transactor->auth_token = this->auth_token;
}
