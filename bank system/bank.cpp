#include <iostream>
#include <vector>
#include <random>

#include "bank.h"
#include "account.h"

using namespace std;

Bank::Bank() {}

Bank& Bank::get() {
	if (self == NULL)
		self = new Bank();
	return *self;
}

int Bank::register_client(Client* new_client) {
	if (client_by_passport(new_client->passport) != nullptr )
		return 0;

	int id;

	do { id = rand(); } while (client_by_id(id) != nullptr);
	new_client->id = id;
	clients.push_back(new_client);

	return id;
}

bool Bank::update_client_information(int client_id, Client* new_client) {

	Client* client = client_by_id(client_id);
	if (client == nullptr || client->client_type != new_client->client_type)
		return false;
	
	new_client->id = client_id;

	if (client->client_type == ClientType::Person)
		*(Person*)client = *(Person*)new_client;
	else
		*(LegalEntity*)client = *(LegalEntity*)new_client;
	
	return true;
}

Client* Bank::client_by_id(int id) {
	auto it = find_if(clients.begin(), clients.end(), 
		[&id](const Client* client) 
		{return client->id == id; });
	if (it == clients.end())
		return nullptr;
	else
		return *it;
}

Client* Bank::client_by_passport(string passport) {
	auto it = find_if(clients.begin(), clients.end(), 
		[&passport](const Client* client) 
		{return client->passport == passport; });
	if (it == clients.end())
		return nullptr;
	else
		return *it;
}

Account* Bank::account_by_id(int id) {
	auto it = find_if(accounts.begin(), accounts.end(),
		[&id](const Account* account)
		{return account->id == id; });
	if (it == accounts.end())
		return nullptr;
	else
		return *it;
};

Card* Bank::card_by_id(int id) {
	auto it = find_if(cards.begin(), cards.end(),
		[&id](const Card* card)
		{return card->id == id; });
	if (it == cards.end())
		return nullptr;
	else
		return *it;
}

Card* Bank::card_by_account(Account* account) {
	auto it = find_if(cards.begin(), cards.end(),
		[&account](const Card* card)
		{return card->account == account; });
	if (it == cards.end())
		return nullptr;
	else
		return *it;
}

int Bank::open_account(int client_id, Currency currency, FixedPoint transfer_limit)
{
	Client* client = client_by_id(client_id);
	if (client == nullptr) 
		return false;

	int id;

	do { id = rand(); } 
	while (id == 0 || account_by_id(id) != nullptr);

	accounts.push_back(new Account(client, currency, transfer_limit, id));
	return id;
};


string Bank::close_account_with_transaction(int account_id, int credit_id) {



	Account* account = account_by_id(account_id);

	if (account == nullptr) 
		return "debit account is not regestired";

	Account* credit = account_by_id(credit_id);

	if (credit == nullptr) 
		return "credit account is not regestired";

	account->transfer_limit = FixedPoint(0, 0);

	string status = Transaction(account, credit, account->balance).make_transaction();
	if (status != "sucsess") {
		return status;
	}

	Card* card = card_by_account(account);
	if (card != nullptr)
		close_card(card->id);
	accounts.erase(find(accounts.begin(),accounts.end(),account));
	delete account;

	return status;
}

int Bank::open_card(int account_id, PaymentSystem payment_system)
{
	Account* account = account_by_id(account_id);
	if (account == nullptr) 
		return 0;

	int id;

	do { id = rand(); } 
	while (id == 0 || card_by_id(id) != nullptr);

	Card* card = new Card(id, account, payment_system);
	cards.push_back(card);

	return id;
}

bool Bank::close_card(int card_id)
{
	Card* card = card_by_id(card_id);
	if (card == nullptr) 
		return false;

	cards.erase(find(cards.begin(), cards.end(), card));
	delete card;

	return false;
}

bool Bank::change_card_account(int card_id, int account_id)
{
	Account* account = account_by_id(account_id);
	if (account == nullptr) 
		return false;

	Card* card = card_by_id(card_id);

	if (card == nullptr) 
		return false;

	card->account = account;

	return true;
}

bool Bank::update_account_transfer_limit(int account_id, FixedPoint new_limit) {
	Account* account = account_by_id(account_id);

	if (account == nullptr) 
		return false;

	account->transfer_limit = new_limit;

	return true;
}

bool Bank::update_card_transfer_limit(int card_id, FixedPoint new_limit) {

	Card* card = card_by_id(card_id);

	if (card == nullptr) 
		return false;

	card->transfer_limit = new_limit;

	return true;
}

bool Bank::cash_in(int account_id, FixedPoint amount) {

	Account* account = account_by_id(account_id);

	if (account == nullptr) 
		return false;

	account->balance += amount;

	return true;
}

bool Bank::cash_out(int account_id, FixedPoint amount) {

	Account* account = account_by_id(account_id);

	if (account == nullptr) 
		return false;

	if (account->balance < amount || account->transfer_limit < amount)
		return false;

	account->balance -= amount;

	return true;
}

void Bank::print_client_info(int client_id) {

	Client* client = client_by_id(client_id);

	if (client == nullptr) 
		cout << "Client not found." << endl << endl;
	else
		client->print_all_information();
};

void Bank::print_account_info(int account_id) {

	Account* account = account_by_id(account_id);

	if (account == nullptr)
		cout << "Account not found." << endl << endl;
	else
		account->print_account_information();
};

Bank* Bank::self = NULL;