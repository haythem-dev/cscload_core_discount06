//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief
*   \author 
*   \date   
*/
//-------------------------------------------------------------------------------------------//

#ifndef GUARD_TRANSFERFROMZDPUC_H
#define GUARD_TRANSFERFROMZDPUC_H

//-------------------------------------------------------------------------------------------//

#include "transferbaseuc.h"
#include "ctransfercscdmptr.h"

//-------------------------------------------------------------------------------------------//

namespace csc_phatra {
namespace useCase {

//-------------------------------------------------------------------------------------------//

class TransferFromZDPUC  : public TransferBaseUC
{
public:
	TransferFromZDPUC();
	virtual ~TransferFromZDPUC();

	void injectCTransferCscDMPtr(domMod::pharmosTransaction::preparation::CTransferCscDMPtr cTransferCscDM);

protected:
	virtual basar::appl::EventReturnStruct doRun();
	virtual void doCheckInjections() const;

private:
	domMod::pharmosTransaction::preparation::CTransferCscDMPtr	m_cTransferCscDM;
};

//-------------------------------------------------------------------------------------------//

typedef boost::shared_ptr<TransferFromZDPUC> TransferFromZDPUCPtr;

//-------------------------------------------------------------------------------------------//

} //namespace useCase
}//namespace csc_phatra

//-------------------------------------------------------------------------------------------//

#endif // GUARD_TRANSFERFROMZDPUC_H

//-------------------------------------------------------------------------------------------//
