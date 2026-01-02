/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderTransmit:
Special functions and methodes for foreign DCT applications

REVISION HISTORY

05 May 2004 V1.00 REV 00 written by Ysbrand Bouma.
*/
#include "pxxmit.hpp"
#include "pxcustrouting.hpp"
#include "pxparameter.hpp"
#include "pxarticlecodes.hpp"
#include "pxcustomerspecials.hpp"
#include "pxartean.hpp"
#include "pxcstbas.hpp"
#include "pxcustinf.hpp"
#include "pxcstrou.hpp"
#include "pxcstonr.hpp"
#include "pxcountrycodes.hpp"
#include "pxoeparm.hpp"
#include "pxbranch.hpp"
#include "pxorder.hpp"

/*----------------------------------------------------------------------------*/
/*  Create a new Customer Information object                                  */
/*----------------------------------------------------------------------------*/
int
pxOrderTransmit :: NewCustOrderInfoPolymed( nString& cOrdnum, long IDFNr, nString& cTourid, nString& cVersandart, long ProcessNr )
{
    if ( CustInfo_ == NULL)
    {
        CustInfo_ = new pxCustOrderInfo(Session(), cOrdnum, IDFNr, cTourid, cVersandart, ProcessNr);
        CustInfo_->SetBatchOrderNr(0);
        CustInfo_->SetProcessNr(ProcessNr);
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
/*  Insert Customer Information object into Database                          */
/*----------------------------------------------------------------------------*/
int
pxOrderTransmit :: PutCustOrderInfo
(
  const   long    KdAuftragNr
)
{
    pxCustOrderInfo* temp = NULL;
    if ( CustInfo_ != NULL)
    {
        temp = new pxCustOrderInfo(Session(), KdAuftragNr);
        if ( !temp->IsGoodState() )
        {
            CustInfo_->SetOrderNr(KdAuftragNr);
            CustInfo_->Put();
            delete CustInfo_;
            CustInfo_= NULL;
        }
    }
    if (temp)
        delete temp;
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Look for the corresponding Article number by a given EanNumber            */
/*----------------------------------------------------------------------------*/
nString
pxOrderTransmit :: ConvertEan2Pzn
(
    const nString& EanNumber
)
{
    nString Artnum;
    pxArtEanList* eanlist = new pxArtEanList( Session() );
    eanlist->Select(EanNumber);
    pxArtEan* ean;
    pxArtEanListIter cursor(*eanlist);

    if (eanlist->IsGoodState())
    {
       while ( (ean = (pxArtEan*) ++cursor) != NULL )
       {
          Artnum = ean->ArtikelNr();
          break;
       }
    }
    delete eanlist;
    return Artnum;
}

/*----------------------------------------------------------------------------*/
/*  Look for the corresponding EanNumber given by an ArticleNo                */
/*----------------------------------------------------------------------------*/
nString
pxOrderTransmit :: ConvertPzn2Ean
(
    const long ArtikelNr,
    const long Len                //  Length of returned eannumber
)
{
    nString EanNum = "";
    EanNum.Trim(13);
    long artikelnr = ArtikelNr;
    pxArtEanList* eanlist = new pxArtEanList( Session() );
    eanlist->Select(artikelnr);
    pxArtEan* ean;
    pxArtEanListIter cursor(*eanlist);

    if (eanlist->IsGoodState())
    {
        while ( (ean = (pxArtEan*) ++cursor) != NULL )
        {
            EanNum = ean->Ean();
            EanNum.Strip(nString::cTRAILING);
            if ( EanNum.Length() == (size_t) Len )
                break;
        }
    }
    if ( EanNum.Length() != (size_t) Len )
        EanNum.Clear();
    delete eanlist;
    return EanNum;
}

/*----------------------------------------------------------------------------*/
/*  CustomerRouting:                                                          */
/*----------------------------------------------------------------------------*/
short
pxOrderTransmit :: CustomerRouting
(
    const long CustomerNo
)
{
    short               retvz       = 0;
    pxBranch*           branch      = Session()->Branch();
    pxCustRoutingList*  routinglist = NULL;
    pxCustRouting*      entry       = NULL;
    nDate   today;
    routinglist =  new pxCustRoutingList(Session());
    routinglist->Select(CustomerNo, branch->FilialNr(), today.GetDayOfWeek());
    pxCustRoutingListIter cursor(*routinglist);
    if (routinglist->Entries())
    {
        while ( (entry = (pxCustRouting*) ++cursor) != NULL )
        {
            if ( entry->TimeInWindow() )
            {
                retvz = entry->DestBranchNo();
            }
        }
    }
    delete routinglist;

    return retvz;
}

/*----------------------------------------------------------------------------*/
/*  CheckDoubleOrder: used on XML and Bytec(Swiss) application                */
/*----------------------------------------------------------------------------*/
int
pxOrderTransmit :: CheckDoubleOrder
(
)
{
    // Active OrderList
    if ( ActiveOrders_ )                   // ensure orders are there
    {
        pxOrderListIter ocursor(*ActiveOrders_);

        while ( (Order_ = (pxOrder*) ++ocursor) != NULL )
        {
            // Check double Order
            if ( Order_->CheckDoubleOrder() )
            {
                Order_->SetSendOrderDouble();
            }
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  CountryCodesInfoCode: This methode selects a countrycodetableentry depend */
/*  on Code and InfoType Infotype = 0, just select InfoCode (Code_Blockage)   */
/*  Infotype = 1, just select XMLCode                                         */
/*----------------------------------------------------------------------------*/
pxCountryCodes*
pxOrderTransmit :: CountryCodesInfo
(
    const short         vz,
    const nString&      Code,
    const short         InfoType
)
{
    pxCountryCodes*     Ccode     = NULL;
    pxCountryCodesList* CcodeList = new pxCountryCodesList(Session());
    CcodeList->Select(vz,Code,InfoType);
    if ( CcodeList->Entries() )
    {
        Ccode = (pxCountryCodes*)CcodeList->RemoveAt(0);
    }
    CcodeList->Clear();
    delete CcodeList;
    return Ccode;
}

/*---------------------------------------------------------------------------*/
/*  GetLockLevelParam: read from table parameter                              */
/*----------------------------------------------------------------------------*/
pxParameter*
pxOrderTransmit :: GetLockLevelParam
(
)
{
    pxParameter* locklevel = NULL;

    locklevel = new pxParameter(Session(), Branch()->FilialNr(), (nString)cPAR_KSCSERVER_GROUP,
                                (nString)cPAR_KSCSERVER_PURPOSE,(nString)cPAR_KSCSERVER_PARAMNAME);
    if (locklevel->Get(cDBGET_READONLY))
    {
        delete locklevel;
        locklevel = NULL;
    }
    return locklevel;
}

/*---------------------------------------------------------------------------*/
/*  GetMessageText: Gets message from the message file giben by num          */
/*---------------------------------------------------------------------------*/
nString
pxOrderTransmit :: GetMessageText
(
    const int num
)
{
    nString retval;
    nMessage text(CMsgStream(), num, 0);
    retval = text.String();
    retval.Compress('\n');
    return retval;
}


/***************************************************************************************************************************/
long pxOrderTransmit :: getCustomerSpecialsUWIDFNr( const short BranchNo, const long CustomerNo, const nString& OrderType)
{
    long uwIDFNr = 0;
    pxCustomerSpecials* entriep;
    pxCustomerSpecialsList* csList;
    pxParameter* param = NULL;
    nString ot(OrderType);
    ot.Strip();
    if ( ot != "UW")
    {
        return uwIDFNr;
    }
    // check parameter
    param  = new pxParameter(Session(), BranchNo, (nString)cPAR_KSCSERVER_GROUP,
                             (nString)cPAR_KSCSERVER_PURPOSE_CUSTOMERSPECIALS, (nString)cPAR_KSCSERVER_PARAMNAME);
    if (param->Get(cDBGET_READONLY))
    {
        delete param;
        return uwIDFNr;
    }
    if ( param->Wert() != 1 )
    {
        delete param;
        return uwIDFNr;
    }

    csList = new pxCustomerSpecialsList(Session());
    csList->SelectFirstUWIDF( BranchNo, CustomerNo);
    if ( csList->Entries() > 0 )
    {
        pxCustomerSpecialsListIter cursor(*csList);
        while ( (entriep = (pxCustomerSpecials*) ++cursor) != NULL )
        {
            uwIDFNr = entriep->UW_IDF();
            break;
        }
    }
    delete param;
    delete csList;
    return uwIDFNr;
}
