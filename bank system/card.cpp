#include <string>
#include <ctime>

#include "account.h"
#include "card.h"

using namespace std;

Card::Card(int _id, Account* _account, PaymentSystem _payment_system) {
	id = _id;
	account = _account;
	transfer_limit = account->transfer_limit;
	payment_system = _payment_system;
}
