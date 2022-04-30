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

int Bank::open_account(int client_id, Currency currency, int transfer_limit)
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

bool Bank::transaction_between_accounts(int debit_id, int credit_id, int amount) {
	Account* debit = account_by_id(debit_id);
	if (debit == nullptr) return false;

	Account* credit = account_by_id(credit_id);
	if (credit == nullptr) return false;

	if (debit->currency != credit->currency)
		return false;

	if (debit->balance < amount || debit->transfer_limit < amount) {
		return false;
	}

	debit->balance -= amount;
	credit->balance += amount;

	return true;
}

bool Bank::transaction_between_cards(int debit_card_id, int credit_card_id, int amount) {

	Card* debit_card = card_by_id(debit_card_id);

	if (debit_card == nullptr) 
		return false;

	Card* credit_card = card_by_id(credit_card_id);

	if (credit_card == nullptr) 
		return false;


	if (debit_card->account->currency != credit_card->account->currency)
		return false;
	if (debit_card->account->balance < amount || debit_card->transfer_limit < amount)
		return false;
	
	debit_card->account->balance -= amount;
	credit_card->account->balance += amount;

	return true;
}

bool Bank::close_account_with_transaction(int account_id, int credit_id) {

	Account* account = account_by_id(account_id);

	if (account == nullptr) 
		return false;

	Account* credit = account_by_id(credit_id);

	if (credit == nullptr) 
		return false;

	if (account->currency != credit->currency)
		return false;

	credit->balance += account->balance;

	if (account->card != nullptr)
		close_card(account->card->id);
	
	accounts.erase(find(accounts.begin(),accounts.end(),account));
	delete account;

	return true;
}

bool Bank::close_account_with_cash(int account_id) {

	Account* account = account_by_id(account_id);

	if (account == nullptr) 
		return false;

	if (account->card != nullptr)
		close_card(account->card->id);
	
	accounts.erase(find(accounts.begin(), accounts.end(), account));
	delete account;

	return true;
}

int Bank::open_card(int account_id, PaymentSystem payment_system)
{
	Account* account = account_by_id(account_id);
	if (account == nullptr) 
		return 0;

	if (account->card != nullptr) 
		return 0;

	int id;

	do { id = rand(); } 
	while (id == 0 || card_by_id(id) != nullptr);

	Card* card = new Card(id, account, payment_system);
	account->card = card;
	cards.push_back(card);

	return id;
}

bool Bank::close_card(int card_id)
{
	Card* card = card_by_id(card_id);
	if (card == nullptr) 
		return false;

	card->account->card = nullptr;
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

	if (account->card != nullptr) 
		return false;

	card->account->card = nullptr;
	account->card = card;
	card->account = account;

	return true;
}

bool Bank::update_account_transfer_limit(int account_id, int new_limit) {
	Account* account = account_by_id(account_id);

	if (account == nullptr) 
		return false;

	account->transfer_limit = new_limit;

	return true;
}

bool Bank::update_card_transfer_limit(int card_id, int new_limit) {

	Card* card = card_by_id(card_id);

	if (card == nullptr) 
		return false;

	card->transfer_limit = new_limit;

	return true;
}

bool Bank::cash_in(int account_id, int amount) {

	Account* account = account_by_id(account_id);

	if (account == nullptr) 
		return false;

	account->balance += amount;

	return true;
}

bool Bank::cash_out(int account_id, int amount) {

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