#include "tenderinvoicecancellationrecord.h"

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
TenderInvoiceCancellationRecord::TenderInvoiceCancellationRecord( IPhadexTransactionPtr phadexTransaction )
: TransactionRecordBase( phadexTransaction )
{
}

TenderInvoiceCancellationRecord::~TenderInvoiceCancellationRecord()
{
}

basar::Int16 TenderInvoiceCancellationRecord::getBranchno() const
{
    return TransactionRecordBase::getBranchno();
}

const basar::DateTime & TenderInvoiceCancellationRecord::getCreationDateTime() const
{
    return TransactionRecordBase::getCreationDateTime();
}

basar::Int16 TenderInvoiceCancellationRecord::getRecordType() const
{
    return TransactionRecordBase::getRecordType();
}

basar::Int32 TenderInvoiceCancellationRecord::getRecordNo() const
{
    return TransactionRecordBase::getRecordNo();
}


const basar::VarString TenderInvoiceCancellationRecord::getProgramName() const
{
    return getString( 3, 6 ); //size 6
}

basar::Int32 TenderInvoiceCancellationRecord::getInvoiceNo() const
{
    return getInt32( 9, 10 ); //size 10
}

basar::Int32 TenderInvoiceCancellationRecord::getInvoiceDate() const
{
    return getInt32( 19, 8 ); //size 8
}

basar::Int32 TenderInvoiceCancellationRecord::getCustomerNo() const
{
    return getInt32( 27, 7 ); //size 7
}

basar::Int32 TenderInvoiceCancellationRecord::getArticleNo() const
{
    return getInt32( 34, 7 ); //size 7
}

basar::Int32 TenderInvoiceCancellationRecord::getInvoiceQty() const
{
    return getInt32( 41, 7 ); //size 7
}

basar::Int32 TenderInvoiceCancellationRecord::getOrderNo() const
{
    return getInt32( 48, 7 ); //size 7
}

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

/*
KSC-FIL             N     2   Filiale
KSC-SA             N     3   Satzart  
KSC-DATUM  N     8    aktuelles Datum
KSC-ZEIT         N      6   aktuelle Zeit
KSC-leer         C       1   leer
KSC-DATA      N 480    Datenbereich mit Struktur je nach Satzart

Als Beispiel für KSC-DATA ist der Aufbau der Satzart 001 wie folgt:

K001-SA                N     3  : '001' Recordtype-Nr. (bedarfsbezogen, fortlaufend nummeriert)
K001-PROG          C     6  : Name des Programms, das den Satz schreibt, Z.B.'PVG570'
K001-RECHNR     N   10  : Rechnungs-Nr.
K001-RECHDAT   N    8  : Rechnungsdatum
K001-IDF               N      7 : IDF
K001-PZN              N     7 : PZN
K001-MENGE      N     7 : Menge
K001-KSCANR     N     7 : KSC-Auftragsnummer
K001-STORNO     C     1 : Stornogrund, 'J'= Storno, 'N'= Entstorno
K001-DATA           C 424 : Recordtype-spezifische Daten

*/