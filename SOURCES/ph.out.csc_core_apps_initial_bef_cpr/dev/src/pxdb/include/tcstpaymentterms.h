#ifndef __PP_CSTPAYMENTTERMS_H_
#define __PP_CSTPAYMENTTERMS_H_

/******************************************************************************/
/* u:\CstPaymentTerms *********************************************************/
/******************************************************************************/

/* Length-Define of CSTPAYMENTTERMS *******************************************/

  #define L_CSTPAYMENTTERMS_BRANCHNO 6
  #define L_CSTPAYMENTTERMS_CUSTOMERNO 11
  #define L_CSTPAYMENTTERMS_PREIS_TYP 6
  #define L_CSTPAYMENTTERMS_PAYMENTARGET 6

/* Length/Count-Define of CSTPAYMENTTERMS *************************************/

  #define LS_CSTPAYMENTTERMS_BRANCHNO 5 + 1
  #define LS_CSTPAYMENTTERMS_CUSTOMERNO 10 + 1
  #define LS_CSTPAYMENTTERMS_PREIS_TYP 5 + 1
  #define LS_CSTPAYMENTTERMS_PAYMENTARGET 5 + 1

  #define CSTPAYMENTTERMSBRANCHNO 0
  #define CSTPAYMENTTERMSCUSTOMERNO 1
  #define CSTPAYMENTTERMSPREIS_TYP 2
  #define CSTPAYMENTTERMSPAYMENTARGET 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define CSTPAYMENTTERMS_H
 #define CSTPAYMENTTERMS_ANZ ( sizeof(CSTPAYMENTTERMS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CSTPAYMENTTERMS ***********************************************/

 #define CSTPAYMENTTERMS_LISTE \
         CSTPAYMENTTERMS.BRANCHNO,\
         CSTPAYMENTTERMS.CUSTOMERNO,\
         CSTPAYMENTTERMS.PREIS_TYP,\
         CSTPAYMENTTERMS.PAYMENTARGET

 #define CSTPAYMENTTERMS_LISTE_390 \
         BRANCHNO,\
         CUSTOMERNO,\
         PREIS_TYP,\
         PAYMENTARGET

 #define CSTPAYMENTTERMS_PLISTE \
         "CSTPAYMENTTERMS.BRANCHNO,"\
         "CSTPAYMENTTERMS.CUSTOMERNO,"\
         "CSTPAYMENTTERMS.PREIS_TYP,"\
         "CSTPAYMENTTERMS.PAYMENTARGET"

 #define CSTPAYMENTTERMS_PELISTE \
         "BRANCHNO,"\
         "CUSTOMERNO,"\
         "PREIS_TYP,"\
         "PAYMENTARGET"

 #define CSTPAYMENTTERMS_UPDLISTE \
         "BRANCHNO=?,"\
         "CUSTOMERNO=?,"\
         "PREIS_TYP=?,"\
         "PAYMENTARGET=?"

/* SqlMacros-Define of CSTPAYMENTTERMS ****************************************/

 #define CSTPAYMENTTERMS_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->PREIS_TYP,\
         :x->PAYMENTARGET

 #define CSTPAYMENTTERMS_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->PREIS_TYP,\
         :x->PAYMENTARGET

 #define CSTPAYMENTTERMS_UPDATE(x) \
         CSTPAYMENTTERMS.BRANCHNO=:x->BRANCHNO,\
         CSTPAYMENTTERMS.CUSTOMERNO=:x->CUSTOMERNO,\
         CSTPAYMENTTERMS.PREIS_TYP=:x->PREIS_TYP,\
         CSTPAYMENTTERMS.PAYMENTARGET=:x->PAYMENTARGET

/* SqlMacros390-Define of CSTPAYMENTTERMS *************************************/

 #define CSTPAYMENTTERMS_ZEIGER_390 \
         :BRANCHNO,\
         :CUSTOMERNO,\
         :PREIS_TYP,\
         :PAYMENTARGET

 #define CSTPAYMENTTERMS_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         CUSTOMERNO=:CUSTOMERNO,\
         PREIS_TYP=:PREIS_TYP,\
         PAYMENTARGET=:PAYMENTARGET

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of CSTPAYMENTTERMS ****************************************/

 #ifndef TRANSCLASS
 typedef struct N_CSTPAYMENTTERMS {
         short BRANCHNO;
         long CUSTOMERNO;
         short PREIS_TYP;
         short PAYMENTARGET;
        } cstpaymenttermsS;
 #else /*TRANSCLASS*/
 typedef struct N_CSTPAYMENTTERMS {
         short BRANCHNO;
         long CUSTOMERNO;
         short PREIS_TYP;
         short PAYMENTARGET;

                        bool operator==(const N_CSTPAYMENTTERMS& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                CUSTOMERNO == right.CUSTOMERNO &&
                                PREIS_TYP == right.PREIS_TYP &&
                                PAYMENTARGET == right.PAYMENTARGET
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                CUSTOMERNO = 0;
                                PREIS_TYP = 0;
                                PAYMENTARGET = 0;
#endif
                        }
         } cstpaymenttermsS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CSTPAYMENTTERMS ***********************************/

 struct S_CSTPAYMENTTERMS {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char PREIS_TYP[7];
         char PAYMENTARGET[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CSTPAYMENTTERMS ******************/

 struct O_CSTPAYMENTTERMS {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char PREIS_TYP[7];
         char PAYMENTARGET[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CSTPAYMENTTERMS *****************************/

 struct C_CSTPAYMENTTERMS {
         short BRANCHNO;
         long CUSTOMERNO;
         short PREIS_TYP;
         short PAYMENTARGET;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CSTPAYMENTTERMS ***************************/

 struct I_CSTPAYMENTTERMS {
         short BRANCHNO;
         short CUSTOMERNO;
         short PREIS_TYP;
         short PAYMENTARGET;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CSTPAYMENTTERMS *************************************/

#if defined (BUF_DESC)
 static struct buf_desc CSTPAYMENTTERMS_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc CSTPAYMENTTERMS_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of CSTPAYMENTTERMS *******************************/

 #define CSTPAYMENTTERMS_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         short PREIS_TYP; \
         short PAYMENTARGET; \



/* Copy-Function Struct to single Data CSTPAYMENTTERMS ************************/

 #define CSTPAYMENTTERMS_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         PREIS_TYP=_x_->PREIS_TYP;\
         PAYMENTARGET=_x_->PAYMENTARGET;\

 #define CSTPAYMENTTERMS_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->PREIS_TYP=PREIS_TYP;\
          _x_->PAYMENTARGET=PAYMENTARGET;\



/* FunctionNumber-Define of CstPaymentTerms ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CstPaymentTerms *******************************/


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

class CCSTPAYMENTTERMS : public ppDadeVirtual
{
        //data members
        public:
                cstpaymenttermsS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<cstpaymenttermsS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<cstpaymenttermsS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<cstpaymenttermsS>; Strip(s); cstpaymenttermsS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<cstpaymenttermsS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<cstpaymenttermsS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<cstpaymenttermsS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                long            GetCustomerno() const   { return s.CUSTOMERNO; }
                short           GetPreis_typ() const    { return s.PREIS_TYP; }
                short           GetPaymentarget() const { return s.PAYMENTARGET; }
                const cstpaymenttermsS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetCustomerno(long t) { s.CUSTOMERNO = t; }
                void            SetPreis_typ(short t) { s.PREIS_TYP = t; }
                void            SetPaymentarget(short t) { s.PAYMENTARGET = t; }
                void            SetStruct(const cstpaymenttermsS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CCSTPAYMENTTERMS()  //constructor
                {
                        ::buf_default((void *)&s, CSTPAYMENTTERMS_BES, CSTPAYMENTTERMS_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CCSTPAYMENTTERMS()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, CSTPAYMENTTERMS_BES, CSTPAYMENTTERMS_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CSTPAYMENTTERMS_BES, CSTPAYMENTTERMS_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, CSTPAYMENTTERMS_BES, CSTPAYMENTTERMS_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_CSTPAYMENTTERMS& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, CSTPAYMENTTERMS_BES, CSTPAYMENTTERMS_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of CSTPAYMENTTERMS **************************************/

 #define CSTPAYMENTTERMS_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         PREIS_TYP smallint default 0 not null,\
         PAYMENTARGET smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of CSTPAYMENTTERMS ************************************/

 #define CSTPAYMENTTERMS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_cstpayterm_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              preis_typ,\
              paymentarget ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CSTPAYMENTTERMS ************************************/

 #define CSTPAYMENTTERMS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_cstpayterm_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
