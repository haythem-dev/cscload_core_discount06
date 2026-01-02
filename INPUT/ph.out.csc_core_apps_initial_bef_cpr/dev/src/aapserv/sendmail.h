#ifndef __PP_SENDMAIL_H_
#define __PP_SENDMAIL_H_

/******************************************************************************/
/* d:\prj\AA\UNIX\aapserv\src\SendMail ****************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of SENDMAIL **************************************************/

#define L_SENDMAIL_BRANCHNO 6
#define L_SENDMAIL_MAILINGLIST 254
#define L_SENDMAIL_TITEL 30
#define L_SENDMAIL_EMAILADRESSE 60
#define L_SENDMAIL_MAILTEXT 1024
#define L_SENDMAIL_MAILSUBJECT 60

/* Length/Count-Define of SENDMAIL ********************************************/

#define LS_SENDMAIL_BRANCHNO 5 + 1
#define LS_SENDMAIL_MAILINGLIST 254 + 1
#define LS_SENDMAIL_TITEL 30 + 1
#define LS_SENDMAIL_EMAILADRESSE 60 + 1
#define LS_SENDMAIL_MAILTEXT 1024 + 1
#define LS_SENDMAIL_MAILSUBJECT 60 + 1

#define SENDMAILBRANCHNO 0
#define SENDMAILMAILINGLIST 1
#define SENDMAILTITEL 2
#define SENDMAILEMAILADRESSE 3
#define SENDMAILMAILTEXT 4
#define SENDMAILMAILSUBJECT 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define SENDMAIL_H
#define SENDMAIL_ANZ ( sizeof(SENDMAIL_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of SENDMAIL ******************************************************/

#define SENDMAIL_LISTE \
        CALLBACKDIVISION.BRANCHNO,\
        CALLBACKDIVISION.MAILINGLIST,\
        KDKRITIK.TITEL,\
        KUNDE.EMAILADRESSE,\
        AADUMMY.MAILTEXT,\
        AADUMMY.MAILSUBJECT
#define SENDMAIL_LISTE_390 \
        BRANCHNO,\
        MAILINGLIST,\
        TITEL,\
        EMAILADRESSE,\
        MAILTEXT,\
        MAILSUBJECT
#define SENDMAIL_PLISTE \
        "CALLBACKDIVISION.BRANCHNO,"\
        "CALLBACKDIVISION.MAILINGLIST,"\
        "KDKRITIK.TITEL,"\
        "KUNDE.EMAILADRESSE,"\
        "AADUMMY.MAILTEXT,"\
        "AADUMMY.MAILSUBJECT"
#define SENDMAIL_PELISTE \
        "BRANCHNO,"\
        "MAILINGLIST,"\
        "TITEL,"\
        "EMAILADRESSE,"\
        "MAILTEXT,"\
        "MAILSUBJECT"
#define SENDMAIL_UPDLISTE \
        "BRANCHNO=?,"\
        "MAILINGLIST=?,"\
        "TITEL=?,"\
        "EMAILADRESSE=?,"\
        "MAILTEXT=?,"\
        "MAILSUBJECT=?"
/* SqlMacros-Define of SENDMAIL ***********************************************/

#define SENDMAIL_ZEIGER(x) \
        :x->BRANCHNO,\
        :x->MAILINGLIST,\
        :x->TITEL,\
        :x->EMAILADRESSE,\
        :x->MAILTEXT,\
        :x->MAILSUBJECT
#define SENDMAIL_ZEIGERSEL(x) \
        :x->BRANCHNO,\
        :x->MAILINGLIST,\
        :x->TITEL,\
        :x->EMAILADRESSE,\
        :x->MAILTEXT,\
        :x->MAILSUBJECT
#define SENDMAIL_UPDATE(x) \
        CALLBACKDIVISION.BRANCHNO=:x->BRANCHNO,\
        CALLBACKDIVISION.MAILINGLIST=:x->MAILINGLIST,\
        KDKRITIK.TITEL=:x->TITEL,\
        KUNDE.EMAILADRESSE=:x->EMAILADRESSE,\
        AADUMMY.MAILTEXT=:x->MAILTEXT,\
        AADUMMY.MAILSUBJECT=:x->MAILSUBJECT
/* SqlMacros390-Define of SENDMAIL ********************************************/

#define SENDMAIL_ZEIGER_390 \
        :BRANCHNO,\
        :MAILINGLIST,\
        :TITEL,\
        :EMAILADRESSE,\
        :MAILTEXT,\
        :MAILSUBJECT
#define SENDMAIL_UPDATE_390 \
        BRANCHNO=:BRANCHNO,\
        MAILINGLIST=:MAILINGLIST,\
        TITEL=:TITEL,\
        EMAILADRESSE=:EMAILADRESSE,\
        MAILTEXT=:MAILTEXT,\
        MAILSUBJECT=:MAILSUBJECT
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of SENDMAIL ************************************************/

#ifndef TRANSCLASS
typedef struct N_SENDMAIL {
    short BRANCHNO;
    char MAILINGLIST[255];
    char TITEL[31];
    char EMAILADRESSE[61];
    char MAILTEXT[1025];
    char MAILSUBJECT[61];
} sendmailS;
#else /* TRANSCLASS */
typedef struct N_SENDMAIL {
    short BRANCHNO;
    char MAILINGLIST[255];
    char TITEL[31];
    char EMAILADRESSE[61];
    char MAILTEXT[1025];
    char MAILSUBJECT[61];

    bool operator == (const N_SENDMAIL& right) const {
        return (
            BRANCHNO == right.BRANCHNO &&
            !strcmp(MAILINGLIST, right.MAILINGLIST) &&
            !strcmp(TITEL, right.TITEL) &&
            !strcmp(EMAILADRESSE, right.EMAILADRESSE) &&
            !strcmp(MAILTEXT, right.MAILTEXT) &&
            !strcmp(MAILSUBJECT, right.MAILSUBJECT)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        BRANCHNO = 0;
        strcpy(MAILINGLIST, " " );
        strcpy(TITEL, " " );
        strcpy(EMAILADRESSE, " " );
        strcpy(MAILTEXT, " " );
        strcpy(MAILSUBJECT, " " );
#endif
    }
} sendmailS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of SENDMAIL ******************************************/

struct S_SENDMAIL {
    char BRANCHNO[7];
    char MAILINGLIST[254 + 1];
    char TITEL[30 + 1];
    char EMAILADRESSE[60 + 1];
    char MAILTEXT[1024 + 1];
    char MAILSUBJECT[60 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of SENDMAIL *************************/

struct O_SENDMAIL {
    char BRANCHNO[7];
    char MAILINGLIST[254];
    char TITEL[30];
    char EMAILADRESSE[60];
    char MAILTEXT[1024];
    char MAILSUBJECT[60];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of SENDMAIL ************************************/

struct C_SENDMAIL {
    short BRANCHNO;
    char MAILINGLIST[255];
    char TITEL[31];
    char EMAILADRESSE[61];
    char MAILTEXT[1025];
    char MAILSUBJECT[61];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of SENDMAIL **********************************/

struct I_SENDMAIL {
    short BRANCHNO;
    short MAILINGLIST;
    short TITEL;
    short EMAILADRESSE;
    short MAILTEXT;
    short MAILSUBJECT;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of SENDMAIL ********************************************/

#if defined (BUF_DESC)
static struct buf_desc SENDMAIL_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 60, 0 },
   { TYP_C, 1024, 0 },
   { TYP_C, 60, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc SENDMAIL_BES [] = {
   { TYP_S ,  6, 0 },
   { TYP_C, 254, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 60, 0 },
   { TYP_C, 1024, 0 },
   { TYP_C, 60, 0 },
};
#endif

/* description for datatypes of SENDMAIL **************************************/

 #define SENDMAIL_S390 \
         short BRANCHNO; \
         char MAILINGLIST[255]; \
         char TITEL[31]; \
         char EMAILADRESSE[61]; \
         char MAILTEXT[1025]; \
         char MAILSUBJECT[61]; \



/* Copy-Function Struct to single Data SENDMAIL *******************************/

 #define SENDMAIL_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
          strcpy(MAILINGLIST,_x_->MAILINGLIST);\
          strcpy(TITEL,_x_->TITEL);\
          strcpy(EMAILADRESSE,_x_->EMAILADRESSE);\
          strcpy(MAILTEXT,_x_->MAILTEXT);\
          strcpy(MAILSUBJECT,_x_->MAILSUBJECT);\

 #define SENDMAIL_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          strcpy(_x_->MAILINGLIST,MAILINGLIST);\
          strcpy(_x_->TITEL,TITEL);\
          strcpy(_x_->EMAILADRESSE,EMAILADRESSE);\
          strcpy(_x_->MAILTEXT,MAILTEXT);\
          strcpy(_x_->MAILSUBJECT,MAILSUBJECT);\



/* FunctionNumber-Define of SendMail ******************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of SendMail **************************************/


#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS

#include<vector>
using namespace std;

/* ppunixc */
#include <sockclient.h>
#include <ppstring.h>
#include <ppgeneric.h>

/* must be implemented */
void FehlerBehandlung(int rc, const char * const error_msg);

#ifndef __VIRTUAL_DADE_CLASS__
#define __VIRTUAL_DADE_CLASS__

class ppDadeVirtual {
public:
    virtual    ~ppDadeVirtual() {};
    virtual int SelList      (int FetchRel = 1, int pos = 0) = 0;
    virtual int SelListHist  (int FetchRel = 1, int pos = 0) = 0;
    virtual int SelListFuture(int FetchRel = 1, int pos = 0) = 0;
    virtual int Load         (int pos = 0                  ) = 0;
    virtual int Delete       (int pos = 0                  ) = 0;
    virtual int Save         (int pos = 0                  ) = 0;
};
#endif

class CSENDMAIL : public ppDadeVirtual {
public:
    sendmailS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<sendmailS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< sendmailS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     sendmailS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< sendmailS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<sendmailS>::iterator
                 beginList() { return lst.begin(); }
    vector<sendmailS>::iterator
                 endList  () { return lst.end  (); }

    short        GetBranchno() const { return s.BRANCHNO; }
    const char*  GetMailinglist(ppString & t) const { t = s.MAILINGLIST; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetTitel(ppString & t) const { t = s.TITEL; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetEmailadresse(ppString & t) const { t = s.EMAILADRESSE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetMailtext(ppString & t) const { t = s.MAILTEXT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetMailsubject(ppString & t) const { t = s.MAILSUBJECT; t.erasespace(ppString::END); return t.c_str(); }

    const sendmailS &
                 GetStruct() const { return s; }
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetMailinglist(const ppString & t) { ppGStrCopy(s.MAILINGLIST, t.c_str(), L_SENDMAIL_MAILINGLIST); }
    void         SetTitel(const ppString & t) { ppGStrCopy(s.TITEL, t.c_str(), L_SENDMAIL_TITEL); }
    void         SetEmailadresse(const ppString & t) { ppGStrCopy(s.EMAILADRESSE, t.c_str(), L_SENDMAIL_EMAILADRESSE); }
    void         SetMailtext(const ppString & t) { ppGStrCopy(s.MAILTEXT, t.c_str(), L_SENDMAIL_MAILTEXT); }
    void         SetMailsubject(const ppString & t) { ppGStrCopy(s.MAILSUBJECT, t.c_str(), L_SENDMAIL_MAILSUBJECT); }

    void         SetStruct(const sendmailS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CSENDMAIL() {
        ::buf_default((void *)&s, SENDMAIL_BES, SENDMAIL_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CSENDMAIL() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, SENDMAIL_BES, SENDMAIL_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, SENDMAIL_BES, (int)SENDMAIL_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, SENDMAIL_BES, (int)SENDMAIL_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_SENDMAIL & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.MAILINGLIST);
        ppGStripLast(d.TITEL);
        ppGStripLast(d.EMAILADRESSE);
        ppGStripLast(d.MAILTEXT);
        ppGStripLast(d.MAILSUBJECT);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, SENDMAIL_BES, (int)SENDMAIL_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};
#endif    // TRANSCLASS
/* CreateSqlStatement of SENDMAIL *********************************************/

 #define SENDMAIL_CREATE(x) EXEC SQL create table x (\
         BRANCHNO smallint default 0 not null,\
         MAILINGLIST varchar(254,0) default " " not null,\
         TITEL char(30) default " " not null,\
         EMAILADRESSE varchar(60,0) default " " not null,\
         MAILTEXT varchar(1024,0) default " " not null,\
         MAILSUBJECT varchar(60,0) default " " not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of SENDMAIL *******************************************/

 #define SENDMAIL_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_callbackdivision_1 on _X_(\
              BranchNo,\
              CallbackDivisionNo );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of SENDMAIL *******************************************/

 #define SENDMAIL_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_callbackdivision_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
