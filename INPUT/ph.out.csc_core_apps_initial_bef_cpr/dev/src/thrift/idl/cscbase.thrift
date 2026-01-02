namespace cpp csc.base
namespace csharp Csc.Base

include "types/messagecodeenum.inc"
include "types/languageenum.inc"

typedef string VersionIdentifier

const VersionIdentifier CSCSERVICE_VERSION = "1.0.0.0"

struct ReturnStruct
{
	1: optional messagecodeenum.MessageCodeEnum 	ErrorCode,		// d.LACKREASON
	2: optional string								ErrorMessage,	// d.TEXT
}

struct Date
{
	1: optional i16 	Year,
	2: optional i16 	Month,
	3: optional i16 	Day,
}

struct Time
{
	1: optional i16		Hour,
	2: optional i16		Minute,
	3: optional i16		Second,
}

struct DateTime
{
	1: optional i16 	Year,
	2: optional i16 	Month,
	3: optional i16 	Day,

	4: optional i16 	Hour,
	5: optional i16 	Minute,
	6: optional i16 	Second,
}

struct SessionRequest
{
	1: optional string				DeviceName,
	2: optional i32					Uid,
	10: optional VersionIdentifier	ClientVersion = CSCSERVICE_VERSION,
}

struct SessionResponse
{
	1: optional ReturnStruct		RetValue,
	2: optional i32					Pid,				// d.PID
	3: optional string				ServerName,
	4: optional i32					ServerPort,
	10: optional VersionIdentifier	ServerVersion = CSCSERVICE_VERSION,
}

struct BankAccount
{
	1:	optional string																NameOfBank,
	2:	optional string																BIC,
	3:	optional string																IBAN,
}

struct Address
{
	1:	optional string																Street,
	2:	optional string																PostalCode,
	3:	optional string																City,
}

struct BranchDetails
{
	1:	optional i16																BranchNo,
	2:	optional string																BranchName,
	3:	optional Address															BranchAddress,
}

struct CustomerDetails
{
	1:	optional i16																BranchNo,
	2:	optional i32																CustomerNo,
	3:	optional string																PharmacyName,
	4:  optional string																Salutation,
	5:	optional string																OwnerName,
	6:	optional Address															CustomerAddress,
	7:	optional string																MailAddress,
	8:	optional string																FaxNo,
	9:  optional languageenum.LanguageEnum											Language,
    10: optional i16                                                                SalutationId,
    11: optional string                                                             SalutationExtension,
    12: optional string                                                             CustomerGroup,
    13: optional string                                                             TelephoneNo,
}