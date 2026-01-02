#include "stdafx.h"
#include "CppUnitTest.h"

#include <PriceType.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AeUnitTest
{
    TEST_CLASS(CPriceTypeTests)
    {
    public:
        TEST_METHOD_INITIALIZE(Initialize)
        {
        }

        TEST_METHOD_CLEANUP(Cleanup)
        {
        }

        TEST_METHOD(CorrectPriceType3_PriceTypeNot3_OpiIsChanger_EinzelhandelIsChanger_PriceTypeWasNotChanged)
        {
            short sPriceTypeExp = 9;
            short sPriceType = 9;
            CString strOpi = "1";
            CString strEinzelhandel = "1";

            sPriceType = CPriceType::CorrectPriceType3(sPriceType, strOpi, strEinzelhandel);

            Assert::AreEqual(sPriceTypeExp, sPriceType);
        }

        TEST_METHOD(CorrectPriceType3_PriceType3_OpiIsChanger_EinzelhandelIsNoChanger_PriceTypeWasNotChangedTo0)
        {
            short sPriceTypeExp = 0;
            short sPriceType = 3;
            CString strOpi = "1";
            CString strEinzelhandel = "0";

            sPriceType = CPriceType::CorrectPriceType3(sPriceType, strOpi, strEinzelhandel);

            Assert::AreEqual(sPriceTypeExp, sPriceType);
        }

        TEST_METHOD(CorrectPriceType3_PriceType3_OpiIsNoChanger_EinzelhandelIsChanger_PriceTypeWasNotChangedTo0)
        {
            short sPriceTypeExp = 0;
            short sPriceType = 3;
            CString strOpi = "0";
            CString strEinzelhandel = "1";

            sPriceType = CPriceType::CorrectPriceType3(sPriceType, strOpi, strEinzelhandel);

            Assert::AreEqual(sPriceTypeExp, sPriceType);
        }

        TEST_METHOD(CorrectPriceType3_PriceType3_OpiIsChanger_EinzelhandelIsChanger_PriceTypeWasNotChangedTo0)
        {
            short sPriceTypeExp = 0;
            short sPriceType = 3;
            CString strOpi = "1";
            CString strEinzelhandel = "1";

            sPriceType = CPriceType::CorrectPriceType3(sPriceType, strOpi, strEinzelhandel);

            Assert::AreEqual(sPriceTypeExp, sPriceType);
        }

        TEST_METHOD(CorrectPriceType3_PriceType3_OpiIsNoChanger_EinzelhandelIsNoChanger_PriceTypeWasNotChangedTo2)
        {
            short sPriceTypeExp = 2;
            short sPriceType = 3;
            CString strOpi = "0";
            CString strEinzelhandel = "0";

            sPriceType = CPriceType::CorrectPriceType3(sPriceType, strOpi, strEinzelhandel);

            Assert::AreEqual(sPriceTypeExp, sPriceType);
        }
    };
}
