#include <iostream>
#include "bank.h"
#include "transaction.h"
#include "fixedpoint.h"

using namespace std;

int main() {

	Bank bank = Bank::get();

	//register clients
	cout << "\n\n\n* \t\t register clients \t\t *\n\n\n";
	int client1 = bank.register_client(new Person(
		"Yakubiv", 
		"Yulia", 
		"Andreevna", 
		Date({ 10,04,2002 }), 
		"8(123)456-78-90", 
		"2727 272727"));
	int client2 = bank.register_client(new Person(
		"Bain", 
		"Danila", 
		"Denisovich", 
		Date({ 26,07,2002 }), 
		"8(980)65-44-222", 
		"7676 767676"));
	int client3 = bank.register_client(new LegalEntity(
		"Macdonalds", 
		Date({ 12,12,2012 }), 
		"<Address>", 
		"12345678901234"));

	//prints information about every client here
	bank.print_client_info(client1);
	bank.print_client_info(client2);
	bank.print_client_info(client3);

	//open accounts
	cout << "\n\n\n* \t\t open accounts \t\t *\n\n\n";
	int account1 = bank.open_account(client1, Currency::ruble, FixedPoint(10000, 0));
	int account2 = bank.open_account(client2, Currency::ruble, FixedPoint(5000, 0));

	//???????? ?????? ? ????????? ?? ?????? ????
	bank.cash_in(account1, FixedPoint(40000, 0));
	bank.cash_in(account2, FixedPoint(30000, 0));

	//	 print account information
	bank.print_account_info(account1);
	bank.print_account_info(account2);

/// transactions
	cout << "\n\n\n* \t\t transactions \t\t *\n\n\n";	

	// transaction : account1 -> account2
	cout << Transaction(bank.account_by_id(account1), 
		bank.account_by_id(account2), 
		FixedPoint(7000, 0)
	).make_transaction() << endl;
	cout << endl << "transaction: " << 7000 
		<< " from " << account1 << " to " << account2 << endl << endl;

	//	 print account information
	bank.print_account_info(account1);
	bank.print_account_info(account2);

	// transaction : account1 -> account2
	cout << Transaction(bank.account_by_id(account1),
		bank.account_by_id(account2),
		FixedPoint(10000, 0)
	).make_transaction() << endl;
	cout << endl << "transaction: " << 10000 
		<< " from " << account1 << " to " << account2 << endl << endl;

	//	 print account information
	bank.print_account_info(account1);
	bank.print_account_info(account2);

	// transaction : account1 -> account2
	cout << Transaction(bank.account_by_id(account1),
		bank.account_by_id(account2),
		FixedPoint(10001, 0)
	).make_transaction() << endl;
	cout << endl << "transaction: " << 10001 
		<< " from " << account1 << " to " << account2 << endl << endl;

	//	 print account information
	bank.print_account_info(account1);
	bank.print_account_info(account2);

	bank.cash_out(account2, FixedPoint(1000, 0));
	cout << endl << "cash out: " << 1000 << " from " << account2 << endl << endl;

	//	 print account information
	bank.print_account_info(account2);

	bank.cash_out(account2, FixedPoint(6000, 0));
	cout << endl << "cash out: " << 6000 << " from " << account2 << endl << endl;

	//	 print account information
	bank.print_account_info(account2);

/// update client information scenario:
	cout << "\n\n\n* \t\t updating client info \t\t *\n\n\n";
	cout << "BEFORE:" << endl;
	bank.print_client_info(client3);

	Client* changed_client = new LegalEntity(
			"Uncle Vanya", 
			Date({ 12,12,2012 }), 
			"<Address>", 
			"12345678901234");

	bank.update_client_information(client3, changed_client);
	delete changed_client;

	cout << "AFTER:" << endl;
	bank.print_client_info(client3);

/// cards
	cout << "\n\n\n* \t\t cards \t\t *\n\n\n";

	int card1 = bank.open_card(account1, PaymentSystem::HoMiR);
	int card2 = bank.open_card(account2, PaymentSystem::Lisa);

	//	 print account information
	bank.print_account_info(account1);
	bank.print_account_info(account2);

	//   transaction : card2 -> card1
	cout << Transaction(bank.card_by_id(card2),
		bank.account_by_id(card1),
		FixedPoint(10000, 0)
	).make_transaction() << endl;
	cout << endl << "card transaction: " << 10000 
		<< " from " << account1 << " to " << account2 << endl << endl;

	//	 print account information
	bank.print_account_info(account1);
	bank.print_account_info(account2);

	cout << endl << "close card for " << account2 << endl << endl;
	bank.close_card(card2);

	//	 print account information
	bank.print_account_info(account1);
	bank.print_account_info(account2);

	cout << endl << "change card1 account from " << account1 
		<< " to " << account2 << endl << endl;
	bank.change_card_account(card1, account2);

	//	 print account information
	bank.print_account_info(account1);
	bank.print_account_info(account2);

/// update transfer limit scenario:
	cout << "\n\n\n* \t\t updating transfer limit \t\t *\n\n\n";
	bank.print_account_info(account2);
	bank.update_account_transfer_limit(account2, FixedPoint(15000, 0));
	cout << "Set account transfer limit to 15000" << endl << endl;
	bank.print_account_info(account2);
	bank.update_card_transfer_limit(card1, FixedPoint(7000, 0));
	cout << "Set card transfer limit to 7000" << endl << endl;
	bank.print_account_info(account2);

/// close account scenario:
	cout << "\n\n\n* \t\t closing accounts \t\t *\n\n\n";
	//	 print account information
	bank.print_account_info(account1);
	bank.print_account_info(account2);

	bank.close_account_with_transaction(account1, account2);
	cout << "Closing account number " << account1 
		<< " using transaction..." << endl << endl;

	//	 print account information
	bank.print_account_info(account1);
	bank.print_account_info(account2);

	return 0;
}
