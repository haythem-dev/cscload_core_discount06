#ifndef __PP_PROMOTIONQUOTACST_H_
#define __PP_PROMOTIONQUOTACST_H_

/******************************************************************************/
/* u:\PromotionQuotaCst *******************************************************/
/******************************************************************************/

/* Length-Define of PROMOTIONQUOTACST *****************************************/

  #define L_PROMOTIONQUOTACST_BRANCHNO 6
  #define L_PROMOTIONQUOTACST_PROMOTION_NO 6
  #define L_PROMOTIONQUOTACST_CUSTOMERQUOTAQTY 11
  #define L_PROMOTIONQUOTACST_SOLDQTYCST 11
  #define L_PROMOTIONQUOTACST_CUSTOMERNO 11
  #define L_PROMOTIONQUOTACST_ARTICLENO 11

/* Length/Count-Define of PROMOTIONQUOTACST ***********************************/

  #define LS_PROMOTIONQUOTACST_BRANCHNO 5 + 1
  #define LS_PROMOTIONQUOTACST_PROMOTION_NO 5 + 1
  #define LS_PROMOTIONQUOTACST_CUSTOMERQUOTAQTY 10 + 1
  #define LS_PROMOTIONQUOTACST_SOLDQTYCST 10 + 1
  #define LS_PROMOTIONQUOTACST_CUSTOMERNO 10 + 1
  #define LS_PROMOTIONQUOTACST_ARTICLENO 10 + 1

  #define PROMOTIONQUOTACSTBRANCHNO 0
  #define PROMOTIONQUOTACSTPROMOTION_NO 1
  #define PROMOTIONQUOTACSTCUSTOMERQUOTAQTY 2
  #define PROMOTIONQUOTACSTSOLDQTYCST 3
  #define PROMOTIONQUOTACSTCUSTOMERNO 4
  #define PROMOTIONQUOTACSTARTICLENO 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define PROMOTIONQUOTACST_H
 #define PROMOTIONQUOTACST_ANZ ( sizeof(PROMOTIONQUOTACST_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of PROMOTIONQUOTACST *********************************************/

 #define PROMOTIONQUOTACST_LISTE \
         PROMOTIONQUOTACST.BRANCHNO,\
         PROMOTIONQUOTACST.PROMOTION_NO,\
         PROMOTIONQUOTACST.CUSTOMERQUOTAQTY,\
         PROMOTIONQUOTACST.SOLDQTYCST,\
         PROMOTIONQUOTACST.CUSTOMERNO,\
         PROMOTIONQUOTACST.ARTICLENO

 #define PROMOTIONQUOTACST_LISTE_390 \
         BRANCHNO,\
         PROMOTION_NO,\
         CUSTOMERQUOTAQTY,\
         SOLDQTYCST,\
         CUSTOMERNO,\
         ARTICLENO

 #define PROMOTIONQUOTACST_PLISTE \
         "PROMOTIONQUOTACST.BRANCHNO,"\
         "PROMOTIONQUOTACST.PROMOTION_NO,"\
         "PROMOTIONQUOTACST.CUSTOMERQUOTAQTY,"\
         "PROMOTIONQUOTACST.SOLDQTYCST,"\
         "PROMOTIONQUOTACST.CUSTOMERNO,"\
         "PROMOTIONQUOTACST.ARTICLENO"

 #define PROMOTIONQUOTACST_PELISTE \
         "BRANCHNO,"\
         "PROMOTION_NO,"\
         "CUSTOMERQUOTAQTY,"\
         "SOLDQTYCST,"\
         "CUSTOMERNO,"\
         "ARTICLENO"

 #define PROMOTIONQUOTACST_UPDLISTE \
         "BRANCHNO=?,"\
         "PROMOTION_NO=?,"\
         "CUSTOMERQUOTAQTY=?,"\
         "SOLDQTYCST=?,"\
         "CUSTOMERNO=?,"\
         "ARTICLENO=?"

/* SqlMacros-Define of PROMOTIONQUOTACST **************************************/

 #define PROMOTIONQUOTACST_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->PROMOTION_NO,\
         :x->CUSTOMERQUOTAQTY,\
         :x->SOLDQTYCST,\
         :x->CUSTOMERNO,\
         :x->ARTICLENO

 #define PROMOTIONQUOTACST_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->PROMOTION_NO,\
         :x->CUSTOMERQUOTAQTY,\
         :x->SOLDQTYCST,\
         :x->CUSTOMERNO,\
         :x->ARTICLENO

 #define PROMOTIONQUOTACST_UPDATE(x) \
         PROMOTIONQUOTACST.BRANCHNO=:x->BRANCHNO,\
         PROMOTIONQUOTACST.PROMOTION_NO=:x->PROMOTION_NO,\
         PROMOTIONQUOTACST.CUSTOMERQUOTAQTY=:x->CUSTOMERQUOTAQTY,\
         PROMOTIONQUOTACST.SOLDQTYCST=:x->SOLDQTYCST,\
         PROMOTIONQUOTACST.CUSTOMERNO=:x->CUSTOMERNO,\
         PROMOTIONQUOTACST.ARTICLENO=:x->ARTICLENO

/* SqlMacros390-Define of PROMOTIONQUOTACST ***********************************/

 #define PROMOTIONQUOTACST_ZEIGER_390 \
         :BRANCHNO,\
         :PROMOTION_NO,\
         :CUSTOMERQUOTAQTY,\
         :SOLDQTYCST,\
         :CUSTOMERNO,\
         :ARTICLENO

 #define PROMOTIONQUOTACST_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         PROMOTION_NO=:PROMOTION_NO,\
         CUSTOMERQUOTAQTY=:CUSTOMERQUOTAQTY,\
         SOLDQTYCST=:SOLDQTYCST,\
         CUSTOMERNO=:CUSTOMERNO,\
         ARTICLENO=:ARTICLENO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of PROMOTIONQUOTACST **************************************/

 #ifndef TRANSCLASS
 typedef struct N_PROMOTIONQUOTACST {
         short BRANCHNO;
         short PROMOTION_NO;
         long CUSTOMERQUOTAQTY;
         long SOLDQTYCST;
         long CUSTOMERNO;
         long ARTICLENO;
        } promotionquotacstS;
 #else /*TRANSCLASS*/
 typedef struct N_PROMOTIONQUOTACST {
         short BRANCHNO;
         short PROMOTION_NO;
         long CUSTOMERQUOTAQTY;
         long SOLDQTYCST;
         long CUSTOMERNO;
         long ARTICLENO;

                        bool operator==(const N_PROMOTIONQUOTACST& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                PROMOTION_NO == right.PROMOTION_NO &&
                                CUSTOMERQUOTAQTY == right.CUSTOMERQUOTAQTY &&
                                SOLDQTYCST == right.SOLDQTYCST &&
                                CUSTOMERNO == right.CUSTOMERNO &&
                                ARTICLENO == right.ARTICLENO
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                PROMOTION_NO = 0;
                                CUSTOMERQUOTAQTY = 0;
                                SOLDQTYCST = 0;
                                CUSTOMERNO = 0;
                                ARTICLENO = 0;
#endif
                        }
         } promotionquotacstS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of PROMOTIONQUOTACST *********************************/

 struct S_PROMOTIONQUOTACST {
         char BRANCHNO[7];
         char PROMOTION_NO[7];
         char CUSTOMERQUOTAQTY[11];
         char SOLDQTYCST[11];
         char CUSTOMERNO[11];
         char ARTICLENO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of PROMOTIONQUOTACST ****************/

 struct O_PROMOTIONQUOTACST {
         char BRANCHNO[7];
         char PROMOTION_NO[7];
         char CUSTOMERQUOTAQTY[11];
         char SOLDQTYCST[11];
         char CUSTOMERNO[11];
         char ARTICLENO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of PROMOTIONQUOTACST ***************************/

 struct C_PROMOTIONQUOTACST {
         short BRANCHNO;
         short PROMOTION_NO;
         long CUSTOMERQUOTAQTY;
         long SOLDQTYCST;
         long CUSTOMERNO;
         long ARTICLENO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of PROMOTIONQUOTACST *************************/

 struct I_PROMOTIONQUOTACST {
         short BRANCHNO;
         short PROMOTION_NO;
         short CUSTOMERQUOTAQTY;
         short SOLDQTYCST;
         short CUSTOMERNO;
         short ARTICLENO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of PROMOTIONQUOTACST ***********************************/

#if defined (BUF_DESC)
 static struct buf_desc PROMOTIONQUOTACST_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc PROMOTIONQUOTACST_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of PROMOTIONQUOTACST *****************************/

 #define PROMOTIONQUOTACST_S390 \
         short BRANCHNO; \
         short PROMOTION_NO; \
         long CUSTOMERQUOTAQTY; \
         long SOLDQTYCST; \
         long CUSTOMERNO; \
         long ARTICLENO; \



/* Copy-Function Struct to single Data PROMOTIONQUOTACST **********************/

 #define PROMOTIONQUOTACST_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         PROMOTION_NO=_x_->PROMOTION_NO;\
         CUSTOMERQUOTAQTY=_x_->CUSTOMERQUOTAQTY;\
         SOLDQTYCST=_x_->SOLDQTYCST;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         ARTICLENO=_x_->ARTICLENO;\

 #define PROMOTIONQUOTACST_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->PROMOTION_NO=PROMOTION_NO;\
          _x_->CUSTOMERQUOTAQTY=CUSTOMERQUOTAQTY;\
          _x_->SOLDQTYCST=SOLDQTYCST;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->ARTICLENO=ARTICLENO;\



/* FunctionNumber-Define of PromotionQuotaCst *********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of PromotionQuotaCst *****************************/


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

class CPROMOTIONQUOTACST : public ppDadeVirtual
{
        //data members
        public:
                promotionquotacstS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<promotionquotacstS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<promotionquotacstS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<promotionquotacstS>; Strip(s); promotionquotacstS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<promotionquotacstS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<promotionquotacstS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<promotionquotacstS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                short           GetPromotion_no() const { return s.PROMOTION_NO; }
                long            GetCustomerquotaqty() const     { return s.CUSTOMERQUOTAQTY; }
                long            GetSoldqtycst() const   { return s.SOLDQTYCST; }
                long            GetCustomerno() const   { return s.CUSTOMERNO; }
                long            GetArticleno() const    { return s.ARTICLENO; }
                const promotionquotacstS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetPromotion_no(short t) { s.PROMOTION_NO = t; }
                void            SetCustomerquotaqty(long t) { s.CUSTOMERQUOTAQTY = t; }
                void            SetSoldqtycst(long t) { s.SOLDQTYCST = t; }
                void            SetCustomerno(long t) { s.CUSTOMERNO = t; }
                void            SetArticleno(long t) { s.ARTICLENO = t; }
                void            SetStruct(const promotionquotacstS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CPROMOTIONQUOTACST()  //constructor
                {
                        ::buf_default((void *)&s, PROMOTIONQUOTACST_BES, PROMOTIONQUOTACST_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CPROMOTIONQUOTACST()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, PROMOTIONQUOTACST_BES, PROMOTIONQUOTACST_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, PROMOTIONQUOTACST_BES, PROMOTIONQUOTACST_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, PROMOTIONQUOTACST_BES, PROMOTIONQUOTACST_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_PROMOTIONQUOTACST& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, PROMOTIONQUOTACST_BES, PROMOTIONQUOTACST_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of PROMOTIONQUOTACST ************************************/

 #define PROMOTIONQUOTACST_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         PROMOTION_NO smallint default 0 not null,\
         CUSTOMERQUOTAQTY integer default 0 not null,\
         SOLDQTYCST integer default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         ARTICLENO integer default 0 not null) in ksc extent size 7844 next size 788 lock mode row;



/* CreateIndexStatement of PROMOTIONQUOTACST **********************************/

 #define PROMOTIONQUOTACST_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_PromoQuotaCst_1 on _X_(\
              BranchNo,\
              promotion_no,\
              CustomerNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of PROMOTIONQUOTACST **********************************/

 #define PROMOTIONQUOTACST_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_PromoQuotaCst_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
