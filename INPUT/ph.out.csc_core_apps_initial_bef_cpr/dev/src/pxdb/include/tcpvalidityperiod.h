#ifndef __PP_CPVALIDITYPERIOD_H_
#define __PP_CPVALIDITYPERIOD_H_

/******************************************************************************/
/* u:\cpValidityPeriod ********************************************************/
/******************************************************************************/

/* Length-Define of CPVALIDITYPERIOD ******************************************/

  #define L_CPVALIDITYPERIOD_ARTICLE_NO_PACK 11
  #define L_CPVALIDITYPERIOD_DATEFROM 11
  #define L_CPVALIDITYPERIOD_DATETO 11
  #define L_CPVALIDITYPERIOD_COMPACK_TYPE 6

/* Length/Count-Define of CPVALIDITYPERIOD ************************************/

  #define LS_CPVALIDITYPERIOD_ARTICLE_NO_PACK 10 + 1
  #define LS_CPVALIDITYPERIOD_DATEFROM 10 + 1
  #define LS_CPVALIDITYPERIOD_DATETO 10 + 1
  #define LS_CPVALIDITYPERIOD_COMPACK_TYPE 5 + 1

  #define CPVALIDITYPERIODARTICLE_NO_PACK 0
  #define CPVALIDITYPERIODDATEFROM 1
  #define CPVALIDITYPERIODDATETO 2
  #define CPVALIDITYPERIODCOMPACK_TYPE 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define CPVALIDITYPERIOD_H
 #define CPVALIDITYPERIOD_ANZ ( sizeof(CPVALIDITYPERIOD_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CPVALIDITYPERIOD **********************************************/

 #define CPVALIDITYPERIOD_LISTE \
         CPVALIDITYPERIOD.ARTICLE_NO_PACK,\
         CPVALIDITYPERIOD.DATEFROM,\
         CPVALIDITYPERIOD.DATETO,\
         CPVALIDITYPERIOD.COMPACK_TYPE

 #define CPVALIDITYPERIOD_LISTE_390 \
         ARTICLE_NO_PACK,\
         DATEFROM,\
         DATETO,\
         COMPACK_TYPE

 #define CPVALIDITYPERIOD_PLISTE \
         "CPVALIDITYPERIOD.ARTICLE_NO_PACK,"\
         "CPVALIDITYPERIOD.DATEFROM,"\
         "CPVALIDITYPERIOD.DATETO,"\
         "CPVALIDITYPERIOD.COMPACK_TYPE"

 #define CPVALIDITYPERIOD_PELISTE \
         "ARTICLE_NO_PACK,"\
         "DATEFROM,"\
         "DATETO,"\
         "COMPACK_TYPE"

 #define CPVALIDITYPERIOD_UPDLISTE \
         "ARTICLE_NO_PACK=?,"\
         "DATEFROM=?,"\
         "DATETO=?,"\
         "COMPACK_TYPE=?"

/* SqlMacros-Define of CPVALIDITYPERIOD ***************************************/

 #define CPVALIDITYPERIOD_ZEIGER(x) \
         :x->ARTICLE_NO_PACK,\
         :x->DATEFROM,\
         :x->DATETO,\
         :x->COMPACK_TYPE

 #define CPVALIDITYPERIOD_ZEIGERSEL(x) \
         :x->ARTICLE_NO_PACK,\
         :x->DATEFROM,\
         :x->DATETO,\
         :x->COMPACK_TYPE

 #define CPVALIDITYPERIOD_UPDATE(x) \
         CPVALIDITYPERIOD.ARTICLE_NO_PACK=:x->ARTICLE_NO_PACK,\
         CPVALIDITYPERIOD.DATEFROM=:x->DATEFROM,\
         CPVALIDITYPERIOD.DATETO=:x->DATETO,\
         CPVALIDITYPERIOD.COMPACK_TYPE=:x->COMPACK_TYPE

/* SqlMacros390-Define of CPVALIDITYPERIOD ************************************/

 #define CPVALIDITYPERIOD_ZEIGER_390 \
         :ARTICLE_NO_PACK,\
         :DATEFROM,\
         :DATETO,\
         :COMPACK_TYPE

 #define CPVALIDITYPERIOD_UPDATE_390 \
         ARTICLE_NO_PACK=:ARTICLE_NO_PACK,\
         DATEFROM=:DATEFROM,\
         DATETO=:DATETO,\
         COMPACK_TYPE=:COMPACK_TYPE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of CPVALIDITYPERIOD ***************************************/

 #ifndef TRANSCLASS
 typedef struct N_CPVALIDITYPERIOD {
         long ARTICLE_NO_PACK;
         long DATEFROM;
         long DATETO;
         short COMPACK_TYPE;
        } cpvalidityperiodS;
 #else /*TRANSCLASS*/
 typedef struct N_CPVALIDITYPERIOD {
         long ARTICLE_NO_PACK;
         long DATEFROM;
         long DATETO;
         short COMPACK_TYPE;

                        bool operator==(const N_CPVALIDITYPERIOD& right) const {
                        return(
                                ARTICLE_NO_PACK == right.ARTICLE_NO_PACK &&
                                DATEFROM == right.DATEFROM &&
                                DATETO == right.DATETO &&
                                COMPACK_TYPE == right.COMPACK_TYPE
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                ARTICLE_NO_PACK = 0;
                                DATEFROM = 0;
                                DATETO = 0;
                                COMPACK_TYPE = 0;
#endif
                        }
         } cpvalidityperiodS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CPVALIDITYPERIOD **********************************/

 struct S_CPVALIDITYPERIOD {
         char ARTICLE_NO_PACK[11];
         char DATEFROM[11];
         char DATETO[11];
         char COMPACK_TYPE[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CPVALIDITYPERIOD *****************/

 struct O_CPVALIDITYPERIOD {
         char ARTICLE_NO_PACK[11];
         char DATEFROM[11];
         char DATETO[11];
         char COMPACK_TYPE[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CPVALIDITYPERIOD ****************************/

 struct C_CPVALIDITYPERIOD {
         long ARTICLE_NO_PACK;
         long DATEFROM;
         long DATETO;
         short COMPACK_TYPE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CPVALIDITYPERIOD **************************/

 struct I_CPVALIDITYPERIOD {
         short ARTICLE_NO_PACK;
         short DATEFROM;
         short DATETO;
         short COMPACK_TYPE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CPVALIDITYPERIOD ************************************/

#if defined (BUF_DESC)
 static struct buf_desc CPVALIDITYPERIOD_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc CPVALIDITYPERIOD_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of CPVALIDITYPERIOD ******************************/

 #define CPVALIDITYPERIOD_S390 \
         long ARTICLE_NO_PACK; \
         long DATEFROM; \
         long DATETO; \
         short COMPACK_TYPE; \



/* Copy-Function Struct to single Data CPVALIDITYPERIOD ***********************/

 #define CPVALIDITYPERIOD_S390_COPY_TO_SINGLE(_x_) \
         ARTICLE_NO_PACK=_x_->ARTICLE_NO_PACK;\
         DATEFROM=_x_->DATEFROM;\
         DATETO=_x_->DATETO;\
         COMPACK_TYPE=_x_->COMPACK_TYPE;\

 #define CPVALIDITYPERIOD_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLE_NO_PACK=ARTICLE_NO_PACK;\
          _x_->DATEFROM=DATEFROM;\
          _x_->DATETO=DATETO;\
          _x_->COMPACK_TYPE=COMPACK_TYPE;\



/* FunctionNumber-Define of cpValidityPeriod **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of cpValidityPeriod ******************************/


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

class CCPVALIDITYPERIOD : public ppDadeVirtual
{
        //data members
        public:
                cpvalidityperiodS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<cpvalidityperiodS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<cpvalidityperiodS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<cpvalidityperiodS>; Strip(s); cpvalidityperiodS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<cpvalidityperiodS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<cpvalidityperiodS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<cpvalidityperiodS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetArticle_no_pack() const      { return s.ARTICLE_NO_PACK; }
                long            GetDatefrom() const     { return s.DATEFROM; }
                long            GetDateto() const       { return s.DATETO; }
                short           GetCompack_type() const { return s.COMPACK_TYPE; }
                const cpvalidityperiodS& GetStruct() const { return s; }
                void            SetArticle_no_pack(long t) { s.ARTICLE_NO_PACK = t; }
                void            SetDatefrom(long t) { s.DATEFROM = t; }
                void            SetDateto(long t) { s.DATETO = t; }
                void            SetCompack_type(short t) { s.COMPACK_TYPE = t; }
                void            SetStruct(const cpvalidityperiodS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CCPVALIDITYPERIOD()  //constructor
                {
                        ::buf_default((void *)&s, CPVALIDITYPERIOD_BES, CPVALIDITYPERIOD_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CCPVALIDITYPERIOD()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, CPVALIDITYPERIOD_BES, CPVALIDITYPERIOD_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CPVALIDITYPERIOD_BES, CPVALIDITYPERIOD_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, CPVALIDITYPERIOD_BES, CPVALIDITYPERIOD_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_CPVALIDITYPERIOD& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, CPVALIDITYPERIOD_BES, CPVALIDITYPERIOD_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of CPVALIDITYPERIOD *************************************/

 #define CPVALIDITYPERIOD_CREATE(x) exec sql create table x (\
         ARTICLE_NO_PACK integer default 0 not null,\
         DATEFROM integer default 0 not null,\
         DATETO integer default 0 not null,\
         COMPACK_TYPE smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of CPVALIDITYPERIOD ***********************************/

 #define CPVALIDITYPERIOD_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_ValPeriod_1 on _X_(\
              article_no_pack ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CPVALIDITYPERIOD ***********************************/

 #define CPVALIDITYPERIOD_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_ValPeriod_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
