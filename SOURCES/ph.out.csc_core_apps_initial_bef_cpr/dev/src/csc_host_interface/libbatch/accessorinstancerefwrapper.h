//---------------------------------------------------------------------------//
/*! \file 
 *  \brief      Wrapper for creation (lazy instantiation), hosting and assembling the accessor instance name of basar::db::aspect::AccessorInstanceRef
 *  \author     Bischof Bjoern
 *  \date       27.10.2012
 *  \version    00.00.00.01 first version
 */ //-----------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_ACCESSOR_INSTANCE_REF_WRAPPER_H
#define GUARD_DOMMOD_ACCESSOR_INSTANCE_REF_WRAPPER_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasardbaspect_accessor.h>
#include <libbasardbaspect_connectionref.h>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace basar
{
	namespace db
	{
		namespace aspect
		{
            class AccessorInstanceRef;
			class ConnectionRef;
//			class AccessorPropertyTable_YIterator;
			class AccessorPropertyTableRef;
		}
	}
}

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
class AccessorInstanceRefWrapper
{
//--------------------------------------------------------------------------------------------------//
// object definition section
//--------------------------------------------------------------------------------------------------//
    public:
        AccessorInstanceRefWrapper( const basar::VarString& accDefName, basar::db::aspect::ConnectionRef conn,
                                    const basar::db::aspect::CachingPolicyEnum eCachePolicy = basar::db::aspect::ON_DEMAND_CACHING,
                                    const bool storeInInstanceList = false );
	    ~AccessorInstanceRefWrapper();
        basar::db::aspect::AccessorInstanceRef          get() const;
        void                                            reset();
		basar::db::aspect::ConnectionRef	            getConnection();
		bool										isNull() const;

    private:
        AccessorInstanceRefWrapper( const AccessorInstanceRefWrapper& );
        const AccessorInstanceRefWrapper& operator=( const AccessorInstanceRefWrapper& );

        void                                            initAccessor() const;
        basar::VarString                          	createAccessorInstanceName() const;

        const basar::VarString                          m_AccessorName;
        basar::db::aspect::ConnectionRef	            m_Connection;
        const basar::db::aspect::CachingPolicyEnum      m_CachePolicyEnum;
        const bool                                      m_StoreInInstanceList;

        //ReturnInitParams                                            m_ReturnInitParams;
	mutable basar::db::aspect::AccessorInstanceRef  m_AccessorInstanceRef;
};

} // end namespace domMod

#endif // GUARD_DOMMOD_ACCESSOR_INSTANCE_REF_WRAPPER_H
