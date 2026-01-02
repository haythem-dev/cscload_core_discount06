//-------------------------------------------------------------------------------------------------//
/*! \file   kscclientwrapper.cpp
 *  \brief  Wrapper class for access to KSC server.
 *  \author Klaus Hinz
 *  \date   03.01.2008
 */
//-------------------------------------------------------------------------------------------------//
#include "kscclientwrapper.h"
#include <libbasarcmnutil.h>
#include <libbasarcmnutil_logging.h>
#include <log4cplus/logger.h>

#include <orderinfo.h>
#include <articleinfostruct.h>
#include <articleinfostructcode.h>
#include <callbackinquiry.h>
#include <newcallback.h>
#include <newcallbackcritpos.h>
#include <callbackreasoninquiry.h>
#include <callbackdivisioninquiry.h>
#include <callksc.h>

#include <cstdio>

#ifdef WIN32 
	#if _MSC_VER > 1000 
		#define strcpy strcpy_s 
		#define strncpy strncpy_s 
		#define sprintf sprintf_s 
		#define sscanf sscanf_s 
	#endif // _MSC_VER > 1000 
#endif


namespace domMod {
	KSCClientWrapper::KSCClientWrapper(  log4cplus::Logger & logger )
	: m_Logger( logger ),
	  m_branchNoDefault(0),
	  m_branchNo(0),
	  m_customerNo(0),
	  m_deliveryDate(0),
	  m_originBranchNo(0),
	  m_batchTyp(0),
	  m_deferredPaymentDate(0),
	  m_articleNo(0),
	  m_orderQty(0),
	  m_interBranchTransfer(false),
	  m_subsequentDelivery(false),
	  m_articleRequirementPurchase(false),
	  m_partialDelivery(false),
	  m_sequenceNo(0),
      m_returnData( new orderinfoS() )
	{
		BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::KSCClientWrapper()." );

	    // initializations that can't be done in member initialization list
        memset( m_device, 0, sizeof(m_device) );
	    memset( m_server, 0, sizeof(m_server) );
	    memset( m_orderType, 0, sizeof(m_orderType) );
        memset( m_subOrderType, 0, sizeof(m_subOrderType) );
	    memset( m_pickingType, 0, sizeof(m_pickingType) );
	    memset( m_bookingType, 0, sizeof(m_bookingType) );
	    memset( m_orderHeadline, 0, sizeof(m_orderHeadline) );
	    memset( m_orderNote, 0, sizeof(m_orderNote) );
	    memset( m_itemNote, 0, sizeof(m_itemNote) );
        memset( m_reference, 0, sizeof(m_reference) );
	    clearReturnData();
	}
	
	KSCClientWrapper::~KSCClientWrapper()
	{
	    BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::~KSCClientWrapper().");
        delete m_returnData;
    }

	//*************************************** setBranchNoDefault ******************************************************
	void KSCClientWrapper::setBranchNoDefault(basar::Int16 branchNoDefault) {
		m_branchNoDefault = branchNoDefault;
	}

	//*************************************** kscConnectServerNoIni ******************************************************
	void KSCClientWrapper::kscConnectServerNoIni(const KSCClientDMConnParams& myKSCClientDMConnParams) {
		BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscConnectServerNoIni().");

		setDevice(myKSCClientDMConnParams.device);
		setServer(myKSCClientDMConnParams.server);
		clearReturnData();

		basar::Int32 result = ConnectServerNoIni(m_device, DEFAULT_UID, myKSCClientDMConnParams.port, m_server, m_returnData);

		if (result != 0)
		{
			char errormsg[1000+1];
			sprintf(errormsg, "KSC client function ConnectServerNoIni failed! result=%d, m_device=%s, uid=%d, myKSCClientDMConnParams.port=%d, m_server=%s", result, m_device, DEFAULT_UID, myKSCClientDMConnParams.port, m_server);
			basar::cmnutil::ExceptionInfoStruct sInfo("domMod.KSCClientWrapper.kscConnectServerNoIni",errormsg, __FILE__, __LINE__);
			basar::VarString result_str;
			result_str.itos(result);
			basar::VarString uid_str;
			result_str.itos(DEFAULT_UID);
			basar::VarString port_str;
			result_str.itos(myKSCClientDMConnParams.port);
			basar::VarString reason= "KSC client function ConnectServerNoIni failed! (result=";
			reason.append(result_str);
			reason.append(", ");
			reason.append(m_device);
			reason.append(", ");
			reason.append(uid_str);
			reason.append(", ");
			reason.append(port_str);
			reason.append(", ");
			reason.append(m_server);
			reason.append(").");
			BLOG_ERROR(m_Logger, reason); 

			// Log KSC-Server-text 
			basar::VarString returnDataText= "Ksc-Server TEXT: ";
			returnDataText.append(m_returnData->TEXT);
			//BLOG_ERROR(m_Logger, m_returnData->TEXT); 
			BLOG_ERROR(m_Logger, returnDataText); 

			throw KSCClientDMException(sInfo);
		}// if (result != 0)
	}// kscConnectServerNoIni

	//*************************************** kscDisconnectServer ******************************************************
  void KSCClientWrapper::kscDisconnectServer()
  {
	BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscDisconnectServer().");

	clearReturnData();

	basar::Int32 result = DisconnectServer(m_returnData);

	if (result != 0)
	{
	  basar::cmnutil::ExceptionInfoStruct sInfo(
		"domMod.KSCClientWrapper.kscDisconnectServer",
		"KSC client function DisconnectServer failed!", __FILE__, __LINE__);
	  throw KSCClientDMException(sInfo);
	}
  }

	//*************************************** kscOpenOrderReferenceVz ******************************************************
	KSCClientDMReturn KSCClientWrapper::kscOpenOrderReferenceVz(const basar::db::aspect::AccessorPropertyTable_YIterator itOrder, basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo) {
		BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscOpenOrderReferenceVz().");

		setBranchNo(itOrder);    
		setCustomerNo(itOrder);
		setReference(itOrder);

		clearReturnData();

		KSCClientDMReturn returnStruct;
		returnStruct.itInfo = itOrderInfo;
		returnStruct.stateInfo = INPUT_ERROR;
		basar::Int32 result = OpenOrderReferenceVz(m_branchNo, m_customerNo, m_reference, m_returnData);

		bool blnOK=true;
		if(result != 0)
		{
			blnOK=false;
			if(6 == result)
			{
				basar::Int32 lackreason=m_returnData->LACKREASON;
				if(lackreason>99999)
				{
					lackreason=lackreason/100;
				}
				if(30027==lackreason)  //KEINE_TOUR_MEHR
				{
					blnOK=true;
				}
			}// if(6 == result)
		}// if(result != 0)

		if(!blnOK) {  
			basar::VarString result_str;
			result_str.itos(result);
			basar::VarString reason= "KSC client function OpenOrderReferenceVz failed! (result=";
			reason.append(result_str);

			// kes 14.01.14: appended errortext to reason. Will be shown in exception.
			// kes 16.04.14: cut Text to the first 100 chars. Otherwise there is some "iij" at the end
			basar::VarString txtbuf("");
			txtbuf = m_returnData->TEXT;
			txtbuf = txtbuf.substr(0, 100);
			reason.append(" Text:");
			reason.append(txtbuf.substr(0, 100));
			// orig: reason.append(" Text:");
			// orig: reason.append(m_returnData->TEXT);

			reason.append(").");
			BLOG_ERROR(m_Logger, reason); 

			// kes 14.01.14: commented:BLOG_ERROR(m_Logger, m_returnData->TEXT); 
			// kes 16.04.14: No Exception but return
			// orig:	basar::cmnutil::ExceptionInfoStruct sInfo("domMod.KSCClientWrapper.kscOpenOrderReferenceVz",reason, __FILE__, __LINE__);
			// orig:	throw KSCClientDMException(sInfo);
			// orig:    returnStruct.textInfo=m_returnData->TEXT;
			returnStruct.textInfo=txtbuf;

		}// if(!blnOK)
		else {
			getOrderNo(itOrderInfo);
			getPharmacyName(itOrderInfo);
			returnStruct.stateInfo = OK;
		}// if(OK == returnStruct.stateInfo)

		return returnStruct;
	}// kscOpenOrderReferenceVz

	//*************************************** kscOpenOrderReferenceVzType ******************************************************
	KSCClientDMReturn KSCClientWrapper::kscOpenOrderReferenceVzType(const basar::db::aspect::AccessorPropertyTable_YIterator itOrder, basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo) {
		BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscOpenOrderReferenceVz().");

		setBranchNo(itOrder);    
		setCustomerNo(itOrder);
		setReference(itOrder);

		clearReturnData();

		KSCClientDMReturn returnStruct;
		returnStruct.itInfo = itOrderInfo;
		returnStruct.stateInfo = INPUT_ERROR;

		basar::VarString orderType = itOrder.getString( "ordertype" );
		basar::VarString pickingType = itOrder.getString( "pickingtype" );
		basar::VarString bookingType = itOrder.getString( "bookingtype" );
		basar::VarString subOrderType;
		if( itOrder.isContainedAndSet( "ordertypesub" ) )
		{
			subOrderType = itOrder.getString( "ordertypesub" );
		}
		basar::Int32 result = OpenOrderReferenceVzType( 
			m_branchNo, 
			m_customerNo, 
			m_reference, 
			const_cast<char *>( orderType.c_str() ), 
			const_cast<char *>( pickingType.c_str() ), 
			const_cast<char *>( bookingType.c_str() ), 
			const_cast<char *>( subOrderType.c_str() ),
			m_returnData );

		bool blnOK=true;
		if(result != 0)
		{
			blnOK=false;
			if(6 == result)
			{
				basar::Int32 lackreason=m_returnData->LACKREASON;
				if(lackreason>99999)
				{
					lackreason=lackreason/100;
				}
				if(30027==lackreason)  //KEINE_TOUR_MEHR
				{
					blnOK=true;
				}
			}// if(6 == result)
		}// if(result != 0)

		if(!blnOK) {  
			basar::VarString result_str;
			result_str.itos(result);
			basar::VarString reason= "KSCclient function OpenOrderReferenceVzType failed! (result=";
			reason.append(result_str);

			// kes 14.01.14: appended errortext to reason. Will be shown in exception.
			// kes 16.04.14: cut Text to the first 100 chars. Otherwise there is some "iij" at the end
			basar::VarString txtbuf("");
			txtbuf = m_returnData->TEXT;
			txtbuf = txtbuf.substr(0, 100);
			reason.append(" Text:");
			reason.append(txtbuf.substr(0, 100));

			// orig: reason.append(" Text:");
			// orig: reason.append(m_returnData->TEXT);

			reason.append(").");
			BLOG_ERROR(m_Logger, reason); 
			// kes 14.01.14: commented:BLOG_ERROR(m_Logger, m_returnData->TEXT); 
			// kes 16.04.14: No Exception but return
			// orig:	basar::cmnutil::ExceptionInfoStruct sInfo("domMod.KSCClientWrapper.kscOpenOrderReferenceVz",reason, __FILE__, __LINE__);
			// orig:	throw KSCClientDMException(sInfo);
			// orig:    returnStruct.textInfo=m_returnData->TEXT;
			returnStruct.textInfo=txtbuf;

		}// if(!blnOK)
		else {
			getOrderNo(itOrderInfo);
			getPharmacyName(itOrderInfo);
			returnStruct.stateInfo = OK;
		}// if(OK == returnStruct.stateInfo)

		return returnStruct;
	}// kscOpenOrderReferenceVzType

	//*************************************** kscSetOrderTypeSub ******************************************************
		KSCClientDMReturn KSCClientWrapper::kscSetOrderTypeSub(const basar::db::aspect::AccessorPropertyTable_YIterator itOrder, basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo) {
		BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscSetOrderTypeSub().");

		setOrderType(itOrder);
		setPickingType(itOrder);
		setBookingType(itOrder);
		setSubOrderType(itOrder);

		clearReturnData();

		KSCClientDMReturn returnStruct;
		returnStruct.itInfo = itOrderInfo;
		returnStruct.stateInfo = INPUT_ERROR;

		basar::Int32 result = SetOrderTypeSub(m_orderType, m_pickingType, m_bookingType, m_subOrderType, m_returnData);

		if(!evaluateKSCRetVal(result, returnStruct)) {
			basar::cmnutil::ExceptionInfoStruct sInfo(
			"domMod.KSCClientWrapper.kscSetOrderTypeSub",
			"KSC client function SetOrderTypeSub failed!", __FILE__, __LINE__);
			throw KSCClientDMException(sInfo);
		}// if(!evaluateKSCRetVal(result, returnStruct))

		return returnStruct;
	}// kscSetOrderTypeSub

	//*************************************** kscSetDeliveryDate ******************************************************
	KSCClientDMReturn KSCClientWrapper::kscSetDeliveryDate(const basar::db::aspect::AccessorPropertyTable_YIterator itOrder, basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo) {
		BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscSetDeliveryDate().");

		setDeliveryDate(itOrder);
		clearReturnData();

		KSCClientDMReturn returnStruct;
		returnStruct.itInfo = itOrderInfo;
		returnStruct.stateInfo = INPUT_ERROR;

		basar::Int32 result = SetDeliveryDate(m_deliveryDate, m_returnData);

		if (false == evaluateKSCRetVal(result, returnStruct))
		{
			basar::cmnutil::ExceptionInfoStruct sInfo(
			"domMod.KSCClientWrapper.kscSetDeliveryDate",
			"KSC client function SetDeliveryDate failed!", __FILE__, __LINE__);
			throw KSCClientDMException(sInfo);
		}

		return returnStruct;
	}// kscSetDeliveryDate

	//*************************************** kscSetBatchOrderTyp ******************************************************
	//
	// Attention! This function sets 4 attributes:
	//				- BatchTyp
	//				- OriginBranch
	//				- ValutaDatum
	//				- EdiLieferschein
	//
	//*****************************************************************************************************************
	KSCClientDMReturn KSCClientWrapper::kscSetBatchOrderTyp(const basar::db::aspect::AccessorPropertyTable_YIterator itOrder, basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo) {
		BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscSetBatchOrderTyp().");
		setBatchOrderTyp(itOrder);
		setOriginBranch(itOrder);
		setDeferredPaymentDate(itOrder);
		setEdiDeliveryNote(itOrder);
		clearReturnData();

		KSCClientDMReturn returnStruct;
		returnStruct.itInfo = itOrderInfo;
		returnStruct.stateInfo = INPUT_ERROR;

		basar::Int32 result = SetBatchOrderTyp(m_batchTyp, m_originBranchNo, m_deferredPaymentDate, m_ediDeliveryNote, "0", m_returnData);

		if (false == evaluateKSCRetVal(result, returnStruct)) {
			basar::VarString err="KSC client function setOriginBranch failed!";
			basar::VarString err1="";
			err1.format("m_batchTyp=%d;", m_batchTyp);
			err.append(err1);	
			err1.format("m_originBranchNo=%d;", m_originBranchNo);
			err.append(err1);	
			err1.format("result=%d;", result);
			err.append(err1);	

			basar::cmnutil::ExceptionInfoStruct sInfo("domMod.KSCClientWrapper.kscSetBatchOrderTyp", "KSC client function setOriginBranch failed!", __FILE__, __LINE__);
			throw KSCClientDMException(sInfo);
		}
		return returnStruct;
	}// kscSetBatchOrderTyp


KSCClientDMReturn KSCClientWrapper::kscSetBatchValueDate(
	const basar::db::aspect::AccessorPropertyTable_YIterator itOrder, 
	basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo
		)
{
	BLOG_TRACE_METHOD( m_Logger, "KSCClientWrapper::kscSetBatchValueDate()." );

	setOriginBranch( itOrder );
	setDeferredPaymentDate( itOrder );
	setBatchSchreiben( itOrder );

	clearReturnData();

	KSCClientDMReturn returnStruct;
	returnStruct.itInfo = itOrderInfo;
	returnStruct.stateInfo = INPUT_ERROR;

	basar::Int32 result = SetBatchValueDate( m_BatchSchreiben, m_originBranchNo, m_deferredPaymentDate, m_returnData );
	if( false == evaluateKSCRetVal( result, returnStruct ) ) 
	{
		basar::cmnutil::ExceptionInfoStruct sInfo( "domMod.KSCClientWrapper.kscSetBatchValueDate", "KSC client function SetBatchValueDate failed!", __FILE__, __LINE__ );
		throw KSCClientDMException( sInfo );
	}

	return returnStruct;
}

	//*************************************** kscAddOrderHeadItem ******************************************************
  KSCClientDMReturn KSCClientWrapper::kscAddOrderHeadItem(
	const basar::db::aspect::AccessorPropertyTable_YIterator itOrder,
	basar::VarString headline,
	basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo)
  {
	BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscAddOrderHeadItem().");

	setOrderHeadline(itOrder, headline);
	clearReturnData();

	KSCClientDMReturn returnStruct;
	returnStruct.itInfo = itOrderInfo;
	returnStruct.stateInfo = INPUT_ERROR;

	//! \todo  AddOrderHeadItem returns non initialized struct orderinfoS
	basar::Int32 result = AddOrderHeadItem(m_orderHeadline, m_returnData);

	if (false == evaluateKSCRetVal(result, returnStruct))
	{
	  basar::cmnutil::ExceptionInfoStruct sInfo(
		"domMod.KSCClientWrapper.kscAddOrderHeadItem",
		"KSC client function AddOrderHeadItem failed!", __FILE__, __LINE__);
	  throw KSCClientDMException(sInfo);
	}

	return returnStruct;
  }

	//*************************************** kscSetOrderText ******************************************************
  KSCClientDMReturn KSCClientWrapper::kscSetOrderText(const basar::db::aspect::AccessorPropertyTable_YIterator itOrder, basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo) {
	BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscSetOrderText().");

	setOrderNote(itOrder);
	clearReturnData();

	KSCClientDMReturn returnStruct;
	returnStruct.itInfo = itOrderInfo;
	returnStruct.stateInfo = INPUT_ERROR;

	basar::Int32 result = SetOrderText(m_orderNote, m_returnData);

	if (false == evaluateKSCRetVal(result, returnStruct))
	{
	  basar::cmnutil::ExceptionInfoStruct sInfo(
		"domMod.KSCClientWrapper.kscSetOrderText",
		"KSC client function SetOrderText failed!", __FILE__, __LINE__);
	  throw KSCClientDMException(sInfo);
	}

	return returnStruct;
  }

	//*************************************** kscSetCallback ******************************************************
  KSCClientDMReturn KSCClientWrapper::kscSetCallback(
	basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo)
  {
	BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscSetCallback().");

	clearReturnData();

	KSCClientDMReturn returnStruct;
	returnStruct.itInfo = itOrderInfo;
	returnStruct.stateInfo = INPUT_ERROR;

	basar::Int32 result = SetCallback(m_returnData);

	if (false == evaluateKSCRetVal(result, returnStruct))
	{
	  basar::cmnutil::ExceptionInfoStruct sInfo(
		"domMod.KSCClientWrapper.kscSetCallback",
		"KSC client function SetCallback failed!", __FILE__, __LINE__);
	  throw KSCClientDMException(sInfo);
	}

	return returnStruct;
  }

	//*************************************** kscAddOrderItem ******************************************************
	KSCClientDMReturn KSCClientWrapper::kscAddOrderItem(const basar::db::aspect::AccessorPropertyTable_YIterator itItem, basar::db::aspect::AccessorPropertyTable_YIterator itItemInfo) {
		BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscAddOrderItem().");

		setOrderQty(itItem);
		setArticleNo(itItem);
		setEan(itItem);
		setArticleCode(itItem);
		setInterBranchTransfer(itItem);
		setSubsequentDelivery(itItem);
		setArticleRequirementPurchase(itItem);
		setPartialDelivery(itItem);
		setSequenceNo(itItem);
		setItemNote(itItem);
		setIdfOrigin(itItem);
		setOrderNoOrigin(itItem);
		setPosNoOrigin(itItem);

		clearReturnData();

		KSCClientDMReturn returnStruct;
		returnStruct.itInfo = itItemInfo;
		returnStruct.stateInfo = INPUT_ERROR;

//		basar::Int32 result = AddOrderItem(m_orderQty, m_articleNo, m_ean, m_interBranchTransfer, m_subsequentDelivery,	m_articleRequirementPurchase, m_partialDelivery, m_sequenceNo, m_itemNote, m_returnData);
//		basar::Int32 result = AddOrderItem(m_orderQty, m_articleNo, m_ean, m_interBranchTransfer, m_subsequentDelivery,	m_articleRequirementPurchase, m_partialDelivery, m_sequenceNo, m_idfOrigin, m_orderNoOrigin, m_posNoOrigin, m_itemNote, m_returnData);
		int pricetype=0;
		basar::Int32 result = AddOrderItemCode(m_orderQty, m_articleCode, m_interBranchTransfer, m_subsequentDelivery,	m_articleRequirementPurchase, m_partialDelivery, m_sequenceNo, m_idfOrigin, m_orderNoOrigin, m_posNoOrigin, pricetype, m_itemNote, m_returnData);
//		basar::Int32 result = AddOrderItemCode(m_orderQty, "code1848198", m_interBranchTransfer, m_subsequentDelivery,	m_articleRequirementPurchase, m_partialDelivery, m_sequenceNo, m_idfOrigin, m_orderNoOrigin, m_posNoOrigin, pricetype, m_itemNote, m_returnData);

		if(!evaluateKSCRetVal(result, returnStruct)) {
			basar::cmnutil::ExceptionInfoStruct sInfo("domMod.KSCClientWrapper.kscAddOrderItem", "KSC client function AddOrderItem failed!", __FILE__, __LINE__);
			throw KSCClientDMException(sInfo);
		}// if(!evaluateKSCRetVal(result, returnStruct))

		if(OK == returnStruct.stateInfo) {
			getArticleNo(itItemInfo);
			getEan(itItemInfo);
			getQtyLack(itItemInfo);
			getLackReason(itItemInfo);
			getAuxQty(itItemInfo);
			getArticleUnit(itItemInfo);
			getArticleName(itItemInfo);
			getHandout(itItemInfo);
			getAuxBranchNo(itItemInfo);
			getCodeBlocage(itItemInfo);
			getRestDeliveryQty(itItemInfo);
			getDeliveryQty(itItemInfo);
			getLackReasonCtyCode(itItemInfo);
			getPharmPurchPrice(itItemInfo);
			getCustPurchPrice(itItemInfo);
			getPharmSellPrice(itItemInfo);
			getTaxRate(itItemInfo);
			getExpiryDate(itItemInfo);
			getLpprPrice(itItemInfo);
			getSeraCode(itItemInfo);
			getXmlCode(itItemInfo);
			getXmlText(itItemInfo);
			getArticleUnitOrg(itItemInfo);
			getArticleNameOrg(itItemInfo);
			getHandoutOrg(itItemInfo);
			getPharmPurchPriceOrg(itItemInfo);
			getCustPurchPriceOrg(itItemInfo);
			getPharmSellPriceOrg(itItemInfo);
			getTaxRateOrg(itItemInfo);
			getLpprPriceOrg(itItemInfo);
			getArticleNoOrg(itItemInfo);
			getCodeBlocageOrg(itItemInfo);
			getSeraCodeOrg(itItemInfo);
			getXmlCodeOrg(itItemInfo);
			getXmlTextOrg(itItemInfo);
		}// if(OK == returnStruct.stateInfo)

		return returnStruct;
	}// kscAddOrderItem
 
	//*************************************** kscAddOrderItemCodeRab ******************************************************
	KSCClientDMReturn KSCClientWrapper::kscAddOrderItemCodeRab(
		const basar::db::aspect::AccessorPropertyTable_YIterator itItem,
		basar::db::aspect::AccessorPropertyTable_YIterator itItemInfo )
	{
		setOrderQty( itItem );
		setArticleNo( itItem );
		setEan( itItem );
		setArticleCode( itItem );
		setInterBranchTransfer( itItem );
		setSubsequentDelivery( itItem );
		setArticleRequirementPurchase( itItem );
		setPartialDelivery( itItem );
		setSequenceNo( itItem );
		setItemNote( itItem );
		setIdfOrigin( itItem );
		setOrderNoOrigin( itItem );
		setPosNoOrigin( itItem );
		setRebateInKind( itItem );
		// 19.03.14 kes: Don't set these values as log as percent-rebate is sent via text "BR23;00" 
		// 09.05.14 kes: Set these values to zero values as long as percent-rebate is sent via text "BR23;00" 
		//               This is done in cscorderdm.cpp
		setFreeRebate( itItem );
		setRebateType( itItem );

		clearReturnData();

		KSCClientDMReturn returnStruct;
		returnStruct.itInfo = itItemInfo;
		returnStruct.stateInfo = INPUT_ERROR;

		int pricetype = 0;
		basar::Int32 result = AddOrderItemCodeRab( m_orderQty, m_articleCode, m_interBranchTransfer, m_subsequentDelivery,
			m_articleRequirementPurchase, m_partialDelivery, m_sequenceNo, m_idfOrigin, m_orderNoOrigin, m_posNoOrigin, 
			pricetype, m_RebateInKind, m_FreeRebate.toFloat64(), m_RebateType, m_itemNote, m_returnData );
		//basar::Int32 result = AddOrderItemCodeRab( m_orderQty, m_articleCode, m_interBranchTransfer, m_subsequentDelivery,
		//	m_articleRequirementPurchase, m_partialDelivery, m_sequenceNo, m_idfOrigin, m_orderNoOrigin, m_posNoOrigin, 
		//	pricetype, m_RebateInKind, 0.0, 0, m_itemNote, m_returnData );

		if( false == evaluateKSCRetVal( result, returnStruct ) ) 
		{
			basar::cmnutil::ExceptionInfoStruct sInfo( "domMod.KSCClientWrapper.kscAddOrderItemCodeRab", "KSC client function AddOrderItemCodeRab failed!", __FILE__, __LINE__ );
			throw KSCClientDMException( sInfo );
		}

		if( OK == returnStruct.stateInfo ) 
		{
			getArticleNo( itItemInfo );
			getEan( itItemInfo );
			getQtyLack( itItemInfo );
			getLackReason( itItemInfo );
			getAuxQty( itItemInfo );
			getArticleUnit( itItemInfo );
			getArticleName( itItemInfo );
			getHandout( itItemInfo );
			getAuxBranchNo( itItemInfo );
			getCodeBlocage( itItemInfo );
			getRestDeliveryQty( itItemInfo );
			getDeliveryQty( itItemInfo );
			getLackReasonCtyCode( itItemInfo );
			getPharmPurchPrice( itItemInfo );
			getCustPurchPrice( itItemInfo );
			getPharmSellPrice( itItemInfo );
			getTaxRate( itItemInfo );
			getExpiryDate( itItemInfo );
			getLpprPrice( itItemInfo );
			getSeraCode( itItemInfo );
			getXmlCode( itItemInfo );
			getXmlText( itItemInfo );
			getArticleUnitOrg( itItemInfo );
			getArticleNameOrg( itItemInfo );
			getHandoutOrg( itItemInfo );
			getPharmPurchPriceOrg( itItemInfo );
			getCustPurchPriceOrg( itItemInfo );
			getPharmSellPriceOrg( itItemInfo );
			getTaxRateOrg( itItemInfo );
			getLpprPriceOrg( itItemInfo );
			getArticleNoOrg( itItemInfo );
			getCodeBlocageOrg( itItemInfo );
			getSeraCodeOrg( itItemInfo );
			getXmlCodeOrg( itItemInfo );
			getXmlTextOrg( itItemInfo );
		}

		return returnStruct;
	}

	//*************************************** kscAddOrderItemCodeBatch ******************************************************
	KSCClientDMReturn KSCClientWrapper::kscAddOrderItemCodeBatch(
		const basar::db::aspect::AccessorPropertyTable_YIterator itItem,
		basar::db::aspect::AccessorPropertyTable_YIterator itItemInfo )
	{
		setOrderQty( itItem );
		setArticleNo( itItem );
		setEan( itItem );
		setArticleCode( itItem );
		setBatch( itItem );

		clearReturnData();

		KSCClientDMReturn returnStruct;
		returnStruct.itInfo = itItemInfo;
		returnStruct.stateInfo = INPUT_ERROR;

		int pricetype = 0;
		basar::Int32 result = AddOrderItemCodeBatch( m_orderQty, m_articleCode, m_Batch, pricetype, m_itemNote, m_returnData );

		if( false == evaluateKSCRetVal( result, returnStruct ) ) 
		{
			basar::cmnutil::ExceptionInfoStruct sInfo( "domMod.KSCClientWrapper.kscAddOrderItemCodeBatch", "KSC client function AddOrderItemCodeBatch failed!", __FILE__, __LINE__ );
			throw KSCClientDMException( sInfo );
		}

		if( OK == returnStruct.stateInfo ) 
		{
			getArticleNo( itItemInfo );
			getEan( itItemInfo );
			getQtyLack( itItemInfo );
			getLackReason( itItemInfo );
			getAuxQty( itItemInfo );
			getArticleUnit( itItemInfo );
			getArticleName( itItemInfo );
			getHandout( itItemInfo );
			getAuxBranchNo( itItemInfo );
			getCodeBlocage( itItemInfo );
			getRestDeliveryQty( itItemInfo );
			getDeliveryQty( itItemInfo );
			getLackReasonCtyCode( itItemInfo );
			getPharmPurchPrice( itItemInfo );
			getCustPurchPrice( itItemInfo );
			getPharmSellPrice( itItemInfo );
			getTaxRate( itItemInfo );
			getExpiryDate( itItemInfo );
			getLpprPrice( itItemInfo );
			getSeraCode( itItemInfo );
			getXmlCode( itItemInfo );
			getXmlText( itItemInfo );
			getArticleUnitOrg( itItemInfo );
			getArticleNameOrg( itItemInfo );
			getHandoutOrg( itItemInfo );
			getPharmPurchPriceOrg( itItemInfo );
			getCustPurchPriceOrg( itItemInfo );
			getPharmSellPriceOrg( itItemInfo );
			getTaxRateOrg( itItemInfo );
			getLpprPriceOrg( itItemInfo );
			getArticleNoOrg( itItemInfo );
			getCodeBlocageOrg( itItemInfo );
			getSeraCodeOrg( itItemInfo );
			getXmlCodeOrg( itItemInfo );
			getXmlTextOrg( itItemInfo );
		}

		return returnStruct;
	}

	//*************************************** kscAddTextItem ******************************************************
	KSCClientDMReturn KSCClientWrapper::kscAddTextItem(const basar::db::aspect::AccessorPropertyTable_YIterator itItem, basar::db::aspect::AccessorPropertyTable_YIterator itItemInfo) {
		BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscAddTextItem().");

		setOrderQty(itItem);
		setItemNote(itItem);

		clearReturnData();

		KSCClientDMReturn returnStruct;
		returnStruct.itInfo = itItemInfo;
		returnStruct.stateInfo = INPUT_ERROR;

		basar::Int32 result = AddTextItem(m_orderQty, m_itemNote, m_returnData);
		if(!evaluateKSCRetVal(result, returnStruct)) {
			basar::cmnutil::ExceptionInfoStruct sInfo("domMod.KSCClientWrapper.kscAddTextItem", "KSC client function AddTextItem failed!", __FILE__, __LINE__);
			throw KSCClientDMException(sInfo);
		}// if(!evaluateKSCRetVal(result, returnStruct))

		if(OK == returnStruct.stateInfo) {
			getArticleNo(itItemInfo);
			getEan(itItemInfo);
			getQtyLack(itItemInfo);
			getLackReason(itItemInfo);
			getAuxQty(itItemInfo);
			getArticleUnit(itItemInfo);
			getArticleName(itItemInfo);
			getHandout(itItemInfo);
			getAuxBranchNo(itItemInfo);
			getCodeBlocage(itItemInfo);
			getRestDeliveryQty(itItemInfo);
			getDeliveryQty(itItemInfo);
			getLackReasonCtyCode(itItemInfo);
			getPharmPurchPrice(itItemInfo);
			getCustPurchPrice(itItemInfo);
			getPharmSellPrice(itItemInfo);
			getTaxRate(itItemInfo);
			getExpiryDate(itItemInfo);
			getLpprPrice(itItemInfo);
			getSeraCode(itItemInfo);
			getXmlCode(itItemInfo);
			getXmlText(itItemInfo);
			getArticleUnitOrg(itItemInfo);
			getArticleNameOrg(itItemInfo);
			getHandoutOrg(itItemInfo);
			getPharmPurchPriceOrg(itItemInfo);
			getCustPurchPriceOrg(itItemInfo);
			getPharmSellPriceOrg(itItemInfo);
			getTaxRateOrg(itItemInfo);
			getLpprPriceOrg(itItemInfo);
			getArticleNoOrg(itItemInfo);
			getCodeBlocageOrg(itItemInfo);
			getSeraCodeOrg(itItemInfo);
			getXmlCodeOrg(itItemInfo);
			getXmlTextOrg(itItemInfo);
		}// if(OK == returnStruct.stateInfo)

		return returnStruct;
	}// kscAddTextItem
 
	//*************************************** kscCloseOrder ******************************************************
	KSCClientDMReturn KSCClientWrapper::kscCloseOrder(basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo) {
		BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscCloseOrder().");

		clearReturnData();

		KSCClientDMReturn returnStruct;
		returnStruct.itInfo = itOrderInfo;
		returnStruct.stateInfo = INPUT_ERROR;

		// CloseOrder throws exception, if order was not opened
		basar::Int32 result = CloseOrder("", m_returnData);

		if (false == evaluateKSCRetVal(result, returnStruct)) {
			basar::cmnutil::ExceptionInfoStruct sInfo(
			"domMod.KSCClientWrapper.kscCloseOrder",
			"KSC client function CloseOrder failed!", __FILE__, __LINE__);
			throw KSCClientDMException(sInfo);
		}
		if (OK == returnStruct.stateInfo) {
			getTourId(itOrderInfo);
			getTourDate(itOrderInfo);
			getValueOfOrder(itOrderInfo);
			getLinesOfOrder(itOrderInfo);
			getLackLines(itOrderInfo);
			getTextLines(itOrderInfo);
			getDeliveryBranchNo(itOrderInfo);
		}

		return returnStruct;
	}// kscCloseOrder

	//*************************************** kscCancelOrder ******************************************************
  KSCClientDMReturn KSCClientWrapper::kscCancelOrder()
  {
	BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscCancelOrder().");

	clearReturnData();

	KSCClientDMReturn returnStruct;
	returnStruct.stateInfo = INPUT_ERROR;

	basar::Int32 result = CancelOrder(m_returnData);

	if (false == evaluateKSCRetVal(result, returnStruct))
	{
	  basar::cmnutil::ExceptionInfoStruct sInfo(
		"domMod.KSCClientWrapper.kscCancelOrder",
		"KSC client function CancelOrder failed!", __FILE__, __LINE__);
	  throw KSCClientDMException(sInfo);
	}

	return returnStruct;
  }

	//*************************************** kscPostponeOrder ******************************************************
  KSCClientDMReturn KSCClientWrapper::kscPostponeOrder()
  {
	BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscPostponeOrder().");

	clearReturnData();

	KSCClientDMReturn returnStruct;
	returnStruct.stateInfo = INPUT_ERROR;

	basar::Int32 result = PostponeOrder(m_returnData);

	if (false == evaluateKSCRetVal(result, returnStruct))
	{
	  basar::cmnutil::ExceptionInfoStruct sInfo(
		"domMod.KSCClientWrapper.kscPostponeOrder",
		"KSC client function PostponeOrder failed!", __FILE__, __LINE__);
		basar::I18nString strOrderMessage1;
		strOrderMessage1.itos(result);
		basar::I18nString strOrderMessage="";
		strOrderMessage.append("Returnvalue PostponeOrder: ");
		strOrderMessage.append(strOrderMessage1);
		BLOG_ERROR(m_Logger, strOrderMessage);
	  throw KSCClientDMException(sInfo);
	}

	return returnStruct;
  }


KSCClientDMReturn KSCClientWrapper::kscSetOrderRelationNo( const basar::Int32 no, const basar::Int16 type)
{
	BLOG_TRACE_METHOD(m_Logger, "KSCClientWrapper::kscSetOrderRelationNo().");

	clearReturnData();

	KSCClientDMReturn returnStruct;
	returnStruct.stateInfo = INPUT_ERROR;

	basar::Int32 result = SetOrderRelationNo(no, type, m_returnData);

	if (false == evaluateKSCRetVal(result, returnStruct))
	{
	  basar::cmnutil::ExceptionInfoStruct sInfo(
		"domMod.KSCClientWrapper.kscSetOrderRelationNo",
		"KSC client function SetOrderRelationNo failed!", __FILE__, __LINE__);
		basar::I18nString strOrderMessage1;
		strOrderMessage1.itos(result);
		basar::I18nString strOrderMessage="";
		strOrderMessage.append("Returnvalue SetOrderRelationNo: ");
		strOrderMessage.append(strOrderMessage1);
		BLOG_ERROR(m_Logger, strOrderMessage);
	  throw KSCClientDMException(sInfo);
	}

	return returnStruct;
}

	//*************************************** clearReturnData ******************************************************
  void KSCClientWrapper::clearReturnData()
  {
		m_returnData->ORDERNO = 0;
		m_returnData->ORDERQTY = 0;
		m_returnData->ARTICLENO = 0;
		m_returnData->QTYLACK = 0;
		m_returnData->LACKREASON = 0;
		m_returnData->AUXQTY = 0;
        memset( m_returnData->ARTICLEUNIT, 0, sizeof(m_returnData->ARTICLEUNIT) );
		memset( m_returnData->ARTICLENAME, 0, sizeof(m_returnData->ARTICLENAME) );
		memset( m_returnData->HANDOUT, 0, sizeof(m_returnData->HANDOUT) );
		memset( m_returnData->EAN, 0, sizeof(m_returnData->EAN) );
		memset( m_returnData->TEXT, 0, sizeof(m_returnData->TEXT) );
		memset( m_returnData->TOURID, 0, sizeof(m_returnData->TOURID) );
		m_returnData->AUXBRANCHNO = 0;
		memset( m_returnData->CODEBLOCAGE, 0, sizeof(m_returnData->CODEBLOCAGE) );
		m_returnData->RESTDELIVERYQTY = 0;
		m_returnData->DISPOQTY = 0;
		m_returnData->DELIVERYQTY = 0;
		m_returnData->TOURDATE = 0;
		memset( m_returnData->LACKREASONCTYCODE, 0, sizeof(m_returnData->LACKREASONCTYCODE) );
		m_returnData->PHARMPURCHPRICE = 0;
		m_returnData->CUSTPURCHPRICE = 0;
		m_returnData->PHARMSELLPRICE = 0;
		m_returnData->TAXRATE = 0;
		m_returnData->TAXVALUE = 0;
		memset( m_returnData->MANUFACTURERNAME, 0, sizeof(m_returnData->MANUFACTURERNAME) );
		m_returnData->EXPIRYDATE = 0;
		m_returnData->VALUEOFORDER = 0;
		m_returnData->LINESOFORDER = 0;
		m_returnData->LACKLINES = 0;
		m_returnData->TEXTLINES = 0;
		memset(m_returnData->PHARMACYNAME, 0, sizeof(m_returnData->PHARMACYNAME) );
		m_returnData->QTYRESERVATION = 0;
		m_returnData->DATEOFUPDATE = 0;
		memset(m_returnData->AVAILABLE, 0, sizeof(m_returnData->AVAILABLE) );
		memset(m_returnData->ARTICLEUNITORG, 0, sizeof(m_returnData->ARTICLEUNITORG) );
		memset(m_returnData->ARTICLENAMEORG, 0, sizeof(m_returnData->ARTICLENAMEORG) );
		memset(m_returnData->HANDOUTORG, 0, sizeof(m_returnData->HANDOUTORG) );
		m_returnData->PHARMPURCHPRICEORG = 0;
		m_returnData->CUSTPURCHPRICEORG = 0;
		m_returnData->PHARMSELLPRICEORG = 0;
		m_returnData->TAXRATEORG = 0;
		m_returnData->LPPR_PRICE = 0;
		m_returnData->LPPR_PRICEORG = 0;
		m_returnData->DELIVERYBRANCHNO = 0;
		memset(m_returnData->SERACODE, 0, sizeof(m_returnData->SERACODE) );
		memset(m_returnData->XMLCODE, 0, sizeof(m_returnData->XMLCODE) );
		memset(m_returnData->XMLTEXT, 0, sizeof(m_returnData->XMLTEXT) );
		memset(m_returnData->EANORG, 0, sizeof(m_returnData->EANORG) );
		m_returnData->ARTICLENOORG = 0;
		memset( m_returnData->CODEBLOCAGEORG, 0, sizeof(m_returnData->CODEBLOCAGEORG) );
		memset( m_returnData->SERACODEORG, 0, sizeof(m_returnData->SERACODEORG) );
		memset( m_returnData->XMLCODEORG, 0, sizeof(m_returnData->XMLCODEORG) );
		memset( m_returnData->XMLTEXTORG, 0, sizeof(m_returnData->XMLTEXTORG) );
	}

	//*************************************** setDevice ******************************************************
  void KSCClientWrapper::setDevice(const basar::VarString& device)
  {
	delimitedString2Char(m_device, device, MAX_LEN_DEVICE);
  }

	//*************************************** setServer ******************************************************
  void KSCClientWrapper::setServer(const basar::VarString& server)
  {
	delimitedString2Char(m_server, server, MAX_LEN_SERVER);
  }

	//*************************************** setBranchNo ******************************************************
  void KSCClientWrapper::setBranchNo(const basar::db::aspect::AccessorPropertyTable_YIterator iter)
  {
	// check, if default branchnumber to be used
	if (iter.isContainedAndSet("branchno"))
	{
	  m_branchNo = iter.getInt16("branchno");
	}
	else
	{
	  m_branchNo = m_branchNoDefault;
	};
  }

	//*************************************** setCustomerNo ******************************************************
  void KSCClientWrapper::setCustomerNo(const basar::db::aspect::AccessorPropertyTable_YIterator iter)
  {
	m_customerNo = iter.getInt32("customerno");
  }

	//*************************************** setOrderType ******************************************************
  void KSCClientWrapper::setOrderType(const basar::db::aspect::AccessorPropertyTable_YIterator iter)
  {
	delimitedString2Char(m_orderType, iter.getString("ordertype"), LEN_ORDERTYPE);
  }

	//*************************************** setSubOrderType ******************************************************
  void KSCClientWrapper::setSubOrderType(const basar::db::aspect::AccessorPropertyTable_YIterator iter)
  {
	m_subOrderType[0] = '\0';
	if (iter.isContainedAndSet("subordertype"))
	{
	  delimitedString2Char(m_subOrderType, iter.getString("subordertype"), LEN_SUBORDERTYPE);
	}
  }

	//*************************************** setPickingType ******************************************************
  void KSCClientWrapper::setPickingType(const basar::db::aspect::AccessorPropertyTable_YIterator iter)
  {
	delimitedString2Char(m_pickingType, iter.getString("pickingtype"), LEN_PICKINGTYPE);
  }

	//*************************************** setBookingType ******************************************************
  void KSCClientWrapper::setBookingType(const basar::db::aspect::AccessorPropertyTable_YIterator iter)
  {
	delimitedString2Char(m_bookingType, iter.getString("bookingtype"), LEN_BOOKINGTYPE);
  }

  //*************************************** setDeliveryDate ******************************************************
  void KSCClientWrapper::setDeliveryDate(const basar::db::aspect::AccessorPropertyTable_YIterator iter)
  {
	m_deliveryDate = iter.getDate("deliverydate").getDate();
  }

	//*************************************** setOrderHeadline ******************************************************
  void KSCClientWrapper::setOrderHeadline(
	const basar::db::aspect::AccessorPropertyTable_YIterator iter,
	basar::VarString headline)
  {
	delimitedString2Char(m_orderHeadline, iter.getString(headline), MAX_LEN_ORDERHEADLINE);
  }

	//*************************************** setOrderNote ******************************************************
  void KSCClientWrapper::setOrderNote(const basar::db::aspect::AccessorPropertyTable_YIterator iter)
  {
	delimitedString2Char(m_orderNote, iter.getString("ordernote"), MAX_LEN_ORDERNOTE);  //kdauftrag.bemerkungen
  }

	//*************************************** setReference ******************************************************
  void KSCClientWrapper::setReference(const basar::db::aspect::AccessorPropertyTable_YIterator iter)
  {
	m_reference[0] = '\0';
	if (iter.isContainedAndSet("reference"))
	{
	  delimitedString2Char(m_reference, iter.getString("reference"), MAX_LEN_REFERENCE);
	}
  }

	//*************************************** setArticleNo ******************************************************
  void KSCClientWrapper::setArticleNo(const basar::db::aspect::AccessorPropertyTable_YIterator iter)
  {
	m_articleNo = 0;
	if (iter.isContainedAndSet("articleno")) // alternative: ean
	{
	  m_articleNo = iter.getInt32("articleno");
	}
  }

	//*************************************** setEan ******************************************************
	void KSCClientWrapper::setEan(const basar::db::aspect::AccessorPropertyTable_YIterator iter)  {
		m_ean[0] = '\0';
		if (iter.isContainedAndSet("ean")) // alternative: articleno
			delimitedString2Char(m_ean, iter.getString("ean"), LEN_EAN);
	}// setEan

	//*************************************** setArticleCode ******************************************************
	void KSCClientWrapper::setArticleCode(const basar::db::aspect::AccessorPropertyTable_YIterator iter)  {
		m_articleCode[0] = '\0';
		if (iter.isContainedAndSet("articlecode")) // alternative: articleno
			delimitedString2Char(m_articleCode, iter.getString("articlecode"), MAX_LEN_ARTICLECODE);
	}// setArticleCode

	//*************************************** setOrderQty ******************************************************
	void KSCClientWrapper::setOrderQty(const basar::db::aspect::AccessorPropertyTable_YIterator iter) {
		m_orderQty = iter.getInt32("orderqty");
	}// setOrderQty

	//*************************************** setInterBranchTransfer ******************************************************
  void KSCClientWrapper::setInterBranchTransfer(const basar::db::aspect::AccessorPropertyTable_YIterator iter)
  {
	m_interBranchTransfer = iter.getInt16("interbranchtransfer");
  }

	//*************************************** setSubsequentDelivery ******************************************************
  void KSCClientWrapper::setSubsequentDelivery(const basar::db::aspect::AccessorPropertyTable_YIterator iter)
  {
	m_subsequentDelivery = iter.getInt16("subsequentdelivery");
  }

	//*************************************** setArticleRequirementPurchase ******************************************************
  void KSCClientWrapper::setArticleRequirementPurchase(const basar::db::aspect::AccessorPropertyTable_YIterator iter)
  {
	m_articleRequirementPurchase = iter.getInt16("articlerequirementpurchase");
  }

	//*************************************** setPartialDelivery ******************************************************
  void KSCClientWrapper::setPartialDelivery(const basar::db::aspect::AccessorPropertyTable_YIterator iter)
  {
	m_partialDelivery = iter.getInt16("partialdelivery");
  }

	//*************************************** setSequenceNo ******************************************************
  void KSCClientWrapper::setSequenceNo(const basar::db::aspect::AccessorPropertyTable_YIterator iter)
  {
	m_sequenceNo = 0;
	if (iter.isContainedAndSet("sequenceno"))
	{
	  m_sequenceNo = iter.getInt16("sequenceno");
	}
  }

	//*************************************** setItemNote ******************************************************
	void KSCClientWrapper::setItemNote(const basar::db::aspect::AccessorPropertyTable_YIterator iter)  {
		m_itemNote[0] = '\0';
		if (iter.isContainedAndSet("itemnote"))
			delimitedString2Char(m_itemNote, iter.getString("itemnote"), MAX_LEN_ITEMNOTE);
	}// setItemNote

	//*************************************** setOriginBranch ******************************************************
	void KSCClientWrapper::setOriginBranch(const basar::db::aspect::AccessorPropertyTable_YIterator iter) {
		m_originBranchNo = iter.getInt16("originbranchno");
	}// setOriginBranch

	//*************************************** setDeferredPaymentDate ******************************************************
	void KSCClientWrapper::setDeferredPaymentDate(const basar::db::aspect::AccessorPropertyTable_YIterator iter) {
		m_deferredPaymentDate = iter.getInt32("deferredpaymentdate");
	}// setDeferredPaymentDate

	//*************************************** setEdiDeliveryNote ******************************************************
	void KSCClientWrapper::setEdiDeliveryNote(const basar::db::aspect::AccessorPropertyTable_YIterator iter)  {
		m_ediDeliveryNote[0] = '\0';
		if (iter.isContainedAndSet("edideliverynote"))
			delimitedString2Char(m_itemNote, iter.getString("edideliverynote"), MAX_LEN_EDIDELIVERYNOTE);
	}// setEdiDeliveryNote

	//*************************************** setBatchOrderTyp ******************************************************
	void KSCClientWrapper::setBatchOrderTyp(const basar::db::aspect::AccessorPropertyTable_YIterator iter) {
		m_batchTyp = iter.getInt32("batchtyp");
	}// setBatchOrderTyp

	//*************************************** setIdfOrigin ******************************************************
	void KSCClientWrapper::setIdfOrigin(const basar::db::aspect::AccessorPropertyTable_YIterator iter) {
		m_idfOrigin = iter.getInt32("idforigin");
	}// setIdfOrigin

	//*************************************** setOrderNoOrigin ******************************************************
	void KSCClientWrapper::setOrderNoOrigin(const basar::db::aspect::AccessorPropertyTable_YIterator iter) {
		m_orderNoOrigin = iter.getInt32("ordernoorigin");
	}// setOrderNoOrigin

	//*************************************** setPosNoOrigin ******************************************************
	void KSCClientWrapper::setPosNoOrigin(const basar::db::aspect::AccessorPropertyTable_YIterator iter) {
		m_posNoOrigin = iter.getInt32("posnoorigin");
	}// setPosNoOrigin

void KSCClientWrapper::setRebateInKind( const basar::db::aspect::AccessorPropertyTable_YIterator iter )
{
	m_RebateInKind = iter.getInt32( "rebateinkind" );
}

void KSCClientWrapper::setFreeRebate( const basar::db::aspect::AccessorPropertyTable_YIterator iter )
{
	m_FreeRebate = iter.getDecimal( "discountpct" );
}

void KSCClientWrapper::setRebateType( const basar::db::aspect::AccessorPropertyTable_YIterator iter )
{
	m_RebateType = iter.getInt16( "kindofdiscount" );
}

void KSCClientWrapper::setBatchSchreiben( const basar::db::aspect::AccessorPropertyTable_YIterator iter )
{
	m_BatchSchreiben = iter.getInt32( "batchschreiben" );
}

void KSCClientWrapper::setBatch( const basar::db::aspect::AccessorPropertyTable_YIterator iter )
{
	m_Batch[0] = '\0';
	if (iter.isContainedAndSet("batch"))
		delimitedString2Char(m_Batch, iter.getString("batch"), MAX_LEN_BATCH);
}


	//*************************************** getInfoText ******************************************************
  void KSCClientWrapper::getInfoText(basar::VarString& str) const
  {
	delimitedChar2String(str, m_returnData->TEXT, MAX_LEN_INFOTEXT);
  }

	//*************************************** getOrderNo ******************************************************
  void KSCClientWrapper::getOrderNo(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setInt32("orderno", m_returnData->ORDERNO);
  }

	//*************************************** getEan ******************************************************
  void KSCClientWrapper::getEan(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->EAN, LEN_EAN);
	iterInfo.setString("ean", buf);
  }

  //*************************************** getTourId ******************************************************
  void KSCClientWrapper::getTourId(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->TOURID, LEN_TOURID);
	iterInfo.setString("tourid", buf);
  }

	//*************************************** getTourDate ******************************************************
  void KSCClientWrapper::getTourDate(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setDate("tourdate", m_returnData->TOURDATE);
  }

	//*************************************** getValueOfOrder ******************************************************
  void KSCClientWrapper::getValueOfOrder(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setDecimal("valueoforder", basar::Decimal(m_returnData->VALUEOFORDER));
  }

	//*************************************** getLinesOfOrder ******************************************************
  void KSCClientWrapper::getLinesOfOrder(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setInt32("linesoforder", m_returnData->LINESOFORDER);
  }

	//*************************************** getLackLines ******************************************************
  void KSCClientWrapper::getLackLines(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setInt32("lacklines", m_returnData->LACKLINES);
  }

	//*************************************** getTextLines ******************************************************
  void KSCClientWrapper::getTextLines(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setInt32("textlines", m_returnData->TEXTLINES);
  }

	//*************************************** getPharmacyName ******************************************************
  void KSCClientWrapper::getPharmacyName(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->PHARMACYNAME, MAX_LEN_PHARMACYNAME);
	iterInfo.setString("pharmacyname", buf);
  }

	//*************************************** getDeliveryBranchNo ******************************************************
  void KSCClientWrapper::getDeliveryBranchNo(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setInt16("deliverybranchno", m_returnData->DELIVERYBRANCHNO);
  }

	//*************************************** getArticleNo ******************************************************
  void KSCClientWrapper::getArticleNo(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setInt32("articleno", m_returnData->ARTICLENO);
  }

	//*************************************** getQtyLack ******************************************************
  void KSCClientWrapper::getQtyLack(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setInt32("qtylack", m_returnData->QTYLACK);
  }

	//*************************************** getLackReason ******************************************************
  void KSCClientWrapper::getLackReason(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setInt32("lackreason", m_returnData->LACKREASON);
  }

	//*************************************** getAuxQty ******************************************************
  void KSCClientWrapper::getAuxQty(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setInt32("auxqty", m_returnData->AUXQTY);
  }

	//*************************************** getArticleUnit ******************************************************
  void KSCClientWrapper::getArticleUnit(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->ARTICLEUNIT, MAX_LEN_ARTICLEUNIT);
	iterInfo.setString("articleunit", buf);
  }

	//*************************************** getArticleName ******************************************************
  void KSCClientWrapper::getArticleName(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->ARTICLENAME, MAX_LEN_ARTICLENAME);
	iterInfo.setString("articlename", buf);
  }

	//*************************************** getHandout ******************************************************
  void KSCClientWrapper::getHandout(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->HANDOUT, MAX_LEN_HANDOUT);
	iterInfo.setString("handout", buf);
  }

	//*************************************** getAuxBranchNo ******************************************************
  void KSCClientWrapper::getAuxBranchNo(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setInt16("auxbranchno", m_returnData->AUXBRANCHNO);
  }

	//*************************************** getCodeBlocage ******************************************************
  void KSCClientWrapper::getCodeBlocage(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->CODEBLOCAGE, MAX_LEN_CODEBLOCAGE);
	iterInfo.setString("codeblocage", buf);
  }

	//*************************************** getRestDeliveryQty ******************************************************
  void KSCClientWrapper::getRestDeliveryQty(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setInt32("restdeliveryqty", m_returnData->RESTDELIVERYQTY);
  }

	//*************************************** getDeliveryQty ******************************************************
  void KSCClientWrapper::getDeliveryQty(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setInt32("deliveryqty", m_returnData->DELIVERYQTY);
  }

	//*************************************** getLackReasonCtyCode ******************************************************
  void KSCClientWrapper::getLackReasonCtyCode(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->LACKREASONCTYCODE, MAX_LEN_LACKREASONCTYCODE);
	iterInfo.setString("lackreasonctycode", buf);
  }

	//*************************************** getPharmPurchPrice ******************************************************
  void KSCClientWrapper::getPharmPurchPrice(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setDecimal("pharmpurchprice", basar::Decimal(m_returnData->PHARMPURCHPRICE));
  }

	//*************************************** getCustPurchPrice ******************************************************
  void KSCClientWrapper::getCustPurchPrice(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setDecimal("custpurchprice", basar::Decimal(m_returnData->CUSTPURCHPRICE));
  }

	//*************************************** getPharmSellPrice ******************************************************
  void KSCClientWrapper::getPharmSellPrice(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setDecimal("pharmsellprice", basar::Decimal(m_returnData->PHARMSELLPRICE));
  }

	//*************************************** getTaxRate ******************************************************
  void KSCClientWrapper::getTaxRate(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setDecimal("taxrate", basar::Decimal(m_returnData->TAXRATE));
  }

	//*************************************** getExpiryDate ******************************************************
  void KSCClientWrapper::getExpiryDate(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setDate("expirydate", m_returnData->EXPIRYDATE);
  }

	//*************************************** getLpprPrice ******************************************************
  void KSCClientWrapper::getLpprPrice(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setDecimal("lpprprice", basar::Decimal(m_returnData->LPPR_PRICE));
  }

	//*************************************** getSeraCode ******************************************************
  void KSCClientWrapper::getSeraCode(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->SERACODE, MAX_LEN_SERACODE);
	iterInfo.setString("seracode", buf);
  }

	//*************************************** getXmlCode ******************************************************
  void KSCClientWrapper::getXmlCode(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->XMLCODE, MAX_LEN_XMLCODE);
	iterInfo.setString("xmlcode", buf);
  }

	//*************************************** getXmlText ******************************************************
  void KSCClientWrapper::getXmlText(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->XMLTEXT, MAX_LEN_XMLTEXT);
	iterInfo.setString("xmltext", buf);
  }

	//*************************************** getArticleUnitOrg ******************************************************
  void KSCClientWrapper::getArticleUnitOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->ARTICLEUNITORG, MAX_LEN_ARTICLEUNITORG);
	iterInfo.setString("articleunitorg", buf);
  }

	//*************************************** getArticleNameOrg ******************************************************
  void KSCClientWrapper::getArticleNameOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->ARTICLENAMEORG, MAX_LEN_ARTICLENAMEORG);
	iterInfo.setString("articlenameorg", buf);
  }

	//*************************************** getHandoutOrg ******************************************************
  void KSCClientWrapper::getHandoutOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->HANDOUTORG, MAX_LEN_HANDOUTORG);
	iterInfo.setString("handoutorg", buf);
  }

	//*************************************** getPharmPurchPriceOrg ******************************************************
  void KSCClientWrapper::getPharmPurchPriceOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setDecimal("pharmpurchpriceorg", basar::Decimal(m_returnData->PHARMPURCHPRICEORG));
  }

	//*************************************** getCustPurchPriceOrg ******************************************************
  void KSCClientWrapper::getCustPurchPriceOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setDecimal("custpurchpriceorg", basar::Decimal(m_returnData->CUSTPURCHPRICEORG));
  }

	//*************************************** getPharmSellPriceOrg ******************************************************
  void KSCClientWrapper::getPharmSellPriceOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setDecimal("pharmsellpriceorg", basar::Decimal(m_returnData->PHARMSELLPRICEORG));
  }

	//*************************************** getTaxRateOrg ******************************************************
  void KSCClientWrapper::getTaxRateOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setDecimal("taxrateorg", basar::Decimal(m_returnData->TAXRATEORG));
  }

	//*************************************** getLpprPriceOrg ******************************************************
  void KSCClientWrapper::getLpprPriceOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setDecimal("lpprpriceorg", basar::Decimal(m_returnData->LPPR_PRICEORG));
  }

	//*************************************** getArticleNoOrg ******************************************************
  void KSCClientWrapper::getArticleNoOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	iterInfo.setInt32("articlenoorg", m_returnData->ARTICLENOORG);
  }

	//*************************************** getCodeBlocageOrg ******************************************************
  void KSCClientWrapper::getCodeBlocageOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->CODEBLOCAGEORG, MAX_LEN_CODEBLOCAGEORG);
	iterInfo.setString("codeblocageorg", buf);
  }

	//*************************************** getSeraCodeOrg ******************************************************
  void KSCClientWrapper::getSeraCodeOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->SERACODEORG, MAX_LEN_SERACODEORG);
	iterInfo.setString("seracodeorg", buf);
  }

	//*************************************** getXmlCodeOrg ******************************************************
  void KSCClientWrapper::getXmlCodeOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->XMLCODEORG, MAX_LEN_XMLCODEORG);
	iterInfo.setString("xmlcodeorg", buf);
  }

	//*************************************** getXmlTextOrg ******************************************************
  void KSCClientWrapper::getXmlTextOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const
  {
	basar::VarString buf;
	delimitedChar2String(buf, m_returnData->XMLTEXTORG, MAX_LEN_XMLTEXTORG);
	iterInfo.setString("xmltextorg", buf);
  }

	//*************************************** evaluateKSCRetVal ******************************************************
  bool KSCClientWrapper::evaluateKSCRetVal(
	basar::Int32 result,
	KSCClientDMReturn& returnStruct) const
  {
	switch (result)
	{
	  case 0:  // success
		getInfoText(returnStruct.textInfo);
		returnStruct.stateInfo = OK;
		return true;
	  case 6:  // input error
		getInfoText(returnStruct.textInfo);
		returnStruct.stateInfo = INPUT_ERROR;
		return true;
	  case -5:  // out of operating time error 
		getInfoText(returnStruct.textInfo);
		returnStruct.stateInfo = OUT_OF_OPERATING_TIME_ERROR;
		return true;
	  default:
		return false;
	}
  }

	//*************************************** delimitedString2Char ******************************************************
  void KSCClientWrapper::delimitedString2Char(char* const dest, const basar::VarString& source, basar::Int16 maxLength) const
  {
	  memset( dest, '\0', maxLength );
	  dest[maxLength] = '\0'; // Buffer length is actually maxLength + 1

#ifdef WIN32
	#if _MSC_VER > 1000 
		strncpy_s( dest, maxLength + 1, source.c_str(), source.length() );
	#else
		strncpy(dest, source.c_str(), maxLength);
	#endif // _MSC_VER > 1000 
#else
	strncpy(dest, source.c_str(), maxLength);
#endif
  }

	//*************************************** delimitedChar2String ******************************************************
  void KSCClientWrapper::delimitedChar2String(basar::VarString& dest, const char* const source, basar::Int16 maxLength) const
  {
	dest = basar::VarString(source, 0, maxLength);
	dest.cleanchar();
	dest.trim();
  }

	//*************************************** kscSetNoRouting ******************************************************
	void KSCClientWrapper::kscSetNoRouting()
	{
		SetNoRouting();
	}

}
