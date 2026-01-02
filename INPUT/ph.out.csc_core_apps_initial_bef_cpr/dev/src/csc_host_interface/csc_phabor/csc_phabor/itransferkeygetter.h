//-------------------------------------------------------------------------------------------------//
/*! \file itransferkeygetter.h
 *  \brief 
 *  \author Julian Machata
 *  \date 29.06.2012
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_UTIL_ITRANSFER_KEY_GETTER_H
#define GUARD_UTIL_ITRANSFER_KEY_GETTER_H


//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace util
{
	class ITransferKeyGetter
    {
        public:	
            virtual ~ITransferKeyGetter(){};
			virtual basar::Int32 getLastKey( const basar::Int16 branchno ) = 0;
    };

}
}
} // end namespace util

//----------------------------------------------------------------------------
#endif //GUARD_UTIL_ITRANSACTION_KEY_GETTER_H
