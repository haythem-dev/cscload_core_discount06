//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief
*   \author 
*   \date   
*/
//-------------------------------------------------------------------------------------------//
#ifndef GUARD_TRANSFERTOCSCUC_H
#define GUARD_TRANSFERTOCSCUC_H

//-------------------------------------------------------------------------------------------//

#include "transferbaseuc.h"

//-------------------------------------------------------------------------------------------//

namespace csc_phatra {
namespace useCase {

//-------------------------------------------------------------------------------------------//

class TransferToCscUC : public TransferBaseUC
{
public:
	TransferToCscUC();
	virtual ~TransferToCscUC();

protected:
	virtual basar::appl::EventReturnStruct	doRun();
	virtual void							doCheckInjections() const {}
};

//-------------------------------------------------------------------------------------------//

typedef boost::shared_ptr<TransferToCscUC> TransferToCscUCPtr;

//-------------------------------------------------------------------------------------------//

} //namespace useCase
} //namespace csc_phatra

//-------------------------------------------------------------------------------------------//

#endif // GUARD_TRANSFERTOCSCUC_H

//-------------------------------------------------------------------------------------------//
