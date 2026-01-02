//----------------------------------------------------------------------------//
/*! \file
 *  \brief  RecordTypeImportInvoiceNo
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEIMPORTINVOICENO_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEIMPORTINVOICENO_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypebase.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

class RecordTypeImportInvoiceNo : public core::RecordTypeBase
{
public:
    RecordTypeImportInvoiceNo();
    ~RecordTypeImportInvoiceNo();

    virtual void process( const core::TransactionRecordBasePtr record ) const;

private:
    RecordTypeImportInvoiceNo( const RecordTypeImportInvoiceNo& );
    RecordTypeImportInvoiceNo& operator= ( const RecordTypeImportInvoiceNo& );

    virtual void doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const;
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEIMPORTINVOICENO_H
