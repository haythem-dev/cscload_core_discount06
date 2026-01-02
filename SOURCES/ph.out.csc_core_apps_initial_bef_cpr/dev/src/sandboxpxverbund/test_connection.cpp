#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"
#include <persistence/connection.h>
#include <persistence/connectionptr.h>

using namespace std;

// -----------------------------------------------------------------------------
// Fixture holding former global variables
// -----------------------------------------------------------------------------
class ConnectionFixture
{
public:
    short branchNo;
    basar::VarString countryCode;
    basar::VarString dbServerName;
    basar::VarString dbName;
    basar::VarString dataSource;
    ::pxDeviceType deviceType;
    basar::VarString deviceName;
    basar::VarString messageFileName;

    ConnectionFixture()
        : branchNo(33)
        , countryCode("DE")
        , dbServerName(SessionUtil::getDatabaseServer())
        , dbName("ode21")
        , dataSource(dbName + "@" + dbServerName)
        , deviceType(pxDVC_DCT_SERIAL)
        , deviceName("SBOX")
        , messageFileName(SessionUtil::getMessageFile())
    {
    }
};

// -----------------------------------------------------------------------------
// Test Suite
// -----------------------------------------------------------------------------
SUITE(Connection)
{
    TEST_FIXTURE(ConnectionFixture, Connection01)
    {
        pxSession* session = new pxSession(branchNo, countryCode.c_str(), dataSource.c_str(), deviceType, deviceName.c_str(), messageFileName.c_str());
        session->OpenDBConnection();
        CHECK_EQUAL(true, session->IsGoodState());
        if (session->IsGoodState())
        {
            session->Close();
        }
        delete session; session = NULL;
    }

    TEST_FIXTURE(ConnectionFixture, Connection02)
    {
        pxOrderTransmit* xmit = new pxOrderTransmit(branchNo, countryCode.c_str(), dataSource.c_str(), deviceType, deviceName.c_str(), messageFileName.c_str());
        CHECK_EQUAL(true, xmit->IsGoodState());
        if (xmit->IsGoodState())
        {
            xmit->Close();
        }
        delete xmit; xmit = NULL;
    }

    TEST_FIXTURE(ConnectionFixture, Connection03)
    {
        pxSessionInitialization sessinit;
        sessinit.setBranchInformation(branchNo, pxSessionInitialization::getCountryCode(branchNo));
        sessinit.setDBInformation(dbServerName, dbName);
        sessinit.setDevice(deviceType, deviceName);
        sessinit.setMessageFileName(messageFileName);

        libcsc::persistence::ConnectionPtr Connection = libcsc::persistence::ConnectionPtr(new libcsc::persistence::Connection());
        Connection->open(dbServerName, dbName);
        pxSession* session = new pxSession(sessinit);
        session->injectDBConnection(Connection);
        CHECK_EQUAL(true, session->IsGoodState());
        if (session->IsGoodState())
        {
            session->prepareSession();
            CHECK_EQUAL(true, session->IsGoodState());
            if (session->IsGoodState())
            {
                session->Close();
            }
        }
        delete session; session = NULL;

        if (Connection)
        {
            if (!Connection.get()->getDbSqlConnection().isNull())
            {
                if (Connection->getDbSqlConnection().isOpen())
                {
                    Connection->close();
                }
            }
        }
    }

    TEST_FIXTURE(ConnectionFixture, Connection04)
    {
        pxSessionInitialization sessinit;
        sessinit.setBranchInformation(branchNo, pxSessionInitialization::getCountryCode(branchNo));
        sessinit.setDBInformation(dbServerName, dbName);
        sessinit.setDevice(deviceType, deviceName);
        sessinit.setMessageFileName(messageFileName);

        libcsc::persistence::ConnectionPtr Connection = libcsc::persistence::ConnectionPtr(new libcsc::persistence::Connection());
        Connection->open(dbServerName, dbName);
        pxSession* session = new pxSession(sessinit);
        session->injectDBConnection(Connection);
        session->prepareSession();
        CHECK_EQUAL(true, session->IsGoodState());
        session->injectDBConnection(Connection); // duplicate injection
        CHECK_EQUAL(false, session->IsGoodState());
        if (session->IsGoodState())
        {
            session->Close();
        }
        delete session; session = NULL;

        if (Connection)
        {
            if (!Connection.get()->getDbSqlConnection().isNull())
            {
                if (Connection->getDbSqlConnection().isOpen())
                {
                    Connection->close();
                }
            }
        }
    }

    TEST_FIXTURE(ConnectionFixture, Connection05)
    {
        pxSessionInitialization sessinit;
        sessinit.setBranchInformation(branchNo, pxSessionInitialization::getCountryCode(branchNo));
        sessinit.setDBInformation(dbServerName, dbName);
        sessinit.setDevice(deviceType, deviceName);
        sessinit.setMessageFileName(messageFileName);

        libcsc::persistence::ConnectionPtr Connection = libcsc::persistence::ConnectionPtr(new libcsc::persistence::Connection());
        Connection->open(dbServerName, dbName);
        pxOrderTransmit* xmit = new pxOrderTransmit(sessinit);
        xmit->injectDBConnection(Connection);
        if (xmit->IsGoodState())
        {
            xmit->prepareSession();
            if (xmit->IsGoodState())
            {
                xmit->Close();
            }
        }
        delete xmit; xmit = NULL;

        if (Connection)
        {
            if (!Connection.get()->getDbSqlConnection().isNull())
            {
                if (Connection->getDbSqlConnection().isOpen())
                {
                    Connection->close();
                }
            }
        }
    }

    TEST_FIXTURE(ConnectionFixture, Connection06)
    {
        pxSessionInitialization sessinit;
        sessinit.setBranchInformation(branchNo, pxSessionInitialization::getCountryCode(branchNo));
        sessinit.setDBInformation(dbServerName, dbName);
        sessinit.setDevice(deviceType, deviceName);
        sessinit.setMessageFileName(messageFileName);

        libcsc::persistence::ConnectionPtr Connection = libcsc::persistence::ConnectionPtr(new libcsc::persistence::Connection());
        Connection->open(dbServerName, dbName);
        pxOrderTransmit* xmit = new pxOrderTransmit(sessinit);
        xmit->injectDBConnection(Connection);
        xmit->prepareSession();
        CHECK_EQUAL(true, xmit->IsGoodState());
        xmit->injectDBConnection(Connection); // duplicate injection
        CHECK_EQUAL(false, xmit->IsGoodState());
        if (xmit->IsGoodState())
        {
            xmit->Close();
        }
        delete xmit; xmit = NULL;

        if (Connection)
        {
            if (!Connection.get()->getDbSqlConnection().isNull())
            {
                if (Connection->getDbSqlConnection().isOpen())
                {
                    Connection->close();
                }
            }
        }
    }

    TEST_FIXTURE(ConnectionFixture, Connections)
    {
        // Placeholder for previously commented scenarios (07,08) intentionally left empty
        CHECK(true);
    }
}
