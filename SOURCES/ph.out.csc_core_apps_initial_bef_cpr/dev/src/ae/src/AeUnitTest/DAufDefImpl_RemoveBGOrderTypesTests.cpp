#include "stdafx.h"
#include "CppUnitTest.h"

#include <Country.h>
#include <DAufDefImpl.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AeUnitTest
{
    TEST_CLASS(RemoveBGOrderTypesTests)
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

        TEST_METHOD(RemoveBGOrderTypes_NotIsBG_false)
        {
            _country.SetCountry("DE");

            Assert::IsFalse(pImpl->RemoveBGOrderTypes("", ""));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_CO_NotCO_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("CO", ""));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_CO_CO_false)
        {
            Assert::IsFalse(pImpl->RemoveBGOrderTypes("CO", "CO"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_NO_NotCOAndNotNO_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("NO", ""));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_NO_CO_false)
        {
            Assert::IsFalse(pImpl->RemoveBGOrderTypes("NO", "CO"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_NO_NO_false)
        {
            Assert::IsFalse(pImpl->RemoveBGOrderTypes("NO", "NO"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_MP_NotMP_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("MP", ""));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_NotMP_MP_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("", "MP"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_MP_MP_false)
        {
            Assert::IsFalse(pImpl->RemoveBGOrderTypes("MP", "MP"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_EH_NotEH_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("EH", ""));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_NotEH_EH_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("", "EH"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_EH_EH_false)
        {
            Assert::IsFalse(pImpl->RemoveBGOrderTypes("EH", "EH"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_RO_NotRO_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("RO", ""));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_NotRO_RO_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("", "RO"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_RO_RO_false)
        {
            Assert::IsFalse(pImpl->RemoveBGOrderTypes("RO", "RO"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_S1_NotS1_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("S1", ""));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_NotS1_S1_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("", "S1"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_S1_S1_false)
        {
            Assert::IsFalse(pImpl->RemoveBGOrderTypes("S1", "S1"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_S2_NotS2_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("S2", ""));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_NotS2_S2_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("", "S2"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_S2_S2_false)
        {
            Assert::IsFalse(pImpl->RemoveBGOrderTypes("S2", "S2"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_S3_NotS3_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("S3", ""));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_NotS3_S3_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("", "S3"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_S3_S3_false)
        {
            Assert::IsFalse(pImpl->RemoveBGOrderTypes("S3", "S3"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_S4_NotS4_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("S4", ""));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_NotS4_S4_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("", "S4"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_S4_S4_false)
        {
            Assert::IsFalse(pImpl->RemoveBGOrderTypes("S4", "S4"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_S5_NotS5_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("S5", ""));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_NotS5_S5_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("", "S5"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_S5_S5_false)
        {
            Assert::IsFalse(pImpl->RemoveBGOrderTypes("S5", "S5"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_S6_NotS6_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("S6", ""));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_NotS6_S6_true)
        {
            Assert::IsTrue(pImpl->RemoveBGOrderTypes("", "S6"));
        }

        TEST_METHOD(RemoveBGOrderTypes_IsBG_S6_S6_false)
        {
            Assert::IsFalse(pImpl->RemoveBGOrderTypes("S6", "S6"));
        }
    };
}
