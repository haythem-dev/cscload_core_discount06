#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

#include <blockedarticles/componentmanager/blockedarticlescomponentmanagerptr.h>
#include <blockedarticles/componentmanager/blockedarticlescomponentmanager.h>

#include <blockedarticles/blockedarticles.h>
#include <blockedarticles/blockedarticlesrepository.h>
#include <blockedarticles/blockedarticlesrepositoryptr.h>

using namespace std;
// ------------------------------------------------------------------------------------------- //
void testBlockedArticles()
{
	SessionUtil session(33);
	pxOrderTransmit* xmit = session.get();
	short branchNo = 33;
	int blockID = 7654321;

	cout << "\tUsing BranchNo:" << branchNo << " BlockID:" << blockID << endl;

	libcsc::blockedarticles::BlockedArticlesComponentManagerPtr comp = xmit->getBlockedArticlesComponentManager();
	libcsc::blockedarticles::IBlockedArticlesRepositoryPtr repo = comp->getBlockedArticlesRepository();
	libcsc::blockedarticles::BlockedArticlesCollectionPtr coll = repo->findBlockedArticles(branchNo, blockID);
	libcsc::blockedarticles::BlockedArticlesCollection::iterator it =  coll->begin();

	while (coll->end() != it)
	{
		cout << "\tBranchNo:" << (*it)->getBranchNo() << endl;
		cout << "\tArticleNo:" << (*it)->getArticleNo() << endl;
		cout << "\tBlockedID:" << (*it)->getBlockedID() << endl;
		cout << "\tStorageLocation:" << (*it)->getStorageLocation() << endl;
		cout << "\tQuantity:" << (*it)->getQuantity() << endl;
		cout << "\tBookingType:" << (*it)->getBookingType() << endl;
		cout << "\tCreationDate:" << (*it)->getCreationDate() << endl;
		cout << "\tCreationTime:" << (*it)->getCreationTime() << endl;
		cout << "\tProcessedDate:" << (*it)->getProcessedDate() << endl;
		cout << "\tProcessedTime:" << (*it)->getProcessedTime() << endl;

		++it;
	}
}

void testUpdateBlockedArticles()
{
	SessionUtil session(33);
	pxOrderTransmit* xmit = session.get();
	short branchNo = 33;
	int blockID = 7654321;

	cout << "\tUsing BranchNo:" << branchNo << " BlockID:" << blockID << endl;

	libcsc::blockedarticles::BlockedArticlesComponentManagerPtr comp = xmit->getBlockedArticlesComponentManager();
	libcsc::blockedarticles::IBlockedArticlesRepositoryPtr repo = comp->getBlockedArticlesRepository();
	libcsc::blockedarticles::BlockedArticlesCollectionPtr coll = repo->findBlockedArticles(branchNo, blockID);
	libcsc::blockedarticles::BlockedArticlesCollection::iterator it = coll->begin();

	if (coll->end() != it)
	{
		cout << "\tBranchNo:" << (*it)->getBranchNo() << endl;
		cout << "\tArticleNo:" << (*it)->getArticleNo() << endl;
		cout << "\tBlockedID:" << (*it)->getBlockedID() << endl;
		cout << "\tStorageLocation:" << (*it)->getStorageLocation() << endl;
		cout << "\tQuantity:" << (*it)->getQuantity() << endl;
		cout << "\tBookingType:" << (*it)->getBookingType() << endl;
		cout << "\tCreationDate:" << (*it)->getCreationDate() << endl;
		cout << "\tCreationTime:" << (*it)->getCreationTime() << endl;
		cout << "\tProcessedDate:" << (*it)->getProcessedDate() << endl;
		cout << "\tProcessedTime:" << (*it)->getProcessedTime() << endl;

		(*it)->setProcessedDate(1234);
		(*it)->setProcessedTime(12456);

		repo->saveBlockedArticle((*it));

		cout << "\tBranchNo:" << (*it)->getBranchNo() << endl;
		cout << "\tArticleNo:" << (*it)->getArticleNo() << endl;
		cout << "\tBlockedID:" << (*it)->getBlockedID() << endl;
		cout << "\tStorageLocation:" << (*it)->getStorageLocation() << endl;
		cout << "\tQuantity:" << (*it)->getQuantity() << endl;
		cout << "\tBookingType:" << (*it)->getBookingType() << endl;
		cout << "\tCreationDate:" << (*it)->getCreationDate() << endl;
		cout << "\tCreationTime:" << (*it)->getCreationTime() << endl;
		cout << "\tProcessedDate:" << (*it)->getProcessedDate() << endl;
		cout << "\tProcessedTime:" << (*it)->getProcessedTime() << endl;

		++it;
	}
}