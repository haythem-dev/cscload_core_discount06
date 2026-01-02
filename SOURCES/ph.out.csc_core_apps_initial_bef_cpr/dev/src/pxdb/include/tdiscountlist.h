#ifndef __PP_DISCOUNTLIST_H_
#define __PP_DISCOUNTLIST_H_

/******************************************************************************/
/* v:\discountlist ************************************************************/
/******************************************************************************/

/* Length-Define of DISCOUNTLIST **********************************************/

  #define L_DISCOUNTLIST_ORDER_TYPE 2
  #define L_DISCOUNTLIST_SUB_ORDER_TYPE 3
  #define L_DISCOUNTLIST_PHARMACYGROUPID 3
  #define L_DISCOUNTLIST_PAYMENT_TERM 4
  #define L_DISCOUNTLIST_MONTHLY_DISC_PCT 5
  #define N_DISCOUNTLIST_MONTHLY_DISC_PCT 2
  #define L_DISCOUNTLIST_VALUTA_DAYS 6

/* Length/Count-Define of DISCOUNTLIST ****************************************/

  #define LS_DISCOUNTLIST_ORDER_TYPE 2 + 1
  #define LS_DISCOUNTLIST_SUB_ORDER_TYPE 3 + 1
  #define LS_DISCOUNTLIST_PHARMACYGROUPID 3 + 1
  #define LS_DISCOUNTLIST_PAYMENT_TERM 4 + 1
  #define LS_DISCOUNTLIST_MONTHLY_DISC_PCT 5 + 2
  #define LS_DISCOUNTLIST_VALUTA_DAYS 5 + 1

  #define DISCOUNTLISTORDER_TYPE 0
  #define DISCOUNTLISTSUB_ORDER_TYPE 1
  #define DISCOUNTLISTPHARMACYGROUPID 2
  #define DISCOUNTLISTPAYMENT_TERM 3
  #define DISCOUNTLISTMONTHLY_DISC_PCT 4
  #define DISCOUNTLISTVALUTA_DAYS 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define DISCOUNTLIST_H
 #define DISCOUNTLIST_ANZ ( sizeof(DISCOUNTLIST_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DISCOUNTLIST **************************************************/

 #define DISCOUNTLIST_LISTE \
         DISCOUNTLIST.ORDER_TYPE,\
         DISCOUNTLIST.SUB_ORDER_TYPE,\
         DISCOUNTLIST.PHARMACYGROUPID,\
         DISCOUNTLIST.PAYMENT_TERM,\
         DISCOUNTLIST.MONTHLY_DISC_PCT,\
         DISCOUNTLIST.VALUTA_DAYS

 #define DISCOUNTLIST_LISTE_390 \
         ORDER_TYPE,\
         SUB_ORDER_TYPE,\
         PHARMACYGROUPID,\
         PAYMENT_TERM,\
         MONTHLY_DISC_PCT,\
         VALUTA_DAYS

 #define DISCOUNTLIST_PLISTE \
         "DISCOUNTLIST.ORDER_TYPE,"\
         "DISCOUNTLIST.SUB_ORDER_TYPE,"\
         "DISCOUNTLIST.PHARMACYGROUPID,"\
         "DISCOUNTLIST.PAYMENT_TERM,"\
         "DISCOUNTLIST.MONTHLY_DISC_PCT,"\
         "DISCOUNTLIST.VALUTA_DAYS"

 #define DISCOUNTLIST_PELISTE \
         "ORDER_TYPE,"\
         "SUB_ORDER_TYPE,"\
         "PHARMACYGROUPID,"\
         "PAYMENT_TERM,"\
         "MONTHLY_DISC_PCT,"\
         "VALUTA_DAYS"

 #define DISCOUNTLIST_UPDLISTE \
         "ORDER_TYPE=?,"\
         "SUB_ORDER_TYPE=?,"\
         "PHARMACYGROUPID=?,"\
         "PAYMENT_TERM=?,"\
         "MONTHLY_DISC_PCT=?,"\
         "VALUTA_DAYS=?"

/* SqlMacros-Define of DISCOUNTLIST *******************************************/

 #define DISCOUNTLIST_ZEIGER(x) \
         :x->ORDER_TYPE,\
         :x->SUB_ORDER_TYPE,\
         :x->PHARMACYGROUPID,\
         :x->PAYMENT_TERM,\
         :x->MONTHLY_DISC_PCT,\
         :x->VALUTA_DAYS

 #define DISCOUNTLIST_ZEIGERSEL(x) \
         :x->ORDER_TYPE,\
         :x->SUB_ORDER_TYPE,\
         :x->PHARMACYGROUPID,\
         :x->PAYMENT_TERM,\
         :x->MONTHLY_DISC_PCT,\
         :x->VALUTA_DAYS

 #define DISCOUNTLIST_UPDATE(x) \
         DISCOUNTLIST.ORDER_TYPE=:x->ORDER_TYPE,\
         DISCOUNTLIST.SUB_ORDER_TYPE=:x->SUB_ORDER_TYPE,\
         DISCOUNTLIST.PHARMACYGROUPID=:x->PHARMACYGROUPID,\
         DISCOUNTLIST.PAYMENT_TERM=:x->PAYMENT_TERM,\
         DISCOUNTLIST.MONTHLY_DISC_PCT=:x->MONTHLY_DISC_PCT,\
         DISCOUNTLIST.VALUTA_DAYS=:x->VALUTA_DAYS

/* SqlMacros390-Define of DISCOUNTLIST ****************************************/

 #define DISCOUNTLIST_ZEIGER_390 \
         :ORDER_TYPE,\
         :SUB_ORDER_TYPE,\
         :PHARMACYGROUPID,\
         :PAYMENT_TERM,\
         :MONTHLY_DISC_PCT,\
         :VALUTA_DAYS

 #define DISCOUNTLIST_UPDATE_390 \
         ORDER_TYPE=:ORDER_TYPE,\
         SUB_ORDER_TYPE=:SUB_ORDER_TYPE,\
         PHARMACYGROUPID=:PHARMACYGROUPID,\
         PAYMENT_TERM=:PAYMENT_TERM,\
         MONTHLY_DISC_PCT=:MONTHLY_DISC_PCT,\
         VALUTA_DAYS=:VALUTA_DAYS

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of DISCOUNTLIST *******************************************/

 #ifndef TRANSCLASS
 typedef struct N_DISCOUNTLIST {
         char ORDER_TYPE[3];
         char SUB_ORDER_TYPE[4];
         char PHARMACYGROUPID[4];
         char PAYMENT_TERM[5];
         double MONTHLY_DISC_PCT;
         short VALUTA_DAYS;
        } discountlistS;
 #else /*TRANSCLASS*/
 typedef struct N_DISCOUNTLIST {
         char ORDER_TYPE[3];
         char SUB_ORDER_TYPE[4];
         char PHARMACYGROUPID[4];
         char PAYMENT_TERM[5];
         double MONTHLY_DISC_PCT;
         short VALUTA_DAYS;

                        bool operator==(const N_DISCOUNTLIST& right) const {
                        return(
                                !strcmp(ORDER_TYPE, right.ORDER_TYPE) &&
                                !strcmp(SUB_ORDER_TYPE, right.SUB_ORDER_TYPE) &&
                                !strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
                                !strcmp(PAYMENT_TERM, right.PAYMENT_TERM) &&
                                MONTHLY_DISC_PCT == right.MONTHLY_DISC_PCT &&
                                VALUTA_DAYS == right.VALUTA_DAYS
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                strcpy(ORDER_TYPE, " " );
                                strcpy(SUB_ORDER_TYPE, " " );
                                strcpy(PHARMACYGROUPID, " " );
                                strcpy(PAYMENT_TERM, " " );
                                MONTHLY_DISC_PCT = 0;
                                VALUTA_DAYS = 0;
#endif
                        }
         } discountlistS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DISCOUNTLIST **************************************/

 struct S_DISCOUNTLIST {
         char ORDER_TYPE[2 + 1];
         char SUB_ORDER_TYPE[3 + 1];
         char PHARMACYGROUPID[3 + 1];
         char PAYMENT_TERM[4 + 1];
         char MONTHLY_DISC_PCT[5 + 2];
         char VALUTA_DAYS[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DISCOUNTLIST *********************/

 struct O_DISCOUNTLIST {
         char ORDER_TYPE[2];
         char SUB_ORDER_TYPE[3];
         char PHARMACYGROUPID[3];
         char PAYMENT_TERM[4];
         char MONTHLY_DISC_PCT[5];
         char VALUTA_DAYS[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DISCOUNTLIST ********************************/

 struct C_DISCOUNTLIST {
         char ORDER_TYPE[3];
         char SUB_ORDER_TYPE[4];
         char PHARMACYGROUPID[4];
         char PAYMENT_TERM[5];
         double MONTHLY_DISC_PCT;
         short VALUTA_DAYS;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DISCOUNTLIST ******************************/

 struct I_DISCOUNTLIST {
         short ORDER_TYPE;
         short SUB_ORDER_TYPE;
         short PHARMACYGROUPID;
         short PAYMENT_TERM;
         short MONTHLY_DISC_PCT;
         short VALUTA_DAYS;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DISCOUNTLIST ****************************************/

#if defined (BUF_DESC)
 static struct buf_desc DISCOUNTLIST_BES [] =
 {
   { TYP_C, 2, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 4, 0 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DISCOUNTLIST_BES [] =
 {
   { TYP_C, 2, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 4, 0 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of DISCOUNTLIST **********************************/

 #define DISCOUNTLIST_S390 \
         char ORDER_TYPE[3]; \
         char SUB_ORDER_TYPE[4]; \
         char PHARMACYGROUPID[4]; \
         char PAYMENT_TERM[5]; \
         double MONTHLY_DISC_PCT; \
         short VALUTA_DAYS; \



/* Copy-Function Struct to single Data DISCOUNTLIST ***************************/

 #define DISCOUNTLIST_S390_COPY_TO_SINGLE(_x_) \
          strcpy(ORDER_TYPE,_x_->ORDER_TYPE);\
          strcpy(SUB_ORDER_TYPE,_x_->SUB_ORDER_TYPE);\
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\
          strcpy(PAYMENT_TERM,_x_->PAYMENT_TERM);\
         MONTHLY_DISC_PCT=_x_->MONTHLY_DISC_PCT;\
         VALUTA_DAYS=_x_->VALUTA_DAYS;\

 #define DISCOUNTLIST_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->ORDER_TYPE,ORDER_TYPE);\
          strcpy(_x_->SUB_ORDER_TYPE,SUB_ORDER_TYPE);\
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\
          strcpy(_x_->PAYMENT_TERM,PAYMENT_TERM);\
          _x_->MONTHLY_DISC_PCT=MONTHLY_DISC_PCT;\
          _x_->VALUTA_DAYS=VALUTA_DAYS;\



/* FunctionNumber-Define of discountlist **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of discountlist **********************************/


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

class CDISCOUNTLIST : public ppDadeVirtual
{
        //data members
        public:
                discountlistS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<discountlistS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<discountlistS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<discountlistS>; Strip(s); discountlistS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<discountlistS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<discountlistS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<discountlistS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                const char*     GetOrder_type(ppString& t) const        { t = s.ORDER_TYPE; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetSub_order_type(ppString& t) const    { t = s.SUB_ORDER_TYPE; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetPharmacygroupid(ppString& t) const   { t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetPayment_term(ppString& t) const      { t = s.PAYMENT_TERM; t.erasespace(ppString::END); return t.c_str(); }
                double          GetMonthly_disc_pct() const     { return s.MONTHLY_DISC_PCT; }
                short           GetValuta_days() const  { return s.VALUTA_DAYS; }
                const discountlistS& GetStruct() const { return s; }
                void            SetOrder_type(const ppString& t) { ppGStrCopy(s.ORDER_TYPE,t.c_str() ,L_DISCOUNTLIST_ORDER_TYPE); }
                void            SetSub_order_type(const ppString& t) { ppGStrCopy(s.SUB_ORDER_TYPE,t.c_str() ,L_DISCOUNTLIST_SUB_ORDER_TYPE); }
                void            SetPharmacygroupid(const ppString& t) { ppGStrCopy(s.PHARMACYGROUPID,t.c_str() ,L_DISCOUNTLIST_PHARMACYGROUPID); }
                void            SetPayment_term(const ppString& t) { ppGStrCopy(s.PAYMENT_TERM,t.c_str() ,L_DISCOUNTLIST_PAYMENT_TERM); }
                void            SetMonthly_disc_pct(double t) { s.MONTHLY_DISC_PCT = t; }
                void            SetValuta_days(short t) { s.VALUTA_DAYS = t; }
                void            SetStruct(const discountlistS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CDISCOUNTLIST()  //constructor
                {
                        ::buf_default((void *)&s, DISCOUNTLIST_BES, DISCOUNTLIST_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CDISCOUNTLIST()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, DISCOUNTLIST_BES, DISCOUNTLIST_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DISCOUNTLIST_BES, DISCOUNTLIST_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, DISCOUNTLIST_BES, DISCOUNTLIST_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_DISCOUNTLIST& d)
                {
#ifdef WIN32
                        ppGStripLast(d.ORDER_TYPE);
                        ppGStripLast(d.SUB_ORDER_TYPE);
                        ppGStripLast(d.PHARMACYGROUPID);
                        ppGStripLast(d.PAYMENT_TERM);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, DISCOUNTLIST_BES, DISCOUNTLIST_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of DISCOUNTLIST *****************************************/

 #define DISCOUNTLIST_CREATE(x) exec sql create table x (\
         ORDER_TYPE char(2) default " " not null,\
         SUB_ORDER_TYPE char(3) default " " not null,\
         PHARMACYGROUPID char(3) default " " not null,\
         PAYMENT_TERM char(4) default " " not null,\
         MONTHLY_DISC_PCT decimal(5,2) default 0 not null,\
         VALUTA_DAYS smallint default 0 not null) in ksc extent size 80 next size 8 lock mode row;



/* CreateIndexStatement of DISCOUNTLIST ***************************************/

 #define DISCOUNTLIST_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_discountlist_1 on _X_(\
              order_type,\
              sub_order_type ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of DISCOUNTLIST ***************************************/

 #define DISCOUNTLIST_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_discountlist_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
