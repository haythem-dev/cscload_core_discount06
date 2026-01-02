#ifndef __PP_CSCORDERIMPORTCSVFILE_H_
#define __PP_CSCORDERIMPORTCSVFILE_H_

/******************************************************************************/
/* c:\tmp\CSCOrderImportCSVFile ***********************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of CSCORDERIMPORTCSVFILE *************************************/

#define L_CSCORDERIMPORTCSVFILE_CSVFORMATNAME 200
#define L_CSCORDERIMPORTCSVFILE_CSCORDERIMPORTFORMATID 11
#define L_CSCORDERIMPORTCSVFILE_FEHLER 11
#define L_CSCORDERIMPORTCSVFILE_DATEINAME 200
#define L_CSCORDERIMPORTCSVFILE_CSVLOGFILE 255
#define L_CSCORDERIMPORTCSVFILE_DATEINAMEORG 200
#define L_CSCORDERIMPORTCSVFILE_CSVFEHLERTEXT 200
#define L_CSCORDERIMPORTCSVFILE_CSVREPORTFILE 200
#define L_CSCORDERIMPORTCSVFILE_LANGUAGE 2

/* Length/Count-Define of CSCORDERIMPORTCSVFILE *******************************/

#define LS_CSCORDERIMPORTCSVFILE_CSVFORMATNAME 200 + 1
#define LS_CSCORDERIMPORTCSVFILE_CSCORDERIMPORTFORMATID 10 + 1
#define LS_CSCORDERIMPORTCSVFILE_FEHLER 10 + 1
#define LS_CSCORDERIMPORTCSVFILE_DATEINAME 200 + 1
#define LS_CSCORDERIMPORTCSVFILE_CSVLOGFILE 255 + 1
#define LS_CSCORDERIMPORTCSVFILE_DATEINAMEORG 200 + 1
#define LS_CSCORDERIMPORTCSVFILE_CSVFEHLERTEXT 200 + 1
#define LS_CSCORDERIMPORTCSVFILE_CSVREPORTFILE 200 + 1
#define LS_CSCORDERIMPORTCSVFILE_LANGUAGE 2 + 1

#define CSCORDERIMPORTCSVFILECSVFORMATNAME 0
#define CSCORDERIMPORTCSVFILECSCORDERIMPORTFORMATID 1
#define CSCORDERIMPORTCSVFILEFEHLER 2
#define CSCORDERIMPORTCSVFILEDATEINAME 3
#define CSCORDERIMPORTCSVFILECSVLOGFILE 4
#define CSCORDERIMPORTCSVFILEDATEINAMEORG 5
#define CSCORDERIMPORTCSVFILECSVFEHLERTEXT 6
#define CSCORDERIMPORTCSVFILECSVREPORTFILE 7
#define CSCORDERIMPORTCSVFILELANGUAGE 8

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CSCORDERIMPORTCSVFILE_H
#define CSCORDERIMPORTCSVFILE_ANZ ( sizeof(CSCORDERIMPORTCSVFILE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CSCORDERIMPORTCSVFILE *****************************************/

#define CSCORDERIMPORTCSVFILE_LISTE \
        CSCORDERIMPORTCSVFORMATS.CSVFORMATNAME,\
        CSCORDERIMPORTCSVFORMATS.CSCORDERIMPORTFORMATID,\
        AADUMMY.FEHLER,\
        AADUMMY.DATEINAME,\
        AADUMMY.CSVLOGFILE,\
        AADUMMY.DATEINAMEORG,\
        AADUMMY.CSVFEHLERTEXT,\
        AADUMMY.CSVREPORTFILE,\
        AADUMMY.LANGUAGE
#define CSCORDERIMPORTCSVFILE_LISTE_390 \
        CSVFORMATNAME,\
        CSCORDERIMPORTFORMATID,\
        FEHLER,\
        DATEINAME,\
        CSVLOGFILE,\
        DATEINAMEORG,\
        CSVFEHLERTEXT,\
        CSVREPORTFILE,\
        LANGUAGE
#define CSCORDERIMPORTCSVFILE_PLISTE \
        "CSCORDERIMPORTCSVFORMATS.CSVFORMATNAME,"\
        "CSCORDERIMPORTCSVFORMATS.CSCORDERIMPORTFORMATID,"\
        "AADUMMY.FEHLER,"\
        "AADUMMY.DATEINAME,"\
        "AADUMMY.CSVLOGFILE,"\
        "AADUMMY.DATEINAMEORG,"\
        "AADUMMY.CSVFEHLERTEXT,"\
        "AADUMMY.CSVREPORTFILE,"\
        "AADUMMY.LANGUAGE"
#define CSCORDERIMPORTCSVFILE_PELISTE \
        "CSVFORMATNAME,"\
        "CSCORDERIMPORTFORMATID,"\
        "FEHLER,"\
        "DATEINAME,"\
        "CSVLOGFILE,"\
        "DATEINAMEORG,"\
        "CSVFEHLERTEXT,"\
        "CSVREPORTFILE,"\
        "LANGUAGE"
#define CSCORDERIMPORTCSVFILE_UPDLISTE \
        "CSVFORMATNAME=?,"\
        "CSCORDERIMPORTFORMATID=?,"\
        "FEHLER=?,"\
        "DATEINAME=?,"\
        "CSVLOGFILE=?,"\
        "DATEINAMEORG=?,"\
        "CSVFEHLERTEXT=?,"\
        "CSVREPORTFILE=?,"\
        "LANGUAGE=?"
/* SqlMacros-Define of CSCORDERIMPORTCSVFILE **********************************/

#define CSCORDERIMPORTCSVFILE_ZEIGER(x) \
        :x->CSVFORMATNAME,\
        :x->CSCORDERIMPORTFORMATID,\
        :x->FEHLER,\
        :x->DATEINAME,\
        :x->CSVLOGFILE,\
        :x->DATEINAMEORG,\
        :x->CSVFEHLERTEXT,\
        :x->CSVREPORTFILE,\
        :x->LANGUAGE
#define CSCORDERIMPORTCSVFILE_ZEIGERSEL(x) \
        :x->CSVFORMATNAME,\
        :x->CSCORDERIMPORTFORMATID,\
        :x->FEHLER,\
        :x->DATEINAME,\
        :x->CSVLOGFILE,\
        :x->DATEINAMEORG,\
        :x->CSVFEHLERTEXT,\
        :x->CSVREPORTFILE,\
        :x->LANGUAGE
#define CSCORDERIMPORTCSVFILE_UPDATE(x) \
        CSCORDERIMPORTCSVFORMATS.CSVFORMATNAME=:x->CSVFORMATNAME,\
        AADUMMY.FEHLER=:x->FEHLER,\
        AADUMMY.DATEINAME=:x->DATEINAME,\
        AADUMMY.CSVLOGFILE=:x->CSVLOGFILE,\
        AADUMMY.DATEINAMEORG=:x->DATEINAMEORG,\
        AADUMMY.CSVFEHLERTEXT=:x->CSVFEHLERTEXT,\
        AADUMMY.CSVREPORTFILE=:x->CSVREPORTFILE,\
        AADUMMY.LANGUAGE=:x->LANGUAGE
/* SqlMacros390-Define of CSCORDERIMPORTCSVFILE *******************************/

#define CSCORDERIMPORTCSVFILE_ZEIGER_390 \
        :CSVFORMATNAME,\
        :CSCORDERIMPORTFORMATID,\
        :FEHLER,\
        :DATEINAME,\
        :CSVLOGFILE,\
        :DATEINAMEORG,\
        :CSVFEHLERTEXT,\
        :CSVREPORTFILE,\
        :LANGUAGE
#define CSCORDERIMPORTCSVFILE_UPDATE_390 \
        CSVFORMATNAME=:CSVFORMATNAME,\
        CSCORDERIMPORTFORMATID=:CSCORDERIMPORTFORMATID,\
        FEHLER=:FEHLER,\
        DATEINAME=:DATEINAME,\
        CSVLOGFILE=:CSVLOGFILE,\
        DATEINAMEORG=:DATEINAMEORG,\
        CSVFEHLERTEXT=:CSVFEHLERTEXT,\
        CSVREPORTFILE=:CSVREPORTFILE,\
        LANGUAGE=:LANGUAGE
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CSCORDERIMPORTCSVFILE ***********************************/

#ifndef TRANSCLASS
typedef struct N_CSCORDERIMPORTCSVFILE {
    char CSVFORMATNAME[201];
    long CSCORDERIMPORTFORMATID;
    long FEHLER;
    char DATEINAME[201];
    char CSVLOGFILE[256];
    char DATEINAMEORG[201];
    char CSVFEHLERTEXT[201];
    char CSVREPORTFILE[201];
    char LANGUAGE[3];
} cscorderimportcsvfileS;
#else /* TRANSCLASS */
typedef struct N_CSCORDERIMPORTCSVFILE {
    char CSVFORMATNAME[201];
    long CSCORDERIMPORTFORMATID;
    long FEHLER;
    char DATEINAME[201];
    char CSVLOGFILE[256];
    char DATEINAMEORG[201];
    char CSVFEHLERTEXT[201];
    char CSVREPORTFILE[201];
    char LANGUAGE[3];

    bool operator == (const N_CSCORDERIMPORTCSVFILE& right) const {
        return (
            !strcmp(CSVFORMATNAME, right.CSVFORMATNAME) &&
            CSCORDERIMPORTFORMATID == right.CSCORDERIMPORTFORMATID &&
            FEHLER == right.FEHLER &&
            !strcmp(DATEINAME, right.DATEINAME) &&
            !strcmp(CSVLOGFILE, right.CSVLOGFILE) &&
            !strcmp(DATEINAMEORG, right.DATEINAMEORG) &&
            !strcmp(CSVFEHLERTEXT, right.CSVFEHLERTEXT) &&
            !strcmp(CSVREPORTFILE, right.CSVREPORTFILE) &&
            !strcmp(LANGUAGE, right.LANGUAGE)
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(CSVFORMATNAME, " " );
        CSCORDERIMPORTFORMATID = 0;
        FEHLER = 0;
        strcpy(DATEINAME, " " );
        strcpy(CSVLOGFILE, " " );
        strcpy(DATEINAMEORG, " " );
        strcpy(CSVFEHLERTEXT, " " );
        strcpy(CSVREPORTFILE, " ");
        strcpy(LANGUAGE, " ");
#endif
    }
} cscorderimportcsvfileS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CSCORDERIMPORTCSVFILE *****************************/

struct S_CSCORDERIMPORTCSVFILE {
    char CSVFORMATNAME[200 + 1];
    char CSCORDERIMPORTFORMATID[11];
    char FEHLER[11];
    char DATEINAME[200 + 1];
    char CSVLOGFILE[255 + 1];
    char DATEINAMEORG[200 + 1];
    char CSVFEHLERTEXT[200 + 1];
    char CSVREPORTFILE[200 + 1];
    char LANGUAGE[2 + 1];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CSCORDERIMPORTCSVFILE ************/

struct O_CSCORDERIMPORTCSVFILE {
    char CSVFORMATNAME[200];
    char CSCORDERIMPORTFORMATID[11];
    char FEHLER[11];
    char DATEINAME[200];
    char CSVLOGFILE[255];
    char DATEINAMEORG[200];
    char CSVFEHLERTEXT[200];
    char CSVREPORTFILE[200];
    char LANGUAGE[2];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CSCORDERIMPORTCSVFILE ***********************/

struct C_CSCORDERIMPORTCSVFILE {
    char CSVFORMATNAME[201];
    long CSCORDERIMPORTFORMATID;
    long FEHLER;
    char DATEINAME[201];
    char CSVLOGFILE[256];
    char DATEINAMEORG[201];
    char CSVFEHLERTEXT[201];
    char CSVREPORTFILE[201];
    char LANGUAGE[3];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CSCORDERIMPORTCSVFILE *********************/

struct I_CSCORDERIMPORTCSVFILE {
    short CSVFORMATNAME;
    short CSCORDERIMPORTFORMATID;
    short FEHLER;
    short DATEINAME;
    short CSVLOGFILE;
    short DATEINAMEORG;
    short CSVFEHLERTEXT;
    short CSVREPORTFILE;
    short LANGUAGE;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CSCORDERIMPORTCSVFILE *******************************/

#if defined (BUF_DESC)
static struct buf_desc CSCORDERIMPORTCSVFILE_BES [] = {
   { TYP_C, 200, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 200, 0 },
   { TYP_C, 255, 0 },
   { TYP_C, 200, 0 },
   { TYP_C, 200, 0 },
   { TYP_C, 200, 0 },
   { TYP_C, 2, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CSCORDERIMPORTCSVFILE_BES [] = {
   { TYP_C, 200, 0 },
   { TYP_L ,  11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 200, 0 },
   { TYP_C, 255, 0 },
   { TYP_C, 200, 0 },
   { TYP_C, 200, 0 },
   { TYP_C, 200, 0 },
   { TYP_C, 2, 0 },
};
#endif

/* description for datatypes of CSCORDERIMPORTCSVFILE *************************/

 #define CSCORDERIMPORTCSVFILE_S390 \
         char CSVFORMATNAME[201]; \
         long CSCORDERIMPORTFORMATID; \
         long FEHLER; \
         char DATEINAME[201]; \
         char CSVLOGFILE[256]; \
         char DATEINAMEORG[201]; \
         char CSVFEHLERTEXT[201]; \
         char CSVREPORTFILE[201]; \
         char LANGUAGE[3]; \



/* Copy-Function Struct to single Data CSCORDERIMPORTCSVFILE ******************/

 #define CSCORDERIMPORTCSVFILE_S390_COPY_TO_SINGLE(_x_) \
          strcpy(CSVFORMATNAME,_x_->CSVFORMATNAME);\
         CSCORDERIMPORTFORMATID=_x_->CSCORDERIMPORTFORMATID;\
         FEHLER=_x_->FEHLER;\
          strcpy(DATEINAME,_x_->DATEINAME);\
          strcpy(CSVLOGFILE,_x_->CSVLOGFILE);\
          strcpy(DATEINAMEORG,_x_->DATEINAMEORG);\
          strcpy(CSVFEHLERTEXT,_x_->CSVFEHLERTEXT);\
          strcpy(CSVREPORTFILE,_x_->CSVREPORTFILE);\
          strcpy(LANGUAGE,_x_->LANGUAGE);\

 #define CSCORDERIMPORTCSVFILE_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->CSVFORMATNAME,CSVFORMATNAME);\
          _x_->CSCORDERIMPORTFORMATID=CSCORDERIMPORTFORMATID;\
          _x_->FEHLER=FEHLER;\
          strcpy(_x_->DATEINAME,DATEINAME);\
          strcpy(_x_->CSVLOGFILE,CSVLOGFILE);\
          strcpy(_x_->DATEINAMEORG,DATEINAMEORG);\
          strcpy(_x_->CSVFEHLERTEXT,CSVFEHLERTEXT);\
          strcpy(_x_->CSVREPORTFILE,CSVREPORTFILE);\
          strcpy(_x_->LANGUAGE,LANGUAGE);\



/* FunctionNumber-Define of CSCOrderImportCSVFile *****************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CSCOrderImportCSVFile *************************/


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

class CCSCORDERIMPORTCSVFILE : public ppDadeVirtual {
public:
    cscorderimportcsvfileS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cscorderimportcsvfileS> lst; // class list

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
                     vector< cscorderimportcsvfileS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cscorderimportcsvfileS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cscorderimportcsvfileS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cscorderimportcsvfileS>::iterator
                 beginList() { return lst.begin(); }
    vector<cscorderimportcsvfileS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetCsvformatname(ppString & t) const { t = s.CSVFORMATNAME; t.erasespace(ppString::END); return t.c_str(); }
    long         GetCscorderimportformatid() const { return s.CSCORDERIMPORTFORMATID; }
    long         GetFehler() const { return s.FEHLER; }
    const char*  GetDateiname(ppString & t) const { t = s.DATEINAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetCsvlogfile(ppString & t) const { t = s.CSVLOGFILE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetDateinameorg(ppString & t) const { t = s.DATEINAMEORG; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetCsvfehlertext(ppString & t) const { t = s.CSVFEHLERTEXT; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetCsvreportfile(ppString & t) const { t = s.CSVREPORTFILE; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetLanguage(ppString& t) const { t = s.LANGUAGE; t.erasespace(ppString::END); return t.c_str(); }

    const cscorderimportcsvfileS &
                 GetStruct() const { return s; }
    void         SetCsvformatname(const ppString & t) { ppGStrCopy(s.CSVFORMATNAME, t.c_str(), L_CSCORDERIMPORTCSVFILE_CSVFORMATNAME); }
    void         SetCscorderimportformatid(long t) { s.CSCORDERIMPORTFORMATID = t; }
    void         SetFehler(long t) { s.FEHLER = t; }
    void         SetDateiname(const ppString & t) { ppGStrCopy(s.DATEINAME, t.c_str(), L_CSCORDERIMPORTCSVFILE_DATEINAME); }
    void         SetCsvlogfile(const ppString & t) { ppGStrCopy(s.CSVLOGFILE, t.c_str(), L_CSCORDERIMPORTCSVFILE_CSVLOGFILE); }
    void         SetDateinameorg(const ppString & t) { ppGStrCopy(s.DATEINAMEORG, t.c_str(), L_CSCORDERIMPORTCSVFILE_DATEINAMEORG); }
    void         SetCsvfehlertext(const ppString & t) { ppGStrCopy(s.CSVFEHLERTEXT, t.c_str(), L_CSCORDERIMPORTCSVFILE_CSVFEHLERTEXT); }
    void         SetCsvreportfile(const ppString & t) { ppGStrCopy(s.CSVREPORTFILE, t.c_str(), L_CSCORDERIMPORTCSVFILE_CSVREPORTFILE); }
    void         SetLanguage(const ppString & t) { ppGStrCopy(s.LANGUAGE, t.c_str(), L_CSCORDERIMPORTCSVFILE_LANGUAGE); }

    void         SetStruct(const cscorderimportcsvfileS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCSCORDERIMPORTCSVFILE() {
        ::buf_default((void *)&s, CSCORDERIMPORTCSVFILE_BES, CSCORDERIMPORTCSVFILE_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCSCORDERIMPORTCSVFILE() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CSCORDERIMPORTCSVFILE_BES, CSCORDERIMPORTCSVFILE_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CSCORDERIMPORTCSVFILE_BES, (int)CSCORDERIMPORTCSVFILE_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, CSCORDERIMPORTCSVFILE_BES, (int)CSCORDERIMPORTCSVFILE_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_CSCORDERIMPORTCSVFILE & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.CSVFORMATNAME);
        ppGStripLast(d.DATEINAME);
        ppGStripLast(d.CSVLOGFILE);
        ppGStripLast(d.DATEINAMEORG);
        ppGStripLast(d.CSVFEHLERTEXT);
        ppGStripLast(d.CSVREPORTFILE);
        ppGStripLast(d.LANGUAGE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CSCORDERIMPORTCSVFILE_BES, (int)CSCORDERIMPORTCSVFILE_ANZ, error_msg);
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
/* CreateSqlStatement of CSCORDERIMPORTCSVFILE ********************************/

 #define CSCORDERIMPORTCSVFILE_CREATE(x) EXEC SQL create table x (\
         CSVFORMATNAME varchar(200,0) default " " not null,\
         CSCORDERIMPORTFORMATID serial not null,\
         FEHLER integer default 0 not null,\
         DATEINAME char(200) default " " not null,\
         CSVLOGFILE char(255) default " " not null,\
         DATEINAMEORG char(200) default " " not null,\
         CSVFEHLERTEXT char(200) default " " not null,\
         CSVREPORTFILE char(200) default " " not null,\
         LANGUAGE char(2) default " " not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of CSCORDERIMPORTCSVFILE ******************************/

 #define CSCORDERIMPORTCSVFILE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_csvformat_1 on _X_(\
              CSCOrderImportFormatID );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CSCORDERIMPORTCSVFILE ******************************/

 #define CSCORDERIMPORTCSVFILE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_csvformat_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
