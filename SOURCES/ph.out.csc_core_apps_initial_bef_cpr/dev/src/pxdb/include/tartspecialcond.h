#ifndef __PP_ARTSPECIALCOND_H_
#define __PP_ARTSPECIALCOND_H_

/******************************************************************************/
/* u:\ArtSpecialCond **********************************************************/
/******************************************************************************/

/* Length-Define of ARTSPECIALCOND ********************************************/

  #define L_ARTSPECIALCOND_ARTICLENO 11
  #define L_ARTSPECIALCOND_INVOICE_REBATE_PCT 5
  #define N_ARTSPECIALCOND_INVOICE_REBATE_PCT 2
  #define L_ARTSPECIALCOND_REBATE_IN_KIND_PCT 5
  #define N_ARTSPECIALCOND_REBATE_IN_KIND_PCT 2
  #define L_ARTSPECIALCOND_ANNUAL_INV_REB_PCT 5
  #define N_ARTSPECIALCOND_ANNUAL_INV_REB_PCT 2
  #define L_ARTSPECIALCOND_ANNUAL_REB_I_K_PCT 5
  #define N_ARTSPECIALCOND_ANNUAL_REB_I_K_PCT 2
  #define L_ARTSPECIALCOND_CUST_REB_RED_PCT 5
  #define N_ARTSPECIALCOND_CUST_REB_RED_PCT 2
  #define L_ARTSPECIALCOND_HI_REIMBURSEMENT 9
  #define N_ARTSPECIALCOND_HI_REIMBURSEMENT 2
  #define L_ARTSPECIALCOND_SUPPL_HI_REIMB 9
  #define N_ARTSPECIALCOND_SUPPL_HI_REIMB 2
  #define L_ARTSPECIALCOND_SUPPL_FS_REIMB 9
  #define N_ARTSPECIALCOND_SUPPL_FS_REIMB 2
  #define L_ARTSPECIALCOND_SUPPL_DISCOUNT_PCT 5
  #define N_ARTSPECIALCOND_SUPPL_DISCOUNT_PCT 2

/* Length/Count-Define of ARTSPECIALCOND **************************************/

  #define LS_ARTSPECIALCOND_ARTICLENO 10 + 1
  #define LS_ARTSPECIALCOND_INVOICE_REBATE_PCT 5 + 2
  #define LS_ARTSPECIALCOND_REBATE_IN_KIND_PCT 5 + 2
  #define LS_ARTSPECIALCOND_ANNUAL_INV_REB_PCT 5 + 2
  #define LS_ARTSPECIALCOND_ANNUAL_REB_I_K_PCT 5 + 2
  #define LS_ARTSPECIALCOND_CUST_REB_RED_PCT 5 + 2
  #define LS_ARTSPECIALCOND_HI_REIMBURSEMENT 9 + 2
  #define LS_ARTSPECIALCOND_SUPPL_HI_REIMB 9 + 2
  #define LS_ARTSPECIALCOND_SUPPL_FS_REIMB 9 + 2
  #define LS_ARTSPECIALCOND_SUPPL_DISCOUNT_PCT 5 + 2

  #define ARTSPECIALCONDARTICLENO 0
  #define ARTSPECIALCONDINVOICE_REBATE_PCT 1
  #define ARTSPECIALCONDREBATE_IN_KIND_PCT 2
  #define ARTSPECIALCONDANNUAL_INV_REB_PCT 3
  #define ARTSPECIALCONDANNUAL_REB_I_K_PCT 4
  #define ARTSPECIALCONDCUST_REB_RED_PCT 5
  #define ARTSPECIALCONDHI_REIMBURSEMENT 6
  #define ARTSPECIALCONDSUPPL_HI_REIMB 7
  #define ARTSPECIALCONDSUPPL_FS_REIMB 8
  #define ARTSPECIALCONDSUPPL_DISCOUNT_PCT 9

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTSPECIALCOND_H
 #define ARTSPECIALCOND_ANZ ( sizeof(ARTSPECIALCOND_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTSPECIALCOND ************************************************/

 #define ARTSPECIALCOND_LISTE \
         ARTSPECIALCOND.ARTICLENO,\
         ARTSPECIALCOND.INVOICE_REBATE_PCT,\
         ARTSPECIALCOND.REBATE_IN_KIND_PCT,\
         ARTSPECIALCOND.ANNUAL_INV_REB_PCT,\
         ARTSPECIALCOND.ANNUAL_REB_I_K_PCT,\
         ARTSPECIALCOND.CUST_REB_RED_PCT,\
         ARTSPECIALCOND.HI_REIMBURSEMENT,\
         ARTSPECIALCOND.SUPPL_HI_REIMB,\
         ARTSPECIALCOND.SUPPL_FS_REIMB,\
         ARTSPECIALCOND.SUPPL_DISCOUNT_PCT

 #define ARTSPECIALCOND_LISTE_390 \
         ARTICLENO,\
         INVOICE_REBATE_PCT,\
         REBATE_IN_KIND_PCT,\
         ANNUAL_INV_REB_PCT,\
         ANNUAL_REB_I_K_PCT,\
         CUST_REB_RED_PCT,\
         HI_REIMBURSEMENT,\
         SUPPL_HI_REIMB,\
         SUPPL_FS_REIMB,\
         SUPPL_DISCOUNT_PCT

 #define ARTSPECIALCOND_PLISTE \
         "ARTSPECIALCOND.ARTICLENO,"\
         "ARTSPECIALCOND.INVOICE_REBATE_PCT,"\
         "ARTSPECIALCOND.REBATE_IN_KIND_PCT,"\
         "ARTSPECIALCOND.ANNUAL_INV_REB_PCT,"\
         "ARTSPECIALCOND.ANNUAL_REB_I_K_PCT,"\
         "ARTSPECIALCOND.CUST_REB_RED_PCT,"\
         "ARTSPECIALCOND.HI_REIMBURSEMENT,"\
         "ARTSPECIALCOND.SUPPL_HI_REIMB,"\
         "ARTSPECIALCOND.SUPPL_FS_REIMB,"\
         "ARTSPECIALCOND.SUPPL_DISCOUNT_PCT"

 #define ARTSPECIALCOND_PELISTE \
         "ARTICLENO,"\
         "INVOICE_REBATE_PCT,"\
         "REBATE_IN_KIND_PCT,"\
         "ANNUAL_INV_REB_PCT,"\
         "ANNUAL_REB_I_K_PCT,"\
         "CUST_REB_RED_PCT,"\
         "HI_REIMBURSEMENT,"\
         "SUPPL_HI_REIMB,"\
         "SUPPL_FS_REIMB,"\
         "SUPPL_DISCOUNT_PCT"

 #define ARTSPECIALCOND_UPDLISTE \
         "ARTICLENO=?,"\
         "INVOICE_REBATE_PCT=?,"\
         "REBATE_IN_KIND_PCT=?,"\
         "ANNUAL_INV_REB_PCT=?,"\
         "ANNUAL_REB_I_K_PCT=?,"\
         "CUST_REB_RED_PCT=?,"\
         "HI_REIMBURSEMENT=?,"\
         "SUPPL_HI_REIMB=?,"\
         "SUPPL_FS_REIMB=?,"\
         "SUPPL_DISCOUNT_PCT=?"

/* SqlMacros-Define of ARTSPECIALCOND *****************************************/

 #define ARTSPECIALCOND_ZEIGER(x) \
         :x->ARTICLENO,\
         :x->INVOICE_REBATE_PCT,\
         :x->REBATE_IN_KIND_PCT,\
         :x->ANNUAL_INV_REB_PCT,\
         :x->ANNUAL_REB_I_K_PCT,\
         :x->CUST_REB_RED_PCT,\
         :x->HI_REIMBURSEMENT,\
         :x->SUPPL_HI_REIMB,\
         :x->SUPPL_FS_REIMB,\
         :x->SUPPL_DISCOUNT_PCT

 #define ARTSPECIALCOND_ZEIGERSEL(x) \
         :x->ARTICLENO,\
         :x->INVOICE_REBATE_PCT,\
         :x->REBATE_IN_KIND_PCT,\
         :x->ANNUAL_INV_REB_PCT,\
         :x->ANNUAL_REB_I_K_PCT,\
         :x->CUST_REB_RED_PCT,\
         :x->HI_REIMBURSEMENT,\
         :x->SUPPL_HI_REIMB,\
         :x->SUPPL_FS_REIMB,\
         :x->SUPPL_DISCOUNT_PCT

 #define ARTSPECIALCOND_UPDATE(x) \
         ARTSPECIALCOND.ARTICLENO=:x->ARTICLENO,\
         ARTSPECIALCOND.INVOICE_REBATE_PCT=:x->INVOICE_REBATE_PCT,\
         ARTSPECIALCOND.REBATE_IN_KIND_PCT=:x->REBATE_IN_KIND_PCT,\
         ARTSPECIALCOND.ANNUAL_INV_REB_PCT=:x->ANNUAL_INV_REB_PCT,\
         ARTSPECIALCOND.ANNUAL_REB_I_K_PCT=:x->ANNUAL_REB_I_K_PCT,\
         ARTSPECIALCOND.CUST_REB_RED_PCT=:x->CUST_REB_RED_PCT,\
         ARTSPECIALCOND.HI_REIMBURSEMENT=:x->HI_REIMBURSEMENT,\
         ARTSPECIALCOND.SUPPL_HI_REIMB=:x->SUPPL_HI_REIMB,\
         ARTSPECIALCOND.SUPPL_FS_REIMB=:x->SUPPL_FS_REIMB,\
         ARTSPECIALCOND.SUPPL_DISCOUNT_PCT=:x->SUPPL_DISCOUNT_PCT

/* SqlMacros390-Define of ARTSPECIALCOND **************************************/

 #define ARTSPECIALCOND_ZEIGER_390 \
         :ARTICLENO,\
         :INVOICE_REBATE_PCT,\
         :REBATE_IN_KIND_PCT,\
         :ANNUAL_INV_REB_PCT,\
         :ANNUAL_REB_I_K_PCT,\
         :CUST_REB_RED_PCT,\
         :HI_REIMBURSEMENT,\
         :SUPPL_HI_REIMB,\
         :SUPPL_FS_REIMB,\
         :SUPPL_DISCOUNT_PCT

 #define ARTSPECIALCOND_UPDATE_390 \
         ARTICLENO=:ARTICLENO,\
         INVOICE_REBATE_PCT=:INVOICE_REBATE_PCT,\
         REBATE_IN_KIND_PCT=:REBATE_IN_KIND_PCT,\
         ANNUAL_INV_REB_PCT=:ANNUAL_INV_REB_PCT,\
         ANNUAL_REB_I_K_PCT=:ANNUAL_REB_I_K_PCT,\
         CUST_REB_RED_PCT=:CUST_REB_RED_PCT,\
         HI_REIMBURSEMENT=:HI_REIMBURSEMENT,\
         SUPPL_HI_REIMB=:SUPPL_HI_REIMB,\
         SUPPL_FS_REIMB=:SUPPL_FS_REIMB,\
         SUPPL_DISCOUNT_PCT=:SUPPL_DISCOUNT_PCT

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTSPECIALCOND *****************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTSPECIALCOND {
         long ARTICLENO;
         double INVOICE_REBATE_PCT;
         double REBATE_IN_KIND_PCT;
         double ANNUAL_INV_REB_PCT;
         double ANNUAL_REB_I_K_PCT;
         double CUST_REB_RED_PCT;
         double HI_REIMBURSEMENT;
         double SUPPL_HI_REIMB;
         double SUPPL_FS_REIMB;
         double SUPPL_DISCOUNT_PCT;
        } artspecialcondS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTSPECIALCOND {
         long ARTICLENO;
         double INVOICE_REBATE_PCT;
         double REBATE_IN_KIND_PCT;
         double ANNUAL_INV_REB_PCT;
         double ANNUAL_REB_I_K_PCT;
         double CUST_REB_RED_PCT;
         double HI_REIMBURSEMENT;
         double SUPPL_HI_REIMB;
         double SUPPL_FS_REIMB;
         double SUPPL_DISCOUNT_PCT;

                        bool operator==(const N_ARTSPECIALCOND& right) const {
                        return(
                                ARTICLENO == right.ARTICLENO &&
                                INVOICE_REBATE_PCT == right.INVOICE_REBATE_PCT &&
                                REBATE_IN_KIND_PCT == right.REBATE_IN_KIND_PCT &&
                                ANNUAL_INV_REB_PCT == right.ANNUAL_INV_REB_PCT &&
                                ANNUAL_REB_I_K_PCT == right.ANNUAL_REB_I_K_PCT &&
                                CUST_REB_RED_PCT == right.CUST_REB_RED_PCT &&
                                HI_REIMBURSEMENT == right.HI_REIMBURSEMENT &&
                                SUPPL_HI_REIMB == right.SUPPL_HI_REIMB &&
                                SUPPL_FS_REIMB == right.SUPPL_FS_REIMB &&
                                SUPPL_DISCOUNT_PCT == right.SUPPL_DISCOUNT_PCT
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                ARTICLENO = 0;
                                INVOICE_REBATE_PCT = 0;
                                REBATE_IN_KIND_PCT = 0;
                                ANNUAL_INV_REB_PCT = 0;
                                ANNUAL_REB_I_K_PCT = 0;
                                CUST_REB_RED_PCT = 0;
                                HI_REIMBURSEMENT = 0;
                                SUPPL_HI_REIMB = 0;
                                SUPPL_FS_REIMB = 0;
                                SUPPL_DISCOUNT_PCT = 0;
#endif
                        }
         } artspecialcondS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTSPECIALCOND ************************************/

 struct S_ARTSPECIALCOND {
         char ARTICLENO[11];
         char INVOICE_REBATE_PCT[5 + 2];
         char REBATE_IN_KIND_PCT[5 + 2];
         char ANNUAL_INV_REB_PCT[5 + 2];
         char ANNUAL_REB_I_K_PCT[5 + 2];
         char CUST_REB_RED_PCT[5 + 2];
         char HI_REIMBURSEMENT[9 + 2];
         char SUPPL_HI_REIMB[9 + 2];
         char SUPPL_FS_REIMB[9 + 2];
         char SUPPL_DISCOUNT_PCT[5 + 2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTSPECIALCOND *******************/

 struct O_ARTSPECIALCOND {
         char ARTICLENO[11];
         char INVOICE_REBATE_PCT[5];
         char REBATE_IN_KIND_PCT[5];
         char ANNUAL_INV_REB_PCT[5];
         char ANNUAL_REB_I_K_PCT[5];
         char CUST_REB_RED_PCT[5];
         char HI_REIMBURSEMENT[9];
         char SUPPL_HI_REIMB[9];
         char SUPPL_FS_REIMB[9];
         char SUPPL_DISCOUNT_PCT[5];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTSPECIALCOND ******************************/

 struct C_ARTSPECIALCOND {
         long ARTICLENO;
         double INVOICE_REBATE_PCT;
         double REBATE_IN_KIND_PCT;
         double ANNUAL_INV_REB_PCT;
         double ANNUAL_REB_I_K_PCT;
         double CUST_REB_RED_PCT;
         double HI_REIMBURSEMENT;
         double SUPPL_HI_REIMB;
         double SUPPL_FS_REIMB;
         double SUPPL_DISCOUNT_PCT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTSPECIALCOND ****************************/

 struct I_ARTSPECIALCOND {
         short ARTICLENO;
         short INVOICE_REBATE_PCT;
         short REBATE_IN_KIND_PCT;
         short ANNUAL_INV_REB_PCT;
         short ANNUAL_REB_I_K_PCT;
         short CUST_REB_RED_PCT;
         short HI_REIMBURSEMENT;
         short SUPPL_HI_REIMB;
         short SUPPL_FS_REIMB;
         short SUPPL_DISCOUNT_PCT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTSPECIALCOND **************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTSPECIALCOND_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 5, 2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTSPECIALCOND_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 5, 2 },
 };
#endif

/* description for datatypes of ARTSPECIALCOND ********************************/

 #define ARTSPECIALCOND_S390 \
         long ARTICLENO; \
         double INVOICE_REBATE_PCT; \
         double REBATE_IN_KIND_PCT; \
         double ANNUAL_INV_REB_PCT; \
         double ANNUAL_REB_I_K_PCT; \
         double CUST_REB_RED_PCT; \
         double HI_REIMBURSEMENT; \
         double SUPPL_HI_REIMB; \
         double SUPPL_FS_REIMB; \
         double SUPPL_DISCOUNT_PCT; \



/* Copy-Function Struct to single Data ARTSPECIALCOND *************************/

 #define ARTSPECIALCOND_S390_COPY_TO_SINGLE(_x_) \
         ARTICLENO=_x_->ARTICLENO;\
         INVOICE_REBATE_PCT=_x_->INVOICE_REBATE_PCT;\
         REBATE_IN_KIND_PCT=_x_->REBATE_IN_KIND_PCT;\
         ANNUAL_INV_REB_PCT=_x_->ANNUAL_INV_REB_PCT;\
         ANNUAL_REB_I_K_PCT=_x_->ANNUAL_REB_I_K_PCT;\
         CUST_REB_RED_PCT=_x_->CUST_REB_RED_PCT;\
         HI_REIMBURSEMENT=_x_->HI_REIMBURSEMENT;\
         SUPPL_HI_REIMB=_x_->SUPPL_HI_REIMB;\
         SUPPL_FS_REIMB=_x_->SUPPL_FS_REIMB;\
         SUPPL_DISCOUNT_PCT=_x_->SUPPL_DISCOUNT_PCT;\

 #define ARTSPECIALCOND_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLENO=ARTICLENO;\
          _x_->INVOICE_REBATE_PCT=INVOICE_REBATE_PCT;\
          _x_->REBATE_IN_KIND_PCT=REBATE_IN_KIND_PCT;\
          _x_->ANNUAL_INV_REB_PCT=ANNUAL_INV_REB_PCT;\
          _x_->ANNUAL_REB_I_K_PCT=ANNUAL_REB_I_K_PCT;\
          _x_->CUST_REB_RED_PCT=CUST_REB_RED_PCT;\
          _x_->HI_REIMBURSEMENT=HI_REIMBURSEMENT;\
          _x_->SUPPL_HI_REIMB=SUPPL_HI_REIMB;\
          _x_->SUPPL_FS_REIMB=SUPPL_FS_REIMB;\
          _x_->SUPPL_DISCOUNT_PCT=SUPPL_DISCOUNT_PCT;\



/* FunctionNumber-Define of ArtSpecialCond ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArtSpecialCond ********************************/


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

class CARTSPECIALCOND : public ppDadeVirtual
{
        //data members
        public:
                artspecialcondS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<artspecialcondS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<artspecialcondS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<artspecialcondS>; Strip(s); artspecialcondS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<artspecialcondS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<artspecialcondS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<artspecialcondS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetArticleno() const    { return s.ARTICLENO; }
                double          GetInvoice_rebate_pct() const   { return s.INVOICE_REBATE_PCT; }
                double          GetRebate_in_kind_pct() const   { return s.REBATE_IN_KIND_PCT; }
                double          GetAnnual_inv_reb_pct() const   { return s.ANNUAL_INV_REB_PCT; }
                double          GetAnnual_reb_i_k_pct() const   { return s.ANNUAL_REB_I_K_PCT; }
                double          GetCust_reb_red_pct() const     { return s.CUST_REB_RED_PCT; }
                double          GetHi_reimbursement() const     { return s.HI_REIMBURSEMENT; }
                double          GetSuppl_hi_reimb() const       { return s.SUPPL_HI_REIMB; }
                double          GetSuppl_fs_reimb() const       { return s.SUPPL_FS_REIMB; }
                double          GetSuppl_discount_pct() const   { return s.SUPPL_DISCOUNT_PCT; }
                const artspecialcondS& GetStruct() const { return s; }
                void            SetArticleno(long t) { s.ARTICLENO = t; }
                void            SetInvoice_rebate_pct(double t) { s.INVOICE_REBATE_PCT = t; }
                void            SetRebate_in_kind_pct(double t) { s.REBATE_IN_KIND_PCT = t; }
                void            SetAnnual_inv_reb_pct(double t) { s.ANNUAL_INV_REB_PCT = t; }
                void            SetAnnual_reb_i_k_pct(double t) { s.ANNUAL_REB_I_K_PCT = t; }
                void            SetCust_reb_red_pct(double t) { s.CUST_REB_RED_PCT = t; }
                void            SetHi_reimbursement(double t) { s.HI_REIMBURSEMENT = t; }
                void            SetSuppl_hi_reimb(double t) { s.SUPPL_HI_REIMB = t; }
                void            SetSuppl_fs_reimb(double t) { s.SUPPL_FS_REIMB = t; }
                void            SetSuppl_discount_pct(double t) { s.SUPPL_DISCOUNT_PCT = t; }
                void            SetStruct(const artspecialcondS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CARTSPECIALCOND()  //constructor
                {
                        ::buf_default((void *)&s, ARTSPECIALCOND_BES, ARTSPECIALCOND_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CARTSPECIALCOND()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ARTSPECIALCOND_BES, ARTSPECIALCOND_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTSPECIALCOND_BES, ARTSPECIALCOND_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, ARTSPECIALCOND_BES, ARTSPECIALCOND_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ARTSPECIALCOND& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, ARTSPECIALCOND_BES, ARTSPECIALCOND_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ARTSPECIALCOND ***************************************/

 #define ARTSPECIALCOND_CREATE(x) exec sql create table x (\
         ARTICLENO integer default 0 not null,\
         INVOICE_REBATE_PCT decimal(5,2) default 0 not null,\
         REBATE_IN_KIND_PCT decimal(5,2) default 0 not null,\
         ANNUAL_INV_REB_PCT decimal(5,2) default 0 not null,\
         ANNUAL_REB_I_K_PCT decimal(5,2) default 0 not null,\
         CUST_REB_RED_PCT decimal(5,2) default 0 not null,\
         HI_REIMBURSEMENT decimal(9,2) default 0 not null,\
         SUPPL_HI_REIMB decimal(9,2) default 0 not null,\
         SUPPL_FS_REIMB decimal(9,2) default 0 not null,\
         SUPPL_DISCOUNT_PCT decimal(5,2) default 0 not null) in ksc extent size 156 next size 16 lock mode row;



/* CreateIndexStatement of ARTSPECIALCOND *************************************/

 #define ARTSPECIALCOND_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_artspeccon_1 on _X_(\
              ArticleNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTSPECIALCOND *************************************/

 #define ARTSPECIALCOND_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_artspeccon_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
