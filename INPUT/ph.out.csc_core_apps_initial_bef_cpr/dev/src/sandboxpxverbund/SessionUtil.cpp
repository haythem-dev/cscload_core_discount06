#include "pxverbundincludes.h"
#include "SessionUtil.h"
#include "persistence/connection.h"
#include "persistence/accessor.h"
#include "persistence/iaccessor.h"


basar::VarString SessionUtil::m_DatabaseServer = "zdev21_tcp";

#ifdef WIN32
basar::VarString SessionUtil::m_MessageFile = "..\\..\\..\\..\\src\\pxverbund\\files\\message.txt";
#else
basar::VarString SessionUtil::m_MessageFile = "../pxverbund/files/message.txt";
#endif

// ------------------------------------------------------------------------------------------- //

SessionUtil::SessionUtil(short branchno) :
    m_BranchNo(branchno)
{
    m_Session = NULL;
    m_IsVideo = false;
}

// ------------------------------------------------------------------------------------------- //

SessionUtil::~SessionUtil()
{
    cleanSession();
}

// ------------------------------------------------------------------------------------------- //

void SessionUtil::setVideo()
{
    m_IsVideo = true;
}

// ------------------------------------------------------------------------------------------- //

void SessionUtil::setDatabaseServer(const basar::VarString& dbserver)
{
    m_DatabaseServer = dbserver;
}

// ------------------------------------------------------------------------------------------- //

basar::VarString SessionUtil::getDatabaseServer()
{
    return m_DatabaseServer;
}

// ------------------------------------------------------------------------------------------- //

basar::VarString SessionUtil::getMessageFile()
{
    return m_MessageFile;
}

// ------------------------------------------------------------------------------------------- //

basar::db::sql::ExecuteReturnInfo SessionUtil::doSQL(const basar::VarString& sql)
{
    libcsc::persistence::IAccessorPtr acc(new libcsc::persistence::Accessor(get()->GetConnection()->getDbSqlConnection()));
    basar::db::sql::ExecuteReturnInfo ret = acc->execute(sql);
    return ret;
}

// ------------------------------------------------------------------------------------------- //

basar::db::sql::ResultsetRef SessionUtil::doSelect(const basar::VarString& sql)
{
    if (m_FindAccessor.get() == NULL)
    {
        m_FindAccessor = libcsc::persistence::IAccessorPtr(new libcsc::persistence::Accessor(get()->GetConnection()->getDbSqlConnection()));
    }
    basar::db::sql::ResultsetRef ret = m_FindAccessor->select(sql);
    return ret;
}

// ------------------------------------------------------------------------------------------- //

pxOrderTransmit* SessionUtil::get()
{
    if( NULL == m_Session )
    {
        if( m_IsVideo )
        {
            openSession(1);
        }
        else
        {
            openSession(7);
        }
    }
    return m_Session;
}

// ------------------------------------------------------------------------------------------- //

void SessionUtil::openSession(int devicetype)
{
    setCountry();
    setDatabase();
    basar::VarString devname = "SANDBOX";
    //std::cout << "# OpenSession for Branch(" << m_BranchNo << "), Country(" << m_Country << "), Database(" << m_Database << ") \n" << std::endl;
    m_Session = new pxOrderTransmit( m_BranchNo, m_Country, m_Database, (::pxDeviceType)devicetype, devname, m_MessageFile);
    if( !m_Session->IsGoodState() )
    {
        std::cout << "ERR -> pxOrderTransmit != GoodState" << std::endl;
        throw;
    }
}

// ------------------------------------------------------------------------------------------- //

void SessionUtil::setDatabase()
{
    if (isAustria())
    {
        m_Database = "oat21@" + m_DatabaseServer;
    }
    else if (isBulgaria())
    {
        m_Database = "obg21@" + m_DatabaseServer;
    }
    else if (isCroatia())
    {
        m_Database = "ohr21@" + m_DatabaseServer;
    }
    else if (isGermany())
    {
        m_Database = "ode21@" + m_DatabaseServer;
    }
    else if (isSwitzerland())
    {
        m_Database = "och21@" + m_DatabaseServer;
    }
    else if (isFrance())
    {
        m_Database = "ofr21@" + m_DatabaseServer;
    }
    else if (isTest())
    {
        m_Database = "ode21@" + m_DatabaseServer;
    }
}

// ------------------------------------------------------------------------------------------- //
void SessionUtil::setCountry()
{
    if( 		isGermany() 	)
    {
        m_Country = "DE";
    }
    else if(    isAustria()     )
    {
        m_Country = "AT";
    }
    else if( 	isSwitzerland() )
    {
        m_Country = "CH";
    }
    else if( 	isBulgaria() 	)
    {
        m_Country = "BG";
    }
    else if(    isCroatia()     )
    {
        m_Country = "HR";
    }
    else if(    isSerbia()      )
    {
        m_Country = "RS";
    }
    else if(    isFrance()      )
    {
        m_Country = "FR";
    }
    else if (isTest())
    {
        m_Country = "DE";
    }
    else
    {
        std::cout << "ERR -> BranchNo " << m_BranchNo << " unknown" << std::endl;
        throw;
    }
}

// ------------------------------------------------------------------------------------------- //
bool SessionUtil::isSerbia() const
{
    if( 03 == m_BranchNo || 84 == m_BranchNo || 85 == m_BranchNo )
    {
        return true;
    }
    return false;
}

// ------------------------------------------------------------------------------------------- //
bool SessionUtil::isCroatia() const
{
    if( 71 == m_BranchNo || 72 == m_BranchNo || 73 == m_BranchNo || 74 == m_BranchNo || 77 == m_BranchNo )
    {
        return true;
    }
    return false;
}

// ------------------------------------------------------------------------------------------- //
bool SessionUtil::isAustria() const
{
    if( 61 == m_BranchNo || 62 == m_BranchNo || 63 == m_BranchNo || 64 == m_BranchNo || 83 == m_BranchNo )
    {
        return true;
    }
    return false;
}

// ------------------------------------------------------------------------------------------- //
bool SessionUtil::isBulgaria() const
{
    if( 22 == m_BranchNo || 23 == m_BranchNo || 25 == m_BranchNo || 26 == m_BranchNo || 28 == m_BranchNo )
    {
        return true;
    }
    return false;
}

// ------------------------------------------------------------------------------------------- //
bool SessionUtil::isSwitzerland() const
{
    if( 12 == m_BranchNo || 13 == m_BranchNo || 16 == m_BranchNo )
    {
        return true;
    }
    return false;
}

// ------------------------------------------------------------------------------------------- //
bool SessionUtil::isGermany() const
{
    if(  5 == m_BranchNo || 6 == m_BranchNo ||  8 == m_BranchNo ||  9 == m_BranchNo ||
        21 == m_BranchNo || 31 == m_BranchNo || 33 == m_BranchNo ||
        40 == m_BranchNo || 44 == m_BranchNo || 46 == m_BranchNo ||
        51 == m_BranchNo || 52 == m_BranchNo || 54 == m_BranchNo || 56 == m_BranchNo ||
        57 == m_BranchNo || 58 == m_BranchNo || 59 == m_BranchNo ||
        70 == m_BranchNo || 78 == m_BranchNo ||
        81 == m_BranchNo || 82 == m_BranchNo)
    {
        return true;
    }
    return false;
}

// ------------------------------------------------------------------------------------------- //
bool SessionUtil::isFrance() const
{
    if( 17 == m_BranchNo || 18 == m_BranchNo || 30 == m_BranchNo || 32 == m_BranchNo ||
            34 == m_BranchNo || 35 == m_BranchNo || 36 == m_BranchNo || 37 == m_BranchNo ||
            38 == m_BranchNo || 39 == m_BranchNo || 41 == m_BranchNo || 42 == m_BranchNo ||
            43 == m_BranchNo || 45 == m_BranchNo || 48 == m_BranchNo || 50 == m_BranchNo ||
            53 == m_BranchNo || 55 == m_BranchNo || 60 == m_BranchNo || 66 == m_BranchNo ||
            68 == m_BranchNo || 75 == m_BranchNo || 76 == m_BranchNo || 80 == m_BranchNo ||
            86 == m_BranchNo || 87 == m_BranchNo
      )
    {
        return true;
    }
    return false;
}

// ------------------------------------------------------------------------------------------- //
bool SessionUtil::isTest() const
{
    return (m_BranchNo == 666);
}

// ------------------------------------------------------------------------------------------- //
void SessionUtil::cleanSession()
{
    if (m_FindAccessor.get() != NULL)
    {
        m_FindAccessor.reset();
    }
    if (0 != m_Session)
    {
        delete m_Session;
        m_Session = NULL;
    }
}
