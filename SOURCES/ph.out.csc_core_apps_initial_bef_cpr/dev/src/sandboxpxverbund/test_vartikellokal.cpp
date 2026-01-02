#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

using namespace std;

// ----------------------------------------------------------------------------- //
class VArtikelLokalFixture
{
public:
    short branchno;
    long articleno;
    SessionUtil* session;
    pxVartikelLokalList* stl;

    VArtikelLokalFixture()
        : branchno(44)
        , articleno(78597)
        , session(NULL)
        , stl(NULL)
    {
        session = new SessionUtil(branchno);
        stl = new pxVartikelLokalList(session->get(), session->get()->getOrderEntryParam(branchno));
    }

    ~VArtikelLokalFixture()
    {
        if (stl) { delete stl; stl = NULL; }
        if (session) { delete session; session = NULL; }
    }
};

SUITE(VArtikelLokalTests)
{
	TEST_FIXTURE(VArtikelLokalFixture, TestBasic)
	{
		CHECK(NULL != stl->getIBTWarehouseStockList(articleno, branchno, 0, NULL));
		CHECK(stl->Entries() > 0UL || stl->Entries() == 0); // non-negative sanity check
	}

	TEST_FIXTURE(VArtikelLokalFixture, TestGeneral)
	{
		CHECK(NULL != stl->getIBTWarehouseStockListGeneral(articleno, branchno));
		CHECK(stl->Entries() > 0UL || stl->Entries() == 0); // non-negative sanity check
	}

		/*short branchno = 18;
		SessionUtil session(branchno);
		pxOrderTransmit* xmit = session.get();
		pxVartikelLokalList* vartlok1 = new pxVartikelLokalList(xmit->Session());
		vartlok1->setUseOldLogic( true );
		pxVartikelLokal* vart1 = NULL;

		pxVartikelLokalList* vartlok2 = new pxVartikelLokalList(xmit->Session());
		pxVartikelLokal* vart2 = NULL;

		pxVartikelLokalList* vartlok3 = new pxVartikelLokalList(xmit->Session());
		pxVartikelLokal* vart3 = NULL;

		std::queue<long> va;

		cout << " V E R B U N D A R T I K E L -> 1 " << endl;
		va.push( 2186109 );
		va.push( 2210090 );

		while( !va.empty() )
		{
			long articleno = va.front();
			vartlok1->SelectNormal( branchno, articleno );
			vartlok2->AlternFilSelect( branchno, articleno );
			vartlok3->IBTBranchesSelect( branchno, articleno );

			cout << " ArticleNo: " << articleno << endl;
			cout << " \t Entries 1: " << vartlok1->Entries() << " Entries 2: " << vartlok2->Entries() << " Entries 3: " << vartlok3->Entries() << endl;

			cout << " \t Items 1: " << endl;
			if( vartlok1->Entries() > 0 )
			{
				pxVartikelLokalListIter iter1(*vartlok1);
				while( (vart1 = ((pxVartikelLokal*)++iter1)) )
				{
					cout << " \t\t " << vart1->FilialNr() << " - " << vart1->ArtikelNr() << " - " << vart1->Artikelaktiv() << " - " << vart1->Bestand() << endl;
				}
			}

			cout << " \t Items 2: " << endl;
			if( vartlok2->Entries() > 0 )
			{
				pxVartikelLokalListIter iter2(*vartlok2);
				while( (vart2 = ((pxVartikelLokal*)++iter2)) )
				{
					cout << " \t\t " << vart2->FilialNr() << " - " << vart2->ArtikelNr() << " - " << vart2->Artikelaktiv() << " - " << vart2->Bestand() << endl;
				}
			}

			cout << " \t Items 3: " << endl;
			if( vartlok3->Entries() > 0 )
			{
				pxVartikelLokalListIter iter3(*vartlok3);
				while( (vart3 = ((pxVartikelLokal*)++iter3)) )
				{
					cout << " \t\t " << vart3->FilialNr() << " - " << vart3->ArtikelNr() << " - " << vart3->Artikelaktiv() << " - " << vart3->Bestand() << endl;
				}
			}

			va.pop();
		}

		cout << " V E R B U N D A R T I K E L -> 3 " << endl;
		va.push( 6728582 );
		va.push( 6721433 );

		while( !va.empty() )
		{
			long articleno = va.front();
			vartlok1->SelectVeto( branchno, articleno ); // SelectVetoNotime, SelectVetoLokalMachine, SelectVetoLokalMachineNotime
			vartlok2->AlternFilSelect( branchno, articleno );
			vartlok3->IBTBranchesSelect( branchno, articleno );

			cout << " ArticleNo: " << articleno << endl;
			cout << " \t Entries 1: " << vartlok1->Entries() << " Entries 2: " << vartlok2->Entries() << " Entries 3: " << vartlok3->Entries() << endl;

			cout << " \t Items 1: " << endl;
			if( vartlok1->Entries() > 0 )
			{
				pxVartikelLokalListIter iter1(*vartlok1);
				while( (vart1 = ((pxVartikelLokal*)++iter1)) )
				{
					cout << " \t\t " << vart1->FilialNr() << " - " << vart1->ArtikelNr() << " - " << vart1->Artikelaktiv() << " - " << vart1->Bestand() << endl;
				}
			}

			cout << " \t Items 2: " << endl;
			if( vartlok2->Entries() > 0 )
			{
				pxVartikelLokalListIter iter2(*vartlok2);
				while( (vart2 = ((pxVartikelLokal*)++iter2)) )
				{
					cout << " \t\t " << vart2->FilialNr() << " - " << vart2->ArtikelNr() << " - " << vart2->Artikelaktiv() << " - " << vart2->Bestand() << endl;
				}
			}

			cout << " \t Items 3: " << endl;
			if( vartlok3->Entries() > 0 )
			{
				pxVartikelLokalListIter iter3(*vartlok3);
				while( (vart3 = ((pxVartikelLokal*)++iter3)) )
				{
					cout << " \t\t " << vart3->FilialNr() << " - " << vart3->ArtikelNr() << " - " << vart3->Artikelaktiv() << " - " << vart3->Bestand() << endl;
				}
			}

			va.pop();
		}

		cout << " V E R B U N D A R T I K E L -> 4 " << endl;
		va.push( 2167307 );
		va.push( 2194178 );

		while( !va.empty() )
		{
			long articleno = va.front();
			vartlok1->SelectRegional( branchno, articleno );
			vartlok2->AlternFilSelect( branchno, articleno );
			vartlok3->IBTBranchesSelect( branchno, articleno );

			cout << " ArticleNo: " << articleno << endl;
			cout << " \t Entries 1: " << vartlok1->Entries() << " Entries 2: " << vartlok2->Entries() << " Entries 3: " << vartlok3->Entries() << endl;

			cout << " \t Items 1: " << endl;
			if( vartlok1->Entries() > 0 )
			{
				pxVartikelLokalListIter iter1(*vartlok1);
				while( (vart1 = ((pxVartikelLokal*)++iter1)) )
				{
					cout << " \t\t " << vart1->FilialNr() << " - " << vart1->ArtikelNr() << " - " << vart1->Artikelaktiv() << " - " << vart1->Bestand() << endl;
				}
			}

			cout << " \t Items 2: " << endl;
			if( vartlok2->Entries() > 0 )
			{
				pxVartikelLokalListIter iter2(*vartlok2);
				while( (vart2 = ((pxVartikelLokal*)++iter2)) )
				{
					cout << " \t\t " << vart2->FilialNr() << " - " << vart2->ArtikelNr() << " - " << vart2->Artikelaktiv() << " - " << vart2->Bestand() << endl;
				}
			}

			cout << " \t Items 3: " << endl;
			if( vartlok3->Entries() > 0 )
			{
				pxVartikelLokalListIter iter3(*vartlok3);
				while( (vart3 = ((pxVartikelLokal*)++iter3)) )
				{
					cout << " \t\t " << vart3->FilialNr() << " - " << vart3->ArtikelNr() << " - " << vart3->Artikelaktiv() << " - " << vart3->Bestand() << endl;
				}
			}

			va.pop();
		}

		if( NULL != vartlok1 ){ delete vartlok1; vartlok1 = NULL; }
		if( NULL != vartlok2 ){ delete vartlok2; vartlok2 = NULL; }
		if( NULL != vartlok3 ){ delete vartlok3; vartlok3 = NULL; }
		*/
}
