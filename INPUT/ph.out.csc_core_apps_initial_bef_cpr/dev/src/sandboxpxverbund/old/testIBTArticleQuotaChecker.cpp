//#include <UnitTest++/UnitTest++.h>
//#include "SessionUtil.h"
//#include <ibt/componentmanager/ibtcomponentmanager.h>
//#include <ibt/articlequotachecker/iarticlequotachecker.h>
//
//using namespace std;
//
//// ------------------------------------------------------------------------------------------- //
//void testIBTArticleQuotaChecker()
//{	
//	cout << "Test testIBTArticleQuotaChecker: " << endl;
//	{		
//		short branchno = TestUtil::askUserForBranchNo();
//		short ibtbranchno = TestUtil::askUserForIBTBranchNo();
//		long articleno = TestUtil::askUserForArticleNo();
//		cout << "\t using BranchNo " << branchno << ", IBTBranchNo " << ibtbranchno << " and ArticleNo " << articleno << endl;
//
//		SessionUtil session(branchno);
//		pxOrderTransmit* xmit = session.get();
//
//		basar::Int32 remainingQuotaQty = 0;
//		if( xmit->getIbtComponentManager()->getArticleQuotaChecker()->isArticleQuotaAvailable( branchno, ibtbranchno, articleno, remainingQuotaQty ) )
//		{
//			cout << "Quota found! RemainingQuotaQty: " << remainingQuotaQty << endl;
//		}
//		else
//		{
//			cout << "No Quota found!" << endl;
//		}
//		
//	}
//}