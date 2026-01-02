//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <boost/lexical_cast.hpp>
#include <icsc_logger.h>
#include <iapplconfiguration.h>
#include <libbasardbaspect_accessorpropertytable.h>
#include <libbasardbaspect_accessorpropertytable_yiterator.h>

#include "pxvborderdm_definitions.h"
#include "ordertransformer.h"
#include "pxvborderdm.h"
#include "recordtypecollection.h"
#include "recordtypebase.h"
#include "stringtransformer.h"

#include "recordtypeorderheaderptr.h"
#include "recordtypeorderheader.h"

#include "recordtypeordertextptr.h"
#include "recordtypeordertext.h"

#include "recordtyperemarkptr.h"
#include "recordtyperemark.h"

#include "recordtypeorderinfoptr.h"
#include "recordtypeorderinfo.h"

#include "recordtypeinterbranchinfoptr.h"
#include "recordtypeinterbranchinfo.h"

#include "recordtypeorderline.h"

#include "recordtypeorderresponseptr.h"
#include "recordtypeorderresponse.h"

#include "recordtypemsv3infoptr.h"
#include "recordtypemsv3info.h"

#include "recordtypeibtpickingdataptr.h"
#include "recordtypeibtpickingdata.h"

#include "icicsorderdm.h"

#include <discount/orderpositiondiscount/orderpositiondiscountcollection.h>
#include <discount/orderpositiondiscount/orderpositiondiscount.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepositoryptr.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepository.h>

#include <ibt/componentmanager/ibtcomponentmanager.h>
#include <ibt/ibtrequest/ibtrequestrepository.h>
#include <ibt/ibtrequest/iibtrequestptr.h>
#include <ibt/ibtrequest/iibtrequest.h>
#include <ibt/ibtresponse/ibtresponserepository.h>
#include <ibt/ibtresponse/iibtresponse.h>

#include <cscorder/componentmanager/cscordercomponentmanager.h>
#include <cscorder/cscorderibtpickingdata/icscorderibtpickingdatarepositoryptr.h>
#include <cscorder/cscorderibtpickingdata/icscorderibtpickingdatarepository.h>
#include <cscorder/cscorderibtpickingdata/cscorderibtpickingdata.h>

#include "csccustomer.hpp"
#include "tourmasterdatalist.hpp"
#include "tourmasterdata.hpp"

#include "recordtypediscount.h"
#include "recordtypediscountptr.h"

#include <pxtenderhead.hpp>
#include <pxorderdiscacc.hpp>
#include <pxtxtdoc.hpp>
#include <pxoclpar.hpp>
#include <pxorderremarks.hpp>
#include <pxitem.hpp>
#include <pxitemdiscount.hpp>
#include <pxcustinf.hpp>
#include <pxoeparm.hpp>
#include <pxcstbas.hpp>
#include <pxcustomerflags.hpp>
#include <pxdiscountdef.h>
#include <nntypes.h>
#include <pxbase/pxconstants.hpp>
#include <pxartprc.hpp>
#include <pxparameter.hpp>

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

namespace domMod
{
namespace corpha
{
namespace ProcessOrderDM
{

	//----------------------------------------------------------------------------//
	OrderTransformer::OrderTransformer( libcsc_utils::ICSC_LoggerPtr logger, libcsc_utils::IApplConfigurationPtr appconfig )
		: m_Logger( logger ), m_ApplConfiguration( appconfig )
	{
		METHODNAME_DEF( OrderTransformer, OrderTransformer );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	OrderTransformer::~OrderTransformer()
	{
		METHODNAME_DEF( OrderTransformer, ~OrderTransformer );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	recordtypes::RecordTypeCollectionPtr OrderTransformer::getCollection()
	{
		METHODNAME_DEF( OrderTransformer, getCollection );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		if( 0 == m_RecordTypeCollection.get() )
		{
			m_RecordTypeCollection = recordtypes::RecordTypeCollectionPtr( new recordtypes::RecordTypeCollection( m_Logger ) );
		}
		return m_RecordTypeCollection;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	recordtypes::RecordTypeCollectionPtr OrderTransformer::transform( domMod::corpha::processOrder::ICICSOrderDMPtr cicsorderdm )
	{
		METHODNAME_DEF( OrderTransformer, transform );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		getCollection()->clear();
		for( basar::db::aspect::AccessorPropertyTable_YIterator yit = cicsorderdm->getResponsePropTab().begin(); yit != cicsorderdm->getResponsePropTab().end(); ++yit )
		{
			domMod::corpha::processOrder::CICSRecord data = cicsorderdm->getCICSRecord( yit );
			recordtypes::RecordTypeOrderResponsePtr record( new recordtypes::RecordTypeOrderResponse( data.Buffer, m_Logger ) );
			getCollection()->addRecord( record );
			getCollection()->setCSCOrderNo( data.CSCOrderNo );
		}
		return m_RecordTypeCollection;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	recordtypes::RecordTypeCollectionPtr OrderTransformer::transform( pxVerbund::PXVBOrderDMPtr order )
	{
		METHODNAME_DEF( OrderTransformer, transform );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		getCollection()->clear();
		getCollection()->setCSCOrderNo( order->getOrderHeader()->getOrder()->KdAuftragNr() );
		getCollection()->setTransferTimeID( order->getTime() );

		addOrderHeader( order );
		addRemarks( order );
		addHeaderTexts( order );
		addFooterTexts( order );
		addOrderInfo( order );
		addOrderItems( order );
		addMSV3InfoItems( order );

		return m_RecordTypeCollection;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::addOrderHeader( pxVerbund::PXVBOrderDMPtr order )
	{
		METHODNAME_DEF( OrderTransformer, addOrderHeader );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		unsigned long ETAuftragFlags[6];
		order->getOrderHeader()->getOrder()->ETAuftrag().Export(ETAuftragFlags, 6, 2);

		OriginTypeEnum batchschreiben = order->getOrderHeader()->getOrder()->BatchSchreiben();
		basar::VarString origin;

		if (batchschreiben > 0)
		{
			origin = static_cast<const char*>(pxOrderCloseParam::ConvertBatchSchreiben(batchschreiben));
		}
		else
		{
			origin = " ";
		}

		recordtypes::RecordTypeOrderHeaderPtr record( new recordtypes::RecordTypeOrderHeader( m_Logger ) );

		if( order->getOrderHeader()->isCalcExpressCharge() )
		{
			record->setExpressDeliveryCharge("J");
		}
		else
		{
			record->setExpressDeliveryCharge("N");
		}

		record->setPurchaseOrderNo( order->getOrderHeader()->getOrder()->getPurchaseOrderNo() );
		record->setPaymentType( basar::VarString(order->getOrderHeader()->getOrder()->PaymentType()) );
		record->setMandant( order->getOrderHeader()->getOrder()->Vertriebszentrum() );
		record->setOrderNo( order->getOrderHeader()->getOrder()->KdAuftragNr() );
		record->setCustomerNo( order->getOrderHeader()->getOrder()->IDFNr() );
		record->setTerminalId( order->getOrderHeader()->getOrder()->GeraetName()() );
		record->setTourId( order->getOrderHeader()->getOrder()->TourId()() );
		record->setTourIdOld( order->getOrderHeader()->getOrder()->TourIdAlt()() );
		record->setUserId( order->getOrderHeader()->getOrder()->PersonalNr() );
		record->setBranchNo( order->getOrderHeader()->getOrder()->OrderFilialNr() );
		record->setET1Flags( (long) ETAuftragFlags[0] );
		record->setET2Flags( (long) ETAuftragFlags[1] );
		record->setET3Flags( (long) ETAuftragFlags[2] );
		record->setET4Flags( (long) ETAuftragFlags[3] );
		record->setET5Flags( (long) ETAuftragFlags[4] );
		record->setET6Flags( (long) ETAuftragFlags[5] );
		record->setOrderType( order->getOrderHeader()->getOrder()->KdAuftragArt()() );
		record->setPickingType( basar::VarString( order->getOrderHeader()->getOrder()->KoArt() ) );
		record->setBookingType( basar::VarString( order->getOrderHeader()->getOrder()->BuchArt() ) );
		record->setValidationDate( order->getOrderHeader()->getOrder()->DatumValuta().GetYYYYMMDD() );
		basar::Decimal wertAuftrag( order->getOrderHeader()->getOrder()->WertAuftrag());
		record->setOrderValue( wertAuftrag );
		basar::Decimal wertLieferung( order->getOrderHeader()->getOrder()->WertLieferung() );
		record->setDeliveryValue( wertLieferung );
		basar::Decimal wertZeilen( order->getOrderHeader()->getOrder()->WertZeilen() );
		record->setAvgLineValue( wertZeilen );
		record->setLines( order->getOrderHeader()->getOrder()->AnzPos() );
		record->setLinesNoCalc( order->getOrderHeader()->getOrder()->AnzPosOB() );
		record->setLinesDialUp( order->getOrderHeader()->getOrder()->AnzPosDafue() );
		record->setLinesDialUpErrors( order->getOrderHeader()->getOrder()->AnzPosDafueFehler() );
		record->setLinesAlphaTxt( order->getOrderHeader()->getOrder()->AnzAlphaText() );
		record->setLinesNarcotics( order->getOrderHeader()->getOrder()->AnzBTM() );
		basar::Decimal rabattBarProz( order->getOrderHeader()->getOrder()->RabattBarProz() );
		record->setCashDiscountPercentage( rabattBarProz );
		record->setOrigin( origin );
		record->setOriginBranchNo( order->getOrderHeader()->getOrder()->HerkunftFiliale() );
		record->setNextTourId( order->getOrderHeader()->getOrder()->NaechsteTour()() );
		record->setLastTourId( order->getOrderHeader()->getOrder()->LetzteTour()() );
		record->setDialUpOrderNo( order->getOrderHeader()->getOrder()->DafueAuftragNr() );
		record->setDialUpDeviceType( order->getOrderHeader()->getOrder()->DafueGeraeteName()() );
		basar::VarString data = order->getOrderHeader()->getOrder()->Bemerkungen()();
		record->setHint( StringTransformer::transform( data ) );
		record->setBatchOrderNo( order->getOrderHeader()->getOrder()->BatchAuftragNr() );
		record->setSubOrderType( order->getOrderHeader()->getOrder()->SubOrderType()() );
		record->setPaymentTerm( order->getOrderHeader()->getOrder()->PaymentTerm()() );
		record->setValueMonthManual( order->getOrderHeader()->getOrder()->ValutaMonManuell() );
		record->setValueMonthAuto( order->getOrderHeader()->getOrder()->ValutaMonAuto() );
		record->setPartialOrder( order->getOrderHeader()->getOrder()->AnzAuf() );
		record->setTenderNo( order->getOrderHeader()->getOrder()->TenderNo() );
		record->setShipmentDate( order->getOrderHeader()->getOrder()->DatumVersand().GetYYYYMMDD() );
		record->setNarcoticsFormNo( order->getOrderHeader()->getOrder()->BTMFormularNr()() );
		record->setValueDateDays( order->getOrderHeader()->getOrder()->GetValutaDays() );
		record->setXMLReference( order->getOrderHeader()->getOrder()->XMLReferenceNo()() );

		if( order->getOrderHeader()->getOrder()->IsAuftragSHWithC() )
		{
			record->setParentBranchFlag( "C" );
		}
		else if( order->getOrderHeader()->getOrder()->IsAuftragSHWithS() )
		{
			record->setParentBranchFlag( "S" );
		}

		if( order->getOrderHeader()->getOrder()->TenderHead() )
		{
			record->setContractNo( order->getOrderHeader()->getOrder()->TenderHead()->ContractNo()() );
		}

		if( order->getOrderHeader()->getOrderDiscountAccount().get() )
		{
			record->setDiscountAccFromDate( order->getOrderHeader()->getOrderDiscountAccount()->DateFrom().GetYYYYMMDD() );
			record->setDiscountAccToDate( order->getOrderHeader()->getOrderDiscountAccount()->DateTo().GetYYYYMMDD() );
			if( 1 == order->getOrderHeader()->getOrderDiscountAccount()->SwChain() )
			{
				record->setChainMember( "J" );
			}
		}

		if( order->getOrderHeader()->getOrderCalcMode().get() )
		{
			if( 1 == order->getOrderHeader()->getOrderCalcMode()->Print() )
			{
				record->setPrintPriceProposal( "J" );
			}
			if( 2 == order->getOrderHeader()->getOrderCalcMode()->Print() )
			{
				record->setPrintPriceProposal( "2" );
			}
			if( 1 == order->getOrderHeader()->getOrderCalcMode()->DeductionAep() )
			{
				record->setDeductionPharmacyPurchasePrice( "J" );
			}
			if( 1 == order->getOrderHeader()->getOrderCalcMode()->DeductionAvp() )
			{
				record->setDeductionPharmacySellPrice( "J" );
			}
			if( 1 == order->getOrderHeader()->getOrderCalcMode()->WithColumnNr() )
			{
				record->setDeductionColumnNo( "1" );
			}
			if( 1 == order->getOrderHeader()->getOrderCalcMode()->ByEmail() )
			{
				record->setEmailInvoice( "J" );
			}
		}

		if( order->getOrderHeader()->getOrderProLink().get() )
		{
			nString InvoiceNumberPro = order->getOrderHeader()->getOrderProLink()->InvoiceNumberPro();
			InvoiceNumberPro.Trim(7);
			record->setPseudoInvoiceNo( atoi( InvoiceNumberPro ) );
            if (TourUtil::getNullDate() != order->getOrderHeader()->getOrderProLink()->DateProforma())
            {
                record->setProformaOrderDate(order->getOrderHeader()->getOrderProLink()->DateProforma().GetYYYYMMDD());
            }
		}
		else
		{
			// PHARMAONE   (09.09.2016) - Versorgung Pseudo-Rechnungsnummer aus Originalrechnungsnummer - Übertragung in A1PSRENR
			record->setPseudoInvoiceNo( order->getOrderHeader()->getOrder()->getOriginalInvoiceNo() );
		}

		if( order->isMSV3Order() )
		{
			record->setMSV3Order( "J" );
		}

		if( order->getOrderHeader()->getOrder()->TenderHead() )
		{
			record->setTenderType( order->getOrderHeader()->getOrder()->TenderHead()->TenderType() );
		}

		getCollection()->addRecord( record ); // A1 record must be added as first record in the collection

		addDiscountRecords( order->getOrderHeader(), record );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::addRemarks( pxVerbund::PXVBOrderDMPtr order )
	{
		METHODNAME_DEF( OrderTransformer, addRemarks );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
		try
		{
			::pxGenericOrderRemarkList remarklist = order->getOrderHeader()->getOrder()->getGenericOrderRemarks();
			if( remarklist.Entries() > 0 )
			{
				::pxGenericOrderRemarkListIter iter = ::pxGenericOrderRemarkListIter(remarklist);
				::pxGenericOrderRemark* remark;

				while( NULL != (remark = (::pxGenericOrderRemark*)++iter) )
				{
					recordtypes::RecordTypeRemarkPtr record( new recordtypes::RecordTypeRemark( m_Logger ) );
					record->setOrderNo( remark->CSCOrderNo() );
					record->setPositionNo( remark->PositionNo() );
					record->setTextType( (short)remark->RemarkType() );
					record->setSequentialNo( remark->TextNumber() );

					basar::VarString data = remark->RemarkText();
					record->setText( StringTransformer::transform( data ) );
					getCollection()->addRecord( record );
				}
			}
		}
		catch(...)
		{
			basar::VarString logmsg("");
			logmsg.format( "   unexpected exception in OrderTransformer::addRemarks" );
			m_Logger->log( log4cplus::ERROR_LOG_LEVEL, logmsg );
		}
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::addHeaderTexts( pxVerbund::PXVBOrderDMPtr order )
	{
		METHODNAME_DEF( OrderTransformer, addHeaderTexts );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		::pxTextDoc* headtext = order->getOrderHeader()->getHeadText();
		::pxTextDocIter iter = ::pxTextDocIter(*headtext);
		if( headtext->Entries() > 0 )
		{
			while ( (headtext = (pxTextDoc*)++iter) != NULL )
			{
				nString headline = ((pxTextLine*) headtext)->Text();
				headline.Strip();
				if( !headline.IsEmpty() )
				{
					if( headline(headline.Length()-1) == cNEWLINE )
					{
						headline.Trim(headline.Length()-1);
					}
					if( "DOPPELTE BESTELLUNG." == headline )
					{
						continue;
					}
					if( "AUFTRAG ZURUECKGESTELLT WEGEN UMBUCHEN." == headline )
					{
						continue;
					}
					recordtypes::RecordTypeOrderTextPtr record( new recordtypes::RecordTypeOrderText( recordtypes::HEADTEXT, m_Logger ) );
					basar::VarString data = headline();
					record->setText( StringTransformer::transform( data ) );
					getCollection()->addRecord( record );
				}
			}
		}
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::addFooterTexts( pxVerbund::PXVBOrderDMPtr order )
	{
		METHODNAME_DEF( OrderTransformer, addFooterTexts );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		::pxTextDoc* text = order->getOrderHeader()->getFooterText();
		::pxTextDocIter iter = ::pxTextDocIter(*text);
		if( text->Entries() > 0 )
		{
			while ( (text = (pxTextDoc*)++iter) != NULL )
			{
				nString footerline = ((pxTextLine*)text)->Text();
				recordtypes::RecordTypeOrderTextPtr record( new recordtypes::RecordTypeOrderText( recordtypes::TAILTEXT, m_Logger ) );
				basar::VarString data = footerline();
				record->setText( StringTransformer::transform( data ) );
				getCollection()->addRecord( record );
			}
		}
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::addOrderInfo( pxVerbund::PXVBOrderDMPtr order )
	{
		METHODNAME_DEF( OrderTransformer, addOrderInfo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		if( order->getOrderHeader()->getOrderInfo().get() )
		{
			if( !order->getOrderHeader()->getOrder()->Customer()->Flags().IsMehrfachBestell() )
			{
				order->getOrderHeader()->getOrderInfo()->CheckMembers();
			}

			recordtypes::RecordTypeOrderInfoPtr record( new recordtypes::RecordTypeOrderInfo( m_Logger ) );
			record->setCustomerOrderNo( order->getOrderHeader()->getOrderInfo()->KdAuftragNr() );
			record->setPharmacyOrderNo( order->getOrderHeader()->getOrderInfo()->KdAuftragBestellNr()() );
			record->setInternalCustomerNo( order->getOrderHeader()->getOrderInfo()->IDFNrIntern() );
			record->setPharmacyTour( order->getOrderHeader()->getOrderInfo()->ApoTourId()() );
			record->setShipmentType( order->getOrderHeader()->getOrderInfo()->VersandArt()() );
			record->setProcessNo( order->getOrderHeader()->getOrderInfo()->ProcessNr() );
			record->setEDIDeliveryNote( basar::VarString( order->getOrderHeader()->getOrderInfo()->EdiLieferSchein() ) );
			record->setBatchOrderNo( order->getOrderHeader()->getOrderInfo()->BatchAuftragNr() );

			getCollection()->addRecord( record );
		}
	}
	//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
	void OrderTransformer::addMSV3InfoItems( pxVerbund::PXVBOrderDMPtr order )
	{
		METHODNAME_DEF( OrderTransformer, addMSV3InfoItems );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		if( order->isMSV3Order() || order->isSwimpATOrder() )
		{
			addMSV3OrderLabel(order);
			addMSV3PackageLabels(order);
		}
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::addMSV3OrderLabel( pxVerbund::PXVBOrderDMPtr order )
	{
		METHODNAME_DEF( OrderTransformer, addMSV3OrderLabel );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		recordtypes::RecordTypeMSV3InfoPtr record( new recordtypes::RecordTypeMSV3Info( recordtypes::ORDERLABEL, m_Logger ) );
		record->setKSCOrderNo( order->getOrderHeader()->getOrder()->KdAuftragNr() );
		basar::VarString data = order->getOrderHeader()->getOrder()->OrderLabel()();
		record->setText( StringTransformer::transform( data ) );
		getCollection()->addRecord( record );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::addMSV3PackageLabels( pxVerbund::PXVBOrderDMPtr order )
	{
		METHODNAME_DEF( OrderTransformer, addMSV3PackageLabels );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		if( order->m_PackageLabelCollection.hasItems() )
		{
			pxVerbund::PackageLabelCollection::sPackageLabelItem label = order->m_PackageLabelCollection.getFirst();
			addMSV3PackageLabel( order, label.PackageLabelID, label.PackageLabel );

			while( !order->m_PackageLabelCollection.isEnd() )
			{
				label = order->m_PackageLabelCollection.getNext();
				addMSV3PackageLabel( order, label.PackageLabelID, label.PackageLabel );
			}
		}
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::addMSV3PackageLabel( pxVerbund::PXVBOrderDMPtr order, const basar::Int32 seqno, const basar::VarString& label )
	{
		recordtypes::RecordTypeMSV3InfoPtr record( new recordtypes::RecordTypeMSV3Info( recordtypes::PACKAGELABEL, m_Logger ) );
		record->setKSCOrderNo( order->getOrderHeader()->getOrder()->KdAuftragNr() );
		record->setSeqNo( seqno );
		record->setText( StringTransformer::transform( ( basar::VarString& )label ) );
		getCollection()->addRecord( record );

		basar::VarString logmsg("");
		logmsg.format( "   added MSV3PackageLabel: (%d) %s", seqno, label.c_str() );
		m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmsg );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::addOrderItems( pxVerbund::PXVBOrderDMPtr order )
	{
		METHODNAME_DEF( OrderTransformer, addOrderItems );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		::pxOrderItemListIter itemiter = order->getOrderItemIterator();
		::pxOrderItem* item;
		while ( (item = (::pxOrderItem*)++itemiter) != NULL )
		{
			pxVerbund::PXVBOrderItemPtr orderitem = order->createOrderItem( item );
			if( orderitem->hasToBeTransferred() )
			{
				order->getOrderHeader()->getOrder()->getIbtRequestHandler().readIbtRequest(
					order->getOrderHeader()->getOrder(), item);
				addOrderItem( orderitem, order );
			}
		}
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::addInterBranchTransferInfo( pxVerbund::PXVBOrderDMPtr order, pxVerbund::PXVBOrderItemPtr item, recordtypes::RecordTypeOrderLinePtr lineRecord)
	{
		METHODNAME_DEF( OrderTransformer, addInterBranchTransferInfo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		// add information of ibt original customers only for shuttle orders (batchschreiben 1)
		if( cORTYPE_AUXILIARY != order->getOrderHeader()->getOrder()->BatchSchreiben() ) return;

		pxOrderItem* pxItem = item->getOrderItem();
		libcsc::ibt::IIbtResponseRepositoryPtr responseRepo = pxItem->Session()->getIbtComponentManager()->createIbtResponseRepository();
		libcsc::ibt::IIbtResponsePtr response = responseRepo->findIbtResponse(pxItem->KdAuftragNr(), pxItem->PosNr());
		if (NULL == response.get() || response->getIbtResponseId().isUnset())
		{
			return;
		}

		libcsc::ibt::IIbtRequestRepositoryPtr repo = pxItem->Session()->getIbtComponentManager()->createIbtRequestRepository();
		libcsc::ibt::IIbtRequestPtr request = repo->findIbtRequestById( response->getIbtRequestId() );
		if (NULL == request.get() || request->getIbtRequestId().isUnset())
		{
			return;
		}

		CSCCustomer customer(pxItem->Session(), request->getBranchNo(), request->getCustomerNo());
		if (0 != customer.Read())
		{
			return;
		}
		recordtypes::RecordTypeInterBranchInfoPtr record( new recordtypes::RecordTypeInterBranchInfo( m_Logger ) );
		record->setBranchNo			( request->getIbtBranchNo() );
		record->setOriginBranchNo	( request->getBranchNo() );
		record->setCustomerNo		( request->getCustomerNo() );
		record->setTourId			( request->getCustomerTourId().stoi() );
		record->setWeekdayId		( request->getTourWeekDay() );

		record->setPharmacyName		( customer.getNameApo() );
		record->setOwnerName		( customer.getNameInhaber() );
		record->setStreet			( customer.getStrasse() );
		record->setPostalCode		( customer.getPostLeitZahl().stoi() );
		record->setCity				( customer.getOrt() );
		record->setPhoneNo			( customer.getTelnr() );
		record->setDialUpPhoneNo	( customer.getTelnrDafue() );
		record->setFax				( customer.getFaxnr() );
		record->setSalutationId		( customer.getAnredeKz() );
		record->setSalesRepNo		( customer.getPersonalNrVertr() );
		record->setDistrictNo		( customer.getImsBezirkNr() );
		record->setCustomerGroup	( customer.getKdGruppe() );
		record->setWebShopFlag		( customer.isVersandApo() == "1" ? "J" : "N" );
		record->setLanguage			( customer.getKzSprache() );
		record->setDecTourId		(0L);
		record->setOrderChannel(atoi(customer.getDafueSystemSchluessel().c_str()));


        lineRecord->setIBTOriginFMDCustomer(customer.isFMDCustomer());

		TourMasterDataList tmdl(pxItem->Session());
		tmdl.getTourMasterData( request->getBranchNo(), request->getCustomerTourId().c_str() );
		if( tmdl.Entries() > 0 )
		{
			TourMasterDataListIter iter(tmdl);
			TourMasterData* tmd = NULL;
			tmd = (TourMasterData*)++iter;
			record->setDecTourId( tmd->getDecTour() );
		}

		getCollection()->addRecord(record);
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::addOrderItem( pxVerbund::PXVBOrderItemPtr item, pxVerbund::PXVBOrderDMPtr order )
	{
		METHODNAME_DEF( OrderTransformer, addOrderItem );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		if( m_ApplConfiguration->isExtendedLoggingSet() )
		{
			basar::VarString logmsg("");
			logmsg.format( "   processing orderitem lineno:%d pzn:%d", item->getOrderItem()->PosNr(), item->getOrderItem()->ArtikelNr() );
			m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmsg );
		}

		recordtypes::RecordTypeOrderLinePtr record( new recordtypes::RecordTypeOrderLine( m_Logger ) );
		setStdItemValues( item, record );

		if( item->checkDispo() )
		{
			setDispoItemValues( item, record );
		}
		else
		{
			addInterBranchTransferInfo( order, item, record );
			setNormalOrderItemValues( item, record );
		}

		addDiscountRecords( item, record );

		if( order->isMSV3Order() )
		{
			if( order->hasOrderTypeWithPackageLabels() )
			{
				addMSV3PackageLabelItemInfo( item, record, order );
			}
		}

		getCollection()->addRecord( record );

        addIBTPickingInformationForIBT(item);
	}
	//----------------------------------------------------------------------------//

	void OrderTransformer::addIBTPickingInformationForIBT(pxVerbund::PXVBOrderItemPtr item)
    {
        if (item->getOrder()->BatchSchreiben() == cORTYPE_PURE_IBT_ORDER)
        {
            libcsc::cscorder::domMod::CSCOrderIBTPickingdataCollectionPtr ibtPickingData = item->getOrderItem()->getIBTPickingDataCollection();
            if (NULL != ibtPickingData.get())
            {
                libcsc::cscorder::domMod::CSCOrderIBTPickingdataCollection::Iterator ibtPickingDataIter;
                size_t serialNo = 0;
                for (ibtPickingDataIter = ibtPickingData->begin(); ibtPickingDataIter != ibtPickingData->end(); ++ibtPickingDataIter)
                {
                    ++serialNo;
                    recordtypes::RecordTypeIBTPickingDataPtr record(new recordtypes::RecordTypeIBTPickingData(m_Logger));
                    record->setBatch((*ibtPickingDataIter)->getBatch());
                    record->setCSCOrderNo((*ibtPickingDataIter)->getCscOrderNo());
                    record->setCSCOrderPosNo((*ibtPickingDataIter)->getCscOrderPosNo());
                    record->setDeliveryPosNo((*ibtPickingDataIter)->getDeliveryPosNo());
                    record->setDeliveryQty((*ibtPickingDataIter)->getQuantity());
                    record->setExpiryDate((*ibtPickingDataIter)->getExpiryDate());
                    record->setIBTBranchNo(item->getOrderItem()->VerbundFilialNr());
                    record->setSequentialNo(serialNo);
                    getCollection()->addRecord(record);
                }
            }
        }
    }
    //----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::addDiscountRecords( pxVerbund::PXVBOrderHeaderPtr orderheader, recordtypes::RecordTypeOrderHeaderPtr recordHead )
	{
		if (orderheader->getOrder()->Param()->IsUseNewDiscountCalc())
		{
			recordHead->setNumberOfDiscountRecords( orderheader->getNumberOfDiscountRecords() );

			// HR-08 -> add recordtypes RecordTypeDiscount for each discount record of the current order
			libcsc::discount::OrderPositionDiscountListPtr discountList = orderheader->getOrder()->getDiscountList();
			libcsc::discount::OrderPositionDiscountList::const_iterator iter = discountList->begin();
			for( ; iter != discountList->end(); ++iter )
			{
				libcsc::discount::OrderPositionDiscountPtr discount( *iter );
				if( 0 != discount->getPositionNo() )
				{
					continue;
				}

				recordtypes::RecordTypeDiscountPtr record( new recordtypes::RecordTypeDiscount( m_Logger ) );

				record->setBranchNo( orderheader->getOrder()->FilialNr() );
				record->setDiscountMode( static_cast<basar::Int32>( discount->getDiscountMode() ) );
				record->setOrderNo( discount->getOrderNo() );

				switch( discount->getDiscountMode() )
				{
					case libcsc::discount::DM_RETAIL:
					case libcsc::discount::DM_WHOLESALE_PERCENT_MODE:
					case libcsc::discount::DM_WHOLESALE_INDUSTRY_PERCENT_MODE:
					{
						record->setDiscount( discount->getDiscountPercent() );
						record->setOrderPosNo( 0 );
						getCollection()->addRecord( record );
						break;
					}

					case libcsc::discount::DM_FIXED_PRICE_MODE:
					{
						// nothing to do
						break;
					}

					case libcsc::discount::DM_UNSET:
					default:
					{
						// TODO HR-08 logging
						// TODO HR-08 throw new Exception UnknownDiscountMode
						break;
					}
				}
			}
		}

		// in der "alten" Rabattlogik gibt es keine Rabatte, die nicht zu einer Position gehören = keine Rabatte auf Kopfebene!
	}

	//----------------------------------------------------------------------------//
	recordtypes::RecordTypeDiscountPtr OrderTransformer::addOldDiscountRecord( pxVerbund::PXVBOrderItemPtr orderitem, libcsc::discount::OrderPositionDiscountMode discMode,
		basar::Decimal discountValue, basar::Int16 & discountCounter )
	{
		recordtypes::RecordTypeDiscountPtr record(createRecordTypeDiscount(orderitem));
		record->setDiscountMode( static_cast<basar::Int32>( discMode ) );
		record->setDiscount( discountValue );
		getCollection()->addRecord( record );
		++discountCounter;
		return record;
	}

	//----------------------------------------------------------------------------//
	void	OrderTransformer::addOldDiscountRecordsHR( pxVerbund::PXVBOrderItemPtr orderitem, recordtypes::RecordTypeOrderLinePtr recordItem )
	{
		/*	kdauftragposrab.discounttype				OrderPositionDiscountModeEnum

			CROATIA:
			NatraDefault                    = 1			DM_WHOLESALE_REBATE_IN_KIND_MODE = 5 / DM_WHOLESALE_INDUSTRY_REBATE_IN_KIND_MODE = 6
			ValuePercentage WholeSale       = 11		DM_WHOLESALE_PERCENT_MODE = 3
			ValuePercentage Retail          = 12		DM_RETAIL = 2
			ValuePercentage WholeSale Ind.  = 19		DM_WHOLESALE_INDUSTRY_PERCENT_MODE = 4
			special price (HR)              = 20		DM_FIXED_PRICE_MODE = 1
		*/

		basar::Int16 numberOfDiscountRecords = 0;

		// Fixpreis
		if ( pxConstants::mZero < orderitem->getOrderItem()->PreisEKGrossoNA() )
		{
			addOldDiscountRecord(orderitem, libcsc::discount::DM_FIXED_PRICE_MODE, basar::Decimal(orderitem->getOrderItem()->PreisEKGrossoNA()), numberOfDiscountRecords);
		}

		// Natra WholeSale
		if ( 0 < orderitem->getOrderItem()->MengeNatraGrossH() )
		{
			basar::Int32 rikQty;
			if (orderitem->getOrderItem()->MengeNatraGrossH() <= orderitem->getOrderItem()->MengeGeliefert())
				rikQty = static_cast<basar::Int32>(orderitem->getOrderItem()->MengeNatraGrossH());
			else
				rikQty = static_cast<basar::Int32>(orderitem->getOrderItem()->MengeGeliefert());

			addOldDiscountRecord(orderitem, libcsc::discount::DM_WHOLESALE_REBATE_IN_KIND_MODE, basar::Decimal(rikQty), numberOfDiscountRecords);
		}

		// Natra WholeSaleIndustry
		if ( 0 < orderitem->getOrderItem()->MengeNatraHerst() )
		{
			basar::Int32 rikQty;
			if (orderitem->getOrderItem()->MengeNatraHerst() <= orderitem->getOrderItem()->MengeGeliefert())
				rikQty = static_cast<basar::Int32>(orderitem->getOrderItem()->MengeNatraHerst());
			else
				rikQty = static_cast<basar::Int32>(orderitem->getOrderItem()->MengeGeliefert());

			addOldDiscountRecord(orderitem, libcsc::discount::DM_WHOLESALE_INDUSTRY_REBATE_IN_KIND_MODE, basar::Decimal(rikQty), numberOfDiscountRecords);
		}

		if( 0 != orderitem->getDiscountList().get() )
		{
			::pxItemDiscountListIter disciter(*orderitem->getDiscountList().get());
			::pxItemDiscount* disc = NULL;
			while ( (disc = (::pxItemDiscount*) ++disciter) != NULL )
			{
				// % WholeSale
				if ( ::BestBuy_ValuePctWholeSale == disc->DiscountType() )
				{
					addOldDiscountRecord(orderitem, libcsc::discount::DM_WHOLESALE_PERCENT_MODE, basar::Decimal( disc->DiscountValuePct()), numberOfDiscountRecords);
				}
				// % Retail
				else if ( ::BestBuy_ValuePctRetail == disc->DiscountType() )
				{
					addOldDiscountRecord(orderitem, libcsc::discount::DM_RETAIL, basar::Decimal( disc->DiscountValuePct()), numberOfDiscountRecords);
				}
				// % WholeSaleIndustry
				else if ( ::BestBuy_ValuePctWholeSaleInd == disc->DiscountType() )
				{
					addOldDiscountRecord(orderitem, libcsc::discount::DM_WHOLESALE_INDUSTRY_PERCENT_MODE, basar::Decimal( disc->DiscountValuePct()), numberOfDiscountRecords);
				}
			}
		}

		recordItem->setNumberOfDiscountRecords( numberOfDiscountRecords );
	}

	//----------------------------------------------------------------------------//
	void	OrderTransformer::addOldDiscountRecordsFR( pxVerbund::PXVBOrderItemPtr orderitem, recordtypes::RecordTypeOrderLinePtr recordItem )
	{
		/*	kdauftragposrab.discounttype				OrderPositionDiscountModeEnum

			FRANCE:
			NatraDefault                    = 1			DM_REBATE_IN_KIND_MODE = 7
			ValuePctCash					= 7			DM_PERCENT_MODE = 8
			ValuePctShort					= 8					"
			ValuePctGenerika				= 9					"
			ValuePctPartenariat				= 10				"
			ValuePctTena					= 13				"
			ValuePctPhoenixMagic			= 17				"
			ValuePctShortLine				= 22				"
			FixedPriceDefault               = 4			DM_FIXED_PRICE_MODE = 1
			FixedDiscountValue				= 23		DM_FIXED_DISCOUNT_VALUE_MODE = 9
		*/

		basar::Int16 numberOfDiscountRecords = 0;

		// Fixpreis aus discount
		if ( pxConstants::mZero < orderitem->getOrderItem()->PreisEKApoNetto() )
		{
			addOldDiscountRecord(orderitem, libcsc::discount::DM_FIXED_PRICE_MODE, basar::Decimal(orderitem->getOrderItem()->PreisEKApoNetto()), numberOfDiscountRecords);
		}
		// Fixpreis manuell eingegeben auf Pos-Level (größer oder kleiner AEP) - genutzt für Auftragsart "RL"
		else if (0 < orderitem->getOrderItem()->RabattFest())
		{
			addOldDiscountRecord(orderitem, libcsc::discount::DM_FIXED_PRICE_MODE, basar::Decimal(orderitem->getOrderItem()->RabattFest()), numberOfDiscountRecords);
		}

		// Natra
		if ( 0 < orderitem->getOrderItem()->MengeNatra() )
		{
			basar::Int32 rikQty;
			if (orderitem->getOrderItem()->MengeNatra() <= orderitem->getOrderItem()->MengeGeliefert())
				rikQty = static_cast<basar::Int32>(orderitem->getOrderItem()->MengeNatra());
			else
				rikQty = static_cast<basar::Int32>(orderitem->getOrderItem()->MengeGeliefert());

			addOldDiscountRecord(orderitem, libcsc::discount::DM_REBATE_IN_KIND_MODE, basar::Decimal(rikQty), numberOfDiscountRecords);
		}

		// fester Rabattwert
		if ( 0 < orderitem->getOrderItem()->RabattFest() )
		{
			addOldDiscountRecord(orderitem, libcsc::discount::DM_FIXED_DISCOUNT_VALUE_MODE, basar::Decimal(orderitem->getOrderItem()->RabattFest()), numberOfDiscountRecords);
		}

		// %- Rabatt --> paymenttargetno / surchargepct not handeled (but also not used in FR) - compared to OrderTransformer::getDiscountDetails
		if( 0 != orderitem->getDiscountList().get() )
		{
			::pxItemDiscountListIter disciter(*orderitem->getDiscountList().get());
			::pxItemDiscount* disc = NULL;
			double pct = 0.0;

			while ( (disc = (::pxItemDiscount*) ++disciter) != NULL )
			{
				if ( ::BestBuy_ValuePctCash			== disc->DiscountType() || // discountvalpctman findet sich auch immer in discountvaluepct !
					 ::BestBuy_ValuePctShort		== disc->DiscountType() ||
					 ::BestBuy_ValuePctGenerika		== disc->DiscountType() ||
					 ::BestBuy_ValuePctPartenariat	== disc->DiscountType() ||
					 ::BestBuy_ValuePctTena			== disc->DiscountType() ||
					 ::BestBuy_ValuePctPhoenixMagic	== disc->DiscountType() ||
					 ::BestBuy_ValuePctShortLine	== disc->DiscountType() )
				{
					if (disc->DiscountValuePct() > pct)
						pct = disc->DiscountValuePct(); // look for the best pct of these discount types, as only one pct-value is expected by invoicing (better than current logic: last -not best!-  pct-value is transferred, result = random)
				}
			}

			if (pct > 0.0)
				addOldDiscountRecord(orderitem, libcsc::discount::DM_PERCENT_MODE, basar::Decimal( pct ), numberOfDiscountRecords);
		}

		recordItem->setNumberOfDiscountRecords( numberOfDiscountRecords );
	}

	//----------------------------------------------------------------------------//

	const basar::Decimal OrderTransformer::getCashRebate( pxVerbund::PXVBOrderItemPtr orderitem, libcsc::discount::OrderPositionDiscountModeEnum mode )
	{
		basar::VarString txt = getArticleHint( orderitem );

		basar::Decimal rebate = basar::Decimal(0.0);
		basar::VarString type = "";
		basar::Int16 dcf = 0;
		basar::Int16 dat = 0;
		if (orderitem->getOrder()->Session()->isSwitzerland())
		{
			// for switzerland there are multiple values in the article hint
			if (transformArticleHint(txt, type, rebate, dcf, dat) == true)
			{
				if (("BR" == type && mode == libcsc::discount::DM_CASH_REBATE_MODE) ||
					("AR" == type && mode == libcsc::discount::DM_CASH_REBATE_AS_PRICE_MODE))
				{
					return rebate;
				}
			}
		}
		else
		{
			// standard behavior of all other countries
            if( ( "BR" == txt.substr( 0, 2 ) && mode == libcsc::discount::DM_CASH_REBATE_MODE ) ||
                ( "AR" == txt.substr( 0, 2 ) && mode == libcsc::discount::DM_CASH_REBATE_AS_PRICE_MODE ) )
            {
				basar::VarString sRebate(txt.substr(2, txt.length() - 2));
				sRebate.exchange(";", ".");
				sRebate.exchange(",", ".");
				try
				{
					basar::Decimal rebate(sRebate.stof());
					return rebate;
				}
				catch (...)
				{
				}
			}
		}
		return basar::Decimal(0.0);
	}

	basar::Int16 OrderTransformer::getCashRebateCalcFromFlag(pxVerbund::PXVBOrderItemPtr orderitem)
	{
		basar::VarString txt = getArticleHint(orderitem);

		basar::Decimal rebate = basar::Decimal(0.0);
		basar::VarString type = "";
		basar::Int16 dcf = basar::Int16(0);
		basar::Int16 dat = basar::Int16(0);
		if (transformArticleHint(txt, type, rebate, dcf, dat) == true)
		{
			return dcf;
		}
		return basar::Int16(0);
	}

	basar::Int16 OrderTransformer::getCashRebateApplyToFlag(pxVerbund::PXVBOrderItemPtr orderitem)
	{
		basar::VarString txt = getArticleHint(orderitem);

		basar::Decimal rebate = basar::Decimal(0.0);
		basar::VarString type = "";
		basar::Int16 dcf = basar::Int16(0);
		basar::Int16 dat = basar::Int16(0);
		if (transformArticleHint(txt, type, rebate, dcf, dat) == true)
		{
			return dat;
		}
		return basar::Int16(0);
	}

	bool OrderTransformer::transformArticleHint(basar::VarString hintText, basar::VarString& hintType, basar::Decimal& discountVal, basar::Int16& discountCalcFrom, basar::Int16& discountApplyTo)
	{
		// split the comment/hint field from each order item e.g. BR54;00
		// it contains
		//   2 fixed chars = type of hint (e.g. discount "BR" = cash discount percentage or discount "AR" = cash discount price)
		// rest are values delimited with ; (sometimes discount decimals are delimited with ,)
		//   value of discount 
		//   decimals of discount
		//   discount calc from flag (for CH only)
		//   discount apply to flag (for CH only)
		//   H flag (for AT only)
		bool ret = true;

		// set defaults for the values
		hintType = "";
		discountVal = basar::Decimal(0.0);
		discountCalcFrom = 0;
		discountApplyTo = 1;

		if (hintText.empty() == true)
		{
			return ret;
		}

		basar::VarString data(hintText);
		if (data.length() > 1)
		{
			hintType = data.substr(0, 2);
			// if hint type is a rebate
			if (("BR" == hintType) || ("AR" == hintType))
			{
				data = data.substr(2, data.length() - 2);
				// scan for discount value and discount flags
				basar::VarString sDiscount = "";
				// scan for delimiter
				size_t pos = data.find(",");
				if (pos == std::string::npos)
				{
					pos = data.find(";");
				}
				if (pos != data.npos)
				{
					// delimiter found, take over the value as rebate
					sDiscount = data.substr(0, pos);
					data = data.substr(pos + 1);
					// scan for next delimiter
					pos = data.find(";");
					if (pos != data.npos)
					{
						// delimiter found, take over the value as rebate decimals
						sDiscount += "." + data.substr(0, pos);
						data = data.substr(pos + 1);
						// scan for next delimiter
						pos = data.find(";");
						if (pos != data.npos)
						{
							// delimiter found, take over the value as discount(calcfrom) flag
							if (data.substr(0, pos) == "1")
							{
								discountCalcFrom = 1;
							}
							data = data.substr(pos + 1);
							// scan for next delimieter
							pos = data.find(";");
							if (pos != data.npos)
							{
								// delimiter found, take over the value as discount(applyto) flag
								if (data.substr(0, pos) == "0")
								{
									discountApplyTo = 0;
								}
								data = data.substr(pos + 1);
							}
							else
							{
								//take over the value as discount(applyto) flag
								if (data.substr(0, pos) == "0")
								{
									discountApplyTo = 0;
								}
							}
						}
						else
						{
							// take over the value as discount(calcfrom) flag
							if (data.substr(0, pos) == "1")
							{
								discountCalcFrom = 1;
							}
						}
					}
					else
					{
						// take over the value as rebate decimals
						sDiscount += "." + data;
					}
				}
				else
				{
					// take over the value as rebate
					sDiscount = data;
				}
				try
				{
					discountVal = basar::Decimal(sDiscount.stof());
				}
				catch (...)
				{
				}
			}
		}
		return ret;
	}
	//----------------------------------------------------------------------------//

	const basar::Decimal OrderTransformer::taxSpannenCheckGermany(pxVerbund::PXVBOrderItemPtr orderitem, const basar::Decimal& discountPct)
	{
		if (false == orderitem->getOrderItem()->Session()->isGermany())
		{
			return discountPct;
		}

		if (false == orderitem->getOrderItem()->ArtBase()->ArtClass().IsRezeptPflichtig() ||
			false == orderitem->getOrderItem()->ArtBase()->IsTaxPflichtigRX())
		{
			return discountPct;
		}

		// Taxspannenfestbetrag bestimmen
		static bool isInitialized = false;
		static basar::Decimal s_TaxSpannenFestBetrag = basar::Decimal(0.7);

		if (false == isInitialized)
		{
			pxParameter parameter(orderitem->getOrderItem()->Session(), 0, 
				cPAR_GROUP_ORDERENTRY, cPAR_PURPOSE_TAXSPANNE, cPAR_PARAM_FIXZUSCHLAG);
			if (parameter.Get() == 0)
			{
				s_TaxSpannenFestBetrag = basar::Decimal(parameter.Wert() / 100.0);
			}
			isInitialized = true;
		}
		// Taxspannenfestbetrag bestimmen


		// AEP - x%
		basar::Decimal aep = basar::Decimal(orderitem->getOrderItem()->ArtPriceList()->GetPreisEKApo());
		basar::Decimal discountedPrice = aep * (basar::Decimal(1.0) - discountPct / (basar::Decimal(100)));
		basar::Decimal minimumPrice = basar::Decimal(orderitem->getOrderItem()->ArtPriceList()->GetPreisEKGrosso() + s_TaxSpannenFestBetrag);

		if (minimumPrice >= aep)
		{
			return basar::Decimal();
		}

		if (discountedPrice < minimumPrice)
		{
			basar::Decimal minPricePct = (aep - minimumPrice) / aep * 100;
			return minPricePct;
		}
		return discountPct;
	}

	//----------------------------------------------------------------------------//
	void OrderTransformer::addOldDiscountRecordsCH( pxVerbund::PXVBOrderItemPtr orderitem, recordtypes::RecordTypeOrderLinePtr recordItem )
	{
		basar::Int16 numberOfDiscountRecords = 0;
		basar::VarString logmsg("");

		// GEP vs. AGP
		// CPR-200670: Take AGP value from kdauftragpos if not 0.0 otherwise from artikelpreis	    
		basar::Decimal agp;

		logmsg.format("   preparing discounts for orderno=%d, pos=%d, pzn=%d", orderitem->getOrder()->KdAuftragNr(), orderitem->getOrderItem()->PosNr(), orderitem->getOrderItem()->ArtikelNr());
		m_Logger->log(log4cplus::INFO_LOG_LEVEL, logmsg);

		// Takes value from kdauftragpos
		basar::Decimal agpkdauftragpos(orderitem->getOrderItem()->PreisAGP());
		if (agpkdauftragpos > basar::Decimal(0.0))
		{
			agp = agpkdauftragpos;
		}
		else
		{
			// Takes value from artikelpreis
			basar::Decimal agpartikelpreis(orderitem->getOrderItem()->ArtPriceList()->GetPreisAGP());
			agp = agpartikelpreis;
		}
		if (agp > basar::Decimal(0.0))
		{
			basar::Decimal gep(orderitem->getOrderItem()->PreisEKGrosso());
			logmsg.format("   -> AGP found for CH for this position with gep=%0.2f and agp=%0.2lf", gep.toFloat64(), agp.toFloat64());
			m_Logger->log(log4cplus::INFO_LOG_LEVEL, logmsg);

			recordtypes::RecordTypeDiscountPtr dkpraRecord = addOldDiscountRecord(orderitem, libcsc::discount::DM_ABP_BASEPRICE_MODE, agp, numberOfDiscountRecords);
			dkpraRecord->setInternalRebate(1);
			dkpraRecord->setDiscountBase(static_cast<basar::Int16>(DiscCategory_Common));
			dkpraRecord->setRefundPercent(basar::Decimal(0.0));
			dkpraRecord->setPharmacyGroup(basar::VarString(""));
			logmsg.format("   -> added as %d. discount base price (record type=%d) with agp=%0.2lf", numberOfDiscountRecords, libcsc::discount::DM_ABP_BASEPRICE_MODE, agp.toFloat64());
			m_Logger->log(log4cplus::INFO_LOG_LEVEL, logmsg);
		}

		// Natra
		if( 0 < orderitem->getOrderItem()->MengeNatra() )
		{
			basar::Int32 rikQty;
			if (orderitem->getOrderItem()->MengeNatra() <= orderitem->getOrderItem()->MengeGeliefert())
			{
				rikQty = static_cast<basar::Int32>(orderitem->getOrderItem()->MengeNatra());
			}
			else
			{
				rikQty = static_cast<basar::Int32>(orderitem->getOrderItem()->MengeGeliefert());
			}
			logmsg.format("   -> discount type natra found with qty=%d", rikQty);
			m_Logger->log(log4cplus::INFO_LOG_LEVEL, logmsg);

			recordtypes::RecordTypeDiscountPtr dkpraRecord = addOldDiscountRecord( orderitem, libcsc::discount::DM_REBATE_IN_KIND_MODE, basar::Decimal(rikQty), numberOfDiscountRecords );
			pxItemDiscount* disc = orderitem->getDiscountList().get()->Find(::BestBuy_NatraDefault);
			if (NULL != disc)
			{
				dkpraRecord->setInternalRebate(disc->InternalDiscountFlag());
				dkpraRecord->setDiscountBase(static_cast<basar::Int16>(disc->DiscountCategory()));
				dkpraRecord->setRefundPercent(basar::Decimal(disc->RefundValuePct()));
				dkpraRecord->setPharmacyGroup(disc->PharmacyGroupId()());
				dkpraRecord->setDiscountCalcFrom(0);
				dkpraRecord->setDiscountApplyTo(1);
				dkpraRecord->setDiscountSortBase(0);
			}
			else
			{
				dkpraRecord->setInternalRebate(orderitem->getOrderItem()->IsNaturalRabattIntern() ? 1 : 0);
				dkpraRecord->setDiscountBase(static_cast<basar::Int16>(orderitem->getOrderItem()->NatraCategory()));
				dkpraRecord->setRefundPercent(basar::Decimal(0.0));
				dkpraRecord->setPharmacyGroup(orderitem->getOrderItem()->NatraPharmacyGroup()());
				dkpraRecord->setDiscountCalcFrom(0);
				dkpraRecord->setDiscountApplyTo(1);
				dkpraRecord->setDiscountSortBase(0);
			}
			logmsg.format("   -> added as %d. discount type natra(record type=%d)", numberOfDiscountRecords, libcsc::discount::DM_REBATE_IN_KIND_MODE);
			m_Logger->log(log4cplus::INFO_LOG_LEVEL, logmsg);

		}

		// cash rebate, bemerkungen == "BR12;34" == UW
		basar::Decimal cashRebate( getCashRebate( orderitem, libcsc::discount::DM_CASH_REBATE_MODE ) );
		if( basar::Decimal() <  cashRebate )
		{
			basar::VarString hint = getArticleHint(orderitem);
			basar::Int16 dcf = getCashRebateCalcFromFlag(orderitem);
			basar::Int16 dat = getCashRebateApplyToFlag(orderitem);
			logmsg.format("   -> discount manual cashRebate(%s) found with cashRebate=%0.2lf and DFC=%d and DAT=%d", hint.c_str(), cashRebate.toFloat64(), dcf, dat);
			m_Logger->log(log4cplus::INFO_LOG_LEVEL, logmsg);

			recordtypes::RecordTypeDiscountPtr dkpraRecord = addOldDiscountRecord( orderitem, libcsc::discount::DM_CASH_REBATE_MODE, cashRebate, numberOfDiscountRecords );
			dkpraRecord->setInternalRebate(0);
			dkpraRecord->setDiscountBase(static_cast<basar::Int16>(DiscCategory_Manual));  // 3 = MANUELL ERFASST
			dkpraRecord->setRefundPercent(basar::Decimal(0.0));
			dkpraRecord->setPharmacyGroup(basar::VarString(""));
			dkpraRecord->setDiscountCalcFrom(dcf);
			dkpraRecord->setDiscountApplyTo(dat);
			dkpraRecord->setDiscountSortBase(0);
			logmsg.format("   -> added as %d. discount type manual cashRebate (record type=%d)", numberOfDiscountRecords, libcsc::discount::DM_CASH_REBATE_MODE);
			m_Logger->log(log4cplus::INFO_LOG_LEVEL, logmsg);
		}

		if( 0 != orderitem->getDiscountList().get() )
		{
			::pxItemDiscountListIter disciter(*orderitem->getDiscountList().get());
			::pxItemDiscount* disc = NULL;
			double pct = 0.0;
			while ( (disc = (::pxItemDiscount*) ++disciter) != NULL )
			{
				bool sortbase = 0;
				if (::BestBuy_ValuePctCashAssorted == disc->DiscountType())
				{
					// assorted cash discount flag covered in discount type
					sortbase = 1;
				}
				logmsg.format("   -> discount type (=%d) found with value internaldiscount=%d, discountcat=%d, surchargepct=%0.2f, refundpct=%0.2lf, pharmacygrp=%s, pct=%0.2lf, discountcalcfrom=%d, discountapplyto=%d, discountsortbase=%d", disc->DiscountType(), disc->InternalDiscountFlag(), (short)disc->DiscountCategory(), disc->SurchargePct(), disc->RefundValuePct(), disc->PharmacyGroupId()(), disc->DiscountValuePct(), disc->DiscountCalcFrom(), disc->DiscountApplyTo(), sortbase);
				m_Logger->log(log4cplus::INFO_LOG_LEVEL, logmsg);

				if ( ::BestBuy_ValuePctOMG == disc->DiscountType() )
				{
					if( disc->DiscountValuePct() > 0.0 )
					{
						recordtypes::RecordTypeDiscountPtr dkpraRecord = addOldDiscountRecord( orderitem, libcsc::discount::DM_OMG_REBATE_MODE, basar::Decimal( disc->DiscountValuePct() ), numberOfDiscountRecords );
						dkpraRecord->setInternalRebate(disc->InternalDiscountFlag());
						dkpraRecord->setDiscountBase(static_cast<basar::Int16>(disc->DiscountCategory()));
						dkpraRecord->setRefundPercent(basar::Decimal(disc->RefundValuePct()));
						dkpraRecord->setPharmacyGroup(disc->PharmacyGroupId()());
						dkpraRecord->setDiscountCalcFrom(disc->DiscountCalcFrom());
						dkpraRecord->setDiscountApplyTo(disc->DiscountApplyTo());

						logmsg.format("   -> added as %d. discount type OMG(record type=%d)", numberOfDiscountRecords, libcsc::discount::DM_OMG_REBATE_MODE);
						m_Logger->log(log4cplus::INFO_LOG_LEVEL, logmsg);
					}
				}
				else if(	::BestBuy_ValuePctCash			== disc->DiscountType()
						 || ::BestBuy_ValuePctPartenariat	== disc->DiscountType()
						 || ::BestBuy_ValuePctTena			== disc->DiscountType()
						 || ::BestBuy_ValuePctShortLine		== disc->DiscountType()
						 || ::BestBuy_ValuePctCashAssorted  == disc->DiscountType())
				{
					pct = disc->DiscountValuePct();
					if( 0 < pct )
					{
						recordtypes::RecordTypeDiscountPtr dkpraRecord = addOldDiscountRecord( orderitem, libcsc::discount::DM_PERCENT_MODE, basar::Decimal( pct ), numberOfDiscountRecords );
						dkpraRecord->setInternalRebate(disc->InternalDiscountFlag());
						dkpraRecord->setDiscountBase(static_cast<basar::Int16>(disc->DiscountCategory()));
						dkpraRecord->setRefundPercent(basar::Decimal(disc->RefundValuePct()));
						dkpraRecord->setPharmacyGroup(disc->PharmacyGroupId()());
						dkpraRecord->setDiscountCalcFrom(disc->DiscountCalcFrom());
						dkpraRecord->setDiscountApplyTo(disc->DiscountApplyTo());
						dkpraRecord->setDiscountSortBase(sortbase);

						logmsg.format("   -> added as %d. discount type percentage (record type=%d)", numberOfDiscountRecords, libcsc::discount::DM_PERCENT_MODE);
						m_Logger->log(log4cplus::INFO_LOG_LEVEL, logmsg);
					}
				}
				else if( ::BestBuy_LogisticAddition == disc->DiscountType() )
				{
					pct = disc->DiscountValuePct();
					recordtypes::RecordTypeDiscountPtr dkpraRecord = addOldDiscountRecord( orderitem, libcsc::discount::DM_FIX_LOGISTIC_SURCHARGE_MODE, basar::Decimal( pct ), numberOfDiscountRecords );
					dkpraRecord->setInternalRebate(disc->InternalDiscountFlag());
					dkpraRecord->setDiscountBase(static_cast<basar::Int16>(disc->DiscountCategory()));
					dkpraRecord->setRefundPercent(basar::Decimal(disc->RefundValuePct()));
					dkpraRecord->setPharmacyGroup(disc->PharmacyGroupId()());
					dkpraRecord->setDiscountCalcFrom(disc->DiscountCalcFrom());
					dkpraRecord->setDiscountApplyTo(disc->DiscountApplyTo());

					logmsg.format("   -> added as %d. discount type surcharge logistics (record type=%d)", numberOfDiscountRecords, libcsc::discount::DM_FIX_LOGISTIC_SURCHARGE_MODE);
					m_Logger->log(log4cplus::INFO_LOG_LEVEL, logmsg);
				}
				else if (::BestBuy_LogisticDataTransfer == disc->DiscountType())
				{
					//pct = disc->DiscountValuePct(); not used for this logistics addition, as this will be calculated by Sales/Factura, so will be set to 0
					recordtypes::RecordTypeDiscountPtr dkpraRecord = addOldDiscountRecord(orderitem, libcsc::discount::DM_LOGISTIC_DATATRANSFER_MODE, basar::Decimal(0), numberOfDiscountRecords);
					dkpraRecord->setDiscountBase(basar::Int16(0));
					dkpraRecord->setRefundPercent(basar::Decimal(disc->RefundValuePct()));
					dkpraRecord->setPharmacyGroup(disc->PharmacyGroupId()());
					dkpraRecord->setInternalRebate(basar::Int16(0));
					dkpraRecord->setDiscountCalcFrom(disc->DiscountCalcFrom());
					dkpraRecord->setDiscountApplyTo(disc->DiscountApplyTo());

					logmsg.format("   -> added as %d. discount type datatransfer logistics (record type=%d)", numberOfDiscountRecords, libcsc::discount::DM_LOGISTIC_DATATRANSFER_MODE);
					m_Logger->log(log4cplus::INFO_LOG_LEVEL, logmsg);
				}
			}
		}

		logmsg.format("   sum of %d discounts will be send for order=%d, pos=%d, pzn=%d", numberOfDiscountRecords, orderitem->getOrder()->KdAuftragNr(), orderitem->getOrderItem()->PosNr(), orderitem->getOrderItem()->ArtikelNr());
		m_Logger->log(log4cplus::INFO_LOG_LEVEL, logmsg);

		recordItem->setNumberOfDiscountRecords( numberOfDiscountRecords );
	}

	//----------------------------------------------------------------------------//
	void OrderTransformer::addOldDiscountRecords( pxVerbund::PXVBOrderItemPtr orderitem, recordtypes::RecordTypeOrderLinePtr recordItem )
	{
		if(		!orderitem->getOrder()->Session()->isCroatia()
			&&	!orderitem->getOrder()->Session()->isFrance()
			&&	!orderitem->getOrder()->Session()->isSwitzerland() )
		{
			return;
		}

		// Versorgung DKPRA aus "alten" Rabattwerten

		basar::Int32 goodsTrafficQty = orderitem->getOrderItem()->MengeGeliefert();
		goodsTrafficQty += orderitem->getOrderItem()->MengeVerbund();
		goodsTrafficQty += orderitem->getOrderItem()->MengeNachgeliefert();

		if( 0 < goodsTrafficQty )
		{
			if( orderitem->getOrder()->Session()->isCroatia() )
			{
				addOldDiscountRecordsHR( orderitem, recordItem );
			}
			else if( orderitem->getOrder()->Session()->isFrance() )
			{
				addOldDiscountRecordsFR( orderitem, recordItem );
			}
			else if( orderitem->getOrder()->Session()->isSwitzerland() )
			{
				addOldDiscountRecordsCH( orderitem, recordItem );
			}
		}
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::addDiscountRecords( pxVerbund::PXVBOrderItemPtr orderitem, recordtypes::RecordTypeOrderLinePtr recordItem )
	{
		if (orderitem->getOrder()->Param()->IsUseNewDiscountCalc())
		{
			basar::Int16 numberOfDiscountRecords = 0;

			// HR-08 -> add recordtypes RecordTypeDiscount for each discount record of the current order item
			libcsc::discount::OrderPositionDiscountList::const_iterator iter = orderitem->getNewDiscountList()->begin();
			for( ; iter != orderitem->getNewDiscountList()->end(); ++iter )
			{
				libcsc::discount::OrderPositionDiscountPtr discount( *iter );
				recordtypes::RecordTypeDiscountPtr record( new recordtypes::RecordTypeDiscount( m_Logger ) );

				record->setBranchNo( orderitem->getOrder()->FilialNr() );
				record->setDiscountMode( static_cast<basar::Int32>( discount->getDiscountMode() ) );
				record->setOrderNo( discount->getOrderNo() );
				record->setPharmacyGroup(discount->getPharmacyGroupId());

				switch( discount->getDiscountMode() )
				{
					case libcsc::discount::DM_FIXED_PRICE_MODE:
					case libcsc::discount::DM_FIXED_PRICE_CONCEPT_DEAP_MODE: // DEPricing
					case libcsc::discount::DM_FIXED_PRICE_CONCEPT_MVDA_MODE: // DEPricing
					{
						record->setDiscount( discount->getDiscountValue() );
						record->setOrderPosNo( discount->getPositionNo() );
						getCollection()->addRecord( record );
						++numberOfDiscountRecords;
						break;
					}

					case libcsc::discount::DM_RETAIL:
					case libcsc::discount::DM_WHOLESALE_PERCENT_MODE:
					case libcsc::discount::DM_WHOLESALE_INDUSTRY_PERCENT_MODE:
					case libcsc::discount::DM_SURCHARGE_EXF_MODE: // DEPricing
					{
						record->setDiscount( discount->getDiscountPercent() );
						record->setOrderPosNo( discount->getPositionNo() );
						getCollection()->addRecord( record );
						++numberOfDiscountRecords;
						break;
					}

					case libcsc::discount::DM_UNSET:
					default:
					{
						// TODO HR-08 logging
						// TODO HR-08 throw new Exception UnknownDiscountMode
						break;
					}
				}
			}

			libcsc::discount::IOrderPositionDiscountRepositoryPtr repo = orderitem->getOrderItem()->Session()->getOrderPositionDiscountRepository();
			libcsc::discount::OrderPositionDiscountListPtr discounts = repo->findByIDBackward(orderitem->getOrderItem()->KdAuftragNr(), orderitem->getOrderItem()->PosNr());
			iter = discounts->begin();
			if (iter != discounts->end())
			{
				libcsc::discount::OrderPositionDiscountPtr discount = (*iter);

				switch (discount->getDiscountMode())
				{
					case libcsc::discount::DM_WHOLESALE_REBATE_IN_KIND_MODE:
					case libcsc::discount::DM_WHOLESALE_INDUSTRY_REBATE_IN_KIND_MODE:
					{
						recordtypes::RecordTypeDiscountPtr record(new recordtypes::RecordTypeDiscount(m_Logger));
						record->setBranchNo(orderitem->getOrder()->FilialNr());
						record->setDiscountMode(static_cast<basar::Int32>(discount->getDiscountMode()));
						record->setOrderNo(discount->getRebateInKindOrderNo());
						record->setOrderPosNo(discount->getRebateInKindPositionNo());
						record->setDiscount(basar::Decimal(discount->getDiscountQty()));
						getCollection()->addRecord(record);
						++numberOfDiscountRecords;
						break;
					}
					default: 
						break;
				}
//				++iter;
			}

			// DEPricing TODO BR12;34 AR12;34 kann man sicher besser implementieren!
			if (orderitem->getOrderItem()->Session()->isGermany())
			{
				// auf Auftragsarten abprüfen  Faktur-Code: IF(A1AART = 'AK' OR = 'UW' OR = 'MD' OR = 'SG' OR = 'UN' OR = 'AC' OR = 'HZ')
				if (orderitem->getOrder()->KdAuftragArt() == "AK" || orderitem->getOrder()->KdAuftragArt() == "UW" ||
					orderitem->getOrder()->KdAuftragArt() == "HZ" || orderitem->getOrder()->KdAuftragArt() == "MD" || 
					orderitem->getOrder()->KdAuftragArt() == "GM")
				{
					// cash rebate, bemerkungen == "BR12;34" --> UW
					basar::Decimal cashRebate(getCashRebate(orderitem, libcsc::discount::DM_CASH_REBATE_MODE));
					cashRebate = taxSpannenCheckGermany(orderitem, cashRebate); // DEPricing Taxspannencheck durchführen (10.00% -> 9.53%)

					if (basar::Decimal() < cashRebate)
					{
						recordtypes::RecordTypeDiscountPtr dkpraRecord(createRecordTypeDiscount(orderitem));
						dkpraRecord->setDiscountMode(static_cast<basar::Int32>(libcsc::discount::DM_CASH_REBATE_MODE));
						dkpraRecord->setDiscount(cashRebate);
						dkpraRecord->setInternalRebate(0);
						dkpraRecord->setDiscountBase(static_cast<basar::Int16>(DiscCategory_Manual));  // 3 = MANUELL ERFASST
						dkpraRecord->setRefundPercent(basar::Decimal(0.0));
						dkpraRecord->setPharmacyGroup(basar::VarString(""));
						getCollection()->addRecord(dkpraRecord);
						++numberOfDiscountRecords;
					}

					// cash rebate as fixed price, bemerkungen == "AR12;34" --> AK, HZ
					basar::Decimal cashRebateAsPrice(getCashRebate(orderitem, libcsc::discount::DM_CASH_REBATE_AS_PRICE_MODE));
					cashRebateAsPrice = taxSpannenCheckGermany(orderitem, cashRebateAsPrice); // DEPricing Taxspannencheck durchführen (10.00% -> 9.53%)
					if (basar::Decimal() < cashRebateAsPrice)
					{
						recordtypes::RecordTypeDiscountPtr dkpraRecord(createRecordTypeDiscount(orderitem));
						dkpraRecord->setDiscountMode(static_cast<basar::Int32>(libcsc::discount::DM_CASH_REBATE_AS_PRICE_MODE));
						dkpraRecord->setDiscount(cashRebateAsPrice);
						dkpraRecord->setInternalRebate(0);
						dkpraRecord->setDiscountBase(static_cast<basar::Int16>(DiscCategory_Manual));  // 3 = MANUELL ERFASST
						dkpraRecord->setRefundPercent(basar::Decimal(0.0));
						dkpraRecord->setPharmacyGroup(basar::VarString(""));
						getCollection()->addRecord(dkpraRecord);
						++numberOfDiscountRecords;
					}
				}
			}

			recordItem->setNumberOfDiscountRecords(numberOfDiscountRecords);
		}
		else
			addOldDiscountRecords(orderitem, recordItem);
	}

	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	recordtypes::RecordTypeDiscountPtr	OrderTransformer::createRecordTypeDiscount( pxVerbund::PXVBOrderItemPtr orderitem )
	{
		recordtypes::RecordTypeDiscountPtr record( new recordtypes::RecordTypeDiscount( m_Logger ) );
		record->setBranchNo( orderitem->getOrder()->FilialNr() );
		record->setOrderNo( orderitem->getOrder()->KdAuftragNr() );
		record->setOrderPosNo( orderitem->getOrderItem()->PosNr() );

		return record;
	}

	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::addMSV3PackageLabelItemInfo( pxVerbund::PXVBOrderItemPtr item, recordtypes::RecordTypeOrderLinePtr record, pxVerbund::PXVBOrderDMPtr order )
	{
		METHODNAME_DEF( OrderTransformer, addMSV3PackageLabelInfo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		if( item->isMSV3Item() )
		{
			basar::VarString xmlorderref;

			pxGenericOrderRemarkList remarklist(item->getOrderItem()->Session());
			remarklist.SelectOrderRemarksByOrderLineAndType(item->getOrderItem()->KdAuftragNr(), item->getOrderItem()->PosNr(), eOrderReferenceXML);
			if (remarklist.Entries() > 0)
			{
				pxGenericOrderRemarkListIter iter = ::pxGenericOrderRemarkListIter(remarklist);
				pxGenericOrderRemark* remark;
				if (NULL != (remark = (pxGenericOrderRemark*)++iter))
				{
					xmlorderref = remark->RemarkText();
				}
			}

			if( "" != xmlorderref  )
			{
				basar::Int32 packagelabelid = order->m_PackageLabelCollection.addPackageLabel( xmlorderref );
				basar::VarString labelid("");
				labelid.format( "%09d", packagelabelid );
				record->setXMLReference( labelid );
			}
			else
			{
				basar::VarString labelid("000000000");
				record->setXMLReference( labelid );
			}
		}
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	bool OrderTransformer::isSetInvoicePrice(const int /*branchno*/) const
	{
		/* 2014-01-24 Heinlein: CACIC
		if( 48 == branchno || 43 == branchno ) // do not set FAP for prewholesale france
		{
			return false;
		}
		*/
		return true;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::setStdItemValues( pxVerbund::PXVBOrderItemPtr item, recordtypes::RecordTypeOrderLinePtr record )
	{
		METHODNAME_DEF( OrderTransformer, setStdItemValues );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		unsigned long itemFlags[7];
		item->getOrderItem()->ItemFlags().Export(itemFlags, 7, 2);
		record->setET1Flags( itemFlags[0] );
		record->setET2Flags( itemFlags[1] );
		record->setET3Flags( itemFlags[2] );
		record->setET4Flags( itemFlags[3] );
		record->setET5Flags( itemFlags[4] );
		record->setET6Flags( itemFlags[5] );
		record->setET7Flags( itemFlags[6] );

		unsigned long articleFlags[6];
		item->getOrderItem()->ItemArtFlags().Export(articleFlags, 6, 2);
		record->setArtET2( articleFlags[1] );

		if( isSetInvoicePrice(item->getOrder()->FilialNr()) )
		{
			basar::Decimal preisFaktur( item->getOrderItem()->PreisFaktur() );
			record->setInvoicePrice( preisFaktur );
		}

		record->setLineNo( static_cast< long int >( item->getOrderItem()->PosNr() ) );
		record->setArticleNo( item->getOrderItem()->ArtikelNr() );
		record->setLineType( static_cast< int >( item->getOrderItem()->PosTyp() ) );
		record->setDeviceType( static_cast< int >( item->getOrderItem()->GeraetTyp() ) );
		record->setQState( static_cast< int >( item->getOrderItem()->QState() ) );
		record->setArticleState( static_cast< int >( item->getOrderItem()->ArtState() ) );
		record->setOrderQty( item->getOrderItem()->MengeBestellt() );
		basar::Decimal preisVKApo( item->getOrderItem()->PreisVKApo() );
		record->setPharmacySellPrice( preisVKApo );
		basar::Decimal preisEKApoNetto( item->getOrderItem()->PreisEKApoNetto() );
		record->setNetPrice( preisEKApoNetto );
		basar::Decimal preisEKGrossNA( item->getOrderItem()->PreisEKGrossoNA() );
		record->setNetCostPrice( preisEKGrossNA );
		record->setPreDeliveryQty( item->getOrderItem()->MengeVorausBezug() );
		record->setXMLReference( basar::VarString( item->getOrderItem()->KdAuftragBestellNr() ) );
		record->setCodeBlocage( basar::VarString( item->getOrderItem()->CodeBlocage() ) );
		record->setPriceType( static_cast< int >( item->getOrderItem()->PreisTyp() ) );
		record->setArticleCode( basar::VarString( item->getOrderItem()->ArticleCode() ) );
		record->setCodeType( item->getOrderItem()->CodeType() );
		record->setBusinessType( item->getOrderItem()->BusinessTypeNo() );
		record->setTourIdIbt( basar::VarString(item->getOrderItem()->TourIdIBT()) );
		record->setSubDeviceType( item->getOrderItem()->SubGeraetTyp() );
		record->setIBTWeekday( item->getOrderItem()->IBTTourWeekDay() );
		record->setPurchaseRelevantQuantity( item->getOrderItem()->GetPurchaseRelevantQty() );
		record->setOriginalOrderedQuantity( item->getOrderItem()->MengeBestelltOrg() );
		record->setIBTDeliveryDate( static_cast<long int>( item->getOrderItem()->getIBTCustomerDeliveryDate() ) );
		record->setPromotionNo(item->getOrderItem()->PromotionNo());
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::setDispoItemValues( pxVerbund::PXVBOrderItemPtr item, recordtypes::RecordTypeOrderLinePtr record )
	{
		METHODNAME_DEF( OrderTransformer, setDispoItemValues );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		::tDISPOITEM dispoitem;
		item->getOrderItem()->DispoGet( dispoitem );

		char Rabattfaehig[2+1] = "00";
		Rabattfaehig[1] = ( dispoitem.Rabattfaehig) ? '1' : '0';

		char cTaxLevel = '0';
		if (item->getOrderItem()->ArtDispo() )
		{
			cTaxLevel = item->getOrderItem()->ArtDispo()->TaxLevel() + '0';
		}

        if (item->getOrderItem()->Session()->isBulgaria())
		{
			basar::Decimal netPrice( dispoitem.NetPrice );
			record->setPharmacyPurchasePrice( netPrice );
		}
		else
		{
			basar::Decimal preisEKApo( dispoitem.PreisEKApo );
			record->setPharmacyPurchasePrice( preisEKApo );
		}

		record->setDispensingForm( dispoitem.Darreichform() );
		record->setUnit( dispoitem.Einheit() );
		record->setArticleName( dispoitem.Bezeichnung() );
		record->setDiscountable( atoi( static_cast< char* >( Rabattfaehig ) ) );
		record->setCommodityGroup( dispoitem.WarenGruppeEigen() );
		basar::Decimal preisEKGrosso( dispoitem.PreisEKGrosso );
		record->setCostPrice( preisEKGrosso );
		basar::Decimal rabattFestDM( dispoitem.RabattFestDM );
		record->setDiscountValue( rabattFestDM );
		basar::Decimal rabattFest( /*dispoitem.RabattFest*/ 0 ); // since 09/2016, rabattfest is used to store discount.fixeddicountvalue for FR shortliner --> must NOT be transferred to FERA !
		record->setFixedDiscount( rabattFest );
		basar::VarString data = item->getOrderItem()->Bemerkungen()();
		record->setHints( StringTransformer::transform( data ) );
		record->setChangeDiscountType( basar::VarString( "0" ) );
		record->setTaxLevel( &cTaxLevel );
		record->setContLevel( "0" );
		record->setServiceNo( dispoitem.Service_No );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void OrderTransformer::setNormalOrderItemValues( pxVerbund::PXVBOrderItemPtr item, recordtypes::RecordTypeOrderLinePtr record )
	{
		METHODNAME_DEF( OrderTransformer, setNormalOrderItemValues );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		OrderTransformer::DiscountDetails discdetails = getDiscountDetails( item );

		::nString ChargenNr = " ";
		ChargenNr = item->getOrderItem()->GetChargenNr().c_str();
		ChargenNr.Replace( '/', '$' );
		record->setDesiredBatch( basar::VarString( ChargenNr ) );

        if (item->getOrderItem()->IsFixBatch())
        {
            record->setFixBatch(true);
        }

		if( item->getOrderItem()->IsAuxPosted() || item->getOrderItem()->IsDayNightMergePosition())
		{
			record->setIBTQty( item->getOrderItem()->MengeVerbund() );
			record->setIBTBranchNo( item->getOrderItem()->VerbundFilialNr() );
			record->setIBTBranchNo2( 0 );
			record->setIBTOriginCustomerNo( item->getOrderItem()->VerbundUrIDFNr() );
			record->setIBTOriginOrderNo( item->getOrderItem()->VerbundUrKaufNr() );
		}
		else if (cORTYPE_AUXILIARY == item->getOrder()->BatchSchreiben())
		{
			const pxOrderItem* pxItem = item->getOrderItem();
			libcsc::ibt::IIbtResponseRepositoryPtr responseRepo = pxItem->Session()->getIbtComponentManager()->createIbtResponseRepository();
			libcsc::ibt::IIbtResponsePtr response = responseRepo->findIbtResponse(pxItem->KdAuftragNr(), pxItem->PosNr());
			if (NULL != response.get() && false == response->getIbtResponseId().isUnset())
			{
				libcsc::ibt::IIbtRequestRepositoryPtr repo = pxItem->Session()->getIbtComponentManager()->createIbtRequestRepository();
				libcsc::ibt::IIbtRequestPtr request = repo->findIbtRequestById(response->getIbtRequestId());
				if (NULL != request.get() && false == request->getIbtRequestId().isUnset())
				{
					record->setIBTBranchNo(request->getBranchNo());
					record->setIBTBranchNo2(0);
					record->setIBTOriginCustomerNo(request->getCustomerNo());
					record->setIBTOriginOrderNo(request->getCscOrderNo());
					record->setIBTOriginLineNo(request->getCscOrderPosNo());
				}
			}
		}
		//else if (0 != item->getDeliveryInformation().get())
		//{
		//	record->setIBTBranchNo(item->getDeliveryInformation()->FirstPartnerNr());
		//	record->setIBTBranchNo2(item->getDeliveryInformation()->SecondPartnerNr());
		//	record->setIBTOriginCustomerNo(item->getDeliveryInformation()->IDFNr());
		//	record->setIBTOriginOrderNo(item->getDeliveryInformation()->UrsprungAuftragNr());
		//	record->setIBTOriginLineNo(item->getDeliveryInformation()->UrsprungPosNr());
		//}
		else if( item->getOrderItem()->BatchPosNr() > 0 )
		{
			record->setIBTOriginLineNo( item->getOrderItem()->BatchPosNr() );
		}

		if( item->getOrderItem()->IsPartialIBTQantity() && item->getOrderItem()->LinkPosNr() > 0 )
		{
			record->setOriginalIBTQty( item->getOrderItem()->GetIBTQuantityOfLinkedPosition() );
		}


        // transfer original ibt qty and ibt branch for orders with splitted ibt positions (not for shuttle orders!!!)
        if (cORTYPE_AUXILIARY != item->getOrder()->BatchSchreiben())
        {
            long tempOriginalIBTQty = item->getOrderItem()->getOriginalIBTQtyFromSplittedOrder();
            if (tempOriginalIBTQty > 0)
            {
                record->setOriginalIBTQty(tempOriginalIBTQty);
            }

            if (0 == record->getIBTBranchNo())
            {
                short tempOriginalIBTBranch = item->getOrderItem()->getOriginalIBTBranchFromSplittedOrder();
                if (tempOriginalIBTBranch > 0)
                {
                    record->setIBTBranchNo(tempOriginalIBTBranch);
                }
            }
        }


		record->setConfirmedQty( item->getOrderItem()->MengeBestaetigt() );
		record->setDeliveryQty( item->getOrderItem()->MengeGeliefert() );
		record->setBookedQty( item->getOrderItem()->MengeAbgebucht() );
		record->setQtyRebateInKind( item->getOrderItem()->MengeNatra() );
		record->setQtyRebateInKindWholesale( item->getOrderItem()->MengeNatraGrossH() );
		record->setQtyRebateInKindManufacturer( item->getOrderItem()->MengeNatraHerst() );
		basar::Decimal preisEKApo( item->getOrderItem()->PreisEKApo() );
		record->setPharmacyPurchasePrice( preisEKApo );
		basar::Decimal preisEKGrosso( item->getOrderItem()->PreisEKGrosso() );
		record->setCostPrice( preisEKGrosso );
		basar::Decimal rabattFestDM( item->getOrderItem()->RabattFestDM() );
		record->setDiscountValue( rabattFestDM );
		basar::Decimal rabattFest( /*item->getOrderItem()->RabattFest()*/ 0 ); // since 09/2016, rabattfest is used to store discount.fixeddicountvalue for FR shortliner --> must NOT be transferred to FERA !
		record->setFixedDiscount( rabattFest );
		record->setHints( getArticleHint( item ) );
		record->setChangeDiscount( discdetails.DiscountPercentage );
		record->setBonusAbility( discdetails.LogisticSurcharge );
		record->setChangeDiscountType( discdetails.DiscountType );
		record->setInvoicedPurchaseGroup( discdetails.CustomerPurchaseGroupDiscount );

		if (!item->getOrder()->Session()->isBulgaria()) // do not do this for Bulgaria (fields are not big enough for Bulgarian values...) (CPR-190165)
		{
			record->setPaymentTargetDiscPercentage1(discdetails.PaymentTargetDiscPercentage1);
			record->setPaymentTargetDiscPercentage2(discdetails.PaymentTargetDiscPercentage2);
			record->setPaymentTargetDiscPercentage3(discdetails.PaymentTargetDiscPercentage3);
			record->setPaymentTargetDiscPercentage4(discdetails.PaymentTargetDiscPercentage4);
			record->setPaymentTargetDiscPercentage5(discdetails.PaymentTargetDiscPercentage5);
			record->setPaymentTargetDiscPercentage6(discdetails.PaymentTargetDiscPercentage6);
		}

		record->setMaxPaymentTarget( item->getOrderItem()->MaxTargetNo() );
		record->setContLevel(boost::lexical_cast<basar::VarString>(item->getOrderItem()->ContainerLevel()));
		basar::Decimal maxAvp( item->getOrderItem()->GetMaxAvp() );
		record->setMaxPharmacySellPrice( maxAvp );
		record->setSkontoAbility( discdetails.MISK );
		record->setAmedisPriceDifference( discdetails.PDIFF );
		record->setCalcPharmacySellPrice( discdetails.KAVP2 );
		basar::Decimal surchargePercentage( discdetails.SurchargePercentage );
		record->setMarginCluster( surchargePercentage );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	const basar::VarString OrderTransformer::getArticleHint( pxVerbund::PXVBOrderItemPtr item ) const
	{
		METHODNAME_DEF( OrderTransformer, getArticleHint );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if ( item->getOrderItem()->Session()->isFrance() || item->getOrderItem()->Session()->isFrancePrewhole() )
		{
			if( item->getOrderItem()->IsNachliefern() || item->getOrderItem()->IsNachLieferungVerarbeitet() )
			{
				return "";
			}
		}

		if( item->getOrderItem()->IsInhibitTransferBem() )
		{
			return "";
		}

		return item->getOrderItem()->Bemerkungen()();
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	const OrderTransformer::DiscountDetails OrderTransformer::getDiscountDetails( pxVerbund::PXVBOrderItemPtr item ) const
	{
		METHODNAME_DEF( OrderTransformer, getDiscountDetails );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		OrderTransformer::DiscountDetails retval;

		if( 0 != item->getDiscountList().get() )
		{
			::pxItemDiscountListIter disciter(*item->getDiscountList().get());
			::pxItemDiscount* disc = NULL;
			while ( (disc = (::pxItemDiscount*) ++disciter) != NULL )
			{
				switch( disc->DiscountType() )
				{
					case ::BestBuy_ValuePctCash:
					case ::BestBuy_ValuePctShort:
					case ::BestBuy_ValuePctGenerika:
					case ::BestBuy_ValuePctPartenariat:
					case ::BestBuy_ValuePctWholeSale:
					case ::BestBuy_ValuePctRetail:
					case ::BestBuy_ValuePctTena:
					case ::BestBuy_ValuePctPhoenixMagic:
					case ::BestBuy_ValuePctOverdrive:
					case ::BestBuy_ValuePctWholeSaleInd:
					case ::BestBuy_GrossProfitPct:
						{
							if( 1 == disc->PaymentTargetNo() )
							{
								retval.PaymentTargetDiscPercentage1 = basar::Decimal( disc->DiscountValuePct() );
							}
							else if( 2 == disc->PaymentTargetNo() )
							{
								retval.PaymentTargetDiscPercentage2 = basar::Decimal( disc->DiscountValuePct() );
							}
							else if( 3 == disc->PaymentTargetNo() )
							{
								retval.PaymentTargetDiscPercentage3 = basar::Decimal( disc->DiscountValuePct() );
							}
							else if( 4 == disc->PaymentTargetNo() )
							{
								retval.PaymentTargetDiscPercentage4 = basar::Decimal( disc->DiscountValuePct() );
							}
							else if( 5 == disc->PaymentTargetNo() )
							{
								retval.PaymentTargetDiscPercentage5 = basar::Decimal( disc->DiscountValuePct() );
							}
							else if( 6 == disc->PaymentTargetNo() )
							{
								retval.PaymentTargetDiscPercentage6 = basar::Decimal( disc->DiscountValuePct() );
							}
							else
							{
								retval.DiscountPercentage = basar::Decimal( disc->DiscountValuePct() );
								retval.SurchargePercentage = basar::Decimal( disc->SurchargePct() );
								if ( 0.0 < disc->DiscountValPctMan() )
								{
									retval.DiscountPercentage = basar::Decimal( disc->DiscountValPctMan() );
								}
								char discounttype = ( disc->DiscountType() - ::BestBuy_ValuePctCash) + 'A';
								retval.DiscountType = basar::VarString( discounttype );
								retval.CustomerPurchaseGroupDiscount = disc->PharmacyGroupId()();
							}
							break;
						}

					case BestBuy_LogisticAddition:
						{
							retval.LogisticSurcharge = basar::Decimal( disc->DiscountValuePct() );
							retval.CustomerPurchaseGroupDiscount = basar::VarString( disc->PharmacyGroupId() );
							break;
						}

					default:
						{
							retval.CustomerPurchaseGroupDiscount = basar::VarString( disc->PharmacyGroupId() );
							break;
						}
				}
			}
		}

		if( 0 != item->getOrderPosCalcMode().get() )
		{
			retval.PaymentTargetDiscPercentage1 = basar::Decimal( item->getOrderPosCalcMode()->SurchargePct() );
			retval.PaymentTargetDiscPercentage2 = basar::Decimal( item->getOrderPosCalcMode()->DeductionPct() );
			retval.PaymentTargetDiscPercentage3 = basar::Decimal( item->getOrderPosCalcMode()->SurchargeCalc() );
			retval.PDIFF = basar::Decimal( item->getOrderPosCalcMode()->CalcAvp() );
			retval.KAVP2 = basar::Decimal( item->getOrderPosCalcMode()->CalcAvpDis() );
			retval.MISK = basar::Decimal( item->getOrderItem()->RefundValue() );
			retval.LogisticSurcharge = basar::Decimal( item->getOrderItem()->PromotionNo() );
		}
		
		if( item->getOrderItem()->RabattFestDM() < pxConstants::mZero )
		{
			retval.DiscountType = "-";
		}

		return retval;
	}
   //----------------------------------------------------------------------------//


} // namespace ProcessOrderDM
} // namespace corpha
} // namespace domMod
