#include "pxartvza.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "pxartsto.hpp"
#include "pxcountrycodes.hpp"
#include "types/messagecodeenum.inc"

extern bool pxGlobalNoDatabaseWrite;
extern bool pxGlobalNoWriteToLog;

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArtFiliale :: pxArtFiliale
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxArtFiliale :: pxArtFiliale
(
    pxSession   *session,
    long    ArtikelNrL,                // Read via this type
    short   FilialNr,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    ArtikelNr_ = ArtikelNrL;
    FilialNr_ =  FilialNr;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArtFiliale :: pxArtFiliale
(
    pxArtFiliale& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArtFiliale :: ~pxArtFiliale()
{
}


/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxArtFiliale :: Put
(
)

{
     tFARTIKEL record;
     memset(&record, 0, sizeof(tFARTIKEL));
     Assign(record, *this);
     return nDBWrite(&record, sizeof(tFARTIKEL));
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTIKEL structure.            */
/*----------------------------------------------------------------------------*/
tFARTIKEL&
Assign
(
    tFARTIKEL&         dest,
    const pxArtFiliale&  src
)
{
    long l1,l2,l3,l4,l5;
    // Copy native data types:
   dest.FilialNr              = src.FilialNr_;
    dest.ArtikelNr             = src.ArtikelNr_;
    dest.Bestand               = src.Bestand_;
    dest.NachFrage             = src.NachFrage_;
    dest.Zuzahlung             = src.Zuzahlung_;
    dest.NatraStaffelNr        = src.NatraStaffelNr_;
    dest.Prisoart              = src.Prisoart_;
    dest.Artikelaktiv          = src.Artikelaktiv_;
    dest.LagerBereichNr        = src.LagerBereichNr_;
    dest.VerbundArtikel        = src.VerbundArtikel_;
    dest.VerkaufEinheit        = src.VerkaufEinheit_;
    dest.ContainerGroesse      = src.ContainerGroesse_;
//    dest.KontigentMenge        = src.KontigentMenge_;
    dest.TextKey               = src.TextKey_;
    dest.BestandReserviert     = src.BestandReserviert_;
    dest.ChargenArtikel        = src.ChargenArtikel_;
    dest.WafoTyp               = src.WafoTyp_;
    dest.KZRange               = src.KZRange_;
    dest.MoreConditions        = src.MoreConditions_;
    dest.BestandTagesAnfang    = src.BestandTagesAnfang_;
    dest.CodeBlocage           = src.CodeBlocage_;
	dest.BlockedForReturns	   = src.BlockedForReturns_;

    // Strings:
    dest.StationNr[0]          = ' ';
    src.StationNr_.GetData     (dest.StationNr      );
    dest.LagerFachNr[0]        = ' ';
    src.LagerFachNr_.GetData   (dest.LagerFachNr    );

    // Conversions:
    sprintf(dest.Rabattfaehig, "%02d", src.Rabattfaehig_);

    // Bit Map Exporting:
  src.ETArtFSchalter_.Export(l1,l2,l3,l4,l5);
  dest.ETArtSchalter1 |= l1;
  dest.ETArtSchalter2 |= l2;
  dest.ETArtSchalter3 |= l3;
  dest.ETArtSchalter4 |= l4;
  dest.ETArtSchalter5 |= l5;
//src.ETArtFSchalter_.Export(dest.ETArtSchalter1, dest.ETArtSchalter2,
//                          dest.ETArtSchalter3, dest.ETArtSchalter4,
//                          dest.ETArtSchalter5);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTIKEL structure to a pxArtBase object.  */
/*----------------------------------------------------------------------------*/
pxArtFiliale&
Assign
(
    pxArtFiliale&        dest,
    const tFARTIKEL&   src
)
{

    dest.FilialNr_             = src.FilialNr;
    dest.ArtikelNr_            = src.ArtikelNr;
    dest.Bestand_              = src.Bestand;
    dest.NachFrage_            = src.NachFrage;
    dest.Zuzahlung_            = src.Zuzahlung;
    dest.NatraStaffelNr_       = src.NatraStaffelNr;
    dest.Prisoart_             = src.Prisoart;
    dest.Artikelaktiv_         = src.Artikelaktiv;
    dest.LagerBereichNr_       = src.LagerBereichNr;
    dest.VerbundArtikel_       = src.VerbundArtikel;
    dest.VerkaufEinheit_       = src.VerkaufEinheit;
    dest.ContainerGroesse_     = src.ContainerGroesse;
//    dest.KontigentMenge_       = src.KontigentMenge;
    dest.TextKey_              = src.TextKey;
    dest.BestandReserviert_    = src.BestandReserviert;
    dest.ChargenArtikel_       = src.ChargenArtikel;
    dest.WafoTyp_              = src.WafoTyp;
    dest.KZRange_              = src.KZRange;
    dest.MoreConditions_       = src.MoreConditions;
    dest.BestandTagesAnfang_   = src.BestandTagesAnfang;
    dest.CodeBlocage_          = src.CodeBlocage;
	dest.BlockedForReturns_	   = src.BlockedForReturns;

    // Strings:
    dest.StationNr_            = src.StationNr;
    dest.LagerFachNr_          = src.LagerFachNr;

    // Conversions:
    dest.Rabattfaehig_         = atoi(src.Rabattfaehig);

    // Bit Map Importing:
    dest.ETArtFSchalter_.Import(src.ETArtSchalter1, src.ETArtSchalter2,
                                src.ETArtSchalter3, src.ETArtSchalter4,
                                src.ETArtSchalter5);


    dest.Bestand_ = ( (dest.Bestand_ < 0) ? 0 : dest.Bestand_ );
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtFiliale :: Init()
{
    tFARTIKEL    record;
    memset(&record, 0 , sizeof(tFARTIKEL));
    Assign(*this, record);
    //Artikelaktiv_ = '0';
    CodeBlocage_ = '2';
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tARTIKEL struct     */
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxArtFiliale&
pxArtFiliale :: operator=( const pxArtFiliale& src)
{
    tFARTIKEL    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTIKEL structure 'src' to this instance.       */
/*----------------------------------------------------------------------------*/
pxArtFiliale&
pxArtFiliale :: operator=( const tFARTIKEL& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Subtract quantity q from quantity on hand. Returns quantity subtracted.   */
/*----------------------------------------------------------------------------*/
long
pxArtFiliale :: SubQuantity
(
    const long q
)
{
    long retval;
    // avoid negative values in stock:
    retval = ( Bestand_ - q < 0 ) ? Bestand_ : q;
    Bestand_ -= retval;
    SetDirty();
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Add quantity q from quantity on hand. Returns quantity added.             */
/*----------------------------------------------------------------------------*/
long
pxArtFiliale :: AddQuantity
(
    const long q
)
{
    Bestand_ += q;
    SetDirty();
    return q;
}

/*----------------------------------------------------------------------------*/
/*  Set quantity q from quantity on hand. Returns quantity set  .             */
/*----------------------------------------------------------------------------*/
long
pxArtFiliale :: SetQuantity
(
    const long q
)
{
    Bestand_ = q;
    SetDirty();
    return q;
}

/*----------------------------------------------------------------------------*/
/*  Lock this article for selling                                             */
/*----------------------------------------------------------------------------*/
void
pxArtFiliale :: StopSelling
(
)
{
    if (!IsStopSelling())
    {
       Artikelaktiv_ += 3;
    }
}

/*----------------------------------------------------------------------------*/
/*  UnLock this article for selling                                             */
/*----------------------------------------------------------------------------*/
void
pxArtFiliale :: ReleaseStopSelling
(
)
{
    if (IsStopSelling())
    {
       Artikelaktiv_ -= 3;
    }
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArtFiliale :: Get
(
    DBAccessMode mode
)

{
    if ( pxGlobalNoDatabaseWrite)
       pxGlobalNoWriteToLog = true;

    tFARTIKEL record;
    memset(&record, 0, sizeof(tFARTIKEL));
    record.ArtikelNr = ArtikelNr_;
    record.FilialNr = FilialNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);

    if (!retval)
       (*this)= record;                 // import the data from tARTIKEL struct
    else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(), CMSG_ART_NOTFOUND, ArtikelNr_);

    pxGlobalNoWriteToLog = false;
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  CheckCodeBlocage:.                                                        */
/*  if codeblocage changes on stockreceipt, so mark article                   */
/*  depend on entry within table countrycodes selected by the new codeblocage */
/*  It returns ErrorState                                                     */
/*----------------------------------------------------------------------------*/
int
pxArtFiliale :: CheckCodeBlocage
(
    const char codeblocage
)
{
    pxCountryCodes*        Ccode = NULL;
    pxArtStoreLoc*      storeloc = NULL;
    pxArtStoreLocList*       stl = NULL;
    CodeBlocage_  = codeblocage;
    pxCountryCodesList* CcodeList = new pxCountryCodesList(Session());
    CcodeList->Select(FilialNr_,CodeBlocage_, (short) pxCountryCodes::CCT_INFOCODE);
    if ( CcodeList->Entries() )
    {
       Ccode = (pxCountryCodes*)CcodeList->RemoveAt(0);
    }
    CcodeList->Clear();
    delete CcodeList;
    if ( Ccode == NULL )
       return ErrorState();
    Artikelaktiv_   = Ccode->ArticleActiv();
    if ( VerbundArtikel_ == '1' || VerbundArtikel_ == '2' ) // 1 oder 2 3 wird nicht überschrieben
    {
       VerbundArtikel_ = Ccode->AuxDelivery();
    }
    SetDirty();
    // update storelocentries
    stl = new pxArtStoreLocList(Session());
    stl->Select(ArtikelNr_,FilialNr_);
    if ( stl->Entries() )
    {
       storeloc = (pxArtStoreLoc*)stl->RemoveAt(0);
       if ( storeloc->Get(cDBGET_FORUPDATE) == 0)
       {
          if ( storeloc->IsGoodState() )
          {
             storeloc->VerbundArtikel( Ccode->AuxDelivery());
             storeloc->Put();
          }
       }
    }
    delete stl;
    if (storeloc )
       delete storeloc;

    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  GetCBPrintCode:.                                                          */
/*  this methode returns the printcode for this object's code blocage.        */
/*  This is a special request for the french application                      */
/*----------------------------------------------------------------------------*/
nString
pxArtFiliale :: GetCBPrintCode
(
)
{
    nString PrintCode;
    pxCountryCodes*        Ccode = NULL;
    pxCountryCodesList* CcodeList = new pxCountryCodesList(Session());
    CcodeList->Select(FilialNr_,CodeBlocage_, (short) pxCountryCodes::CCT_INFOCODE);
    if ( CcodeList->Entries() )
    {
       Ccode = (pxCountryCodes*)CcodeList->RemoveAt(0);
    }
    CcodeList->Clear();
    delete CcodeList;
    if ( Ccode == NULL )
       return PrintCode;

    PrintCode = Ccode->PrintCode();
    PrintCode.Strip();
    return  PrintCode;
}

int pxArtFiliale::Read(const void *record)
{
    return pxFArtikelRead((tFARTIKEL*)record);
}

int pxArtFiliale::ReadLock(const void *record)
{
    return pxFArtikelReadLock((tFARTIKEL*)record);
}

int pxArtFiliale::Insert(const void *record)
{
    return pxFArtikelInsert((tFARTIKEL*)record);
}

int pxArtFiliale::Update(const void *record)
{
    return pxFArtikelUpdate((tFARTIKEL*)record);
}
