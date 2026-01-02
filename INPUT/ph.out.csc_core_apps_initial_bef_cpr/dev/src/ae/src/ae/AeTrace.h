#pragma once
//Klasse zum Loggen der Procenter-Telegramme

//class AeTrace
class CAeTrace
{
public:
    CAeTrace();

    int WriteTrace(const CString& urprog, const char* rufprog, const char* telegramm);
};
