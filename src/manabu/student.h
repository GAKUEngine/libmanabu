#ifndef _MANABU_STUDENT_H_
#define _MANABU_STUDENT_H_

#include "transactor.h"
#include "personal_attributes.h"

#include <string>
#include <ctime>
using namespace std;

namespace Manabu
{
	// Student container and interaction
	class Student
	{
		private:
			Transactor *transactor;

			const std::unordered_map<std::string, std::string> toQuery() const;

		public:
			string surname, name, middleName;
			string surnameReading, nameReading, middleNameReading;
			unsigned int birthYear, birthMonth, birthDay;
			gender_t gender;


			Student(Transactor *transactor);
			Student(Transactor *transactor, string surname, string name, unsigned int birthYear, unsigned int birthMonth, unsigned int birthDay, gender_t gender = UNKNOWN);

			//! Save the student to the server (create or update)
			//!	* force: Set to true to force overwrite when a collision is detected during creation 
			bool save(bool force = false);

			bool remove();
	};
}

#endif // _MANABU_STUDENT_H_
