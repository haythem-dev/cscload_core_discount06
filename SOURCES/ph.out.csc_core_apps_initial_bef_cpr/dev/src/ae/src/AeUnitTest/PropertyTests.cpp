#include "stdafx.h"
#include "CppUnitTest.h"

#include <Property.h>
#include <limits.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AeUnitTest
{
    TEST_CLASS(PropertyTests)
    {
    public:
        TEST_METHOD_INITIALIZE(Initialize)
        {
        }

        TEST_METHOD_CLEANUP(Cleanup)
        {
        }

        ///////////////////////////////////////////////////////////////////////////////////
        // BoolProp
        ///////////////////////////////////////////////////////////////////////////////////

        TEST_METHOD(BoolProp_Initialization_success)
        {
            BoolProp prop;
            Assert::IsFalse(prop());
        }

        TEST_METHOD(BoolProp_SetFalse_false)
        {
            BoolProp prop;
            prop = false;
            Assert::IsFalse(prop());
        }

        TEST_METHOD(BoolProp_SetTrue_true)
        {
            BoolProp prop;
            prop = true;
            Assert::IsTrue(prop());
        }

        ///////////////////////////////////////////////////////////////////////////////////
        // IntProp
        ///////////////////////////////////////////////////////////////////////////////////

        TEST_METHOD(IntProp_Initialization_success)
        {
            IntProp prop;
            Assert::AreEqual(0, prop());
        }

        TEST_METHOD(IntProp_SetIntMin)
        {
            IntProp prop;
            prop = INT_MIN;
            Assert::AreEqual(INT_MIN, prop());
        }

        TEST_METHOD(IntProp_SetIntMax)
        {
            IntProp prop;
            prop = INT_MAX;
            Assert::AreEqual(INT_MAX, prop());
        }

        ///////////////////////////////////////////////////////////////////////////////////
        // ShortProp
        ///////////////////////////////////////////////////////////////////////////////////

        TEST_METHOD(ShortProp_Initialization_success)
        {
            ShortProp prop;
            Assert::AreEqual((short)0, prop());
        }

        TEST_METHOD(ShortProp_SetIntMin)
        {
            ShortProp prop;
            prop = SHRT_MIN;
            Assert::AreEqual((short)SHRT_MIN, prop());
        }

        TEST_METHOD(ShortProp_SetIntMax)
        {
            ShortProp prop;
            prop = SHRT_MAX;
            Assert::AreEqual((short)SHRT_MAX, prop());
        }

        ///////////////////////////////////////////////////////////////////////////////////
        // LongProp
        ///////////////////////////////////////////////////////////////////////////////////

        TEST_METHOD(LongProp_Initialization_success)
        {
            LongProp prop;
            Assert::AreEqual(0L, prop());
        }

        TEST_METHOD(LongProp_SetIntMin)
        {
            LongProp prop;
            prop = LONG_MIN;
            Assert::AreEqual(LONG_MIN, prop());
        }

        TEST_METHOD(LongProp_SetIntMax)
        {
            LongProp prop;
            prop = LONG_MAX;
            Assert::AreEqual(LONG_MAX, prop());
        }

        ///////////////////////////////////////////////////////////////////////////////////
        // CStringProp
        ///////////////////////////////////////////////////////////////////////////////////

        TEST_METHOD(CStringProp_Initialization_success)
        {
            CStringProp prop;
            Assert::AreEqual("", prop());
        }

        TEST_METHOD(CStringProp_SetValue)
        {
            CString str = "Hallo Welt";

            CStringProp prop;
            prop = str;
            Assert::AreEqual(str.GetString(), prop());
        }

        TEST_METHOD(CStringProp_ChangingGetValue_PropertyValueIsNotChanged)
        {
            CString str = "Hallo Welt";

            CStringProp prop;
            prop = str;

            prop().Append("!!!"); // only copy of value is changed!
            str.Append("!!!");

            Assert::AreNotEqual(str.GetString(), prop());
        }

        TEST_METHOD(CStringProp_SetValue_DoStringOperation_ValuesHasChanged)
        {
            CString str = "Hallo Welt        ";

            CStringProp prop;
            prop = str;

            CString strProp = prop().Trim();
            str.Trim();

            Assert::AreEqual(str.GetString(), strProp);
        }
    };
}
