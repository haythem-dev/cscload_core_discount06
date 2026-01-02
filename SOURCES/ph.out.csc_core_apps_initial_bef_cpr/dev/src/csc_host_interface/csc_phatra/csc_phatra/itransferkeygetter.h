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
// forward declaration section
//----------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
        }
    }
}

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace util
{
	class ITransferKeyGetter
    {
        public:	
            virtual ~ITransferKeyGetter(){};
			virtual basar::Int32 getLastKey() = 0;
    };

}
}
} // end namespace util

//----------------------------------------------------------------------------
#endif //GUARD_UTIL_ITRANSACTION_KEY_GETTER_H

