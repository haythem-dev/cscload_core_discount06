#pragma once

class CLetterMan
{
public:
    CLetterMan();
    ~CLetterMan();

    char* Next();
    char* Current();

    void Reset();
    void SetSeed(char seed);

    static bool InRange(WORD key, int listItemCount);
    static bool InAZRange(WORD key);

private:
    char m_kb[2];
};
