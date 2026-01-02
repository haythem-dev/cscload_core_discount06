#ifndef DKRAKRELEASESTMT_HPP_
#define DKRAKRELEASESTMT_HPP_

#include "dkrakstatement.hpp"

class DKRAKReleaseStmt: public DKRAKStatement
{
public:
	DKRAKReleaseStmt();
	~DKRAKReleaseStmt();

	void SetDateTo(const nDate& date);
};

#endif /* DKRAKRELEASESTMT_HPP_ */
