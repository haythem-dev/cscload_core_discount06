include "cscbase.thrift"
include "types/critlevelenum.inc"

namespace cpp csc.callback
namespace csharp Csc.Callback

struct GetCallbackRequest
{
     1: optional i32 CallbackNo,             // d.CALLBACKNO
     2: optional i16 BranchNo,               // d.FILIALNR
}

struct CallbackPosItem
{
     1: optional string Text,                // d.TEXT
     2: optional cscbase.DateTime CreationDateTime,
     3: optional string UserName,            // d.USERNAME64
     4: optional i32    CallbackNo,          // d.CALLBACKNO
     5: optional i32    CallbackPosNo,       // d.POSNO
     6: optional i32    CallbackPosNoDone,   // d.POSNO_DONE
     7: optional cscbase.DateTime CallbackDateTimeWished,  // d.CALLBACKTIMEWISHED & d.CALLBACKDATEWISHED
     8: optional string DivisionName,        // d.DIVISIONNAME
}

typedef list<CallbackPosItem> CallbackPosItemList

struct GetCallbackResponse
{
     1: optional i16    BranchNo,            // d.FILIALNR
     2: optional string Title,               // d.TITEL
     3: optional critlevelenum.CritLevelEnum CritLevel, // d.KRITIKLEVEL
     4: optional cscbase.DateTime CallbackDateTime,

    10: optional i32    CustomerNo,          // d.KUNDENNR
    11: optional string CustomerClassTag,    // d.KZKDKLASSE

    20: optional string PharmacyName,        // d.NAMEAPO
    21: optional string OwnerName,           // d.NAMEINHABER
    22: optional string City,                // d.ORT
    23: optional string Street,              // d.STRASSE
    24: optional string ZipCode,             // d.POSTLEITZAHL
    25: optional string TelefonNo,           // d.TELNR
    26: optional string FaxNo,               // d.FAXNR
    27: optional string SpeedDialNo,         // d.TELKURZWAHL

    30: optional CallbackPosItemList CallbackPositions,

    40: optional cscbase.ReturnStruct RetValue,
}

struct CallbackDivisionInquiryRequest
{
    1: optional i16    BranchNo,            // d.BRANCHNO
}

struct CallbackDivisionInquiryResponseItem
{
    1: optional i16    DivisionNo,          // d.CALLBACKDIVISIONNO
    2: optional string DivisionName,        // d.DIVISIONNAME
}

typedef list<CallbackDivisionInquiryResponseItem> CallbackDivisionInquiryResponseItemList

struct CallbackDivisionInquiryResponse
{
    1: optional CallbackDivisionInquiryResponseItemList Divisions,

    10: optional cscbase.ReturnStruct RetValue,
}

struct CallbackReasonInquiryRequest
{
    1: optional i16    BranchNo,            // d.BRANCHNO
    2: optional i16    DivisionNo,          // d.CALLBACKDIVISIONNO
}

struct CallbackReasonInquiryResponseItem
{
    1: optional i16    ReasonNo,            // d.REASONNO
    2: optional string Reason,              // d.CALLBACKREASON
}

typedef list<CallbackReasonInquiryResponseItem> CallbackReasonInquiryResponseItemList

struct CallbackReasonInquiryResponse
{
     1: optional CallbackReasonInquiryResponseItemList Reasons,

    10: optional cscbase.ReturnStruct RetValue,
}

struct NewCallbackCritPosRequest
{
    1: optional i32    CallbackNo,          // d.CALLBACKNO
    2: optional string Text,                // d.TEXT
    3: optional i32    UId,                 // d.UID
    4: optional i16    BranchNo,            // d.FILIALNR
    5: optional i16    SourceApplication,   // d.SOURCEAPPLICATION
    6: optional string WindowsUser,         // d.USERNAME64
}

struct NewCallbackCritPosResponse
{
    1: optional cscbase.ReturnStruct RetValue,
}

struct NewCallbackRequest
{
     1: optional i16    BranchNo,           // d.FILIALNR
     2: optional i16    DivisionNo,         // d.CALLBACKDIVISIONNO
     3: optional i16    ReasonNo,           // d.REASONNO
     4: optional string CritText,           // d.TEXT
     5: optional i16    CritLevel,          // d.KRITIKLEVEL
     6: optional cscbase.DateTime CallbackDateTimeWished, // d.CALLBACKDATEWISHED & d.CALLBACKTIMEWISHED
     7: optional string State,              // d.STATE
     8: optional string CallbackWantedText, // d.CALLBACKWANTEDTEXT

    20: optional i16    CstBranchNo         // d.VERTRIEBSZENTRUMNR
    21: optional i32    CustomerNo,         // d.IDFNR
    22: optional string ContactPerson,      // d.CONTACTPERSON

    30: optional string WindowsUser,        // d.USERNAME64
    31: optional string WebSiteBaseUrl,     // d.URL128
    32: optional i16    SourceApplication,  // d.SOURCEAPPLICATION
    33: optional i32    UId,                // d.UID
    40: optional bool   SendEmail,
}

struct NewCallbackResponse
{
     1: optional cscbase.ReturnStruct RetValue,
    10: optional i16    BranchNo,
    11: optional i32    CallbackNo,
}

struct FindCustomersRequest
{
     1: optional i16    BranchNo,           // REGIONNR/VERTRIEBSZENTRUMNR
     2: optional bool   OnlyOwnBranch,
     3: optional i32    CustomerNo,         // IDFNR
     4: optional string MatchCode,          // MATCHCODE
     5: optional string OwnerName,          // NAMEINHABER
     6: optional string PharmacyName,       // NAMEAPO
     7: optional string City,               // ORT
     8: optional bool   LockedCustomers,    // SKDKUNDEAEGESPERRT

    10: optional i32    MaxResults,
}

struct FindCustomersResponseItem
{
     1: optional i16    BranchNo,           // FILIALNR
     2: optional i16    OrigBranchNo,       // ORIGINALFILIALNR
     3: optional i32    CustomerNo,         // IDFNR
     4: optional i16    CstBranchNo,        // VERTRIEBSZENTRUMNR
     5: optional string PharmacyName,       // NAMEAPO
     6: optional string OwnerName,          // NAMEINHABER
     7: optional string City,               // ORT
     8: optional string Street,             // STRASSE
     9: optional string SpeedDialNo,        // TELKURZWAHL
}

typedef list<FindCustomersResponseItem> FindCustomersResponseItemList

struct FindCustomersResponse
{
     1: optional FindCustomersResponseItemList Customers,
     2: optional i32    CompleteResultCount,

    10: optional cscbase.ReturnStruct RetValue,
}

struct FindCallbacksRequest
{
     1: optional i16    BranchNo,           // REGIONNR/VERTRIEBSZENTRUMNR
     2: optional bool   OnlyOwnBranch,
     3: optional i32    CustomerNo,
     4: optional string Title,
     5: optional cscbase.Date DateFrom,
     6: optional cscbase.Date DateTo,
     7: optional i16    DivisionNo,
     8: optional i16    ReasonNo,

    10: optional i32    MaxResults,
}

struct FindCallbacksResponseItem
{
     1: optional i32    CallbackNo,
     2: optional i16    BranchNo,           // FILIALNR
     3: optional cscbase.DateTime CallbackDateTime,
     4: optional string Title,              // d.TITEL
     5: optional string PharmacyName,       // NAMEAPO
     6: optional string City,               // ORT
     7: optional critlevelenum.CritLevelEnum CritLevel, // d.KRITIKLEVEL
}

typedef list<FindCallbacksResponseItem> FindCallbacksResponseItemList

struct FindCallbacksResponse
{
     1: optional FindCallbacksResponseItemList Callbacks,
     2: optional i32    CompleteResultCount,

    10: optional cscbase.ReturnStruct RetValue,
}

struct GetCallbackDivisionAndReasonNameRequest
{
    1: optional i16     BranchNo,
    2: optional i16     DivisionNo,
    3: optional i16     ReasonNo,
}

struct GetCallbackDivisionAndReasonNameResponse
{
     1: optional string DivisionName,
     2: optional string ReasonName,

    10: optional cscbase.ReturnStruct RetValue,
}
