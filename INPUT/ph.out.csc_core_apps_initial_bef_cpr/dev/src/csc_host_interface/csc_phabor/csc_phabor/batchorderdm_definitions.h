//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Bjoern Bischof
 *  \date       23.12.2010
 *  \version    00.00.00.01
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_BATCHORDERHEADDM_DEFINITIONS
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_BATCHORDERHEADDM_DEFINITIONS

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//

namespace domMod
{
    namespace batchOrder
    {
        namespace processing
		{
			namespace batchOrderDM
			{
				static basar::ConstString STATUS_OPEN		 ( "O" );
			    static basar::ConstString STATUS_IN_PROCESS	 ( "I" );
			    static basar::ConstString STATUS_CLOSED		 ( "C" );
			}
        }
    }
}

#endif
