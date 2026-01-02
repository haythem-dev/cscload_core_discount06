#include "stdafx.h"
#include "CppUnitTest.h"

#include <Country.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AeUnitTest
{
    TEST_CLASS(CountryTests)
    {
    private:
        CCountry _country;

    public:
        TEST_METHOD(DefaultCountry_DE_true)
        {
            Assert::IsTrue(_country.IsDE());
        }

        TEST_METHOD(InvalidCountry_DE_true)
        {
            _country.SetCountry("xxx");
            Assert::IsTrue(_country.IsDE());
        }

        TEST_METHOD(NotTrimmedCountry_AT_true)
        {
            _country.SetCountry("AT ");
            Assert::IsTrue(_country.IsAT());
        }

        TEST_METHOD(Country_AT_true)
        {
            _country.SetCountry("AT");
            Assert::IsTrue(_country.IsAT());
        }

        TEST_METHOD(Country_BA_true)
        {
            _country.SetCountry("BA");
            Assert::IsTrue(_country.IsBA());
        }

        TEST_METHOD(Country_BG_true)
        {
            _country.SetCountry("BG");
            Assert::IsTrue(_country.IsBG());
        }

        TEST_METHOD(Country_CH_true)
        {
            _country.SetCountry("CH");
            Assert::IsTrue(_country.IsCH());
        }

        TEST_METHOD(Country_DE_true)
        {
            _country.SetCountry("DE");
            Assert::IsTrue(_country.IsDE());
        }

        TEST_METHOD(Country_FR_true)
        {
            _country.SetCountry("FR");
            Assert::IsTrue(_country.IsFR());
        }

        TEST_METHOD(Country_HR_true)
        {
            _country.SetCountry("HR");
            Assert::IsTrue(_country.IsHR());
        }

        TEST_METHOD(Country_MK_true)
        {
            _country.SetCountry("MK");
            Assert::IsTrue(_country.IsMK());
        }

        TEST_METHOD(Country_PF_true)
        {
            _country.SetCountry("PF");
            Assert::IsTrue(_country.IsPF());
        }

        TEST_METHOD(Country_RS_true)
        {
            _country.SetCountry("RS");
            Assert::IsTrue(_country.IsRS());
        }
    };
}
