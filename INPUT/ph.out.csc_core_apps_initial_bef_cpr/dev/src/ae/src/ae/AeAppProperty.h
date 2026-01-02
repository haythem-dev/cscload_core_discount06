#pragma once

#include "Property.h"

class CAeApp;

namespace AeApp
{
    // BoolProp with private setter and friend CAeApp
    class BoolProp : public ::BoolProp
    {
    private:
        friend class ::CAeApp;
        void operator=(const bool& value) { ::BoolProp::operator=(value); }
    };

    // LongProp with private setter and friend CAeApp
    class LongProp : public ::LongProp
    {
    private:
        friend class ::CAeApp;
        void operator=(const long& value) { ::LongProp::operator=(value); }
    };

    // ShortProp with private setter and friend CAeApp
    class ShortProp : public ::ShortProp
    {
    private:
        friend class ::CAeApp;
        void operator=(const short& value) { ::ShortProp::operator=(value); }
    };

    // CharProp with private setter and friend CAeApp
    class CharProp : public ::CharProp
    {
    private:
        friend class ::CAeApp;
        void operator=(const char& value) { ::CharProp::operator=(value); }
    };

    // CStringProp with private setter and friend CAeApp
    class CStringProp : public ::CStringProp
    {
    private:
        friend class ::CAeApp;
        void operator=(const CString& value) { ::CStringProp::operator=(value); }
    };

    // CStringProp with private setter and friend CAeApp
    class ppStringProp : public ::PropTemp<ppString>
    {
    private:
        friend class ::CAeApp;
        void operator=(const ppString& value) { ::PropTemp<ppString>::operator=(value); }
    };
}
