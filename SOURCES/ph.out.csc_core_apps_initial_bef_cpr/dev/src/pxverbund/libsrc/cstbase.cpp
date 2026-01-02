#include "pxcstbas.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "pxcsterm.hpp"
#include "pxcustomerflags.hpp"
#include "pxcstot.hpp"
#include "pxcstrou.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxcstseporderartgrp.hpp"
#include "pxcustbaseinformation.hpp"
#include "pxcustdeldelivery.hpp"
#include "pxcustpharmgroup.hpp"
#include "pxcustrouteweek.hpp"
#include "pxcustrouting.hpp"
#include "pxcustdisccondition.hpp"
#include "pxcstpaymentterms.hpp"
#include "pxcstprint.hpp"
#include "pxdebitlimit.hpp"
#include "pxdonepromoquotas.hpp"
#include "pxencloserscale.hpp"
#include "pxrangemember.hpp"
#include "pxcstbtm.hpp"
#include "pxbranch.hpp"
#include "pxrange.hpp"
#include "pxsubordertype.hpp"
#include "pxttype.hpp"
#include "tourmanager.hpp"
#include "types/messagecodeenum.inc"

extern int pxGlobalLanguageId;

/*----------------------------------------------------------------------------*/
/*  Default constructor.                                                      */
/*----------------------------------------------------------------------------*/
pxCustBase::pxCustBase(pxSession* session)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustBase::pxCustBase( pxCustBase& src )
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKUNDE structure to construct this instance.                          */
/*----------------------------------------------------------------------------*/
pxCustBase::pxCustBase( pxSession* session, tKUNDE& src )
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxCustBase::pxCustBase( pxSession* session, short Vertriebszentrum, long IDFNr, DBAccessMode mode )
    : pxDBRecord(session)
{
    Init();
    this->VertriebszentrumNr_ = Vertriebszentrum;
    this->IDFNr_ = IDFNr;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustBase::~pxCustBase()
{
    if( NULL != m_TourManager )
    {
        delete m_TourManager;
        m_TourManager = NULL;
    }

    if(flags_)                      { delete flags_; }
    if(terms_)                      { delete terms_; }
    if(OrderTypeList_)              { delete OrderTypeList_; }
    if(RouteList_)                  { delete RouteList_; }
    if(RouteListOrderType_)         { delete RouteListOrderType_; }
    if(RouteWeekList_)              { delete RouteWeekList_; }
    if(RouteWeekListOrderType_)     { delete RouteWeekListOrderType_; }
    if(OrdTypeRouteList_)           { delete OrdTypeRouteList_; }
    if(BusyList_)                   { delete BusyList_; }
    if(PharmGroupList_)             { delete PharmGroupList_; }
    if(DelayedDelivery_)            { delete DelayedDelivery_; }
    if(CustDiscCondition_)          { delete CustDiscCondition_; }
    if(SubOrderType_)               { delete SubOrderType_; }
    if(CustTimeList_)               { delete CustTimeList_; }
    if(CustBaseInformation_)        { delete CustBaseInformation_; }
    if(CstSepOrderArtGroupList_)    { delete CstSepOrderArtGroupList_; }
    if(DebitLimitK2_)               { delete DebitLimitK2_; }
    if(DebitLimitK1_)               { delete DebitLimitK1_; }
    if(CstPaymentTermsList_)        { delete CstPaymentTermsList_; }
    if(DiscountGrpListFive_)        { delete DiscountGrpListFive_; }
    if(DiscountGrpMemListFive_)     { delete DiscountGrpMemListFive_; }
    if(CstPrintList_)               { delete CstPrintList_; }
    if(EncloserScaleList_)          { delete EncloserScaleList_; }
    if(DonePromoQuotaList_)         { delete DonePromoQuotaList_; }
    if(OrdTypeRouteWeekList_)       { delete OrdTypeRouteWeekList_; }
    if(CustomerRoutingList_)        { delete CustomerRoutingList_; }
    if(CustomerGroupFlagsList_)     { delete CustomerGroupFlagsList_; }
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKUNDE structure.              */
/*----------------------------------------------------------------------------*/
tKUNDE& Assign( tKUNDE& dest, const pxCustBase& src )
{
    dest.IDFNr     = src.IDFNr_;
    dest.FilialNr  = src.FilialNr_;

    dest.MatchCode[0] = ' ';
    src.MatchCode_.GetData(dest.MatchCode);

    dest.NameApo[0] = ' ';
    src.NameApo_.GetData(dest.NameApo);

    dest.NameInhaber[0] = ' ';
    src.NameInhaber_.GetData(dest.NameInhaber);

    dest.Land[0] = ' ';
    src.Land_.GetData( dest.Land );

    dest.Strasse[0] = ' ';
    src.Strasse_.GetData(dest.Strasse);

    dest.Ort[0] = ' ';
    src.Ort_.GetData(dest.Ort);

    dest.Postleitzahl[0] = ' ';
    src.Postleitzahl_.GetData(dest.Postleitzahl);

    dest.TelNr[0] = ' ';
    src.TelNr_.GetData(dest.TelNr);

    dest.TelNrDafue[0] = ' ';
    src.TelNrDafue_.GetData(dest.TelNrDafue);

    dest.TelKurzwahl[0] = ' ';
    src.TelKurzwahl_.GetData(dest.TelKurzwahl);

    dest.FaxNr[0] = ' ';
    src.FaxNr_.GetData(dest.FaxNr);

    dest.Bemerkungen[0] = ' ';
    src.Bemerkungen_.GetData((char*)dest.Bemerkungen);

    dest.StdAufKoBuart[0] = ' ';
    src.StdAufKoBuart_.GetData(dest.StdAufKoBuart);

    dest.PassWord[0] = ' ';
    src.PassWord_.GetData(dest.PassWord);

    dest.AnredeKz = src.AnredeKz_;

    dest.KdGruppe[0] = ' ';
    src.KdGruppe_.GetData(dest.KdGruppe);

    dest.DafueSystem[0] = ' ';
    src.DafueSystem_.GetData(dest.DafueSystem);

    dest.LagerFachNrRgBei[0] = ' ';
    src.LagerFachNrRgBei_.GetData(dest.LagerFachNrRgBei);

    dest.AnzPosLS_RG = src.AnzPosLS_RG_;
    dest.AnzPosSortBehaelt = src.AnzPosSortBehaelt_;

    dest.KzKdKlasse[0] = ' ';
    src.KzKdKlasse_.GetData(dest.KzKdKlasse);

    dest.KundeText[0] = ' ';
    src.KundeText_.GetData(dest.KundeText);

    dest.VerbundKunde     = src.VerbundKunde_;
    dest.KuehlBox         = src.KuehlBox_;
    dest.TourenKippZeit   = src.TourenKippZeit_;
    dest.IMSBezirkNr      = src.IMSBezirkNr_;
    dest.PersonalNrVertr  = src.PersonalNrVertr_;

    dest.KzSprache[0] = ' ';
    src.KzSprache_.GetData(dest.KzSprache);

    dest.KundenNr = src.KundenNr_;
    dest.VertriebszentrumNr = src.VertriebszentrumNr_;
    dest.ETKdMerkmal1 = 0;
    dest.ETKdMerkmal2 = 0;
    dest.KzKdDoppelKontr = ' ';
    dest.OriginalFilialNr   = src.OriginalFilialNr_;
    dest.NotFilialNr        = src.NotFilialNr_;
    dest.EmailAdresse[0] = ' ';
    src.EmailAdresse_.GetData(dest.EmailAdresse);
    dest.NachLieferTyp      = src.NachLieferTyp_;
    dest.PartnerNr          = src.PartnerNr_;
    dest.KzPsychoStoffe     = src.KzPsychoStoffe_;
    dest.VZKk1              = src.VZKk1_;
    dest.XMLPreisLevel      = src.XMLPreisLevel_;
    dest.PreWholeTyp        = src.PreWholeTyp_;
    dest.XMLInfoLevel       = src.XMLInfoLevel_;
    dest.AnzAufClose        = src.AnzAufClose_;

    dest.NationalCustomerNo[0] = ' ';
    src.NationalCustomerNo_.GetData(dest.NationalCustomerNo);

    dest.RatioCustomerNo[0] = ' ';
    src.RatioCustomerNo_.GetData(dest.RatioCustomerNo);

    dest.KrankenKassenNr[0] = ' ';
    src.KrankenKassenNr_.GetData(dest.KrankenKassenNr);

    dest.CalculationType    = src.CalculationType_;
    dest.Surcharge_Basic    = src.SurchargeBasic_;
    dest.Deduction_Basic    = src.DeductionBasic_;
    dest.SurchargePct       = src.SurchargePct_;
    dest.DeductionPct       = src.DeductionPct_;
    dest.VatRegistered      = src.VatRegistered_;
    dest.RebateMethFreeSale = src.RebateMethFreeSale_;
    dest.RebateMethHealthf  = src.RebateMethHealthf_;
    dest.MainCstNo          = src.MainCstNo_;
    dest.Surcharge_BasicKK  = src.SurchargeBasicKK_;
    dest.Deduction_BasicKK  = src.DeductionBasicKK_;
    dest.SurchargePctKK     = src.SurchargePctKK_;
    dest.DeductionPctKK     = src.DeductionPctKK_;
    dest.LieferMeldung      = src.LieferMeldung_;
    dest.ManufacturerNo     = src.ManufacturerNo_;
    dest.MSV3CfgChangeDate  = src.MSV3CfgChangeDate_.getDate();

    src.ETArtKlasse_.Export(dest.ETArtKlasse1, dest.ETArtKlasse2); // Bit Map Exporting!

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKUNDE structure to a pxCustBase object.   */
/*----------------------------------------------------------------------------*/
pxCustBase& Assign( pxCustBase& dest, const tKUNDE& src )
{
    dest.Land_ = src.Land;
    dest.Land_.Strip();

    dest.IDFNr_        = src.IDFNr;
    dest.MatchCode_    = src.MatchCode;
    dest.MatchCode_.Strip();
    dest.FilialNr_     = src.FilialNr;
    dest.NameApo_      = src.NameApo;
    dest.NameApo_.Strip();
    dest.NameInhaber_  = src.NameInhaber;
    dest.NameInhaber_.Strip();
    dest.Strasse_      = src.Strasse;
    dest.Strasse_.Strip();
    dest.Ort_          = src.Ort;
    dest.Ort_.Strip();
    dest.Postleitzahl_ = src.Postleitzahl;
    dest.Postleitzahl_.Strip();
    dest.TelNr_        = src.TelNr;
    dest.TelNr_.Strip();
    dest.TelNrDafue_   = src.TelNrDafue;
    dest.TelNrDafue_.Strip();
    dest.FaxNr_        = src.FaxNr;
    dest.FaxNr_.Strip();
    dest.TelKurzwahl_  = src.TelKurzwahl;
    dest.TelKurzwahl_.Strip();
    dest.Bemerkungen_  = src.Bemerkungen;
    dest.Bemerkungen_.Strip();
    dest.AnredeKz_     = src.AnredeKz;
    dest.KdGruppe_     = src.KdGruppe;
    dest.KdGruppe_.Strip();
    dest.DafueSystem_  = src.DafueSystem;
    dest.DafueSystem_.Strip();
    dest.LagerFachNrRgBei_ = src.LagerFachNrRgBei;
    dest.LagerFachNrRgBei_.Strip();
    dest.AnzPosLS_RG_  = src.AnzPosLS_RG;
    dest.AnzPosSortBehaelt_ = src.AnzPosSortBehaelt;
    dest.KzKdKlasse_   = src.KzKdKlasse;
    dest.KzKdKlasse_.Strip();
    dest.KundeText_    = src.KundeText;
    dest.KundeText_.Strip();
    dest.VerbundKunde_  = src.VerbundKunde;
    dest.StdAufKoBuart_   = src.StdAufKoBuart;
    dest.StdAufKoBuart_.Strip();
    dest.PassWord_        = src.PassWord;
    dest.PassWord_.Strip();
    dest.KuehlBox_        = src.KuehlBox;
    dest.TourenKippZeit_  = src.TourenKippZeit;
    dest.IMSBezirkNr_     = src.IMSBezirkNr;
    dest.PersonalNrVertr_ = src.PersonalNrVertr;
    dest.KundenNr_        = src.KundenNr;
    dest.VertriebszentrumNr_ = src.VertriebszentrumNr;
    dest.OriginalFilialNr_   = src.OriginalFilialNr;
    dest.NotFilialNr_        = src.NotFilialNr;
    dest.EmailAdresse_       = src.EmailAdresse;
    dest.EmailAdresse_.Strip();
    dest.NachLieferTyp_      = src.NachLieferTyp;
    dest.PartnerNr_         = src.PartnerNr;
    dest.KzSprache_         = src.KzSprache;
    dest.KzPsychoStoffe_    = src.KzPsychoStoffe;
    dest.VZKk1_             = src.VZKk1;
    dest.XMLPreisLevel_     = src.XMLPreisLevel;
    dest.PreWholeTyp_       = src.PreWholeTyp;
    dest.XMLInfoLevel_      = src.XMLInfoLevel;
    dest.NationalCustomerNo_ = src.NationalCustomerNo;
    dest.RatioCustomerNo_   = src.RatioCustomerNo;
    dest.AnzAufClose_       = src.AnzAufClose;
    dest.KrankenKassenNr_   = src.KrankenKassenNr;
    dest.CalculationType_   = src.CalculationType;
    dest.SurchargeBasic_     = src.Surcharge_Basic;
    dest.DeductionBasic_     = src.Deduction_Basic;
    dest.SurchargePct_       = src.SurchargePct;
    dest.DeductionPct_       = src.DeductionPct;
    dest.VatRegistered_      = src.VatRegistered;
    dest.RebateMethFreeSale_ = src.RebateMethFreeSale;
    dest.RebateMethHealthf_  = src.RebateMethHealthf;
    dest.MainCstNo_          = src.MainCstNo;
    dest.SurchargeBasicKK_   = src.Surcharge_BasicKK;
    dest.DeductionBasicKK_   = src.Deduction_BasicKK;
    dest.SurchargePctKK_     = src.SurchargePctKK;
    dest.DeductionPctKK_     = src.DeductionPctKK;
    dest.LieferMeldung_      = src.LieferMeldung;
    dest.ManufacturerNo_     = src.ManufacturerNo;
    dest.MSV3CfgChangeDate_  = src.MSV3CfgChangeDate;

    dest.ETArtKlasse_.Import(src.ETArtKlasse1, src.ETArtKlasse2); // Bit Map Importing!

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void pxCustBase::Init()
{
    tKUNDE record;
    m_TourManager = NULL;
    flags_                   = NULL;
    terms_                   = NULL;
    OrderTypeList_           = NULL;
    RouteList_               = NULL;
    RouteListOrderType_      = NULL;
    RouteWeekList_           = NULL;
    RouteWeekListOrderType_  = NULL;
    OrdTypeRouteList_        = NULL;
    OrdTypeRouteWeekList_    = NULL;
    BusyList_                = NULL;
    BusyTime_                = NULL;
    CustTimeList_            = NULL;
    PharmGroupList_          = NULL;
    DelayedDelivery_         = NULL;
    DelayedDeliveryRead_     = false;
    CustDiscCondition_       = NULL;
    SubOrderType_            = NULL;
    CustBaseInformation_     = NULL;
    CstSepOrderArtGroupList_ = NULL;
    DebitLimitK2_            = NULL;
    DebitLimitK1_            = NULL;
    CstPaymentTermsList_     = NULL;
    DiscountGrpListFive_     = NULL;
    DiscountGrpMemListFive_  = NULL;
    CstPrintList_            = NULL;
    EncloserScaleList_       = NULL;
    DonePromoQuotaList_      = NULL;
    CustomerRoutingList_     = NULL;
    CustomerGroupFlagsList_  = NULL;
    NoSeparate_              = false;
    HasDebitLimitK1_         = true;
    DebitLimitK1InitCallDone_ = false;
    HasDebitLimitK2_         = true;
    DebitLimitK2InitCallDone_ = false;
    memset(&record, 0 , sizeof(tKUNDE));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tKUNDE struct       */
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxCustBase& pxCustBase::operator=( const pxCustBase& src )
{
    tKUNDE    record;                 // used to export the data of 'src'
    bool      NoSeparate = src.NoSeparate_;
    Assign(*this, Assign(record, src));
    NoSeparate_ = NoSeparate;
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKUNDE structure 'src' to this instance.         */
/*----------------------------------------------------------------------------*/
pxCustBase& pxCustBase::operator=( const tKUNDE& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures list objects being inserted in the following ascending            */
/*  sequence:    NameApo, Ort, Strasse.                                       */
/*----------------------------------------------------------------------------*/
int pxCustBase::CompareTo( const nCollectable *That, void* /* p */, const long /* lparm */ ) const
{
    pxCustBase *that = (pxCustBase*)That;
    int retval;
    if ( (retval = NameApo_.Compare(that->NameApo_) ) == 0 )
    {                                   // then Name Apotheke ==
       if ( (retval = Ort_.Compare(that->Ort_)) == 0)
          retval = Strasse_.Compare(that->Strasse_);
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int pxCustBase::Get( DBAccessMode mode )
{
    tKUNDE record;
    memset(&record, 0, sizeof(tKUNDE));
    record.IDFNr = IDFNr_;
    record.VertriebszentrumNr = VertriebszentrumNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
    {
        (*this)= record;                 // import the data from tKUNDE struct

        // Must change Filiale?
        if (Session()->Branch()->FilialNr() != Vertriebszentrum())
        {
            pxBranch CustBranch(Session(), Vertriebszentrum());
            if (CustBranch.IsGoodState())
            {
                *(Session()->Branch()) = CustBranch;
            }
            //TODO: (MJ) fixed, tested but commented back out (after clarifications), due to the estimated high effort of retesting all dependent programs and modules...
            //else
            //{
            //    DBCondition(CustBranch.ErrorMsg(), CustBranch.ErrorNumber());
            //    return retval;
            //}
        }

       CustomerGroupFlagsList();

        Session()->Branch()->Store() = FilialNr();
        Session()->LanguageCode(ConvertLanguage(Sprache()));
        pxGlobalLanguageId = Session()->LanguageCode();
    }
    else
        DBCondition(nMessage(CMsgStream(), CMSG_CST_NOTFOUND, IDFNr_),
            CMSG_CST_NOTFOUND);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int pxCustBase::Read( const void* record )
{
    return pxKundeRead((tKUNDE*)record);
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to a list of routes planned for this customer.           */
/*  The container is empty if there are no routes available for this customer.*/
/*----------------------------------------------------------------------------*/
pxCustRouteList* pxCustBase::RouteList()
{
    nDate today;
    if ( RouteList_ == NULL )           // then list not constructed,
    {                                   // do it now
       RouteList_ = new pxCustRouteList(Session());
       RouteList_->Select(Vertriebszentrum(), KundenNr(), FilialNr(),today);     // and read all routes for self
       pxCustRoute* lastroute = (pxCustRoute*)(RouteList_->GetLast());
       if ( RouteList_->Entries() )
       {
          if ( !((pxCustRoute*)(RouteList_->At(0)))->IsPseudoTour() )
             FirstTourId_ = ((pxCustRoute*)(RouteList_->At(0)))->TourId();
          if ( lastroute )
             LastTourId_  = lastroute->TourId();
          RouteList_->SetWeekDay();
       }

    }
    return RouteList_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to a list of routes planned for this customer.           */
/*  This list contains only entries where KdAuftragArt > ""                   */
/*  The container is empty if there are no routes available for this customer.*/
/*----------------------------------------------------------------------------*/
pxCustRouteList* pxCustBase::RouteListOrderType( const nString& KdAuftragArt )
{
    nString ot = KdAuftragArt;
    ot.Strip();
    nDate today;

    if ( RouteListOrderType_  && !ot.IsEmpty() )
    {
       if ( RouteListOrderType_->IsOrderTypeInList(ot) )
       {
          if ( OrdTypeRouteList_ )
          {
             delete OrdTypeRouteList_;
             OrdTypeRouteList_ = RouteListOrderType_->NewList();
             OrdTypeRouteList_->ShrinkForOrderType(ot);
             OrdTypeRouteList_->SetWeekDay();
          }
       }
    }

    if ( RouteListOrderType_ == NULL )           // then list not constructed,
    {                                   // do it now
       if ( RouteList_ )
       {
          if ( !RouteList_->OrderTypesInList() )
          {
             return RouteListOrderType_;
          }
       }
       else
       {
             return RouteListOrderType_;
       }

       RouteListOrderType_ = RouteList_->NewList();
       if ( RouteListOrderType_->Entries() )
       {
          RouteListOrderType_->SetWeekDay();
          RouteListOrderType_->ShrinkForOrderType();
          if (OrdTypeRouteList_   == NULL )
          {
             OrdTypeRouteList_ = RouteListOrderType_->NewList();
             OrdTypeRouteList_->ShrinkForOrderType(ot);
             OrdTypeRouteList_->SetWeekDay();
          }
       }
    }
    return RouteListOrderType_;
}
/*----------------------------------------------------------------------------*/
/*  Return a pointer to a list of routes planned for this customer.           */
/*  The container is empty if there are no routes available for this customer.*/
/*----------------------------------------------------------------------------*/
pxCustRouteList* pxCustBase::OrdTypeRouteList()
{
    nDate today;
    if ( OrdTypeRouteList_ == NULL )           // then list not constructed,
    {
      /*
       OrdTypeRouteList_ = new pxCustRouteList(Session());
       OrdTypeRouteList_->Select(Vertriebszentrum(), KundenNr(), FilialNr(),today);  // and read all routes for self
       OrdTypeRouteList_->SetWeekDay();
      */
    }
    return OrdTypeRouteList_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to a list of routes per Week planned for this customer.  */
/*  The container is empty if there are no routes available for this customer.*/
/*----------------------------------------------------------------------------*/
pxCustRouteWeekList* pxCustBase::RouteWeekList()
{
    if ( RouteWeekList_ == NULL )       // then list not constructed,
    {                                   // do it now
       RouteWeekList_ = new pxCustRouteWeekList(Session());
       RouteWeekList_->Select(Vertriebszentrum(), KundenNr(), FilialNr());     // and read all routes for self
       if ( !RouteWeekList_->IsGoodState() )
       {
          delete  RouteWeekList_;
          RouteWeekList_ = NULL;
       }
    }
    return RouteWeekList_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to a list of routes per Week planned for this customer.  */
/*  The container is empty if there are no routes available for this customer.*/
/*----------------------------------------------------------------------------*/
pxCustRouteWeekList* pxCustBase::RouteWeekListOrderType( const nString& KdAuftragArt )
{
    nString ot = KdAuftragArt;
    ot.Strip();
    nDate today;

    if ( RouteWeekListOrderType_  && !ot.IsEmpty() )
    {
       if ( RouteWeekListOrderType_->IsOrderTypeInList(ot) )
       {
          if ( OrdTypeRouteWeekList_ )
          {
             delete OrdTypeRouteWeekList_;
             OrdTypeRouteWeekList_ = RouteWeekListOrderType_->NewList();
             OrdTypeRouteWeekList_->ShrinkForOrderType(ot);
          }
       }
    }

    if ( RouteWeekListOrderType_ == NULL )  // then list not constructed,
    {                                   // do it now
       if ( RouteWeekList_)
       {
          if ( !RouteWeekList_->OrderTypesInList() )
          {
             return RouteWeekListOrderType_;
          }
       }
       else
       {
             return RouteWeekListOrderType_;
       }
       RouteWeekListOrderType_ = RouteWeekList_->NewList();
       if ( RouteWeekListOrderType_->Entries() )
       {
          RouteWeekListOrderType_->ShrinkForOrderType();
          if (OrdTypeRouteWeekList_   == NULL )
          {
             OrdTypeRouteWeekList_ = RouteWeekListOrderType_->NewList();
             OrdTypeRouteWeekList_->ShrinkForOrderType(ot);

          }
       }
    }

    return RouteWeekListOrderType_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to a list of routes planned for this customer.           */
/*  The container is empty if there are no routes available for this customer.*/
/*----------------------------------------------------------------------------*/
pxCustRouteWeekList* pxCustBase::OrdTypeRouteWeekList()
{
    return OrdTypeRouteWeekList_;
}

/*----------------------------------------------------------------------------*/
/*  Deletes the routlist if RouteList_ not NULLP                              */
/*----------------------------------------------------------------------------*/
void pxCustBase::DeleteRouteList()
{
    if ( RouteList_ != NULL )           // then list  constructed,
    {
       delete RouteList_;
       RouteList_ = NULL;
    }
}

/*----------------------------------------------------------------------------*/

pxCustBaseInformation* pxCustBase::CustBaseInformation()
{
    if (NULL == CustBaseInformation_)
    {
        CustBaseInformation_ = new pxCustBaseInformation(Session(), VertriebszentrumNr_, IDFNr_);
        if (CustBaseInformation_->Get(cDBGET_READONLY))
        {
            delete CustBaseInformation_;
            CustBaseInformation_ = NULL;
        }
    }
    return CustBaseInformation_;
}
/*----------------------------------------------------------------------------*/
/*  DeconstructSubOrderType()                                                 */
/*----------------------------------------------------------------------------*/
int pxCustBase::DeconstructSubOrderType()
{
    int retval = 0;
    if (SubOrderType_)
    {
       delete SubOrderType_;
       SubOrderType_ = NULL;
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  DeconstructSubOrderType()                                                 */
/*----------------------------------------------------------------------------*/
int pxCustBase::DeconstructCustDiscCondition()
{
    int retval = 0;
    if (CustDiscCondition_)
    {
       delete CustDiscCondition_;
       CustDiscCondition_ = NULL;
    }
    return retval;
}
