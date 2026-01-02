/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxordervalues.hpp
KDAUFTRAGWERTE  class

REVISION HISTORY

08 March 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXORDERVALUES_INC
#define PXORDERVALUES_INC

#include "pxbase/pxrecord.hpp"
#include <money.hpp>

class pxOrderItem;
struct tKDAUFTRAGWERTE;

class pxOrderValues : public pxDBRecord
{
public:
/*----------------------------------------------------------------------------*/
/*  Enumerations TaxLevel                                                     */
/*----------------------------------------------------------------------------*/
    enum TaxLevels
    {
       FullTax,               // 0 Full Tax
       LowTax,                // 1 Low  Tax
	   NoTax,                 // 2 Null Tax
           MAXTAXLEVEL                    // 3 MAXTAXLEVEL for determinate length of array
    };

// constructors:
                pxOrderValues(pxOrderValues& src);
                pxOrderValues(pxSession *session);
                pxOrderValues(pxSession *session, tKDAUFTRAGWERTE& src);
                pxOrderValues(pxSession *session, const pxOrderValues* src);
                pxOrderValues(pxSession *session, long  KdauftragNr);

// destructor:
                virtual  ~pxOrderValues();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxOrderValues&   operator=(const pxOrderValues& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxOrderValues&   operator=(const tKDAUFTRAGWERTE& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxOrderValues&
                Assign(pxOrderValues& dest, const tKDAUFTRAGWERTE& src);
    friend   tKDAUFTRAGWERTE&
                Assign(tKDAUFTRAGWERTE& dest, const pxOrderValues& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Delete();

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);

// Update Fields
    void              SetKdAuftragNr(const long KdAuftragNr){ KdAuftragNr_ = KdAuftragNr; SetDirty();}

// some methodes
    int              CalcOrderValues( pxOrderItem* item );
    int              ReduceOrderValues ( pxOrderItem* item, long Qty );
    int              InitOrderValues();

//  Queries:
    long             KdAuftragNr()        { return KdAuftragNr_                  ;}
    //nMoney            OrdValFtaxFSDisc()   { return OrdValFtaxFSDisc_             ;}

    nMoney            OrdValFtaxFSDisc()   { return OrderValueTaxFSDisc_[pxOrderValues::FullTax];}
    nMoney            OrdValFtaxFS()       { return OrderValueTaxFSShip_[pxOrderValues::FullTax];}
    nMoney            OrdValLtaxFSDisc()   { return OrderValueTaxFSDisc_[pxOrderValues::LowTax];}
    nMoney            OrdValLtaxFS()       { return OrderValueTaxFSShip_[pxOrderValues::LowTax];}
    nMoney            TaxValFtaxFSDisc()   { return TaxValueFSDisc_[pxOrderValues::FullTax];}
    nMoney            TaxValFtaxFS()       { return TaxValueFSShip_[pxOrderValues::FullTax];}
    nMoney            TaxValLtaxFSDisc()   { return TaxValueFSDisc_[pxOrderValues::LowTax];}
    nMoney            TaxValLtaxFS()       { return TaxValueFSShip_[pxOrderValues::LowTax];}
    nMoney            OrdValGrossFS()      { return OrdValFtaxFS() + OrdValLtaxFS() + OrdValNtaxFS();}
	nMoney            OrdValNetFS()        { return (OrdValFtaxFS() - TaxValFtaxFS()) + (OrdValLtaxFS() - TaxValLtaxFS()) + (OrdValNtaxFS() - TaxValNtaxFS()); }

    nMoney            OrdValFtaxHFDisc()   { return OrderValueTaxHFDisc_[pxOrderValues::FullTax];}
    nMoney            OrdValFtaxHF()       { return OrderValueTaxHFShip_[pxOrderValues::FullTax];}
    nMoney            OrdValLtaxHFDisc()   { return OrderValueTaxHFDisc_[pxOrderValues::LowTax];}
    nMoney            OrdValLtaxHF()       { return OrderValueTaxHFShip_[pxOrderValues::LowTax];}
    nMoney            TaxValFtaxHFDisc()   { return TaxValueHFDisc_[pxOrderValues::FullTax];}
    nMoney            TaxValFtaxHF()       { return TaxValueHFShip_[pxOrderValues::FullTax];}
    nMoney            TaxValLtaxHFDisc()   { return TaxValueHFDisc_[pxOrderValues::LowTax];}
    nMoney            TaxValLtaxHF()       { return TaxValueHFShip_[pxOrderValues::LowTax];}
    nMoney            OrdValGrossHF()      { return OrdValFtaxHF() + OrdValLtaxHF();}
    nMoney            OrdValNetHF()        { return (OrdValFtaxHF() - TaxValFtaxHF())  + ( OrdValLtaxHF() - TaxValLtaxHF() ) + ( OrdValNtaxHF() - TaxValNtaxHF());}

    nMoney            OrdValFtaxRSDisc()   { return OrderValueTaxRTDisc_[pxOrderValues::FullTax];}
    nMoney            OrdValFtaxRS()       { return OrderValueTaxRTShip_[pxOrderValues::FullTax];}
    nMoney            OrdValLtaxRSDisc()   { return OrderValueTaxRTDisc_[pxOrderValues::LowTax];}
    nMoney            OrdValLtaxRS()       { return OrderValueTaxRTShip_[pxOrderValues::LowTax];}
    nMoney            TaxValFtaxRSDisc()   { return TaxValueRTDisc_[pxOrderValues::FullTax];}
    nMoney            TaxValFtaxRS()       { return TaxValueRTShip_[pxOrderValues::FullTax];}
    nMoney            TaxValLtaxRSDisc()   { return TaxValueRTDisc_[pxOrderValues::LowTax];}
    nMoney            TaxValLtaxRS()       { return TaxValueRTShip_[pxOrderValues::LowTax];}
    nMoney            OrdValGrossRS()      { return OrdValFtaxRS() + OrdValLtaxRS();}
    nMoney            OrdValNetRS()        { return (OrdValFtaxRS() - TaxValFtaxRS())  + (OrdValLtaxRS() - TaxValLtaxRS()) + (OrdValNtaxRS() - TaxValNtaxRS());}

	nMoney            OrdValNtaxFSDisc()  { return OrderValueTaxFSDisc_[pxOrderValues::NoTax]; }
	nMoney            OrdValNtaxFS()      { return OrderValueTaxFSShip_[pxOrderValues::NoTax]; }
	nMoney            TaxValNtaxFSDisc()  { return TaxValueFSDisc_[pxOrderValues::NoTax]; }
	nMoney            TaxValNtaxFS()      { return TaxValueFSShip_[pxOrderValues::NoTax]; }
	nMoney            OrdValNtaxHFDisc()  { return OrderValueTaxHFDisc_[pxOrderValues::NoTax]; }
	nMoney            OrdValNtaxHF()      { return OrderValueTaxHFShip_[pxOrderValues::NoTax]; }
	nMoney            TaxValNtaxHFDisc()  { return TaxValueHFDisc_[pxOrderValues::NoTax]; }
	nMoney            TaxValNtaxHF()      { return TaxValueHFShip_[pxOrderValues::NoTax]; }
	nMoney            OrdValNtaxRSDisc()  { return OrderValueTaxRTDisc_[pxOrderValues::NoTax]; }
	nMoney            OrdValNtaxRS()      { return OrderValueTaxRTShip_[pxOrderValues::NoTax]; }
	nMoney            TaxValNtaxRSDisc()  { return TaxValueRTDisc_[pxOrderValues::NoTax]; }
	nMoney            TaxValNtaxRS()      { return TaxValueRTShip_[pxOrderValues::NoTax]; }

// Set Methodes


protected:
    void        Init();

    long       KdAuftragNr_        ;      // Kundenauftragsnummer

    nMoney      OrderValueFSDisc_[MAXTAXLEVEL];      // Order value for freesales items based on discounted prices (FS)
    nMoney      OrderValueFSShip_[MAXTAXLEVEL];      // Order value for freesales items based on normal prices (FS)
    nMoney      TaxValueFSDisc_[MAXTAXLEVEL];        // Tax value for freesales items based on discounted prices (FS)
    nMoney      TaxValueFSShip_[MAXTAXLEVEL];        // Tax value for freesales items based on normal prices (FS)
    nMoney      OrderValueTaxFSDisc_[MAXTAXLEVEL];      // Order value for freesales items based on discounted prices including tax (FS)
    nMoney      OrderValueTaxFSShip_[MAXTAXLEVEL];      // Order value for freesales items based on normal prices including tax (FS)

    nMoney      OrderValueHFDisc_[MAXTAXLEVEL];      // Order value for health fund items based on discounted prices (HF)
    nMoney      OrderValueHFShip_[MAXTAXLEVEL];      // Order value for health fund items based on normal prices (HF)
    nMoney      TaxValueHFDisc_[MAXTAXLEVEL];        // Tax value for health fund  items based on discounted prices (HF)
    nMoney      TaxValueHFShip_[MAXTAXLEVEL];        // Tax value for health fund  items based on normal prices (HF)
    nMoney      OrderValueTaxHFDisc_[MAXTAXLEVEL];      // Order value for health fund items based on discounted prices including tax (HF)
    nMoney      OrderValueTaxHFShip_[MAXTAXLEVEL];      // Order value for health fund items based on normal prices including tax (HF)

    nMoney      OrderValueRTDisc_[MAXTAXLEVEL];      // Order value for retail items based on discounted prices (RT)
    nMoney      OrderValueRTShip_[MAXTAXLEVEL];      // Order value for retail items based on normal prices (RT)
    nMoney      TaxValueRTDisc_[MAXTAXLEVEL];        // Tax value for retail  items based on discounted prices (RT)
    nMoney      TaxValueRTShip_[MAXTAXLEVEL];        // Tax value for retail  items based on normal prices (RT)
    nMoney      OrderValueTaxRTDisc_[MAXTAXLEVEL];      // Order value for retail items based on discounted prices including tax (RT)
    nMoney      OrderValueTaxRTShip_[MAXTAXLEVEL];      // Order value for retail items based on normal prices including tax (RT)

    nMoney      OrdValFtaxFSDisc_   ;      // Order Value Full Tax FS Price with Rebate
    nMoney      OrdValFtaxFS_       ;      // Order Value Full Tax FS Price without Rebate
    nMoney      OrdValLtaxFSDisc_   ;      // Order Value Low  Tax FS Price with Rebate
    nMoney      OrdValLtaxFS_       ;      // Order Value Low  Tax FS Price without Rebate
    nMoney      OrdValFtaxHFDisc_   ;      // Order Value Full Tax HF Price with Rebate
    nMoney      OrdValFtaxHF_       ;      // Order Value Full Tax HF Price without Rebate
    nMoney      OrdValLtaxHFDisc_   ;      // Order Value Low  Tax HF Price with Rebate
    nMoney      OrdValLtaxHF_       ;      // Order Value Low  Tax HF Price without Rebate
    nMoney      TaxValFtaxFSDisc_   ;      // Tax  full tax FS with rebate(Fakturpreis)
    nMoney      TaxValFtaxFS_       ;      // Tax  full tax FS without rebate(Fakturpreis)
    nMoney      TaxValLtaxFSDisc_   ;      // Tax  low  tax FS with rebate(Fakturpreis)
    nMoney      TaxValLtaxFS_       ;      // Tax  low  tax FS without rebate(Fakturpreis)
    nMoney      TaxValFtaxHFDisc_   ;      // Tax  full tax HF with rebate(Fakturpreis)
    nMoney      TaxValFtaxHF_       ;      // Tax  full tax HF without rebate(Fakturpreis)
    nMoney      TaxValLtaxHFDisc_   ;      // Tax  low  tax HF with rebate(Fakturpreis)
    nMoney      TaxValLtaxHF_       ;      // Tax  low  tax HF without rebate(Fakturpreis)
    nMoney      OrdValFtaxRSDisc_   ;      // Order Value Full Tax RS Price with Rebate
    nMoney      OrdValFtaxRS_       ;      // Order Value Full Tax RS Price without Rebate
    nMoney      OrdValLtaxRSDisc_   ;      // Order Value Low  Tax RS Price with Rebate
    nMoney      OrdValLtaxRS_       ;      // Order Value Low  Tax RS Price without Rebate
    nMoney      TaxValFtaxRSDisc_   ;      // Tax  full tax RS with rebate(Fakturpreis)
    nMoney      TaxValFtaxRS_       ;      // Tax  full tax RS without rebate(Fakturpreis)
    nMoney      TaxValLtaxRSDisc_   ;      // Tax  low  tax RS with rebate(Fakturpreis)
    nMoney      TaxValLtaxRS_       ;      // Tax  low  tax RS without rebate(Fakturpreis)
	nMoney      OrdValNtaxFSDisc_   ;      // Order Value Null Tax FS Price with Rebate
	nMoney      OrdValNtaxFS_       ;      // Order Value Null Tax FS Price without Rebate
	nMoney      OrdValNtaxHFDisc_   ;      // Order Value Null Tax HF Price with Rebate
	nMoney      OrdValNtaxHF_       ;      // Order Value Null Tax HF Price without Rebate
	nMoney      OrdValNtaxRSDisc_   ;      // Order Value Null Tax RS Price with Rebate
	nMoney      OrdValNtaxRS_       ;      // Order Value Null Tax RS Price without Rebate
	nMoney      TaxValNtaxFSDisc_   ;      // Tax  Null tax FS with rebate(Fakturpreis)
	nMoney      TaxValNtaxFS_       ;      // Tax  Null tax FS without rebate(Fakturpreis)
	nMoney      TaxValNtaxHFDisc_   ;      // Tax  Null tax HF with rebate(Fakturpreis)
	nMoney      TaxValNtaxHF_       ;      // Tax  Null tax HF without rebate(Fakturpreis)
	nMoney      TaxValNtaxRSDisc_   ;      // Tax  Null tax RS with rebate(Fakturpreis)
	nMoney      TaxValNtaxRS_       ;      // Tax  Null tax RS without rebate(Fakturpreis)




private:
    friend class pxOrderValuesList;
};

class pxOrderValuesList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxOrderValuesList(pxSession *session);
//  destructor:
                virtual ~pxOrderValuesList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const long  KdAuftragNr,
                         const int   count  = 1000
                       );
// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxOrderValuesListIter;
};

class pxOrderValuesListIter : public nDListCollectIter
{

public:
// constructors:
    pxOrderValuesListIter(pxOrderValuesList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxOrderValuesListIter() {;}
};
#endif
