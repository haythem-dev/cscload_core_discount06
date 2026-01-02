/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXDELLOG.HPP
Alternate Deliver Position Class.

REVISION HISTORY

06 April 1998 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXDELLOG_INC
#define PXDELLOG_INC

#include "pxbase/pxrecord.hpp"
#include <clock.hpp>
#include <date.hpp>

class pxOrderItem;

namespace pxVerbund
{
    namespace subsequentDelivery
    {
        class pxDeliveryPos;
    }
}
    
struct tNACHLIEFPROT;

//namespace pxVerbund
//{
//    namespace subsequentDelivery
//    {

class pxDeliveryLog : public pxDBRecord
{

public:


    enum pxDelLogTyp
    {
        pxDLT_UNDEFINED,                    // undefined type
        pxDLT_AUXDELIVERY_ITEM,             // auxdelivery
        pxDLT_DISPOSAL_ITEM,                // disposal
        pxDLT_RESTDELIVERY_ITEM,            // restdelivery
        pxDLT_BATCH_ITEM
    };


    enum pxDelLogStat
    {
        pxDLS_UNDEFINED,                    // indefined
        pxDLS_DELETED,                      // deleted
        pxDLS_QUANTITY_CHANGE,              // quantity changed
        pxDLS_DELIVERY_POSSIBLE             // delivery possible
    };

// constructors:
                pxDeliveryLog(pxDeliveryLog& src);
                pxDeliveryLog(pxSession *session);
                pxDeliveryLog(pxSession *session, tNACHLIEFPROT& src);
                pxDeliveryLog(pxOrderItem& Item, pxVerbund::subsequentDelivery::pxDeliveryPos& Dpos);

// destructor:
                virtual  ~pxDeliveryLog();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxDeliveryLog&   operator=(const pxDeliveryLog& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxDeliveryLog&   operator=(const tNACHLIEFPROT& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxDeliveryLog&
                Assign(pxDeliveryLog& dest, const tNACHLIEFPROT& src);
    friend   tNACHLIEFPROT&
                Assign(tNACHLIEFPROT& dest, const pxDeliveryLog& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Put();
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);


//  Queries:
    long             ArtikelNr()       const {return ArtikelNr_         ;}
    long             IDFNr()           const {return IDFNr_             ;}
    long             MengeAlt()        const {return MengeAlt_          ;}
    short            AnderungsTyp()    const {return AenderungsTyp_     ;}
    short            PosTyp()          const {return PosTyp_            ;}
    const nDate&     Datum()           const {return Datum_             ;}
    long             PosNr()           const {return PosNr_             ;}
    long             KdAuftragNr()     const {return KdAuftragNr_       ;}
    const nClock&    Zeit()            const {return Zeit_              ;}
    const nDate&     DatumNeu()        const {return DatumNeu_          ;}
    long             KdAuftragNrNeu()  const {return KdAuftragNrNeu_    ;}
    long             MengeAktuell()    const {return MengeAktuell_      ;}
    long             MengeGeliefert()  const {return MengeGeliefert_    ;}
    long             MengeNeu()        const {return MengeNeu_          ;}
    long             Uid()             const {return Uid_               ;}
    short            UserBranchNo()    const {return UserBranchNo_      ;}

protected:
    void        Init();

    long       ArtikelNr_         ;      // Artikelnummer
    long       IDFNr_             ;      // Kundennummer
    long       MengeAlt_          ;      // Menge alt
    short      AenderungsTyp_     ;      // Aenderungstyp
    short      PosTyp_            ;      // Positionstyp
    nDate      Datum_             ;      // Datum
    long       PosNr_             ;      // Positionsnummer
    long       KdAuftragNr_       ;      // Kunden Auftragsnummer
    nClock     Zeit_              ;      // Zeit
    nDate      DatumNeu_          ;      // Datum neu
    long       KdAuftragNrNeu_    ;      // Kunden Auftragsnummer neu
    long       MengeAktuell_      ;      // Menge Aktuell
    long       MengeGeliefert_    ;      // Menge geliefert
    long       MengeNeu_          ;      // Menge neu
    long       Uid_               ;      // Userid
    short      UserBranchNo_      ;      // Menge neu
private:
    friend class pxDeliveryLogList;

};
class pxDeliveryLogList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxDeliveryLogList(pxSession *session);
//  destructor:
                virtual ~pxDeliveryLogList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 500 );
    size_t      Select ( const long KdAuftragNr,
                         const long ArtikelNr,
                         const int     count = 500 );

    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);
	    
protected:

private:
    friend class pxDeliveryLogListIter;
};

class pxDeliveryLogListIter : public nDListCollectIter
{

public:
// constructors:
    pxDeliveryLogListIter(pxDeliveryLogList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxDeliveryLogListIter() {;}
};

//    } // end namespace subsequentDelivery
//} // end namespace pxVerbund

#endif
