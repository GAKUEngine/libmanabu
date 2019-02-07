#ifndef _MANABU_AUTHENTICATOR_H_
#define _MANABU_AUTHENTICATOR_H_

#include "transactor.h"

#include <string>
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
		string auth_token;
		string refresh_token;


		public:
		bool authenticated;
		Authenticator(const string username, const string password, Transactor *activeTransactor);

		void updateTransactorAuth();
	};
}

#endif /* _MANABU_AUTHENTICATOR_H_ */
