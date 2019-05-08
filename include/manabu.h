#ifndef _MANABU_H_
#define _MANABU_H_

/*! \mainpage libmanabu Portable Low-Level Client Package
 *
 * \section intro_sec Introduction
 *
 * libmanabu provides a full set of tools to access and operate GAKU Engine 
 * servers through the API. Please see the README.md file for more 
 * information including build instructions. libmanabu is hosted on 
 * github at https://github.com/GAKUEngine/libmanabu .
 *
 * \subsection License
 *
 * libmanabu and all official GAKU Engine and Manabu components are dual 
 * licensed under the GNU GPL v3 and AGPL v3. For alternative licenses please 
 * contact info@phantom.industries .
 *  
 *****************************************************************************/

#include "manabu/transactor.h"
#include "manabu/authenticator.h"

#include "manabu/student.h"

#include <string>
using namespace std;

#define GAKU_API_VERSION 1

namespace Manabu {
	class Manabu {
		private:

		public:
		//! Transactor that is used to perform transactions with the server
		Transactor *transactor;
		//! Authenticator that is used to authenticate the user and maintain the session
		Authenticator *authenticator;

		static const uint8_t apiVersion;

		Manabu();
		~Manabu();

		bool connect(const string api_protocol = "http", const string api_host = "localhost", unsigned int api_port = 9000, const string api_prefix = "api/v1/");
		bool authenticate(const string username, const string password);

	}; // class Manabu
} // namespace Manabu

#endif /* _MANABU_H_ */
