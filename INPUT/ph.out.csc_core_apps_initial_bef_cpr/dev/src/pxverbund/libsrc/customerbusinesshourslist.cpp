#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "customerbusinesshours.hpp"
#include "customerbusinesshourslist.hpp"

/*############################################################################################################################*/
/*                                       P U B L I C                                                                          */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerBusinessHoursList::CustomerBusinessHoursList(pxSession* session)
    : nDBRecordSet( session )
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerBusinessHoursList::~CustomerBusinessHoursList()
{	
    Clear();
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerBusinessHoursList::getBusinessHours( const short branchno, const long& customerno )
{	
    this->Clear();
    
    tCUSTOMERBUSINESSHOURS data;
    memset( &data, 0, sizeof(tCUSTOMERBUSINESSHOURS) );

    data.BranchNo = branchno;
    data.CustomerNo = customerno;	

    int cursorid = cCUSTOMERBUSINESSHOURS_DEFAULT;
    int count_ = -1;
    count_ = nDBSelect( &data, cursorid, count_, &data );
    return (count_ > 0);
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerBusinessHoursList::isInsideBusinessHours( const nDate& datetime )
{
    if( this->Entries() > 0 )
    {
        CustomerBusinessHoursListIter iter( *this );
        CustomerBusinessHours* item = NULL;
        while( NULL != (item = (CustomerBusinessHours*)++iter) )
        {
            if( item->isInsideBusinessHours( datetime ) )
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
nCollectable* CustomerBusinessHoursList::AddToList( const void* record, const int /* row */)
{
    CustomerBusinessHours *objectp = new CustomerBusinessHours( getSession(), *(tCUSTOMERBUSINESSHOURS*) record );
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CustomerBusinessHoursList::Clear()
{
    nDBRecordSet::Clear();
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int CustomerBusinessHoursList::EndBrowse(const int cursorid)
{
    return CustomerBusinessHoursEndBrowse( cursorid );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int CustomerBusinessHoursList::GetNext(const void* record, const int cursorid)
{
    return CustomerBusinessHoursGetNext( (tCUSTOMERBUSINESSHOURS*)record, cursorid );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int CustomerBusinessHoursList::StartBrowse(const void* keys, const int cursorid)
{
    return CustomerBusinessHoursStartBrowse( (tCUSTOMERBUSINESSHOURS*)keys, this->getSession()->getDatabaseName( ((tCUSTOMERBUSINESSHOURS*)keys)->BranchNo ).c_str(), cursorid );
}

/*############################################################################################################################*/
/*                                       P R I V A T E                                                                        */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
pxSession* CustomerBusinessHoursList::getSession()
{
    return (pxSession*) DataBase();
}
