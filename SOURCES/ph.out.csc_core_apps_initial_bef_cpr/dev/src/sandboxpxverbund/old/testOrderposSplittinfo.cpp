#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"
#include <cscorderpos/componentmanager/cscorderposcomponentmanager.h>
#include <cscorderpos/cscorderpossplittinfo/cscorderpossplittinforepository.h>
#include <cscorderpos/cscorderpossplittinfo/cscorderpossplittinfo.h>

using namespace std;

libcsc::cscorderpos::repo::ICSCOrderposSplittinfoRepositoryPtr getRepository(short branchno)
{
    SessionUtil session(branchno);
    pxOrderTransmit* xmit = session.get();

    libcsc::cscorderpos::CSCOrderposComponentManagerPtr compMgr = xmit->getCSCOrderposComponentManager();

    return compMgr->getCSCOrderposSplittinfoRepository();
}

void print(libcsc::cscorderpos::domMod::ICSCOrderposSplittinfoPtr splittinfo,
    int cscorderno, int cscorderposno, int splitttype, int date)
{
    cout
        << ((splittinfo == NULL) ? "Nothing found" : "Result") << " for"
        << " cscorderno: " << cscorderno
        << " cscorderposno: " << cscorderposno
        << " splitttype: " << splitttype
        << " date: " << date << endl;

    if (splittinfo == NULL)
    {
        return;
    }

    cout
        << ": cscorderno: " << splittinfo->getCscOrderNo()
        << " cscorderposno: " << splittinfo->getCscOrderPosNo()
        << " splitttype: " << splittinfo->getSplittType()
        << " original: " << splittinfo->getOriginal()
        << " orderno: " << splittinfo->getOrderNo()
        << " orderposno: " << splittinfo->getOrderPosNo() << endl;
}

void testOrderposSplittinfo_save()
{
    short branchno = 5;
    int cscOrderNo = 12345;
    int cscOrderPosNo = 3;
    int orderNo = 54321;
    int orderPosNo = 1;

    libcsc::cscorderpos::repo::ICSCOrderposSplittinfoRepositoryPtr repo = getRepository(branchno);

    libcsc::cscorderpos::domMod::ICSCOrderposSplittinfoPtr splittinfo =
        libcsc::cscorderpos::domMod::ICSCOrderposSplittinfoPtr(
            new libcsc::cscorderpos::domMod::CSCOrderposSplittinfo());
    splittinfo->setCscOrderNo(cscOrderNo);
    splittinfo->setCscOrderPosNo(cscOrderPosNo);
    splittinfo->setSplittType(SplittType_IBT);
    splittinfo->setOriginal(SplittPosition);
    splittinfo->setOrderNo(orderNo);
    splittinfo->setOrderPosNo(orderPosNo);

    repo->saveSplittinfo(splittinfo);

    splittinfo->setCscOrderNo(orderNo);
    splittinfo->setCscOrderPosNo(orderPosNo);
    splittinfo->setSplittType(SplittType_IBT);
    splittinfo->setOriginal(OriginalPosition);
    splittinfo->setOrderNo(cscOrderNo);
    splittinfo->setOrderPosNo(cscOrderPosNo);

    repo->saveSplittinfo(splittinfo);
}

void testOrderposSplittinfo_find()
{
    short branchno = 5;
    int cscOrderNo = 12345;
    int cscOrderPosNo = 3;
    int orderNo = 54321;
    int orderPosNo = 1;
    int date = 20181111;

    libcsc::cscorderpos::repo::ICSCOrderposSplittinfoRepositoryPtr repo = getRepository(branchno);

    libcsc::cscorderpos::domMod::ICSCOrderposSplittinfoPtr splittinfo1 =
        repo->findSplittinfo(cscOrderNo, cscOrderPosNo, SplittType_Unknown);
    splittinfo1 = splittinfo1;

    libcsc::cscorderpos::domMod::ICSCOrderposSplittinfoPtr splittinfo2 =
        repo->findSplittinfo(orderNo, orderPosNo, SplittType_IBT);
    splittinfo2 = splittinfo2;

    libcsc::cscorderpos::domMod::ICSCOrderposSplittinfoPtr splittinfo3 =
        repo->findSplittinfo(cscOrderNo, cscOrderPosNo, SplittType_IBT, date);
    splittinfo3 = splittinfo3;

    libcsc::cscorderpos::domMod::ICSCOrderposSplittinfoPtr splittinfo4 =
        repo->findSplittinfo(orderNo, orderPosNo, SplittType_IBT, date);
    splittinfo4 = splittinfo4;
}
