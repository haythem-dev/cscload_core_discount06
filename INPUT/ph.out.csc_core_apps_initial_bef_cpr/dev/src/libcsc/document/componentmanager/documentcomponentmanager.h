#ifndef GUARD_LIBCSC_DOCUMENT_COMPONENT_MANAGER_H
#define GUARD_LIBCSC_DOCUMENT_COMPONENT_MANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/itransactionfactory.h>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>

#include <document/documentarchiveinfo/documentarchiveinforepositoryptr.h>
#include <document/narcoticarchive/narcoticarchiverepositoryptr.h>
#include <document/deliveryadvice/deliveryadvicerepositoryptr.h>
#include <document/documentprintinfo/documentprintinforepositoryptr.h>
#include <document/taxrates/taxratesrepositoryptr.h>
#include <parameter/ibranchparametergetterptr.h>

class pxSession;

namespace libcsc {
namespace document {

class DocumentComponentManager : public persistence::ITransactionFactory,
                             public boost::enable_shared_from_this<DocumentComponentManager>
{
public:
    DocumentComponentManager();
    virtual ~DocumentComponentManager();

    void injectConnection( persistence::ConnectionPtr connection );
    void injectTransactionHandler (nDataBase * transHandler);
    void injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter);


    virtual libcsc::persistence::TransactionGuard   createTransaction() const;

    DocumentArchiveInfoRepositoryPtr                getDocumentArchiveInfoRepository();
    NarcoticArchiveRepositoryPtr                    getNarcoticArchiveRepository();
    DeliveryAdviceRepositoryPtr                     getDeliveryAdviceRepository();
    DocumentPrintInfoRepositoryPtr                  getDocumentPrintInfoRepository();
    TaxratesRepositoryPtr                           getTaxratesRepository();

private:
    DocumentComponentManager( const DocumentComponentManager & );
    DocumentComponentManager & operator=( const DocumentComponentManager & );

    persistence::IAccessorPtr                   createAccessor();

    persistence::ConnectionPtr                  m_Connection;
    nDataBase *                                 m_TransactionHandler;
    parameter::IBranchParameterGetterPtr        m_BranchParameterGetter;

    mutable DocumentArchiveInfoRepositoryPtr    m_DocumentArchiveInfoRepository;
    mutable NarcoticArchiveRepositoryPtr        m_NarcoticArchiveRepository;
    mutable DeliveryAdviceRepositoryPtr         m_DeliveryAdviceRepository;
    mutable DocumentPrintInfoRepositoryPtr      m_DocumentPrintInfoRepository;
    mutable TaxratesRepositoryPtr               m_TaxratesRepository;
};

} // end namespace msv3
} // end namespace libcsc

#endif //end GUARD_LIBCSC_DOCUMENT_COMPONENT_MANAGER_H
