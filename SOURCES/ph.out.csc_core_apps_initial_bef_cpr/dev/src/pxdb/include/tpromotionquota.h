#ifndef __PP_PROMOTIONQUOTA_H_
#define __PP_PROMOTIONQUOTA_H_

/******************************************************************************/
/* u:\PromotionQuota **********************************************************/
/******************************************************************************/

/* Length-Define of PROMOTIONQUOTA ********************************************/

  #define L_PROMOTIONQUOTA_BRANCHNO 6
  #define L_PROMOTIONQUOTA_PROMOTION_NO 6
  #define L_PROMOTIONQUOTA_BRANCHQUOTAQTY 11
  #define L_PROMOTIONQUOTA_CUSTOMERQUOTAQTY 11
  #define L_PROMOTIONQUOTA_SOLDQTYBRANCH 11
  #define L_PROMOTIONQUOTA_UPD_FLAG 1
  #define L_PROMOTIONQUOTA_ARTICLENO 11
  #define L_PROMOTIONQUOTA_CUSTOMERMINQTY 11

/* Length/Count-Define of PROMOTIONQUOTA **************************************/

  #define LS_PROMOTIONQUOTA_BRANCHNO 5 + 1
  #define LS_PROMOTIONQUOTA_PROMOTION_NO 5 + 1
  #define LS_PROMOTIONQUOTA_BRANCHQUOTAQTY 10 + 1
  #define LS_PROMOTIONQUOTA_CUSTOMERQUOTAQTY 10 + 1
  #define LS_PROMOTIONQUOTA_SOLDQTYBRANCH 10 + 1
  #define LS_PROMOTIONQUOTA_UPD_FLAG 1 + 1
  #define LS_PROMOTIONQUOTA_ARTICLENO 10 + 1
  #define LS_PROMOTIONQUOTA_CUSTOMERMINQTY 10 + 1

  #define PROMOTIONQUOTABRANCHNO 0
  #define PROMOTIONQUOTAPROMOTION_NO 1
  #define PROMOTIONQUOTABRANCHQUOTAQTY 2
  #define PROMOTIONQUOTACUSTOMERQUOTAQTY 3
  #define PROMOTIONQUOTASOLDQTYBRANCH 4
  #define PROMOTIONQUOTAUPD_FLAG 5
  #define PROMOTIONQUOTAARTICLENO 6
  #define PROMOTIONQUOTACUSTOMERMINQTY 7

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define PROMOTIONQUOTA_H
 #define PROMOTIONQUOTA_ANZ ( sizeof(PROMOTIONQUOTA_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of PROMOTIONQUOTA ************************************************/

 #define PROMOTIONQUOTA_LISTE \
         PROMOTIONQUOTA.BRANCHNO,\
         PROMOTIONQUOTA.PROMOTION_NO,\
         PROMOTIONQUOTA.BRANCHQUOTAQTY,\
         PROMOTIONQUOTA.CUSTOMERQUOTAQTY,\
         PROMOTIONQUOTA.SOLDQTYBRANCH,\
         PROMOTIONQUOTA.UPD_FLAG,\
         PROMOTIONQUOTA.ARTICLENO,\
         PROMOTIONQUOTA.CUSTOMERMINQTY

 #define PROMOTIONQUOTA_LISTE_390 \
         BRANCHNO,\
         PROMOTION_NO,\
         BRANCHQUOTAQTY,\
         CUSTOMERQUOTAQTY,\
         SOLDQTYBRANCH,\
         UPD_FLAG,\
         ARTICLENO,\
         CUSTOMERMINQTY

 #define PROMOTIONQUOTA_PLISTE \
         "PROMOTIONQUOTA.BRANCHNO,"\
         "PROMOTIONQUOTA.PROMOTION_NO,"\
         "PROMOTIONQUOTA.BRANCHQUOTAQTY,"\
         "PROMOTIONQUOTA.CUSTOMERQUOTAQTY,"\
         "PROMOTIONQUOTA.SOLDQTYBRANCH,"\
         "PROMOTIONQUOTA.UPD_FLAG,"\
         "PROMOTIONQUOTA.ARTICLENO,"\
         "PROMOTIONQUOTA.CUSTOMERMINQTY"

 #define PROMOTIONQUOTA_PELISTE \
         "BRANCHNO,"\
         "PROMOTION_NO,"\
         "BRANCHQUOTAQTY,"\
         "CUSTOMERQUOTAQTY,"\
         "SOLDQTYBRANCH,"\
         "UPD_FLAG,"\
         "ARTICLENO,"\
         "CUSTOMERMINQTY"

 #define PROMOTIONQUOTA_UPDLISTE \
         "BRANCHNO=?,"\
         "PROMOTION_NO=?,"\
         "BRANCHQUOTAQTY=?,"\
         "CUSTOMERQUOTAQTY=?,"\
         "SOLDQTYBRANCH=?,"\
         "UPD_FLAG=?,"\
         "ARTICLENO=?,"\
         "CUSTOMERMINQTY=?"

/* SqlMacros-Define of PROMOTIONQUOTA *****************************************/

 #define PROMOTIONQUOTA_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->PROMOTION_NO,\
         :x->BRANCHQUOTAQTY,\
         :x->CUSTOMERQUOTAQTY,\
         :x->SOLDQTYBRANCH,\
         :x->UPD_FLAG,\
         :x->ARTICLENO,\
         :x->CUSTOMERMINQTY

 #define PROMOTIONQUOTA_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->PROMOTION_NO,\
         :x->BRANCHQUOTAQTY,\
         :x->CUSTOMERQUOTAQTY,\
         :x->SOLDQTYBRANCH,\
         :x->UPD_FLAG,\
         :x->ARTICLENO,\
         :x->CUSTOMERMINQTY

 #define PROMOTIONQUOTA_UPDATE(x) \
         PROMOTIONQUOTA.BRANCHNO=:x->BRANCHNO,\
         PROMOTIONQUOTA.PROMOTION_NO=:x->PROMOTION_NO,\
         PROMOTIONQUOTA.BRANCHQUOTAQTY=:x->BRANCHQUOTAQTY,\
         PROMOTIONQUOTA.CUSTOMERQUOTAQTY=:x->CUSTOMERQUOTAQTY,\
         PROMOTIONQUOTA.SOLDQTYBRANCH=:x->SOLDQTYBRANCH,\
         PROMOTIONQUOTA.UPD_FLAG=:x->UPD_FLAG,\
         PROMOTIONQUOTA.ARTICLENO=:x->ARTICLENO,\
         PROMOTIONQUOTA.CUSTOMERMINQTY=:x->CUSTOMERMINQTY

/* SqlMacros390-Define of PROMOTIONQUOTA **************************************/

 #define PROMOTIONQUOTA_ZEIGER_390 \
         :BRANCHNO,\
         :PROMOTION_NO,\
         :BRANCHQUOTAQTY,\
         :CUSTOMERQUOTAQTY,\
         :SOLDQTYBRANCH,\
         :UPD_FLAG,\
         :ARTICLENO,\
         :CUSTOMERMINQTY

 #define PROMOTIONQUOTA_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         PROMOTION_NO=:PROMOTION_NO,\
         BRANCHQUOTAQTY=:BRANCHQUOTAQTY,\
         CUSTOMERQUOTAQTY=:CUSTOMERQUOTAQTY,\
         SOLDQTYBRANCH=:SOLDQTYBRANCH,\
         UPD_FLAG=:UPD_FLAG,\
         ARTICLENO=:ARTICLENO,\
         CUSTOMERMINQTY=:CUSTOMERMINQTY

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of PROMOTIONQUOTA *****************************************/

 #ifndef TRANSCLASS
 typedef struct N_PROMOTIONQUOTA {
         short BRANCHNO;
         short PROMOTION_NO;
         long BRANCHQUOTAQTY;
         long CUSTOMERQUOTAQTY;
         long SOLDQTYBRANCH;
         char UPD_FLAG[2];
         long ARTICLENO;
         long CUSTOMERMINQTY;
        } promotionquotaS;
 #else /*TRANSCLASS*/
 typedef struct N_PROMOTIONQUOTA {
         short BRANCHNO;
         short PROMOTION_NO;
         long BRANCHQUOTAQTY;
         long CUSTOMERQUOTAQTY;
         long SOLDQTYBRANCH;
         char UPD_FLAG[2];
         long ARTICLENO;
         long CUSTOMERMINQTY;

                        bool operator==(const N_PROMOTIONQUOTA& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                PROMOTION_NO == right.PROMOTION_NO &&
                                BRANCHQUOTAQTY == right.BRANCHQUOTAQTY &&
                                CUSTOMERQUOTAQTY == right.CUSTOMERQUOTAQTY &&
                                SOLDQTYBRANCH == right.SOLDQTYBRANCH &&
                                !strcmp(UPD_FLAG, right.UPD_FLAG) &&
                                ARTICLENO == right.ARTICLENO &&
                                CUSTOMERMINQTY == right.CUSTOMERMINQTY
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                PROMOTION_NO = 0;
                                BRANCHQUOTAQTY = 0;
                                CUSTOMERQUOTAQTY = 0;
                                SOLDQTYBRANCH = 0;
                                strcpy(UPD_FLAG, " " );
                                ARTICLENO = 0;
                                CUSTOMERMINQTY = 0;
#endif
                        }
         } promotionquotaS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of PROMOTIONQUOTA ************************************/

 struct S_PROMOTIONQUOTA {
         char BRANCHNO[7];
         char PROMOTION_NO[7];
         char BRANCHQUOTAQTY[11];
         char CUSTOMERQUOTAQTY[11];
         char SOLDQTYBRANCH[11];
         char UPD_FLAG[1 + 1];
         char ARTICLENO[11];
         char CUSTOMERMINQTY[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of PROMOTIONQUOTA *******************/

 struct O_PROMOTIONQUOTA {
         char BRANCHNO[7];
         char PROMOTION_NO[7];
         char BRANCHQUOTAQTY[11];
         char CUSTOMERQUOTAQTY[11];
         char SOLDQTYBRANCH[11];
         char UPD_FLAG[1];
         char ARTICLENO[11];
         char CUSTOMERMINQTY[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of PROMOTIONQUOTA ******************************/

 struct C_PROMOTIONQUOTA {
         short BRANCHNO;
         short PROMOTION_NO;
         long BRANCHQUOTAQTY;
         long CUSTOMERQUOTAQTY;
         long SOLDQTYBRANCH;
         char UPD_FLAG;
         long ARTICLENO;
         long CUSTOMERMINQTY;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of PROMOTIONQUOTA ****************************/

 struct I_PROMOTIONQUOTA {
         short BRANCHNO;
         short PROMOTION_NO;
         short BRANCHQUOTAQTY;
         short CUSTOMERQUOTAQTY;
         short SOLDQTYBRANCH;
         short UPD_FLAG;
         short ARTICLENO;
         short CUSTOMERMINQTY;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of PROMOTIONQUOTA **************************************/

#if defined (BUF_DESC)
 static struct buf_desc PROMOTIONQUOTA_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc PROMOTIONQUOTA_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of PROMOTIONQUOTA ********************************/

 #define PROMOTIONQUOTA_S390 \
         short BRANCHNO; \
         short PROMOTION_NO; \
         long BRANCHQUOTAQTY; \
         long CUSTOMERQUOTAQTY; \
         long SOLDQTYBRANCH; \
         char UPD_FLAG; \
         long ARTICLENO; \
         long CUSTOMERMINQTY; \



/* Copy-Function Struct to single Data PROMOTIONQUOTA *************************/

 #define PROMOTIONQUOTA_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         PROMOTION_NO=_x_->PROMOTION_NO;\
         BRANCHQUOTAQTY=_x_->BRANCHQUOTAQTY;\
         CUSTOMERQUOTAQTY=_x_->CUSTOMERQUOTAQTY;\
         SOLDQTYBRANCH=_x_->SOLDQTYBRANCH;\
         UPD_FLAG=_x_->UPD_FLAG;\
         ARTICLENO=_x_->ARTICLENO;\
         CUSTOMERMINQTY=_x_->CUSTOMERMINQTY;\

 #define PROMOTIONQUOTA_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->PROMOTION_NO=PROMOTION_NO;\
          _x_->BRANCHQUOTAQTY=BRANCHQUOTAQTY;\
          _x_->CUSTOMERQUOTAQTY=CUSTOMERQUOTAQTY;\
          _x_->SOLDQTYBRANCH=SOLDQTYBRANCH;\
          _x_->UPD_FLAG=UPD_FLAG;\
          _x_->ARTICLENO=ARTICLENO;\
          _x_->CUSTOMERMINQTY=CUSTOMERMINQTY;\



/* FunctionNumber-Define of PromotionQuota ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of PromotionQuota ********************************/


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

class CPROMOTIONQUOTA : public ppDadeVirtual
{
        //data members
        public:
                promotionquotaS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<promotionquotaS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<promotionquotaS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<promotionquotaS>; Strip(s); promotionquotaS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<promotionquotaS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<promotionquotaS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<promotionquotaS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                short           GetPromotion_no() const { return s.PROMOTION_NO; }
                long            GetBranchquotaqty() const       { return s.BRANCHQUOTAQTY; }
                long            GetCustomerquotaqty() const     { return s.CUSTOMERQUOTAQTY; }
                long            GetSoldqtybranch() const        { return s.SOLDQTYBRANCH; }
                char            GetUpd_flag() const     { return s.UPD_FLAG[0]; }
                long            GetArticleno() const    { return s.ARTICLENO; }
                long            GetCustomerminqty() const       { return s.CUSTOMERMINQTY; }
                const promotionquotaS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetPromotion_no(short t) { s.PROMOTION_NO = t; }
                void            SetBranchquotaqty(long t) { s.BRANCHQUOTAQTY = t; }
                void            SetCustomerquotaqty(long t) { s.CUSTOMERQUOTAQTY = t; }
                void            SetSoldqtybranch(long t) { s.SOLDQTYBRANCH = t; }
                void            SetUpd_flag(char t) { s.UPD_FLAG[0] = t; s.UPD_FLAG[1] = '\0';}
                void            SetArticleno(long t) { s.ARTICLENO = t; }
                void            SetCustomerminqty(long t) { s.CUSTOMERMINQTY = t; }
                void            SetStruct(const promotionquotaS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CPROMOTIONQUOTA()  //constructor
                {
                        ::buf_default((void *)&s, PROMOTIONQUOTA_BES, PROMOTIONQUOTA_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CPROMOTIONQUOTA()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, PROMOTIONQUOTA_BES, PROMOTIONQUOTA_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, PROMOTIONQUOTA_BES, PROMOTIONQUOTA_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, PROMOTIONQUOTA_BES, PROMOTIONQUOTA_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_PROMOTIONQUOTA& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, PROMOTIONQUOTA_BES, PROMOTIONQUOTA_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of PROMOTIONQUOTA ***************************************/

 #define PROMOTIONQUOTA_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         PROMOTION_NO smallint default 0 not null,\
         BRANCHQUOTAQTY integer default 0 not null,\
         CUSTOMERQUOTAQTY integer default 0 not null,\
         SOLDQTYBRANCH integer default 0 not null,\
         UPD_FLAG char(1) default " " not null,\
         ARTICLENO integer default 0 not null,\
         CUSTOMERMINQTY integer default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of PROMOTIONQUOTA *************************************/

 #define PROMOTIONQUOTA_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_PromoQuota_1 on _X_(\
              BranchNo,\
              promotion_no,\
              ArticleNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of PROMOTIONQUOTA *************************************/

 #define PROMOTIONQUOTA_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_PromoQuota_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
