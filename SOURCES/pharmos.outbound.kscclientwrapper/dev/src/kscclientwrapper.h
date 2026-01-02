//----------------------------------------------------------------------------
/*! \file   kscclientwrapper.h
 *  \brief  Wrapper class for access to KSC server.
 *  \author Klaus Hinz
 *  \date   03.01.2008
 */
//----------------------------------------------------------------------------

#ifndef GUARD_KSCCLIENTWRAPPER_H
#define GUARD_KSCCLIENTWRAPPER_H

#include <libbasar_definitions.h>
#include <libbasardbaspect_accessorpropertytable.h>
#include <libbasarproperty_propertytype.h>
#include <libbasardbaspect_accessorpropertytable_yiterator.h>
#include <libbasarproperty_propertydescriptionlistref.h>

#include "kscclientdmexception.h"

// forward declaration
struct N_ORDERINFO;
typedef struct N_ORDERINFO orderinfoS;

namespace domMod
{
  /*! \brief  Execution status of a method. */
  typedef enum
  {
    OK, //!< Successfully, property "infotext" can contain further infos.
    INPUT_ERROR, //!< Input parameter(s) are incorrect/inconsistent, see property "infotext".
    OUT_OF_OPERATING_TIME_ERROR //!< KSC server was called outside its operating time.
  } KSCClientDMErrorCodeEnum;  

  /*! \brief  Params for establishing a connection to KSC server */
  struct KSCClientDMConnParams
  {
    /*! \brief  Device (max length 8) */
    basar::VarString device;
    /*! \brief  Port */
    basar::Int32 port;
    /*! \brief  Name of the computer the KSC server runs on (max length 8) */
    basar::VarString server;
  };

  /*! \brief  Params for establishing a connection to KSC server */
  struct KSCClientDMReturn
  {
    /*! \brief  Execution status of a method */
    KSCClientDMErrorCodeEnum stateInfo;
    /*! \brief  Additional infos about execution */
    basar::VarString textInfo;
    /*! \brief  Returned Values */
    basar::db::aspect::AccessorPropertyTable_YIterator itInfo;
  };

  /*! \brief  Wrapper class for access to KSC server. */
	class KSCClientWrapper
	{
	public:
		/*! \brief  Default constructor. */
		KSCClientWrapper( log4cplus::Logger & logger );

		/*! \brief  Destructor. */
		virtual ~KSCClientWrapper();

    /*! \brief  Set the default branchNo */
    void setBranchNoDefault(basar::Int16 branchNoDefault);

    /*! \brief  Wrapper function for ConnectServerNoIni. */
    void kscConnectServerNoIni(const KSCClientDMConnParams& myKSCClientDMConnParams);

    /*! \brief  Wrapper function for DisconnectServer. */
    void kscDisconnectServer();

    /*! \brief  Wrapper function for OpenOrderReferenceVz. */
    KSCClientDMReturn kscOpenOrderReferenceVz(
      const basar::db::aspect::AccessorPropertyTable_YIterator itOrder,
      basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo);

    KSCClientDMReturn kscOpenOrderReferenceVzType(
      const basar::db::aspect::AccessorPropertyTable_YIterator itOrder,
      basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo);

    /*! \brief  Wrapper function for SetOrderTypeSub. */
    KSCClientDMReturn kscSetOrderTypeSub(
      const basar::db::aspect::AccessorPropertyTable_YIterator itOrder,
      basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo);

    /*! \brief  Wrapper function for SetDeliveryDate. */
    KSCClientDMReturn kscSetDeliveryDate(
      const basar::db::aspect::AccessorPropertyTable_YIterator itOrder,
      basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo);

    /*! \brief  Wrapper function for SetOrderHeadItem. */
    KSCClientDMReturn kscAddOrderHeadItem(
      const basar::db::aspect::AccessorPropertyTable_YIterator itOrder,
      basar::VarString headline,
      basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo);

    /*! \brief  Wrapper function for SetOrderText. */
    KSCClientDMReturn kscSetOrderText(
      const basar::db::aspect::AccessorPropertyTable_YIterator itOrder,
      basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo);

    /*! \brief  Wrapper function for kscSetBatchOrderTyp. */
    KSCClientDMReturn kscSetBatchOrderTyp(const basar::db::aspect::AccessorPropertyTable_YIterator itOrder, basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo);

	KSCClientDMReturn kscSetBatchValueDate(
		const basar::db::aspect::AccessorPropertyTable_YIterator itOrder, 
		basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo
			);

    /*! \brief  Wrapper function for kscSetOriginBranch. */
    KSCClientDMReturn kscSetOriginBranch(const basar::db::aspect::AccessorPropertyTable_YIterator itOrder, basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo);

	KSCClientDMReturn kscSetOrderRelationNo( const basar::Int32 no, const basar::Int16 type);

	/*! \brief  Wrapper function for SetCallback. */
    KSCClientDMReturn kscSetCallback(
      basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo);

    /*! \brief  Wrapper function for kscSetOrderNoOrigin. */
    KSCClientDMReturn kscSetOrderNoOrigin(const basar::db::aspect::AccessorPropertyTable_YIterator itOrder, basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo);

    /*! \brief  Wrapper function for kscSetPosNoOriginm_posNo. */
    KSCClientDMReturn kscSetPosNoOrigin(const basar::db::aspect::AccessorPropertyTable_YIterator itOrder, basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo);

	/*! \brief  Wrapper function for SetOrderItem. */
    KSCClientDMReturn kscAddOrderItem(
      const basar::db::aspect::AccessorPropertyTable_YIterator itItem,
      basar::db::aspect::AccessorPropertyTable_YIterator itItemInfo);

	/*! \brief  Wrapper function for AddOrderItemCodeRab. */
    KSCClientDMReturn kscAddOrderItemCodeRab(
      const basar::db::aspect::AccessorPropertyTable_YIterator itItem,
      basar::db::aspect::AccessorPropertyTable_YIterator itItemInfo);

	/*! \brief  Wrapper function for AddOrderItemCodeBatch. */
    KSCClientDMReturn kscAddOrderItemCodeBatch(
      const basar::db::aspect::AccessorPropertyTable_YIterator itItem,
      basar::db::aspect::AccessorPropertyTable_YIterator itItemInfo);

	/*! \brief  Wrapper function for AddTextItem. */
	KSCClientDMReturn kscAddTextItem(const basar::db::aspect::AccessorPropertyTable_YIterator itItem, basar::db::aspect::AccessorPropertyTable_YIterator itItemInfo);

    /*! \brief  Wrapper function for CloseOrder. */
    KSCClientDMReturn kscCloseOrder(
      basar::db::aspect::AccessorPropertyTable_YIterator itOrderInfo);

    /*! \brief  Wrapper function for CancelOrder. */
    KSCClientDMReturn kscCancelOrder();

    /*! \brief  Wrapper function for PostponeOrder. */
    KSCClientDMReturn kscPostponeOrder();

	/*! \brief  Wrapper function for PostponeOrder. */
	void kscSetNoRouting();

	protected:

  private:
    /*! \brief  Copy constructor. */
    KSCClientWrapper(const KSCClientWrapper& KSCClientWrapper);

    /*! \brief  Assignment operator. */
    KSCClientWrapper& operator= (const KSCClientWrapper& KSCClientWrapper);

    /*! \brief  Clear return structure. */
    void clearReturnData();

    /*! \brief  Set m_device */
    void setDevice(const basar::VarString& userID);

    /*! \brief  Set m_server */
    void setServer(const basar::VarString& server);

    /*! \brief  Set m_branchNo */
    void setBranchNo(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_customerNo */
    void setCustomerNo(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_orderType */
    void setOrderType(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_subOrderType */
    void setSubOrderType(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_pickingType */
    void setPickingType(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_bookingType */
    void setBookingType(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_deliveryDate */
    void setDeliveryDate(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_orderHeadline */
    void setOrderHeadline(
      const basar::db::aspect::AccessorPropertyTable_YIterator iter,
      basar::VarString headline);

    /*! \brief  Set m_orderNote */
    void setOrderNote(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_reference */
    void setReference(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

	/*! \brief  Set m_deferredPaymentDate */
    void setDeferredPaymentDate(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

	/*! \brief  Set m_ediDeliveryNote */
    void setEdiDeliveryNote(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

	/*! \brief  Set m_articleNo */
    void setArticleNo(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_ean */
    void setEan(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_articleCode */
    void setArticleCode(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

	/*! \brief  Set m_orderQty */
    void setOrderQty(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_interBranchTransfer */
    void setInterBranchTransfer(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_subsequentdelivery */
    void setSubsequentDelivery(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_articleRequirementPurchase */
    void setArticleRequirementPurchase(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_setPartialDelivery */
    void setPartialDelivery(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_sequenceNo */
    void setSequenceNo(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_itemNote */
    void setItemNote(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_originBranch */
    void setOriginBranch(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

	/*! \brief  Set m_batchOrderTyp */
    void setBatchOrderTyp(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

    /*! \brief  Set m_idfOrigin */
    void setIdfOrigin(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

	/*! \brief  Set m_orderNoOrigin */
    void setOrderNoOrigin(const basar::db::aspect::AccessorPropertyTable_YIterator iter);

	/*! \brief  Set m_posNoOrigin */
    void setPosNoOrigin( const basar::db::aspect::AccessorPropertyTable_YIterator iter );

    void setRebateInKind( const basar::db::aspect::AccessorPropertyTable_YIterator iter );
    void setFreeRebate( const basar::db::aspect::AccessorPropertyTable_YIterator iter );
    void setRebateType( const basar::db::aspect::AccessorPropertyTable_YIterator iter );
	void setBatchSchreiben( const basar::db::aspect::AccessorPropertyTable_YIterator iter );
	void setBatch( const basar::db::aspect::AccessorPropertyTable_YIterator iter );




	/*! \brief  Get property "infotext" from KSC returnData */
    void getInfoText(basar::VarString& str) const;

    /*! \brief  Get property "orderno" from KSC returnData */
    void getOrderNo(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "tourid" from KSC returnData */
    void getTourId(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "tourdate" from KSC returnData */
    void getTourDate(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "valueoforder" from KSC returnData */
    void getValueOfOrder(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "linesoforder" from KSC returnData */
    void getLinesOfOrder(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "lacklines" from KSC returnData */
    void getLackLines(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "textlines" from KSC returnData */
    void getTextLines(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "pharmacyname" from KSC returnData */
    void getPharmacyName(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "deliverybranchno" from KSC returnData */
    void getDeliveryBranchNo(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "articleno" from KSC returnData */
    void getArticleNo(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "ean" from KSC returnData */
    void getEan(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

	/*! \brief  Get property "qtylack" from KSC returnData */
    void getQtyLack(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "lackreason" from KSC returnData */
    void getLackReason(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "auxqty" from KSC returnData */
    void getAuxQty(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "articleunit" from KSC returnData */
    void getArticleUnit(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "articlename" from KSC returnData */
    void getArticleName(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "handout" from KSC returnData */
    void getHandout(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "auxbranchno" from KSC returnData */
    void getAuxBranchNo(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "codeblocage" from KSC returnData */
    void getCodeBlocage(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "restdeliveryqty" from KSC returnData */
    void getRestDeliveryQty(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "deliveryqty" from KSC returnData */
    void getDeliveryQty(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "lackreasonctycode" from KSC returnData */
    void getLackReasonCtyCode(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "pharmpurchprice" from KSC returnData */
    void getPharmPurchPrice(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "custpurchprice" from KSC returnData */
    void getCustPurchPrice(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "pharmsellprice" from KSC returnData */
    void getPharmSellPrice(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "taxrate" from KSC returnData */
    void getTaxRate(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "expirydate" from KSC returnData */
    void getExpiryDate(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "lpprprice" from KSC returnData */
    void getLpprPrice(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "seracode" from KSC returnData */
    void getSeraCode(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "xmlcode" from KSC returnData */
    void getXmlCode(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "xmltext" from KSC returnData */
    void getXmlText(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "articleunitorg" from KSC returnData */
    void getArticleUnitOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "articlenameorg" from KSC returnData */
    void getArticleNameOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "handoutorg" from KSC returnData */
    void getHandoutOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "pharmpurchpriceorg" from KSC returnData */
    void getPharmPurchPriceOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "custpurchpriceorg" from KSC returnData */
    void getCustPurchPriceOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "pharmsellpriceorg" from KSC returnData */
    void getPharmSellPriceOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "taxrateorg" from KSC returnData */
    void getTaxRateOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "lpprpriceorg" from KSC returnData */
    void getLpprPriceOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "articlenoorg" from KSC returnData */
    void getArticleNoOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "codeblcageorg" from KSC returnData */
    void getCodeBlocageOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "seracodeorg" from KSC returnData */
    void getSeraCodeOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "xmlcodeorg" from KSC returnData */
    void getXmlCodeOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Get property "xmltextorg" from KSC returnData */
    void getXmlTextOrg(basar::db::aspect::AccessorPropertyTable_YIterator iterInfo) const;

    /*! \brief  Evaluate KSC return value */
    bool evaluateKSCRetVal(
      basar::Int32 result,
      KSCClientDMReturn& stateInfo) const;

    /*! \brief  Convert from string to char * with max length */
    void delimitedString2Char(char* const dest, const basar::VarString& source, basar::Int16 maxLength) const;

    /*! \brief  Convert from char * to string with max length */
    void delimitedChar2String(basar::VarString& dest, const char* const source, basar::Int16 maxLength) const;

    // user id for openening connection
    static const basar::Int16 DEFAULT_UID = 0;

    // length for conversion std::string to char * (order)
    static const basar::Int16 MAX_LEN_DEVICE = 8;
    static const basar::Int16 MAX_LEN_SERVER = 20;
    static const basar::Int16 LEN_ORDERTYPE = 2;
    static const basar::Int16 LEN_SUBORDERTYPE = 3;
    static const basar::Int16 LEN_PICKINGTYPE = 1;
    static const basar::Int16 LEN_BOOKINGTYPE = 1;
    static const basar::Int16 MAX_LEN_ORDERHEADLINE = 30;
    static const basar::Int16 MAX_LEN_ORDERNOTE = 30;  // = ORDERTEXT in orderinfoS
    static const basar::Int16 MAX_LEN_REFERENCE = 10;  //!  \todo MAX_LEN_REFERENCE?
    static const basar::Int16 MAX_LEN_INFOTEXT = 240;  // = TEXT in orderinfoS
    static const basar::Int16 MAX_LEN_PHARMACYNAME = 40;
    static const basar::Int16 MAX_LEN_EDIDELIVERYNOTE = 30;
    static const basar::Int16 LEN_TOURID = 6;

    // length for conversion std::string to char * (item)
    static const basar::Int16 LEN_EAN = 13;
    static const basar::Int16 MAX_LEN_ARTICLECODE = 25;
    static const basar::Int16 MAX_LEN_ITEMNOTE = 30;
    static const basar::Int16 MAX_LEN_ARTICLEUNIT = 9;
    static const basar::Int16 MAX_LEN_ARTICLENAME = 30;
    static const basar::Int16 MAX_LEN_HANDOUT = 3;
    static const basar::Int16 MAX_LEN_CODEBLOCAGE = 1;
    static const basar::Int16 MAX_LEN_LACKREASONCTYCODE = 10;
    static const basar::Int16 MAX_LEN_SERACODE = 20;
    static const basar::Int16 MAX_LEN_XMLCODE = 5;
    static const basar::Int16 MAX_LEN_XMLTEXT = 100;
    static const basar::Int16 MAX_LEN_ARTICLEUNITORG = MAX_LEN_ARTICLEUNIT;
    static const basar::Int16 MAX_LEN_ARTICLENAMEORG = MAX_LEN_ARTICLENAME;
    static const basar::Int16 MAX_LEN_HANDOUTORG = MAX_LEN_HANDOUT;
    static const basar::Int16 MAX_LEN_CODEBLOCAGEORG = MAX_LEN_CODEBLOCAGE;
    static const basar::Int16 MAX_LEN_SERACODEORG = MAX_LEN_SERACODE;
    static const basar::Int16 MAX_LEN_XMLCODEORG = MAX_LEN_XMLCODE;
    static const basar::Int16 MAX_LEN_XMLTEXTORG = MAX_LEN_XMLTEXT;
	static const basar::Int16 MAX_LEN_BATCH = 24;

	log4cplus::Logger		m_Logger;
    basar::Int16 m_branchNoDefault;

    // connection
    char m_device[MAX_LEN_DEVICE+1];
    char m_server[MAX_LEN_SERVER+1];

    // order
    basar::Int16 m_branchNo;
    basar::Int32 m_customerNo;
    char m_orderType[LEN_ORDERTYPE+1];
    char m_subOrderType[LEN_SUBORDERTYPE+1];
    char m_pickingType[LEN_PICKINGTYPE+1];
    char m_bookingType[LEN_BOOKINGTYPE+1];
    basar::Int32 m_deliveryDate;
    char m_orderHeadline[MAX_LEN_ORDERHEADLINE+1];
    char m_orderNote[MAX_LEN_ORDERNOTE+1];
    char m_reference[MAX_LEN_REFERENCE+1];
    basar::Int16 m_originBranchNo;
    basar::Int32 m_batchTyp;
	basar::Int32 m_deferredPaymentDate;
	char m_ediDeliveryNote[MAX_LEN_EDIDELIVERYNOTE];

    // item
    basar::Int32 m_articleNo;
    char m_ean[LEN_EAN+1];
    char m_articleCode[MAX_LEN_ARTICLECODE+1];
    basar::Int32 m_orderQty;
    basar::Int16 m_interBranchTransfer;
    basar::Int16 m_subsequentDelivery;
    basar::Int16 m_articleRequirementPurchase;
    basar::Int16 m_partialDelivery;
    basar::Int16 m_sequenceNo;
    basar::Int32 m_idfOrigin;
	basar::Int32 m_orderNoOrigin;
	basar::Int32 m_posNoOrigin;
    char m_itemNote[MAX_LEN_ITEMNOTE+1];
	char m_Batch[MAX_LEN_BATCH+1];

	basar::Int32		m_RebateInKind;		// Naturalrabatt 
	basar::Decimal		m_FreeRebate;		// freier Rabatt 
	basar::Int16		m_RebateType;		// Rabatttyp
	basar::Int32		m_BatchSchreiben;	// BatchSchreiben (???)

    orderinfoS*			m_returnData;
  };
}
#endif
