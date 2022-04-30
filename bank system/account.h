#pragma once

#include <string>
#include "client.h"

class Account;
#include "card.h"

using namespace std;

enum class Currency {ruble, dollar, euro};

class Account {
public:
	Client* client;
	int id=0;
	Currency currency;

	int balance; // TODO fixed_point class

	int transfer_limit;

	Card* card = nullptr;

	Account(Client* _client, Currency _currency, int _transfer_limit, int _id);

	void print_account_information();
};
