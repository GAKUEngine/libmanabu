#include "authenticator.h"

#include <iostream>
#include <chrono>
using namespace std;

Manabu::Authenticator::Authenticator(Transactor *transactor, const string username, const string password)
	: refreshThread(NULL)
{
	bool responseSucceeded = false;

	this->authenticated = false;

	if (transactor == NULL)
		return;

	this->transactor = transactor;
	responseSucceeded = handleAuthResponse(
			this->transactor->POST("authenticate", {{"username", username}, {"password", password}}));

	this->authenticated = responseSucceeded;
}

void Manabu::Authenticator::refreshThreadMonitor(unsigned int timeout, Manabu::Authenticator *authObj)
{
	this_thread::sleep_for(chrono::minutes(timeout));
	authObj->refreshAuth();
}

bool Manabu::Authenticator::handleAuthResponse(const string response)
{
	msgpack::object_handle moh = msgpack::unpack(response.data(), response.size());
	msgpack::object mo = moh.get();

	// Check for auth failure/errors
	if(	mo.type != msgpack::type::MAP
		||	mo.via.map.size == 0
		||	mo.via.map.ptr[0].key.as<std::string>().compare("error") == 0	)
		return false;

	TokenContainer tokenContainer = mo.as<TokenContainer>();
	this->username = username;
	this->authToken = tokenContainer.at("tokens").at("auth_token");
	this->refreshToken = tokenContainer.at("tokens").at("refresh_token");
	//this->authTokenTimeout = tokenContainer.at("tokens").at("auth_token_timeout");
	//this->refreshTokenTimeout = tokenContainer.at("tokens").at("refresh_token_timeout");

	updateTransactorAuthToken();

	// Start a refresh thread to automatically refresh the auth token
	if (this->refreshThread != NULL) // stop existing thread if one is active
		this->refreshThread->join();

	this->refreshThread = new thread(Manabu::Authenticator::refreshThreadMonitor, this->authTokenTimeout - 1, this);

	return true;
}

void Manabu::Authenticator::updateTransactorAuthToken()
{
	this->transactor->setAuthToken(this->authToken);
}

bool Manabu::Authenticator::refreshAuth()
{
	return handleAuthResponse(
		this->transactor->POST("authenticate/renew", {{"refresh_token", this->refreshToken}}));
}
