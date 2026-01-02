#ifndef __PP_ARTICLEPACKUNIT_H_
#define __PP_ARTICLEPACKUNIT_H_

/******************************************************************************/
/* v:\nordat\ArticlePackUnit **************************************************/
/******************************************************************************/

/* Length-Define of ARTICLEPACKUNIT *******************************************/

  #define L_ARTICLEPACKUNIT_ARTICLENO 11
  #define L_ARTICLEPACKUNIT_PACKINGUNIT 11
  #define L_ARTICLEPACKUNIT_ROUNDPCT 6

/* Length/Count-Define of ARTICLEPACKUNIT *************************************/

  #define LS_ARTICLEPACKUNIT_ARTICLENO 10 + 1
  #define LS_ARTICLEPACKUNIT_PACKINGUNIT 10 + 1
  #define LS_ARTICLEPACKUNIT_ROUNDPCT 5 + 1

  #define ARTICLEPACKUNITARTICLENO 0
  #define ARTICLEPACKUNITPACKINGUNIT 1
  #define ARTICLEPACKUNITROUNDPCT 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTICLEPACKUNIT_H
 #define ARTICLEPACKUNIT_ANZ ( sizeof(ARTICLEPACKUNIT_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTICLEPACKUNIT ***********************************************/

 #define ARTICLEPACKUNIT_LISTE \
         ARTICLEPACKUNIT.ARTICLENO,\
         ARTICLEPACKUNIT.PACKINGUNIT,\
         ARTICLEPACKUNIT.ROUNDPCT

 #define ARTICLEPACKUNIT_LISTE_390 \
         ARTICLENO,\
         PACKINGUNIT,\
         ROUNDPCT

 #define ARTICLEPACKUNIT_PLISTE \
         "ARTICLEPACKUNIT.ARTICLENO,"\
         "ARTICLEPACKUNIT.PACKINGUNIT,"\
         "ARTICLEPACKUNIT.ROUNDPCT"

 #define ARTICLEPACKUNIT_PELISTE \
         "ARTICLENO,"\
         "PACKINGUNIT,"\
         "ROUNDPCT"

 #define ARTICLEPACKUNIT_UPDLISTE \
         "ARTICLENO=?,"\
         "PACKINGUNIT=?,"\
         "ROUNDPCT=?"

/* SqlMacros-Define of ARTICLEPACKUNIT ****************************************/

 #define ARTICLEPACKUNIT_ZEIGER(x) \
         :x->ARTICLENO,\
         :x->PACKINGUNIT,\
         :x->ROUNDPCT

 #define ARTICLEPACKUNIT_ZEIGERSEL(x) \
         :x->ARTICLENO,\
         :x->PACKINGUNIT,\
         :x->ROUNDPCT

 #define ARTICLEPACKUNIT_UPDATE(x) \
         ARTICLEPACKUNIT.ARTICLENO=:x->ARTICLENO,\
         ARTICLEPACKUNIT.PACKINGUNIT=:x->PACKINGUNIT,\
         ARTICLEPACKUNIT.ROUNDPCT=:x->ROUNDPCT

/* SqlMacros390-Define of ARTICLEPACKUNIT *************************************/

 #define ARTICLEPACKUNIT_ZEIGER_390 \
         :ARTICLENO,\
         :PACKINGUNIT,\
         :ROUNDPCT

 #define ARTICLEPACKUNIT_UPDATE_390 \
         ARTICLENO=:ARTICLENO,\
         PACKINGUNIT=:PACKINGUNIT,\
         ROUNDPCT=:ROUNDPCT

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTICLEPACKUNIT ****************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTICLEPACKUNIT {
         long ARTICLENO;
         long PACKINGUNIT;
         short ROUNDPCT;
        } articlepackunitS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTICLEPACKUNIT {
         long ARTICLENO;
         long PACKINGUNIT;
         short ROUNDPCT;

                        bool operator==(const N_ARTICLEPACKUNIT& right) const {
                        return(
                                ARTICLENO == right.ARTICLENO &&
                                PACKINGUNIT == right.PACKINGUNIT &&
                                ROUNDPCT == right.ROUNDPCT
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                ARTICLENO = 0;
                                PACKINGUNIT = 0;
                                ROUNDPCT = 0;
#endif
                        }
         } articlepackunitS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTICLEPACKUNIT ***********************************/

 struct S_ARTICLEPACKUNIT {
         char ARTICLENO[11];
         char PACKINGUNIT[11];
         char ROUNDPCT[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTICLEPACKUNIT ******************/

 struct O_ARTICLEPACKUNIT {
         char ARTICLENO[11];
         char PACKINGUNIT[11];
         char ROUNDPCT[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTICLEPACKUNIT *****************************/

 struct C_ARTICLEPACKUNIT {
         long ARTICLENO;
         long PACKINGUNIT;
         short ROUNDPCT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTICLEPACKUNIT ***************************/

 struct I_ARTICLEPACKUNIT {
         short ARTICLENO;
         short PACKINGUNIT;
         short ROUNDPCT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTICLEPACKUNIT *************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTICLEPACKUNIT_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTICLEPACKUNIT_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of ARTICLEPACKUNIT *******************************/

 #define ARTICLEPACKUNIT_S390 \
         long ARTICLENO; \
         long PACKINGUNIT; \
         short ROUNDPCT; \



/* Copy-Function Struct to single Data ARTICLEPACKUNIT ************************/

 #define ARTICLEPACKUNIT_S390_COPY_TO_SINGLE(_x_) \
         ARTICLENO=_x_->ARTICLENO;\
         PACKINGUNIT=_x_->PACKINGUNIT;\
         ROUNDPCT=_x_->ROUNDPCT;\

 #define ARTICLEPACKUNIT_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLENO=ARTICLENO;\
          _x_->PACKINGUNIT=PACKINGUNIT;\
          _x_->ROUNDPCT=ROUNDPCT;\



/* FunctionNumber-Define of ArticlePackUnit ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArticlePackUnit *******************************/


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
                virtual int SelList      (int FetchRel = 1, int pos = 0) = 0;
                virtual int SelListHist  (int FetchRel = 1, int pos = 0) = 0;
                virtual int SelListFuture(int FetchRel = 1, int pos = 0) = 0;
                virtual int Load         (int pos = 0                  ) = 0;
                virtual int Delete       (int pos = 0                  ) = 0;
                virtual int Save         (int pos = 0                  ) = 0;
};
#endif

class CARTICLEPACKUNIT : public ppDadeVirtual
{
        //data members
        public:
                articlepackunitS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<articlepackunitS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<articlepackunitS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<articlepackunitS>; Strip(s); articlepackunitS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<articlepackunitS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<articlepackunitS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<articlepackunitS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetArticleno() const    { return s.ARTICLENO; }
                long            GetPackingunit() const  { return s.PACKINGUNIT; }
                short           GetRoundpct() const     { return s.ROUNDPCT; }
                const articlepackunitS& GetStruct() const { return s; }
                void            SetArticleno(long t) { s.ARTICLENO = t; }
                void            SetPackingunit(long t) { s.PACKINGUNIT = t; }
                void            SetRoundpct(short t) { s.ROUNDPCT = t; }
                void            SetStruct(const articlepackunitS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CARTICLEPACKUNIT()  //constructor
                {
                        ::buf_default((void *)&s, ARTICLEPACKUNIT_BES, ARTICLEPACKUNIT_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CARTICLEPACKUNIT()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ARTICLEPACKUNIT_BES, ARTICLEPACKUNIT_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTICLEPACKUNIT_BES, ARTICLEPACKUNIT_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, ARTICLEPACKUNIT_BES, ARTICLEPACKUNIT_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ARTICLEPACKUNIT& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, ARTICLEPACKUNIT_BES, ARTICLEPACKUNIT_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ARTICLEPACKUNIT **************************************/

 #define ARTICLEPACKUNIT_CREATE(x) exec sql create table x (\
         ARTICLENO integer default 0 not null,\
         PACKINGUNIT integer default 0 not null,\
         ROUNDPCT smallint default 0 not null) in ksc extent size 4704 next size 472 lock mode row;



/* CreateIndexStatement of ARTICLEPACKUNIT ************************************/

 #define ARTICLEPACKUNIT_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_articlepack_1 on _X_(\
              ArticleNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTICLEPACKUNIT ************************************/

 #define ARTICLEPACKUNIT_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_articlepack_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
