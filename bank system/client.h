#pragma once

#include <iostream>
#include <string>
#include <time.h>

using namespace std;

enum class ClientType { GenericClient, Person, LegalEntity };

enum Sex { Male, Female };

struct Date {
	int d = 1;
	int m = 1;
	int y = 2000;
};

class Client {

public:
	ClientType client_type = ClientType::GenericClient;
	int id=0;
	string passport;

	friend bool operator==(Client& const, Client& const);
	
	virtual void print_all_information() {
		cout << "GenericClient" << endl;
		cout << "id:\n\t" << id << endl;
		cout << "passport:\n\t" << passport << endl;
	};

	virtual ~Client() {};
};


class Person : public Client {
	string surname;
	string name;
	string patronymic;
	
	Date birthday;

	string phone_number;
public:
	Person(string _surname,
		string _name,
		string _patronymic,
		Date _birthday,
		string _phone_number,
		string _passport);

	bool has_patronymic() const;

	void print_all_information();
	
};

class LegalEntity : public Client {
	string name;
	Date establishing_date;
	string legal_address;
public:
	LegalEntity(string _name,
				Date _establishing_date,
				string _legal_address,
				string _passport);

	void print_all_information();
};

