#ifndef PXSESS_HPP
#define PXSESS_HPP

class pxBranch;
class pxDevice;
class pxOrderTypeList;
class pxStockTransList;
class pxCommTypeList;
class pxOrderValidTransList;
class pxDiscountOrdTypList;
class pxOrder;
class pxOrderItem;
class pxComputerList;
class pxHoliDayList;
class pxTaxRatesList;
class pxSepOrderArtGroupList;
class pxTcaSession;
class pxTcaSessionList;
class pxGeneralCalcAvpList;
class pxIBTTypeList;
class pxStockBooking;
class IBTAssortmentTypeList;

#include <map>
#include "database.hpp"
#include "pxsessioninitialization.h"
#include "pxorderentryparamptr.h"
#include "oeorigintypeenum.h"
#include <persistence/connectionptr.h>
#include <crema/componentmanager/cremacomponentmanagerptr.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountfinderptr.h>
#include <discount/tender/repository/itenderdiscountfinderptr.h>
#include <tender/repository/itenderrepositoryptr.h>
#include <discount/componentmanager/discountcomponentmanagerptr.h>
#include <tender/componentmanager/tendercomponentmanagerptr.h>
#include <subseqdelivery/componentmanager/sudcomponentmanagerptr.h>
#include <subseqdelivery/workupcompletedchecker/iworkupcompletedcheckerptr.h>
#include <procurementpermission/componentmanager/componentmanagerptr.h>
#include <base/irunnableptr.h>
#include <cscorder/componentmanager/cscordercomponentmanagerptr.h>
#include <cscorderpos/componentmanager/cscorderposcomponentmanagerptr.h>
#include "icallbackcomponentmanager.hpp"
#include <ibt/componentmanager/ibtcomponentmanagerptr.h>
#include <stockbooking/componentmanager/stockbookingcomponentmanagerptr.h>
#include <parameter/componentmanager/parametercomponentmanagerptr.h>
#include <cscordertype/componentmanager/cscordertypecomponentmanagerptr.h>
#include <document/componentmanager/documentcomponentmanagerptr.h>
#include <returns/componentmanager/returncomponentmanagerptr.h>
#include <customer/componentmanager/customercomponentmanagerptr.h>
#include <workingdayscalendar/componentmanager/workingdayscalendarcomponentmanagerptr.h>
#include <blockedarticles/componentmanager/blockedarticlescomponentmanagerptr.h>
#include <shipmenttracking/componentmanager/shipmenttrackingcomponentmanagerptr.h>

#include <liblockmanager/lockguard/ilockguardfactoryptr.h>
#include <liblockmanager/lockguard/ilockguardptr.h>
#include <liblockmanager/lockmanager/ilockmanagerptr.h>
#include <liblockmanager/lock/ikeyptr.h>
#include <liblockmanager/infrastructure/accessor/idblockaccessorfactoryptr.h>

#include <discount/discountcollectionfinder/idiscountcollectionfinderptr.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepositoryptr.h>
#include <discount/componentmanager/discountcomponentmanagerptr.h>

class pxSession : public nDataBase
{
	public:

		static const char* COUNTRY_AUSTRIA;
		static const char* COUNTRY_AUSTRIA_PREWHOLE;
		static const char* COUNTRY_BULGARIA;
		static const char* COUNTRY_CROATIA;
		static const char* COUNTRY_GERMANY;
		static const char* COUNTRY_FRANCE_PREWHOLE;
		static const char* COUNTRY_FRANCE;
		static const char* COUNTRY_SERBIA;
		static const char* COUNTRY_SWITZERLAND;

		//////////////////////////////////////////////// C O N S T R U C T / D E S T R U C T ////////////////////////////////////////////////

															                pxSession( const pxSessionInitialization& );  // connection has to be set using injectDBConnection

															                pxSession( const basar::VarString& IniFileName, const short sFilialNr = 0 );

															                pxSession(  const short branchNo,
															                			const basar::VarString& countryCode,
															                			const basar::VarString& dataSource,
															                			const ::pxDeviceType deviceType,
															                			const basar::VarString& deviceName,
															                			const basar::VarString& messageFileName );

		virtual                                                             ~pxSession();

		//////////////////////////////////////////////// C O N S T R U C T / D E S T R U C T ////////////////////////////////////////////////

		//////////////////////////////////////////////// I N J E C T S ////////////////////////////////////////////////

		void                                                                injectDBConnection( libcsc::persistence::ConnectionPtr connection );

		//////////////////////////////////////////////// I N J E C T S ////////////////////////////////////////////////

		//////////////////////////////////////////////// G E T T E R ////////////////////////////////////////////////

		const basar::VarString&                                             Country() const;
		const basar::VarString&                                             DataSource() const;
		const basar::VarString                                              getDatabaseName(const short FilialNr);
		const basar::VarString                                              getDatabaseNameWarehouse(const short FilialNr);
		int                                                                 LanguageCode() const;
		long                                                                PersonnelNo() const;
		long                                                                ProcessNumber() const;
		short                                                               SubDeviceType() const;
		short                                                               UsersFilialNr() const;
		const basar::VarString&								                getSmtpServer() const;
		short												                getSmtpPort() const;

		pxBranch*                                                           Branch();
		std::ifstream*                                                      CMsgStream();
		pxCommTypeList*                                                     CommTypeList( const short BranchNo );
		pxComputerList*                                                     ComputerList();

		pxOrder*                                                            CurrentOrder();
		pxDevice*                                                           Device();
		pxDiscountOrdTypList*                                               DiscountOrderTypList();
		pxGeneralCalcAvpList*                                               GeneralCalcAvpList();
		pxOrderEntryParamPtr                                                getOrderEntryParam( const short branchno );
		void                                                                resetOrderEntryParam();
		pxTcaSession*                                                       GetTcaSessionEntry( const short BranchNo );
		pxHoliDayList*                                                      HoliDayList( const short VZ );
		pxIBTTypeList*                                                      IBTTypeList();
		pxTaxRatesList*                                                     TaxRatesList();
		pxOrderTypeList*                                                    OrderTypeList( const short BranchNo );
		pxOrderValidTransList*                                              OrderValidTransList( const short BranchNo );
		pxSepOrderArtGroupList*                                             SepOrderArtGroupList( const short VZ );
		void                                                                resetSepOrderArtGroupList();
		pxStockTransList*                                                   StockTransList( const short BranchNo );
		pxTcaSessionList*                                                   TcaSessionList();
		IBTAssortmentTypeList*                                              getIBTAssortmentTypeList();
		libcsc::persistence::ConnectionPtr                                  GetConnection();

		//////////////////////////////////////////////// G E T T E R ////////////////////////////////////////////////

		//////////////////////////////////////////////// S E T T E R ////////////////////////////////////////////////

		void                                                                LanguageCode( const int language );
		void                                                                PersonnelNo( const long no );
		void                                                                SetCurrentOrder( pxOrder* order );
		void                                                                SetSubDeviceType( const nString& DeviceName );
		void                                                                UsersFilialNr( const short fil );
		void																SetIgnoreOrderPeriodDDfromDB(const short branchNo);

		//////////////////////////////////////////////// S E T T E R ////////////////////////////////////////////////

		//////////////////////////////////////////////// M E T H O D S ////////////////////////////////////////////////

		virtual int                                                         Close();
		void                                                                CloseTcaSessions();
		void                                                                InitCurrentOrder();
        bool                                                                isCheckPriceLimitationSet() const;
		bool                                                                isAustria() const;
		bool                                                                isBulgaria() const;
		bool                                                                isCroatia() const;
		bool                                                                isFrance() const;
		bool                                                                isFrancePrewhole() const;
		bool                                                                isGermany() const;
		bool                                                                isSerbia() const;
		bool                                                                IsNewOrder(const short VZ);
		bool                                                                IsSubDeviceTypeOf(OeOriginTypeEnum type) const;
		bool                                                                isSwitzerland() const;
		int                                                                 OpenDBConnection();
		int                                                                 prepareSession();
		int                                                                 ReadProfile(const basar::VarString& file);
		bool																getIgnoreOrderPeriodDD();

		virtual bool                                                        IsOpen() const;                                                     //!< \override nDatabase::IsOpen
		virtual void                                                        WriteLog(const nString& message, nErrorState state, int msgid);     //!< \override nError::WriteLog

		//////////////////////////////////////////////// M E T H O D S ////////////////////////////////////////////////


		//////////////////////////////////////////////// A P P L I C A T I O N C O N T R O L L E R ////////////////////////////////////////////////

		// TODO: pxSession treated to be an application controller at the moment. This has to be reworked to use an real application controller and injects instead!
		boost::shared_ptr<pxStockBooking>									getStockBooking();
		void																resetStockBooking();
        libcsc::crema::CremaComponentManagerPtr						        getCremaComponentManager();
        libcsc::cscordertype::CSCOrderTypeComponentManagerPtr				getCSCOrderTypeComponentManager();
		libcsc::cscorder::CSCOrderComponentManagerPtr						getCSCOrderComponentManager();
        libcsc::cscorderpos::CSCOrderposComponentManagerPtr					getCSCOrderposComponentManager();
		libcsc::customer::CustomerComponentManagerPtr						getCustomerComponentManager();
		libcsc::discount::ITenderDiscountFinderPtr							getTenderDiscountFinder();
		libcsc::discount::IOrderPositionDiscountRepositoryPtr				getOrderPositionDiscountRepository();
		libcsc::discount::IOrderPositionDiscountFinderPtr					getOrderPositionDiscountFinder();
		libcsc::discount::IDiscountCollectionFinderPtr                      getDiscountCollectionFinder();
        libcsc::tender::ITenderRepositoryPtr								getTenderRepository();
        libcsc::base::IRunnablePtr											getPositionDiscountCalcUC( pxOrderItem * orderItem );
        libcsc::base::IRunnablePtr											getOrderDiscountCalcUC( pxOrder * order );
        libcsc::ibt::IbtComponentManagerPtr									getIbtComponentManager();
		libcsc::sud::IWorkupCompletedCheckerPtr								getSudWorkupCompletedChecker();
		bool																isExportPermitted(short const branchNo, long const customerNo, long const articleNo);
		ICallbackComponentManagerPtr										getCallbackComponentManager();
		libcsc::stockbooking::StockBookingComponentManagerPtr				getStockBookingComponentManager();
		libcsc::parameter::ParameterComponentManagerPtr						getParameterComponentManager();
		libcsc::document::DocumentComponentManagerPtr						getDocumentComponentManager();
		libcsc::returns::ReturnComponentManagerPtr							getReturnComponentManager();
		libcsc::workingdayscalendar::WorkingdaysCalendarComponentManagerPtr getWorkingdaysCalendarComponentManager();
		libcsc::blockedarticles::BlockedArticlesComponentManagerPtr			getBlockedArticlesComponentManager();
        libcsc::shipmenttracking::ShipmentTrackingComponentManagerPtr		getShipmentTrackingComponentManager();


		//////////////////////////////////////////////// A P P L I C A T I O N C O N T R O L L E R ////////////////////////////////////////////////

		virtual int                                                         nDBBeginTransaction(const tDBTransactLevel level = cDBTransRecord);
		virtual int                                                         nDBCommit(const tDBTransactLevel level = cDBTransRecord);
		virtual int                                                         nDBRollBack();
		void												                nDBSetExplainOn();
		void												                nDBSetExplainOff();

		// lockmanager
		libLockManager::ILockManagerPtr                                     getCustomerOrderLockManager();
		libLockManager::IKeyPtr                                             createCustomerOrderLockKey( basar::Int32 orderNo );
		libLockManager::ILockGuardPtr                                       createCustomerOrderLockGuard( const basar::VarString& context, basar::Int32 orderNo );

	protected:

		virtual int                                                         Connect(const std::string& datasrc);
		virtual int                                                         DisConnect();
		virtual int                                                         GetSqlCode();
		virtual int                                                         GetIsamCode();
		virtual const std::string                                           GetSqlMessage();
		virtual const std::string                                           GetTableName();
		virtual const std::string                                           GetFunctionName();

	private:
		virtual int                                                         BeginTransaction();
		virtual int                                                         Commit();
		virtual int                                                         RollBack();


		void                                                                Init( const short sFilialNr );
		void                                                                InitializeDBConnection();
		libLockManager::accessor::IDBLockAccessorFactoryPtr                 getDBLockAccessorFactory();
		void                                                                InitializeComponentManagers();
		int                                                                 InitializeCMsgStream();
		void                                                                InitMailGate();
		void                                                                setProcessId();

		// member
		pxSessionInitialization                                             m_SessionInitialization;

		int                                                                 m_LanguageCode;

		long                                                                m_PersonalNo;
		long                                                                m_ProcessNumber;

		OeOriginTypeEnum                                                    m_SubDeviceType;
		short                                                               m_UsersFilialNr;

		bool                                                                m_ConnectionOwnership;
		basar::VarString                                                    m_InternalConnectionName;  // TODO remove when BASAR returns internal connection name
		basar::VarString                                                    m_LockConnectionName;   // TODO remove when BASAR returns internal connection name

		basar::VarString									                m_SmtpServer;
		short												                m_SmtpPort;
		bool																m_IgnoreOrderPeriodDD;

		// pointer member
		pxBranch*                                                           m_Branch;
		pxCommTypeList*                                                     m_CommTypeList;
		pxComputerList*                                                     m_ComputerList;
		pxOrder*                                                            m_CurrentOrder;
		pxDevice*                                                           m_Device;
		pxDiscountOrdTypList*                                               m_DiscountOrderTypeList;
		pxGeneralCalcAvpList*                                               m_GeneralCalcAvpList;
		pxHoliDayList*                                                      m_HoliDayList;
		pxIBTTypeList*                                                      m_IBTTypeList;
		std::ifstream*                                                      m_MsgStream;
		std::map<short, pxOrderEntryParamPtr>				                m_OrderEntryParamMap;
		pxOrderTypeList*                                                    m_OrderTypeList;
		pxOrderValidTransList*                                              m_OrderValidTransList;
		pxSepOrderArtGroupList*                                             m_SepOrderArtGroupList;
		pxStockTransList*                                                   m_StockTransList;
		pxTaxRatesList*                                                     m_TaxRatesList;
		pxTcaSessionList*                                                   m_TcaSessionList;
		IBTAssortmentTypeList*								                m_IBTAssortmentTypeList;


		boost::shared_ptr<pxStockBooking>					                m_StockBooking;
		// libcsc member
		libcsc::persistence::ConnectionPtr									m_Connection;
		libcsc::discount::DiscountComponentManagerPtr						m_DiscountComponentManager;
        libcsc::tender::TenderComponentManagerPtr							m_TenderComponentManager;
        libcsc::ibt::IbtComponentManagerPtr									m_IbtComponentManager;
        libcsc::crema::CremaComponentManagerPtr                             m_CremaComponentManager;
		libcsc::cscorder::CSCOrderComponentManagerPtr						m_CSCOrderComponentManager;
        libcsc::cscorderpos::CSCOrderposComponentManagerPtr					m_CSCOrderposComponentManager;
        libcsc::cscordertype::CSCOrderTypeComponentManagerPtr				m_CSCOrderTypeComponentManager;
		libcsc::customer::CustomerComponentManagerPtr						m_CustomerComponentManager;
		libcsc::procurementpermission::ComponentManagerPtr					m_ProcurementPermissionComponentManager;
		libLockManager::ILockManagerPtr										m_CustomerOrderLockManager;
		libLockManager::accessor::IDBLockAccessorFactoryPtr					m_DBLockAccessorFactory;
		libLockManager::ILockGuardFactoryPtr								m_CustomerOrderLockGuardFactory;
		ICallbackComponentManagerPtr										m_CallbackComponentManager;
		libcsc::sud::SudComponentManagerPtr									m_SudComponentManager;
		libcsc::stockbooking::StockBookingComponentManagerPtr				m_StockBookingComponentManager;
		libcsc::parameter::ParameterComponentManagerPtr						m_ParameterComponentManager;
		libcsc::document::DocumentComponentManagerPtr						m_DocumentComponentManager;
		libcsc::returns::ReturnComponentManagerPtr							m_ReturnsComponentManager;
		libcsc::workingdayscalendar::WorkingdaysCalendarComponentManagerPtr	m_WorkingdaysCalendarComponentManager;
		libcsc::blockedarticles::BlockedArticlesComponentManagerPtr			m_BlockedArticlesComponentManager;
        libcsc::shipmenttracking::ShipmentTrackingComponentManagerPtr		m_ShipmentTrackingComponentManager;
};

#endif // PXSESS_HPP

