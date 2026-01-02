/*----------------------------------------------------------------------------*/
// PXCUSTOMERGRPFLAGS
// Customer Group Class.
/*----------------------------------------------------------------------------*/

#ifndef PXCUSTOMERGRPFLAGS_INC
#define PXCUSTOMERGRPFLAGS_INC

#include "pxbase/pxrecord.hpp"

struct tCUSTOMERGRPFLAGS;

class pxCustomerGrpFlags : public pxDBRecord
{
public:
    enum CustomerGrpFlagTypes       // CustomerGroup Flagtypes
    {
       KscDiscountEnabled         = 1, // Discount enabled for KSC applications
       EKGrossoNaEnabled          = 3, // EKGrossoNa enabled(NOT USED)
       EKGrossoEnabled               , // EKGrosso   enabled(NOT USED)
       WithoutCertificateEnabled     , // WithoutCertificate enabled
       NoConsignmentPermission       , // NoConsignmentPermission
       StotinkiEnabled               , // Stotinki
       NoDiminishDiscount            , // Do not reduce Discount
       NoReduceDiscountForExclusiveArticle, // Do not reduce discount for ExclusiveArticle
       GroupPriceBase,                  // PriceBase: 0 = AEP,1 = GEP,2 = GEPNA, 3 = DGEP
       GroupNoSalesTax,                 // Customer Group no SalesTax
       GroupNoQuotaInheritance          // no article Quota inheritance
    };

    enum GroupBasePrice                // CustomerGroup BasePrice
    {
       GroupBasePriceAEP             , // GroupBasePrice AEP
       GroupBasePriceGEP             , // GroupBasePrice GEP
       GroupBasePriceGEPNA           , // GroupBasePrice GEPNA
       GroupBasePriceDGEP              // GroupBasePrice DGEP?????
    };

// destructor:
    virtual           ~pxCustomerGrpFlags();
// constructors:
                      pxCustomerGrpFlags(pxCustomerGrpFlags& src);
                      pxCustomerGrpFlags(pxSession *session);
                      pxCustomerGrpFlags(pxSession *session, short BranchNo, short CustomerGroupNo,
                                  DBAccessMode mode = cDBGET_READONLY);

    pxCustomerGrpFlags&      operator=(const pxCustomerGrpFlags& src);
//  Assigns the values of 'src' to self and returns a reference to it.
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

//  Queries:

    short            BranchNo        () {return BranchNo_;                    }
    short            CustomerGroupNo () {return CustomerGroupNo_;             }
    short            CustGrpFlagType () {return CustGrpFlagType_;             }
    short            CustomerGrpFlag () {return CustomerGrpFlag_;             }


protected:
                      pxCustomerGrpFlags(pxSession *session, tCUSTOMERGRPFLAGS& src);
    pxCustomerGrpFlags&      operator=(const tCUSTOMERGRPFLAGS& src);
    friend
    pxCustomerGrpFlags&      Assign(pxCustomerGrpFlags& dest, const tCUSTOMERGRPFLAGS& src);
    friend
    tCUSTOMERGRPFLAGS&    Assign(tCUSTOMERGRPFLAGS& dest, const pxCustomerGrpFlags& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    void              Init();

    short            BranchNo_;        // Branchno
    short            CustomerGroupNo_; // Kundengruppe
    short            CustGrpFlagType_; // Flagtype
    short            CustomerGrpFlag_; // Flag on/off

private:
    friend class pxCustomerGrpFlagsList;
};

class pxCustomerGrpFlagsList : public nDBRecordSet, public nDListCollect
{

public:
                      virtual ~pxCustomerGrpFlagsList() {Clear();}
                      pxCustomerGrpFlagsList(pxSession *session);
//  member functions:
    bool              IsKscDiscountEnabled();
    bool              IsWithoutCertificateEnabled();
    bool              IsNoConsignmentPermission();
    bool              IsNoDiminishDiscount();
    bool              IsStotinkiEnabled();
    bool              IsNoReduceDiscountForExclusiveArticle();
    bool              isGroupBasePriceAEP();
    bool              isGroupBasePriceGEP();
    bool              isGroupBasePriceGEPNA();
    bool              isGroupBasePriceDGEP();
    bool              isGroupNoQuotaInheritance();
    void              Clear()           {nDBRecordSet::Clear();}
    size_t            Select(const int count = cDEFAULT);
    size_t            Select(const short BranchNo,const short CustomerGroupNo, const int count = cDEFAULT);
    pxCustomerGrpFlags* Find(const short FlagType );
    pxSession*        Session()         { return (pxSession*) DataBase();}

protected:
    virtual
    nCollectable*     AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxCustomerGrpFlagsListIter;
};

class pxCustomerGrpFlagsListIter : public nDListCollectIter
{

public:
// constructors:
    pxCustomerGrpFlagsListIter(pxCustomerGrpFlagsList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCustomerGrpFlagsListIter() {;}

};

#endif
