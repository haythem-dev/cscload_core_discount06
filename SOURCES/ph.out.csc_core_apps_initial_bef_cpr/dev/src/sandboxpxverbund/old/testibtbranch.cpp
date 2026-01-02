#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

using namespace std;

// ------------------------------------------------------------------------------------------- //
//void showIBTBranch(IBTBranch* ib)
//{
//	if( NULL == ib )
//	{
//		return;
//	}
//	
//			
//	cout	<< "\t\tLocalBranchNo:" << ib->getLocalBranchNo() << " | "
//			<< "CustomerNo:" << ib->getCustomerNo() << " | "
//			<< "PickingDate:" << ib->getPickingDate() << " | "
//			<< "IBTBranchNo:" << ib->getIBTBranchNo() << " | "
//			<< "TourId:" << ib->getTourId() << " | "
//			<< "IBTCustomerNo:" << ib->getIBTCustomerNo() << " | "
//			<< "IBTType:" << ib->getIBTType() << " | "
//			<< "DayIBT:" << ib->isDayIBT() << " | "
//			<< endl;			
//}

// ------------------------------------------------------------------------------------------- //
void showIBTBranchesItem( IBTBranches* ib )
{
	if( NULL == ib )
	{
		return;
	}
		
	cout	<< "\t\tLocalBranchNo:" << ib->getBranchNo() << " | "			
			<< "IBTBranchNo:" << ib->getIBTBranchNo() << " | "			
			<< "IBTCustomerNo:" << ib->getIBTCustomerNo() << " | "
			<< "IBTType:" << ib->getIBTType() << " | "
			<< "DayIBT:" << ib->getDayIBT() << " | "
			<< "Priority: " << ib->getPriority() << " | " 
			<< endl;			
}

// ------------------------------------------------------------------------------------------- //
void showIBTBranchesList( IBTBranchesList* ibl )
{
	if( NULL == ibl )
	{
		return;
	}
	if( ibl->Entries() == 0 )
	{
		cout << "No IBTBranches available." << endl;
	}
	else
	{
		IBTBranchesListIter iter(*ibl);
		IBTBranches* ib = NULL;					
		while ( (ib = (IBTBranches*)++iter) != NULL )
		{
			showIBTBranchesItem(ib);
		}
	}	
}


// ------------------------------------------------------------------------------------------- //
void testIBTBranches()
{
	short branchno = 30;
	short ibtbranchno = 32;

	SessionUtil session(branchno);
	pxOrderTransmit* xmit = session.get();
	IBTBranchesList* ibtbrancheslist = new IBTBranchesList( xmit->Session() );

	cout << "Search ibtbranches for IBTProductNone: " << endl;
	ibtbrancheslist->getIBTBranchesByIBTType( branchno, ibtbranchno, pxArtFiliale::IBTProductNone );
	showIBTBranchesList( ibtbrancheslist );

	cout << "Search ibtbranches for IBTProductNormal: " << endl;
	ibtbrancheslist->getIBTBranchesByIBTType( branchno, ibtbranchno, pxArtFiliale::IBTProductNormal );
	showIBTBranchesList( ibtbrancheslist );

	cout << "Search ibtbranches for IBTProductPrivatSortiment: " << endl;
	ibtbrancheslist->getIBTBranchesByIBTType( branchno, ibtbranchno, pxArtFiliale::IBTProductPrivatSortiment );
	showIBTBranchesList( ibtbrancheslist );

	cout << "Search ibtbranches for IBTProductVeterinary: " << endl;
	ibtbrancheslist->getIBTBranchesByIBTType( branchno, ibtbranchno, pxArtFiliale::IBTProductVeterinary );
	showIBTBranchesList( ibtbrancheslist );

	cout << "Search ibtbranches for IBTProductRegional: " << endl;
	ibtbrancheslist->getIBTBranchesByIBTType( branchno, ibtbranchno, pxArtFiliale::IBTProductRegional );
	showIBTBranchesList( ibtbrancheslist );

	cout << "Search ibtbranches for IBTProductNational: " << endl;
	ibtbrancheslist->getIBTBranchesByIBTType( branchno, ibtbranchno, pxArtFiliale::IBTProductNational );
	showIBTBranchesList( ibtbrancheslist );

	cout << "Search ibtbranches for IBTProductNatRegional: " << endl;
	ibtbrancheslist->getIBTBranchesByIBTType( branchno, ibtbranchno, pxArtFiliale::IBTProductNatRegional );
	showIBTBranchesList( ibtbrancheslist );

	cout << "Search ibtbranches for IBTProductLokNational: " << endl;
	ibtbrancheslist->getIBTBranchesByIBTType( branchno, ibtbranchno, pxArtFiliale::IBTProductLokNational );
	showIBTBranchesList( ibtbrancheslist );

	cout << "Search ibtbranches for IBTProductLokRegional: " << endl;
	ibtbrancheslist->getIBTBranchesByIBTType( branchno, ibtbranchno, pxArtFiliale::IBTProductLokRegional );
	showIBTBranchesList( ibtbrancheslist );

	cout << "Search ibtbranches for IBTProductOverAll: " << endl;
	ibtbrancheslist->getIBTBranchesByIBTType( branchno, ibtbranchno, pxArtFiliale::IBTProductOverAll );
	showIBTBranchesList( ibtbrancheslist );	
}

// ------------------------------------------------------------------------------------------- //
//void testIBTBranch()
//{
//	SessionUtil session(33);
//	pxOrderTransmit* xmit = session.get();
//
//	short localbranchno = 33;
//	short customerno = 19063;
//	short ibtbranchno = 31;
//	short ibttype = 0;
//
//	pxOrderEntryParam* oeparam = new pxOrderEntryParam( xmit->Session(), localbranchno );
//	IBTBranchList* ibtbranchlist = new IBTBranchList( xmit->Session(), oeparam );
//
//	{
//		cout << "\tGet DAY IBT" << endl;
//		ibtbranchlist->getIBTBranches( localbranchno, customerno, ibtbranchno, 4, true );
//		IBTBranchListIter iter(*ibtbranchlist);
//		IBTBranch* ib = NULL;			
//		showIBTBranch( NULL );
//		while ( (ib = (IBTBranch*)++iter) != NULL )
//		{
//			showIBTBranch(ib);
//		}
//	}
//
//	{
//		cout << "\tGet NO DAY IBT" << endl;
//		ibtbranchlist->getIBTBranches( localbranchno, customerno, ibtbranchno, ibttype );
//		IBTBranchListIter iter(*ibtbranchlist);
//		IBTBranch* ib = NULL;			
//		showIBTBranch( NULL );
//		while ( (ib = (IBTBranch*)++iter) != NULL )
//		{
//			showIBTBranch(ib);
//		}
//	}
//}
