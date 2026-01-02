#ifndef GUARD_MSV3HANDLER
#define GUARD_MSV3HANDLER

#include <pxordertransmitptr.h>
#include <msv3/componentmanager/msv3componentmanagerptr.h>
#include "cscmsv3_types.h"
#include "cscorder_types.h"
#include "csclibtothrifthandlerbase.h"

namespace csc {
namespace service {

class MSV3Handler : public CscLibToThriftHandlerBase
{
public:
	MSV3Handler();
	virtual ~MSV3Handler();

	// called before and after nomal order handling
	void processPrepareMSV3Transmission(
		msv3::Msv3TransmissionPreparationResponse& _return,
		const msv3::Msv3TransmissionPreparationRequest& request);

	void processPostProcessMSV3Transmission(
		const msv3::Msv3TransmissionPostProcessingRequest& request);

	// order status
	void processMSV3OrderStatus(
		msv3::Msv3OrderStatusResponse& _return,
		const msv3::Msv3OrderStatusRequest& request);

	// misc
	void getXmlInfoLevel(
		msv3::XmlInfoLevelResponse& _return,
		const msv3::XmlInfoLevelRequest& request);

	void getMsv3ContractData(
		msv3::Msv3ContractDataResponse& _return,
		const msv3::Msv3ContractDataRequest& request);

	// Hooks called from nomal order handling
	void postProcessOrderOpen( order::OpenOrderResponse& _return, const order::OpenOrderRequest& request);

	void postProcessOrderProductPosition( order::OrderPositionResponse& _return );
	void postProcessOrderArticleInquiryPosition( order::OrderPositionResponse& _return );	

	void preProcessOrderClose(
		order::CloseOrderResponse& _return);

	void postProcessOrderClose(
		order::CloseOrderResponse& _return);


private:
	void processPrepareMSV3OrderType(
		msv3::Msv3OrderPreparationResponseList& _return,
		const msv3::Msv3OrderTypeEnum::type ordertype,
		const msv3::Msv3OrderPreparationRequestList& request,
		const long orderperiodid,
		const long transmissionid);

	void postProcessMSV3DeliveryTime( order::OrderPositionResponse& _return );
	void postProcessMSV3ResetIBTTourInformation( order::OrderPositionResponse& _return );

	libcsc::msv3::MSV3ComponentManagerPtr	getMSV3ComponentManager();

	libcsc::msv3::MSV3ComponentManagerPtr	m_MSV3ComponentManager;

};

} // namespace service
} // namespace csc

#endif // GUARD_MSV3HANDLER
