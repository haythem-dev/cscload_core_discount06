#ifndef DKRAKLOCKSTMT_HPP_
#define DKRAKLOCKSTMT_HPP_

#include "dkrakstatement.hpp"

class DKRAKLockStmt: public DKRAKStatement
{
public:
	DKRAKLockStmt();
	~DKRAKLockStmt();

	void SetDateTo( const nDate& date );
	void SetRabateChainEnabled( bool chainEnabled );

	// overwritten method from base class to set additional information
	void SetOrderNo( long orderNo );
};

#endif /* DKRAKLOCKSTMT_HPP_ */
