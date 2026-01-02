#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

using namespace std;

// ------------------------------------------------------------------------------------------- //
void testEmergencyService()
{	
	SessionUtil session(33);
	pxOrderTransmit* xmit = session.get();

	EmergencyService esvc( xmit->Session(), 33, 649 );
	if( esvc.Get() )
	{
		cout << "BranchNo:" << esvc.getBranchNo() << " CustomerNo:" << esvc.getCustomerNo() << endl;
		cout << "Date:" << esvc.getEmergencyServiceDate() << " TimeTo:" << esvc.getEmergencyServiceTimeTo() << endl;
		cout << "BTM:" << esvc.delayDeliveryForNarcotics() << " KK:" << esvc.delayDeliveryForCoolChain() << " K08:" << esvc.delayDeliveryForCoolBelow8() << " K20:" << esvc.delayDeliveryForCoolBelow20() << endl;
		cout << "Remarks:" << esvc.getRemarks().c_str() << endl;
	}
	else
	{
		cout << "Nothing found or error?" << endl;
	}
}
