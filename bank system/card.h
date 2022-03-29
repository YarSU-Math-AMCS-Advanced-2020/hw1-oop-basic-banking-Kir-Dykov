#pragma once

#include <string>
#include <ctime>

class Card;
#include "account.h"

using namespace std;

enum class PaymentSystem {Lisa, MasterBart, HoMiR};

class Card {
public:
	int id;
	Account * account;
	int transfer_limit;
	PaymentSystem payment_system;

	Card(int _id, Account* _account, PaymentSystem _payment_system);
};