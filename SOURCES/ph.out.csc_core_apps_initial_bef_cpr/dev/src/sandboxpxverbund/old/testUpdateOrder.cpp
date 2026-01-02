#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

void testUpdateOrder()
{
    int auftrag = 4848;
    short vz = 5;
    int pos = 1;
    int mengeneu = 5;

    SessionUtil session(vz);

    pxOrderTransmit* xmit = session.get();

    pxOrder* ord = new pxOrder(xmit,auftrag, cDBGET_DEFAULT);

    if (ord == NULL)
    {
        std::cout << "not found" << std::endl;
        return;
    }

    std::cout << "-> Order: \t"
        << "KdAuftragNr: [" << ord->KdAuftragNr() << "] "
        << "IDFNr: [" << ord->IDFNr() << "] "
        << "FilialNr: [" << ord->FilialNr() << "] "
        << "AnzPos: [" << ord->AnzPos() << "] "
        << std::endl;

    pxOrderItem* item = new pxOrderItem(xmit, auftrag, pos, cDBGET_FORUPDATE);
    if (item->ErrorState() != 0)
    {
        std::cout << "error:" << item->ErrorState() << "; " << item->ErrorMsg() << "; "
            << item->ErrorNumber() << "; " << item->ErrorString() << "; " << item->ErrorType() << std::endl;
        return;
    }

    if (ord->AnzPos() < pos)
    {
        std::cout << "position does not exist" << std::endl;
        return;
    }

    std::cout << "-> OrderItem: \t"
        << "KdAuftragNr: [" << item->KdAuftragNr() << "] "
        << "PosNr: [" << item->PosNr() << "] "
        << "ArtikelNr: [" << item->ArtikelNr() << "] "
        << "MengeBestellt: [" << item->MengeBestellt() << "] "
        << "MengeBestaetigt: [" << item->MengeBestaetigt() << "] "
        << std::endl;

    item->OrderRef(*ord);
    item->MengeBestaetigt(mengeneu);
    item->nDBBeginTransaction(cDBTransRecord);
    item->Put();
    if (item->ErrorState() != 0)
    {
        item->nDBRollBack();
        std::cout << "error:" << item->ErrorState() << "; " << item->ErrorMsg() << "; "
            << item->ErrorNumber() << "; " << item->ErrorString() << "; " << item->ErrorType() << std::endl;
        return;
    }
    item->nDBCommit();
}
