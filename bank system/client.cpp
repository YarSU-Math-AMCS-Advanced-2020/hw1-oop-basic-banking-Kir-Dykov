#pragma once

#include <string>
#include <time.h>
#include "client.h"

using namespace std;


bool operator==(Client& const a, Client& const b) {
	return a.passport == b.passport;
}

Person::Person(string _surname,
	string _name,
	string _patronymic,
	Date _birthday,
	string _phone_number,
	string _passport)
{
	surname = _surname;
	name = _name;
	patronymic = _patronymic;
	birthday = _birthday;
	phone_number = _phone_number;
	passport = _passport;
	client_type = ClientType::Person;
}

bool Person::has_patronymic() const {
	return patronymic != "";
}

void Person::print_all_information() {
	cout << "Type of client:\n\t\tPerson" << endl;
	cout << "id:\n\t\t" << id << endl;
	cout << "passport:\n\t\t" << passport << endl;
	cout << "full name:\n\t\t" << surname << " " << name << " " << patronymic << endl;
	cout << "birthday:\n\t\t" << birthday.d << "." << birthday.m << "." << birthday.y << endl;
	cout << "phone number:\n\t\t" << phone_number << endl << endl;
};

LegalEntity::LegalEntity(string _name,
	Date _establishing_date,
	string _legal_address,
	string _passport) 
{
	name = _name;
	establishing_date = _establishing_date;
	legal_address = _legal_address;
	passport = _passport;
	client_type = ClientType::LegalEntity;
}
void LegalEntity::print_all_information() {
	cout << "Type of client:\n\t\tLegalEntity" << endl;
	cout << "id:\n\t\t" << id << endl;
	cout << "passport:\n\t\t" << passport << endl;
	cout << "name:\n\t\t" << name << endl;
	cout << "establishing date:\n\t\t" << establishing_date.d
		<< "." << establishing_date.m << "." << establishing_date.y << endl;
	cout << "legal address:\n\t\t" << legal_address << endl << endl;
};

;