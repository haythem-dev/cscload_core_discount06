#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"
#include "pxartbas.hpp"
#include "pxbartik.hpp"
#include "pxartmas.hpp"

class ArtBaseFixture
{
public:
    short branchno;
    long articleno;
    SessionUtil* session;
    pxArtBase* artBase;

    ArtBaseFixture()
        : branchno(31), articleno(106), session(NULL), artBase(NULL)
    {
        // Setup: Initialize shared resources
        session = new SessionUtil(branchno);
        artBase = pxArtBase::CreateArticle(session->get(), articleno, branchno); // Example article number: 106
    }

    ~ArtBaseFixture()
    {
        // Teardown: Clean up resources
        delete artBase;
        delete session;
    }
};

SUITE(ArtBaseTests)
{
    TEST_FIXTURE(ArtBaseFixture, TestArtBaseInitialization)
    {
        // Verify that the pxArtBase object is in a good state after initialization
        CHECK(artBase->IsGoodState());
    }

    TEST_FIXTURE(ArtBaseFixture, TestArtBaseArticleNumber)
    {
        // Verify that the article number is correctly set
        CHECK_EQUAL(articleno, artBase->ArtikelNr());
    }

    TEST_FIXTURE(ArtBaseFixture, TestArtBaseStockField)
    {
        // Test to read, modify, and save the stock field
        artBase->Session()->nDBBeginTransaction();
        artBase->Get(cDBGET_FORUPDATE);

        // Read the current stock value
        int currentStock = dynamic_cast<pxBArtikel*>(artBase)->GetQuantity();

        // Modify the stock value
        int newStock = currentStock + 10; // Example modification
        dynamic_cast<pxBArtikel*>(artBase)->SetQuantity(newStock);
        artBase->Put();
        artBase->Session()->nDBCommit();

        // Verify the stock value was updated
        artBase->Get();
        CHECK_EQUAL(newStock, dynamic_cast<pxBArtikel*>(artBase)->GetQuantity());

        // Revert the stock value to its original state
        artBase->Session()->nDBBeginTransaction();
        dynamic_cast<pxBArtikel*>(artBase)->SetQuantity(currentStock);
        artBase->Put();
        artBase->Session()->nDBCommit();

        // Verify the stock value was reverted
        artBase->Get();
        CHECK_EQUAL(currentStock, dynamic_cast<pxBArtikel*>(artBase)->GetQuantity());
    }
}

class ArtMasterFixture
{
public:
    short branchno;
    long articleno;
    SessionUtil* session;
    pxArtMaster* artMaster;

    ArtMasterFixture()
        : branchno(31), articleno(106), session(NULL), artMaster(NULL)
    {
        // Setup: Initialize shared resources
        session = new SessionUtil(branchno);
        artMaster = new pxArtMaster(session->get(), articleno);
    }

    ~ArtMasterFixture()
    {
        // Teardown: Clean up resources
        delete artMaster;
        delete session;
    }
};

SUITE(ArtMasterTests)
{
    TEST_FIXTURE(ArtMasterFixture, TestArtMasterSelect)
    {
        // Test the select functionality
        CHECK(artMaster->IsGoodState());
        CHECK_EQUAL(articleno, artMaster->ArtikelNr());
    }

    TEST_FIXTURE(ArtMasterFixture, TestArtMasterUpdate)
    {
        // Test the update functionality
        artMaster->nDBBeginTransaction();
        artMaster->Get(cDBGET_FORUPDATE);
        bool ohneZertifikat = artMaster->ArtMFlags().IsOhneZertifikat();
        if (artMaster->ArtMFlags().IsOhneZertifikat())
            artMaster->ArtMFlags().ClearOhneZertifikat();
        else
            artMaster->ArtMFlags().SetOhneZertifikat();
        artMaster->Put();
        artMaster->nDBCommit();

        artMaster->nDBBeginTransaction();
        artMaster->Get(cDBGET_FORUPDATE);
        CHECK(artMaster->IsGoodState());
        CHECK(artMaster->ArtMFlags().IsOhneZertifikat() != ohneZertifikat);

        // Revert the change
        if (true == ohneZertifikat)
            artMaster->ArtMFlags().SetOhneZertifikat();
        else
            artMaster->ArtMFlags().ClearOhneZertifikat();

        artMaster->Put();
        artMaster->nDBCommit();

        artMaster->Get();
        CHECK(artMaster->IsGoodState());
        CHECK(artMaster->ArtMFlags().IsOhneZertifikat() == ohneZertifikat);
    }
}
