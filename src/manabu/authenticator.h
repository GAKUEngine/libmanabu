#ifndef _MANABU_AUTHENTICATOR_H_
#define _MANABU_AUTHENTICATOR_H_

#include "transactor.h"

#include <string>
#include <thread>
using namespace std;


namespace Manabu
{
	//! Authenticates a user on a GAKU server and maintains an active authentication token
	class Authenticator
	{
		private:
		Transactor *transactor;
		typedef unordered_map<string, string> Tokens;
		typedef unordered_map<string, Tokens> TokenContainer;
		Tokens *tokens;

		string username;
		string authToken;
		unsigned int authTokenTimeout;
		string refreshToken;
		unsigned int refreshTokenTimeout;

		bool handleAuthResponse(const string response);
		void updateTransactorAuthToken();

		thread *refreshThread;
		static void refreshThreadMonitor(unsigned int timeout, Manabu::Authenticator *authObj);

		public:
		bool authenticated;
		Authenticator(Transactor *transactor, const string username, const string password);
		~Authenticator();

		bool refreshAuth();
	};
}

#endif /* _MANABU_AUTHENTICATOR_H_ */
