#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

// ------------------------------------------------------------------------------------------- //
void testTenderHead()
{	

	//short branchno = 85;
	//long customerno = 31041;
	//long tenderno = 2828;
	//long tenderno2 = 5103;

	//char temp[200];		
	//sprintf((char*)temp,"%d SetTenderNo Error: Branch[%d] Customer[%d] TenderNo[%d]", (int)999999, (int)99, (int)1234567, (int)tenderno );								
	//nString message(temp);
	//pxGenericOrderRemarkList remarklist( xmit->Session() );
	//remarklist.AddOrderRemark( 999999, 0, pxOrderRemarkType::eErrorLogging, message );		

	//int ok = 0;
	//int err1 = 0;
	//int err2 = 0;
	//int err3 = 0;

	//for( int i = 0; i < 1000; ++i )
	//{
	//	pxTenderHead th( xmit->Session(), tenderno, branchno, customerno );					
	//	if( th.IsGoodState() )
	//	{
	//		th.Get();
	//		if( th.IsGoodState() )
	//		{
	//			if( th.TenderNo() == tenderno )
	//			{
	//				std::cout << "OK pxTenderHead: " << tenderno << " == " << th.TenderNo() << " Contract: " << th.ContractNo() << std::endl;
	//				++ok;
	//			}
	//			else
	//			{
	//				std::cout << "ERROR Wrong TenderNo: " << tenderno << " == " << th.TenderNo() << " Contract: " << th.ContractNo() << std::endl;
	//				++err3;
	//			}
	//		}
	//		else
	//		{
	//			std::cout << "ERROR pxTenderHead: not GoodState (A)" << std::endl;
	//			++err1;
	//		}
	//	}
	//	else
	//	{
	//		std::cout << "ERROR pxTenderHead not GoodState (B)" << std::endl;
	//		++err2;
	//	}

	//	pxTenderHead th2( xmit->Session(), tenderno2, branchno, customerno );					
	//	if( th2.IsGoodState() )
	//	{
	//		th2.Get();
	//		if( th2.IsGoodState() )
	//		{
	//			if( th2.TenderNo() == tenderno2 )
	//			{
	//				std::cout << "OK pxTenderHead: " << tenderno2 << " == " << th2.TenderNo() << " Contract: " << th2.ContractNo() << std::endl;
	//				++ok;
	//			}
	//			else
	//			{
	//				std::cout << "ERROR Wrong TenderNo: " << tenderno2 << " == " << th2.TenderNo() << " Contract: " << th2.ContractNo() << std::endl;
	//				++err3;
	//			}
	//		}
	//		else
	//		{
	//			std::cout << "ERROR pxTenderHead: not GoodState (A2)" << std::endl;
	//			++err1;
	//		}
	//	}
	//	else
	//	{
	//		std::cout << "ERROR pxTenderHead not GoodState (B2)" << std::endl;
	//		++err2;
	//	}

	//	


	//	/*pxTenderHead th( xmit->Session(), tenderno, branchno, customerno );					
	//	int retval = th.Get();
	//	if( 0 == retval )			
	//	{
	//		if( th.TenderNo() != tenderno )
	//		{
	//			std::cout << "ERROR pxTenderHead: Wrong TenderNo: " << tenderno << " != " << th.TenderNo() << " Contract: " << th.ContractNo() << std::endl;
	//			++err1;
	//		}			
	//		else
	//		{
	//			//std::cout << "OK pxTenderHead: " << tenderno << " == " << th.TenderNo() << " Contract: " << th.ContractNo() << std::endl;
	//			++ok;
	//		}
	//	}
	//	else
	//	{
	//		std::cout << "ERROR pxTenderHead: Get returned: " << retval << std::endl;
	//		++err2;
	//	}*/
	//}

	//std::cout << "OK  : " << ok   << std::endl;
	//std::cout << "ERR1: " << err1 << std::endl;
	//std::cout << "ERR2: " << err2 << std::endl;
	//std::cout << "ERR3: " << err3 << std::endl;
}
