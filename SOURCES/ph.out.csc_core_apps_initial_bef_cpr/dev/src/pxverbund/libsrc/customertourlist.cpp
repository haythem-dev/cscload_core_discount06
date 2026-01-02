#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "customertour.hpp"
#include "customertourlist.hpp"
#include "tourutil.hpp"
#include "csccustomer.hpp"
#include <logger/loggerpool.h>

/*############################################################################################################################*/
/*                                       P U B L I C                                                                          */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerTourList::CustomerTourList(pxSession* session, const short branchno, const long customerno)
    : nDBRecordSet( session ), m_BranchNo( branchno ), m_CustomerNo( customerno )
{
    nDBSetList(this);
    m_Customer = NULL;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerTourList::~CustomerTourList()
{
    if( NULL != m_Customer )
    {
        delete m_Customer;
        m_Customer = NULL;
    }

    Clear();
}

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerTour* CustomerTourList::getTour( const nString& tourid, nDate tourdate )
{
    Clear();
    std::stringstream s;
    s << "CTL:getTour [" << tourid << "/" << tourdate.GetYYYYMMDD() << "] ";

    if( !getToursForWeek(tourid) )
    {
        s << " NoWeekTours! -> NULL";
        TourUtil::writeLogDEBUG( s );
        return NULL;
    }

    s << "Entries " << Entries() << " ";

    if( this->Entries() > 0 )
    {
        CustomerTour* ct = NULL;
        CustomerTourListIter iter(*this);
        while ( (ct = (CustomerTour*)++iter) != NULL )
        {
            if( tourdate.GetDayOfWeek() != TourUtil::getWeekDay(ct->getWeekDay()) ) continue;
            if( ct->getTourId() == tourid )
            {
                ct->setPickingDate( tourdate );
                return ct;
            }
        }
    }

    s << " NotFound! -> NULL";
    TourUtil::writeLogDEBUG( s );

    return NULL;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTourList::getTour( const nString& tourid )
{
    Clear();
    if( !getToursForWeek(tourid) )
    {
        return false;
    }
    if( 0 == this->Entries() )
    {
        return false;
    }
    return true;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTourList::getTours(const nString& ordertype /*= ""*/ )
{
    Clear();
    ClearError();
    // no tours available
    if( !getToursForWeek() )
    {
        return false;
    }
    if( 0 == this->Entries() )
    {
        return false;
    }

    // if there are tours with a specific ordertype, remove all entries without the current ordertype or no order type set
    nString ordtype = ordertype;
    ordtype.Strip();
    if( !ordtype.IsEmpty() && hasToursWithOrderType(ordtype) )
    {
        removeToursWithoutOrderType(ordtype);
    }

    return true;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTourList::getCurrentTour( const nString& tourid )
{
    Clear();
    if( !getToursForToday(tourid) )
    {
        return false;
    }
    if( 0 == this->Entries() )
    {
        return false;
    }
    return true;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTourList::getCurrentTours(const nString& ordertype /*= ""*/ )
{
    Clear();
    ClearError();
    // no tours available
    if( !getToursForToday() )
    {
        return false;
    }
    if( 0 == this->Entries() )
    {
        return false;
    }

    // if there are tours with a specific ordertype, remove all entries without the current ordertype or no order type set
    nString ordtype = ordertype;
    ordtype.Strip();
    if( !ordtype.IsEmpty() && hasToursWithOrderType(ordtype) )
    {
        removeToursWithoutOrderType(ordtype);
    }

    // set current weekday in entries
    if( this->Entries() > 0 )
    {
        CustomerTour* ct = NULL;
        CustomerTourListIter iter(*this);
        while ( (ct = (CustomerTour*)++iter) != NULL )
        {
            ct->setWeekDay( ct->m_PickingDate.GetDayOfWeek() );
        }
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
nString CustomerTourList::getFirstTourId()
{
    if( this->Entries() > 0 )
    {
        return ((CustomerTour*)(this->At(0)))->getTourId();
    }
    return nString("");
}

/*----------------------------------------------------------------------------------------------------------------------------*/
nString CustomerTourList::getLastTourId()
{
    if( this->Entries() > 0 )
    {
        CustomerTourListIter cursor(*this);
        CustomerTour* ct = NULL;
        cursor.ToLast();
        while ( (ct = (CustomerTour*) --cursor) != NULL )
        {
            if( !ct->isPseudoTour() )
            {
                return ct->getTourId();
            }
        }
    }
    return nString("");
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTourList::isArticleDeliverable( pxArtBase* article )
{
    if( this->Entries() > 0 )
    {
        CustomerTourListIter cursor(*this);
        CustomerTour* ct = NULL;
        while ( (ct = (CustomerTour*)++cursor) != NULL )
        {
            if (ct->isValidForArticle(article))
            {
                return true;
            }
        }
    }
    return false;
}

/*############################################################################################################################*/
/*                                       P R O T E C T E D                                                                    */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
nCollectable* CustomerTourList::AddToList( const void* record, const int /* row */)
{
    CustomerTour *objectp = new CustomerTour( getSession(), getCustomer()->getBranchNo(), getCustomer()->getCustomerNo(), *(tCUSTOMERTOUR*) record  );
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CustomerTourList::Clear()
{
    nDBRecordSet::Clear();
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int CustomerTourList::EndBrowse(const int cursorid)
{
    return CustomerTourEndBrowse( cursorid );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int CustomerTourList::GetNext(const void* record, const int cursorid)
{
    return CustomerTourGetNext( (tCUSTOMERTOUR*)record, cursorid );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int CustomerTourList::StartBrowse(const void* keys, const int cursorid)
{
    return CustomerTourStartBrowse( (tCUSTOMERTOUR*)keys, this->getSession()->getDatabaseName( this->getCustomer()->getBranchNo() ).c_str(), cursorid );
}

/*############################################################################################################################*/
/*                                       P R I V A T E                                                                        */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
CSCCustomer* CustomerTourList::getCustomer()
{
    if( NULL != m_Customer )
    {
        if( m_Customer->getBranchNo() != m_BranchNo || m_Customer->getCustomerNo() != m_CustomerNo )
        {
            delete m_Customer;
            m_Customer = NULL;
        }
    }

    if( NULL == m_Customer )
    {
        m_Customer = new CSCCustomer( getSession(), m_BranchNo, m_CustomerNo );
        m_Customer->Read();
    }

    return m_Customer;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
pxSession* CustomerTourList::getSession()
{
    return (pxSession*) DataBase();
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTourList::getToursForToday()
{
    tCUSTOMERTOUR data;
    memset( &data, 0, sizeof(tCUSTOMERTOUR) );
    int cursorid = cCUSTOMERTOUR_DEFAULT;
    data.BranchNo = getCustomer()->getBranchNo();
    data.CustomerNo = getCustomer()->getCustomerNo();
    data.PickingDate = TourUtil::getCurrentDate().GetYYYYMMDD();
    int count_ = -1;
    count_ = nDBSelect( &data, cursorid, count_, &data );
    return count_ > 0 ? true : false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTourList::getToursForToday(const nString& tourid)
{
    tCUSTOMERTOUR data;
    memset( &data, 0, sizeof(tCUSTOMERTOUR) );
    int cursorid = cCUSTOMERTOUR_BYTOURID;
    data.BranchNo = getCustomer()->getBranchNo();
    data.CustomerNo = getCustomer()->getCustomerNo();
    data.PickingDate = TourUtil::getCurrentDate().GetYYYYMMDD();
    tourid.GetData(data.TourId);
    int count_ = -1;
    count_ = nDBSelect( &data, cursorid, count_, &data );
    return count_ > 0 ? true : false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTourList::getToursForWeek()
{
    tCUSTOMERTOUR data;
    memset( &data, 0, sizeof(tCUSTOMERTOUR) );
    int cursorid = cCUSTOMERTOUR_WHOLEWEEK;
    data.BranchNo = getCustomer()->getBranchNo();
    data.CustomerNo = getCustomer()->getCustomerNo();
    int count_ = -1;
    count_ = nDBSelect( &data, cursorid, count_, &data );
    return count_ > 0 ? true : false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTourList::getToursForWeek(const nString& tourid)
{
    tCUSTOMERTOUR data;
    memset( &data, 0, sizeof(tCUSTOMERTOUR) );
    int cursorid = cCUSTOMERTOUR_BYTOURIDWEEK;
    data.BranchNo = getCustomer()->getBranchNo();
    data.CustomerNo = getCustomer()->getCustomerNo();
    tourid.GetData(data.TourId);
    int count_ = -1;
    count_ = nDBSelect( &data, cursorid, count_, &data );
    return count_ > 0 ? true : false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTourList::hasToursWithOrderType( const nString& ordertype )
{
    if( this->Entries() > 0 )
    {
        CustomerTour* ct = NULL;
        CustomerTourListIter iter(*this);
        while ( (ct = (CustomerTour*)++iter) != NULL )
        {
            if( ct->hasOrderType(ordertype) )
            {
                return true;
            }
        }
    }
    return false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CustomerTourList::removeToursWithDepartureOnPublicHoliday()
{
    if( this->Entries() > 0 )
    {
        CustomerTour* ct = NULL;
        CustomerTourListIter iter(*this);
        while ( (ct = (CustomerTour*)++iter) != NULL )
        {
            if( ct->isDepartureOnPublicHoliday() )
            {
                    delete iter.Remove();
            }
        }
    }
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CustomerTourList::removeToursWithoutOrderType( const nString& ordertype )
{
    if( this->Entries() > 0 )
    {
        CustomerTour* ct = NULL;
        CustomerTourListIter iter(*this);
        while ( (ct = (CustomerTour*)++iter) != NULL )
        {
            if( !ct->hasOrderType(ordertype) )
            {
                if( ct->isAutoAssignable() )    // delete only auto assignable tours (pseudo tours should stay in list)
                {
                    delete iter.Remove();
                }
            }
        }
    }
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CustomerTourList::removeExpiredTours( const pxCommType* commtype )
{
    if( this->Entries() > 0 )
    {
        CustomerTour* ct = NULL;
        CustomerTourListIter iter(*this);
        while ( (ct = (CustomerTour*)++iter) != NULL )
        {
            if( ct->hasExpired(commtype) )
            {
                if( ct->isAutoAssignable() )    // delete only auto assignable tours (pseudo tours should stay in list)
                {
                    delete iter.Remove();
                }
            }
        }
    }
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CustomerTourList::removeUnassignableTours()
{
    if( this->Entries() > 0 )
    {
        CustomerTour* ct = NULL;
        CustomerTourListIter iter(*this);
        while ( (ct = (CustomerTour*)++iter) != NULL )
        {
            if( !ct->isAssignable() )
            {
                delete iter.Remove();
            }
        }
    }
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTourList::isTourAvailable( const nString& tourid )
{
    bool retval = false;
    if( this->Entries() > 0 )
    {
        CustomerTour* ct = NULL;
        CustomerTourListIter iter(*this);
        while ( (ct = (CustomerTour*)++iter) != NULL )
        {
            if( ct->getTourId() == tourid )
            {
                retval = true;
                break;
            }
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTourList::isTourAvailableForWeekday( const nString& tourid, short weekday )
{
    bool retval = false;
    if( this->Entries() > 0 )
    {
        CustomerTour* ct = NULL;
        CustomerTourListIter iter(*this);
        while ( (ct = (CustomerTour*)++iter) != NULL )
        {
            if( weekday != TourUtil::getWeekDay(ct->getWeekDay()) ) continue;
            if( ct->getTourId() == tourid )
            {
                retval = true;
                break;
            }
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTourList::isTourPossibleForArticle( const nString& tourid, pxArtBase* article )
{
    if( NULL == article ) return true;

    if( this->Entries() > 0 )
    {
        CustomerTour* ct = NULL;
        CustomerTourListIter iter(*this);
        while ( (ct = (CustomerTour*)++iter) != NULL )
        {
            if( ct->getTourId() == tourid )
            {
                if( !ct->isValidForArticle( article ) )
                {
                    return false;
                }
            }
        }
    }

    return true;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CustomerTourList::setIBTShuttleTourDetermination( const bool b /*= true*/ )
{
    if( this->Entries() > 0 )
    {
        CustomerTour* ct = NULL;
        CustomerTourListIter iter(*this);
        while ( (ct = (CustomerTour*)++iter) != NULL )
        {
            ct->injectIBTShuttleTourDetermination(b);
        }
    }
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CustomerTourList::setIBTOrderImport( const bool b /*= true*/ )
{
    if( this->Entries() > 0 )
    {
        CustomerTour* ct = NULL;
        CustomerTourListIter iter(*this);
        while ( (ct = (CustomerTour*)++iter) != NULL )
        {
            ct->injectIBTOrderImport(b);
        }
    }
}
