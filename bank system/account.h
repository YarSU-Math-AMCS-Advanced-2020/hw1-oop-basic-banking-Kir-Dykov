#pragma once

#include <string>
#include "fixedpoint.h"

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

	FixedPoint balance;

	FixedPoint transfer_limit;

	Account(Client* _client, Currency _currency, FixedPoint _transfer_limit, int _id);

	void print_account_information();
};
