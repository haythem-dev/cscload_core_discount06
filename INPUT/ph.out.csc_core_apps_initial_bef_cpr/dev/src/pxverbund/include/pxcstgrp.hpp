/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXCSTGRP.HPP
Customer Group Class.

REVISION HISTORY

13 Nov 1995 V1.00 REV 00 written by Peter Hoernich.
*/

#ifndef PXCSTGRP_INC
#define PXCSTGRP_INC

#include "pxbase/pxrecord.hpp"
#include "pxcstprm.hpp"

struct tKUNDENGRUPPE;

class pxCustGroup : public pxDBRecord
{
public:
    enum CustomerGroupTypeBG            // customer groups in Bulgaria
    {
        TypePharmacy=1,            // Apotheken
		TypeHospital		   =  6,  // Apothekenbelegschaft (in BG: Krankenhaus)
        TypeExternalWholesaler=8,  // FREMDGROSSHANDEL + ANDERE AG
        TypeOwnBranch=9,           // FILIALE DER EIGENEN AG
                TypeOwnConsumption=13,     // EIGENVERBRAUCH, INT. KONTEN
                TypeOwnConsumptionAep=18,  // EIGENVERBRAUCH,INT.KONTEN AEP
        TypeWholesaler=12          // Groﬂh‰ndler
    };

// destructor:
    virtual           ~pxCustGroup();
// constructors:
                      pxCustGroup(pxCustGroup& src);
                      pxCustGroup(pxSession *session);
                      pxCustGroup(pxSession *session, nString& KdGruppe, short VZ,
                                  DBAccessMode mode = cDBGET_READONLY);

    pxCustGroup&      operator=(const pxCustGroup& src);
//  Assigns the values of 'src' to self and returns a reference to it.
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

//  Queries:
    bool              IsOrderEntryDisabled() const;
    bool              IsDiscountDisabled();
    bool              IsWithoutCertificateEnabled() const;
    bool              IsNoConsignmentPermission() ;
    //bool              Croatia() const;
    bool              IsGroupEKGrossoNaBulgaria() const;
    bool              IsGroupEKGrossoBulgaria() const;
    bool              IsGroupHospital() const;

    nString&          KdGruppe        () {return KdGruppe_;                    }
    nString&          Bezeichnung     () {return Bezeichnung_;                 }
    pxCustPermission& BMCustPermission() {return BMCustPermission_;            }
    char&            KdGruppeSperrKZ () {return KdGruppeSperrKZ_;             }
    char&            KdGruppeFreiKZ  () {return KdGruppeFreiKZ_;              }
        int               CustomerGroup()    {return group_; }


protected:
                      pxCustGroup(pxSession *session, tKUNDENGRUPPE& src);
    pxCustGroup&      operator=(const tKUNDENGRUPPE& src);
    friend
    pxCustGroup&      Assign(pxCustGroup& dest, const tKUNDENGRUPPE& src);
    friend
    tKUNDENGRUPPE&    Assign(tKUNDENGRUPPE& dest, const pxCustGroup& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    void              Init();

    nString           KdGruppe_;        // Kundengruppe
    nString           Bezeichnung_;     // Kundengruppe Text
    char             KdGruppeSperrKZ_; // Kundengruppe SperrKZ
    char             KdGruppeFreiKZ_;  // Kundengruppe FreiKZ
    pxCustPermission  BMCustPermission_;// Bit Map Berechtigungen Kundengruppe
    int               group_;           // binary group number
    short            FilialNr_;        // optional help

private:
    friend class pxCustGroupList;
};

class pxCustGroupList : public nDBRecordSet, public nDListCollect
{

public:
                      virtual ~pxCustGroupList() {Clear();}
                      pxCustGroupList(pxSession *session);
//  member functions:
    void              Clear()           {nDBRecordSet::Clear();}
    size_t            Select(const int count = cDEFAULT);
    pxSession*        Session()         { return (pxSession*) DataBase();}

protected:
    virtual
    nCollectable*     AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxCustGroupListIter;
};

class pxCustGroupListIter : public nDListCollectIter
{

public:
// constructors:
    pxCustGroupListIter(pxCustGroupList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCustGroupListIter() {;}

};

#endif
