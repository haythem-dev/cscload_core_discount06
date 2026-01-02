#ifndef __PP_CUSTOMERORDERNO_H_
#define __PP_CUSTOMERORDERNO_H_

/******************************************************************************/
/* v:\nordat\customerorderno **************************************************/
/******************************************************************************/

/* Length-Define of CUSTOMERORDERNO *******************************************/

  #define L_CUSTOMERORDERNO_BRANCHNO 6
  #define L_CUSTOMERORDERNO_CUSTOMERNO 11
  #define L_CUSTOMERORDERNO_PROCESSNO 11
  #define L_CUSTOMERORDERNO_CUSTOMERORDERNO 30
  #define L_CUSTOMERORDERNO_ORDERVALUE 0

/* Length/Count-Define of CUSTOMERORDERNO *************************************/

  #define LS_CUSTOMERORDERNO_BRANCHNO 5 + 1
  #define LS_CUSTOMERORDERNO_CUSTOMERNO 31 + 1
  #define LS_CUSTOMERORDERNO_PROCESSNO 10 + 1
  #define LS_CUSTOMERORDERNO_CUSTOMERORDERNO 31 + 1
  #define LS_CUSTOMERORDERNO_ORDERVALUE 0 + 1

  #define CUSTOMERORDERNOBRANCHNO 0
  #define CUSTOMERORDERNOCUSTOMERNO 1
  #define CUSTOMERORDERNOPROCESSNO 2
  #define CUSTOMERORDERNOCUSTOMERORDERNO 3
  #define CUSTOMERORDERNOORDERVALUE 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define CUSTOMERORDERNO_H
 #define CUSTOMERORDERNO_ANZ ( sizeof(CUSTOMERORDERNO_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CUSTOMERORDERNO ***********************************************/

 #define CUSTOMERORDERNO_LISTE \
         CUSTOMERORDERNO.BRANCHNO,\
         CUSTOMERORDERNO.CUSTOMERNO,\
         CUSTOMERORDERNO.PROCESSNO,\
         CUSTOMERORDERNO.CUSTOMERORDERNO,\
         CUSTOMERORDERNO.ORDERVALUE

 #define CUSTOMERORDERNO_LISTE_390 \
         BRANCHNO,\
         CUSTOMERNO,\
         PROCESSNO,\
         CUSTOMERORDERNO,\
         ORDERVALUE

 #define CUSTOMERORDERNO_PLISTE \
         "CUSTOMERORDERNO.BRANCHNO,"\
         "CUSTOMERORDERNO.CUSTOMERNO,"\
         "CUSTOMERORDERNO.PROCESSNO,"\
         "CUSTOMERORDERNO.CUSTOMERORDERNO,"\
         "CUSTOMERORDERNO.ORDERVALUE"

 #define CUSTOMERORDERNO_PELISTE \
         "BRANCHNO,"\
         "CUSTOMERNO,"\
         "PROCESSNO,"\
         "CUSTOMERORDERNO,"\
         "ORDERVALUE"

 #define CUSTOMERORDERNO_UPDLISTE \
         "BRANCHNO=?,"\
         "CUSTOMERNO=?,"\
         "PROCESSNO=?,"\
         "CUSTOMERORDERNO=?,"\
         "ORDERVALUE=?"

/* SqlMacros-Define of CUSTOMERORDERNO ****************************************/

 #define CUSTOMERORDERNO_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->PROCESSNO,\
         :x->CUSTOMERORDERNO,\
         :x->ORDERVALUE

 #define CUSTOMERORDERNO_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->PROCESSNO,\
         :x->CUSTOMERORDERNO,\
         :x->ORDERVALUE

 #define CUSTOMERORDERNO_UPDATE(x) \
         CUSTOMERORDERNO.BRANCHNO=:x->BRANCHNO,\
         CUSTOMERORDERNO.CUSTOMERNO=:x->CUSTOMERNO,\
         CUSTOMERORDERNO.PROCESSNO=:x->PROCESSNO,\
         CUSTOMERORDERNO.CUSTOMERORDERNO=:x->CUSTOMERORDERNO,\
         CUSTOMERORDERNO.ORDERVALUE=:x->ORDERVALUE

/* SqlMacros390-Define of CUSTOMERORDERNO *************************************/

 #define CUSTOMERORDERNO_ZEIGER_390 \
         :BRANCHNO,\
         :CUSTOMERNO,\
         :PROCESSNO,\
         :CUSTOMERORDERNO,\
         :ORDERVALUE

 #define CUSTOMERORDERNO_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         CUSTOMERNO=:CUSTOMERNO,\
         PROCESSNO=:PROCESSNO,\
         CUSTOMERORDERNO=:CUSTOMERORDERNO,\
         ORDERVALUE=:ORDERVALUE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of CUSTOMERORDERNO ****************************************/

 #ifndef TRANSCLASS
 typedef struct N_CUSTOMERORDERNO {
         short BRANCHNO;
         long CUSTOMERNO;
         long PROCESSNO;
         char CUSTOMERORDERNO[31];
         double ORDERVALUE;
        } customerordernoS;
 #else /*TRANSCLASS*/
 typedef struct N_CUSTOMERORDERNO {
         short BRANCHNO;
         long CUSTOMERNO;
         long PROCESSNO;
         char CUSTOMERORDERNO[31];
         double ORDERVALUE;

                        bool operator==(const N_CUSTOMERORDERNO& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                CUSTOMERNO == right.CUSTOMERNO &&
                                PROCESSNO == right.PROCESSNO &&
                                !strcmp(CUSTOMERORDERNO, right.CUSTOMERORDERNO) &&
                                ORDERVALUE == right.ORDERVALUE
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                CUSTOMERNO = 0;
                                PROCESSNO = 0;
                                strcpy(CUSTOMERORDERNO, " " );
                                ORDERVALUE = 0;
#endif
                        }
         } customerordernoS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CUSTOMERORDERNO ***********************************/

 struct S_CUSTOMERORDERNO {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char PROCESSNO[11];
         char CUSTOMERORDERNO[30 + 1];
         char ORDERVALUE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CUSTOMERORDERNO ******************/

 struct O_CUSTOMERORDERNO {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char PROCESSNO[11];
         char CUSTOMERORDERNO[30];
         char ORDERVALUE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CUSTOMERORDERNO *****************************/

 struct C_CUSTOMERORDERNO {
         short BRANCHNO;
         long CUSTOMERNO;
         long PROCESSNO;
         char CUSTOMERORDERNO[31];
         double ORDERVALUE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CUSTOMERORDERNO ***************************/

 struct I_CUSTOMERORDERNO {
         short BRANCHNO;
         short CUSTOMERNO;
         short PROCESSNO;
         short CUSTOMERORDERNO;
         short ORDERVALUE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CUSTOMERORDERNO *************************************/

#if defined (BUF_DESC)
 static struct buf_desc CUSTOMERORDERNO_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 9, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc CUSTOMERORDERNO_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 9, 0 },
 };
#endif

/* description for datatypes of CUSTOMERORDERNO *******************************/

 #define CUSTOMERORDERNO_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long PROCESSNO; \
         char CUSTOMERORDERNO[31]; \
         double ORDERVALUE; \



/* Copy-Function Struct to single Data CUSTOMERORDERNO ************************/

 #define CUSTOMERORDERNO_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         PROCESSNO=_x_->PROCESSNO;\
          strcpy(CUSTOMERORDERNO,_x_->CUSTOMERORDERNO);\
         ORDERVALUE=_x_->ORDERVALUE;\

 #define CUSTOMERORDERNO_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->PROCESSNO=PROCESSNO;\
          strcpy(_x_->CUSTOMERORDERNO,CUSTOMERORDERNO);\
          _x_->ORDERVALUE=ORDERVALUE;\



/* FunctionNumber-Define of customerorderno ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of customerorderno *******************************/


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

class CCUSTOMERORDERNO : public ppDadeVirtual
{
        //data members
        public:
                customerordernoS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<customerordernoS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<customerordernoS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<customerordernoS>; Strip(s); customerordernoS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<customerordernoS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<customerordernoS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<customerordernoS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                long            GetCustomerno() const   { return s.CUSTOMERNO; }
                long            GetProcessno() const    { return s.PROCESSNO; }
                const char*     GetCustomerorderno(ppString& t) const   { t = s.CUSTOMERORDERNO; t.erasespace(ppString::END); return t.c_str(); }
                double          GetOrdervalue() const   { return s.ORDERVALUE; }
                const customerordernoS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetCustomerno(long t) { s.CUSTOMERNO = t; }
                void            SetProcessno(long t) { s.PROCESSNO = t; }
                void            SetCustomerorderno(const ppString& t) { ppGStrCopy(s.CUSTOMERORDERNO,t.c_str() ,L_CUSTOMERORDERNO_CUSTOMERORDERNO); }
                void            SetOrdervalue(double t) { s.ORDERVALUE = t; }
                void            SetStruct(const customerordernoS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CCUSTOMERORDERNO()  //constructor
                {
                        ::buf_default((void *)&s, CUSTOMERORDERNO_BES, CUSTOMERORDERNO_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CCUSTOMERORDERNO()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, CUSTOMERORDERNO_BES, CUSTOMERORDERNO_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CUSTOMERORDERNO_BES, CUSTOMERORDERNO_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, CUSTOMERORDERNO_BES, CUSTOMERORDERNO_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_CUSTOMERORDERNO& d)
                {
#ifdef WIN32
                        ppGStripLast(d.CUSTOMERORDERNO);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTOMERORDERNO_BES, CUSTOMERORDERNO_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of CUSTOMERORDERNO **************************************/

 #define CUSTOMERORDERNO_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         PROCESSNO integer default 0 not null,\
         CUSTOMERORDERNO char(30) default " " not null,\
         ORDERVALUE double) in ksc extent size 48 next size 8 lock mode row;



/* CreateIndexStatement of CUSTOMERORDERNO ************************************/

 #define CUSTOMERORDERNO_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_custorderno_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              CustomerOrderNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CUSTOMERORDERNO ************************************/

 #define CUSTOMERORDERNO_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_custorderno_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
