#include "pxdkrakresult.hpp"
#include "pxtcarecord.h"
#include <stdlib.h>

/*----------------------------------------------------------------------------*/
/*  Constructor for dkraksesult object                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/
pxDkrakResult :: pxDkrakResult
(
    char* ResultBuffer
)
{
    ResultBuffer_ = ResultBuffer;
}

/*----------------------------------------------------------------------------*/
/*  Destructor  for dkraksesult  object                                       */
/*----------------------------------------------------------------------------*/
pxDkrakResult :: ~pxDkrakResult()
{
}

/*----------------------------------------------------------------------------*/
/*  BranchNo                                                                  */
/*----------------------------------------------------------------------------*/
short
pxDkrakResult :: BranchNo
(
)
{
    char   temp[20];
    struct VI52_resultpage* VK52 = (VI52_resultpage*)ResultBuffer_;
    sprintf((char*)temp,"%2.2s", VK52->line.BranchNo);
    return static_cast<short>(atoi(temp));
}

/*----------------------------------------------------------------------------*/
/*  CustomerNo                                                                */
/*----------------------------------------------------------------------------*/
long
pxDkrakResult :: CustomerNo
(
)
{
    char temp[20];
    struct VI52_resultpage* VK52 = (VI52_resultpage*)ResultBuffer_;
    sprintf((char*)temp,"%7.7s", VK52->line.IDFNr);
    return atol(temp);
}

/*----------------------------------------------------------------------------*/
/*  InvoiceNumber                                                             */
/*----------------------------------------------------------------------------*/
nString
pxDkrakResult :: InvoiceNumber
(
)
{
    nString InvoiceNumber;
    char temp[20];
    struct VI52_resultpage* VK52 = (VI52_resultpage*)ResultBuffer_;
    sprintf((char*)temp,"%10.10s", VK52->line.InvoiceNo);
    InvoiceNumber = temp;
    InvoiceNumber.Trim(15);
    return InvoiceNumber;
}

/*----------------------------------------------------------------------------*/
/*  VoucherTyp                                                                */
/*----------------------------------------------------------------------------*/
nString
pxDkrakResult :: VoucherType
(
)
{
    char temp[20];
    struct VI52_resultpage* VK52 = (VI52_resultpage*)ResultBuffer_;
    sprintf((char*)temp,"%2.2s", VK52->line.DocumentType);
    return nString(temp);
}

/*----------------------------------------------------------------------------*/
/*  DocumentNo                                                                */
/*----------------------------------------------------------------------------*/
nString
pxDkrakResult :: DocumentNo
(
)
{
    nString DocumentNo;
    char  temp[20];
    struct VI52_resultpage* VK52 = (VI52_resultpage*)ResultBuffer_;
    sprintf((char*)temp,"%10.10s", VK52->line.DocumentNo);
    DocumentNo = temp;
    DocumentNo.Trim(15);
    return DocumentNo;
}
/*----------------------------------------------------------------------------*/
/*  LfdNr                                                                     */
/*----------------------------------------------------------------------------*/
long
pxDkrakResult :: LfdNr
(
)
{
    nString LfdNr;
    char  temp[20];
    struct VI52_resultpage* VK52 = (VI52_resultpage*)ResultBuffer_;
    sprintf((char*)temp,"%3.3s", VK52->line.LFDNr);
    LfdNr = temp;
    LfdNr.Trim(3);
    return atol( (char*)LfdNr );
}
/*----------------------------------------------------------------------------*/
/*  InvoiceAmountPaid                                                         */
/*----------------------------------------------------------------------------*/
double
pxDkrakResult :: InvoiceAmountPaid
(
)
{
    double  InvoiceAmountPaid;
    char temp[20];
    nString AmountPaid;

    struct VI52_resultpage* VK52 = (VI52_resultpage*)ResultBuffer_;
    sprintf((char*)temp,"%9.9s", VK52->line.InvoiceAmountPaid);
    AmountPaid  = temp;
    AmountPaid.Trim(9);
    InvoiceAmountPaid = atof((char*)AmountPaid);
    InvoiceAmountPaid = InvoiceAmountPaid/100;
    return InvoiceAmountPaid;
}

/*----------------------------------------------------------------------------*/
/*  DueDate                                                                   */
/*----------------------------------------------------------------------------*/
long
pxDkrakResult :: DueDate
(
)
{
    long  DueDate   = 20000000;
    char  temp[20];
    long  lDate;
    nString hDate;
    struct VI52_resultpage* VK52 = (VI52_resultpage*)ResultBuffer_;
    sprintf((char*)temp,"%6.6s", VK52->line.DueDate);
    hDate = temp;
    hDate.Trim(6);
    lDate = atol((char*)hDate);
    if ( lDate == 0 )
        return DueDate = 0;
    DueDate += lDate;
    return DueDate;
}

/*----------------------------------------------------------------------------*/
/*  LastPaymentDate                                                           */
/*----------------------------------------------------------------------------*/
long
pxDkrakResult :: LastPaymentDate
(
)
{
    long  LastDate   = 20000000;
    char  temp[20];
    long  lDate;
    nString hDate;
    struct VI52_resultpage* VK52 = (VI52_resultpage*)ResultBuffer_;
    sprintf((char*)temp,"%6.6s", VK52->line.LastPaymentDate);
    hDate = temp;
    hDate.Trim(6);
    lDate = atol((char*)hDate);
    if ( lDate == 0 )
        return  LastDate = 0;
    LastDate += lDate;
    return LastDate;
}

/*----------------------------------------------------------------------------*/
/*  NormalBalance                                                             */
/*----------------------------------------------------------------------------*/
double
pxDkrakResult :: NormalBalance
(
)
{
    double   NormalBalance;
    char  temp[20];
    nString Balance;

    struct VI52_resultpage* VK52 = (VI52_resultpage*)ResultBuffer_;
    sprintf((char*)temp,"%9.9s", VK52->line.NOUM);
    Balance  = temp;
    Balance.Trim(9);
    NormalBalance = atof((char*)Balance);
    NormalBalance = NormalBalance/100;
    return NormalBalance;
}

long
pxDkrakResult::LockCount
(
)
{
    char temp[20];

    struct VI52_resultpage* VK52 = (VI52_resultpage*)ResultBuffer_;
    sprintf((char*)temp,"%6.6s", VK52->line.LockCount);
    return atol(temp);
}
