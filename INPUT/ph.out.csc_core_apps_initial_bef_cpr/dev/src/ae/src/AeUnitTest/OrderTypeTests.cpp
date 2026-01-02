#include "stdafx.h"
#include "CppUnitTest.h"

#include <OrderType.h>
#include "OrderTypeModelMock.h"

#include <boost/make_shared.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AeUnitTest
{
    TEST_CLASS(COrderTypeTests)
    {
    private:
        boost::shared_ptr<COrderType> _pOrderType;
        boost::shared_ptr<COrderTypeModelMock> _pModel;

    public:
        COrderTypeTests()
        {
            _pModel = boost::make_shared<COrderTypeModelMock>();
            _pOrderType = boost::make_shared<COrderType>(_pModel);
        }

        TEST_METHOD_INITIALIZE(Initialize)
        {
        }

        TEST_METHOD_CLEANUP(Cleanup)
        {
        }

        TEST_METHOD(GetAufArtenListeVZ_NoDataInDB_OTnotFound)
        {
            short sBranchNo = 5;
            int index = 0;
            CString strOrderType;

            int rc = _pOrderType->GetAufArtenListeVZ(sBranchNo, index, strOrderType);

            Assert::AreEqual(-1, rc);
            Assert::IsTrue(strOrderType.IsEmpty());
        }

        TEST_METHOD(GetAufArtenListeVZ_NoDataForBranchInDB_OTnotFound)
        {
            short sBranchNo = 5;
            int index = 0;
            CString strOrderType;

            auftragsartS ot;
            ot.BRANCHNO = 81;
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            int rc = _pOrderType->GetAufArtenListeVZ(sBranchNo, index, strOrderType);

            Assert::AreEqual(-1, rc);
            Assert::IsTrue(strOrderType.IsEmpty());
        }

        TEST_METHOD(GetAufArtenListeVZ_DataForBranchInDB_SSTANDARDis1_OTfound)
        {
            short sBranchNo = 5;
            int index = 0;
            CString strOrderType;

            CString strOrderType0 = "NO";
            CString strOrderTypeName0 = "Normal";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            strcpy_s(ot.KDAUFTRAGART, strOrderType0.GetString());
            strcpy_s(ot.BEZEICHNUNG, strOrderTypeName0.GetString());
            ot.SSTANDARD[0] = '1';
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            int rc = _pOrderType->GetAufArtenListeVZ(sBranchNo, index, strOrderType);

            CString strOrderTypeExp = FormatOrderType(strOrderType0, strOrderTypeName0);

            Assert::AreEqual(1, rc);
            Assert::AreEqual(strOrderTypeExp.GetString(), strOrderType.GetString());
        }

        TEST_METHOD(GetAufArtenListeVZ_DataForBranchInDB_DataLoadedTwoTimes_OTfound)
        {
            short sBranchNo = 5;
            int index = 0;
            CString strOrderType;

            CString strOrderType0 = "NO";
            CString strOrderTypeName0 = "Normal";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            strcpy_s(ot.KDAUFTRAGART, strOrderType0.GetString());
            strcpy_s(ot.BEZEICHNUNG, strOrderTypeName0.GetString());
            ot.SSTANDARD[0] = '1';
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            // Data loaded first time
            int rc = _pOrderType->GetAufArtenListeVZ(sBranchNo, index, strOrderType);

            // Data already in memory
            rc = _pOrderType->GetAufArtenListeVZ(sBranchNo, index, strOrderType);

            CString strOrderTypeExp = FormatOrderType(strOrderType0, strOrderTypeName0);

            Assert::AreEqual(1, rc);
            Assert::AreEqual(strOrderTypeExp.GetString(), strOrderType.GetString());
        }

        TEST_METHOD(GetAufArtenListeVZ_DataForBranchInDB_SSTANDARDis0_OTfound)
        {
            short sBranchNo = 5;
            int index = 0;
            CString strOrderType;

            CString strOrderType0 = "NO";
            CString strOrderTypeName0 = "Normal";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            strcpy_s(ot.KDAUFTRAGART, strOrderType0.GetString());
            strcpy_s(ot.BEZEICHNUNG, strOrderTypeName0.GetString());
            ot.SSTANDARD[0] = '0';
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            int rc = _pOrderType->GetAufArtenListeVZ(sBranchNo, index, strOrderType);

            CString strOrderTypeExp = FormatOrderType(strOrderType0, strOrderTypeName0);

            Assert::AreEqual(0, rc);
            Assert::AreEqual(strOrderTypeExp.GetString(), strOrderType.GetString());
        }

        TEST_METHOD(GetAufArtenListeVZ_DataForBranchInDB_indexTooBig_OTnotFound)
        {
            short sBranchNo = 5;
            int index = 1;
            CString strOrderType;

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            int rc = _pOrderType->GetAufArtenListeVZ(sBranchNo, index, strOrderType);

            Assert::AreEqual(-1, rc);
            Assert::IsTrue(strOrderType.IsEmpty());
        }

        TEST_METHOD(GetAufArtenListeVZ_DataForBranchInDB_AtIndex_OTfound)
        {
            short sBranchNo = 5;
            int index = 1;
            CString strOrderType;

            CString strOrderType0 = "NO";
            CString strOrderTypeName0 = "Normal";
            CString strOrderType1 = "DI";
            CString strOrderTypeName1 = "Dispo";
            CString strOrderType2 = "NL";
            CString strOrderTypeName2 = "Nachlieferung";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            strcpy_s(ot.KDAUFTRAGART, strOrderType0.GetString());
            strcpy_s(ot.BEZEICHNUNG, strOrderTypeName0.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            strcpy_s(ot.BEZEICHNUNG, strOrderTypeName1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType2.GetString());
            strcpy_s(ot.BEZEICHNUNG, strOrderTypeName2.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            int rc = _pOrderType->GetAufArtenListeVZ(sBranchNo, index, strOrderType);

            CString strOrderTypeExp = FormatOrderType(strOrderType1, strOrderTypeName1);

            Assert::AreEqual(strOrderTypeExp.GetString(), strOrderType.GetString());
        }

        TEST_METHOD(GetAufArtenListeVZ_DataForBranchInDB_SBILDSCHIRMis0_OTignored)
        {
            short sBranchNo = 5;
            int index = 0;
            CString strOrderType;

            CString strOrderType0 = "NO";
            CString strOrderTypeName0 = "Normal";
            CString strOrderType1 = "DI";
            CString strOrderTypeName1 = "Dispo";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SBILDSCHIRM[0] = '0';
            strcpy_s(ot.KDAUFTRAGART, strOrderType0.GetString());
            strcpy_s(ot.BEZEICHNUNG, strOrderTypeName0.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            ot.SBILDSCHIRM[0] = '1';
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            strcpy_s(ot.BEZEICHNUNG, strOrderTypeName1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            int rc = _pOrderType->GetAufArtenListeVZ(sBranchNo, index, strOrderType);

            CString strOrderTypeExp = FormatOrderType(strOrderType1, strOrderTypeName1);

            Assert::AreEqual(strOrderTypeExp.GetString(), strOrderType.GetString());
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IsOnlyEH
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TEST_METHOD(IsOnlyEH_true_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SONLYEH[0] = '1';

            bool rc = _pOrderType->IsOnlyEH(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsOnlyEH_true_DataLoadedTwoTimes_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SONLYEH[0] = '1';

            // Data loaded first time
            bool rc = _pOrderType->IsOnlyEH(sBranchNo, strOrderType0);

            // Data already in memory
            rc = _pOrderType->IsOnlyEH(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsOnlyEH_false_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SONLYEH[0] = '0';

            bool rc = _pOrderType->IsOnlyEH(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsOnlyEH_NoDataForBranchInDB_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SONLYEH[0] = '1';

            bool rc = _pOrderType->IsOnlyEH(81, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsOnlyEH_KdAuftragartDoesNotMatch_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SONLYEH[0] = '1';

            bool rc = _pOrderType->IsOnlyEH(sBranchNo, "DI");

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsOnlyEH_MultipleKdAuftragart_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SONLYEH[0] = '1';

            CString strOrderType1 = "DI";
            CString strOrderType2 = "NL";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SONLYEH[0] = '1';
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType2.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            bool rc = _pOrderType->IsOnlyEH(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IsNatraAufArt
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TEST_METHOD(IsNatraAufArt_true_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].DISINKINDENTERABLE[0] = '1';

            bool rc = _pOrderType->IsNatraAufArt(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsNatraAufArt_true_DataLoadedTwoTimes_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].DISINKINDENTERABLE[0] = '1';

            // Data loaded first time
            bool rc = _pOrderType->IsNatraAufArt(sBranchNo, strOrderType0);

            // Data already in memory
            rc = _pOrderType->IsNatraAufArt(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsNatraAufArt_false_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].DISINKINDENTERABLE[0] = '0';

            bool rc = _pOrderType->IsNatraAufArt(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsNatraAufArt_NoDataForBranchInDB_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].DISINKINDENTERABLE[0] = '1';

            bool rc = _pOrderType->IsNatraAufArt(81, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsNatraAufArt_KdAuftragartDoesNotMatch_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].DISINKINDENTERABLE[0] = '1';

            bool rc = _pOrderType->IsNatraAufArt(sBranchNo, "DI");

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsNatraAufArt_MultipleKdAuftragart_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].DISINKINDENTERABLE[0] = '1';

            CString strOrderType1 = "DI";
            CString strOrderType2 = "NL";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.DISINKINDENTERABLE[0] = '1';
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType2.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            bool rc = _pOrderType->IsNatraAufArt(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IsAufArtDefaultKennung
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TEST_METHOD(IsAufArtDefaultKennung_true_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SDEFAULTKENNUNG = 1;

            bool rc = _pOrderType->IsAufArtDefaultKennung(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsAufArtDefaultKennung_true_DataLoadedTwoTimes_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SDEFAULTKENNUNG = 1;

            // Data loaded first time
            bool rc = _pOrderType->IsAufArtDefaultKennung(sBranchNo, strOrderType0);

            // Data already in memory
            rc = _pOrderType->IsAufArtDefaultKennung(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsAufArtDefaultKennung_false_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SDEFAULTKENNUNG = 0;

            bool rc = _pOrderType->IsAufArtDefaultKennung(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsAufArtDefaultKennung_NoDataForBranchInDB_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SDEFAULTKENNUNG = 1;

            bool rc = _pOrderType->IsAufArtDefaultKennung(81, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsAufArtDefaultKennung_KdAuftragartDoesNotMatch_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SDEFAULTKENNUNG = 1;

            bool rc = _pOrderType->IsAufArtDefaultKennung(sBranchNo, "DI");

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsAufArtDefaultKennung_MultipleKdAuftragart_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SDEFAULTKENNUNG = 1;

            CString strOrderType1 = "DI";
            CString strOrderType2 = "NL";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SDEFAULTKENNUNG = 1;
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType2.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            bool rc = _pOrderType->IsAufArtDefaultKennung(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IsAufArtNoPromo
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TEST_METHOD(IsAufArtNoPromo_true_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNOPROMOTIONS = 1;

            bool rc = _pOrderType->IsAufArtNoPromo(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsAufArtNoPromo_true_DataLoadedTwoTimes_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNOPROMOTIONS = 1;

            // Data loaded first time
            bool rc = _pOrderType->IsAufArtNoPromo(sBranchNo, strOrderType0);

            // Data already in memory
            rc = _pOrderType->IsAufArtNoPromo(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsAufArtNoPromo_false_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNOPROMOTIONS = 0;

            bool rc = _pOrderType->IsAufArtNoPromo(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsAufArtNoPromo_NoDataForBranchInDB_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNOPROMOTIONS = 1;

            bool rc = _pOrderType->IsAufArtNoPromo(81, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsAufArtNoPromo_KdAuftragartDoesNotMatch_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNOPROMOTIONS = 1;

            bool rc = _pOrderType->IsAufArtNoPromo(sBranchNo, "DI");

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsAufArtNoPromo_MultipleKdAuftragart_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNOPROMOTIONS = 1;

            CString strOrderType1 = "DI";
            CString strOrderType2 = "NL";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SNOPROMOTIONS = 1;
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType2.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            bool rc = _pOrderType->IsAufArtNoPromo(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IsGlobalAufArt
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TEST_METHOD(IsGlobalAufArt_true_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SGLOBAL[0] = '1';

            bool rc = _pOrderType->IsGlobalAufArt(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsGlobalAufArt_true_DataLoadedTwoTimes_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SGLOBAL[0] = '1';

            // Data loaded first time
            bool rc = _pOrderType->IsGlobalAufArt(sBranchNo, strOrderType0);

            // Data already in memory
            rc = _pOrderType->IsGlobalAufArt(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsGlobalAufArt_false_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SGLOBAL[0] = '0';

            bool rc = _pOrderType->IsGlobalAufArt(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsGlobalAufArt_NoDataForBranchInDB_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SGLOBAL[0] = '1';

            bool rc = _pOrderType->IsGlobalAufArt(81, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsGlobalAufArt_KdAuftragartDoesNotMatch_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SGLOBAL[0] = '1';

            bool rc = _pOrderType->IsGlobalAufArt(sBranchNo, "DI");

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsGlobalAufArt_MultipleKdAuftragart_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SGLOBAL[0] = '1';

            CString strOrderType1 = "DI";
            CString strOrderType2 = "NL";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SGLOBAL[0] = '1';
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType2.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            bool rc = _pOrderType->IsGlobalAufArt(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IsAufArtIVCNo
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TEST_METHOD(IsAufArtIVCNo_true_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SIVCVOUCHERNO = 1;

            bool rc = _pOrderType->IsAufArtIVCNo(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsAufArtIVCNo_true_DataLoadedTwoTimes_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SIVCVOUCHERNO = 1;

            // Data loaded first time
            bool rc = _pOrderType->IsAufArtIVCNo(sBranchNo, strOrderType0);

            // Data already in memory
            rc = _pOrderType->IsAufArtIVCNo(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsAufArtIVCNo_false_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SIVCVOUCHERNO = 0;

            bool rc = _pOrderType->IsAufArtIVCNo(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsAufArtIVCNo_NoDataForBranchInDB_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SIVCVOUCHERNO = 1;

            bool rc = _pOrderType->IsAufArtIVCNo(81, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsAufArtIVCNo_KdAuftragartDoesNotMatch_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SIVCVOUCHERNO = 1;

            bool rc = _pOrderType->IsAufArtIVCNo(sBranchNo, "DI");

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsAufArtIVCNo_MultipleKdAuftragart_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SIVCVOUCHERNO = 1;

            CString strOrderType1 = "DI";
            CString strOrderType2 = "NL";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SIVCVOUCHERNO = 1;
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType2.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            bool rc = _pOrderType->IsAufArtIVCNo(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IsAufArtOriginalInvoiceNo
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TEST_METHOD(IsAufArtOriginalInvoiceNo_true_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SORIGINALINVOICENO = 1;

            bool rc = _pOrderType->IsAufArtOriginalInvoiceNo(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsAufArtOriginalInvoiceNo_true_DataLoadedTwoTimes_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SORIGINALINVOICENO = 1;

            // Data loaded first time
            bool rc = _pOrderType->IsAufArtOriginalInvoiceNo(sBranchNo, strOrderType0);

            // Data already in memory
            rc = _pOrderType->IsAufArtOriginalInvoiceNo(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsAufArtOriginalInvoiceNo_false_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SORIGINALINVOICENO = 0;

            bool rc = _pOrderType->IsAufArtOriginalInvoiceNo(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsAufArtOriginalInvoiceNo_NoDataForBranchInDB_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SORIGINALINVOICENO = 1;

            bool rc = _pOrderType->IsAufArtOriginalInvoiceNo(81, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsAufArtOriginalInvoiceNo_KdAuftragartDoesNotMatch_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SORIGINALINVOICENO = 1;

            bool rc = _pOrderType->IsAufArtOriginalInvoiceNo(sBranchNo, "DI");

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsAufArtOriginalInvoiceNo_MultipleKdAuftragart_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SORIGINALINVOICENO = 1;

            CString strOrderType1 = "DI";
            CString strOrderType2 = "NL";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SORIGINALINVOICENO = 1;
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType2.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            bool rc = _pOrderType->IsAufArtOriginalInvoiceNo(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IsAufArtMustHeadline
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TEST_METHOD(IsAufArtMustHeadline_true_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SMUSTHEADLINE = 1;

            bool rc = _pOrderType->IsAufArtMustHeadline(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsAufArtMustHeadline_true_DataLoadedTwoTimes_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SMUSTHEADLINE = 1;

            // Data loaded first time
            bool rc = _pOrderType->IsAufArtMustHeadline(sBranchNo, strOrderType0);

            // Data already in memory
            rc = _pOrderType->IsAufArtMustHeadline(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsAufArtMustHeadline_false_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SMUSTHEADLINE = 0;

            bool rc = _pOrderType->IsAufArtMustHeadline(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsAufArtMustHeadline_NoDataForBranchInDB_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SMUSTHEADLINE = 1;

            bool rc = _pOrderType->IsAufArtMustHeadline(81, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsAufArtMustHeadline_KdAuftragartDoesNotMatch_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SMUSTHEADLINE = 1;

            bool rc = _pOrderType->IsAufArtMustHeadline(sBranchNo, "DI");

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsAufArtMustHeadline_MultipleKdAuftragart_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SMUSTHEADLINE = 1;

            CString strOrderType1 = "DI";
            CString strOrderType2 = "NL";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SMUSTHEADLINE = 1;
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType2.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            bool rc = _pOrderType->IsAufArtMustHeadline(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IsMustSubOrder
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TEST_METHOD(IsMustSubOrder_true_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SMUSTSUBORDER[0] = '1';

            bool rc = _pOrderType->IsMustSubOrder(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsMustSubOrder_true_DataLoadedTwoTimes_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SMUSTSUBORDER[0] = '1';

            // Data loaded first time
            bool rc = _pOrderType->IsMustSubOrder(sBranchNo, strOrderType0);

            // Data already in memory
            rc = _pOrderType->IsMustSubOrder(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsMustSubOrder_false_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SMUSTSUBORDER[0] = '0';

            bool rc = _pOrderType->IsMustSubOrder(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsMustSubOrder_NoDataForBranchInDB_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SMUSTSUBORDER[0] = '1';

            bool rc = _pOrderType->IsMustSubOrder(81, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsMustSubOrder_KdAuftragartDoesNotMatch_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SMUSTSUBORDER[0] = '1';

            bool rc = _pOrderType->IsMustSubOrder(sBranchNo, "DI");

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsMustSubOrder_MultipleKdAuftragart_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SMUSTSUBORDER[0] = '1';

            CString strOrderType1 = "DI";
            CString strOrderType2 = "NL";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SMUSTSUBORDER[0] = '1';
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType2.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            bool rc = _pOrderType->IsMustSubOrder(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IsNoVideoAufArt
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TEST_METHOD(IsNoVideoAufArt_SBILDSCHIRMis1_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SBILDSCHIRM[0] = '1';

            bool rc = _pOrderType->IsNoVideoAufArt(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsNoVideoAufArt_SBILDSCHIRMis1_DataLoadedTwoTimes_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SBILDSCHIRM[0] = '1';

            // Data loaded first time
            bool rc = _pOrderType->IsNoVideoAufArt(sBranchNo, strOrderType0);

            // Data already in memory
            rc = _pOrderType->IsNoVideoAufArt(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsNoVideoAufArt_SBILDSCHIRMis0_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SBILDSCHIRM[0] = '0';

            bool rc = _pOrderType->IsNoVideoAufArt(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsNoVideoAufArt_NoDataForBranchInDB_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SBILDSCHIRM[0] = '0';

            bool rc = _pOrderType->IsNoVideoAufArt(81, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsNoVideoAufArt_KdAuftragartDoesNotMatch_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SBILDSCHIRM[0] = '0';

            bool rc = _pOrderType->IsNoVideoAufArt(sBranchNo, "DI");

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsNoVideoAufArt_SBILDSCHIRMis0_MultipleKdAuftragart_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SBILDSCHIRM[0] = '0';

            CString strOrderType1 = "DI";
            CString strOrderType2 = "NL";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SBILDSCHIRM[0] = '0';
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType2.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            bool rc = _pOrderType->IsNoVideoAufArt(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IsFreePrice
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TEST_METHOD(IsFreePrice_true_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SFREEPRICE[0] = '1';

            bool rc = _pOrderType->IsFreePrice(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsFreePrice_true_DataLoadedTwoTimes_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SFREEPRICE[0] = '1';

            // Data loaded first time
            bool rc = _pOrderType->IsFreePrice(sBranchNo, strOrderType0);

            // Data already in memory
            rc = _pOrderType->IsFreePrice(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsFreePrice_false_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SFREEPRICE[0] = '0';

            bool rc = _pOrderType->IsFreePrice(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsFreePrice_NoDataForBranchInDB_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SFREEPRICE[0] = '1';

            bool rc = _pOrderType->IsFreePrice(81, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsFreePrice_KdAuftragartDoesNotMatch_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SFREEPRICE[0] = '1';

            bool rc = _pOrderType->IsFreePrice(sBranchNo, "DI");

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsFreePrice_KdAuftragartDoesNotMatch_Reload_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SFREEPRICE[0] = '1';

            CString strOrderType1 = "DI";

            bool rc = _pOrderType->IsFreePrice(sBranchNo, strOrderType1);

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SFREEPRICE[0] = '1';
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            rc = _pOrderType->IsFreePrice(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsFreePrice_MultipleKdAuftragart_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SFREEPRICE[0] = '1';

            CString strOrderType1 = "DI";
            CString strOrderType2 = "NL";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SFREEPRICE[0] = '1';
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType2.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            bool rc = _pOrderType->IsFreePrice(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IsNachlief
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TEST_METHOD(IsNachlief_true_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SRESTDEL[0] = '1';

            bool rc = _pOrderType->IsNachlief(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsNachlief_true_DataLoadedTwoTimes_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SRESTDEL[0] = '1';

            // Data loaded first time
            bool rc = _pOrderType->IsNachlief(sBranchNo, strOrderType0);

            // Data already in memory
            rc = _pOrderType->IsNachlief(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsNachlief_false_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SRESTDEL[0] = '0';

            bool rc = _pOrderType->IsNachlief(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsNachlief_NoDataForBranchInDB_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SRESTDEL[0] = '1';

            bool rc = _pOrderType->IsNachlief(81, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsNachlief_KdAuftragartDoesNotMatch_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SRESTDEL[0] = '1';

            bool rc = _pOrderType->IsNachlief(sBranchNo, "DI");

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsNachlief_KdAuftragartDoesNotMatch_Reload_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SRESTDEL[0] = '1';

            CString strOrderType1 = "DI";

            bool rc = _pOrderType->IsNachlief(sBranchNo, strOrderType1);

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SRESTDEL[0] = '1';
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            rc = _pOrderType->IsNachlief(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsNachlief_MultipleKdAuftragart_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SRESTDEL[0] = '1';

            CString strOrderType1 = "DI";
            CString strOrderType2 = "NL";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SRESTDEL[0] = '1';
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType2.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            bool rc = _pOrderType->IsNachlief(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IsQuota
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TEST_METHOD(IsQuota_SNOQUOTAis1_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNOQUOTA[0] = '1';

            bool rc = _pOrderType->IsQuota(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsQuota_SNOQUOTAis1_DataLoadedTwoTimes_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNOQUOTA[0] = '1';

            // Data loaded first time
            bool rc = _pOrderType->IsQuota(sBranchNo, strOrderType0);

            // Data already in memory
            rc = _pOrderType->IsQuota(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsQuota_SNOQUOTAis0_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNOQUOTA[0] = '0';

            bool rc = _pOrderType->IsQuota(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsQuota_NoDataForBranchInDB_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNOQUOTA[0] = '0';

            bool rc = _pOrderType->IsQuota(81, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsQuota_KdAuftragartDoesNotMatch_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNOQUOTA[0] = '0';

            bool rc = _pOrderType->IsQuota(sBranchNo, "DI");

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsQuota_KdAuftragartDoesNotMatch_SNOQUOTAis1_Reload_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNOQUOTA[0] = '1';

            CString strOrderType1 = "DI";

            bool rc = _pOrderType->IsQuota(sBranchNo, strOrderType1);

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SNOQUOTA[0] = '1';
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            rc = _pOrderType->IsQuota(sBranchNo, strOrderType1);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsQuota_SNOQUOTAis0_MultipleKdAuftragart_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNOQUOTA[0] = '0';

            CString strOrderType1 = "DI";
            CString strOrderType2 = "NL";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SNOQUOTA[0] = '0';
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType2.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            bool rc = _pOrderType->IsQuota(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // IsNoDD
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TEST_METHOD(IsNoDD_true_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNODD[0] = '1';

            bool rc = _pOrderType->IsNoDD(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsNoDD_true_DataLoadedTwoTimes_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNODD[0] = '1';

            // Data loaded first time
            bool rc = _pOrderType->IsNoDD(sBranchNo, strOrderType0);

            // Data already in memory
            rc = _pOrderType->IsNoDD(sBranchNo, strOrderType0);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsNoDD_false_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNODD[0] = '0';

            bool rc = _pOrderType->IsNoDD(sBranchNo, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsNoDD_NoDataForBranchInDB_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNODD[0] = '1';

            bool rc = _pOrderType->IsNoDD(81, strOrderType0);

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsNoDD_KdAuftragartDoesNotMatch_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNODD[0] = '1';

            bool rc = _pOrderType->IsNoDD(sBranchNo, "DI");

            Assert::IsFalse(rc);
        }

        TEST_METHOD(IsNoDD_KdAuftragartDoesNotMatch_Reload_true)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNODD[0] = '1';

            CString strOrderType1 = "DI";

            bool rc = _pOrderType->IsNoDD(sBranchNo, strOrderType1);

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SNODD[0] = '1';
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            rc = _pOrderType->IsNoDD(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

        TEST_METHOD(IsNoDD_MultipleKdAuftragart_false)
        {
            short sBranchNo;
            CString strOrderType0;
            PrepareAttributeTest(sBranchNo, strOrderType0);
            _pModel->OrderTypes.begin()->second[0].SNODD[0] = '1';

            CString strOrderType1 = "DI";
            CString strOrderType2 = "NL";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            ot.SNODD[0] = '1';
            strcpy_s(ot.KDAUFTRAGART, strOrderType1.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
            strcpy_s(ot.KDAUFTRAGART, strOrderType2.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);

            bool rc = _pOrderType->IsNoDD(sBranchNo, strOrderType1);

            Assert::IsTrue(rc);
        }

    private:
        CString FormatOrderType(const CString& strOrderType, const CString& strOrderTypeName)
        {
            CString strOrderTypeFormatted;
            strOrderTypeFormatted.Format("%*.*s - %*.*s",
                L_AUFTRAGSART_KDAUFTRAGART, L_AUFTRAGSART_KDAUFTRAGART, strOrderType.GetString(),
                L_AUFTRAGSART_BEZEICHNUNG, L_AUFTRAGSART_BEZEICHNUNG, strOrderTypeName.GetString());
            return strOrderTypeFormatted;
        }

        void PrepareAttributeTest(short& sBranchNo, CString& strOrderType0)
        {
            sBranchNo = 5;
            strOrderType0 = "NO";

            auftragsartS ot;
            ot.BRANCHNO = sBranchNo;
            strcpy_s(ot.KDAUFTRAGART, strOrderType0.GetString());
            _pModel->OrderTypes[ot.BRANCHNO].push_back(ot);
        }
    };
}
