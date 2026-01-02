#include "customerorderlockentry.hpp"

#include <liblockmanager/lock/ikey.h>
#include <liblockmanager/infrastructure/serialization/serializer.h>

namespace lock
{
    CustomerOrderLockEntry::CustomerOrderLockEntry( libLockManager::IKeyPtr key )
        : m_Key( key )
    {
    }

    CustomerOrderLockEntry::~CustomerOrderLockEntry()
    {
    }

    void CustomerOrderLockEntry::setContext( const basar::VarString& context )
    {
        m_Context = context;
    }

    void CustomerOrderLockEntry::setProcessNumber( basar::Int32 pid )
    {
        m_ProcessNumber = pid;
    }

    void CustomerOrderLockEntry::setDeviceName( const basar::VarString& deviceName )
    {
        m_DeviceName = deviceName;
    }

    const libLockManager::IKey& CustomerOrderLockEntry::getKey() const
    {
        return *m_Key;
    }

    const basar::DateTime& CustomerOrderLockEntry::getTimestamp() const
    {
        return m_Timestamp;
    }

    libLockManager::ISerializable::DataCollection CustomerOrderLockEntry::serialize() const
    {
        libLockManager::serialization::Serializer serializer( m_Key->serialize() );
        serializer.add( "context", m_Context );
        serializer.add( "device",  m_DeviceName );
        serializer.add( "pid",     m_ProcessNumber );

        return serializer.serialize();
    }

} // end namespace lock
