#ifndef DKRAKBOOKORDERVALUESTMT_HPP_
#define DKRAKBOOKORDERVALUESTMT_HPP_

#include "dkrakstatement.hpp"

class DKRAKBookOrderValueStmt: public DKRAKStatement
{
public:
	DKRAKBookOrderValueStmt();
	~DKRAKBookOrderValueStmt();

	void SetDateTo(const nDate& date);
	void SetRabateChainEnabled( bool chainEnabled );
	void SetSplittOrderNo( long orderNo );
	void SetOrderValueGross( const nMoney& orderValue );
	void SetOrderValueNet( const nMoney& orderValue );
};

#endif /* DKRAKBOOKORDERVALUESTMT_HPP_ */
