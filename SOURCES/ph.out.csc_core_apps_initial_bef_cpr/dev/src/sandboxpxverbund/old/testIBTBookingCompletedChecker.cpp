//#include <UnitTest++/UnitTest++.h>
//#include "SessionUtil.h"
//#include <ibt/componentmanager/ibtcomponentmanager.h>
//#include <ibt/bookingcompletedchecker/ibookingcompletedchecker.h>
//
//using namespace std;
//
//// ------------------------------------------------------------------------------------------- //
//void testIBTBookingCompletedChecker()
//{	
//	cout << "Test IBTBookingCompletedChecker #01: Order" << endl;
//	{		
//		short branchno = TestUtil::askUserForBranchNo();
//		long orderno = TestUtil::askUserForOrderNo();
//		cout << "\t using BranchNo " << branchno << " and OrderNo " << orderno << endl;
//
//		SessionUtil session(branchno);
//		pxOrderTransmit* xmit = session.get();
//
//		if( xmit->getIbtComponentManager()->getBookingCompletedChecker()->isIBTBookingCompleted( branchno, orderno ) )
//		{
//			cout << "\t => at least one IBTBooking completed in this order." << endl;
//		}
//		else
//		{
//			cout << "\t => all IBTBookings still open or no IBTBookings in this order." << endl;
//		}
//	}
//
//	cout << "Test IBTBookingCompletedChecker #02: OrderLine" << endl;
//	{		
//		short branchno = TestUtil::askUserForBranchNo();
//		long orderno = TestUtil::askUserForOrderNo();
//		cout << "\t using BranchNo " << branchno << " and OrderNo " << orderno << endl;
//
//		SessionUtil session(branchno);
//		pxOrderTransmit* xmit = session.get();
//
//		if( xmit->getIbtComponentManager()->getBookingCompletedChecker()->isIBTBookingCompleted( branchno, orderno ) )
//		{
//			cout << "\t => IBTBooking completed for this order line." << endl;
//		}
//		else
//		{
//			cout << "\t => IBTBooking still open for this order line." << endl;
//		}
//	}
//}