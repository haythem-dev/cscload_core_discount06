#pragma once


#ifndef SQL_OK
#define SQL_OK           0L
#define SQL_NOK         -1L
#define SQL_NO_MORE_DATA 100L
#endif

long BeginTransfer(int importno, long pznfrom, long pznto);
long BeginAgpCleanup();
