#pragma once
#include "account.h"
#include "card.h"
#include "fixedpoint.h"

class Transaction
{
	Account* from;
	Account* to;
	FixedPoint amount;
	FixedPoint transfer_limit;

public:
	string status;

	Transaction(Account* from_, Account* to_, FixedPoint amount_);
	Transaction(Card* from_, Card* to_, FixedPoint amount_);
	Transaction(Card* from_, Account* to_, FixedPoint amount_);
	Transaction(Account* from_, Card* to_, FixedPoint amount_);

	string make_transaction();

	bool is_correct();
};

