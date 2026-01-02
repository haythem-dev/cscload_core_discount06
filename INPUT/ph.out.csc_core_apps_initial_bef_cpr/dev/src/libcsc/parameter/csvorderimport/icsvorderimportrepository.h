#ifndef GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_REPOSITORY_H
#define GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_REPOSITORY_H

#include <libbasarcmnutil_bstring.h>
#include <parameter/csvorderimport/icscorderimportfieldsptr.h>
#include <parameter/csvorderimport/icscorderimportcsvformatsptr.h>
#include <parameter/csvorderimport/icscorderimportcsvcolumnsptr.h>

namespace libcsc {
namespace parameter {

class ICSVOrderImportRepository
{
public:
	virtual ~ICSVOrderImportRepository() {}

	virtual void										reset() = 0;

	virtual ICSCOrderImportFieldsCollectionPtr			findCSCOrderImportCSVFields() = 0;

	virtual ICSCOrderImportCSVFormatsCollectionPtr		findCSCOrderImportCSVFormats() = 0;

	virtual ICSCOrderImportCSVFormatsPtr				findCSCOrderImportCSVFormatsById(
															const basar::Int32& id) = 0;

	virtual void										saveCSCOrderImportCSVFormats(
														ICSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats) = 0;
	virtual void										deleteCSCOrderImportCSVFormats(
														ICSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats) = 0;

	virtual ICSCOrderImportCSVFormatsPtr				getEmptyCSCOrderImportCSVFormats() = 0;

	virtual void										saveCSCOrderImportCSVColumns(
														ICSCOrderImportCSVColumnsPtr CSCOrderImportCSVColumns) = 0;
	virtual void										deleteCSCOrderImportCSVColumnsByKey(
														const basar::Int16& ColumnNo,
														const basar::Int32& CscOrderImportFormatId) = 0;

	virtual bool										areMandatoryFieldsSet(
														ICSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats) = 0;
};

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_REPOSITORY_H
