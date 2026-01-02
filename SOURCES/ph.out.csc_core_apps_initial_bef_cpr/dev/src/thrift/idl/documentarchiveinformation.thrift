include "cscbase.thrift"
include "types/documenttypeenum.inc"

namespace cpp documents
namespace csharp Documents


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// write document archive information to database request
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SetDocumentInformationRequest
{
	1:	optional i16									BranchNo,
	2:	optional i32									CustomerNo,
	10: optional documenttypeenum.DocumentTypeEnum		DocumentType,
	11:	optional string									DocumentNo,
	12:	optional cscbase.Date							DocumentDate,
	13:	optional string									DocumentGuid,
	14: optional string									DocumentLink,
	15:	optional bool									SentViaMail,
	16:	optional bool									SentViaFax,
}

struct SetDocumentInformationResponse
{
	1:	optional cscbase.ReturnStruct				RetValue,
	5:	optional bool								SendMail,
	6:	optional bool								SendFax,
    10: optional cscbase.BranchDetails				BranchInformation,
    20: optional cscbase.CustomerDetails			CustomerInformation,
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// read document archive information from database
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct GetDocumentInformationRequest
{
	1:	optional i16									BranchNo,
	2:	optional i32									CustomerNo,

	10: optional documenttypeenum.DocumentTypeEnum		DocumentType,		// set either 10, 11, 12 ...
	11:	optional string									DocumentNo,
	12:	optional cscbase.Date							DocumentDate,

	20:	optional string									DocumentGuid,	// ... or 20 as search restriction
}

struct GetDocumentInformationResponse
{
	1:	optional cscbase.ReturnStruct					RetValue
	10:	optional i16									BranchNo,
	11:	optional i32									CustomerNo,
	20: optional documenttypeenum.DocumentTypeEnum		DocumentType,
	21:	optional string									DocumentNo,
	22:	optional cscbase.Date							DocumentDate,
	25:	optional string									DocumentGuid,
	26: optional string									DocumentLink
}

