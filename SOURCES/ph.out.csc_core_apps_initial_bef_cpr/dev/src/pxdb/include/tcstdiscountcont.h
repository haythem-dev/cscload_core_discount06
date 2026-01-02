#ifndef __PP_CSTDISCOUNTCONT_H_
#define __PP_CSTDISCOUNTCONT_H_

/******************************************************************************/
/* v:\cstdiscountcont *********************************************************/
/******************************************************************************/

/* Length-Define of CSTDISCOUNTCONT *******************************************/

  #define L_CSTDISCOUNTCONT_BRANCHNO 6
  #define L_CSTDISCOUNTCONT_CUSTOMERNO 11
  #define L_CSTDISCOUNTCONT_ORDER_TYPE 2
  #define L_CSTDISCOUNTCONT_SUB_ORDER_TYPE 3
  #define L_CSTDISCOUNTCONT_PAYMENT_TERM 4
  #define L_CSTDISCOUNTCONT_VALUTA_DAYS 6
  #define L_CSTDISCOUNTCONT_MIN_ORDER_VALUE 9
  #define N_CSTDISCOUNTCONT_MIN_ORDER_VALUE 2
  #define L_CSTDISCOUNTCONT_MIN_TUBES 6
  #define L_CSTDISCOUNTCONT_LOSS_IN_DISCOUNT 5
  #define N_CSTDISCOUNTCONT_LOSS_IN_DISCOUNT 2

/* Length/Count-Define of CSTDISCOUNTCONT *************************************/

  #define LS_CSTDISCOUNTCONT_BRANCHNO 5 + 1
  #define LS_CSTDISCOUNTCONT_CUSTOMERNO 10 + 1
  #define LS_CSTDISCOUNTCONT_ORDER_TYPE 2 + 1
  #define LS_CSTDISCOUNTCONT_SUB_ORDER_TYPE 3 + 1
  #define LS_CSTDISCOUNTCONT_PAYMENT_TERM 4 + 1
  #define LS_CSTDISCOUNTCONT_VALUTA_DAYS 5 + 1
  #define LS_CSTDISCOUNTCONT_MIN_ORDER_VALUE 9 + 2
  #define LS_CSTDISCOUNTCONT_MIN_TUBES 5 + 1
  #define LS_CSTDISCOUNTCONT_LOSS_IN_DISCOUNT 5 + 2

  #define CSTDISCOUNTCONTBRANCHNO 0
  #define CSTDISCOUNTCONTCUSTOMERNO 1
  #define CSTDISCOUNTCONTORDER_TYPE 2
  #define CSTDISCOUNTCONTSUB_ORDER_TYPE 3
  #define CSTDISCOUNTCONTPAYMENT_TERM 4
  #define CSTDISCOUNTCONTVALUTA_DAYS 5
  #define CSTDISCOUNTCONTMIN_ORDER_VALUE 6
  #define CSTDISCOUNTCONTMIN_TUBES 7
  #define CSTDISCOUNTCONTLOSS_IN_DISCOUNT 8

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define CSTDISCOUNTCONT_H
 #define CSTDISCOUNTCONT_ANZ ( sizeof(CSTDISCOUNTCONT_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CSTDISCOUNTCONT ***********************************************/

 #define CSTDISCOUNTCONT_LISTE \
         CSTDISCOUNTCONT.BRANCHNO,\
         CSTDISCOUNTCONT.CUSTOMERNO,\
         CSTDISCOUNTCONT.ORDER_TYPE,\
         CSTDISCOUNTCONT.SUB_ORDER_TYPE,\
         CSTDISCOUNTCONT.PAYMENT_TERM,\
         CSTDISCOUNTCONT.VALUTA_DAYS,\
         CSTDISCOUNTCONT.MIN_ORDER_VALUE,\
         CSTDISCOUNTCONT.MIN_TUBES,\
         CSTDISCOUNTCONT.LOSS_IN_DISCOUNT

 #define CSTDISCOUNTCONT_LISTE_390 \
         BRANCHNO,\
         CUSTOMERNO,\
         ORDER_TYPE,\
         SUB_ORDER_TYPE,\
         PAYMENT_TERM,\
         VALUTA_DAYS,\
         MIN_ORDER_VALUE,\
         MIN_TUBES,\
         LOSS_IN_DISCOUNT

 #define CSTDISCOUNTCONT_PLISTE \
         "CSTDISCOUNTCONT.BRANCHNO,"\
         "CSTDISCOUNTCONT.CUSTOMERNO,"\
         "CSTDISCOUNTCONT.ORDER_TYPE,"\
         "CSTDISCOUNTCONT.SUB_ORDER_TYPE,"\
         "CSTDISCOUNTCONT.PAYMENT_TERM,"\
         "CSTDISCOUNTCONT.VALUTA_DAYS,"\
         "CSTDISCOUNTCONT.MIN_ORDER_VALUE,"\
         "CSTDISCOUNTCONT.MIN_TUBES,"\
         "CSTDISCOUNTCONT.LOSS_IN_DISCOUNT"

 #define CSTDISCOUNTCONT_PELISTE \
         "BRANCHNO,"\
         "CUSTOMERNO,"\
         "ORDER_TYPE,"\
         "SUB_ORDER_TYPE,"\
         "PAYMENT_TERM,"\
         "VALUTA_DAYS,"\
         "MIN_ORDER_VALUE,"\
         "MIN_TUBES,"\
         "LOSS_IN_DISCOUNT"

 #define CSTDISCOUNTCONT_UPDLISTE \
         "BRANCHNO=?,"\
         "CUSTOMERNO=?,"\
         "ORDER_TYPE=?,"\
         "SUB_ORDER_TYPE=?,"\
         "PAYMENT_TERM=?,"\
         "VALUTA_DAYS=?,"\
         "MIN_ORDER_VALUE=?,"\
         "MIN_TUBES=?,"\
         "LOSS_IN_DISCOUNT=?"

/* SqlMacros-Define of CSTDISCOUNTCONT ****************************************/

 #define CSTDISCOUNTCONT_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->ORDER_TYPE,\
         :x->SUB_ORDER_TYPE,\
         :x->PAYMENT_TERM,\
         :x->VALUTA_DAYS,\
         :x->MIN_ORDER_VALUE,\
         :x->MIN_TUBES,\
         :x->LOSS_IN_DISCOUNT

 #define CSTDISCOUNTCONT_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->ORDER_TYPE,\
         :x->SUB_ORDER_TYPE,\
         :x->PAYMENT_TERM,\
         :x->VALUTA_DAYS,\
         :x->MIN_ORDER_VALUE,\
         :x->MIN_TUBES,\
         :x->LOSS_IN_DISCOUNT

 #define CSTDISCOUNTCONT_UPDATE(x) \
         CSTDISCOUNTCONT.BRANCHNO=:x->BRANCHNO,\
         CSTDISCOUNTCONT.CUSTOMERNO=:x->CUSTOMERNO,\
         CSTDISCOUNTCONT.ORDER_TYPE=:x->ORDER_TYPE,\
         CSTDISCOUNTCONT.SUB_ORDER_TYPE=:x->SUB_ORDER_TYPE,\
         CSTDISCOUNTCONT.PAYMENT_TERM=:x->PAYMENT_TERM,\
         CSTDISCOUNTCONT.VALUTA_DAYS=:x->VALUTA_DAYS,\
         CSTDISCOUNTCONT.MIN_ORDER_VALUE=:x->MIN_ORDER_VALUE,\
         CSTDISCOUNTCONT.MIN_TUBES=:x->MIN_TUBES,\
         CSTDISCOUNTCONT.LOSS_IN_DISCOUNT=:x->LOSS_IN_DISCOUNT

/* SqlMacros390-Define of CSTDISCOUNTCONT *************************************/

 #define CSTDISCOUNTCONT_ZEIGER_390 \
         :BRANCHNO,\
         :CUSTOMERNO,\
         :ORDER_TYPE,\
         :SUB_ORDER_TYPE,\
         :PAYMENT_TERM,\
         :VALUTA_DAYS,\
         :MIN_ORDER_VALUE,\
         :MIN_TUBES,\
         :LOSS_IN_DISCOUNT

 #define CSTDISCOUNTCONT_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         CUSTOMERNO=:CUSTOMERNO,\
         ORDER_TYPE=:ORDER_TYPE,\
         SUB_ORDER_TYPE=:SUB_ORDER_TYPE,\
         PAYMENT_TERM=:PAYMENT_TERM,\
         VALUTA_DAYS=:VALUTA_DAYS,\
         MIN_ORDER_VALUE=:MIN_ORDER_VALUE,\
         MIN_TUBES=:MIN_TUBES,\
         LOSS_IN_DISCOUNT=:LOSS_IN_DISCOUNT

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of CSTDISCOUNTCONT ****************************************/

 #ifndef TRANSCLASS
 typedef struct N_CSTDISCOUNTCONT {
         short BRANCHNO;
         long CUSTOMERNO;
         char ORDER_TYPE[3];
         char SUB_ORDER_TYPE[4];
         char PAYMENT_TERM[5];
         short VALUTA_DAYS;
         double MIN_ORDER_VALUE;
         short MIN_TUBES;
         double LOSS_IN_DISCOUNT;
        } cstdiscountcontS;
 #else /*TRANSCLASS*/
 typedef struct N_CSTDISCOUNTCONT {
         short BRANCHNO;
         long CUSTOMERNO;
         char ORDER_TYPE[3];
         char SUB_ORDER_TYPE[4];
         char PAYMENT_TERM[5];
         short VALUTA_DAYS;
         double MIN_ORDER_VALUE;
         short MIN_TUBES;
         double LOSS_IN_DISCOUNT;

                        bool operator==(const N_CSTDISCOUNTCONT& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                CUSTOMERNO == right.CUSTOMERNO &&
                                !strcmp(ORDER_TYPE, right.ORDER_TYPE) &&
                                !strcmp(SUB_ORDER_TYPE, right.SUB_ORDER_TYPE) &&
                                !strcmp(PAYMENT_TERM, right.PAYMENT_TERM) &&
                                VALUTA_DAYS == right.VALUTA_DAYS &&
                                MIN_ORDER_VALUE == right.MIN_ORDER_VALUE &&
                                MIN_TUBES == right.MIN_TUBES &&
                                LOSS_IN_DISCOUNT == right.LOSS_IN_DISCOUNT
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                CUSTOMERNO = 0;
                                strcpy(ORDER_TYPE, " " );
                                strcpy(SUB_ORDER_TYPE, " " );
                                strcpy(PAYMENT_TERM, " " );
                                VALUTA_DAYS = 0;
                                MIN_ORDER_VALUE = 0;
                                MIN_TUBES = 0;
                                LOSS_IN_DISCOUNT = 0;
#endif
                        }
         } cstdiscountcontS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CSTDISCOUNTCONT ***********************************/

 struct S_CSTDISCOUNTCONT {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char ORDER_TYPE[2 + 1];
         char SUB_ORDER_TYPE[3 + 1];
         char PAYMENT_TERM[4 + 1];
         char VALUTA_DAYS[7];
         char MIN_ORDER_VALUE[9 + 2];
         char MIN_TUBES[7];
         char LOSS_IN_DISCOUNT[5 + 2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CSTDISCOUNTCONT ******************/

 struct O_CSTDISCOUNTCONT {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char ORDER_TYPE[2];
         char SUB_ORDER_TYPE[3];
         char PAYMENT_TERM[4];
         char VALUTA_DAYS[7];
         char MIN_ORDER_VALUE[9];
         char MIN_TUBES[7];
         char LOSS_IN_DISCOUNT[5];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CSTDISCOUNTCONT *****************************/

 struct C_CSTDISCOUNTCONT {
         short BRANCHNO;
         long CUSTOMERNO;
         char ORDER_TYPE[3];
         char SUB_ORDER_TYPE[4];
         char PAYMENT_TERM[5];
         short VALUTA_DAYS;
         double MIN_ORDER_VALUE;
         short MIN_TUBES;
         double LOSS_IN_DISCOUNT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CSTDISCOUNTCONT ***************************/

 struct I_CSTDISCOUNTCONT {
         short BRANCHNO;
         short CUSTOMERNO;
         short ORDER_TYPE;
         short SUB_ORDER_TYPE;
         short PAYMENT_TERM;
         short VALUTA_DAYS;
         short MIN_ORDER_VALUE;
         short MIN_TUBES;
         short LOSS_IN_DISCOUNT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CSTDISCOUNTCONT *************************************/

#if defined (BUF_DESC)
 static struct buf_desc CSTDISCOUNTCONT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 4, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc CSTDISCOUNTCONT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 4, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
 };
#endif

/* description for datatypes of CSTDISCOUNTCONT *******************************/

 #define CSTDISCOUNTCONT_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         char ORDER_TYPE[3]; \
         char SUB_ORDER_TYPE[4]; \
         char PAYMENT_TERM[5]; \
         short VALUTA_DAYS; \
         double MIN_ORDER_VALUE; \
         short MIN_TUBES; \
         double LOSS_IN_DISCOUNT; \



/* Copy-Function Struct to single Data CSTDISCOUNTCONT ************************/

 #define CSTDISCOUNTCONT_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
          strcpy(ORDER_TYPE,_x_->ORDER_TYPE);\
          strcpy(SUB_ORDER_TYPE,_x_->SUB_ORDER_TYPE);\
          strcpy(PAYMENT_TERM,_x_->PAYMENT_TERM);\
         VALUTA_DAYS=_x_->VALUTA_DAYS;\
         MIN_ORDER_VALUE=_x_->MIN_ORDER_VALUE;\
         MIN_TUBES=_x_->MIN_TUBES;\
         LOSS_IN_DISCOUNT=_x_->LOSS_IN_DISCOUNT;\

 #define CSTDISCOUNTCONT_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          strcpy(_x_->ORDER_TYPE,ORDER_TYPE);\
          strcpy(_x_->SUB_ORDER_TYPE,SUB_ORDER_TYPE);\
          strcpy(_x_->PAYMENT_TERM,PAYMENT_TERM);\
          _x_->VALUTA_DAYS=VALUTA_DAYS;\
          _x_->MIN_ORDER_VALUE=MIN_ORDER_VALUE;\
          _x_->MIN_TUBES=MIN_TUBES;\
          _x_->LOSS_IN_DISCOUNT=LOSS_IN_DISCOUNT;\



/* FunctionNumber-Define of cstdiscountcont ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of cstdiscountcont *******************************/


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

class CCSTDISCOUNTCONT : public ppDadeVirtual
{
        //data members
        public:
                cstdiscountcontS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<cstdiscountcontS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<cstdiscountcontS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<cstdiscountcontS>; Strip(s); cstdiscountcontS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<cstdiscountcontS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<cstdiscountcontS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<cstdiscountcontS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                long            GetCustomerno() const   { return s.CUSTOMERNO; }
                const char*     GetOrder_type(ppString& t) const        { t = s.ORDER_TYPE; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetSub_order_type(ppString& t) const    { t = s.SUB_ORDER_TYPE; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetPayment_term(ppString& t) const      { t = s.PAYMENT_TERM; t.erasespace(ppString::END); return t.c_str(); }
                short           GetValuta_days() const  { return s.VALUTA_DAYS; }
                double          GetMin_order_value() const      { return s.MIN_ORDER_VALUE; }
                short           GetMin_tubes() const    { return s.MIN_TUBES; }
                double          GetLoss_in_discount() const     { return s.LOSS_IN_DISCOUNT; }
                const cstdiscountcontS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetCustomerno(long t) { s.CUSTOMERNO = t; }
                void            SetOrder_type(const ppString& t) { ppGStrCopy(s.ORDER_TYPE,t.c_str() ,L_CSTDISCOUNTCONT_ORDER_TYPE); }
                void            SetSub_order_type(const ppString& t) { ppGStrCopy(s.SUB_ORDER_TYPE,t.c_str() ,L_CSTDISCOUNTCONT_SUB_ORDER_TYPE); }
                void            SetPayment_term(const ppString& t) { ppGStrCopy(s.PAYMENT_TERM,t.c_str() ,L_CSTDISCOUNTCONT_PAYMENT_TERM); }
                void            SetValuta_days(short t) { s.VALUTA_DAYS = t; }
                void            SetMin_order_value(double t) { s.MIN_ORDER_VALUE = t; }
                void            SetMin_tubes(short t) { s.MIN_TUBES = t; }
                void            SetLoss_in_discount(double t) { s.LOSS_IN_DISCOUNT = t; }
                void            SetStruct(const cstdiscountcontS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CCSTDISCOUNTCONT()  //constructor
                {
                        ::buf_default((void *)&s, CSTDISCOUNTCONT_BES, CSTDISCOUNTCONT_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CCSTDISCOUNTCONT()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, CSTDISCOUNTCONT_BES, CSTDISCOUNTCONT_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CSTDISCOUNTCONT_BES, CSTDISCOUNTCONT_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, CSTDISCOUNTCONT_BES, CSTDISCOUNTCONT_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_CSTDISCOUNTCONT& d)
                {
#ifdef WIN32
                        ppGStripLast(d.ORDER_TYPE);
                        ppGStripLast(d.SUB_ORDER_TYPE);
                        ppGStripLast(d.PAYMENT_TERM);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, CSTDISCOUNTCONT_BES, CSTDISCOUNTCONT_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of CSTDISCOUNTCONT **************************************/

 #define CSTDISCOUNTCONT_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         ORDER_TYPE char(2) default " " not null,\
         SUB_ORDER_TYPE char(3) default " " not null,\
         PAYMENT_TERM char(4) default " " not null,\
         VALUTA_DAYS smallint default 0 not null,\
         MIN_ORDER_VALUE decimal(9,2) default 0 not null,\
         MIN_TUBES smallint default 0 not null,\
         LOSS_IN_DISCOUNT decimal(5,2) default 0 not null) in ksc extent size 80 next size 8 lock mode row;



/* CreateIndexStatement of CSTDISCOUNTCONT ************************************/

 #define CSTDISCOUNTCONT_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of CSTDISCOUNTCONT ************************************/

 #define CSTDISCOUNTCONT_DELETE_INDEX(_X_)\
              _X_ = 0;\

#endif
