//-------------------------------------------------------------------------------------------------//
/*! \file   kscclientdm.cpp
 *  \brief  Domain module for access to KSC-Server.
 *  \author Klaus Hinz
 *  \date   03.01.2008
 */
//-------------------------------------------------------------------------------------------------//
#include "kscclientdm.h"

//#include "utils.h"
#include <libbasardbaspect.h>
#include <libbasarlogin.h>

namespace domMod {
	KSCClientDM::KSCClientDM( log4cplus::Logger logger )
	: m_Logger( logger ),
	  m_initialized(0),
	  m_orderACC(),
	  m_orderInfoACC(),
	  m_itemACC(),
	  m_itemInfoACC(),
	  m_kscClientWrapper( logger )
	{
	BLOG_TRACE_METHOD(m_Logger, "KSCClientDM::KSCClientDM().");
	}
	
	KSCClientDM::~KSCClientDM()
	{
	BLOG_TRACE_METHOD(m_Logger, "KSCClientDM::~KSCClientDM().");

	shutdown();
  }

	//*************************************** init ******************************************************
	void KSCClientDM::init(basar::Int16 branchNo, const KSCClientDMConnParams& connParams) {
		BLOG_TRACE_METHOD(m_Logger, "KSCClientDM::init().");
		if (0 == m_initialized) {
			m_kscClientWrapper.setBranchNoDefault(branchNo);

			// open connection to KSC-server
			m_kscClientWrapper.kscConnectServerNoIni(connParams);

			// dummy db-connection for instantiating the accessors
			basar::db::aspect::ConnectionRef dummyConn;

			// at least 1 SQL builder necessary for instantiating accessors
			acc_kscclientorder::DummyBuilder a;
			acc_kscclientorderinfo::DummyBuilder b;
			acc_kscclientitem::DummyBuilder c;
			acc_kscclientiteminfo::DummyBuilder d;

			// initialize accessor instances
			m_orderACC = basar::db::aspect::Manager::getInstance().createAccessorInstance("AccKSCClientOrderInst", "AccKSCClientOrder", dummyConn);
			m_orderInfoACC = basar::db::aspect::Manager::getInstance().createAccessorInstance("AccKSCClientOrderInfoInst", "AccKSCClientOrderInfo", dummyConn);
			m_itemACC = basar::db::aspect::Manager::getInstance().createAccessorInstance("AccKSCClientItemInst", "AccKSCClientItem", dummyConn);
			m_itemInfoACC = basar::db::aspect::Manager::getInstance().createAccessorInstance("AccKSCClientItemInfoInst", "AccKSCClientItemInfo", dummyConn);
		}
		++m_initialized;
	}// init

	//*************************************** shutdown ******************************************************
	void KSCClientDM::shutdown() {
	BLOG_TRACE_METHOD(m_Logger, "KSCClientDM::shutdown().");

	if (0 == m_initialized) {
		return;
	}
	--m_initialized;

	if (0 == m_initialized) {
		// close connection to KSC-server
		m_kscClientWrapper.kscDisconnectServer();

		if(false == m_orderACC.getPropertyTable().isNull())   { 
			m_orderACC.getPropertyTable().clear(); 
			m_orderACC.getPropertyTable().reset(); 
		} 
		m_orderACC.reset();

		if(false == m_orderInfoACC.getPropertyTable().isNull())   { 
			m_orderInfoACC.getPropertyTable().clear(); 
			m_orderInfoACC.getPropertyTable().reset(); 
		} 
		m_orderInfoACC.reset();

		if(false == m_itemACC.getPropertyTable().isNull())   { 
			m_itemACC.getPropertyTable().clear(); 
			m_itemACC.getPropertyTable().reset(); 
		} 
		m_itemACC.reset();

		if(false == m_itemInfoACC.getPropertyTable().isNull())   { 
			m_itemInfoACC.getPropertyTable().clear(); 
			m_itemInfoACC.getPropertyTable().reset(); 
		} 
		m_itemInfoACC.reset();
		}// if (0 == m_initialized)
	}// shutdown

	//*************************************** getOrderPropTab ******************************************************
  basar::db::aspect::AccessorPropertyTableRef KSCClientDM::getOrderPropTab()
  {
	return m_orderACC.getPropertyTable();
  }

	//*************************************** addEmptyOrder ******************************************************
  basar::db::aspect::AccessorPropertyTable_YIterator KSCClientDM::addEmptyOrder()
  {
	return m_orderACC.getPropertyTable().insert(basar::FOR_INSERT);
  }

	//*************************************** getOrderInfoPropTab ******************************************************
  basar::db::aspect::AccessorPropertyTableRef KSCClientDM::getOrderInfoPropTab()
  {
	return m_orderInfoACC.getPropertyTable();
  }

	//*************************************** addEmptyOrderInfo ******************************************************
  basar::db::aspect::AccessorPropertyTable_YIterator KSCClientDM::addEmptyOrderInfo()
  {
	return m_orderInfoACC.getPropertyTable().insert(basar::FOR_INSERT);
  }

	//*************************************** getItemPropTab ******************************************************
  basar::db::aspect::AccessorPropertyTableRef KSCClientDM::getItemPropTab()
  {
	return m_itemACC.getPropertyTable();
  }

	//*************************************** addEmptyItem ******************************************************
  basar::db::aspect::AccessorPropertyTable_YIterator KSCClientDM::addEmptyItem()
  {
	return m_itemACC.getPropertyTable().insert(basar::FOR_INSERT);
  }

	//*************************************** getItemInfoPropTab ******************************************************
  basar::db::aspect::AccessorPropertyTableRef KSCClientDM::getItemInfoPropTab()
  {
	return m_itemInfoACC.getPropertyTable();
  }

	//*************************************** addEmptyItemInfo ******************************************************
  basar::db::aspect::AccessorPropertyTable_YIterator KSCClientDM::addEmptyItemInfo()
  {
	return m_itemInfoACC.getPropertyTable().insert(basar::FOR_INSERT);
  }

	//*************************************** openOrder ******************************************************
	//
	// Descr:	Creates an order in database.
	//
	// Changes:	Write in database AFTER checks!
	//
	//
	//********************************************************************************************************
	KSCClientDMReturn KSCClientDM::openOrder(const basar::db::aspect::AccessorPropertyTable_YIterator itOrder, bool clearBeforeSelect) {
		BLOG_TRACE_METHOD(m_Logger, "KSCClientDM::openOrder().");
		KSCClientDMReturn returnStruct;

		// prepare order info property table
		if (true == clearBeforeSelect)	{
			m_orderInfoACC.getPropertyTable().clear();
		}
		basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo = addEmptyOrderInfo();

		if(    itOrder.isContainedAndSet("ordertype") 
			|| itOrder.isContainedAndSet("pickingtype") 
			|| itOrder.isContainedAndSet("bookingtype") 
			|| itOrder.isContainedAndSet("ordertypesub")) 
		{
			returnStruct = m_kscClientWrapper.kscOpenOrderReferenceVzType(itOrder, itOrderInfo);
			if (returnStruct.stateInfo != OK) {
			return returnStruct;
			}
		}
		else
		{
			returnStruct = m_kscClientWrapper.kscOpenOrderReferenceVz(itOrder, itOrderInfo);  // this writes into database
			if (returnStruct.stateInfo != OK) {
				return returnStruct;
			}
		}

		if (itOrder.isContainedAndSet("orderheadline1")) {
			returnStruct = m_kscClientWrapper.kscAddOrderHeadItem(itOrder, "orderheadline1", itOrderInfo);
			if (returnStruct.stateInfo != OK) {
			return returnStruct;
			}
		}

		if (itOrder.isContainedAndSet("orderheadline2")) {
			returnStruct = m_kscClientWrapper.kscAddOrderHeadItem(itOrder, "orderheadline2", itOrderInfo);
			if (returnStruct.stateInfo != OK) {
			return returnStruct;
			}
		}

		if (itOrder.isContainedAndSet("orderheadline3")) {
			returnStruct = m_kscClientWrapper.kscAddOrderHeadItem(itOrder, "orderheadline3", itOrderInfo);
			if (returnStruct.stateInfo != OK) {
			return returnStruct;
			}
		}

		if (itOrder.isContainedAndSet("deliverydate")) {
			returnStruct = m_kscClientWrapper.kscSetDeliveryDate(itOrder, itOrderInfo);
		}
		if (returnStruct.stateInfo != OK) {
			return returnStruct;
		}

		if (itOrder.isContainedAndSet("ordernote")) {
			returnStruct = m_kscClientWrapper.kscSetOrderText(itOrder, itOrderInfo);
			if (returnStruct.stateInfo != OK) {
			return returnStruct;
			}
		}

		if (itOrder.isContainedAndSet("originbranchno")) {
			returnStruct = m_kscClientWrapper.kscSetBatchOrderTyp(itOrder, itOrderInfo);
			if (returnStruct.stateInfo != OK) {
			return returnStruct;
			}
		}

		if (itOrder.isContainedAndSet("callback"))	{
			if (itOrder.getInt16("callback") != false){
			returnStruct = m_kscClientWrapper.kscSetCallback(itOrderInfo);
			}
		}

		return returnStruct;
	}// openOrder

	//*************************************** addItem ******************************************************
	KSCClientDMReturn KSCClientDM::addItem(const basar::db::aspect::AccessorPropertyTable_YIterator itItem, bool clearBeforeSelect) {
		BLOG_TRACE_METHOD(m_Logger, "KSCClientDM::addItem().");

		// prepare item info property table
		if (true == clearBeforeSelect) {
			m_itemInfoACC.getPropertyTable().clear();
		}
		basar::db::aspect::AccessorPropertyTable_YIterator itItemInfo = addEmptyItemInfo();

		return m_kscClientWrapper.kscAddOrderItem(itItem, itItemInfo);
	}// addItem

	//*************************************** addItemCodeRab ******************************************************
	KSCClientDMReturn KSCClientDM::addItemCodeRab(
	  const basar::db::aspect::AccessorPropertyTable_YIterator itItem,
	  bool clearBeforeSelect /*= true*/)
	{
		BLOG_TRACE_METHOD(m_Logger, "KSCClientDM::addItemCodeRab().");

		// prepare item info property table
		if (true == clearBeforeSelect) {
			m_itemInfoACC.getPropertyTable().clear();
		}
		basar::db::aspect::AccessorPropertyTable_YIterator itItemInfo = addEmptyItemInfo();

		return m_kscClientWrapper.kscAddOrderItemCodeRab(itItem, itItemInfo);
	}

	//*************************************** addItemCodeBatch ******************************************************
	KSCClientDMReturn KSCClientDM::addItemCodeBatch(
	  const basar::db::aspect::AccessorPropertyTable_YIterator itItem,
	  bool clearBeforeSelect /*= true*/)
	{
		BLOG_TRACE_METHOD(m_Logger, "KSCClientDM::addItemCodeBatch().");

		// prepare item info property table
		if (true == clearBeforeSelect) {
			m_itemInfoACC.getPropertyTable().clear();
		}
		basar::db::aspect::AccessorPropertyTable_YIterator itItemInfo = addEmptyItemInfo();

		return m_kscClientWrapper.kscAddOrderItemCodeBatch(itItem, itItemInfo);
	}

	//*************************************** addTextItem ******************************************************
	KSCClientDMReturn KSCClientDM::addTextItem(const basar::db::aspect::AccessorPropertyTable_YIterator itItem, bool clearBeforeSelect) {
		BLOG_TRACE_METHOD(m_Logger, "KSCClientDM::addTextItem().");

		// prepare item info property table
		if (true == clearBeforeSelect) {
			m_itemInfoACC.getPropertyTable().clear();
		}
		basar::db::aspect::AccessorPropertyTable_YIterator itItemInfo = addEmptyItemInfo();

		return m_kscClientWrapper.kscAddTextItem(itItem, itItemInfo);
	}// addTextItem

	//*************************************** closeOrder ******************************************************
  KSCClientDMReturn KSCClientDM::closeOrder(bool clearBeforeSelect)
  {
	BLOG_TRACE_METHOD(m_Logger, "KSCClientDM::closeOrder().");

	// prepare order info property table
	if (true == clearBeforeSelect)
	{
	  m_orderInfoACC.getPropertyTable().clear();
	};
	basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo = addEmptyOrderInfo();

	return m_kscClientWrapper.kscCloseOrder(itOrderInfo);
  }

	//*************************************** cancelOrder ******************************************************
  KSCClientDMReturn KSCClientDM::cancelOrder()
  {
	BLOG_TRACE_METHOD(m_Logger, "KSCClientDM::cancelOrder().");

	return m_kscClientWrapper.kscCancelOrder();
  }

	//*************************************** postponeOrder ******************************************************
  KSCClientDMReturn KSCClientDM::postponeOrder(bool clearBeforeSelect)
  {
	BLOG_TRACE_METHOD(m_Logger, "KSCClientDM::postponeOrder().");

//+++ ???
	// prepare order info property table
	if (true == clearBeforeSelect)
	{
	  m_orderInfoACC.getPropertyTable().clear();
	};
	basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo = addEmptyOrderInfo();

	return m_kscClientWrapper.kscPostponeOrder();
  }

// originbranchno, deferredpaymentdate and batchschreiben have to be set
KSCClientDMReturn KSCClientDM::setBatchValueDate( const basar::db::aspect::AccessorPropertyTable_YIterator iter )
{
	BLOG_TRACE_METHOD( m_Logger, "KSCClientDM::setBatchValueDate()." );

	basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo = addEmptyOrderInfo();
	return m_kscClientWrapper.kscSetBatchValueDate( iter, itOrderInfo );
}

KSCClientDMReturn KSCClientDM::setOrderRelationNo(const basar::Int32 no, const basar::Int16 type)
{
	BLOG_TRACE_METHOD( m_Logger, "KSCClientDM::setOrderRelationNo()." );

	return m_kscClientWrapper.kscSetOrderRelationNo(no, type);
}

void KSCClientDM::kscSetNoRouting()
{
	m_kscClientWrapper.kscSetNoRouting();
}



}
