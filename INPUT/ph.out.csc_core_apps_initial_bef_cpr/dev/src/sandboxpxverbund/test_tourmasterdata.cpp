#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

class TourMasterDataFixture
{
public:
    short branchno;
    SessionUtil* session;
    pxOrderTransmit* xmit;
    nString tourid;

    TourMasterDataFixture()
        : branchno(33), session(NULL), xmit(NULL), tourid("103208")
    {
        // Setup: Initialisiere gemeinsam genutzte Ressourcen
        session = new SessionUtil(branchno);
        xmit = session->get();
    }

    ~TourMasterDataFixture()
    {
        // Teardown: Bereinige Ressourcen
        delete session;
    }

    void showTourMasterData(TourMasterData* it)
    {
		CHECK(it != NULL);
		//std::cout << "\t ==========================================================" << std::endl;
		//std::cout << "\t BranchNo    : [" << it->getBranchNo() << "]" << std::endl;
		//std::cout << "\t TourID      : [" << it->getTourID() << "]" << std::endl;
		//std::cout << "\t PickingDate : [" << it->getPickingDate() << "]" << std::endl;
		//std::cout << "\t DecTour     : [" << it->getDecTour() << "]" << std::endl;
    }
};

SUITE(TourMasterData)
{
    TEST_FIXTURE(TourMasterDataFixture, TestGetTourMasterData)
    {
        TourMasterDataList* l = new TourMasterDataList(xmit->Session());
        l->getTourMasterData(branchno, tourid);
        if (l->Entries())
        {
            TourMasterDataListIter iter(*l);
            TourMasterData* it = NULL;
            while ((it = (TourMasterData*)++iter) != NULL)
            {
                showTourMasterData(it);
            }
        }
        delete l;
    }
}
