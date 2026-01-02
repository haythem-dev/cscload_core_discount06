include "cscbase.thrift"
include "types/documenttypeenum.inc"
include "types/transactiontypeenum.inc"

namespace cpp narcotics
namespace csharp Narcotics


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// write document archive information to database request
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SetNarcoticTransactionStatusRequest
{
	1:  optional  i16      										AcknowledgementStatus,
	2:  optional  i32      										ArticleNo,
	3:  optional  i16      										BranchNo,
	4:  optional  i32         									CatalogId,
	5:  optional  i32      										ContributionVoucherNo,
}

struct SetNarcoticTransactionStatusResponse
{
	1:	optional  cscbase.ReturnStruct							RetValue,
	2:  optional  i16      										AcknowledgementStatus,
	3:  optional  i32         									ContributionVoucherNo,
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// read document archive information from database
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct GetNarcoticTransactionRequest
{
	1:  optional  i16      										AcknowledgementStatus,
	2:  optional  i32      										ArticleNo,
	3:  optional  i16      										BranchNo,
	4:  optional  i32         									CatalogId,
	5:  optional  i32      										ContributionVoucherNo,
}

struct GetNarcoticTransactionResponse
{
	1:	optional cscbase.ReturnStruct							RetValue,
	101: optional  i16      									AcknowledgementStatus,
	102: optional  i32      									ArticleNo,
	103: optional  i16      									BranchNo,
	104: optional  i32         									CatalogId,
	105: optional  i32      									ContributionVoucherNo,
	106: optional  cscbase.DateTime 							ContributionVoucherTransferDate,
	107: optional  i16      									ContributionVoucherTransferStatus,
	108: optional  string      									CustomerSupplierCip,
	109: optional  string      									CustomerSupplierCity,
	110: optional  string      									CustomerSupplierName,
	111: optional  i32      									CustomerSupplierNo,
	112: optional  string      									CustomerSupplierStreet,
	113: optional  string      									DeletedFlag,
	114: optional  cscbase.DateTime								DeliveryNoteCopyTransferDate,
	115: optional  i16      									DeliveryNoteCopyTransferStatus,
	116: optional  string      									ForeName,
	117: optional  i32      									InvoiceNo,
	118: optional  double      									NarcFactor,
	119: optional  string     									NarcGroup,
	120: optional  string      									NarcName,
	121: optional  double      									NarcPotency,
	122: optional  string      									NarcUnit,
	123: optional  i32      									PrintedDate,
	124: optional  i32      									PrintedTime,
	125: optional  string      									ProcessedFlag,
	126: optional  i32      									PurchaseOrderNo,
	127: optional  i32      									QtyInstock,
	128: optional  i32      									QtyTransaction,
	129: optional  string      									Surname,
	130: optional  string      									TourId,
	131: optional  i32      									TransactionDate,
	132: optional  i32      									TransactionTime,
	133: optional  transactiontypeenum.TransactionTypeEnum		TransactionType,
	134: optional  string      									Username,
	135: optional  i32      									WarehouseOrderNo,
}

