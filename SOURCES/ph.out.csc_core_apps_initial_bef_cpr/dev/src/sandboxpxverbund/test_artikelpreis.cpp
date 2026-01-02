#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"
#include "pxartprc.hpp"

class ArtPriceFixture
{
public:
    short branchno;
    long articleno;
    SessionUtil* session;
    pxArtPriceList* artPriceList;
    pxArtPrice* artPrice;

    ArtPriceFixture()
        : branchno(31), articleno(106), session(NULL), artPriceList(NULL), artPrice(NULL)
    {
        // Setup: Initialize shared resources
        session = new SessionUtil(branchno);
        artPriceList = new pxArtPriceList(session->get());
        artPriceList->Select(articleno);
        artPriceList->DeleteExpired();       // remove expired prices, so only

        artPrice = new pxArtPrice(session->get(), articleno);
        artPrice = new pxArtPrice(*((pxArtPrice*)artPriceList->RemoveAt(0))); // 1 entry should remain

    }

    ~ArtPriceFixture()
    {
        // Teardown: Clean up resources
        delete artPrice;
        delete artPriceList;
        delete session;
    }
};

SUITE(ArtPriceTests)
{
    TEST_FIXTURE(ArtPriceFixture, TestArtPriceInitialization)
    {
        // Verify that the pxArtPrice object is in a good state after initialization
        CHECK(artPrice->IsGoodState());
    }

    TEST_FIXTURE(ArtPriceFixture, TestArtPriceSelect)
    {
        // Test the select functionality
        CHECK_EQUAL(articleno, artPrice->ArtikelNr());
    }

    TEST_FIXTURE(ArtPriceFixture, TestArtPriceUpdate)
    {
        // Test the update functionality
        artPrice->nDBBeginTransaction();
        artPrice->Get(cDBGET_FORUPDATE);

        double currentPrice = artPrice->PreisEKGrosso();
        double newPrice = currentPrice + 10.0; // Example modification
        artPrice->PreisEKGrosso(newPrice);
        artPrice->Put();
        artPrice->nDBCommit();

        artPrice->Get();
        CHECK_EQUAL(newPrice, artPrice->PreisEKGrosso().operator double());

        // Revert the price to its original value
        artPrice->nDBBeginTransaction();
        artPrice->PreisEKGrosso(currentPrice);
        artPrice->Put();
        artPrice->nDBCommit();

        artPrice->Get();
        CHECK_EQUAL(currentPrice, artPrice->PreisEKGrosso().operator double());
    }
}