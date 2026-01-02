#ifndef __PP_CSCORDERIMPORTCSVFORMATS_H_
#define __PP_CSCORDERIMPORTCSVFORMATS_H_

/******************************************************************************/
/**/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of CSCORDERIMPORTCSVFORMATS **********************************/

#define L_CSCORDERIMPORTCSVFORMATS_CSVFORMATNAME 200
#define L_CSCORDERIMPORTCSVFORMATS_DATASTARTINGLINE 6
#define L_CSCORDERIMPORTCSVFORMATS_POSTPONEORDER 6
#define L_CSCORDERIMPORTCSVFORMATS_CSCORDERIMPORTFORMATID 11
#define L_CSCORDERIMPORTCSVFORMATS_ISVALID 6

/* Length/Count-Define of CSCORDERIMPORTCSVFORMATS ****************************/

#define LS_CSCORDERIMPORTCSVFORMATS_CSVFORMATNAME 200 + 1
#define LS_CSCORDERIMPORTCSVFORMATS_DATASTARTINGLINE 5 + 1
#define LS_CSCORDERIMPORTCSVFORMATS_POSTPONEORDER 5 + 1
#define LS_CSCORDERIMPORTCSVFORMATS_CSCORDERIMPORTFORMATID 10 + 1
#define LS_CSCORDERIMPORTCSVFORMATS_ISVALID 5 + 1

#define CSCORDERIMPORTCSVFORMATSCSVFORMATNAME 0
#define CSCORDERIMPORTCSVFORMATSDATASTARTINGLINE 1
#define CSCORDERIMPORTCSVFORMATSPOSTPONEORDER 2
#define CSCORDERIMPORTCSVFORMATSCSCORDERIMPORTFORMATID 3
#define CSCORDERIMPORTCSVFORMATSISVALID 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CSCORDERIMPORTCSVFORMATS_H
#define CSCORDERIMPORTCSVFORMATS_ANZ ( sizeof(CSCORDERIMPORTCSVFORMATS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CSCORDERIMPORTCSVFORMATS **************************************/

#define CSCORDERIMPORTCSVFORMATS_LISTE \
        CSCORDERIMPORTCSVFORMATS.CSVFORMATNAME,\
        CSCORDERIMPORTCSVFORMATS.DATASTARTINGLINE,\
        CSCORDERIMPORTCSVFORMATS.POSTPONEORDER,\
        CSCORDERIMPORTCSVFORMATS.CSCORDERIMPORTFORMATID,\
        AADUMMY.ISVALID
#define CSCORDERIMPORTCSVFORMATS_LISTE_390 \
        CSVFORMATNAME,\
        DATASTARTINGLINE,\
        POSTPONEORDER,\
        CSCORDERIMPORTFORMATID,\
        ISVALID
#define CSCORDERIMPORTCSVFORMATS_PLISTE \
        "CSCORDERIMPORTCSVFORMATS.CSVFORMATNAME,"\
        "CSCORDERIMPORTCSVFORMATS.DATASTARTINGLINE,"\
        "CSCORDERIMPORTCSVFORMATS.POSTPONEORDER,"\
        "CSCORDERIMPORTCSVFORMATS.CSCORDERIMPORTFORMATID,"\
        "AADUMMY.ISVALID"
#define CSCORDERIMPORTCSVFORMATS_PELISTE \
        "CSVFORMATNAME,"\
        "DATASTARTINGLINE,"\
        "POSTPONEORDER,"\
        "CSCORDERIMPORTFORMATID,"\
        "ISVALID"
#define CSCORDERIMPORTCSVFORMATS_UPDLISTE \
        "CSVFORMATNAME=?,"\
        "DATASTARTINGLINE=?,"\
        "POSTPONEORDER=?,"\
        "CSCORDERIMPORTFORMATID=?,"\
        "ISVALID=?"
/* SqlMacros-Define of CSCORDERIMPORTCSVFORMATS *******************************/

#define CSCORDERIMPORTCSVFORMATS_ZEIGER(x) \
        :x->CSVFORMATNAME,\
        :x->DATASTARTINGLINE,\
        :x->POSTPONEORDER,\
        :x->CSCORDERIMPORTFORMATID,\
        :x->ISVALID
#define CSCORDERIMPORTCSVFORMATS_ZEIGERSEL(x) \
        :x->CSVFORMATNAME,\
        :x->DATASTARTINGLINE,\
        :x->POSTPONEORDER,\
        :x->CSCORDERIMPORTFORMATID,\
        :x->ISVALID
#define CSCORDERIMPORTCSVFORMATS_UPDATE(x) \
        CSCORDERIMPORTCSVFORMATS.CSVFORMATNAME=:x->CSVFORMATNAME,\
        CSCORDERIMPORTCSVFORMATS.DATASTARTINGLINE=:x->DATASTARTINGLINE,\
        CSCORDERIMPORTCSVFORMATS.POSTPONEORDER=:x->POSTPONEORDER,\
        AADUMMY.ISVALID=:x->ISVALID
/* SqlMacros390-Define of CSCORDERIMPORTCSVFORMATS ****************************/

#define CSCORDERIMPORTCSVFORMATS_ZEIGER_390 \
        :CSVFORMATNAME,\
        :DATASTARTINGLINE,\
        :POSTPONEORDER,\
        :CSCORDERIMPORTFORMATID,\
        :ISVALID
#define CSCORDERIMPORTCSVFORMATS_UPDATE_390 \
        CSVFORMATNAME=:CSVFORMATNAME,\
        DATASTARTINGLINE=:DATASTARTINGLINE,\
        POSTPONEORDER=:POSTPONEORDER,\
        CSCORDERIMPORTFORMATID=:CSCORDERIMPORTFORMATID,\
        ISVALID=:ISVALID
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CSCORDERIMPORTCSVFORMATS ********************************/

#ifndef TRANSCLASS
typedef struct N_CSCORDERIMPORTCSVFORMATS {
    char CSVFORMATNAME[201];
    short DATASTARTINGLINE;
    short POSTPONEORDER;
    long CSCORDERIMPORTFORMATID;
    short ISVALID;
} cscorderimportcsvformatsS;
#else /* TRANSCLASS */
typedef struct N_CSCORDERIMPORTCSVFORMATS {
    char CSVFORMATNAME[201];
    short DATASTARTINGLINE;
    short POSTPONEORDER;
    long CSCORDERIMPORTFORMATID;
    short ISVALID;

    bool operator == (const N_CSCORDERIMPORTCSVFORMATS& right) const {
        return (
            !strcmp(CSVFORMATNAME, right.CSVFORMATNAME) &&
            DATASTARTINGLINE == right.DATASTARTINGLINE &&
            POSTPONEORDER == right.POSTPONEORDER &&
            CSCORDERIMPORTFORMATID == right.CSCORDERIMPORTFORMATID &&
            ISVALID == right.ISVALID
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        strcpy(CSVFORMATNAME, " " );
        DATASTARTINGLINE = 0;
        POSTPONEORDER = 0;
        CSCORDERIMPORTFORMATID = 0;
        ISVALID = 0;
#endif
    }
} cscorderimportcsvformatsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CSCORDERIMPORTCSVFORMATS **************************/

struct S_CSCORDERIMPORTCSVFORMATS {
    char CSVFORMATNAME[200 + 1];
    char DATASTARTINGLINE[7];
    char POSTPONEORDER[7];
    char CSCORDERIMPORTFORMATID[11];
    char ISVALID[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CSCORDERIMPORTCSVFORMATS *********/

struct O_CSCORDERIMPORTCSVFORMATS {
    char CSVFORMATNAME[200];
    char DATASTARTINGLINE[7];
    char POSTPONEORDER[7];
    char CSCORDERIMPORTFORMATID[11];
    char ISVALID[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CSCORDERIMPORTCSVFORMATS ********************/

struct C_CSCORDERIMPORTCSVFORMATS {
    char CSVFORMATNAME[201];
    short DATASTARTINGLINE;
    short POSTPONEORDER;
    long CSCORDERIMPORTFORMATID;
    short ISVALID;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CSCORDERIMPORTCSVFORMATS ******************/

struct I_CSCORDERIMPORTCSVFORMATS {
    short CSVFORMATNAME;
    short DATASTARTINGLINE;
    short POSTPONEORDER;
    short CSCORDERIMPORTFORMATID;
    short ISVALID;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CSCORDERIMPORTCSVFORMATS ****************************/

#if defined (BUF_DESC)
static struct buf_desc CSCORDERIMPORTCSVFORMATS_BES [] = {
   { TYP_C, 200, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L ,  11, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CSCORDERIMPORTCSVFORMATS_BES [] = {
   { TYP_C, 200, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L ,  11, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of CSCORDERIMPORTCSVFORMATS **********************/

 #define CSCORDERIMPORTCSVFORMATS_S390 \
         char CSVFORMATNAME[201]; \
         short DATASTARTINGLINE; \
         short POSTPONEORDER; \
         long CSCORDERIMPORTFORMATID; \
         short ISVALID; \



/* Copy-Function Struct to single Data CSCORDERIMPORTCSVFORMATS ***************/

 #define CSCORDERIMPORTCSVFORMATS_S390_COPY_TO_SINGLE(_x_) \
          strcpy(CSVFORMATNAME,_x_->CSVFORMATNAME);\
         DATASTARTINGLINE=_x_->DATASTARTINGLINE;\
         POSTPONEORDER=_x_->POSTPONEORDER;\
         CSCORDERIMPORTFORMATID=_x_->CSCORDERIMPORTFORMATID;\
         ISVALID=_x_->ISVALID;\

 #define CSCORDERIMPORTCSVFORMATS_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->CSVFORMATNAME,CSVFORMATNAME);\
          _x_->DATASTARTINGLINE=DATASTARTINGLINE;\
          _x_->POSTPONEORDER=POSTPONEORDER;\
          _x_->CSCORDERIMPORTFORMATID=CSCORDERIMPORTFORMATID;\
          _x_->ISVALID=ISVALID;\



/* FunctionNumber-Define of CSCOrderImportCSVFormats **************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CSCOrderImportCSVFormats **********************/


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

class CCSCORDERIMPORTCSVFORMATS : public ppDadeVirtual {
public:
    cscorderimportcsvformatsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cscorderimportcsvformatsS> lst; // class list

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
                     vector< cscorderimportcsvformatsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cscorderimportcsvformatsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cscorderimportcsvformatsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cscorderimportcsvformatsS>::iterator
                 beginList() { return lst.begin(); }
    vector<cscorderimportcsvformatsS>::iterator
                 endList  () { return lst.end  (); }

    const char*  GetCsvformatname(ppString & t) const { t = s.CSVFORMATNAME; t.erasespace(ppString::END); return t.c_str(); }
    short        GetDatastartingline() const { return s.DATASTARTINGLINE; }
    short        GetPostponeorder() const { return s.POSTPONEORDER; }
    long         GetCscorderimportformatid() const { return s.CSCORDERIMPORTFORMATID; }
    short        GetIsvalid() const { return s.ISVALID; }

    const cscorderimportcsvformatsS &
                 GetStruct() const { return s; }
    void         SetCsvformatname(const ppString & t) { ppGStrCopy(s.CSVFORMATNAME, t.c_str(), L_CSCORDERIMPORTCSVFORMATS_CSVFORMATNAME); }
    void         SetDatastartingline(short t) { s.DATASTARTINGLINE = t; }
    void         SetPostponeorder(short t) { s.POSTPONEORDER = t; }
    void         SetCscorderimportformatid(long t) { s.CSCORDERIMPORTFORMATID = t; }
    void         SetIsvalid(short t) { s.ISVALID = t; }

    void         SetStruct(const cscorderimportcsvformatsS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCSCORDERIMPORTCSVFORMATS() {
        ::buf_default((void *)&s, CSCORDERIMPORTCSVFORMATS_BES, CSCORDERIMPORTCSVFORMATS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCSCORDERIMPORTCSVFORMATS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CSCORDERIMPORTCSVFORMATS_BES, CSCORDERIMPORTCSVFORMATS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CSCORDERIMPORTCSVFORMATS_BES, (int)CSCORDERIMPORTCSVFORMATS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, CSCORDERIMPORTCSVFORMATS_BES, (int)CSCORDERIMPORTCSVFORMATS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_CSCORDERIMPORTCSVFORMATS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.CSVFORMATNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CSCORDERIMPORTCSVFORMATS_BES, (int)CSCORDERIMPORTCSVFORMATS_ANZ, error_msg);
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
/* CreateSqlStatement of CSCORDERIMPORTCSVFORMATS *****************************/

 #define CSCORDERIMPORTCSVFORMATS_CREATE(x) EXEC SQL create table x (\
         CSVFORMATNAME varchar(200,0) default " " not null,\
         DATASTARTINGLINE smallint default 0 not null,\
         POSTPONEORDER smallint default 0 not null,\
         CSCORDERIMPORTFORMATID serial not null,\
         ISVALID smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of CSCORDERIMPORTCSVFORMATS ***************************/

 #define CSCORDERIMPORTCSVFORMATS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_csvformat_1 on _X_(\
              CSCOrderImportFormatID ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CSCORDERIMPORTCSVFORMATS ***************************/

 #define CSCORDERIMPORTCSVFORMATS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_csvformat_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
