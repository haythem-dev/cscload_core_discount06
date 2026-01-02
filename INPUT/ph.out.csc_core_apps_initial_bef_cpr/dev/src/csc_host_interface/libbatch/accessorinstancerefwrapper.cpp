//---------------------------------------------------------------------------//
/*! \file 
 *  \brief      Wrapper for creation (lazy instantiation), hosting and assembling the accessor instance name of basar::db::aspect::AccessorInstanceRef
 *  \author     Bischof Bjoern
 *  \date       27.10.2012
 *  \version    00.00.00.01 first version
 */ //-----------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "accessorinstancerefwrapper.h"
#include <libbasardbaspect_manager.h>
//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
AccessorInstanceRefWrapper::AccessorInstanceRefWrapper( const basar::VarString& accNameDef, 
                                                        basar::db::aspect::ConnectionRef conn,
                                                        const basar::db::aspect::CachingPolicyEnum eCachePolicy,
                                                        const bool storeInInstanceList )
: m_AccessorName( accNameDef ),
  m_Connection( conn ), 
  m_CachePolicyEnum( eCachePolicy ), 
  m_StoreInInstanceList( storeInInstanceList )
{
}
//--------------------------------------------------------------------------------------------------//
// 
//--------------------------------------------------------------------------------------------------//
AccessorInstanceRefWrapper::~AccessorInstanceRefWrapper()
{
    reset();
}

//--------------------------------------------------------------------------------------------------//
// 
//--------------------------------------------------------------------------------------------------//
bool AccessorInstanceRefWrapper::isNull() const
{
	return m_AccessorInstanceRef.isNull();
}

basar::db::aspect::ConnectionRef AccessorInstanceRefWrapper::getConnection()
{
	return m_Connection;
}

//--------------------------------------------------------------------------------------------------//
// 
//--------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorInstanceRef AccessorInstanceRefWrapper::get() const
{
	initAccessor();
	return m_AccessorInstanceRef;
}
//--------------------------------------------------------------------------------------------------//
// 
//--------------------------------------------------------------------------------------------------//
void AccessorInstanceRefWrapper::initAccessor() const
{
    if( !m_AccessorInstanceRef.isNull() ){
        return;
    }

    using namespace basar::db::aspect;
    const basar::VarString instanceName = createAccessorInstanceName();
    m_AccessorInstanceRef = Manager::getInstance().createAccessorInstance(
                                instanceName, m_AccessorName,
                                m_Connection, m_CachePolicyEnum,
                                m_StoreInInstanceList
                            );
}
//--------------------------------------------------------------------------------------------------//
// 
//--------------------------------------------------------------------------------------------------//
basar::VarString AccessorInstanceRefWrapper::createAccessorInstanceName() const
{
	static basar::Int32 instanceCounter = 1;
    std::stringstream instanceName; instanceName << m_AccessorName << "Instance_" << instanceCounter++;
	return instanceName.str().c_str();
}
//--------------------------------------------------------------------------------------------------//
// 
//--------------------------------------------------------------------------------------------------//
void AccessorInstanceRefWrapper::reset()
{
    if( m_AccessorInstanceRef.isNull() ){
        return;
    }
    
    m_AccessorInstanceRef.reset();
}

} // end namespace domMod

