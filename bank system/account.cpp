#pragma once
#include <iostream>
#include <string>

#include "account.h"

using namespace std;

Account::Account(Client* _client, Currency _currency, int _transfer_limit, int _id) {
	client = _client;
	currency = _currency;
	transfer_limit = _transfer_limit;
	balance = 0;
	id = _id;
	card = nullptr;
}

void Account::print_account_information() {
	string currency_strings[] = { "ruble", "dollar", "euro" };
	string payment_system_string[] = { "Lisa", "MasterBart", "HoMiR" };

	cout << "Account: #" << id << endl;
	cout << "Balance: " << balance << " " << currency_strings[int(currency)] << "s" << endl;
	cout << "Transfer limit: " << transfer_limit << endl;
	cout << "Client: #" << client->id << endl;
	if (card == nullptr) {
		cout << "Card: none" << endl;
	} else {
		cout << "Card: " << payment_system_string[int(card->payment_system)] 
			<< " #" << to_string(card->id) << endl;
		cout << "Card transfer limit: " << card->transfer_limit << endl;
	}
	
	cout << endl;
}
