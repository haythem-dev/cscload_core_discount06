#ifndef SESSIONUTIL_H
#define SESSIONUTIL_H

#include "pxverbundincludes.h"
#include <libbasardbsql.h>
#include <persistence/iaccessorptr.h>

class pxOrderTransmit;

class SessionUtil
{
    public:
                                SessionUtil(short branchno);
                                ~SessionUtil();
        pxOrderTransmit*        get();
        void                    setVideo();
        static void             setDatabaseServer(const basar::VarString& dbserver);
        static basar::VarString getDatabaseServer();
        static basar::VarString getMessageFile();
        basar::db::sql::ExecuteReturnInfo doSQL(const basar::VarString& sql);
        basar::db::sql::ResultsetRef doSelect(const basar::VarString& sql);

    private:
        void                    openSession(int devicetype);
        void                    cleanSession();
        void                    setCountry();
        void                    setDatabase();

        bool                    isAustria() const;
        bool                    isBulgaria() const;
        bool                    isCroatia() const;
        bool                    isFrance() const;
        bool                    isSerbia() const;
        bool                    isSwitzerland() const;
        bool                    isGermany() const;
        bool                    isTest() const;

        basar::VarString        m_Country;
        basar::VarString        m_Database;
        static basar::VarString m_DatabaseServer;
        static basar::VarString m_MessageFile;
        short                   m_BranchNo;
        bool                    m_IsVideo;
        pxOrderTransmit*        m_Session;

        libcsc::persistence::IAccessorPtr m_FindAccessor;
};

#endif // SESSIONUTIL_H
