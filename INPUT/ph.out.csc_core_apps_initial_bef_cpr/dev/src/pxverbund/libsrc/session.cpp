#ifdef WIN32
#include <process.h> // for _getpid()
#endif

#include "pxsess.hpp"
#include "pxdefs.hpp"
#include "pxdbfunc.h"
#include "pxdevice.hpp"
#include "pxordtyp.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxordvtr.hpp"
#include "pxbranch.hpp"
#include "pxcomput.hpp"
#include "pxoeparm.hpp"
#include "pxholiday.hpp"
#include "pxholidaydef.h"
#include "pxcremamail.hpp"
#include "pxdiscountordtyp.hpp"
#include "pxtaxrates.hpp"
#include "pxseporderartgrp.hpp"
#include "pxtcasession.hpp"
#include "pxoeorigintypes.hpp"
#include "pxttype.hpp"
#include "pxgeneralcalcavp.hpp"
#include "pxorder.hpp"
#include "pxcstbas.hpp"
#include "ibttype.hpp"
#include "pxstockbooking.hpp"
#include "ibtassortmenttype.h"
#include "types/messagecodeenum.inc"
#include <logger/loggerpool.h>
#include <sstream>
#include <util/configfilereader.h>
#include <persistence/connection.h>
#include <libbasar_definitions.h>
#include <libbasarcmnutil_exceptions.h>

#include <discount/componentmanager/discountcomponentmanager.h>
#include <discount/discountcollectionfinder/idiscountcollectionfinder.h>
#include <discount/orderpositiondiscount/orderpositiondiscountrepository.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepositoryptr.h>

#include <discount/tender/repository/itenderdiscountfinderptr.h>
#include <discount/tender/repository/tenderdiscountrepository.h>

#include <tender/componentmanager/tendercomponentmanager.h>
#include <tender/repository/tenderrepository.h>

#include <crema/componentmanager/cremacomponentmanager.h>
#include <ibt/componentmanager/ibtcomponentmanager.h>
#include <stockbooking/componentmanager/stockbookingcomponentmanager.h>
#include <parameter/componentmanager/parametercomponentmanager.h>
#include <cscorder/componentmanager/cscordercomponentmanager.h>
#include <cscorderpos/componentmanager/cscorderposcomponentmanager.h>
#include <cscordertype/componentmanager/cscordertypecomponentmanager.h>
#include <customer/componentmanager/customercomponentmanager.h>
#include <subseqdelivery/componentmanager/sudcomponentmanager.h>
#include <document/componentmanager/documentcomponentmanager.h>
#include <returns/componentmanager/returncomponentmanager.h>
#include <workingdayscalendar/componentmanager/workingdayscalendarcomponentmanager.h>
#include <blockedarticles/componentmanager/blockedarticlescomponentmanager.h>
#include <procurementpermission/componentmanager/componentmanager.h>
#include <shipmenttracking/componentmanager/shipmenttrackingcomponentmanager.h>
#include <procurementpermission/repository/irepository.h>
#include <parameter/sessionparametergetter.h>
#include <parameter/branchparametergetter.h>
#include <pxdbxx.h>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/make_shared.hpp>
#include <exceptions/persistenceexception.h>
#include "impl/callbackcomponentmanager.hpp"

#include <libbasardbsql_databaseinfo.h>
#include "pxparameter.hpp"

// lockManager
#include <liblockmanager/lockmanager/ilockmanager.h>
#include <liblockmanager/lockmanager/lockmanager.h>
#include <liblockmanager/lockmanager/lockmanagerptr.h>
#include <liblockmanager/infrastructure/accessor/dblockaccessorfactory.h>
#include <liblockmanager/lockguard/lockguardfactory.h>
#include <liblockmanager/lockguard/lockguardfactoryptr.h>
#include <liblockmanager/lock/key.h>
#include <liblockmanager/lock/keyptr.h>
#include "customerorderlockentry.hpp"
#include "pxlockaccessordecorator.h"
#include "pxlockaccessorerrorhandler.h"

int    pxGlobalLanguageId = 0;
nString pxGlobalMessageFile;
bool   pxGlobalNoDatabaseWrite = false;
bool   pxGlobalNoWriteToLog = false;
bool   pxGlobalInitTcaccess = false;
bool   pxGlobalDataBaseSort = false;
bool   pxGlobalIBTNoTimeCheck = false;
bool   pxGlobalCollectiveOrderDiscountable = false; //CV22

// country shortnames
const char* pxSession::COUNTRY_AUSTRIA          = "AT";
const char* pxSession::COUNTRY_AUSTRIA_PREWHOLE = "AU";
const char* pxSession::COUNTRY_BULGARIA         = "BG";
const char* pxSession::COUNTRY_CROATIA          = "HR";
const char* pxSession::COUNTRY_GERMANY          = "DE";
const char* pxSession::COUNTRY_FRANCE           = "FR";
const char* pxSession::COUNTRY_FRANCE_PREWHOLE  = "PF";
const char* pxSession::COUNTRY_SERBIA           = "RS";
const char* pxSession::COUNTRY_SWITZERLAND      = "CH";

/*----------------------------------------------------------------------------*/
pxSession::pxSession( const basar::VarString& IniFileName, const short branchNo)
{
    std::stringstream ss;
    ss << "pxSession::pxSession(): IniFileName: " << IniFileName << ", branchNo<" << branchNo << ">";
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), ss.str());

    InitializeDBConnection();
    Init(branchNo);

    if(nSTATE_GOOD == ReadProfile(IniFileName))
    {
        InitializeCMsgStream();
    }
}

/*----------------------------------------------------------------------------*/
pxSession::pxSession( const pxSessionInitialization& sessioninit )
{
    m_SessionInitialization = sessioninit;
    Init( sessioninit.getBranchNo() );
    //InitializeDBConnection(); // connection has to be set using injectDBConnection

    if( ::IsValidDevice(sessioninit.getDeviceType()) )
    {
        Device()->Type(sessioninit.getDeviceType());
        Device()->Name(sessioninit.getDeviceName().c_str());
    }
    InitializeCMsgStream();
}

/*----------------------------------------------------------------------------*/
/*  Constructor without ini-file                                              */
/*----------------------------------------------------------------------------*/
pxSession::pxSession( const short branchNo, const basar::VarString& countryCode, const basar::VarString& dataSource, const ::pxDeviceType deviceType, const basar::VarString& deviceName, const basar::VarString& messageFileName)
{
    InitializeDBConnection();
    Init( branchNo );

    pxDeviceType t = (pxDeviceType)deviceType;

    if( !countryCode.empty()     ) { m_SessionInitialization.setBranchInformation( branchNo, countryCode ); }
    if( !dataSource.empty()      ) { m_SessionInitialization.setConnectionString( dataSource ); }
    if( !messageFileName.empty() ) { m_SessionInitialization.setMessageFileName( messageFileName ); }

    if( !deviceName.empty() )
    {
        if( ::IsValidDevice(t) )
        {
            m_SessionInitialization.setDevice( deviceType, deviceName );
            Device()->Type( m_SessionInitialization.getDeviceType() );
            Device()->Name(deviceName.c_str());
        }
    }

    InitializeCMsgStream();
}

/*----------------------------------------------------------------------------*/
void pxSession::injectDBConnection( libcsc::persistence::ConnectionPtr connection )
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerSession(), "pxSession::injectDBConnection()" );

    if( 0 == m_Connection.get() )
    {
        m_Connection = connection;

        if( 0 != m_Connection.get() )
        {
            if( !m_Connection->getDbSqlConnection().isNull() )
            {
                if( m_Connection->getDbSqlConnection().isOpen() )
                {
                    m_ConnectionOwnership = false; // already opened connection has been injected!
                }
            }
        }
        InitializeComponentManagers();
    }
    else
    {
        if( NULL != CMsgStream() ) ExternalError(CMsgStream(), CMSG_SESS_DUPLICATECONNECTIONINJECTION);
        ErrorState(nSTATE_FATALERROR);
    }
}

libcsc::persistence::ConnectionPtr pxSession::GetConnection()
{
    return m_Connection;
}

/*----------------------------------------------------------------------------*/
/*  Destruction.                                                              */
/*----------------------------------------------------------------------------*/
pxSession :: ~pxSession()
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerSession(), "pxSession::~pxSession()" );

    m_DiscountComponentManager.reset();
    m_IbtComponentManager.reset();
    m_CremaComponentManager.reset();
    m_CSCOrderComponentManager.reset();
    m_CSCOrderposComponentManager.reset();
    m_CustomerComponentManager.reset();
    m_ProcurementPermissionComponentManager.reset();
    m_CallbackComponentManager.reset();
    m_SudComponentManager.reset();
    m_StockBookingComponentManager.reset();
    m_ParameterComponentManager.reset();
    m_CSCOrderTypeComponentManager.reset();
    m_DocumentComponentManager.reset();
    m_ReturnsComponentManager.reset();
    m_WorkingdaysCalendarComponentManager.reset();
    m_BlockedArticlesComponentManager.reset();
    m_ShipmentTrackingComponentManager.reset();

    if( IsOpen() ) { Close(); }

    CloseTcaSessions();

    m_OrderEntryParamMap.clear();
    if( NULL != m_OrderTypeList         ) { delete m_OrderTypeList; m_OrderTypeList = NULL; }
    if( NULL != m_StockTransList        ) { delete m_StockTransList; m_StockTransList = NULL; }
    if( NULL != m_CommTypeList          ) { delete m_CommTypeList; m_CommTypeList = NULL; }
    if( NULL != m_OrderValidTransList   ) { delete m_OrderValidTransList; m_OrderValidTransList = NULL; }
    if( NULL != m_Branch                ) { delete m_Branch; m_Branch = NULL; }
    if( NULL != m_MsgStream             ) { delete m_MsgStream; m_MsgStream = NULL; }
    if( NULL != m_Device                ) { delete m_Device; m_Device = NULL; }
    if( NULL != m_ComputerList          ) { delete m_ComputerList; m_ComputerList = NULL; }
    if( NULL != m_HoliDayList           ) { delete m_HoliDayList; m_HoliDayList = NULL; }
    if( NULL != m_DiscountOrderTypeList ) { delete m_DiscountOrderTypeList; m_DiscountOrderTypeList = NULL; }
    if( NULL != m_TaxRatesList          ) { delete m_TaxRatesList; m_TaxRatesList = NULL; }
    if( NULL != m_SepOrderArtGroupList  ) { delete m_SepOrderArtGroupList; m_SepOrderArtGroupList = NULL; }
    if( NULL != m_GeneralCalcAvpList    ) { delete m_GeneralCalcAvpList; m_GeneralCalcAvpList = NULL; }
    if( NULL != m_TcaSessionList        ) { delete m_TcaSessionList; m_TcaSessionList = NULL; }
    if( NULL != m_IBTTypeList           ) { delete m_IBTTypeList; m_IBTTypeList = NULL; }
    if( NULL != m_IBTAssortmentTypeList ) { delete m_IBTAssortmentTypeList; m_IBTAssortmentTypeList = NULL; }
}

/*----------------------------------------------------------------------------*/
void pxSession::InitializeDBConnection()
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerSession(), "pxSession::InitializeDBConnection()" );

    m_Connection = libcsc::persistence::ConnectionPtr( new libcsc::persistence::Connection() );
    m_ConnectionOwnership = true;

    InitializeComponentManagers();
}

/*----------------------------------------------------------------------------*/

void pxSession::InitializeComponentManagers()
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxSession::InitializeComponentManagers()");

    m_DiscountComponentManager = libcsc::discount::DiscountComponentManagerPtr( new libcsc::discount::DiscountComponentManager() );
    m_DiscountComponentManager->injectConnection( m_Connection );
    m_DiscountComponentManager->injectTransactionHandler( this );
    m_DiscountComponentManager->injectParameterGetter( libcsc::parameter::ISessionParameterGetterPtr( new libcsc::parameter::SessionParameterGetter( this ) ) );

    m_TenderComponentManager = libcsc::tender::TenderComponentManagerPtr( new libcsc::tender::TenderComponentManager() );
    m_TenderComponentManager->injectConnection( m_Connection );
    m_TenderComponentManager->injectTransactionHandler( this );
    m_TenderComponentManager->injectBatchParameterGetter( libcsc::parameter::IBranchParameterGetterPtr( new libcsc::parameter::BranchParameterGetter( this ) ) );

    m_IbtComponentManager = boost::make_shared<libcsc::ibt::IbtComponentManager>();
    m_IbtComponentManager->injectConnection( m_Connection );
    m_IbtComponentManager->injectTransactionHandler( this );

    m_CremaComponentManager = boost::make_shared<libcsc::crema::CremaComponentManager>();
    m_CremaComponentManager->injectConnection(m_Connection);
    //m_CremaComponentManager->ininjectTransactionHandler(this);

    m_CSCOrderComponentManager = boost::make_shared<libcsc::cscorder::CSCOrderComponentManager>();
    m_CSCOrderComponentManager->injectConnection( m_Connection );
    m_CSCOrderComponentManager->injectTransactionHandler( this );

    m_CSCOrderposComponentManager = boost::make_shared<libcsc::cscorderpos::CSCOrderposComponentManager>();
    m_CSCOrderposComponentManager->injectConnection(m_Connection);
    m_CSCOrderposComponentManager->injectTransactionHandler(this);

    m_CustomerComponentManager = boost::make_shared<libcsc::customer::CustomerComponentManager>();
    m_CustomerComponentManager->injectConnection(m_Connection);
    m_CustomerComponentManager->injectBranchParameterGetter(libcsc::parameter::IBranchParameterGetterPtr(new libcsc::parameter::BranchParameterGetter(this)));

    m_ProcurementPermissionComponentManager = boost::make_shared<libcsc::procurementpermission::ComponentManager>();
    m_ProcurementPermissionComponentManager->injectConnection(m_Connection);

    m_CallbackComponentManager = CallbackComponentManager::create(this, m_Connection);

    m_SudComponentManager = boost::make_shared<libcsc::sud::SudComponentManager>();
    m_SudComponentManager->injectConnection( m_Connection );
    m_SudComponentManager->injectTransactionHandler( this );

    m_StockBookingComponentManager = boost::make_shared<libcsc::stockbooking::StockBookingComponentManager>();
    m_StockBookingComponentManager->injectConnection(m_Connection);

    m_ParameterComponentManager = boost::make_shared<libcsc::parameter::ParameterComponentManager>();
    m_ParameterComponentManager->injectConnection(m_Connection);

    m_CSCOrderTypeComponentManager = boost::make_shared<libcsc::cscordertype::CSCOrderTypeComponentManager>();
    m_CSCOrderTypeComponentManager->injectConnection(m_Connection);
    m_CSCOrderTypeComponentManager->injectTransactionHandler(this);

    m_DocumentComponentManager = boost::make_shared<libcsc::document::DocumentComponentManager>();
    m_DocumentComponentManager->injectConnection(m_Connection);
    m_DocumentComponentManager->injectTransactionHandler(this);
    m_DocumentComponentManager->injectBranchParameterGetter(
        libcsc::parameter::IBranchParameterGetterPtr(new libcsc::parameter::BranchParameterGetter(this))
        );

    m_ReturnsComponentManager = boost::make_shared<libcsc::returns::ReturnComponentManager>();
    m_ReturnsComponentManager->injectConnection(m_Connection);
    m_ReturnsComponentManager->injectSession(this);
    m_ReturnsComponentManager->injectTransactionHandler(this);

    m_WorkingdaysCalendarComponentManager = boost::make_shared<libcsc::workingdayscalendar::WorkingdaysCalendarComponentManager>();
    m_WorkingdaysCalendarComponentManager->injectConnection(m_Connection);
    m_WorkingdaysCalendarComponentManager->injectTransactionHandler(this);

    m_BlockedArticlesComponentManager = boost::make_shared<libcsc::blockedarticles::BlockedArticlesComponentManager>();
    m_BlockedArticlesComponentManager->injectConnection(m_Connection);
    m_BlockedArticlesComponentManager->injectTransactionHandler(this);
    m_BlockedArticlesComponentManager->injectBranchParameterGetter(libcsc::parameter::IBranchParameterGetterPtr(new libcsc::parameter::BranchParameterGetter(this)));

    m_ShipmentTrackingComponentManager = boost::make_shared<libcsc::shipmenttracking::ShipmentTrackingComponentManager>();
    m_ShipmentTrackingComponentManager->injectConnection(m_Connection);
    m_ShipmentTrackingComponentManager->injectTransactionHandler(this);
    m_ShipmentTrackingComponentManager->injectBranchParameterGetter(libcsc::parameter::IBranchParameterGetterPtr(new libcsc::parameter::BranchParameterGetter(this)));
}

// informix client sdk: Get name of connection which is currently active
// TODO remove when BASAR returns internal connection name
extern "C" char* ifx_getcur_conn_name();

libLockManager::accessor::IDBLockAccessorFactoryPtr pxSession::getDBLockAccessorFactory()
{
    if( m_DBLockAccessorFactory.get() == 0 )
    {
        m_InternalConnectionName = basar::VarString(ifx_getcur_conn_name()); // TODO remove when BASAR returns internal connection name
        m_DBLockAccessorFactory = boost::make_shared< libLockManager::accessor::DBLockAccessorFactory >( m_Connection->getDbSqlConnection() );
        m_LockConnectionName = basar::VarString(ifx_getcur_conn_name()); // TODO remove when BASAR returns internal connection name
    }

    return m_DBLockAccessorFactory;
}

libLockManager::ILockManagerPtr pxSession::getCustomerOrderLockManager()
{
    if( m_CustomerOrderLockManager.get() == 0 )
    {
        libLockManager::accessor::ILockAccessorPtr lockAccessor = getDBLockAccessorFactory()->create( "customerorderlock" );

        // Inject own accessor decorator which switches connections internally.
        // This is needed because ESQLC always uses the current active connection. The lock accessor switches the connection
        // automatically to his own connection when executing SQL, which has to be switched back afterwards so ESQL can run
        // on its own connection again. The task of PxLockAccessor is to ensure the connection is switched back after using the accessor.
        libLockManager::LockManagerPtr lockManager = boost::make_shared<libLockManager::LockManager>();

        libLockManager::accessor::ILockAccessorPtr lockAccessorDecorator = boost::make_shared<lock::PxLockAccessorDecorator>(
            lockAccessor, m_InternalConnectionName, m_LockConnectionName);
        libLockManager::accessor::ILockAccessorErrorHandlerPtr errorHandler = boost::make_shared<lock::PxLockAccessorErrorHandler>();
        lockAccessorDecorator->injectErrorHandler(errorHandler);
        lockManager->injectAccessor(lockAccessorDecorator);

        m_CustomerOrderLockManager = lockManager;
    }

    return m_CustomerOrderLockManager;
}

libLockManager::IKeyPtr pxSession::createCustomerOrderLockKey( basar::Int32 orderNo )
{
    libLockManager::KeyPtr key = boost::make_shared< libLockManager::Key >( orderNo );
    key->setIdentifierName( "orderno" );

    return key;
}

libLockManager::ILockGuardPtr pxSession::createCustomerOrderLockGuard( const basar::VarString& context, basar::Int32 orderNo )
{
    if( m_CustomerOrderLockGuardFactory.get() == 0 )
    {
        libLockManager::LockGuardFactoryPtr lockGuardFactory = boost::make_shared< libLockManager::LockGuardFactory >();
        lockGuardFactory->injectLockManager( getCustomerOrderLockManager() );

        m_CustomerOrderLockGuardFactory = lockGuardFactory;
    }

    lock::CustomerOrderLockEntryPtr lockEntry = boost::make_shared< lock::CustomerOrderLockEntry >( createCustomerOrderLockKey( orderNo ) );
    lockEntry->setContext( context );
    lockEntry->setDeviceName( Device()->Name()() );
#ifdef WIN32
    lockEntry->setProcessNumber( _getpid() ); // ProcessNumber() returns 0 which means child process - we want the actual pid here
#else
    lockEntry->setProcessNumber( getpid() ); // ProcessNumber() returns 0 which means child process - we want the actual pid here
#endif

    return m_CustomerOrderLockGuardFactory->createLockGuard( lockEntry );
}

/*----------------------------------------------------------------------------*/
int pxSession::InitializeCMsgStream()
{
    if( NULL == m_MsgStream )
    {
        if( m_SessionInitialization.getMessageFileName().empty() )
        {
            ErrorState(nSTATE_FATALERROR);
            return ExternalError(nMessage(pxErrorMsg(pxMSGNUM_SESSION_PARM)));
        }

        m_MsgStream = new std::ifstream;
        m_MsgStream->open(m_SessionInitialization.getMessageFileName().c_str(), std::ios::in);
        if( !m_MsgStream->good() )
        {
            delete m_MsgStream; m_MsgStream = NULL;
            ErrorState(nSTATE_FATALERROR);
            return FileError(nMessage(pxErrorMsg(pxMSGNUM_OPENCMSG), m_SessionInitialization.getMessageFileName().c_str()));
        }

        basar::VarString::size_type msglen = m_SessionInitialization.getMessageFileName().find_last_of('/');

        if( msglen != basar::VarString::npos )
        {
            basar::VarString messageFile = m_SessionInitialization.getMessageFileName();
            messageFile = messageFile.substr( msglen + 1, messageFile.length() - (msglen + 1) );
            pxGlobalMessageFile = messageFile.c_str();
        }
        else
        {
            pxGlobalMessageFile = m_SessionInitialization.getMessageFileName().c_str();
        }
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
/*  Init members with default and initial values                              */
/*----------------------------------------------------------------------------*/
void pxSession::Init( const short sFilialNr )
{
    std::stringstream ss;
    ss << "pxSession::Init(): sFilialNr<" << sFilialNr << ">";
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), ss.str());

    // Initialize with default values:
    m_SessionInitialization.setBranchInformation( sFilialNr, pxSessionInitialization::getCountryCode( sFilialNr ) );
    m_PersonalNo = 0;
    m_ProcessNumber = 0;
    m_SubDeviceType = PHONO;
    m_Branch = NULL;
    m_Device = NULL;
//    m_OrderEntryParam = NULL;
    m_IBTTypeList = NULL;
    m_CommTypeList = NULL;
    m_HoliDayList = NULL;
    m_ComputerList = NULL;
    m_OrderTypeList = NULL;
    m_StockTransList = NULL;
    m_OrderValidTransList = NULL;
    m_DiscountOrderTypeList = NULL;
    m_TaxRatesList = NULL;
    m_MsgStream = NULL;
    m_GeneralCalcAvpList = NULL;
    m_SepOrderArtGroupList = NULL;
    m_TcaSessionList = NULL;
    m_IBTAssortmentTypeList = NULL;
    m_CurrentOrder = NULL;
    m_UsersFilialNr = 0;
    m_IgnoreOrderPeriodDD = false;
}

/*----------------------------------------------------------------------------*/
int pxSession::prepareSession()
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerSession(), "pxSession::prepareSession()" );

    // prepare MsgStram for Logging
    if( NULL == CMsgStream() )
    {
        int retval = InitializeCMsgStream();
        if( 0 != retval ) return retval;
    }

    // check current state
    if( !IsGoodState() )
    {
        if( NULL != CMsgStream() ) ExternalError(CMsgStream(), CMSG_SESS);
        return ErrorState(nSTATE_FATALERROR);
    }

    if( 0 != m_Connection.get() )
    {
        if( !m_Connection->getDbSqlConnection().isNull() )
        {
            if( !m_Connection->getDbSqlConnection().isOpen() )
            {
                nDBConnect(m_SessionInitialization.getDBConnectionString());
                setProcessId();
            }
        }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
int pxSession::OpenDBConnection()
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerSession(), "pxSession::OpenDBConnection()" );

    ClearError();
    int retval = 0; // return value

    retval = prepareSession();
    if( 0 != retval ) { return retval; }

    // check connection state
    if( 0 == m_Connection.get() )
    {
        if( NULL != CMsgStream() ) ExternalError(CMsgStream(), CMSG_SESS_NULLCONNECTION);
        return ErrorState(nSTATE_FATALERROR);
    }

    if( !m_SessionInitialization.isConnectionStringSet() )
    {
       return ExternalError(nMessage(pxErrorMsg(pxMSGNUM_SESSION_PARM)));
    }

    /*----------------------------------------------------------------------------*/
    /*  Connect data base and initialize the order entry system.                  */
    /*----------------------------------------------------------------------------*/
    std::stringstream ss;
    ss << "pxSession::Open(): DataSource_<" << m_SessionInitialization.getDBConnectionString() << ">";
    BLOG_TRACE( libcsc::LoggerPool::getLoggerSession(), ss.str().c_str() );

    retval = nDBConnect(m_SessionInitialization.getDBConnectionString());
    if (retval == NULL)
    {
        prepareSession();
    }
    InitMailGate();
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
void pxSession::InitMailGate()
{
    pxCremaMailList l(this);
    tCREMAMAIL m = l.SelectSmtpServer();
    m_SmtpServer = m.SERVER;
    m_SmtpServer.trim();
    m_SmtpPort = static_cast<short>(m.PORT);
}

/*----------------------------------------------------------------------------*/
void pxSession::setProcessId()
{
#ifdef WIN32
    m_ProcessNumber = _getpid();          // get processid
#else
    m_ProcessNumber = getpid();           // get processid
#endif
}

/*----------------------------------------------------------------------------*/
/*  Close the session.                                                        */
/*----------------------------------------------------------------------------*/
int pxSession::Close()
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerSession(), "pxSession::Close()" );
    if( true == m_ConnectionOwnership ) // only close the connection if we opened it by ourself
    {
        if( 0 != m_Connection.get() )
        {
            return nDBDisConnect();
        }
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
/*  Read and process the application profile.                                 */
/*----------------------------------------------------------------------------*/
int pxSession::ReadProfile(const basar::VarString& file)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxSession::ReadProfile()");

    libcsc::util::ConfigFileReader reader(file, libcsc::util::ConfigFileReader::CONFIG_FORMAT_INI);
    if (false == reader.read())
    {
        return ExternalError(nMessage(pxErrorMsg(pxMSGNUM_OPENINI)));
    }
    m_SessionInitialization.setMessageFileName(reader.getEnvString("Generic.MessageFile"));
    m_SessionInitialization.setConnectionString(reader.getString("Session.DataSource"));
    basar::VarString deviceName = reader.getString("Session.DeviceName");
    if (false == deviceName.empty())
    {
        m_SessionInitialization.setDeviceName(deviceName);
        Device()->Name(deviceName.c_str());
    }
    m_SessionInitialization.setCountryCode(reader.getString("Session.Country"));

    pxDeviceType t;
    if (::IsValidDevice(t =(pxDeviceType)reader.getInt("Session.DeviceType")))
    {
        m_SessionInitialization.setDeviceType(t);
        Device()->Type(t);
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Write to log file.                                                        */
/*----------------------------------------------------------------------------*/
void pxSession::WriteLog( const nString& message, nErrorState state, int msgid )
{
    //! \note workaround for messages from message.txt: cut trailing newline from message
    basar::VarString logMessage(message());
    if(logMessage.length() > 0 && '\n' == logMessage.at(logMessage.length()-1) )
    {
        logMessage = logMessage.substr(0, logMessage.length() - 1);
    }

    std::stringstream s;
    s << "MESSAGE_ID : " << msgid << "  DEVICE : " << Device()->Name() << " " << logMessage;
    switch (state)
    {
        case nSTATE_GOOD :
            BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s.str());
            break;
        case nSTATE_CONDITION :
            BLOG_WARN(libcsc::LoggerPool::getLoggerSession(), s.str());
            break;
        case nSTATE_ERROR :
        default :
            BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), s.str());
            break;
    }
}

/*----------------------------------------------------------------------------*/
/*  Virtual functions inherited from nDataBase.                               */
/*----------------------------------------------------------------------------*/
int pxSession::Connect(const std::string& datasrc)
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerSession(), "pxSession::Connect()" );

    std::stringstream ss;
    ss << "pxSession::Connect(): datasrc<" << datasrc << ">";
    BLOG_TRACE( libcsc::LoggerPool::getLoggerSession(), ss.str().c_str() );

    basar::VarString dataSource( datasrc );
    basar::cmnutil::CollBString coll = dataSource.tokenize( "@" );
    try
    {
        pxConnect();
        if( m_Connection->getDbSqlConnection().isNull() )
        {
            m_Connection->open( coll[ 1 ], coll[ 0 ] );
        }
        else if( !m_Connection->getDbSqlConnection().isOpen() )
        {
            m_Connection->open( coll[ 1 ], coll[ 0 ] );
        }
    }
    catch( const basar::Exception & e )
    {
        BLOG_ERROR( libcsc::LoggerPool::getLoggerSession(), e.what() );
        int retval = cDBXR_ISDOWN;
        nDBDiagnostic( Error(), retval );
        return retval;
    }

    return 0;
}

/*----------------------------------------------------------------------------*/
int pxSession::GetSqlCode()
{
    return boost::numeric_cast<int>(pxSQLCode());
}

/*----------------------------------------------------------------------------*/
int pxSession::GetIsamCode()
{
    return boost::numeric_cast<int>(pxISAMCode());
}

/*----------------------------------------------------------------------------*/
bool pxSession::IsOpen() const
{
    if (m_Connection->getDbSqlConnection().isNull())
        return false;
    return m_Connection->getDbSqlConnection().isOpen();
}

/*----------------------------------------------------------------------------*/
const std::string pxSession::GetSqlMessage()
{
    return pxSQLMessage();
}

/*----------------------------------------------------------------------------*/
const std::string pxSession::GetTableName()
{
    int fktnr = pxFunctionNr();
    int tableid = fktnr / 10;
    nMessage msg(CMsgStream(), CMSG_TABLES + tableid);
    return msg.String()();
}

/*----------------------------------------------------------------------------*/
const std::string pxSession::GetFunctionName()
{
    int fktnr = pxFunctionNr();
    int tableid = fktnr / 10;
    int fktid = fktnr % 10;
    int msgid;
    // Determine message ID
    if (tableid == F_ALLGEMEIN)
        msgid = CMSG_FUNCTIONS_COMMON + fktid;
    else if ( tableid == F_LOCKMANAGER)
        msgid = CMSG_FUNCTIONS_LOCKMAN + fktid;
    else
        msgid = CMSG_FUNCTIONS_TABLE + fktid;
    // Get and return function name
    nMessage msg(CMsgStream(), msgid);
    return msg.String()();
}

/*----------------------------------------------------------------------------*/
const basar::VarString pxSession::getDatabaseName( const short FilialNr )
{
    pxComputer* computer = ComputerList()->Find(FilialNr);
    basar::VarString name;
    if (NULL != computer)
    {
        nString compu = computer->DBName();
        compu.Strip();
        if (!compu.IsEmpty())
        {
            name = compu();
        }
    }
    return name;
}

/*----------------------------------------------------------------------------*/
const basar::VarString pxSession::getDatabaseNameWarehouse(const short FilialNr)
{
    pxComputer* computer = ComputerList()->Find(FilialNr);
    basar::VarString name;
    if (NULL != computer)
    {
        nString compu = computer->DBNameWarehouse();
        compu.Strip();
        if (!compu.IsEmpty())
        {
            name = compu();
        }
    }
    return name;
}

/*----------------------------------------------------------------------------*/
int pxSession::DisConnect()
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerSession(), "pxSession::DisConnect()" );
    try
    {
        pxDisconnect();
        m_Connection->close();
    }
    catch( const basar::Exception & e )
    {
        //! \todo FN untersuchen, warum die exception z.B. bei zaapunix und umktreiber regelmässig kommt...
        BLOG_INFO( libcsc::LoggerPool::getLoggerSession(), e.what() );
        return cDBXR_IOERROR;
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
int pxSession::BeginTransaction()
{
   return pxBegin();
}

/*----------------------------------------------------------------------------*/
int pxSession::Commit()
{
    return pxCommit();
}

/*----------------------------------------------------------------------------*/
int pxSession::RollBack()
{
    return pxRollback();
}

/*----------------------------------------------------------------------------*/
/*  IsNewOrder:this is a methode for the XML interface                        */
/*  it looks for the opening hours for the Order Entry System in VZ           */
/*  Keytype = 5                                                               */
/*  Returns: true for Videodevices and for NonVideo depending on             */
/*           timetypelist                                                     */
/*----------------------------------------------------------------------------*/
bool pxSession::IsNewOrder(const short VZ)
{
    bool retval = true;
    nString key;

    pxTimeTypeList timelist(this);
    timelist.Select(Type_ADS_OPEN_FOR_ORDER_ENTRY, key, VZ);
    if (timelist.Entries())
    {
        retval = timelist.TimeInWindow();
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
pxDiscountOrdTypList* pxSession::DiscountOrderTypList()
{
    if( NULL == m_DiscountOrderTypeList )
    {
        m_DiscountOrderTypeList = new pxDiscountOrdTypList(this);
        m_DiscountOrderTypeList->Select();
    }
    return m_DiscountOrderTypeList;
}

/*----------------------------------------------------------------------------*/
pxHoliDayList* pxSession::HoliDayList( const short VZ )
{
    if( NULL == m_HoliDayList )
    {
        m_HoliDayList = new pxHoliDayList(this);
        m_HoliDayList->Select(VZ);
        if( m_HoliDayList->Entries() )
        {
            m_HoliDayList->CalculateDates();
        }
        return m_HoliDayList;
    }

    if( !m_HoliDayList->Find(VZ) )
    {
        pxHoliDayList* tmplist = new pxHoliDayList(this);
        m_HoliDayList->Select(VZ);
        pxHoliDayListIter cursor(*tmplist);
        pxHoliDay* newentryp  = NULL;
        pxHoliDay* entryp = NULL;
        while( (entryp = (pxHoliDay*) ++cursor) != NULL )
        {
            m_HoliDayList->Append(newentryp = new pxHoliDay(this, entryp));
        }
        delete tmplist;
        tmplist = NULL;
        m_HoliDayList->CalculateDates();
    }

    return m_HoliDayList;
}

/*----------------------------------------------------------------------------*/
/* TaxRatesList:                                                              */
/*----------------------------------------------------------------------------*/
pxTaxRatesList* pxSession::TaxRatesList()
{
    if( NULL == m_TaxRatesList )
    {
        m_TaxRatesList = new pxTaxRatesList(this);
        m_TaxRatesList->Select();
    }
    return m_TaxRatesList;
}

/*----------------------------------------------------------------------------*/
/* SepOrderArtGroupList                                                       */
/*----------------------------------------------------------------------------*/
pxSepOrderArtGroupList* pxSession::SepOrderArtGroupList( const short VZ )
{
    if( NULL == m_SepOrderArtGroupList )
    {
        m_SepOrderArtGroupList = new pxSepOrderArtGroupList(this);
        m_SepOrderArtGroupList->Select(VZ);
        return m_SepOrderArtGroupList;
    }

    if( !m_SepOrderArtGroupList->Find(VZ) )
    {
        pxSepOrderArtGroupList* tmplist = new pxSepOrderArtGroupList(this);
        tmplist->Select(VZ);
        pxSepOrderArtGroupListIter cursor(*tmplist);
        pxSepOrderArtGroup* entryp  = NULL;
        pxSepOrderArtGroup* newentryp  = NULL;
        while( (entryp = (pxSepOrderArtGroup*) ++cursor) != NULL )
        {
            m_SepOrderArtGroupList->Append( newentryp = new pxSepOrderArtGroup(this, entryp) );
        }
        delete tmplist;
        tmplist = NULL;
    }

    return m_SepOrderArtGroupList;
}

/*----------------------------------------------------------------------------*/
/* TcaSessionList                                                             */
/*----------------------------------------------------------------------------*/
pxTcaSessionList* pxSession::TcaSessionList()
{
    if( NULL == m_TcaSessionList )
    {
        m_TcaSessionList = new pxTcaSessionList();
    }
    return m_TcaSessionList;
}

/*----------------------------------------------------------------------------*/
/* GeneralCalcAvpList                                                         */
/*----------------------------------------------------------------------------*/
pxGeneralCalcAvpList* pxSession::GeneralCalcAvpList()
{
    if( NULL == m_GeneralCalcAvpList )
    {
        m_GeneralCalcAvpList = new pxGeneralCalcAvpList(this);
        m_GeneralCalcAvpList->Select();
        if( 0 == m_GeneralCalcAvpList->Entries() )
        {
            delete m_GeneralCalcAvpList;
            m_GeneralCalcAvpList = NULL;
        }
    }
    return m_GeneralCalcAvpList;
}

/*----------------------------------------------------------------------------*/
/* IBTTypeList                                                                */
/*----------------------------------------------------------------------------*/
pxIBTTypeList* pxSession::IBTTypeList()
{
    if( NULL == m_IBTTypeList )
    {
        m_IBTTypeList = new pxIBTTypeList(this);
        m_IBTTypeList->Select();
        if (!m_IBTTypeList->IsGoodState())
        {
            std::stringstream s;
            s << "!m_IBTTypeList->IsGoodState(): " << m_IBTTypeList->ErrorMsg();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), s.str());
        }
    }
    return m_IBTTypeList;
}

/*----------------------------------------------------------------------------*/
boost::shared_ptr<pxStockBooking> pxSession::getStockBooking()
{
    if (NULL == m_StockBooking.get())
    {
        m_StockBooking = boost::shared_ptr<pxStockBooking>(new pxStockBooking(this));
    }
    return m_StockBooking;
}

/*----------------------------------------------------------------------------*/
void pxSession::resetStockBooking()
{
    m_StockBooking.reset();
}

/*----------------------------------------------------------------------------*/
libcsc::discount::IDiscountCollectionFinderPtr pxSession::getDiscountCollectionFinder()
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxSession::getDiscountCollectionFinder()");
    return m_DiscountComponentManager->createDiscountCollectionFinder();
}

/*----------------------------------------------------------------------------*/
libcsc::discount::IOrderPositionDiscountFinderPtr pxSession::getOrderPositionDiscountFinder()
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerSession(), "pxSession::getOrderPositionDiscountFinder()" );
    return m_DiscountComponentManager->createOrderPositionDiscountRepository();
}

/*----------------------------------------------------------------------------*/
libcsc::discount::IOrderPositionDiscountRepositoryPtr pxSession::getOrderPositionDiscountRepository()
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxSession::getOrderPositionDiscountFinder()");
    return m_DiscountComponentManager->createOrderPositionDiscountRepository();
}

/*----------------------------------------------------------------------------*/
libcsc::discount::ITenderDiscountFinderPtr pxSession::getTenderDiscountFinder()
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerSession(), "pxSession::getTenderDiscountFinder()" );
    return m_DiscountComponentManager->createTenderDiscountRepository();
}

/*----------------------------------------------------------------------------*/
libcsc::tender::ITenderRepositoryPtr pxSession::getTenderRepository()
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerSession(), "pxSession::getTenderRepository()" );
    return m_TenderComponentManager->createTenderRepository();
}

/*----------------------------------------------------------------------------*/
libcsc::base::IRunnablePtr pxSession::getPositionDiscountCalcUC( pxOrderItem * orderItem )
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerSession(), "pxSession::getPositionDiscountCalcUC()" );
    return m_DiscountComponentManager->getPositionDiscountCalcUC( orderItem );
}

/*----------------------------------------------------------------------------*/
libcsc::base::IRunnablePtr pxSession::getOrderDiscountCalcUC( pxOrder * order )
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerSession(), "pxSession::getOrderDiscountCalcUC()" );
    return m_DiscountComponentManager->getOrderDiscountCalcUC( order );
}

libcsc::crema::CremaComponentManagerPtr pxSession::getCremaComponentManager()
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxSession::getCremaComponentManager()");
    return m_CremaComponentManager;
}

libcsc::cscordertype::CSCOrderTypeComponentManagerPtr pxSession::getCSCOrderTypeComponentManager()
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxSession::getCSCOrderTypeComponentManager()");
    return m_CSCOrderTypeComponentManager;
}

libcsc::cscorder::CSCOrderComponentManagerPtr pxSession::getCSCOrderComponentManager()
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerSession(), "pxSession::getCSCOrderComponentManager()" );
    return m_CSCOrderComponentManager;
}

libcsc::cscorderpos::CSCOrderposComponentManagerPtr pxSession::getCSCOrderposComponentManager()
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxSession::getCSCOrderposComponentManager()");
    return m_CSCOrderposComponentManager;
}

libcsc::customer::CustomerComponentManagerPtr pxSession::getCustomerComponentManager()
{
    return m_CustomerComponentManager;
}

libcsc::ibt::IbtComponentManagerPtr pxSession::getIbtComponentManager()
{
    return m_IbtComponentManager;
}

libcsc::stockbooking::StockBookingComponentManagerPtr pxSession::getStockBookingComponentManager()
{
    return m_StockBookingComponentManager;
}

libcsc::parameter::ParameterComponentManagerPtr pxSession::getParameterComponentManager()
{
    return m_ParameterComponentManager;
}

libcsc::document::DocumentComponentManagerPtr pxSession::getDocumentComponentManager()
{
    return m_DocumentComponentManager;
}

libcsc::returns::ReturnComponentManagerPtr pxSession::getReturnComponentManager()
{
    return m_ReturnsComponentManager;
}

libcsc::workingdayscalendar::WorkingdaysCalendarComponentManagerPtr pxSession::getWorkingdaysCalendarComponentManager()
{
    return m_WorkingdaysCalendarComponentManager;
}

libcsc::blockedarticles::BlockedArticlesComponentManagerPtr pxSession::getBlockedArticlesComponentManager()
{
    return m_BlockedArticlesComponentManager;
}

libcsc::shipmenttracking::ShipmentTrackingComponentManagerPtr pxSession::getShipmentTrackingComponentManager()
{
    return m_ShipmentTrackingComponentManager;
}



libcsc::sud::IWorkupCompletedCheckerPtr pxSession::getSudWorkupCompletedChecker()
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerSession(), "pxSession::getSudWorkupCompletedChecker()" );
    return m_SudComponentManager->getWorkupCompletedChecker();
}


bool pxSession::isExportPermitted(short const branchNo, long const customerNo, long const articleNo)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxSession::IsExportPermitted()");
    pxCustBase customer(this, branchNo, customerNo);
    if (!customer.IsGoodState())
    {
        Error() = customer.Error();
        return false;
    }
    ClearError();
    try
    {
        return m_ProcurementPermissionComponentManager->getRepository()->isExportPermitted((char const*)customer.Land(), articleNo);
    }
    catch (libcsc::exceptions::PersistenceException& ex)
    {
        ExternalCondition(CMsgStream(), CMSG_MISC_EXCEPTION, ex.reason().c_str());
    }
    catch (basar::Exception& ex)
    {
        ExternalCondition(CMsgStream(), CMSG_MISC_EXCEPTION, ex.what().c_str());
    }
    return false;
}

ICallbackComponentManagerPtr pxSession::getCallbackComponentManager()
{
    return m_CallbackComponentManager;
}

/*----------------------------------------------------------------------------*/
const basar::VarString& pxSession::Country() const
{
    return m_SessionInitialization.getCountryCode();
}

/*----------------------------------------------------------------------------*/
const basar::VarString& pxSession::DataSource() const
{
    return m_SessionInitialization.getDBConnectionString();
}


/*----------------------------------------------------------------------------*/
void pxSession::CloseTcaSessions()
{
    pxTcaSessionList* tcasessions = TcaSessionList();
    pxTcaSession* curp;
    pxTcaSessionListIter cursor( *tcasessions );
    while ( (curp = (pxTcaSession*) ++cursor) != NULL )
    {
        curp->DisconnectFromCics();
    }
}

/*----------------------------------------------------------------------------*/
/*  SetSubDeviceType: this fuction selects the Devicename from table          */
/*  oeorigintypes. If entry found, it sets the SubDeviceType_ depend on entry,*/
/*  otherwise SubDeviceType is set to zero                                    */
/*----------------------------------------------------------------------------*/
void pxSession::SetSubDeviceType( const nString& DeviceName )
{
    m_SubDeviceType = PHONO;
    pxOeOriginTypesList* typelist = NULL;
    pxOeOriginTypes*     typelistentry = NULL;

    typelist = new pxOeOriginTypesList(this);
    typelist->Select(DeviceName);
    if ( typelist->Entries() )
    {
        typelistentry = (pxOeOriginTypes*)typelist->At(0);
    }
    if ( typelistentry )
    {
        m_SubDeviceType = static_cast<OeOriginTypeEnum>(typelistentry->OriginType());
    }
}

/*----------------------------------------------------------------------------*/
/*  GetTcaSessionEntry: Initialize a tcasession by reading                     */
/*  tcaconfig%branchno file from the INI_PATH environment                     */
/*----------------------------------------------------------------------------*/
pxTcaSession* pxSession::GetTcaSessionEntry( const short BranchNo )
{
    // return TCA session if there is one available for this branch
    pxTcaSession* tcasession = NULL;
    if ( TcaSessionList() )
    {
        tcasession = TcaSessionList()->Find( BranchNo );
        if ( tcasession )
            return tcasession;
    }

    char* envir = getenv("INI_PATH");
    basar::VarString inifile;
    if (NULL != envir)
    {
        inifile.format("%s/tcaconfig%02d.ini", envir, BranchNo);
    }
    else
    {
        inifile.format("../tcaconfig%02d.ini", BranchNo);
    }

    // Read in port and more
    libcsc::util::ConfigFileReader reader(inifile, libcsc::util::ConfigFileReader::CONFIG_FORMAT_INI);
    if (false == reader.read())
    {
        ExternalError(nMessage(pxErrorMsg(pxMSGNUM_OPENINI)));
        return tcasession;
    }

    tcasession = new pxTcaSession(BranchNo);
    tcasession->SetBranchNo( BranchNo);
    nString config_name = reader.getString("Session.TCA_CONFIG_NAME").c_str();
    nString host_ip     = reader.getString("Session.TCA_HOST_IP").c_str();
    nString host_port   = reader.getString("Session.TCA_HOST_PORT").c_str();
    nString starttrans  = reader.getString("Session.TCA_STARTTRANS").c_str();
    nString user        = reader.getString("Session.TCA_USER").c_str();
    nString passwd      = reader.getString("Session.TCA_PASSWD").c_str();

    tcasession->SetTcaConfigName(config_name);
    tcasession->SetTcaHostIp(host_ip);
    tcasession->SetTcaHostPort(host_port);
    tcasession->SetTcaStartTransId(starttrans);
    tcasession->SetTcaUser(user);
    tcasession->SetTcaPassWord(passwd);

    TcaSessionList()->Append(tcasession);

return tcasession;
}

/*----------------------------------------------------------------------------*/
/*  pxCommTypeList_ we now select the stocktranslist via BranchNo             */
/*----------------------------------------------------------------------------*/
pxOrderValidTransList* pxSession::OrderValidTransList( const short BranchNo )
{
    if( NULL == m_OrderValidTransList )
    {
        m_OrderValidTransList = new pxOrderValidTransList(this);
    }

    pxOrderValidTransList* tmplist = NULL;
    pxOrderValidTrans* vtp;
    pxOrderValidTrans* newvtp = NULL;

    if( m_OrderValidTransList )
    {
        if( 0 == m_OrderValidTransList->Entries() )
        {
            m_OrderValidTransList->Select(BranchNo);
            if( 0 == m_OrderValidTransList->Entries() )
            {
                nMessage table(CMsgStream(), CMSG_TABLES + F_AUFTRAGARTKOMB);
                nMessage error(CMsgStream(), CMSG_SESS_NOORDERVALIDTRANS);
                WriteLog(table.String() + error.String(), nSTATE_ERROR, CMSG_SESS_NOORDERVALIDTRANS );
            }
            return m_OrderValidTransList;
        }

        if( !m_OrderValidTransList->Find(BranchNo) )
        {
            tmplist = new pxOrderValidTransList(this);
            tmplist->Select(BranchNo);
            pxOrderValidTransListIter cursor(*tmplist);
            while( (vtp = (pxOrderValidTrans*) ++cursor) != NULL )
            {
                m_OrderValidTransList->Append(newvtp= new pxOrderValidTrans(this, vtp));
            }
            delete tmplist;
            tmplist = NULL;
        }
    }

    return m_OrderValidTransList;
}

/*----------------------------------------------------------------------------*/
/*  pxCommTypeList_ we now select the stocktranslist via BranchNo             */
/*----------------------------------------------------------------------------*/
pxCommTypeList* pxSession::CommTypeList( const short BranchNo )
{
    if( NULL == m_CommTypeList )
    {
        m_CommTypeList = new pxCommTypeList(this);
    }

    pxCommTypeList* tmplist = NULL;
    pxCommType* ct;
    pxCommType* newct = NULL;

    if( m_CommTypeList )
    {
        if( m_CommTypeList->Entries() == 0 )
        {
            m_CommTypeList->Select(BranchNo);
            if( 0 == m_CommTypeList->Entries() )
            {
                nMessage table(CMsgStream(), CMSG_TABLES + F_KOMMIARTEN);
                nMessage error(CMsgStream(), CMSG_SESS_NOCOMMTYPE);
                WriteLog( table.String() + error.String(), nSTATE_ERROR, CMSG_SESS_NOCOMMTYPE );
            }
            return m_CommTypeList;
        }

        if( !m_CommTypeList->Find(BranchNo) )
        {
            tmplist = new pxCommTypeList(this);
            tmplist->Select(BranchNo);
            pxCommTypeListIter cursor(*tmplist);
            while( (ct = (pxCommType*) ++cursor) != NULL )
            {
                m_CommTypeList->Append(newct = new pxCommType(this, ct));
            }
            delete tmplist;
            tmplist = NULL;
        }
    }
    return m_CommTypeList;
}

/*----------------------------------------------------------------------------*/
/*  pxStockTransList_ we now select the stocktranslist via BranchNo           */
/*----------------------------------------------------------------------------*/
pxStockTransList* pxSession::StockTransList( const short BranchNo )
{
    if( NULL == m_StockTransList )
    {
        m_StockTransList = new pxStockTransList(this);
    }

    pxStockTransList* tmplist = NULL;
    pxStockTrans* stk;
    pxStockTrans* newstk = NULL;
    if( m_StockTransList )
    {
        if( 0 == m_StockTransList->Entries() )
        {
            m_StockTransList->Select(BranchNo);
            if( 0 == m_StockTransList->Entries() )
            {
                nMessage table(CMsgStream(), CMSG_TABLES + F_KDAUFTRAGART);
                nMessage error(CMsgStream(), CMSG_SESS_NOORDERTYPE);
                WriteLog( table.String() + error.String(), nSTATE_ERROR, CMSG_SESS_NOORDERTYPE );
            }
            return m_StockTransList;
        }

        if( !m_StockTransList->Find(BranchNo) )
        {
            tmplist = new pxStockTransList(this);
            tmplist->Select(BranchNo);
            pxStockTransListIter cursor(*tmplist);
            while( (stk = (pxStockTrans*) ++cursor) != NULL )
            {
                m_StockTransList->Append(newstk = new pxStockTrans(this, stk));
            }
            delete tmplist;
            tmplist = NULL;
        }
    }

    return m_StockTransList;
}

/*----------------------------------------------------------------------------*/
/*  pxOrderTypeList: we now select the ordertyplist via BranchNo              */
/*----------------------------------------------------------------------------*/
pxOrderTypeList* pxSession::OrderTypeList( const short BranchNo )
{
    if( NULL == m_OrderTypeList )
    {
        m_OrderTypeList = new pxOrderTypeList (this);
    }

    pxOrderTypeList* tmplist = NULL;
    pxOrderType* otp;
    pxOrderType* newotp = NULL;
    if( m_OrderTypeList )
    {
        if( 0 == m_OrderTypeList->Entries() )
        {
            m_OrderTypeList->Select(BranchNo);
            if( 0 == m_OrderTypeList->Entries() )
            {
                nMessage table(CMsgStream(), CMSG_TABLES + F_KDAUFTRAGART);
                nMessage error(CMsgStream(), CMSG_SESS_NOORDERTYPE);
                WriteLog( table.String() + error.String(), nSTATE_ERROR, CMSG_SESS_NOORDERTYPE );
            }
            return m_OrderTypeList;                  // return this list
        }

        if( !m_OrderTypeList->Find(BranchNo) )
        {
            tmplist = new pxOrderTypeList(this);
            tmplist->Select(BranchNo);
            pxOrderTypeListIter cursor(*tmplist);
            while ( (otp = (pxOrderType*) ++cursor) != NULL )
            {
                m_OrderTypeList->Append(newotp = new pxOrderType(this, otp));
            }
            delete tmplist;
            tmplist = NULL;
        }
    }

    return m_OrderTypeList;
}

/*----------------------------------------------------------------------------*/
bool pxSession::isCheckPriceLimitationSet() const
{
    static bool loaded = false;
    static bool checkPriceLimitationSet = false;

    if (true == isBulgaria())
    {
        if (false == loaded)
        {
            pxParameter param(const_cast<pxSession*>(this), 0, cPAR_KSC_GROUP, cPAR_KSCSERVER_PURPOSE_CHECKPRICELIMITATION, cPAR_KSCSERVER_PARAMNAME);
            if (param.Get() == 0)
            {
                if (param.Wert() == 1)
                {
                    checkPriceLimitationSet = true;
                }
            }

            loaded = true;
        }
    }

    return checkPriceLimitationSet;
}

/*----------------------------------------------------------------------------*/
bool pxSession::isAustria() const
{
    if( pxSession::COUNTRY_AUSTRIA == m_SessionInitialization.getCountryCode() || pxSession::COUNTRY_AUSTRIA_PREWHOLE == m_SessionInitialization.getCountryCode() )
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
bool pxSession::isBulgaria() const
{
    if( pxSession::COUNTRY_BULGARIA == m_SessionInitialization.getCountryCode() )
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
bool pxSession::isCroatia() const
{
    if( pxSession::COUNTRY_CROATIA == m_SessionInitialization.getCountryCode() )
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
bool pxSession::isFrance() const
{
    if( pxSession::COUNTRY_FRANCE == m_SessionInitialization.getCountryCode() )
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
bool pxSession::isFrancePrewhole() const
{
    if( pxSession::COUNTRY_FRANCE_PREWHOLE == m_SessionInitialization.getCountryCode() )
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
bool pxSession::isGermany() const
{
    if( pxSession::COUNTRY_GERMANY == m_SessionInitialization.getCountryCode() )
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
bool pxSession::isSerbia() const
{
    if( pxSession::COUNTRY_SERBIA == m_SessionInitialization.getCountryCode() )
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
bool pxSession::isSwitzerland() const
{
    if( pxSession::COUNTRY_SWITZERLAND == m_SessionInitialization.getCountryCode() )
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
short pxSession::SubDeviceType() const
{
    return static_cast<short>(m_SubDeviceType);
}

/*----------------------------------------------------------------------------*/
bool pxSession::IsSubDeviceTypeOf(OeOriginTypeEnum type) const
{
    // MSV3V1 not in db table oeorigintypes, so m_SubDeviceType will never be MSV3V1!
    if (   ((m_SubDeviceType == MSV3) && (type == MSV3V1))      // MSV3 == MSV3V1 and MSV3V1 is a MSV3
        || ((m_SubDeviceType == MSV3V2) && (type == MSV3)) )    // MSV3 != MSV3V2 and MSV3V2 is a MSV3
    {
        return true;
    }
    return (m_SubDeviceType == type);
}

/*----------------------------------------------------------------------------*/
short pxSession::UsersFilialNr() const
{
    return m_UsersFilialNr;
}

/*----------------------------------------------------------------------------*/
void pxSession::UsersFilialNr(const short fil)
{
    m_UsersFilialNr = fil;
}

/*----------------------------------------------------------------------------*/
int pxSession::LanguageCode() const
{
    return m_LanguageCode;
}

/*----------------------------------------------------------------------------*/
void pxSession::LanguageCode(const int language)
{
    m_LanguageCode = language;
}

/*----------------------------------------------------------------------------*/
pxOrder* pxSession::CurrentOrder()
{
    return m_CurrentOrder;
}

/*----------------------------------------------------------------------------*/
void pxSession::SetCurrentOrder(pxOrder* order)
{
    m_CurrentOrder = order;
}

/*----------------------------------------------------------------------------*/
void pxSession::InitCurrentOrder()
{
    m_CurrentOrder = NULL;
}

/*----------------------------------------------------------------------------*/
long pxSession::PersonnelNo() const
{
    return m_PersonalNo;
}

/*----------------------------------------------------------------------------*/
void pxSession::PersonnelNo(const long no)
{
    m_PersonalNo = no;
}

/*----------------------------------------------------------------------------*/
long pxSession::ProcessNumber() const
{
    return m_ProcessNumber;
}

/*----------------------------------------------------------------------------*/
pxBranch* pxSession::Branch()
{
    if( NULL == m_Branch )
    {
        m_Branch = new pxBranch(this, m_SessionInitialization.getBranchNo());
    }
    return m_Branch;
}

/*----------------------------------------------------------------------------*/
std::ifstream* pxSession::CMsgStream()
{
    return m_MsgStream;
}

/*----------------------------------------------------------------------------*/
pxDevice* pxSession::Device()
{
    if( NULL == m_Device )
    {
        m_Device = new pxDevice();
    }
    return m_Device;
}

/*----------------------------------------------------------------------------*/
pxComputerList* pxSession::ComputerList()
{
    if( NULL == m_ComputerList )
    {
        m_ComputerList = new pxComputerList(this);
        m_ComputerList->Select();
        if( 0 == m_ComputerList->Entries() )
        {
            nMessage table(CMsgStream(), CMSG_TABLES + F_RECHNER);
            nMessage error(CMsgStream(), CMSG_SESS_NOCOMPUTERENTRY);
            WriteLog( table.String() + error.String(), nSTATE_ERROR, CMSG_SESS_NOCOMPUTERENTRY);
        }
    }
    return m_ComputerList;
}
/*----------------------------------------------------------------------------*/
/* IBTAssortmentTypeList                                                                */
/*----------------------------------------------------------------------------*/
IBTAssortmentTypeList* pxSession::getIBTAssortmentTypeList()
{
    if( NULL == m_IBTAssortmentTypeList )
    {
        m_IBTAssortmentTypeList = new IBTAssortmentTypeList(this);
        m_IBTAssortmentTypeList->Select();
        if (!m_IBTAssortmentTypeList->IsGoodState())
        {
            std::stringstream s;
            s << "!m_IBTAssortmentTypeList->IsGoodState(): " << m_IBTAssortmentTypeList->ErrorMsg();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), s.str());
        }
    }
    return m_IBTAssortmentTypeList;
}

/*----------------------------------------------------------------------------*/
pxOrderEntryParamPtr pxSession::getOrderEntryParam( const short branchno )
{
    if (m_OrderEntryParamMap.find(branchno) == m_OrderEntryParamMap.end())
    {
        pxOrderEntryParamPtr ptr = pxOrderEntryParamPtr(new pxOrderEntryParam(this, branchno));
        m_OrderEntryParamMap.insert(std::pair<short, pxOrderEntryParamPtr>(branchno, ptr));
    }
    return m_OrderEntryParamMap.find(branchno)->second;
}

void pxSession::resetOrderEntryParam()
{
    m_OrderEntryParamMap.clear();
}

/*----------------------------------------------------------------------------*/
void pxSession::resetSepOrderArtGroupList()
{
    if( NULL != m_SepOrderArtGroupList )
    {
        delete m_SepOrderArtGroupList;
        m_SepOrderArtGroupList = NULL;
    }
}

/*----------------------------------------------------------------------------*/
int pxSession::nDBBeginTransaction(const tDBTransactLevel level )
{
    std::stringstream s;
    s << "pxSession::nDBBeginTransaction: " << level;
    BLOG_TRACE( libcsc::LoggerPool::getLoggerSession(), s.str() );
    return nDataBase::nDBBeginTransaction( level );
}

/*----------------------------------------------------------------------------*/
int pxSession::nDBCommit(const tDBTransactLevel level )
{
    std::stringstream s;
    s << "pxSession::nDBCommit: " << level;
    BLOG_TRACE( libcsc::LoggerPool::getLoggerSession(), s.str() );
    return nDataBase::nDBCommit( level );
}

/*----------------------------------------------------------------------------*/
int pxSession::nDBRollBack()
{
    std::stringstream s;
    s << "pxSession::nDBRollBack: " << nDBTransactLevel();
    BLOG_TRACE( libcsc::LoggerPool::getLoggerSession(), s.str() );
    return nDataBase::nDBRollBack();
}

/*----------------------------------------------------------------------------*/
void pxSession::nDBSetExplainOn()
{
    // TODO check that we are on TEST system!
    return m_Connection->setExplainOn();
}

/*----------------------------------------------------------------------------*/
void pxSession::nDBSetExplainOff()
{
    // TODO check that we are on TEST system!
    return m_Connection->setExplainOff();
}

/*----------------------------------------------------------------------------*/
const basar::VarString& pxSession::getSmtpServer() const
{
    return m_SmtpServer;
}

/*----------------------------------------------------------------------------*/
short pxSession::getSmtpPort() const
{
    return m_SmtpPort;
}

/*----------------------------------------------------------------------------*/
bool pxSession::getIgnoreOrderPeriodDD()
{
    return m_IgnoreOrderPeriodDD;
}

/*----------------------------------------------------------------------------*/
void pxSession::SetIgnoreOrderPeriodDDfromDB(const short branchNo)
{
    //Parameteres for getting branchAllowingDelayedOrderConsoldation flag
    nString programName("cscservice");
    nString objective_ConsolDelDeliv("IgnoreOrderPeriodDD");
    nString paramName_AllowConsDelDeliv("IgnoreOrderPeriodDD");
    pxParameter* param1;
    param1 = new pxParameter(this, branchNo, programName, objective_ConsolDelDeliv,
        paramName_AllowConsDelDeliv);
    param1->Get(cDBGET_READONLY);
    m_IgnoreOrderPeriodDD = param1->Wert();
}