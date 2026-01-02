/*************************************************************************/
/*                                                                       */
/*  Quelle  : GetNextPhoneCall.h                                         */
/*  Autor   : A.Schmidt-Rehschuh                                         */
/*  erstellt: 07.01.97                                                   */
/*  Aufgabe : Darstellung Tagesanrufplan; Online Pflege; Protokoll-      */
/*            anzeige; Anruf auslösen                                    */
/*  Klassen : GetNextPhoneCall                                           */
/*  Funktion: GetNextCall() - direkter Aufruf Anrufplan                  */
/*            GetCallSelection() - Auswahl der nächsten Anrufe           */
/*  Variable: long idfNo                                                 */
/*                                                                       */
/*************************************************************************/

enum EODATE { ddmmyyyy = 1, ddmmyy, ddmm, dd, mm, yy, yyyymmdd };
#define NO_CUSTOMER -1
static void DateOfDay(char*, int);

/*** DATE-OF-DAY *********************************************************/

static void DateOfDay(char* date, int format)
{
    CTime t = CTime::GetCurrentTime();
    int rc = 0;
    char* frm;

    switch (format)
    {
    case yyyymmdd:
        frm = "%04d%02d%02d";
        rc = 1;
        break;
    case ddmmyyyy:
        frm = "%02d.%02d.%04d";
        break;
    case ddmmyy:
        frm = "%02d.%02d.%02d";
        break;
    case ddmm:
        frm = "%02d.%02d";
        break;
    case dd:
        frm = "%02d";
        break;
    case mm:
        frm = "%0s%02d";
        break;
    case yy:
        frm = "%0s%0s%02d";
        break;
    default:
        return;
    }

    if (rc)
        sprintf(date, frm, t.GetYear(), t.GetMonth(), t.GetDay());
    else
        sprintf(date, frm, t.GetDay(), t.GetMonth(), t.GetYear());

}

/*** CLASS -GET-NEXT-PHONE-CALL ******************************************/

class GetNextPhoneCall
{
private:
    long m_idfNo;
    short m_VzNr;
    bool m_bCancel;
    bool m_bNoParaCalls;

public:
    GetNextPhoneCall()
    {
        m_bCancel      = true;
        m_idfNo        = NO_CUSTOMER;
        m_bNoParaCalls = false;
        m_VzNr         = 0;
    }

    long    GetKndNum() { return m_idfNo; }
    short   GetKndVZ() { return m_VzNr; }
    bool    IsCancel() { return m_bCancel; }
    void    NoParaCalls(bool bCall = true) { m_bNoParaCalls = bCall; }

    long GetNextCall()                      // you get immediately the next free call
    {
       char date[9];
       DateOfDay(date, yyyymmdd);
       m_idfNo = GetNextCall(atol(date));
       return m_idfNo;
    }

    long IsNextCall()                       // is there an call, you get only the
    {                                       // number of the customer
       char date[9];
       DateOfDay(date, yyyymmdd);
       m_idfNo = IsNextCall(atol(date));
       return m_idfNo;
    }

    long GetCallSelection()                 // you get a list of the next possibles calls
    {
       m_idfNo = GetCallSel();
       return m_idfNo;
    }

    long GetCall()
    {
        if (AeGetApp()->IsFastOpenOrder())
            return GetNextCall();
        else
            return GetCallSelection();
    }

    long GetNextCall(long date);
    long GetCallSel();
    long IsNextCall(long date);
};
