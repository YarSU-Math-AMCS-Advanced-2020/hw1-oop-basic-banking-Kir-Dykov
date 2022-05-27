#pragma once

#include <iostream>
#include <string>
#include "account.h"

using namespace std;

Account::Account(Client* _client, Currency _currency, FixedPoint _transfer_limit, int _id) {
	client = _client;
	currency = _currency;
	transfer_limit = _transfer_limit;
	balance = FixedPoint();
	id = _id;
}

void Account::print_account_information() {
	string currency_strings[] = { "ruble", "dollar", "euro" };
	string payment_system_string[] = { "Lisa", "MasterBart", "HoMiR" };

	cout << "Account: #" << id << endl;
	cout << "Balance: " << balance << " " << currency_strings[int(currency)] << "s" << endl;
	cout << "Transfer limit: " << transfer_limit << endl;
	cout << "Client: #" << client->id << endl;	
	cout << endl;
}
