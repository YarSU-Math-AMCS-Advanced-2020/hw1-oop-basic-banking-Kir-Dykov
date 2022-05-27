#include "transaction.h"

Transaction::Transaction(Account* from_, Account* to_, FixedPoint amount_){
	transfer_limit = from_->transfer_limit;
	from = from_;
	to = to_;
	amount = amount_;
	status = "formed";
}

Transaction::Transaction(Card* from_, Card* to_, FixedPoint amount_){
	transfer_limit = from_->transfer_limit;
	from = from_->account;
	to = to_->account;
	amount = amount_;
	status = "formed";
}

Transaction::Transaction(Card* from_, Account* to_, FixedPoint amount_){
	transfer_limit = from_->transfer_limit;
	from = from_->account;
	to = to_;
	amount = amount_;
	status = "formed";
}

Transaction::Transaction(Account* from_, Card* to_, FixedPoint amount_){
	transfer_limit = from_->transfer_limit;
	from = from_;
	to = to_->account;
	amount = amount_;
	status = "formed";
}

string Transaction::make_transaction() {
	if (is_correct()) {
		from->balance -= amount;
		from->balance += amount;
		status = "sucsess";
	}
	return status;
}

bool Transaction::is_correct()
{
	if (from->currency != to->currency) {
		status = "curriencies are not the same";
		return false;
	}
	if (from->balance < amount) {
		status = "not enough means to commit a transaction";
		return false;
	}
	if (transfer_limit != FixedPoint(0, 0) && from->transfer_limit < amount) {
		status = "transfer limit is exceeded";
		return false;
	}
	return true;
}
