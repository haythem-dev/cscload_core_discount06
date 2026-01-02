#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxoeparm.hpp"
//#include "pxcountrycodes.hpp"
#include "pxbranch.hpp"
#include "pxvartikellokal.hpp"
#include "pxvartikellokallist.hpp"
#include "pxarticlequota.hpp"
#include "tourutil.hpp"

extern bool pxGlobalIBTNoTimeCheck;

/*-----------------------------------------------------------------------------------------------------*/
pxVartikelLokalList::pxVartikelLokalList(pxSession* session, pxOrderEntryParamPtr param)
    : nDBRecordSet(session), m_OrderEntryParameter( param )
{
    nDBSetList(this);
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
pxVartikelLokalList* pxVartikelLokalList::getIBTWarehouseStockList(
    const long articleno, const short branchno, long customerno, pxOrder* order)
{
    return getIBTWarehouseStockList(articleno, branchno, customerno, (pxGlobalIBTNoTimeCheck ? 0 : 1), order);
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
pxVartikelLokalList* pxVartikelLokalList::getIBTWarehouseStockListWithoutTimeCheck(
    const long articleno, const short branchno, long customerno, pxOrder* order)
{
    return getIBTWarehouseStockList(articleno, branchno, customerno, 0, order);
}
/*-----------------------------------------------------------------------------------------------------*/

pxVartikelLokalList* pxVartikelLokalList::getIBTWarehouseStockList(
    long const articleno, short const branchno, long customerno, short checkTimeTypes, pxOrder* order)
{
    ClearError();

    m_CheckTimeTypes = checkTimeTypes;

    IBTBranchesSelect( branchno, articleno);
    if (Entries() > 0)
    {
        CheckArticleQuota( articleno, branchno, customerno );
        ShrinkDoubleEntriesAndBranchesWithoutStock();
        ShrinkBranchesWithTransportExclusion(order);
    }
    return this;
}

pxVartikelLokalList* pxVartikelLokalList::getIBTWarehouseStockListGeneral(const long articleno, const short branchno)
{
    ClearError();

    m_CheckTimeTypes = 0;

    IBTBranchesSelectGeneral( branchno, articleno);
    if( Entries() > 0 )
    {
        applyArticleQuotas(branchno);
        ShrinkDoubleEntriesAndBranchesWithoutStock( false );
        ShrinkBranchesWithTransportExclusion(NULL);
    }

    return this;
}

/*-----------------------------------------------------------------------------------------------------*/
pxVartikelLokal* pxVartikelLokalList::Find( const short FilialNr )
{
    pxVartikelLokalListIter   iter( *this );  // define iterator
    pxVartikelLokal          *entryp;         // pointer to listentry

    iter.Reset();                           // top of list
    while ( ( entryp = ( pxVartikelLokal *) ++iter) != NULL ) // browse list
    {
        if ( entryp->FilialNr() == FilialNr )
            break;
    }
    return   entryp;                           // return entrypointer
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
pxVartikelLokal* pxVartikelLokalList::FindArticleNo( const long ArtikelNr )
{
    pxVartikelLokalListIter   iter( *this );  // define iterator
    pxVartikelLokal          *entryp;         // pointer to listentry

    iter.Reset();                           // top of list
    while ( ( entryp = ( pxVartikelLokal *) ++iter) != NULL ) // browse list
    {
        if ( entryp->ArtikelNr() == ArtikelNr )
            break;
    }
    return   entryp;                           // return entrypointer
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
pxVartikelLokal* pxVartikelLokalList::QuantityInList( const long q )
{
    /*  QuantityInList returns a pointer to that pxVartikelLokal entry with the highest quantity in stock.  NULLP returns, if nothing available at all    */
    pxVartikelLokalListIter   iter(*this );  // iterator storelist
    pxVartikelLokal          *entryp;        // entry pointer
    short                     company = 0;   // Company with highest q
    long                      qh = 0;        // Highest q

    iter.Reset();                            // top of list
    while ( ( entryp = ( pxVartikelLokal *) ++iter) != NULL )
    {
        if ( (entryp->Bestand() != 0) && (qh < entryp->Bestand()) )
        {
            qh      = entryp->Bestand();
            company = entryp->FilialNr();
        }
        if ( q <= entryp->Bestand() )
            break;
    }

    if (qh )
        entryp = Find(company);
    return entryp;
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
pxVartikelLokal* pxVartikelLokalList::GetPreferedEntry( const long q, const short cfil )
{
    /*
        GetPreferedEntry returns a pointer to the pxVartikelLokal entry wich matches the Companynumber, but just if the available quantity in that
        entry does satisfy the quantity wanted, otherwise this functions returns  a pointer to the entry with the highest quantity on stock
    */
    pxVartikelLokal* entryp = Find(cfil);               // entry pointer
    if ((entryp != NULL) && (entryp->Bestand() >= q))   // find specified entry; enough ?
    {
        return entryp;  // ok
    }
    return QuantityInList(q); // entry with highest availability
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
pxVartikelLokal* pxVartikelLokalList::QSatisfy( const long q, const short FilialNr )
{
    /* QSatisfy returns a pointer to that pxVartikelLokal entry which satifies the wanted quantity, otherwise NULL returns. Stock in Filialnr is ignored. */
    pxVartikelLokalListIter    iter(*this );
    pxVartikelLokal           *entryp;
    iter.Reset();
    while ( ( entryp = ( pxVartikelLokal *) ++iter) != NULL )
    {
        if ( (q <= entryp->Bestand()) && !(entryp->FilialNr() == FilialNr) )
        {
            break;
        }
    }
    return entryp;
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
int pxVartikelLokalList::Shrink( const short FilialNr )
{
    /* Shrink removes all entries from the list where the entryp->FilialNr is not equal with param FilialNr */
    pxVartikelLokalListIter   cursor(*this);
    pxVartikelLokal           *entryp;

    cursor.Reset();
    while ( ( entryp = ( pxVartikelLokal *) ++cursor) != NULL )
    {
        if ( entryp->FilialNr() == FilialNr )
        {
            delete cursor.Remove();      // remove non auxstocked product
        }
    }
    return static_cast<int>(Entries());
}
/*-----------------------------------------------------------------------------------------------------*/

int pxVartikelLokalList::ShrinkBranchesWithTransportExclusion(pxOrder* order)
{
    if( !order )
    {
        return static_cast<int>(Entries());
    }

    if( m_OrderEntryParameter->IsUseTourManagerWithTransportExclusion() )
    {
        bool deliverable = true;
        pxVartikelLokalListIter   cursor(*this);
        pxVartikelLokal           *entryp;
        cursor.Reset();
        while ( ( entryp = ( pxVartikelLokal *) ++cursor) != NULL )
        {
            entryp->getIBTDeliveryDateTime( order, deliverable );
            if( !deliverable )
            {
                delete cursor.Remove();      // remove products which cannot be delivered
            }
        }
    }

    return static_cast<int>(Entries());
}

/*-----------------------------------------------------------------------------------------------------*/
void pxVartikelLokalList::applyArticleQuotas(const short branchno)
{
    pxVartikelLokalListIter   cursor(*this);
    pxVartikelLokal           *entryp;
    cursor.Reset();
    while ( ( entryp = ( pxVartikelLokal *) ++cursor) != NULL )
    {
        entryp->applyArticleQuota(branchno);
    }
}


/*-----------------------------------------------------------------------------------------------------*/
int pxVartikelLokalList::ShrinkDoubleEntriesAndBranchesWithoutStock( bool removeStockLevel0 /*= true */ )
{
    /*  ShrinkDoubleEntries  removes all double entries within this list */
    pxVartikelLokalListIter cursor(*this);
    pxVartikelLokal* entryp;
    cursor.Reset();
    while ( ( entryp = ( pxVartikelLokal *) ++cursor) != NULL )
    {
        if ( removeStockLevel0 && (0 == entryp->Bestand()) )
        {
            delete cursor.Remove();
            continue;
        }

        if( m_OrderEntryParameter->IsNlevelIBT() )
        {
            if( hasEntriesWithHigherNLevelIBTType( entryp->FilialNr(), entryp->getNLevelIBTTypeId() ) )
            {
                delete cursor.Remove();
                continue;
            }
        }
        else
        {
            if ( CountEntries(entryp->FilialNr(), entryp->getNLevelIBTTypeId()) > 1 )
            {
                delete cursor.Remove();      // remove non auxstocked product
                continue;
            }
        }
    }
    return static_cast<int>(Entries());
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
int pxVartikelLokalList::CountEntries( const short FilialNr, const short NLevelIBTTypeId)
{
    pxVartikelLokalListIter cursor(*this);
    pxVartikelLokal* entryp;
    int count_ = 0;
    cursor.Reset();
    while ( ( entryp = ( pxVartikelLokal *) ++cursor) != NULL )
    {
        if ( entryp->FilialNr() == FilialNr )
        {
            if( m_OrderEntryParameter->IsNlevelIBT() )
            {
                if( entryp->getNLevelIBTTypeId() == NLevelIBTTypeId )
                {
                    ++count_;
                }
            }
            else
            {
                ++count_;
            }
        }
    }
    return count_;
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
bool pxVartikelLokalList::hasEntriesWithHigherNLevelIBTType(const short FilialNr, const short NLevelIBTTypeId)
{
    pxVartikelLokalListIter iter(*this);
    pxVartikelLokal* item;
    iter.Reset();

    bool retval = false;

    int countentries = 0;

    while( (item = (pxVartikelLokal*) ++iter) != NULL )
    {
        if( item->FilialNr() == FilialNr )
        {
            if( item->getNLevelIBTTypeId() < NLevelIBTTypeId && item->getNLevelIBTTypeId() != 0 )
            {
                retval = true;
                break;
            }
            if( item->getNLevelIBTTypeId() == NLevelIBTTypeId && item->getNLevelIBTTypeId() != 0 )
            {
                ++countentries;
            }
        }
    }

    if( countentries > 1 )
    {
        retval = true;
    }

    return retval;
}

/*-----------------------------------------------------------------------------------------------------*/
int pxVartikelLokalList::CheckArticleQuota(const long ArtikelNr, const short FilialNr, const long IDFNr )
{
    pxVartikelLokalListIter   cursor(*this);       // iterator article storeloclist
    pxVartikelLokal           *entryp;             // vartikellokal entry pointer
    pxArticleQuota            *Vquotap = NULL;     // pointer to shuttle customers articlequota
    pxArticleQuota            *Iquotap = NULL;     // pointer to customers quota articlequota
    long BGANr = Session()->Branch()->BGANr_EK();  // Verbundkunde
    long IquotaRest = -1;
    long VquotaRest = -1;

    // First find ordering customers (IDFNr) articlequota entry
    if ( Entries() > 0 )
    {
        Iquotap = new pxArticleQuota(Session(), FilialNr, IDFNr, ArtikelNr);
        if (Iquotap->FindQuotaEntry(cDBGET_READONLY))
        {
            delete Iquotap;
        }
        else
        {
            IquotaRest = Iquotap->Quota() - Iquotap->KumQty();
            IquotaRest = ((IquotaRest < 0) ? 0 : IquotaRest);
            delete Iquotap;
        }
    }

    cursor.Reset();                          // top of artstoreloclist
    while ( ( entryp = ( pxVartikelLokal *) ++cursor) != NULL ) // browse list
    {
        // Find articlequota entry for the Verbundkunde within foreign branch (entryp->FilialNr())
        Vquotap = new pxArticleQuota( Session(), entryp->FilialNr(), BGANr, entryp->ArtikelNr() );
        if ( Vquotap->Get() )            // no entry found
        {
            delete Vquotap;
            Vquotap = NULL;
            if ( (IquotaRest >= 0) && (entryp->Bestand() > IquotaRest) )    // take customers quota entry
            {
                entryp->SetQuantity( IquotaRest );
            }
            continue;
        }
        // Entry found for Verbundkund within foreign branch
        VquotaRest = Vquotap->Quota() - Vquotap->KumQty();
        VquotaRest = ((VquotaRest < 0) ? 0 : VquotaRest);
        if ( VquotaRest <= IquotaRest || IquotaRest == -1 ) //Kunde hat kein Quota - Initialwert beachten
        {
            if ( entryp->Bestand() > VquotaRest )
            {
                entryp->SetQuantity( VquotaRest );
            }
        }
        else
        {
            if ( entryp->Bestand() > IquotaRest )
            {
                entryp->SetQuantity( IquotaRest );
            }
        }
        delete Vquotap;
    }
    return static_cast<int>(Entries());
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
nCollectable* pxVartikelLokalList::AddToList( const void *record, const int /* row */ )
{
    pxVartikelLokal *objectp = new pxVartikelLokal(Session(), *(tVARTIKELLOKAL*) record);
    InsertAscending(objectp);
    return objectp;
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
size_t pxVartikelLokalList::IBTBranchesSelect( const short branchno, const long articleno, const int count_ /*= 500*/ )
{
    tVARTIKELLOKAL fil;
    memset(&fil, 0, sizeof(tVARTIKELLOKAL));
    fil.FilialNr = branchno;
    fil.ArtikelNr = articleno;
    int cursorid = cCRS_IBTBRANCHES;

    // NLevelIBT -> IBTBranchesSelect für N-Level-Verbund
    if( m_OrderEntryParameter->IsNlevelIBT() )
    {
        cursorid = cCRS_IBTBRANCHES_NLEVELIBT;
    }

    nDBSelect(&fil, cursorid, count_);
    return Entries();
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
size_t pxVartikelLokalList::IBTBranchesSelectGeneral( const short branchno, const long articleno, const int count_ /* = 500*/ )
{
    tVARTIKELLOKAL fil;
    memset(&fil, 0, sizeof(tVARTIKELLOKAL));
    fil.FilialNr = branchno;
    fil.ArtikelNr = articleno;
    int cursorid = cCRS_IBTBRANCHES_NLEVELIBT_INACTIVE; // SELECT also entries for branches with inactive IBT period
    nDBSelect(&fil, cursorid, count_);
    return Entries();
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
int pxVartikelLokalList::StartBrowse( const void *keys, const int cursorid )
{
    short useview = 0;
    return pxVartikelLokalStartBrowse( (tVARTIKELLOKAL*)keys, m_CheckTimeTypes, useview,
        static_cast<short>(TourUtil::getCurrentWeekday()), (TourUtil::getLongTime(TourUtil::getCurrentTime()) * 100), cursorid );
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
int pxVartikelLokalList::GetNext( const void *record, const int  cursorid )
{
    return pxVartikelLokalGetNext( (tVARTIKELLOKAL*)record, cursorid );
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
int pxVartikelLokalList::EndBrowse( const int cursorid )
{
    return pxVartikelLokalEndBrowse(cursorid);
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
pxVartikelLokal* pxVartikelLokalList::getNLevelIBTEntryToBeUsed( const long requestedquantity ) // NLevelIBT -> Verbundbuchung nach Prozentualer Logik aus Parameter
{
    if( 0 == Entries() )
    {
        return NULL;
    }

    pxVartikelLokal* retval = NULL;

    // search for entries that match the requested quantity
    retval = getMatchingNLevelIBTEntry( requestedquantity );
    if( retval )
    {
        return retval;
    }

    // return first entry from list (list is ordered by priority)
    retval = (pxVartikelLokal*)At(0);
    return retval;
}
/*-----------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
pxVartikelLokal* pxVartikelLokalList::getMatchingNLevelIBTEntry( const long requestedquantity ) // NLevelIBT -> Suche ersten Eintrag in VartikelLokalListe der Prozentuale Logik erfüllt
{
    pxVartikelLokalListIter iter(*this);
    pxVartikelLokal* retval = NULL;
    while( ( retval = (pxVartikelLokal*) ++iter ) != NULL )
    {
        if( retval->matchesIBTQtyAvailabilityPercentage( requestedquantity ) )
        {
            return retval;
        }
    }
    return NULL;
}
/*-----------------------------------------------------------------------------------------------------*/
