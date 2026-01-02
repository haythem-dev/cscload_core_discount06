#ifndef __PP_STOCKENTRY_H_
#define __PP_STOCKENTRY_H_

/******************************************************************************/
/* v:\nordat\stockentries *****************************************************/
/******************************************************************************/

/* Length-Define of STOCKENTRY **********************************************/

  #define L_STOCKENTRY_DATE 11
  #define L_STOCKENTRY_BRANCHNO 6
  #define L_STOCKENTRY_ARTICLENO 11

/* Length/Count-Define of STOCKENTRY ****************************************/

  #define LS_STOCKENTRY_DATE 10 + 1
  #define LS_STOCKENTRY_BRANCHNO 5 + 1
  #define LS_STOCKENTRY_ARTICLENO 10 + 1

  #define STOCKENTRYDATE 0
  #define STOCKENTRYBRANCHNO 1
  #define STOCKENTRYARTICLENO 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define STOCKENTRY_H
 #define STOCKENTRY_ANZ ( sizeof(STOCKENTRY_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of STOCKENTRY **************************************************/

 #define STOCKENTRY_LISTE \
         STOCKENTRY.DATE,\
         STOCKENTRY.BRANCHNO,\
         STOCKENTRY.ARTICLENO

 #define STOCKENTRY_LISTE_390 \
         DATE,\
         BRANCHNO,\
         ARTICLENO

 #define STOCKENTRY_PLISTE \
         "STOCKENTRY.DATE,"\
         "STOCKENTRY.BRANCHNO,"\
         "STOCKENTRY.ARTICLENO"

 #define STOCKENTRY_PELISTE \
         "DATE,"\
         "BRANCHNO,"\
         "ARTICLENO"

 #define STOCKENTRY_UPDLISTE \
         "DATE=?,"\
         "BRANCHNO=?,"\
         "ARTICLENO=?"

/* SqlMacros-Define of STOCKENTRY *******************************************/

 #define STOCKENTRY_ZEIGER(x) \
         :x->DATE,\
         :x->BRANCHNO,\
         :x->ARTICLENO

 #define STOCKENTRY_ZEIGERSEL(x) \
         :x->DATE,\
         :x->BRANCHNO,\
         :x->ARTICLENO

 #define STOCKENTRY_UPDATE(x) \
         STOCKENTRY.DATE=:x->DATE,\
         STOCKENTRY.BRANCHNO=:x->BRANCHNO,\
         STOCKENTRY.ARTICLENO=:x->ARTICLENO

/* SqlMacros390-Define of STOCKENTRY ****************************************/

 #define STOCKENTRY_ZEIGER_390 \
         :DATE,\
         :BRANCHNO,\
         :ARTICLENO

 #define STOCKENTRY_UPDATE_390 \
         DATE=:DATE,\
         BRANCHNO=:BRANCHNO,\
         ARTICLENO=:ARTICLENO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of STOCKENTRY *******************************************/

 #ifndef TRANSCLASS
 typedef struct N_STOCKENTRY {
         long DATE;
         short BRANCHNO;
         long ARTICLENO;
         long FETCH_REL;
        } stockentriesS;
 #else /*TRANSCLASS*/
 typedef struct N_STOCKENTRY {
         long DATE;
         short BRANCHNO;
         long ARTICLENO;
         long FETCH_REL;
                        bool operator==(const N_STOCKENTRY& right) const {
                        return(
                                DATE == right.DATE &&
                                BRANCHNO == right.BRANCHNO &&
                                ARTICLENO == right.ARTICLENO
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                DATE = 0;
                                BRANCHNO = 0;
                                ARTICLENO = 0;
#endif
                        }
         } stockentriesS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of STOCKENTRY **************************************/

 struct S_STOCKENTRY {
         char DATE[11];
         char BRANCHNO[7];
         char ARTICLENO[11];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of STOCKENTRY *********************/

 struct O_STOCKENTRY {
         char DATE[11];
         char BRANCHNO[7];
         char ARTICLENO[11];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of STOCKENTRY *********************************/

 struct C_STOCKENTRY {
         long DATE;
         short BRANCHNO;
         long ARTICLENO;
         long FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of STOCKENTRY *******************************/

 struct I_STOCKENTRY {
         short DATE;
         short BRANCHNO;
         short ARTICLENO;
         short FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of STOCKENTRY ****************************************/

#if defined (BUF_DESC)
 static struct buf_desc STOCKENTRY_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc STOCKENTRY_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of STOCKENTRY **********************************/

 #define STOCKENTRY_S390 \
         long DATE; \
         short BRANCHNO; \
         long ARTICLENO; \
         long FETCH_REL;



/* Copy-Function Struct to single Data STOCKENTRY ***************************/

 #define STOCKENTRY_S390_COPY_TO_SINGLE(_x_) \
         DATE=_x_->DATE;\
         BRANCHNO=_x_->BRANCHNO;\
         ARTICLENO=_x_->ARTICLENO;\
          FETCH_REL=_x_->FETCH_REL;\

 #define STOCKENTRY_S390_COPY_TO_STRUCT(_x_) \
          _x_->DATE=DATE;\
          _x_->BRANCHNO=BRANCHNO;\
          _x_->ARTICLENO=ARTICLENO;\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of stockentries **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of stockentries **********************************/


#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS
#include<vector>
using namespace std;

#ifndef __VIRTUAL_DADE_CLASS__
#define __VIRTUAL_DADE_CLASS__

class ppDadeVirtual
{
        public:
                virtual    ~ppDadeVirtual() {};
                virtual int SelList(int FetchRel = 1,int pos=0) = 0;
                virtual int SelListHist(int FetchRel = 1,int pos=0) = 0;
                virtual int SelListFuture(int FetchRel = 1,int pos=0) = 0;
                virtual int Load(int pos=0) = 0;
                virtual int Delete(int pos=0) = 0;
                virtual int Save(int pos=0) = 0;
};
#endif

class CSTOCKENTRY : public ppDadeVirtual
{
        //data members
        public:
                stockentriesS s;
                int rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<stockentriesS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<stockentriesS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<stockentriesS>; Strip(s); stockentriesS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<stockentriesS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<stockentriesS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<stockentriesS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetDate() const { return s.DATE; }
                short           GetBranchno() const     { return s.BRANCHNO; }
                long            GetArticleno() const    { return s.ARTICLENO; }
                const stockentriesS& GetStruct() const { return s; }
                long            GetFetch_rel() const { return s.FETCH_REL; }
                void            SetDate(long t) { s.DATE = t; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetArticleno(long t) { s.ARTICLENO = t; }
                void            SetStruct(const stockentriesS& t) { s = t; }
                void            SetFetch_rel(const long t) { s.FETCH_REL = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CSTOCKENTRY()  //constructor
                {
                        ::buf_default((void *)&s,STOCKENTRY_BES,STOCKENTRY_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CSTOCKENTRY()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                        CloseCursor();
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, STOCKENTRY_BES, STOCKENTRY_ANZ );
                }

                int CloseCursor(int pos = 0)  //close db cursor
                {
                        if( !bOpenCursor ) return 0;
                        s.FETCH_REL = 0;
                        #ifndef __DADE_LOAD__
                        rc=::ServerNr(pos, FncNumber, (void *)&s,STOCKENTRY_BES,STOCKENTRY_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
                        #endif
                        bOpenCursor = false;
                        bEndOfSelect = false;
                        FncNumber = 0;
                        CursorPos = 0;
                        AnzPos = 0;
                        if(pl)
                        {
                                delete pl;
                                pl = NULL;
                        }
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc=::ServerNr(pos, fkt_nr, (void *)&s,STOCKENTRY_BES,STOCKENTRY_ANZ, error_msg);
                        #else
                        rc=::Server(fkt_nr, (void *)&s,STOCKENTRY_BES,STOCKENTRY_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_STOCKENTRY& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc=::ServerNr(pos, FncNr, (void *)&s,STOCKENTRY_BES,STOCKENTRY_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

                int CursorServerCall(int FncNr,int FetchRel = 1, int pos=0)
                {
                        if              ( FetchRel == 0 ) return CloseCursor(pos);
                        else if ( FetchRel == 1 ) return GetNext(pos,FncNr);
                        else if ( FetchRel <  0 ) return ChangeCursor(FetchRel);
                        else
                        {
                                FehlerBehandlung( -1, "False cursor position!" );
                                return -1;
                        }
                }

                int GetNext(int pos, int FncNr)
                {
                        CSTOCKENTRY c;
                        if( bOpenCursor && FncNumber != FncNr ) CloseCursor(pos);
                        if( bOpenCursor ) s.FETCH_REL = 1;
                        else
                        {
                                s.FETCH_REL = 2;
                                bOpenCursor = true;
                                FncNumber = FncNr;
                                AnzPos = 0;
                                if ( pl ) delete pl;
                                pl = new vector<stockentriesS>;
                        }
                        if( CursorPos == AnzPos && bEndOfSelect ) { rc = 1; return 1; }
                        else if( CursorPos < AnzPos )
                        {
                                s = pl->at(CursorPos);
                                CursorPos++;
                                return 0;
                        }
                        #ifndef __DADE_LOAD__
                        rc=::ServerNr(pos, FncNumber, (void *)&s,STOCKENTRY_BES,STOCKENTRY_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc==0)
                        {
                                Strip(s);
                                c.s = s;
                                pl->insert(pl->end(),c.s);
                                bEndOfSelect = false;
                                CursorPos++;
                                AnzPos++;
                        }
                        else if (rc==1) bEndOfSelect = true;
                        else if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

                int ChangeCursor(int FetchRel) // FetchRel is a negative value
                {
                        CursorPos = CursorPos + FetchRel < 0 ? 0 : CursorPos + FetchRel - 1;
                        if ( CursorPos >= AnzPos )
                        {
                                FehlerBehandlung( -1, "False cursor position!" );
                                return -1;
                        }
                        s = pl->at(CursorPos);
                        CursorPos++;
                        rc = 0;
                        return 0;
                }

};

#endif

/* CreateSqlStatement of STOCKENTRY *****************************************/

 #define STOCKENTRY_CREATE(x) exec sql create table x (\
         DATE integer default 0 not null,\
         BRANCHNO smallint default 0 not null,\
         ARTICLENO integer default 0 not null) extent size 156 next size 16 lock mode row;



/* CreateIndexStatement of STOCKENTRY ***************************************/

 #define STOCKENTRY_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_stockentry_1 on _X_(\
              date,\
              BranchNo,\
              ArticleNo );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of STOCKENTRY ***************************************/

 #define STOCKENTRY_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_stockentry_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
