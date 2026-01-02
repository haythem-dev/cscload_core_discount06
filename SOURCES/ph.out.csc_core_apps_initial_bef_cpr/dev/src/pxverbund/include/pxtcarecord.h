#ifndef pxtcarecord_DOTH
         #define pxtcarecord_DOTH



/*****************************************************************************/
/*  VSE CVI522 TCA Interface record                                          */
/*****************************************************************************/

typedef struct cvi522_line
{
    char        BranchNo[2];                /* BranchNo(Fil) */
    char        RecordType[2];              /* RecordTyp(Sa) */
    char        InvoiceNo[10];              /* InvoiceNo(RNR) */
    char        IDFNr[7];                   /* IDFNr(IDF) */
    char        DocumentType[2];            /* Documenttype(BTYP)*/
    char        OverFlowNo;                 /* OverFlowNo(UELNR)*/
    char        DocumentNo[10];             /* DocumentNo(BELEGNR)*/
    char        LFDNr[3];                   /* LFDNr*/
    char        MOUM[9];                    /* Umsatz 0 %*/
    char        ERUM[9];                    /* Ermässigter Umsatz 0 %*/
    char        M3UM[9];                    /* 3% Umsatz*/
    char        NOUM[9];                    /* Normaler Umsatz */
    char        Program[6];                 /* Programm */
    char        FehlLink[4];                /* Fehllink */
    char        ErrorText[20];              /* Fehlertext */
    char        SalesText[80];              /* Zahlungstext */
    char        DateFrom[6];                /* Date From */
    char        DateTo[6];                  /* Date to*/
    char        Chain;                      /* Kette*/
    char        TourId[6];                  /* TourId*/
    char        OriginOrderNo[7];           /* Original Auftragsnummer*/
    char        SplittOrderNo[7];           /* Splitt   Auftragsnummer*/
    char        Priority;                   /* Prio Kennzeichen*/
    char        Available;                  /* Verfuegbar*/
    char        LockSwitch;                 /* LockSwitch O/G/K*/
    char        LockCount[6];               /* LockCount already locked records*/
    char        NVH;                        /* J = entry = av, N = entry nav*/
    char        InvoiceAmountPaid[9];       /* Bezahlter Bertrag*/
    char        DueDate[6];                 /* Fälligkeitsdatum*/
    char        LastPaymentDate[6];         /* Datum letzte Zahlung*/
    char        Filler[03];                 /* Filler*/
} tCVI522_RECORD;

/*****************************************************************************/
/*  VSE TCA CallStmt                                                         */
/*****************************************************************************/

typedef struct  TCA_callstmt
{
    char        statement[17];              /* callstatement*/
    char        quoteleft;                  /* '*/
    char        ModuleName[6];              /* Cobl Module name*/
    char        sepright[4];                /* ', '*/
} tTCACALLSTMT;


/*****************************************************************************/
/*  VSE TCA Header record                                                    */
/*****************************************************************************/

typedef struct  TCA_header
{
    char        BufLen[4];                  /* Buffer length */
} tTCAHEADER;

/*****************************************************************************/
/*  VSE UNIX TVA Total page                                                  */
/*****************************************************************************/

typedef struct VI52_page
{
    struct TCA_callstmt   callstmt;
    struct TCA_header     header;
    struct cvi522_line    line;
    char   restend[3];
} tVI52, * tVI52P;

/*****************************************************************************/
/*  VSE UNIX TVA Total page for resultbuffer                                 */
/*****************************************************************************/

typedef struct VI52_resultpage
{
    struct TCA_header     header;
    struct cvi522_line    line;
} tVI52RESULT, * tVI52RESULTP;
#endif
