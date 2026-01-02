#include "pxartmas.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

extern bool pxGlobalNoDatabaseWrite;
extern bool pxGlobalNoWriteToLog;

/*----------------------------------------------------------------------------*/
/*  Put this object into record.                                              */
/*----------------------------------------------------------------------------*/
int
pxArtMaster  :: Put
(
)
{
    tMARTIKEL record;
    memset(&record, 0, sizeof(tMARTIKEL));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tMARTIKEL));
}
/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArtBase list objects being inserted in the following ascending  */
/*  sequence:    Bezeichnung, PackGroesse, Darreichform.                      */
/*----------------------------------------------------------------------------*/
int
pxArtMaster :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxArtMaster *that = (pxArtMaster*)That;
    int retval;
    if ( (retval = Bezeichnung_.Compare(that->Bezeichnung_) ) == 0 )
    {                                   // then Bezeichnung ==
       retval = (PackGroesse_ == that->PackGroesse_) ? 0
                : (PackGroesse_ > that->PackGroesse_ ? 1 : -1);
       if ( retval == 0 )               // then Packgroesse ==, must match Darreichform
          retval = Darreichform_.Compare(that->Darreichform_);
    }
    return retval;
}


/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArtMaster  :: pxArtMaster
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtMaster  :: Init()
{
    tMARTIKEL    record;
    memset(&record, 0 , sizeof(tMARTIKEL));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArtMaster  :: Get
(
    DBAccessMode mode
)

{
    if ( pxGlobalNoDatabaseWrite)
       pxGlobalNoWriteToLog = true;

    tMARTIKEL record;
    memset(&record, 0, sizeof(tMARTIKEL));
    record.ArtikelNr = ArtikelNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;                 // import the data from tARTIKEL struct
    else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(), CMSG_ART_NOTFOUND, ArtikelNr_);

    pxGlobalNoWriteToLog = false;
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArtMaster  :: ~pxArtMaster()
{
// delete subobjects
   ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTIKEL structure.            */
/*----------------------------------------------------------------------------*/
tMARTIKEL&
Assign
(
    tMARTIKEL&         dest,
    const pxArtMaster&  src
)
{
// Copy native data types:
    dest.ArtikelNr              = src.ArtikelNr_;
    dest.PackGroesse            = src.PackGroesse_;
    dest.Laenge                 = src.Laenge_;
    dest.HerstellerNr           = src.HerstellerNr_;
    dest.Hoehe                  = src.Hoehe_;
    dest.Breite                 = src.Breite_;
    dest.Gewicht                = src.Gewicht_;
    dest.LaufzeitMonate         = src.LaufzeitMonate_;
    dest.KzPsychoStoffe         = src.KzPsychoStoffe_;
    dest.TaxLevel               = src.TaxLevel_;
    dest.TextKey_Hospital       = src.TextKey_Hospital_;
    dest.KzReserveHospital      = src.KzReserveHospital_;
    dest.STD_Menge              = src.STDMenge_;
    dest.Rundungs_STD_MGE       = src.KzRundungsSTDMge_;
    dest.Nicht_Ueber_Dafue      = src.Nicht_Ueber_Dafue_;
    dest.Nicht_Ueber_XML        = src.Nicht_Ueber_XML_;
    dest.KzZuschlagsArtikel     = src.KzZuschlagsArtikel_;
    dest.Steller                = src.Steller_;
    dest.PositivListe           = src.PositivListe_;
    dest.Konsig_Partner_Nr      = src.KonsigPartnerNr_;
    dest.Price_Group            = src.PriceGroup_;
    dest.Sortiment1             = src.Sortiment1_;
    dest.Sortiment2             = src.Sortiment2_;
    dest.Sortiment3             = src.Sortiment3_;
    dest.Sortiment4             = src.Sortiment4_;
    dest.Sortiment5             = src.Sortiment5_;
    dest.Datum_Anlage           = src.Datum_Anlage_.GetYYYYMMDD();
    dest.BusinessTypeNo         = src.BusinessTypeNo_;
    dest.Liste_5                = src.Liste_5_;
    dest.Upd_Flag               = src.Upd_Flag_;
    dest.MedProd_ABG_Verord     = src.MedProd_ABG_Verord_;
    dest.ProduserQuota          = src.ProduserQuota_;
    dest.MedicalProduct         = src.MedicalProduct_;
    dest.DateOutOfTrade         = src.DateOutOfTrade_.GetYYYYMMDD();
    dest.ArticleBlocked         = src.ArticleBlocked_;
    dest.IKSCode                = src.IKSCode_;
    dest.BatchRecallDateReturns = src.BatchRecallDateReturns_;
    dest.ImportArticle          = src.ImportArticle_;
    dest.BtmFaktor              = src.BtmFaktor_;
    dest.TFG                    = src.TFG_;
    dest.KontingentPPE          = src.KontingentPPE_;
	dest.Datum_Lieferbar_Ab     = src.Datum_Lieferbar_Ab_.GetYYYYMMDD();
	dest.MedizinProdukt         = src.MedizinProdukt_;
	dest.Frozen                 = src.Frozen_;
	dest.Datum_Aender           = src.Datum_Aender_.GetYYYYMMDD();
    dest.CMIFlag = src.CMIFlag_;
    dest.TaxPflichtig = src.TaxPflichtig_;

// Strings:
    dest.MatchCode[0]          = ' ';
    src.MatchCode_.GetData     (dest.MatchCode      );
    dest.Bezeichnung[0]        = ' ';
    src.Bezeichnung_.GetData   (dest.Bezeichnung    );
    dest.WarenGruppe[0]        = ' ';
    src.WarenGruppe_.GetData   (dest.WarenGruppe    );
    dest.TherapieGruppe[0]     = ' ';
    src.TherapieGruppe_.GetData(dest.TherapieGruppe );
    dest.Darreichform[0]       = ' ';
    src.Darreichform_.GetData  (dest.Darreichform   );
    dest.NormPackung[0]        = ' ';
    src.NormPackung_.GetData   (dest.NormPackung    );
    dest.Einheit[0]            = ' ';
    src.Einheit_.GetData       (dest.Einheit        );
    dest.WarenGruppeEigen[0]   = ' ';
    src.WarenGruppeEigen_.GetData (dest.WarenGruppeEigen );
    dest.Hersteller_Code[0]    = ' ';
    src.Hersteller_Code_.GetData (dest.Hersteller_Code );
    dest.Wirkstoff_NR[0]   = ' ';
    src.Wirkstoff_NR_.GetData (dest.Wirkstoff_NR );
    dest.HealthFundCode[0]     = ' ';
    src.HealthFundCode_.GetData (dest.HealthFundCode );
    dest.AbdaCode[0]           = ' ';
    src.AbdaCode_.GetData (dest.AbdaCode );
    dest.Artikel_Langname[0]           = ' ';
    src.ArtikelLangname_.GetData (dest.Artikel_Langname );
    dest.Artikel_NR_Herst[0]           = ' ';
    src.Artikel_NR_Herst_.GetData (dest.Artikel_NR_Herst );
	dest.ATC_Code[0] = ' ';
	src.ATC_Code_.GetData(dest.ATC_Code);
	dest.MinistryProductCode[0] = ' ';
	src.MinistryProductCode_.GetData(dest.MinistryProductCode);
	dest.HealthFundCodeHospital[0] = ' ';
	src.HealthFundCodeHospital_.GetData(dest.HealthFundCodeHospital);

    // Bit Map Exporting:
    src.ETArtMSchalter_.Export(dest.ETArtSchalter1, dest.ETArtSchalter2,
                               dest.ETArtSchalter3, dest.ETArtSchalter4,
                               dest.ETArtSchalter5);

    long dummy;
    //src.ETArtKlasse_.Export(dest.ETArtKlasse1, dest.ETArtKlasse2);
    src.ETArtKlasse_.Export(dest.ETArtKlasse1, dummy);
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTIKEL structure to a pxArtBase object.  */
/*----------------------------------------------------------------------------*/
pxArtMaster&
Assign
(
    pxArtMaster&        dest,
    const tMARTIKEL&   src
)
{
    dest.ArtikelNr_             = src.ArtikelNr;
    dest.PackGroesse_           = src.PackGroesse;
    dest.Laenge_                = src.Laenge;
    dest.HerstellerNr_          = src.HerstellerNr;
    dest.Hoehe_                 = src.Hoehe;
    dest.Breite_                = src.Breite;
    dest.Gewicht_               = src.Gewicht;
    dest.LaufzeitMonate_        = src.LaufzeitMonate;
    dest.KzPsychoStoffe_        = src.KzPsychoStoffe;
    dest.TaxLevel_              = src.TaxLevel;
    dest.TextKey_Hospital_      = src.TextKey_Hospital;
    dest.KzReserveHospital_     = src.KzReserveHospital;
    dest.STDMenge_              = src.STD_Menge;
    dest.KzRundungsSTDMge_      = src.Rundungs_STD_MGE;
    dest.PriceGroup_            = src.Price_Group;
    dest.ArticleBlocked_        = src.ArticleBlocked;
    dest.IKSCode_               = src.IKSCode;
    dest.BatchRecallDateReturns_ = src.BatchRecallDateReturns;
    dest.ImportArticle_         = src.ImportArticle;
    dest.BtmFaktor_             = src.BtmFaktor;
    dest.TFG_                   = src.TFG;
    dest.KontingentPPE_         = src.KontingentPPE;
	dest.Datum_Lieferbar_Ab_    = nDate(src.Datum_Lieferbar_Ab);
	dest.MedizinProdukt_        = src.MedizinProdukt;
	dest.Frozen_                = src.Frozen;
	dest.Datum_Aender_          = nDate(src.Datum_Aender);
    dest.CMIFlag_ = src.CMIFlag;
    dest.TaxPflichtig_ = src.TaxPflichtig;

    // Strings:
    dest.MatchCode_            = src.MatchCode;
    dest.Bezeichnung_          = src.Bezeichnung;
    dest.WarenGruppe_          = src.WarenGruppe;
    dest.TherapieGruppe_       = src.TherapieGruppe;
    dest.Darreichform_         = src.Darreichform;
    dest.NormPackung_          = src.NormPackung;
    dest.Einheit_              = src.Einheit;
    dest.WarenGruppeEigen_     = src.WarenGruppeEigen;
    dest.Hersteller_Code_      = src.Hersteller_Code;
    dest.Nicht_Ueber_Dafue_    = src.Nicht_Ueber_Dafue;
    dest.Nicht_Ueber_XML_      = src.Nicht_Ueber_XML;
    dest.KzZuschlagsArtikel_   = src.KzZuschlagsArtikel;
    dest.Wirkstoff_NR_         = src.Wirkstoff_NR;
    dest.HealthFundCode_       = src.HealthFundCode;
    dest.Steller_              = src.Steller;
    dest.PositivListe_         = src.PositivListe;
    dest.AbdaCode_             = src.AbdaCode;
    dest.KonsigPartnerNr_      = src.Konsig_Partner_Nr;
    dest.ArtikelLangname_      = src.Artikel_Langname;
    dest.Sortiment1_           = src.Sortiment1;
    dest.Sortiment2_           = src.Sortiment2;
    dest.Sortiment3_           = src.Sortiment3;
    dest.Sortiment4_           = src.Sortiment4;
    dest.Sortiment5_           = src.Sortiment5;
    dest.Datum_Anlage_         = nDate(src.Datum_Anlage);
    dest.BusinessTypeNo_       = src.BusinessTypeNo;
    dest.Liste_5_              = src.Liste_5;
    dest.Upd_Flag_             = src.Upd_Flag;
    dest.Artikel_NR_Herst_     = src.Artikel_NR_Herst;
    dest.MedProd_ABG_Verord_   = src.MedProd_ABG_Verord;
    dest.ProduserQuota_        = src.ProduserQuota;
	dest.MedicalProduct_       = src.MedicalProduct;
    dest.DateOutOfTrade_       = nDate(src.DateOutOfTrade);
	dest.ATC_Code_             = src.ATC_Code;
	dest.ATC_Code_.Strip();
	dest.MinistryProductCode_  = src.MinistryProductCode;
	dest.MinistryProductCode_.Strip();
	dest.HealthFundCodeHospital_ = src.HealthFundCodeHospital;
	dest.HealthFundCodeHospital_.Strip();

	// Bit Map Importing:
    dest.ETArtMSchalter_.Import(src.ETArtSchalter1, src.ETArtSchalter2,
                                src.ETArtSchalter3, src.ETArtSchalter4,
                                src.ETArtSchalter5);

    long dummy = 0;
    //dest.ETArtKlasse_.Import(src.ETArtKlasse1, src.ETArtKlasse2);
    dest.ETArtKlasse_.Import(src.ETArtKlasse1, dummy);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tARTIKEL struct     */
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxArtMaster&
pxArtMaster :: operator=( const pxArtMaster& src)
{
    tMARTIKEL    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTIKEL structure 'src' to this instance.       */
/*----------------------------------------------------------------------------*/
pxArtMaster&
pxArtMaster :: operator=( const tMARTIKEL& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxArtMaster :: pxArtMaster
(
    pxSession   *session,
    long    ArtikelNrL,                // Read via this type
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    ArtikelNr_ = ArtikelNrL;
    Get(mode);
}

int pxArtMaster::Read(const void *record)
{
    return pxMArtikelRead((tMARTIKEL*)record);
}

int pxArtMaster::ReadLock(const void *record)
{
    return pxMArtikelReadLock((tMARTIKEL*)record);
}

int pxArtMaster::Insert(const void *record)
{
    return pxMArtikelInsert((tMARTIKEL*)record);
}

int pxArtMaster::Update(const void *record)
{
    return pxMArtikelUpdate((tMARTIKEL*)record);
}
