#ifndef DKRAKCANCELDELDELIVERYORDERSTMT_HPP_
#define DKRAKCANCELDELDELIVERYORDERSTMT_HPP_

#include "dkrakstatement.hpp"

class DKRAKCancelDelelayedDeliveryOrderStmt: public DKRAKStatement
{
public:
	DKRAKCancelDelelayedDeliveryOrderStmt();
	~DKRAKCancelDelelayedDeliveryOrderStmt();

	void SetDateTo(const nDate& date);
	void SetRabateChainEnabled( bool chainEnabled );
};

#endif /* DKRAKCANCELDELDELIVERYORDERSTMT_HPP_ */
