#include "stdafx.h"
#include "CppUnitTest.h"

#include <Country.h>
#include <DAufDefImpl.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AeUnitTest
{
    TEST_CLASS(RemoveBGAndRSOrderTypesTests)
    {
    private:
        CCountry _country;
        CDAufDefImpl* pImpl;

    public:
        TEST_METHOD_INITIALIZE(Initialize)
        {
            _country.SetCountry("BG");
            pImpl = new CDAufDefImpl(_country);
        }

        TEST_METHOD_CLEANUP(Cleanup)
        {
            delete pImpl;
        }

        TEST_METHOD(RemoveBGAndRSOrderTypes_NotIsBGAndNotIsRS_false)
        {
            _country.SetCountry("DE");

            Assert::IsFalse(pImpl->RemoveBGAndRSOrderTypes("", ""));
        }

        TEST_METHOD(RemoveBGAndRSOrderTypes_IsBG_TO_NotTO_true)
        {
            Assert::IsTrue(pImpl->RemoveBGAndRSOrderTypes("TO", ""));
        }

        TEST_METHOD(RemoveBGAndRSOrderTypes_IsBG_NotTO_TO_true)
        {
            Assert::IsTrue(pImpl->RemoveBGAndRSOrderTypes("", "TO"));
        }

        TEST_METHOD(RemoveBGAndRSOrderTypes_IsBG_TO_TO_false)
        {
            Assert::IsFalse(pImpl->RemoveBGAndRSOrderTypes("TO", "TO"));
        }

        TEST_METHOD(RemoveBGAndRSOrderTypes_IsBG_TI_NotTI_true)
        {
            Assert::IsTrue(pImpl->RemoveBGAndRSOrderTypes("TI", ""));
        }

        TEST_METHOD(RemoveBGAndRSOrderTypes_IsBG_NotTI_TI_true)
        {
            Assert::IsTrue(pImpl->RemoveBGAndRSOrderTypes("", "TI"));
        }

        TEST_METHOD(RemoveBGAndRSOrderTypes_IsBG_TI_TI_false)
        {
            Assert::IsFalse(pImpl->RemoveBGAndRSOrderTypes("TI", "TI"));
        }
    };
}
