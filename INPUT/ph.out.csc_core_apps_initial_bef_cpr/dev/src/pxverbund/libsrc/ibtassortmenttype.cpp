#include "ibtassortmenttype.h"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
IBTAssortmentType::IBTAssortmentType( pxSession* session,  short ibtassortmenttypeid )
	: pxDBRecord( session ), IBTAssortmentTypeID( ibtassortmenttypeid )
{
	Init();
}

/*----------------------------------------------------------------------------*/
IBTAssortmentType::~IBTAssortmentType()
{	
}
/*----------------------------------------------------------------------------*/
/*  Use tIBTASSORTMENTTYPE structure to construct this instance.              */
/*----------------------------------------------------------------------------*/
IBTAssortmentType :: IBTAssortmentType
(
    pxSession   *session,
    tIBTASSORTMENTTYPE& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
void IBTAssortmentType::Init()
{
    tIBTASSORTMENTTYPE record;
    memset( &record, 0, sizeof(tIBTASSORTMENTTYPE) );
    Assign( *this, record );

	m_Values.IBTAssortmentTypeID = 0;
	m_Values.IBTCustomersOnly = 0;
	m_Values.IBTPeriodNeeded = 0;
}

/*----------------------------------------------------------------------------*/
IBTAssortmentType& IBTAssortmentType::operator=( const IBTAssortmentType& src )
{
	tIBTASSORTMENTTYPE record;
    Assign( *this, Assign(record, src) );
    return *this;
}

/*----------------------------------------------------------------------------*/
IBTAssortmentType& IBTAssortmentType::operator=( const tIBTASSORTMENTTYPE& src )		
{
	return Assign( *this, src );
}

/*----------------------------------------------------------------------------*/
bool IBTAssortmentType::Get()
{
	bool retval = false;
    tIBTASSORTMENTTYPE record;	
	memset( &record, 0, sizeof(tIBTASSORTMENTTYPE) );

	record.IBTAssortmentTypeID = this->IBTAssortmentTypeID;
	
    int rc = nDBRead( &record );
    if( 0 == rc )
	{
		this->m_Values = record;		
		retval = true;
	}
    return retval;
}

/*----------------------------------------------------------------------------*/
int IBTAssortmentType::Read( const void* record )
{
	return pxIBTAssortmentTypeRead( (tIBTASSORTMENTTYPE*)record );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
IBTAssortmentType& IBTAssortmentType::Assign( IBTAssortmentType& dest, const tIBTASSORTMENTTYPE& src )
{	
	dest.m_Values.IBTAssortmentTypeID = src.IBTAssortmentTypeID;
	dest.m_Values.IBTCustomersOnly = src.IBTCustomersOnly;
	dest.m_Values.IBTPeriodNeeded = src.IBTPeriodNeeded;
    return dest;
}

/*----------------------------------------------------------------------------*/
tIBTASSORTMENTTYPE& IBTAssortmentType::Assign( tIBTASSORTMENTTYPE& dest, const IBTAssortmentType& src )
{	
	dest.IBTAssortmentTypeID = src.m_Values.IBTAssortmentTypeID;
	dest.IBTCustomersOnly = src.m_Values.IBTCustomersOnly;
	dest.IBTPeriodNeeded = src.m_Values.IBTPeriodNeeded;
	
    return dest;
}

/*----------------------------------------------------------------------------*/
short IBTAssortmentType::getIBTAssortmentTypeID() const
{
	return m_Values.IBTAssortmentTypeID;
}

/*----------------------------------------------------------------------------*/
short IBTAssortmentType::getIBTCustomersOnly() const
{
	return m_Values.IBTCustomersOnly;
}

/*----------------------------------------------------------------------------*/
short IBTAssortmentType::getIBTPeriodNeeded() const
{
	return m_Values.IBTPeriodNeeded;
}

/*----------------------------------------------------------------------------*/
bool IBTAssortmentType::isIBTCustomersOnly() const
{
	return (eIBTCustomersOnly == getIBTCustomersOnly());
}

/*----------------------------------------------------------------------------*/
bool IBTAssortmentType::isIBTPeriodNeeded() const
{
	return (eIBTPeriodNeeded == getIBTPeriodNeeded());
}
/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures IBTAssortmentType: list objects being inserted in the             */
/*  following ascending sequence:                                             */
/*  (IBTTypeId_)                                                              */
/*----------------------------------------------------------------------------*/
int IBTAssortmentType::CompareTo(const nCollectable* That, void* /*p*/, const long /*lparm*/) const
{
    IBTAssortmentType *that = (IBTAssortmentType*)That;
	int retval = (getIBTAssortmentTypeID() == that->getIBTAssortmentTypeID()) ? 0
                : (getIBTAssortmentTypeID() > that->getIBTAssortmentTypeID() ? 1 : -1);
    
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
IBTAssortmentTypeList::IBTAssortmentTypeList(pxSession* session) : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  List Destructor.                                                          */
/*----------------------------------------------------------------------------*/
IBTAssortmentTypeList::~IBTAssortmentTypeList()
{
    Clear();
}

/*----------------------------------------------------------------------------*/
pxSession* IBTAssortmentTypeList::Session()
{
    return (pxSession*) DataBase();
}

/*----------------------------------------------------------------------------*/
void IBTAssortmentTypeList::Clear()
{
    nDBRecordSet::Clear();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t IBTAssortmentTypeList::Select()
{
    tIBTASSORTMENTTYPE record;
    memset(&record, 0, sizeof(tIBTASSORTMENTTYPE));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&record, cursorid);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable* IBTAssortmentTypeList::AddToList(const void* record, const int /*row*/)
{
    IBTAssortmentType *objectp = new IBTAssortmentType(Session(), *(tIBTASSORTMENTTYPE*) record);
    InsertAscending(objectp);
    return objectp;
}

int IBTAssortmentTypeList::EndBrowse(const int cursorid)
{
    return pxIBTAssortmentTypeEndBrowse(cursorid);
}


int IBTAssortmentTypeList::GetNext(const void* record, const int cursorid)
{
    return pxIBTAssortmentTypeGetNext((tIBTASSORTMENTTYPE*)record, cursorid);
}

int IBTAssortmentTypeList::StartBrowse(const void* keys, const int cursorid)
{
    return pxIBTAssortmentTypeStartBrowse((tIBTASSORTMENTTYPE*)keys,cursorid);
}

/*----------------------------------------------------------------------------*/
/* Returns the pointer to the corresponding entry within the list.            */
/* NULL returns if the wanted entry is not found within the list.             */
/*----------------------------------------------------------------------------*/
IBTAssortmentType* IBTAssortmentTypeList::Find(short ibtassortmenttypeid)
{
    IBTAssortmentTypeListIter   iter(*this);
    IBTAssortmentType*          entry;

    iter.Reset();
    while ((entry = (IBTAssortmentType*)++iter) != NULL)
    {
        if ( ibtassortmenttypeid == entry->getIBTAssortmentTypeID() )
        {
            break;
        }
    }
    return entry;
}
