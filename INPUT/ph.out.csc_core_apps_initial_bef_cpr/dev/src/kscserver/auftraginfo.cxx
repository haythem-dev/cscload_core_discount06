#undef TRANSCLASS

#include <stdio.h>
#include "auftraginfo.h"

#define UNUSED(x) (void)(x)

EXEC SQL include sqlca;
EXEC SQL include sqltypes;

/* ProLink::Insert ************************************************************/

int kscProlink_Insert(prolinkS *a, char* error_msg)
{
    int rc = 0;
    exec sql begin declare section;
    prolinkS *d;
    exec sql end declare section;

    UNUSED(error_msg);
    d = a;

    exec sql insert into akdauftragprolink (datum,
                     kdauftragnr,
                     InvoiceNumberPro,
                     InvoiceNumber,
                     DateProforma,
                     kdauftragnrpro)
        values (:d->DATUM,
                     :d->KDAUFTRAGNR,
                     :d->INVOICENUMBERPRO,
                     :d->INVOICENUMBER,
                     :d->DATEPROFORMA,
                     :d->KDAUFTRAGNRPRO);
    return rc;
}

/* ProLinkAct::Insert *********************************************************/

int kscProlinkact_Insert(prolinkactS *a, char* error_msg)
{
    int rc = 0;
    exec sql begin declare section;
    prolinkactS *d;
    exec sql end declare section;

    UNUSED(error_msg);
    d = a;

    exec sql insert into kdauftragprolink (kdauftragnr,
                     InvoiceNumberPro,
                     InvoiceNumber,
                     DateProforma,
                     kdauftragnrpro)
        values (:d->KDAUFTRAGNR,
                     :d->INVOICENUMBERPRO,
                     :d->INVOICENUMBER,
                     :d->DATEPROFORMA,
                     :d->KDAUFTRAGNRPRO);
    return rc;
}
