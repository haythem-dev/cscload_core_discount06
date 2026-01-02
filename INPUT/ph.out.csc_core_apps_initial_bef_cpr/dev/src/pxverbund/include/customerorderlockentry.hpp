#ifndef GUARD_PXVERBUND_LOCK_CUSTOMERORDERLOCKENTRY_H
#define GUARD_PXVERBUND_LOCK_CUSTOMERORDERLOCKENTRY_H

#include <liblockmanager/lock/ilockentry.h>
#include <liblockmanager/lock/ikeyptr.h>

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_datetime.h>

#include <boost/shared_ptr.hpp>

namespace lock
{
    class CustomerOrderLockEntry : public libLockManager::ILockEntry
    {
    public:
        CustomerOrderLockEntry( libLockManager::IKeyPtr );
        ~CustomerOrderLockEntry();

        // from ILockEntry interface
        const libLockManager::IKey&    getKey()       const;
        const basar::DateTime&         getTimestamp() const;

        void                           setContext( const basar::VarString& );
        void                           setProcessNumber( basar::Int32 );
        void                           setDeviceName( const basar::VarString& );

        libLockManager::ISerializable::DataCollection serialize()    const;

    private:
        libLockManager::IKeyPtr        m_Key;
        basar::DateTime                m_Timestamp;

        basar::VarString               m_Context;
        basar::Int32                   m_ProcessNumber;
        basar::VarString               m_DeviceName;
    };

    typedef boost::shared_ptr< CustomerOrderLockEntry > CustomerOrderLockEntryPtr;
} // end namespace lock

#endif // GUARD_PXVERBUND_LOCK_CUSTOMERORDERLOCKENTRY_H
