#ifndef __PP_POSITIONPARKING_H_
#define __PP_POSITIONPARKING_H_

/******************************************************************************/
/* v:\nordat\PositionParking **************************************************/
/******************************************************************************/

/* Length-Define of POSITIONPARKING *******************************************/

  #define L_POSITIONPARKING_BRANCHNO 6
  #define L_POSITIONPARKING_CUSTOMERNO 11
  #define L_POSITIONPARKING_ARTICLENO 11
  #define L_POSITIONPARKING_DATE 11
  #define L_POSITIONPARKING_ORDERNOORG 11
  #define L_POSITIONPARKING_ORDERQTY 11

/* Length/Count-Define of POSITIONPARKING *************************************/

  #define LS_POSITIONPARKING_BRANCHNO 5 + 1
  #define LS_POSITIONPARKING_CUSTOMERNO 10 + 1
  #define LS_POSITIONPARKING_ARTICLENO 10 + 1
  #define LS_POSITIONPARKING_DATE 10 + 1
  #define LS_POSITIONPARKING_ORDERNOORG 10 + 1
  #define LS_POSITIONPARKING_ORDERQTY 10 + 1

  #define POSITIONPARKINGBRANCHNO 0
  #define POSITIONPARKINGCUSTOMERNO 1
  #define POSITIONPARKINGARTICLENO 2
  #define POSITIONPARKINGDATE 3
  #define POSITIONPARKINGORDERNOORG 4
  #define POSITIONPARKINGORDERQTY 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define POSITIONPARKING_H
 #define POSITIONPARKING_ANZ ( sizeof(POSITIONPARKING_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of POSITIONPARKING ***********************************************/

 #define POSITIONPARKING_LISTE \
         POSITIONPARKING.BRANCHNO,\
         POSITIONPARKING.CUSTOMERNO,\
         POSITIONPARKING.ARTICLENO,\
         POSITIONPARKING.DATE,\
         POSITIONPARKING.ORDERNOORG,\
         POSITIONPARKING.ORDERQTY

 #define POSITIONPARKING_LISTE_390 \
         BRANCHNO,\
         CUSTOMERNO,\
         ARTICLENO,\
         DATE,\
         ORDERNOORG,\
         ORDERQTY

 #define POSITIONPARKING_PLISTE \
         "POSITIONPARKING.BRANCHNO,"\
         "POSITIONPARKING.CUSTOMERNO,"\
         "POSITIONPARKING.ARTICLENO,"\
         "POSITIONPARKING.DATE,"\
         "POSITIONPARKING.ORDERNOORG,"\
         "POSITIONPARKING.ORDERQTY"

 #define POSITIONPARKING_PELISTE \
         "BRANCHNO,"\
         "CUSTOMERNO,"\
         "ARTICLENO,"\
         "DATE,"\
         "ORDERNOORG,"\
         "ORDERQTY"

 #define POSITIONPARKING_UPDLISTE \
         "BRANCHNO=?,"\
         "CUSTOMERNO=?,"\
         "ARTICLENO=?,"\
         "DATE=?,"\
         "ORDERNOORG=?,"\
         "ORDERQTY=?"

/* SqlMacros-Define of POSITIONPARKING ****************************************/

 #define POSITIONPARKING_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->ARTICLENO,\
         :x->DATE,\
         :x->ORDERNOORG,\
         :x->ORDERQTY

 #define POSITIONPARKING_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->ARTICLENO,\
         :x->DATE,\
         :x->ORDERNOORG,\
         :x->ORDERQTY

 #define POSITIONPARKING_UPDATE(x) \
         POSITIONPARKING.BRANCHNO=:x->BRANCHNO,\
         POSITIONPARKING.CUSTOMERNO=:x->CUSTOMERNO,\
         POSITIONPARKING.ARTICLENO=:x->ARTICLENO,\
         POSITIONPARKING.DATE=:x->DATE,\
         POSITIONPARKING.ORDERNOORG=:x->ORDERNOORG,\
         POSITIONPARKING.ORDERQTY=:x->ORDERQTY

/* SqlMacros390-Define of POSITIONPARKING *************************************/

 #define POSITIONPARKING_ZEIGER_390 \
         :BRANCHNO,\
         :CUSTOMERNO,\
         :ARTICLENO,\
         :DATE,\
         :ORDERNOORG,\
         :ORDERQTY

 #define POSITIONPARKING_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         CUSTOMERNO=:CUSTOMERNO,\
         ARTICLENO=:ARTICLENO,\
         DATE=:DATE,\
         ORDERNOORG=:ORDERNOORG,\
         ORDERQTY=:ORDERQTY

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of POSITIONPARKING ****************************************/

 #ifndef TRANSCLASS
 typedef struct N_POSITIONPARKING {
         short BRANCHNO;
         long CUSTOMERNO;
         long ARTICLENO;
         long DATE;
         long ORDERNOORG;
         long ORDERQTY;
        } positionparkingS;
 #else /*TRANSCLASS*/
 typedef struct N_POSITIONPARKING {
         short BRANCHNO;
         long CUSTOMERNO;
         long ARTICLENO;
         long DATE;
         long ORDERNOORG;
         long ORDERQTY;

                        bool operator==(const N_POSITIONPARKING& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                CUSTOMERNO == right.CUSTOMERNO &&
                                ARTICLENO == right.ARTICLENO &&
                                DATE == right.DATE &&
                                ORDERNOORG == right.ORDERNOORG &&
                                ORDERQTY == right.ORDERQTY
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                CUSTOMERNO = 0;
                                ARTICLENO = 0;
                                DATE = 0;
                                ORDERNOORG = 0;
                                ORDERQTY = 0;
#endif
                        }
         } positionparkingS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of POSITIONPARKING ***********************************/

 struct S_POSITIONPARKING {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char ARTICLENO[11];
         char DATE[11];
         char ORDERNOORG[11];
         char ORDERQTY[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of POSITIONPARKING ******************/

 struct O_POSITIONPARKING {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char ARTICLENO[11];
         char DATE[11];
         char ORDERNOORG[11];
         char ORDERQTY[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of POSITIONPARKING *****************************/

 struct C_POSITIONPARKING {
         short BRANCHNO;
         long CUSTOMERNO;
         long ARTICLENO;
         long DATE;
         long ORDERNOORG;
         long ORDERQTY;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of POSITIONPARKING ***************************/

 struct I_POSITIONPARKING {
         short BRANCHNO;
         short CUSTOMERNO;
         short ARTICLENO;
         short DATE;
         short ORDERNOORG;
         short ORDERQTY;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of POSITIONPARKING *************************************/

#if defined (BUF_DESC)
 static struct buf_desc POSITIONPARKING_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc POSITIONPARKING_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of POSITIONPARKING *******************************/

 #define POSITIONPARKING_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long ARTICLENO; \
         long DATE; \
         long ORDERNOORG; \
         long ORDERQTY; \



/* Copy-Function Struct to single Data POSITIONPARKING ************************/

 #define POSITIONPARKING_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         ARTICLENO=_x_->ARTICLENO;\
         DATE=_x_->DATE;\
         ORDERNOORG=_x_->ORDERNOORG;\
         ORDERQTY=_x_->ORDERQTY;\

 #define POSITIONPARKING_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->ARTICLENO=ARTICLENO;\
          _x_->DATE=DATE;\
          _x_->ORDERNOORG=ORDERNOORG;\
          _x_->ORDERQTY=ORDERQTY;\



/* FunctionNumber-Define of PositionParking ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of PositionParking *******************************/


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

class CPOSITIONPARKING : public ppDadeVirtual
{
        //data members
        public:
                positionparkingS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<positionparkingS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<positionparkingS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<positionparkingS>; Strip(s); positionparkingS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<positionparkingS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<positionparkingS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<positionparkingS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                long            GetCustomerno() const   { return s.CUSTOMERNO; }
                long            GetArticleno() const    { return s.ARTICLENO; }
                long            GetDate() const { return s.DATE; }
                long            GetOrdernoorg() const   { return s.ORDERNOORG; }
                long            GetOrderqty() const     { return s.ORDERQTY; }
                const positionparkingS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetCustomerno(long t) { s.CUSTOMERNO = t; }
                void            SetArticleno(long t) { s.ARTICLENO = t; }
                void            SetDate(long t) { s.DATE = t; }
                void            SetOrdernoorg(long t) { s.ORDERNOORG = t; }
                void            SetOrderqty(long t) { s.ORDERQTY = t; }
                void            SetStruct(const positionparkingS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CPOSITIONPARKING()  //constructor
                {
                        ::buf_default((void *)&s, POSITIONPARKING_BES, POSITIONPARKING_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CPOSITIONPARKING()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, POSITIONPARKING_BES, POSITIONPARKING_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, POSITIONPARKING_BES, POSITIONPARKING_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, POSITIONPARKING_BES, POSITIONPARKING_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_POSITIONPARKING& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, POSITIONPARKING_BES, POSITIONPARKING_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of POSITIONPARKING **************************************/

 #define POSITIONPARKING_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         ARTICLENO integer default 0 not null,\
         DATE integer default 0 not null,\
         ORDERNOORG integer default 0 not null,\
         ORDERQTY integer default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of POSITIONPARKING ************************************/

 #define POSITIONPARKING_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_PosPark_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              ArticleNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of POSITIONPARKING ************************************/

 #define POSITIONPARKING_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_PosPark_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
