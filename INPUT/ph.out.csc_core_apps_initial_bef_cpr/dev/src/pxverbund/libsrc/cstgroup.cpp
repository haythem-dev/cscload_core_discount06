#include "pxcstgrp.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

enum pxCustGroups
{
   pxCustGroup01 =1,                    // Apotheke
   pxCustGroup02,                       // Drogerie
   pxCustGroup03,                       // Gewerblicher Endverbraucher
   pxCustGroup04,                       // Barverkauf, ohne Berechtigung
   pxCustGroup05,                       // Barverkauf, mit  Berechtigung
   pxCustGroup06,                       // Apothekenbelegschaft
   pxCustGroup07,                       // Eigene Belegschaft
   pxCustGroup08,                       // Fremdgrosshandel und andere AG
   pxCustGroup09,                       // Filiale der eigenen AG
   pxCustGroup10,                       // Wechselkonto, gesperrt für Auftragerf.
   pxCustGroup11,                       // Export an Apotheken, nicht EG
   pxCustGroup12,                       // Export an Grosshandel, nicht EG
   pxCustGroup13,                       // Eigenverbrauch, interne Konten
   pxCustGroup14,                       // Export an Apotheken, EG
   pxCustGroup15,                       // Export an Grosshandel, EG
   pxCustGroup16,                       // Verbundene Unternehmen
   pxCustGroup17,                       // Assoziierte Unternehmen
   pxCustGroup18                        // Eigenverbrauch, interne Konten AEP
};

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustGroup :: pxCustGroup
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustGroup :: pxCustGroup
(
    pxCustGroup& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKUNDENGRUPPE structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxCustGroup :: pxCustGroup
(
    pxSession   *session,
    tKUNDENGRUPPE& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxCustGroup :: pxCustGroup
(
    pxSession   *session,
    nString&    KdGruppe,                 // Read via string input
    short      VZ,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    KdGruppe_ = KdGruppe;
    FilialNr_ = VZ;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustGroup :: ~pxCustGroup()
{
        ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKUNDENGRUPPE structure.       */
/*----------------------------------------------------------------------------*/
tKUNDENGRUPPE&
Assign
(
    tKUNDENGRUPPE&    dest,
    const pxCustGroup&  src
)
{
    // Copy native data types:
    dest.KdGruppeSperrKZ       = src.KdGruppeSperrKZ_;
    dest.KdGruppeFreiKZ        = src.KdGruppeFreiKZ_;

    // Strings:
    dest.KdGruppe[0] = ' ';
    src.KdGruppe_.GetData(dest.KdGruppe);
    dest.Bezeichnung[0] = ' ';
    src.Bezeichnung_.GetData(dest.Bezeichnung);

    // Bit Map Exporting.
    // Define an array of chars's for exporting data.
    char CharArray[pxCustPermission::cPXCSTPRM_MAPWIDTH];
    src.BMCustPermission_.Export(CharArray,
                                 pxCustPermission::cPXCSTPRM_MAPWIDTH);

    // Copy flag chars into record structure:
    dest.SArtGiftKlasse1    = CharArray[ 0];
    dest.SArtGiftKlasse2    = CharArray[ 1];
    dest.SArtGiftKlasse3    = CharArray[ 2];
    dest.SArtRezeptPfl      = CharArray[ 3];
    dest.SArtApothekenPfl   = CharArray[ 4];
    dest.SArtTaxPfl         = CharArray[ 5];
    dest.SArtOpiat          = CharArray[ 6];
    dest.SArtTierArznei     = CharArray[ 7];

    dest.SArtVertriebsgeb   = CharArray[ 8];
    dest.SArtLieferSperre   = CharArray[ 9];
    dest.SArtAbschlag       = CharArray[10];
    dest.SArtPreisErmaess   = CharArray[11];
    dest.SArtVertriebsbind1 = CharArray[12];
    dest.SArtVertriebsbind2 = CharArray[13];
    dest.SArtVertriebsbind3 = CharArray[14];
    dest.SArtVertriebsbind4 = CharArray[15];

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' structure to a pxCustGroup object.         */
/*----------------------------------------------------------------------------*/
pxCustGroup&
Assign
(
    pxCustGroup&           dest,
    const tKUNDENGRUPPE&   src
)
{
    // Copy native data types:
    dest.KdGruppeSperrKZ_      = src.KdGruppeSperrKZ;
    dest.KdGruppeFreiKZ_       = src.KdGruppeFreiKZ;

    // Strings:
    dest.KdGruppe_             = src.KdGruppe;
    dest.Bezeichnung_          = src.Bezeichnung;

    // Bit Maps:
    // Define an array of chars's for importing data.
    char CharArray[pxCustPermission::cPXCSTPRM_MAPWIDTH];

    // Copy record structure into flag chars:
    CharArray[ 0] = src.SArtGiftKlasse1   ;
    CharArray[ 1] = src.SArtGiftKlasse2   ;
    CharArray[ 2] = src.SArtGiftKlasse3   ;
    CharArray[ 3] = src.SArtRezeptPfl     ;
    CharArray[ 4] = src.SArtApothekenPfl  ;
    CharArray[ 5] = src.SArtTaxPfl        ;
    CharArray[ 6] = src.SArtOpiat         ;
    CharArray[ 7] = src.SArtTierArznei    ;

    CharArray[ 8] = src.SArtVertriebsgeb  ;
    CharArray[ 9] = src.SArtLieferSperre  ;
    CharArray[10] = src.SArtAbschlag      ;
    CharArray[11] = src.SArtPreisErmaess  ;
    CharArray[12] = src.SArtVertriebsbind1;
    CharArray[13] = src.SArtVertriebsbind2;
    CharArray[14] = src.SArtVertriebsbind3;
    CharArray[15] = src.SArtVertriebsbind4;

    // Import flag chars into bitmap:
    dest.BMCustPermission_.Import(CharArray,
                                  pxCustPermission::cPXCSTPRM_MAPWIDTH);

    dest.group_ = atoi(src.KdGruppe);
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustGroup :: Init()
{
    group_ = 0;
    tKUNDENGRUPPE    record;
    memset(&record, 0 , sizeof(tKUNDENGRUPPE));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKUNDENGRUPPE struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxCustGroup&
pxCustGroup :: operator=( const pxCustGroup& src)
{
    tKUNDENGRUPPE record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKUNDENGRUPPE structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxCustGroup&
pxCustGroup :: operator=( const tKUNDENGRUPPE& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustGroup :: Get
(
    DBAccessMode mode
)

{
    tKUNDENGRUPPE record;
    memset(&record, 0, sizeof(tKUNDENGRUPPE));
    KdGruppe_.GetData(record.KdGruppe);
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;             // import the data from tKUNDENGRUPPE struct
    else if ( retval > cDBXR_NORMAL )
       DBCondition(nMessage(CMsgStream(),
                            CMSG_CST_GRP_NOTFOUND,
                            record.KdGruppe, 0),
                   CMSG_CST_GRP_NOTFOUND);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCustGroup :: Put
(
)
{
    tKUNDENGRUPPE record;
    memset(&record, 0, sizeof(tKUNDENGRUPPE));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKUNDENGRUPPE));
}

/*----------------------------------------------------------------------------*/
/*  Queries.                                                                  */
/*----------------------------------------------------------------------------*/
bool
pxCustGroup :: IsDiscountDisabled()
{

    if ( FilialNr_ == 16 )
       return false;

    //if( (const_cast<pxCustGroup*>(this))->Session()->isCroatia() ) //if ( Croatia() )
    if( Session()->isCroatia() ) //if ( Croatia() )
    {
       return ( group_ == 9 || group_ == 13 );
    }
    else
    {
       return ( group_ == 8 || group_ == 9 || group_ == 13 );
    }
}

bool
pxCustGroup :: IsOrderEntryDisabled() const
{
    return ( group_ == 10 || KdGruppeSperrKZ_ == '1');
}

bool
pxCustGroup :: IsWithoutCertificateEnabled() const
{
    return ( group_ == 13 || group_ == 18 );
}

bool
pxCustGroup :: IsNoConsignmentPermission()
{
    if ( Session()->isBulgaria() || Session()->isAustria() ) //if (Session()->isBulgaria()), //if (Session()->isAustria())
    {
        return false;
    }

    return ( group_ == 8 || group_ == 9 );
}

/*bool
pxCustGroup ::  Croatia() const
{
    {return FilialNr_ == 71 || FilialNr_ == 72 ||
            FilialNr_ == 73 || FilialNr_ == 74 ||
            FilialNr_ == 75 || FilialNr_ == 76 ||
            FilialNr_ == 77 ;}
}*/

bool
pxCustGroup :: IsGroupEKGrossoNaBulgaria() const
{
    return ( group_ == 8 || group_ == 9 ||
             group_ == 13 ||  group_ == 17 );
}

bool
pxCustGroup :: IsGroupEKGrossoBulgaria() const
{
    return ( group_ == 12 || group_ == 15 );
}

bool
pxCustGroup :: IsGroupHospital() const
{
    return ( group_ == 6 );
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustGroup :: Read
(
    const void  *record
)
{
    return pxKundenGruppeRead((tKUNDENGRUPPE*)record);
}

int
pxCustGroup :: ReadLock
(
    const void  *record
)
{
    return pxKundenGruppeReadLock((tKUNDENGRUPPE*)record);
}

int
pxCustGroup :: Update
(
    const void  *record
)
{
    return pxKundenGruppeUpdate((tKUNDENGRUPPE*)record);
}

int
pxCustGroup :: Insert
(
    const void  *record
)
{
    return pxKundenGruppeInsert((tKUNDENGRUPPE*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable. Ensures pxCustGroup list  */
/*  objects being inserted in the following ascending sequence: KdGruppe.     */
/*----------------------------------------------------------------------------*/
int
pxCustGroup :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCustGroup *that = (pxCustGroup*)That;
    int retval = KdGruppe_.Compare(that->KdGruppe_);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustGroupList :: pxCustGroupList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}


/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxCustGroupList :: Select
(
    const int     count_
)
{
    tKUNDENGRUPPE record;
    memset(&record, 0, sizeof(tKUNDENGRUPPE));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustGroupList :: AddToList
(
    const void  *recordp,
    const int  /* row */
)
{
    // construct new 'pxCustGroup' object:
    pxCustGroup *objectp = new pxCustGroup(Session(), *(tKUNDENGRUPPE*)recordp);
    InsertAscending(objectp);
    return objectp;
}

int
pxCustGroupList :: EndBrowse
(
    const int  cursorid
)
{
    return pxKundenGruppeEndBrowse(cursorid);
}


int
pxCustGroupList :: GetNext
(
    const void  *recordp,
    const int  cursorid
)
{
    return pxKundenGruppeGetNext((tKUNDENGRUPPE*)recordp, cursorid);
}

int
pxCustGroupList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxKundenGruppeStartBrowse((tKUNDENGRUPPE*)keys, cursorid);
}
