#ifndef PXXMIT_INC
#define PXXMIT_INC

#include "pxsess.hpp"
#include "types/pricetypeenum.inc"
#include "types/origintypeenum.inc"
#include "tourutil.hpp"

class nDate;
class nMoney;
class pxSessionInitialization;
class pxCountryCodes;
class pxCustBase;
class pxCustOrderType;
class pxOrderList;
class pxOrderPeriod;
class pxOrderValidTrans;
class pxCustOrderInfo;
class pxParameter;
class pxOrderListIter;

class pxOrderTransmit : public pxSession
{

public:

    enum TransmissionTypeEnum                      // Transmission types
    {
        tFileTransfer,
        tDCT_Serial,
        tDCT_Parallel
    };

    /*----------------------------------------------------------------------------*/
    /*  Construction/destruction.                                                 */
    /*----------------------------------------------------------------------------*/
    pxOrderTransmit(const pxSessionInitialization& sessioninit);

    pxOrderTransmit(const basar::VarString& IniFileName);

    pxOrderTransmit(const short branchNo,
        const basar::VarString& countryCode,
        const basar::VarString& dataSource,
        const ::pxDeviceType deviceType,
        const basar::VarString& deviceName,
        const basar::VarString& messageFileName);

    ~pxOrderTransmit();

    /*----------------------------------------------------------------------------*/
    /*  Transmission control functions.                                           */
    /*----------------------------------------------------------------------------*/
    int             End();
    //  Transmission ended sucessfully.
    int             CancelTransmission();
    //  Cancel entire transmission. Orders transmitted so far are cancelled, too.
    void            CallBack();
    //  Customer requests to call him back by phone.
    long            CountOrderPos();
    //  count position within order
    int             EndProforma();
    //  does a proforma close order for the bulgarian XML application to get
    //  the final prices etc. for the customer

    /*----------------------------------------------------------------------------*/
    /*  Additional CustomerOrderInformation for the Swiss DCT Application         */
    /*----------------------------------------------------------------------------*/

    int             NewCustOrderInfoPolymed(nString& cOrdnum, long IDFNr, nString& cTourid, nString& cVersandart, long ProcessNr);

    int             PutCustOrderInfo(const long KdAuftragNr);

    nString         ConvertEan2Pzn(const nString& eannum);
    nString         ConvertPzn2Ean(const long aticlno, const long len);
    short           CustomerRouting(const long CustomerNo);
    int             CheckOrderOverdrive();
    long            getCustomerSpecialsUWIDFNr(const short BranchNo, const long CustomerNo, const nString& OrderType);

    /*----------------------------------------------------------------------------*/
    /*  Order entry functions:                                                    */
    /*----------------------------------------------------------------------------*/

    pxCustBase* CustomerId(const long IDFNr, const short vz = 0);
    //  Identify Customer with identification number 'IDFNr'.
    //  Returns a pointer to the customer base object.

    pxOrder* OrderTypeMSV3(const nString& _ordertype,
        const nString& _orderlabel,
        const int _pickingtype,
        const int _bookingtype);

    pxOrder* OrderTypeMSV3_2(const basar::VarString& _ordertype,
        const basar::VarString& _orderlabel,
        const int _pickingtype,
        const int _bookingtype,
        const long _orderperiodid);

    pxOrder* OrderType(const nString& t, const nString& number,
        const int kommityp = cDEFAULT,
        const int bookingtyp = cDEFAULT,
        const OriginTypeEnum batchschreiben = cORTYPE_UNKNOWN,
        const short options = 0,
        const nString& desiredTour = "",
        const nDate& desiredTourDate = TourUtil::getNullDate());
    //  Sets the current order to be of type 't' and a customer-own order 'number'.
    //  Opens a new order, if no order with a corresponding type and number has
    //  been previously opened within the current transmission.
    pxOrder* OrderType(const nString& t, const long number,
        const int kommityp = cDEFAULT,
        const int bookingtyp = cDEFAULT,
        const OriginTypeEnum batchschreiben = cORTYPE_UNKNOWN,
        const short options = 0);
    //  Sets the current order to be of type 't' and a customer-own order 'number'.
    //  Opens a new order, if no order with a corresponding type and number has
    //  been previously opened within the current transmission.

    pxOrder* OrderTypeNS(const nString& t, const nString& number,
        const short BranchNo,
        const int kommityp = cDEFAULT,
        const int bookingtyp = cDEFAULT,
        const OriginTypeEnum batchschreiben = cORTYPE_UNKNOWN,
        const short options = 0,
        const nString& desiredTour = "",
        const nDate& desiredTourDate = TourUtil::getNullDate());

    //  Sets the current order to be of type 't' and a customer-own order 'number'.
    //  Opens a new order, if no order with a corresponding type and number has
    //  been previously opened within the current transmission.

    pxOrder* SubOrderType(const nString& OrderType,
        const nString& SubOrderType, const long DeliveryDate);
    pxOrder* SubOrderType(const nString& OrderType,
        const nString& number,
        const char ShippingType,
        const char BookingType,
        const OriginTypeEnum batchschreiben,
        const nString& SubOrderType,
        const long DeliveryDate,
        const nString& desiredTour = "");
    //  Special methode for the old french datacommunication Hardware 170, 171

    pxOrder* OrderRemarks(const nString& remarks);
    //  Set order remarks. (no order, textual delivery remarks, etc.).

    void SetIsOCPOrder(bool isOcpOrder);
    //  Set the current Order type as OCPOrder (FR)
    
    bool GetIsOCPOrder();
    //  Get if the current Order type is OCPOrder (FR)

    pxOrder* FreeTextDoc(const nString& textdoc);
    //  Set free text for the current order.

    pxOrderItem* ItemQuery(const long ProductId,
        const long Quantity);
    //  Order item and product inquiry. This is not a purchase order, and therefore
    //  it does not create a persistent order item. However, a temporary pxOrderItem
    //  object instance is created and a pointer to it is returned.
    //  Order item and product info may be obtained using this object's methods.
    //  The pointer is valid as long as the current order is open or another ItemQuery
    //  request is issued. In either case, the server will free the storage and the
    //  pointer will be no longer valid.

    pxOrder* NewOrder(const long KdAuftragNr);
    //  Opens an existing order. First read that order( with number = KdAuftragNr) and

    pxOrder* NewOrderInfo();
    //  Just defines a pxOrder object with no insert record to th database(XML)

    pxOrder* NewOrderProforma();
    //  Just defines a pxOrder object with no insert record to th database(XML)


    pxOrderItem* NewOrderItem_12(const long  ArticleNo,
        const long QuanOrdered,
        const basar::VarString& XMLOrderReference,
        const basar::VarString& XMLLinereference,
        const bool RemAuxDel,
        const bool RemRestDel,
        const bool RemDispo,
        const bool RemPartDel,
        const PriceTypeEnum RemPriceType,
        const basar::VarString& Batch = "",
        const bool IsFixBatch = false);
    //  Enters a new order item for a stocked product. The product is identified
    //  by the product identification number 'ProductId'.

    pxOrderItem* NewOrderItem_13(const long ArticleNo,
        const long     QuanOrdered,
        const basar::VarString& XMLOrderReference,
        const basar::VarString& XMLLinereference,
        const bool     RemAuxDel,
        const bool     RemRestDel,
        const bool     RemDispo,
        const bool     RemPartDel,
        const PriceTypeEnum RemPriceType,
        const nMoney& PreisEKApo,
        const nMoney& PreisEKApoFree,
        const double   DiscountValPctMan,
        const long     QtyRebateInKind = 0,
        const basar::VarString& Batch = "",
        const bool     IsFixBatch = false);

    //  Enters a new order item for a stocked product. The product is identified
    //  by the product identification number 'ProductId'.

    //  Enters a new order item containing only a text, but no product order.
    pxOrderItem* NewOrderTextItem(const nString& text);
    //  Enters a new order item containing only a text, but no product order.

    //  Just defines a pxOrder object with no insert record to th database(XML)


    pxOrderItem* NewOrderItemInfo(const long ProductId,
        const long QuanOrdered);

    int             SeparateDefects();
    int             SeparateDefects_DE();
    int             CheckDoubleOrder();
    // Checks every order within the ActiveOrders_ list for Double entry
    pxCountryCodes* CountryCodesInfo(const short VZ, const nString& Code, const short type = 0);

    nString         GetMessageText(const int num);
    //  gets message from message file depend on num.

    /*----------------------------------------------------------------------------*/
    /*  Queries.                                                                  */
    /*----------------------------------------------------------------------------*/
    //  Returns a pointer to the customer base object.
    pxCustBase*     Customer()
                    { return Customer_; }
    //  Returns a pointer to the customer base object.
    pxOrderList*    OrderList()
                    { return ActiveOrders_; }
    //  Returns a pointer to the current order container object.
    pxOrder*        Order()
                    { return Order_; }
    //  Returns a pointer to the current order object.
    pxOrderItem*    OrderItem()
                    { return Item_; }
    long            DeliveryDate() { return DeliveryDate_; }
    //  Get Parameter for Locklevel handling
    pxParameter*    GetLockLevelParam();

    //  Set Wrong IDFNr
    void            SetWrongIDFNr(const nString& idfnr);
    // Set DeiveryDate
    void            SetDeliveryDate(const long date)
                    { DeliveryDate_ = date; }
    void            SetDoubleOrder();
    void            SetNotCloseOrder();
    void            SetTransmissionType(const TransmissionTypeEnum mode)
                    { TransmissionType_ = mode; }

    bool            IsSerial() const
                    { return (TransmissionType_ == tDCT_Serial); }
    bool            IsFileTransfer() const
                    { return (TransmissionType_ == tFileTransfer); }

    pxSession*      Session()
                    { return (pxSession*) this; }
    std::ifstream*  CMsgStream()
                    { return Session()->CMsgStream(); }
    void            Reset();          // Reset to initial state

    pxOrderPeriod   getMSV3OrderPeriod();
    bool            isOrderTypeAllowedForMSV3(const nString& ordertype);

private:
    void            Init();           // Init object
    pxOrderItem*    ItemPtr();        // Returns ptr to current item

    const nString&  processMSV3OrderLabel(const nString& orderlabel, pxCustOrderType* customerOrderType, const long orderperiodid);
    pxOrder*        GetOrderMSV3(const pxOrderValidTrans* vtp, const nString& _orderlabel, const pxOrderPeriod& _orderperiodid);
    bool            doConsolidationWithCurrentMSV3Order(const pxOrderPeriod& orderperiod, const nString& ordertype, const nString& orderlabel);

    pxOrder* GetOrder(pxOrderValidTrans* vtp, const long n,
        const OriginTypeEnum batchschreiben = cORTYPE_UNKNOWN,
        const short options = 0,
        const nString& desiredTour = "",
        const nDate& desiredTourDate = TourUtil::getNullDate()
    );
    // get existing order or create a new one
    pxOrder* OpenOrder(const pxOrderValidTrans* vtp, const long n, const OriginTypeEnum batchschreiben, const short options,
        pxOrder* order, pxOrderListIter& it, const pxCustOrderType* otp);

    bool            setDesiredTour(pxOrder* order, const nString& desiredTour, const nDate& desiredTourDate);
    bool            IsOrderSplit();
    bool            IsOrderConsolidation();
    bool            IsOrderConsolidationMSV3();
    bool            IsSplitOrderOnTens();
    long            AnzPosZu();

    pxCustBase*     Customer_;       // ptr to current customer
    pxOrderList*    DeferredOrders_; // ptr to list deferred orders
    pxOrderList*    ActiveOrders_;   // ptr to list of active orders
    pxOrder*        Order_;          // ptr to current order
    pxOrderItem*    Item_;           // ptr to current order item
    pxCustOrderInfo* CustInfo_;      // Swiss Customer Informations
    nString         WrongIDFNr_;     // wrong incoming customer number
    long            TotalTransPos_;  // Total count of positions in this transmission
    long            DeliveryDate_;   // Delivery Date given by fuction

    TransmissionTypeEnum TransmissionType_;

    bool            CallBack_;        // true if call back desired
    bool            isOCPOrder;       // true if current Order is OCP (FR)
};

#endif
