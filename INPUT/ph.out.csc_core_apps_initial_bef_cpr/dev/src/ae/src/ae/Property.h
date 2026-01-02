#pragma once

template<class T> class PropTemp
{
private:
    T _value;

public:
    PropTemp()
    {
        _value = T();
    }

    void operator=(const T& value)
    {
        _value = value;
    }

    // Returns a COPY of the value
    T operator()()
    {
        return _value;
    }
};

typedef PropTemp<bool> BoolProp;

typedef PropTemp<int> IntProp;

typedef PropTemp<long> LongProp;

typedef PropTemp<short> ShortProp;

typedef PropTemp<double> DoubleProp;

typedef PropTemp<char> CharProp;

class CStringProp
{
private:
    CString _value;

public:
    void operator=(const CString& value)
    {
        _value = value;
    }

    // Returns a COPY of the value
    CString operator()()
    {
        return _value;
    }
};
