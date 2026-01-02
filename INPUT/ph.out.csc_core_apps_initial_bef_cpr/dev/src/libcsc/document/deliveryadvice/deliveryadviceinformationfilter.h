#ifndef GUARD_LIBCSC_DOCUMENT_INFORMATION_FILTER_STRUCT_H
#define GUARD_LIBCSC_DOCUMENT_INFORMATION_FILTER_STRUCT_H


namespace libcsc {
namespace document {

struct DeliveryAdviceInformationFilter
{
    DeliveryAdviceInformationFilter(
		const bool _SendTotals = false,
		const bool _SendLineInformation = false,
		const bool _SendLinePickingInformation = false,
		const bool _SendLineDiscountInformation = false,
        const bool _SendLineReturn = false,
        const bool _SendCustomerInformation = false,
        const bool _SendOnlyInvoicedLines = false,
        const bool _SendLineExtrasAT = false
	) :
		SendTotals(_SendTotals),
		SendLineInformation(_SendLineInformation),
		SendLinePickingInformation(_SendLinePickingInformation),
		SendLineDiscountInformation(_SendLineDiscountInformation),
        SendLineReturn(_SendLineReturn),
        SendCustomerInformation(_SendCustomerInformation),
        SendOnlyInvoicedLines(_SendOnlyInvoicedLines),
        SendLineExtrasAT(_SendLineExtrasAT)
    {
    }

	bool	SendTotals;						// optional! true => send information from deliveryadvicetotals and devliveryadvicevattotals
	bool	SendLineInformation;			// optional! true => send information from deliveryadviceline
	bool	SendLinePickingInformation; 	// optional! true => add information from deliveryadvicelinedetails
	bool	SendLineDiscountInformation;	// optional! true => add information from delvieryadvicelinediscounts
    bool	SendLineReturn;					// optional! true => add information from delvieryadvicelinereturn
    bool	SendCustomerInformation;	    // optional! true => add information from cscbase.CustomerDetails
    bool	SendOnlyInvoicedLines;			// optional! true => add only invoiced lines
    bool	SendLineExtrasAT;               // optional! true => add information for Austria
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_KEY_H
