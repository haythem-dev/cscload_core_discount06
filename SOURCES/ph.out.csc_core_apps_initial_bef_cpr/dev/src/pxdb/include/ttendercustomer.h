#ifndef __PP_TENDERCUSTOMER_H_
#define __PP_TENDERCUSTOMER_H_

/******************************************************************************/
/* u:\TenderCustomer **********************************************************/
/******************************************************************************/

/* Length-Define of TENDERCUSTOMER ********************************************/

  #define L_TENDERCUSTOMER_TENDERNO 11
  #define L_TENDERCUSTOMER_BRANCHNO 6
  #define L_TENDERCUSTOMER_CUSTOMERNO 11

/* Length/Count-Define of TENDERCUSTOMER **************************************/

  #define LS_TENDERCUSTOMER_TENDERNO 10 + 1
  #define LS_TENDERCUSTOMER_BRANCHNO 5 + 1
  #define LS_TENDERCUSTOMER_CUSTOMERNO 10 + 1

  #define TENDERCUSTOMERTENDERNO 0
  #define TENDERCUSTOMERBRANCHNO 1
  #define TENDERCUSTOMERCUSTOMERNO 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define TENDERCUSTOMER_H
 #define TENDERCUSTOMER_ANZ ( sizeof(TENDERCUSTOMER_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TENDERCUSTOMER ************************************************/

 #define TENDERCUSTOMER_LISTE \
         TENDERCUSTOMER.TENDERNO,\
         TENDERCUSTOMER.BRANCHNO,\
         TENDERCUSTOMER.CUSTOMERNO

 #define TENDERCUSTOMER_LISTE_390 \
         TENDERNO,\
         BRANCHNO,\
         CUSTOMERNO

 #define TENDERCUSTOMER_PLISTE \
         "TENDERCUSTOMER.TENDERNO,"\
         "TENDERCUSTOMER.BRANCHNO,"\
         "TENDERCUSTOMER.CUSTOMERNO"

 #define TENDERCUSTOMER_PELISTE \
         "TENDERNO,"\
         "BRANCHNO,"\
         "CUSTOMERNO"

 #define TENDERCUSTOMER_UPDLISTE \
         "TENDERNO=?,"\
         "BRANCHNO=?,"\
         "CUSTOMERNO=?"

/* SqlMacros-Define of TENDERCUSTOMER *****************************************/

 #define TENDERCUSTOMER_ZEIGER(x) \
         :x->TENDERNO,\
         :x->BRANCHNO,\
         :x->CUSTOMERNO

 #define TENDERCUSTOMER_ZEIGERSEL(x) \
         :x->TENDERNO,\
         :x->BRANCHNO,\
         :x->CUSTOMERNO

 #define TENDERCUSTOMER_UPDATE(x) \
         TENDERCUSTOMER.TENDERNO=:x->TENDERNO,\
         TENDERCUSTOMER.BRANCHNO=:x->BRANCHNO,\
         TENDERCUSTOMER.CUSTOMERNO=:x->CUSTOMERNO

/* SqlMacros390-Define of TENDERCUSTOMER **************************************/

 #define TENDERCUSTOMER_ZEIGER_390 \
         :TENDERNO,\
         :BRANCHNO,\
         :CUSTOMERNO

 #define TENDERCUSTOMER_UPDATE_390 \
         TENDERNO=:TENDERNO,\
         BRANCHNO=:BRANCHNO,\
         CUSTOMERNO=:CUSTOMERNO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of TENDERCUSTOMER *****************************************/

 #ifndef TRANSCLASS
 typedef struct N_TENDERCUSTOMER {
         long TENDERNO;
         short BRANCHNO;
         long CUSTOMERNO;
        } tendercustomerS;
 #else /*TRANSCLASS*/
 typedef struct N_TENDERCUSTOMER {
         long TENDERNO;
         short BRANCHNO;
         long CUSTOMERNO;

                        bool operator==(const N_TENDERCUSTOMER& right) const {
                        return(
                                TENDERNO == right.TENDERNO &&
                                BRANCHNO == right.BRANCHNO &&
                                CUSTOMERNO == right.CUSTOMERNO
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                TENDERNO = 0;
                                BRANCHNO = 0;
                                CUSTOMERNO = 0;
#endif
                        }
         } tendercustomerS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TENDERCUSTOMER ************************************/

 struct S_TENDERCUSTOMER {
         char TENDERNO[11];
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of TENDERCUSTOMER *******************/

 struct O_TENDERCUSTOMER {
         char TENDERNO[11];
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of TENDERCUSTOMER ******************************/

 struct C_TENDERCUSTOMER {
         long TENDERNO;
         short BRANCHNO;
         long CUSTOMERNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of TENDERCUSTOMER ****************************/

 struct I_TENDERCUSTOMER {
         short TENDERNO;
         short BRANCHNO;
         short CUSTOMERNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TENDERCUSTOMER **************************************/

#if defined (BUF_DESC)
 static struct buf_desc TENDERCUSTOMER_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc TENDERCUSTOMER_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of TENDERCUSTOMER ********************************/

 #define TENDERCUSTOMER_S390 \
         long TENDERNO; \
         short BRANCHNO; \
         long CUSTOMERNO; \



/* Copy-Function Struct to single Data TENDERCUSTOMER *************************/

 #define TENDERCUSTOMER_S390_COPY_TO_SINGLE(_x_) \
         TENDERNO=_x_->TENDERNO;\
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\

 #define TENDERCUSTOMER_S390_COPY_TO_STRUCT(_x_) \
          _x_->TENDERNO=TENDERNO;\
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\



/* FunctionNumber-Define of TenderCustomer ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of TenderCustomer ********************************/


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

class CTENDERCUSTOMER : public ppDadeVirtual
{
        //data members
        public:
                tendercustomerS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<tendercustomerS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<tendercustomerS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<tendercustomerS>; Strip(s); tendercustomerS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<tendercustomerS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<tendercustomerS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<tendercustomerS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetTenderno() const     { return s.TENDERNO; }
                short           GetBranchno() const     { return s.BRANCHNO; }
                long            GetCustomerno() const   { return s.CUSTOMERNO; }
                const tendercustomerS& GetStruct() const { return s; }
                void            SetTenderno(long t) { s.TENDERNO = t; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetCustomerno(long t) { s.CUSTOMERNO = t; }
                void            SetStruct(const tendercustomerS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CTENDERCUSTOMER()  //constructor
                {
                        ::buf_default((void *)&s, TENDERCUSTOMER_BES, TENDERCUSTOMER_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CTENDERCUSTOMER()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, TENDERCUSTOMER_BES, TENDERCUSTOMER_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, TENDERCUSTOMER_BES, TENDERCUSTOMER_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, TENDERCUSTOMER_BES, TENDERCUSTOMER_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_TENDERCUSTOMER& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, TENDERCUSTOMER_BES, TENDERCUSTOMER_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of TENDERCUSTOMER ***************************************/

 #define TENDERCUSTOMER_CREATE(x) exec sql create table x (\
         TENDERNO integer default 0 not null,\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of TENDERCUSTOMER *************************************/

 #define TENDERCUSTOMER_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_tendercustomer_1 on _X_(\
              TenderNo,\
              BranchNo,\
              CustomerNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_tendercustomer_2 on _X_(\
              BranchNo,\
              CustomerNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TENDERCUSTOMER *************************************/

 #define TENDERCUSTOMER_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_tendercustomer_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_tendercustomer_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
