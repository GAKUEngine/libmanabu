#include "student.h"

Manabu::Student::Student(Transactor *transactor)
	: id(ID_NULL)
{
	this->transactor = transactor;
	gender = UNKNOWN; // default to UNKNOWN (nil/?), not FEMALE (0/FALSE)
}


Manabu::Student::Student(Transactor *transactor, string surname, string name, unsigned int birthYear, unsigned int birthMonth, unsigned int birthDay, gender_t gender)
	: id(ID_NULL)
{
	this->transactor = transactor;

	this->surname = surname;
	this->name = name;
	this->birthYear = birthYear;
	this->birthMonth = birthMonth;
	this->birthDay = birthDay;
	this->gender = gender;
}

const std::unordered_map<std::string, std::string> Manabu::Student::toQuery() const
{
	return {
		{"surname", surname},
		{"name", name},
		{"middle_name", middleName},
		{"surname_reading", surnameReading},
		{"name_reading", nameReading},
		{"middle_name_reading", middleNameReading},
		{"birth_date", std::to_string(birthYear) + "-" + std::to_string(birthMonth) + "-" + std::to_string(birthDay)},
		{"gender", std::to_string(gender)},
		{"enrollment_status_code", enrollment_status_code},
		// {"picture", picture},
	};
}
#include <iostream>
bool Manabu::Student::save(bool force)
{
	// TODO Implements force. (?)

	const bool update = (force && id != ID_NULL);

	// Save student.
	const std::string res = update
		? transactor->PATCH("students/" + std::to_string(id), toQuery())
		: transactor->POST("students", toQuery());

	// Check error.
	const msgpack::object_handle moh = msgpack::unpack(res.data(), res.size());
	const msgpack::object mo = moh.get();
	if(			mo.type != msgpack::type::MAP
			||	mo.via.map.size == 0
			||	mo.via.map.ptr[0].key.as<std::string>().compare("error") == 0	)
		return false;

	// Copy id when initiale save.
	if(!update)
	{
		const auto m = mo.as<std::unordered_map<std::string, msgpack::object>>();
		id = m.at("id").as<unsigned int>();
	}

	return true;
}

bool Manabu::Student::remove()
{
	if(id == ID_NULL)
		return false;

	const std::string endpoint = "students/" + std::to_string(id);
	const std::string res = transactor->DELETE(endpoint);

	// Check error.
	const msgpack::object_handle moh = msgpack::unpack(res.data(), res.size());
	const msgpack::object mo = moh.get();
	if(			mo.type != msgpack::type::MAP
			||	mo.via.map.size == 0
			||	mo.via.map.ptr[0].key.as<std::string>().compare("error") == 0	)
		return false;

	return true;
}
