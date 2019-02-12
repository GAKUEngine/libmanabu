#include "student.h"

Manabu::Student::Student(Transactor *transactor)
{
	this->transactor = transactor;
	gender = UNKNOWN; // default to UNKNOWN (nil/?), not FEMALE (0/FALSE)
}


Manabu::Student::Student(Transactor *transactor, string surname, string name, unsigned int birthYear, unsigned int birthMonth, unsigned int birthDay, gender_t gender)
{
	this->transactor = transactor;

	this->surname = surname;
	this->name = name;
	this->birthYear = birthYear;
	this->birthMonth = birthMonth;
	this->birthDay = birthDay;
	this->gender = gender;
}

bool Manabu::Student::save(bool force)
{
	// TODO save to server
	return false;
}
