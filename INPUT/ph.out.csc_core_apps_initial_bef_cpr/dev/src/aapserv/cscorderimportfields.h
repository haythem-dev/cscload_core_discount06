#ifndef __PP_CSCORDERIMPORTFIELDS_H_
#define __PP_CSCORDERIMPORTFIELDS_H_

/******************************************************************************/
/**/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#include <bufkon.h>

/* Length-Define of CSCORDERIMPORTFIELDS **************************************/

#define L_CSCORDERIMPORTFIELDS_FIELDNAMEID 11
#define L_CSCORDERIMPORTFIELDS_IMPORTFIELDNAME 25
#define L_CSCORDERIMPORTFIELDS_DISPLAYNAME 50
#define L_CSCORDERIMPORTFIELDS_IMPORTMANDATORY 6

/* Length/Count-Define of CSCORDERIMPORTFIELDS ********************************/

#define LS_CSCORDERIMPORTFIELDS_FIELDNAMEID 10 + 1
#define LS_CSCORDERIMPORTFIELDS_IMPORTFIELDNAME 25 + 1
#define LS_CSCORDERIMPORTFIELDS_DISPLAYNAME 50 + 1
#define LS_CSCORDERIMPORTFIELDS_IMPORTMANDATORY 5 + 1

#define CSCORDERIMPORTFIELDSFIELDNAMEID 0
#define CSCORDERIMPORTFIELDSIMPORTFIELDNAME 1
#define CSCORDERIMPORTFIELDSDISPLAYNAME 2
#define CSCORDERIMPORTFIELDSIMPORTMANDATORY 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CSCORDERIMPORTFIELDS_H
#define CSCORDERIMPORTFIELDS_ANZ ( sizeof(CSCORDERIMPORTFIELDS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CSCORDERIMPORTFIELDS ******************************************/

#define CSCORDERIMPORTFIELDS_LISTE \
        CSCORDERIMPORTFIELDS.FIELDNAMEID,\
        CSCORDERIMPORTFIELDS.IMPORTFIELDNAME,\
        CSCORDERIMPORTFIELDS.DISPLAYNAME,\
        CSCORDERIMPORTFIELDS.IMPORTMANDATORY
#define CSCORDERIMPORTFIELDS_LISTE_390 \
        FIELDNAMEID,\
        IMPORTFIELDNAME,\
        DISPLAYNAME,\
        IMPORTMANDATORY
#define CSCORDERIMPORTFIELDS_PLISTE \
        "CSCORDERIMPORTFIELDS.FIELDNAMEID,"\
        "CSCORDERIMPORTFIELDS.IMPORTFIELDNAME,"\
        "CSCORDERIMPORTFIELDS.DISPLAYNAME,"\
        "CSCORDERIMPORTFIELDS.IMPORTMANDATORY"
#define CSCORDERIMPORTFIELDS_PELISTE \
        "FIELDNAMEID,"\
        "IMPORTFIELDNAME,"\
        "DISPLAYNAME,"\
        "IMPORTMANDATORY"
#define CSCORDERIMPORTFIELDS_UPDLISTE \
        "FIELDNAMEID=?,"\
        "IMPORTFIELDNAME=?,"\
        "DISPLAYNAME=?,"\
        "IMPORTMANDATORY=?"
/* SqlMacros-Define of CSCORDERIMPORTFIELDS ***********************************/

#define CSCORDERIMPORTFIELDS_ZEIGER(x) \
        :x->FIELDNAMEID,\
        :x->IMPORTFIELDNAME,\
        :x->DISPLAYNAME,\
        :x->IMPORTMANDATORY
#define CSCORDERIMPORTFIELDS_ZEIGERSEL(x) \
        :x->FIELDNAMEID,\
        :x->IMPORTFIELDNAME,\
        :x->DISPLAYNAME,\
        :x->IMPORTMANDATORY
#define CSCORDERIMPORTFIELDS_UPDATE(x) \
        CSCORDERIMPORTFIELDS.IMPORTFIELDNAME=:x->IMPORTFIELDNAME,\
        CSCORDERIMPORTFIELDS.DISPLAYNAME=:x->DISPLAYNAME,\
        CSCORDERIMPORTFIELDS.IMPORTMANDATORY=:x->IMPORTMANDATORY
/* SqlMacros390-Define of CSCORDERIMPORTFIELDS ********************************/

#define CSCORDERIMPORTFIELDS_ZEIGER_390 \
        :FIELDNAMEID,\
        :IMPORTFIELDNAME,\
        :DISPLAYNAME,\
        :IMPORTMANDATORY
#define CSCORDERIMPORTFIELDS_UPDATE_390 \
        FIELDNAMEID=:FIELDNAMEID,\
        IMPORTFIELDNAME=:IMPORTFIELDNAME,\
        DISPLAYNAME=:DISPLAYNAME,\
        IMPORTMANDATORY=:IMPORTMANDATORY
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CSCORDERIMPORTFIELDS ************************************/

#ifndef TRANSCLASS
typedef struct N_CSCORDERIMPORTFIELDS {
    long FIELDNAMEID;
    char IMPORTFIELDNAME[26];
    char DISPLAYNAME[51];
    short IMPORTMANDATORY;
} cscorderimportfieldsS;
#else /* TRANSCLASS */
typedef struct N_CSCORDERIMPORTFIELDS {
    long FIELDNAMEID;
    char IMPORTFIELDNAME[26];
    char DISPLAYNAME[51];
    short IMPORTMANDATORY;

    bool operator == (const N_CSCORDERIMPORTFIELDS& right) const {
        return (
            FIELDNAMEID == right.FIELDNAMEID &&
            !strcmp(IMPORTFIELDNAME, right.IMPORTFIELDNAME) &&
            !strcmp(DISPLAYNAME, right.DISPLAYNAME) &&
            IMPORTMANDATORY == right.IMPORTMANDATORY
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        FIELDNAMEID = 0;
        strcpy(IMPORTFIELDNAME, " " );
        strcpy(DISPLAYNAME, " " );
        IMPORTMANDATORY = 0;
#endif
    }
} cscorderimportfieldsS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CSCORDERIMPORTFIELDS ******************************/

struct S_CSCORDERIMPORTFIELDS {
    char FIELDNAMEID[11];
    char IMPORTFIELDNAME[25 + 1];
    char DISPLAYNAME[50 + 1];
    char IMPORTMANDATORY[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CSCORDERIMPORTFIELDS *************/

struct O_CSCORDERIMPORTFIELDS {
    char FIELDNAMEID[11];
    char IMPORTFIELDNAME[25];
    char DISPLAYNAME[50];
    char IMPORTMANDATORY[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CSCORDERIMPORTFIELDS ************************/

struct C_CSCORDERIMPORTFIELDS {
    long FIELDNAMEID;
    char IMPORTFIELDNAME[26];
    char DISPLAYNAME[51];
    short IMPORTMANDATORY;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CSCORDERIMPORTFIELDS **********************/

struct I_CSCORDERIMPORTFIELDS {
    short FIELDNAMEID;
    short IMPORTFIELDNAME;
    short DISPLAYNAME;
    short IMPORTMANDATORY;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CSCORDERIMPORTFIELDS ********************************/

#if defined (BUF_DESC)
static struct buf_desc CSCORDERIMPORTFIELDS_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_C, 25, 0 },
   { TYP_C, 50, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CSCORDERIMPORTFIELDS_BES [] = {
   { TYP_L ,  11, 0 },
   { TYP_C, 25, 0 },
   { TYP_C, 50, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of CSCORDERIMPORTFIELDS **************************/

 #define CSCORDERIMPORTFIELDS_S390 \
         long FIELDNAMEID; \
         char IMPORTFIELDNAME[26]; \
         char DISPLAYNAME[51]; \
         short IMPORTMANDATORY; \



/* Copy-Function Struct to single Data CSCORDERIMPORTFIELDS *******************/

 #define CSCORDERIMPORTFIELDS_S390_COPY_TO_SINGLE(_x_) \
         FIELDNAMEID=_x_->FIELDNAMEID;\
          strcpy(IMPORTFIELDNAME,_x_->IMPORTFIELDNAME);\
          strcpy(DISPLAYNAME,_x_->DISPLAYNAME);\
         IMPORTMANDATORY=_x_->IMPORTMANDATORY;\

 #define CSCORDERIMPORTFIELDS_S390_COPY_TO_STRUCT(_x_) \
          _x_->FIELDNAMEID=FIELDNAMEID;\
          strcpy(_x_->IMPORTFIELDNAME,IMPORTFIELDNAME);\
          strcpy(_x_->DISPLAYNAME,DISPLAYNAME);\
          _x_->IMPORTMANDATORY=IMPORTMANDATORY;\



/* FunctionNumber-Define of CSCOrderImportFields ******************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CSCOrderImportFields **************************/


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

class CCSCORDERIMPORTFIELDS : public ppDadeVirtual {
public:
    cscorderimportfieldsS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<cscorderimportfieldsS> lst; // class list

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
                     vector< cscorderimportfieldsS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     cscorderimportfieldsS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< cscorderimportfieldsS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<cscorderimportfieldsS>::iterator
                 beginList() { return lst.begin(); }
    vector<cscorderimportfieldsS>::iterator
                 endList  () { return lst.end  (); }

    long         GetFieldnameid() const { return s.FIELDNAMEID; }
    const char*  GetImportfieldname(ppString & t) const { t = s.IMPORTFIELDNAME; t.erasespace(ppString::END); return t.c_str(); }
    const char*  GetDisplayname(ppString & t) const { t = s.DISPLAYNAME; t.erasespace(ppString::END); return t.c_str(); }
    short        GetImportmandatory() const { return s.IMPORTMANDATORY; }

    const cscorderimportfieldsS &
                 GetStruct() const { return s; }
    void         SetFieldnameid(long t) { s.FIELDNAMEID = t; }
    void         SetImportfieldname(const ppString & t) { ppGStrCopy(s.IMPORTFIELDNAME, t.c_str(), L_CSCORDERIMPORTFIELDS_IMPORTFIELDNAME); }
    void         SetDisplayname(const ppString & t) { ppGStrCopy(s.DISPLAYNAME, t.c_str(), L_CSCORDERIMPORTFIELDS_DISPLAYNAME); }
    void         SetImportmandatory(short t) { s.IMPORTMANDATORY = t; }

    void         SetStruct(const cscorderimportfieldsS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCSCORDERIMPORTFIELDS() {
        ::buf_default((void *)&s, CSCORDERIMPORTFIELDS_BES, CSCORDERIMPORTFIELDS_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCSCORDERIMPORTFIELDS() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CSCORDERIMPORTFIELDS_BES, CSCORDERIMPORTFIELDS_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CSCORDERIMPORTFIELDS_BES, (int)CSCORDERIMPORTFIELDS_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, CSCORDERIMPORTFIELDS_BES, (int)CSCORDERIMPORTFIELDS_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_CSCORDERIMPORTFIELDS & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.IMPORTFIELDNAME);
        ppGStripLast(d.DISPLAYNAME);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CSCORDERIMPORTFIELDS_BES, (int)CSCORDERIMPORTFIELDS_ANZ, error_msg);
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
/* CreateSqlStatement of CSCORDERIMPORTFIELDS *********************************/

 #define CSCORDERIMPORTFIELDS_CREATE(x) EXEC SQL create table x (\
         FIELDNAMEID serial not null,\
         IMPORTFIELDNAME varchar(25,0) default " " not null,\
         DISPLAYNAME varchar(50,0) default " " not null,\
         IMPORTMANDATORY smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of CSCORDERIMPORTFIELDS *******************************/

 #define CSCORDERIMPORTFIELDS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         EXEC SQL create unique index i_importfields_1 on _X_(\
              FieldNameID ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CSCORDERIMPORTFIELDS *******************************/

 #define CSCORDERIMPORTFIELDS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         EXEC SQL drop index i_importfields_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\




#endif   // GUARD
