#include "stdafx.h"
#include "CppUnitTest.h"

#include <AeAppPresenter.h>
#include "AeAppModelMock.h"

#include <boost/make_shared.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AeUnitTest
{
    TEST_CLASS(CAeAppTests)
    {
    private:
        boost::shared_ptr<CAeAppPresenter> _pPresenter;
        boost::shared_ptr<CAeAppModelMock> _pModel;

    public:
        CAeAppTests()
        {
            _pModel = boost::make_shared<CAeAppModelMock>();
            _pPresenter = boost::make_shared<CAeAppPresenter>(_pModel);
        }

        TEST_METHOD_INITIALIZE(Initialize)
        {
        }

        TEST_METHOD_CLEANUP(Cleanup)
        {
        }

        ///////////////////////////////////////////////////////////////////////////////////
        // IsKABAKomb
        ///////////////////////////////////////////////////////////////////////////////////

        TEST_METHOD(IsKABAKomb_NoDataInDB_ValueNotFound)
        {
            bool ret = _pPresenter->IsKABAKomb(5, "AA", "K", "B");

            Assert::IsFalse(ret);
        }

        TEST_METHOD(IsKABAKomb_NoDataForBranchInDB_ValueNotFound)
        {
            KaBaKomb_Add(81, "", "", "");

            bool ret = _pPresenter->IsKABAKomb(5, "AA", "K", "B");

            Assert::IsFalse(ret);
        }

        TEST_METHOD(IsKABAKomb_NoDataForBranchInDB_NoMatchingAufArt_ValueNotFound)
        {
            short sBranchNo = 5;
            CString strAufArt = "";
            CString strKA = "K";
            CString strBA = "B";

            KaBaKomb_Add(sBranchNo, strAufArt, strKA, strBA);

            bool ret = _pPresenter->IsKABAKomb(sBranchNo, "AA", strKA, strBA);

            Assert::IsFalse(ret);
        }

        TEST_METHOD(IsKABAKomb_NoDataForBranchInDB_NoMatchingKA_ValueNotFound)
        {
            short sBranchNo = 5;
            CString strAufArt = "AA";
            CString strKA = "";
            CString strBA = "B";

            KaBaKomb_Add(sBranchNo, strAufArt, strKA, strBA);

            bool ret = _pPresenter->IsKABAKomb(sBranchNo, strAufArt, "K", strBA);

            Assert::IsFalse(ret);
        }

        TEST_METHOD(IsKABAKomb_NoDataForBranchInDB_NoMatchingBA_ValueNotFound)
        {
            short sBranchNo = 5;
            CString strAufArt = "AA";
            CString strKA = "K";
            CString strBA = "";

            KaBaKomb_Add(sBranchNo, strAufArt, strKA, strBA);

            bool ret = _pPresenter->IsKABAKomb(sBranchNo, strAufArt, strKA, "B");

            Assert::IsFalse(ret);
        }

        TEST_METHOD(IsKABAKomb_MatchingDataInDB_ValueFound)
        {
            short sBranchNo = 5;
            CString strAufArt = "AA";
            CString strKA = "K";
            CString strBA = "B";

            KaBaKomb_Add(sBranchNo, strAufArt, strKA, strBA);

            bool ret = _pPresenter->IsKABAKomb(sBranchNo, strAufArt, strKA, strBA);

            Assert::IsTrue(ret);
        }

    private:
        void KaBaKomb_Add(short sBranchNo, CString strAufArt, CString strKA, CString strBA)
        {
            PARKABAKOMB parkabakomb;
            parkabakomb.VERTRIEBSZENTRUMNR = sBranchNo;
            strcpy_s(parkabakomb.KDAUFTRAGART, LS_PARKABAKOMB_KDAUFTRAGART, strAufArt.GetString());
            strcpy_s(parkabakomb.KOART, LS_PARKABAKOMB_KOART, strKA.GetString());
            strcpy_s(parkabakomb.BUCHART, LS_PARKABAKOMB_BUCHART, strBA.GetString());
            _pModel->KaBaKomb[parkabakomb.VERTRIEBSZENTRUMNR].push_back(parkabakomb);
        }
    public:

        ///////////////////////////////////////////////////////////////////////////////////
        // GetKoArtenListeVZ
        ///////////////////////////////////////////////////////////////////////////////////

        TEST_METHOD(GetKoArtenListeVZ_NoDataInDB_ValueNotFound)
        {
            CString KoArt;
            int rc = _pPresenter->GetKoArtenListeVZ(5, 0, KoArt);

            Assert::AreEqual(rc, -1);
        }

        TEST_METHOD(GetKoArtenListeVZ_NoDataForBranchInDB_ValueNotFound)
        {
            KoArt_Add(81, "", "");

            CString KoArt;
            int rc = _pPresenter->GetKoArtenListeVZ(5, 0, KoArt);

            Assert::AreEqual(rc, -1);
        }

        TEST_METHOD(GetKoArtenListeVZ_IndexTooBig_ValueNotFound)
        {
            short sBranchNo = 5;

            KoArt_Add(sBranchNo, "A", "Bez1");
            KoArt_Add(sBranchNo, "B", "Bez2");

            CString KoArt;
            int rc = _pPresenter->GetKoArtenListeVZ(sBranchNo, 9, KoArt);

            Assert::AreEqual(rc, -1);
        }

        TEST_METHOD(GetKoArtenListeVZ_IndexLowerBound_ValueFound)
        {
            short sBranchNo = 5;

            KoArt_Add(sBranchNo, "A", "Bez1");
            KoArt_Add(sBranchNo, "B", "Bez2");

            CString KoArt;
            int rc = _pPresenter->GetKoArtenListeVZ(sBranchNo, 0, KoArt);

            Assert::AreEqual(rc, 0);
        }

        TEST_METHOD(GetKoArtenListeVZ_IndexUpperBound_ValueFound)
        {
            short sBranchNo = 5;

            KoArt_Add(sBranchNo, "A", "Bez1");
            KoArt_Add(sBranchNo, "B", "Bez2");

            CString KoArt;
            int rc = _pPresenter->GetKoArtenListeVZ(sBranchNo, 1, KoArt);

            Assert::AreEqual(rc, 0);
        }

    private:
        void KoArt_Add(short sBranchNo, CString strKA, CString strBez)
        {
            PARKOART parkoart;
            parkoart.BRANCHNO = sBranchNo;
            strcpy_s(parkoart.KOART, LS_PARKOART_KOART, strKA.GetString());
            strcpy_s(parkoart.BEZEICHNUNG, LS_PARKOART_BEZEICHNUNG, strBez.GetString());
            _pModel->KoArt[parkoart.BRANCHNO].push_back(parkoart);
        }
    public:

        ///////////////////////////////////////////////////////////////////////////////////
        // GetBranchName
        ///////////////////////////////////////////////////////////////////////////////////

        TEST_METHOD(GetBranchName_NoDataInDB_ValueNotFound)
        {
            CString BranchName;
            _pPresenter->GetBranchName(5, BranchName);

            Assert::AreEqual(BranchName, "");
        }

        TEST_METHOD(GetBranchName_NoDataForBranchInDB_ValueNotFound)
        {
            Rechner_Add(81, "Bez");

            CString BranchName;
            _pPresenter->GetBranchName(5, BranchName);

            Assert::AreEqual(BranchName, "");
        }

        TEST_METHOD(GetBranchName_ValueFound)
        {
            short sBranchNo = 5;
            CString strBranchName = "Bez";

            Rechner_Add(sBranchNo, strBranchName);

            CString BranchName;
            _pPresenter->GetBranchName(sBranchNo, BranchName);

            Assert::AreEqual(BranchName, strBranchName.GetString());
        }

    private:
        void Rechner_Add(short sBranchNo, CString strLocation)
        {
            branchnamesS branchnames;
            branchnames.FILIALNR = sBranchNo;
            strcpy_s(branchnames.STANDORT, 16, strLocation.GetString());
            _pModel->Rechner.push_back(branchnames);
        }
    public:

        ///////////////////////////////////////////////////////////////////////////////////
        // GetRemarkTypes
        ///////////////////////////////////////////////////////////////////////////////////

        TEST_METHOD(GetRemarkTypes_NoDataInDB_ValueNotFound)
        {
            CString RemarkName;
            _pPresenter->GetRemarkTypes(0, RemarkName);

            Assert::AreEqual(RemarkName, "");
        }

        TEST_METHOD(GetRemarkTypes_NoDataForBranchInDB_ValueNotFound)
        {
            Remarktypes_Add(0, "Remark");

            CString RemarkName;
            _pPresenter->GetRemarkTypes(4, RemarkName);

            Assert::AreEqual(RemarkName, "");
        }

        TEST_METHOD(GetRemarkTypes_ValueFound)
        {
            short sRemarkType = 0;
            CString strRemarkName = "Remark";

            Remarktypes_Add(sRemarkType, strRemarkName);

            CString RemarkName;
            _pPresenter->GetRemarkTypes(sRemarkType, RemarkName);

            Assert::AreEqual(RemarkName, strRemarkName.GetString());
        }

    private:
        void Remarktypes_Add(short sRemarkType, CString strRemarkName)
        {
            remarktypesS remarktypes;
            remarktypes.REMARKTYPE = sRemarkType;
            strcpy_s(remarktypes.REMARKNAME, 51, strRemarkName.GetString());
            _pModel->Remarktypes.push_back(remarktypes);
        }
    public:

        ///////////////////////////////////////////////////////////////////////////////////
        // GetBuArtenListeVZ
        ///////////////////////////////////////////////////////////////////////////////////

        TEST_METHOD(GetBuArtenListeVZ_NoDataInDB_ValueNotFound)
        {
            CString BuArt;
            int rc = _pPresenter->GetBuArtenListeVZ(5, 0, BuArt);

            Assert::AreEqual(rc, -1);
        }

        TEST_METHOD(GetBuArtenListeVZ_NoDataForBranchInDB_ValueNotFound)
        {
            BuArt_Add(81, "", "");

            CString BuArt;
            int rc = _pPresenter->GetBuArtenListeVZ(5, 0, BuArt);

            Assert::AreEqual(rc, -1);
        }

        TEST_METHOD(GetBuArtenListeVZ_IndexTooBig_ValueNotFound)
        {
            short sBranchNo = 5;

            BuArt_Add(sBranchNo, "A", "Bez1");
            BuArt_Add(sBranchNo, "B", "Bez2");

            CString BuArt;
            int rc = _pPresenter->GetBuArtenListeVZ(sBranchNo, 9, BuArt);

            Assert::AreEqual(rc, -1);
        }

        TEST_METHOD(GetBuArtenListeVZ_IndexLowerBound_ValueFound)
        {
            short sBranchNo = 5;

            BuArt_Add(sBranchNo, "A", "Bez1");
            BuArt_Add(sBranchNo, "B", "Bez2");

            CString BuArt;
            int rc = _pPresenter->GetBuArtenListeVZ(sBranchNo, 0, BuArt);

            Assert::AreEqual(rc, 0);
        }

        TEST_METHOD(GetBuArtenListeVZ_IndexUpperBound_ValueFound)
        {
            short sBranchNo = 5;

            BuArt_Add(sBranchNo, "A", "Bez1");
            BuArt_Add(sBranchNo, "B", "Bez2");

            CString BuArt;
            int rc = _pPresenter->GetBuArtenListeVZ(sBranchNo, 1, BuArt);

            Assert::AreEqual(rc, 0);
        }

    private:
        void BuArt_Add(short sBranchNo, CString strBA, CString strBez)
        {
            PARBUCHART parbuchart;
            parbuchart.BRANCHNO = sBranchNo;
            strcpy_s(parbuchart.BUCHART, LS_PARBUCHART_BUCHART, strBA.GetString());
            strcpy_s(parbuchart.BEZEICHNUNG, LS_PARBUCHART_BEZEICHNUNG, strBez.GetString());
            _pModel->BuArt[parbuchart.BRANCHNO].push_back(parbuchart);
        }
    public:

        ///////////////////////////////////////////////////////////////////////////////////
        // GetTaxRates
        ///////////////////////////////////////////////////////////////////////////////////

        TEST_METHOD(GetTaxRates_NoDataInDB_ValueNotFound)
        {
            char Std;
            double TaxRate;
            int rc = _pPresenter->GetTaxRates(0, Std, TaxRate);

            Assert::AreEqual(rc, -1);
        }

        TEST_METHOD(GetTaxRates_IndexTooBig_ValueNotFound)
        {
            Taxes_Add(7.0, 'A');
            Taxes_Add(19.0, 'B');

            char Std;
            double TaxRate;
            int rc = _pPresenter->GetTaxRates(9, Std, TaxRate);

            Assert::AreEqual(rc, -1);
        }

        TEST_METHOD(GetTaxRates_IndexLowerBound_ValueFound)
        {
            Taxes_Add(7.0, 'A');
            Taxes_Add(19.0, 'B');

            char Std;
            double TaxRate;
            int rc = _pPresenter->GetTaxRates(0, Std, TaxRate);

            Assert::AreEqual(rc, 0);
        }

        TEST_METHOD(GetTaxRates_IndexUpperBound_ValueFound)
        {
            Taxes_Add(7.0, 'A');
            Taxes_Add(19.0, 'B');

            char Std;
            double TaxRate;
            int rc = _pPresenter->GetTaxRates(1, Std, TaxRate);

            Assert::AreEqual(rc, 0);
        }

    private:
        void Taxes_Add(double sSalesTaxRate, char cDefaultTax)
        {
            taxesS taxes;
            taxes.SALESTAXRATE = sSalesTaxRate;
            taxes.DEFAULTTAX[0] = cDefaultTax;
            _pModel->Taxes.push_back(taxes);
        }
    public:

        ///////////////////////////////////////////////////////////////////////////////////
        // GetBranchesOfRegion
        ///////////////////////////////////////////////////////////////////////////////////

        TEST_METHOD(GetBranchesOfRegion_NoDataInDB_ValueNotFound)
        {
            const std::vector<Filiale>& branches = _pPresenter->GetBranchesOfRegion(5);

            Assert::IsTrue(branches.empty());
        }

        TEST_METHOD(GetBranchesOfRegion_NoDataForBranchInDB_ValueNotFound)
        {
            Filiale_Add(81, 1, "Name");

            const std::vector<Filiale>& branches = _pPresenter->GetBranchesOfRegion(5);

            Assert::IsTrue(branches.empty());
        }

        TEST_METHOD(GetBranchesOfRegion_DataForBranchInDB_ValueFound)
        {
            Filiale_Add(5, 1, "Name");

            const std::vector<Filiale>& branches = _pPresenter->GetBranchesOfRegion(5);

            Assert::IsFalse(branches.empty());
        }

    private:
        void Filiale_Add(short sBranchNo, short sRegionTeilNr, CString strName)
        {
            Filiale filiale;
            filiale.RegionTeilNr = sRegionTeilNr;
            filiale.Name = strName;
            _pModel->Filialen[sBranchNo].push_back(filiale);
        }
    };
}
