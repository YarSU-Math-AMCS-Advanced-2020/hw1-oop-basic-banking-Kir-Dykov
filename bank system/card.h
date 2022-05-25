#pragma once

#include <string>
#include <ctime>
#include "fixedpoint.h"

class Card;
#include "account.h"

using namespace std;

enum class PaymentSystem {Lisa, MasterBart, HoMiR};

class Card {
public:
	int id;
	Account * account; // TODO get rid of "recursive dependance"
	FixedPoint transfer_limit;
	PaymentSystem payment_system;

	Card(int _id, Account* _account, PaymentSystem _payment_system);
};