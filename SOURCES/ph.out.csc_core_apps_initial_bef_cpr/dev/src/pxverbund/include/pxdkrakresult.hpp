#ifndef PXDKRAKRESULT_INC
#define PXDKRAKRESULT_INC

#include "string.hpp"

class pxDkrakResult
{

public:

// constructors:
                      pxDkrakResult(char*  buffer);

// destructor:
    virtual           ~pxDkrakResult();

// public member operators
    pxDkrakResult&    operator=(const pxDkrakResult& src);

// public member functions
	short      BranchNo();
	long       CustomerNo();
	nString     InvoiceNumber();
	nString     VoucherType();
	nString     DocumentNo();
	long       LfdNr();
	double    InvoiceAmountPaid();
	double    NormalBalance();
	long       DueDate();
	long       LastPaymentDate();
	long       LockCount();

// Queries:

protected:
                      pxDkrakResult();

          char*      ResultBuffer_;
private:
};
#endif
