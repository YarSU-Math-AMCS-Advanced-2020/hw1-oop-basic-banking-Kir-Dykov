#pragma once

#include <vector>
#include "account.h"
#include "client.h"
#include "card.h"

#include <iostream>
using namespace std;


class Bank {
	static Bank* self;

	vector<Account*> accounts;

	vector<Client*> clients;

	vector<Card*> cards;

	Bank();

public:
	// First call creates and returns an object of class Bank
	// Further calls return this object
	static Bank& get();

	// registers client in bank, returns client's id used to find a client in database
	int register_client(Client* new_client);

	// creates now account, 
	// returns account id or 0 in case of any error
	int open_account(int client_id, Currency currency, int transfer_limit);

	// returns 0 in cases of incorrect id
	// if account had a card, it closes too.
	bool close_account_with_transaction(int account_id, int credit_id);
	bool close_account_with_cash(int account_id);

	int open_card(int account_id, PaymentSystem payment_system);
	bool close_card(int card_id);

	bool change_card_account(int card_id, int account_id);

	// changes information, returns 0 if id is not correct
	bool update_client_information(int client_id, Client* new_client);
	bool update_account_transfer_limit(int account_id, int new_limit);
	bool update_card_transfer_limit(int card_id, int new_limit);

private:
	Client* client_by_id(int id);

	Client* client_by_passport(string passport);

	Account* account_by_id(int id);

	Card* card_by_id(int id);

public:
	// following functions return 1 if transaction was successful, 0 otherwise

	bool transaction_between_accounts(int debit_id, int credit_id, int amount);
	bool transaction_between_cards(int debit_card_id, int credit_card_id, int amount);
	bool cash_in(int client_id, int amount);

	bool cash_out(int client_id, int amount);



	void print_client_info(int client_id);
	void print_account_info(int account_id);
};

