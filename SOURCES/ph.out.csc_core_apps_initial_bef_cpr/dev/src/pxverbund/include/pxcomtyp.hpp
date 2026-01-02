/*(c)
 ********************* PHARMX Customer Commer Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXCOMTYP.HPP
Internal Comm Type Classes.

REVISION HISTORY

21 August 1995 V1.10 REV 00 written by Dietmar Schloetel.
*/

#ifndef PXCOMTYP_INC
#define PXCOMTYP_INC

#include "pxbase/pxrecord.hpp"
#include "types/pickingtypeenum.inc"

struct tKOMMIARTEN;

class pxCommType : public pxDBRecord
{
public:

                pxCommType(pxSession *session);
                pxCommType(pxCommType& src);
                pxCommType(pxSession *session,tKOMMIARTEN& src);
                pxCommType(pxSession *session, const pxCommType* src);
                pxCommType(pxSession *session,char KommiArt,short BranchNo, DBAccessMode mode = cDBGET_READONLY);
    virtual     ~pxCommType();

    pxCommType& operator=(const pxCommType& src);
    pxCommType& operator=(const tKOMMIARTEN& src);

    friend pxCommType& Assign(pxCommType& dest, const tKOMMIARTEN& src);
    friend tKOMMIARTEN&  Assign(tKOMMIARTEN& dest, const pxCommType& src);
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
             int  Compare(const char commiart);
             nString& Bezeichnung()     {return Bezeichnung_;}
             PickingTypeEnum ShipCode() const {return KoMethode_;}
             short BranchNo()          {return BranchNo_;}
             char KoArt() const { return KoArt_; }

             bool  IsNoShipment() const
                   {return (KoMethode_ == ShipNone);}
             bool  IsShipNormal() const
                   {return (KoMethode_ == ShipNormal);}
             bool  IsShipDisposal() const
                   {return (KoMethode_ == ShipDisposal);}
             bool  IsShipUrgent() const
                   {return (KoMethode_ == ShipUrgent);}
             bool  IsShipUrgentExtra() const
                   {return (KoMethode_ == ShipUrgentExtra);}
             bool  IsShipSpecial() const
                   {return (KoMethode_ == ShipSpecial);}
             bool  IsShipSpecialExtra() const
                   {return (KoMethode_ == ShipSpecialExtra);}
             bool  IsShipSpecialSuper() const
                   {return (KoMethode_ == ShipSpecialSuper);}
             bool  IsShipSpecialAnyway() const
                   {return (IsShipSpecialExtra() || IsShipSpecialSuper());}
             bool  IsUrgentAnyway() const
                   {return (IsShipUrgent() || IsShipUrgentExtra() || IsShipSpecial() );}
             bool  IsShipDeliveryNote() const
                   {return (KoMethode_ == ShipDeliveryNote);}

protected:
    void              Init();
    virtual  int     Read(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     ReadLock(const void *record);

    char            KoArt_;                  // Kommissionierungs-Art
    nString         Bezeichnung_;            // Beschreibung in Klartext
    PickingTypeEnum KoMethode_;              // Kommissionierungs-Methode
    short           BranchNo_;               // Branchnumber

private:
    friend class pxCommTypeList;
};
class pxCommTypeList : public nDListCollect, public nDBRecordSet
{
public:
// constructors:
                pxCommTypeList(pxSession *session);
// destructor:
                virtual  ~pxCommTypeList() {Clear();}
             pxSession*  Session()       { return (pxSession*) DataBase();}
             size_t      Select ( const short BranchNo = 0,const int count = 50 );
             void        Clear()        {nDBRecordSet::Clear();}
             pxCommType*  Find( const char KommiArt, const short BranchNo);
             short       Find( const short BranchNo );
    virtual  int     EndBrowse(const int cursorid);
    virtual  nCollectable* AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);

protected:

private:
    friend class pxCommTypeListIter;
};

class pxCommTypeListIter : public nDListCollectIter
{
public:
// constructors:
    pxCommTypeListIter(pxCommTypeList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCommTypeListIter() {;}
};

#endif
