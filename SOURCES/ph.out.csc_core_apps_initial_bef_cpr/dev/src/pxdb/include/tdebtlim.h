#ifndef __PP_DEBTLIMIT_H_
#define __PP_DEBTLIMIT_H_

/******************************************************************************/
/* u:\debtlimit ***************************************************************/
/******************************************************************************/

/* Length-Define of DEBTLIMIT *************************************************/

  #define L_DEBTLIMIT_PARTNERNO 11
  #define L_DEBTLIMIT_PARTNERNAME 30
  #define L_DEBTLIMIT_LIMIT 13
  #define N_DEBTLIMIT_LIMIT 2
  #define L_DEBTLIMIT_SUM_DEBITSIDE 13
  #define N_DEBTLIMIT_SUM_DEBITSIDE 2
  #define L_DEBTLIMIT_SUM_CREDITSIDE 13
  #define N_DEBTLIMIT_SUM_CREDITSIDE 2
  #define L_DEBTLIMIT_SUM_MONTURNOVER 13
  #define N_DEBTLIMIT_SUM_MONTURNOVER 2
  #define L_DEBTLIMIT_SUM_DAYTURNOVER 13
  #define N_DEBTLIMIT_SUM_DAYTURNOVER 2
  #define L_DEBTLIMIT_SUM_RETURNS 13
  #define N_DEBTLIMIT_SUM_RETURNS 2
  #define L_DEBTLIMIT_SUM_GOODSRECEIPT 13
  #define N_DEBTLIMIT_SUM_GOODSRECEIPT 2
  #define L_DEBTLIMIT_LIMITTYPE 6
  #define L_DEBTLIMIT_LISTE5 1

/* Length/Count-Define of DEBTLIMIT *******************************************/

  #define LS_DEBTLIMIT_PARTNERNO 10 + 1
  #define LS_DEBTLIMIT_PARTNERNAME 30 + 1
  #define LS_DEBTLIMIT_LIMIT 13 + 2
  #define LS_DEBTLIMIT_SUM_DEBITSIDE 13 + 2
  #define LS_DEBTLIMIT_SUM_CREDITSIDE 13 + 2
  #define LS_DEBTLIMIT_SUM_MONTURNOVER 13 + 2
  #define LS_DEBTLIMIT_SUM_DAYTURNOVER 13 + 2
  #define LS_DEBTLIMIT_SUM_RETURNS 13 + 2
  #define LS_DEBTLIMIT_SUM_GOODSRECEIPT 13 + 2
  #define LS_DEBTLIMIT_LIMITTYPE 5 + 1
  #define LS_DEBTLIMIT_LISTE5 1 + 1

  #define DEBTLIMITPARTNERNO 0
  #define DEBTLIMITPARTNERNAME 1
  #define DEBTLIMITLIMIT 2
  #define DEBTLIMITSUM_DEBITSIDE 3
  #define DEBTLIMITSUM_CREDITSIDE 4
  #define DEBTLIMITSUM_MONTURNOVER 5
  #define DEBTLIMITSUM_DAYTURNOVER 6
  #define DEBTLIMITSUM_RETURNS 7
  #define DEBTLIMITSUM_GOODSRECEIPT 8
  #define DEBTLIMITLIMITTYPE 9
  #define DEBTLIMITLISTE5 10

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define DEBTLIMIT_H
 #define DEBTLIMIT_ANZ ( sizeof(DEBTLIMIT_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DEBTLIMIT *****************************************************/

 #define DEBTLIMIT_LISTE \
         DEBTLIMIT.PARTNERNO,\
         DEBTLIMIT.PARTNERNAME,\
         DEBTLIMIT.LIMIT,\
         DEBTLIMIT.SUM_DEBITSIDE,\
         DEBTLIMIT.SUM_CREDITSIDE,\
         DEBTLIMIT.SUM_MONTURNOVER,\
         DEBTLIMIT.SUM_DAYTURNOVER,\
         DEBTLIMIT.SUM_RETURNS,\
         DEBTLIMIT.SUM_GOODSRECEIPT,\
         DEBTLIMIT.LIMITTYPE,\
         DEBTLIMIT.LISTE5

 #define DEBTLIMIT_LISTE_390 \
         PARTNERNO,\
         PARTNERNAME,\
         LIMIT,\
         SUM_DEBITSIDE,\
         SUM_CREDITSIDE,\
         SUM_MONTURNOVER,\
         SUM_DAYTURNOVER,\
         SUM_RETURNS,\
         SUM_GOODSRECEIPT,\
         LIMITTYPE,\
         LISTE5

 #define DEBTLIMIT_PLISTE \
         "DEBTLIMIT.PARTNERNO,"\
         "DEBTLIMIT.PARTNERNAME,"\
         "DEBTLIMIT.LIMIT,"\
         "DEBTLIMIT.SUM_DEBITSIDE,"\
         "DEBTLIMIT.SUM_CREDITSIDE,"\
         "DEBTLIMIT.SUM_MONTURNOVER,"\
         "DEBTLIMIT.SUM_DAYTURNOVER,"\
         "DEBTLIMIT.SUM_RETURNS,"\
         "DEBTLIMIT.SUM_GOODSRECEIPT,"\
         "DEBTLIMIT.LIMITTYPE,"\
         "DEBTLIMIT.LISTE5"

 #define DEBTLIMIT_PELISTE \
         "PARTNERNO,"\
         "PARTNERNAME,"\
         "LIMIT,"\
         "SUM_DEBITSIDE,"\
         "SUM_CREDITSIDE,"\
         "SUM_MONTURNOVER,"\
         "SUM_DAYTURNOVER,"\
         "SUM_RETURNS,"\
         "SUM_GOODSRECEIPT,"\
         "LIMITTYPE,"\
         "LISTE5"

 #define DEBTLIMIT_UPDLISTE \
         "PARTNERNO=?,"\
         "PARTNERNAME=?,"\
         "LIMIT=?,"\
         "SUM_DEBITSIDE=?,"\
         "SUM_CREDITSIDE=?,"\
         "SUM_MONTURNOVER=?,"\
         "SUM_DAYTURNOVER=?,"\
         "SUM_RETURNS=?,"\
         "SUM_GOODSRECEIPT=?,"\
         "LIMITTYPE=?,"\
         "LISTE5=?"

/* SqlMacros-Define of DEBTLIMIT **********************************************/

 #define DEBTLIMIT_ZEIGER(x) \
         :x->PARTNERNO,\
         :x->PARTNERNAME,\
         :x->LIMIT,\
         :x->SUM_DEBITSIDE,\
         :x->SUM_CREDITSIDE,\
         :x->SUM_MONTURNOVER,\
         :x->SUM_DAYTURNOVER,\
         :x->SUM_RETURNS,\
         :x->SUM_GOODSRECEIPT,\
         :x->LIMITTYPE,\
         :x->LISTE5

 #define DEBTLIMIT_ZEIGERSEL(x) \
         :x->PARTNERNO,\
         :x->PARTNERNAME,\
         :x->LIMIT,\
         :x->SUM_DEBITSIDE,\
         :x->SUM_CREDITSIDE,\
         :x->SUM_MONTURNOVER,\
         :x->SUM_DAYTURNOVER,\
         :x->SUM_RETURNS,\
         :x->SUM_GOODSRECEIPT,\
         :x->LIMITTYPE,\
         :x->LISTE5

 #define DEBTLIMIT_UPDATE(x) \
         DEBTLIMIT.PARTNERNO=:x->PARTNERNO,\
         DEBTLIMIT.PARTNERNAME=:x->PARTNERNAME,\
         DEBTLIMIT.LIMIT=:x->LIMIT,\
         DEBTLIMIT.SUM_DEBITSIDE=:x->SUM_DEBITSIDE,\
         DEBTLIMIT.SUM_CREDITSIDE=:x->SUM_CREDITSIDE,\
         DEBTLIMIT.SUM_MONTURNOVER=:x->SUM_MONTURNOVER,\
         DEBTLIMIT.SUM_DAYTURNOVER=:x->SUM_DAYTURNOVER,\
         DEBTLIMIT.SUM_RETURNS=:x->SUM_RETURNS,\
         DEBTLIMIT.SUM_GOODSRECEIPT=:x->SUM_GOODSRECEIPT,\
         DEBTLIMIT.LIMITTYPE=:x->LIMITTYPE,\
         DEBTLIMIT.LISTE5=:x->LISTE5

/* SqlMacros390-Define of DEBTLIMIT *******************************************/

 #define DEBTLIMIT_ZEIGER_390 \
         :PARTNERNO,\
         :PARTNERNAME,\
         :LIMIT,\
         :SUM_DEBITSIDE,\
         :SUM_CREDITSIDE,\
         :SUM_MONTURNOVER,\
         :SUM_DAYTURNOVER,\
         :SUM_RETURNS,\
         :SUM_GOODSRECEIPT,\
         :LIMITTYPE,\
         :LISTE5

 #define DEBTLIMIT_UPDATE_390 \
         PARTNERNO=:PARTNERNO,\
         PARTNERNAME=:PARTNERNAME,\
         LIMIT=:LIMIT,\
         SUM_DEBITSIDE=:SUM_DEBITSIDE,\
         SUM_CREDITSIDE=:SUM_CREDITSIDE,\
         SUM_MONTURNOVER=:SUM_MONTURNOVER,\
         SUM_DAYTURNOVER=:SUM_DAYTURNOVER,\
         SUM_RETURNS=:SUM_RETURNS,\
         SUM_GOODSRECEIPT=:SUM_GOODSRECEIPT,\
         LIMITTYPE=:LIMITTYPE,\
         LISTE5=:LISTE5

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of DEBTLIMIT **********************************************/

 #ifndef TRANSCLASS
 typedef struct N_DEBTLIMIT {
         long PARTNERNO;
         char PARTNERNAME[31];
         double LIMIT;
         double SUM_DEBITSIDE;
         double SUM_CREDITSIDE;
         double SUM_MONTURNOVER;
         double SUM_DAYTURNOVER;
         double SUM_RETURNS;
         double SUM_GOODSRECEIPT;
         short LIMITTYPE;
         char LISTE5[2];
        } debtlimitS;
 #else /*TRANSCLASS*/
 typedef struct N_DEBTLIMIT {
         long PARTNERNO;
         char PARTNERNAME[31];
         double LIMIT;
         double SUM_DEBITSIDE;
         double SUM_CREDITSIDE;
         double SUM_MONTURNOVER;
         double SUM_DAYTURNOVER;
         double SUM_RETURNS;
         double SUM_GOODSRECEIPT;
         short LIMITTYPE;
         char LISTE5[2];

                        bool operator==(const N_DEBTLIMIT& right) const {
                        return(
                                PARTNERNO == right.PARTNERNO &&
                                !strcmp(PARTNERNAME, right.PARTNERNAME) &&
                                LIMIT == right.LIMIT &&
                                SUM_DEBITSIDE == right.SUM_DEBITSIDE &&
                                SUM_CREDITSIDE == right.SUM_CREDITSIDE &&
                                SUM_MONTURNOVER == right.SUM_MONTURNOVER &&
                                SUM_DAYTURNOVER == right.SUM_DAYTURNOVER &&
                                SUM_RETURNS == right.SUM_RETURNS &&
                                SUM_GOODSRECEIPT == right.SUM_GOODSRECEIPT &&
                                LIMITTYPE == right.LIMITTYPE &&
                                !strcmp(LISTE5, right.LISTE5)
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                PARTNERNO = 0;
                                strcpy(PARTNERNAME, " " );
                                LIMIT = 0;
                                SUM_DEBITSIDE = 0;
                                SUM_CREDITSIDE = 0;
                                SUM_MONTURNOVER = 0;
                                SUM_DAYTURNOVER = 0;
                                SUM_RETURNS = 0;
                                SUM_GOODSRECEIPT = 0;
                                LIMITTYPE = 0;
                                strcpy(LISTE5, " " );
#endif
                        }
         } debtlimitS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DEBTLIMIT *****************************************/

 struct S_DEBTLIMIT {
         char PARTNERNO[11];
         char PARTNERNAME[30 + 1];
         char LIMIT[13 + 2];
         char SUM_DEBITSIDE[13 + 2];
         char SUM_CREDITSIDE[13 + 2];
         char SUM_MONTURNOVER[13 + 2];
         char SUM_DAYTURNOVER[13 + 2];
         char SUM_RETURNS[13 + 2];
         char SUM_GOODSRECEIPT[13 + 2];
         char LIMITTYPE[7];
         char LISTE5[1 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DEBTLIMIT ************************/

 struct O_DEBTLIMIT {
         char PARTNERNO[11];
         char PARTNERNAME[30];
         char LIMIT[13];
         char SUM_DEBITSIDE[13];
         char SUM_CREDITSIDE[13];
         char SUM_MONTURNOVER[13];
         char SUM_DAYTURNOVER[13];
         char SUM_RETURNS[13];
         char SUM_GOODSRECEIPT[13];
         char LIMITTYPE[7];
         char LISTE5[1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DEBTLIMIT ***********************************/

 struct C_DEBTLIMIT {
         long PARTNERNO;
         char PARTNERNAME[31];
         double LIMIT;
         double SUM_DEBITSIDE;
         double SUM_CREDITSIDE;
         double SUM_MONTURNOVER;
         double SUM_DAYTURNOVER;
         double SUM_RETURNS;
         double SUM_GOODSRECEIPT;
         short LIMITTYPE;
         char LISTE5;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DEBTLIMIT *********************************/

 struct I_DEBTLIMIT {
         short PARTNERNO;
         short PARTNERNAME;
         short LIMIT;
         short SUM_DEBITSIDE;
         short SUM_CREDITSIDE;
         short SUM_MONTURNOVER;
         short SUM_DAYTURNOVER;
         short SUM_RETURNS;
         short SUM_GOODSRECEIPT;
         short LIMITTYPE;
         short LISTE5;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DEBTLIMIT *******************************************/

#if defined (BUF_DESC)
 static struct buf_desc DEBTLIMIT_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEBTLIMIT_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_D, 13, 2 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
 };
#endif

/* description for datatypes of DEBTLIMIT *************************************/

 #define DEBTLIMIT_S390 \
         long PARTNERNO; \
         char PARTNERNAME[31]; \
         double LIMIT; \
         double SUM_DEBITSIDE; \
         double SUM_CREDITSIDE; \
         double SUM_MONTURNOVER; \
         double SUM_DAYTURNOVER; \
         double SUM_RETURNS; \
         double SUM_GOODSRECEIPT; \
         short LIMITTYPE; \
         char LISTE5; \



/* Copy-Function Struct to single Data DEBTLIMIT ******************************/

 #define DEBTLIMIT_S390_COPY_TO_SINGLE(_x_) \
         PARTNERNO=_x_->PARTNERNO;\
          strcpy(PARTNERNAME,_x_->PARTNERNAME);\
         LIMIT=_x_->LIMIT;\
         SUM_DEBITSIDE=_x_->SUM_DEBITSIDE;\
         SUM_CREDITSIDE=_x_->SUM_CREDITSIDE;\
         SUM_MONTURNOVER=_x_->SUM_MONTURNOVER;\
         SUM_DAYTURNOVER=_x_->SUM_DAYTURNOVER;\
         SUM_RETURNS=_x_->SUM_RETURNS;\
         SUM_GOODSRECEIPT=_x_->SUM_GOODSRECEIPT;\
         LIMITTYPE=_x_->LIMITTYPE;\
         LISTE5=_x_->LISTE5;\

 #define DEBTLIMIT_S390_COPY_TO_STRUCT(_x_) \
          _x_->PARTNERNO=PARTNERNO;\
          strcpy(_x_->PARTNERNAME,PARTNERNAME);\
          _x_->LIMIT=LIMIT;\
          _x_->SUM_DEBITSIDE=SUM_DEBITSIDE;\
          _x_->SUM_CREDITSIDE=SUM_CREDITSIDE;\
          _x_->SUM_MONTURNOVER=SUM_MONTURNOVER;\
          _x_->SUM_DAYTURNOVER=SUM_DAYTURNOVER;\
          _x_->SUM_RETURNS=SUM_RETURNS;\
          _x_->SUM_GOODSRECEIPT=SUM_GOODSRECEIPT;\
          _x_->LIMITTYPE=LIMITTYPE;\
          _x_->LISTE5=LISTE5;\



/* FunctionNumber-Define of debtlimit *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of debtlimit *************************************/


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

class CDEBTLIMIT : public ppDadeVirtual
{
        //data members
        public:
                debtlimitS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<debtlimitS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<debtlimitS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<debtlimitS>; Strip(s); debtlimitS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<debtlimitS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<debtlimitS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<debtlimitS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetPartnerno() const    { return s.PARTNERNO; }
                const char*     GetPartnername(ppString& t) const       { t = s.PARTNERNAME; t.erasespace(ppString::END); return t.c_str(); }
                double          GetLimit() const        { return s.LIMIT; }
                double          GetSum_debitside() const        { return s.SUM_DEBITSIDE; }
                double          GetSum_creditside() const       { return s.SUM_CREDITSIDE; }
                double          GetSum_monturnover() const      { return s.SUM_MONTURNOVER; }
                double          GetSum_dayturnover() const      { return s.SUM_DAYTURNOVER; }
                double          GetSum_returns() const  { return s.SUM_RETURNS; }
                double          GetSum_goodsreceipt() const     { return s.SUM_GOODSRECEIPT; }
                short           GetLimittype() const    { return s.LIMITTYPE; }
                char            GetListe5() const       { return s.LISTE5[0]; }
                const debtlimitS& GetStruct() const { return s; }
                void            SetPartnerno(long t) { s.PARTNERNO = t; }
                void            SetPartnername(const ppString& t) { ppGStrCopy(s.PARTNERNAME,t.c_str() ,L_DEBTLIMIT_PARTNERNAME); }
                void            SetLimit(double t) { s.LIMIT = t; }
                void            SetSum_debitside(double t) { s.SUM_DEBITSIDE = t; }
                void            SetSum_creditside(double t) { s.SUM_CREDITSIDE = t; }
                void            SetSum_monturnover(double t) { s.SUM_MONTURNOVER = t; }
                void            SetSum_dayturnover(double t) { s.SUM_DAYTURNOVER = t; }
                void            SetSum_returns(double t) { s.SUM_RETURNS = t; }
                void            SetSum_goodsreceipt(double t) { s.SUM_GOODSRECEIPT = t; }
                void            SetLimittype(short t) { s.LIMITTYPE = t; }
                void            SetListe5(char t) { s.LISTE5[0] = t; s.LISTE5[1] = '\0';}
                void            SetStruct(const debtlimitS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CDEBTLIMIT()  //constructor
                {
                        ::buf_default((void *)&s, DEBTLIMIT_BES, DEBTLIMIT_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CDEBTLIMIT()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, DEBTLIMIT_BES, DEBTLIMIT_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DEBTLIMIT_BES, DEBTLIMIT_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, DEBTLIMIT_BES, DEBTLIMIT_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_DEBTLIMIT& d)
                {
#ifdef WIN32
                        ppGStripLast(d.PARTNERNAME);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, DEBTLIMIT_BES, DEBTLIMIT_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of DEBTLIMIT ********************************************/

 #define DEBTLIMIT_CREATE(x) exec sql create table x (\
         PARTNERNO integer default 0 not null,\
         PARTNERNAME char(30) default " " not null,\
         LIMIT decimal(13,2) default 0 not null,\
         SUM_DEBITSIDE decimal(13,2) default 0 not null,\
         SUM_CREDITSIDE decimal(13,2) default 0 not null,\
         SUM_MONTURNOVER decimal(13,2) default 0 not null,\
         SUM_DAYTURNOVER decimal(13,2) default 0 not null,\
         SUM_RETURNS decimal(13,2) default 0 not null,\
         SUM_GOODSRECEIPT decimal(13,2) default 0 not null,\
         LIMITTYPE smallint default 0 not null,\
         LISTE5 char(1) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of DEBTLIMIT ******************************************/

 #define DEBTLIMIT_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_debtlimit_1 on _X_(\
              partnerno ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of DEBTLIMIT ******************************************/

 #define DEBTLIMIT_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_debtlimit_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
