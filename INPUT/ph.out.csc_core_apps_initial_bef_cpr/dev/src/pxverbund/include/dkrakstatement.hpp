#ifndef DKRAKSTATEMENT_H_
#define DKRAKSTATEMENT_H_

#include <cstddef>  // size_t

// forward declarations
class nMoney;
class nString;
class nDate;
struct VI52_page;

class DKRAKStatement
{
public:
	DKRAKStatement();
	virtual ~DKRAKStatement();

	virtual void SetBranchNo(   short branchno );
	virtual void SetCustomerNo( long customerNo );
	virtual void SetDateFrom(   const nDate& date );
	virtual void SetOrderNo(    long orderNo );

	nString ToString();

protected:
	char*             StatementBuffer_;
	struct VI52_page*  VK52;

	void InitBuf(   void* position, size_t length );
	void CopyToBuf( char* position, long           source, size_t length );
	void CopyToBuf( char* position, const nMoney&  source, size_t length );
	void CopyToBuf( char* position, const nString& source, size_t length );
};

#endif /* DKRAKSTATEMENT_H_ */
