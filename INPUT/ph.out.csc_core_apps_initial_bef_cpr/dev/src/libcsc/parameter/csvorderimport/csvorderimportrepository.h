#ifndef GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_REPOSITORY_H
#define GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_REPOSITORY_H

#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <libbasarcmnutil_bstring.h>
#include <map>
#include <parameter/csvorderimport/icsvorderimportrepository.h>
#include <parameter/csvorderimport/cscorderimportcsvformatsptr.h>
#include <parameter/csvorderimport/icscorderimportfieldsptr.h>

namespace libcsc {
namespace parameter {

class CSVOrderImportRepository : public ICSVOrderImportRepository
{
public:
	CSVOrderImportRepository();
    virtual ~CSVOrderImportRepository();

	virtual void reset();

	virtual void injectSelectCSCOrderImportCSVFieldsAccessor(persistence::IAccessorPtr accessor);

	virtual void injectSelectCSCOrderImportCSVFormatsAccessor(persistence::IAccessorPtr accessor);
	virtual void injectInsertCSCOrderImportCSVFormatsAccessor(persistence::IAccessorPtr accessor);
	virtual void injectUpdateCSCOrderImportCSVFormatsAccessor(persistence::IAccessorPtr accessor);
	virtual void injectDeleteCSCOrderImportCSVFormatsAccessor(persistence::IAccessorPtr accessor);

	virtual void injectSelectCSCOrderImportCSVColumnsAccessor(persistence::IAccessorPtr accessor);
	virtual void injectInsertCSCOrderImportCSVColumnsAccessor(persistence::IAccessorPtr accessor);
	virtual void injectDeleteCSCOrderImportCSVColumnsAccessor(persistence::IAccessorPtr accessor);


	virtual ICSCOrderImportFieldsCollectionPtr					findCSCOrderImportCSVFields();

	virtual ICSCOrderImportCSVFormatsCollectionPtr				findCSCOrderImportCSVFormats();

	virtual ICSCOrderImportCSVFormatsPtr						findCSCOrderImportCSVFormatsById(const basar::Int32& id);

	virtual void												saveCSCOrderImportCSVFormats(
																ICSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats);

	virtual void												deleteCSCOrderImportCSVFormats(
																ICSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats);

	virtual ICSCOrderImportCSVFormatsPtr						getEmptyCSCOrderImportCSVFormats();

	virtual void												saveCSCOrderImportCSVColumns(
																ICSCOrderImportCSVColumnsPtr CSCOrderImportCSVColumns);

	virtual void												deleteCSCOrderImportCSVColumnsByKey(
																const basar::Int16& ColumnNo,
																const basar::Int32& CscOrderImportFormatId);

	virtual bool												areMandatoryFieldsSet(
																ICSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats);


private:
	virtual void findCSCOrderImportCSVColumns(CSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats);
	virtual void												deleteCSCOrderImportCSVColumnsByID(
																const basar::Int32& CscOrderImportFormatId);

	CSVOrderImportRepository& operator=(const CSVOrderImportRepository&);

	ICSCOrderImportFieldsCollectionPtr							m_CSCOrderImportFieldsList;
	ICSCOrderImportCSVFormatsCollectionPtr						m_CSCOrderImportCSVFormatsList;

    persistence::IAccessorPtr m_SelectCSCOrderImportCSVFieldsAccessor;
    persistence::IAccessorPtr m_SelectCSCOrderImportFormatsAccessor;
	persistence::IAccessorPtr m_InsertCSCOrderImportFormatsAccessor;
	persistence::IAccessorPtr m_UpdateCSCOrderImportFormatsAccessor;
	persistence::IAccessorPtr m_DeleteCSCOrderImportFormatsAccessor;

	persistence::IAccessorPtr m_SelectCSCOrderImportCSVColumnsAccessor;
	persistence::IAccessorPtr m_InsertCSCOrderImportCSVColumnsAccessor;
	persistence::IAccessorPtr m_DeleteCSCOrderImportCSVColumnsAccessor;

};

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_REPOSITORY_H
