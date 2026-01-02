#ifndef DKRAKRELEASECHANGESTMT_HPP_
#define DKRAKRELEASECHANGESTMT_HPP_

#include "dkrakstatement.hpp"

class DKRAKReleaseChangeStmt: public DKRAKStatement
{
public:
	DKRAKReleaseChangeStmt();
	~DKRAKReleaseChangeStmt();

	void SetDateTo( const nDate& date );
	void SetRabateChainEnabled( bool chainEnabled );
};

#endif /* DKRAKRELEASECHANGESTMT_HPP_ */
