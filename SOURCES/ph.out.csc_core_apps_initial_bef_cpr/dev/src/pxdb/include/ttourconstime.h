#ifndef __PP_TOURCONSTIME_H_
#define __PP_TOURCONSTIME_H_

/******************************************************************************/
/* v:\TourConsTime ************************************************************/
/******************************************************************************/

/* Length-Define of TOURCONSTIME **********************************************/

  #define L_TOURCONSTIME_FILIALNR 6
  #define L_TOURCONSTIME_TOURID 6
  #define L_TOURCONSTIME_DATUMKOMMI 11
  #define L_TOURCONSTIME_CONSTIME 11
  #define L_TOURCONSTIME_PROCESSSTATE 1

/* Length/Count-Define of TOURCONSTIME ****************************************/

  #define LS_TOURCONSTIME_FILIALNR 5 + 1
  #define LS_TOURCONSTIME_TOURID 6 + 1
  #define LS_TOURCONSTIME_DATUMKOMMI 10 + 1
  #define LS_TOURCONSTIME_CONSTIME 10 + 1
  #define LS_TOURCONSTIME_PROCESSSTATE 1 + 1

  #define TOURCONSTIMEFILIALNR 0
  #define TOURCONSTIMETOURID 1
  #define TOURCONSTIMEDATUMKOMMI 2
  #define TOURCONSTIMECONSTIME 3
  #define TOURCONSTIMEPROCESSSTATE 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define TOURCONSTIME_H
 #define TOURCONSTIME_ANZ ( sizeof(TOURCONSTIME_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TOURCONSTIME **************************************************/

 #define TOURCONSTIME_LISTE \
         TOURCONSTIME.FILIALNR,\
         TOURCONSTIME.TOURID,\
         TOURCONSTIME.DATUMKOMMI,\
         TOURCONSTIME.CONSTIME,\
         TOURCONSTIME.PROCESSSTATE

 #define TOURCONSTIME_LISTE_390 \
         FILIALNR,\
         TOURID,\
         DATUMKOMMI,\
         CONSTIME,\
         PROCESSSTATE

 #define TOURCONSTIME_PLISTE \
         "TOURCONSTIME.FILIALNR,"\
         "TOURCONSTIME.TOURID,"\
         "TOURCONSTIME.DATUMKOMMI,"\
         "TOURCONSTIME.CONSTIME,"\
         "TOURCONSTIME.PROCESSSTATE"

 #define TOURCONSTIME_PELISTE \
         "FILIALNR,"\
         "TOURID,"\
         "DATUMKOMMI,"\
         "CONSTIME,"\
         "PROCESSSTATE"

 #define TOURCONSTIME_UPDLISTE \
         "FILIALNR=?,"\
         "TOURID=?,"\
         "DATUMKOMMI=?,"\
         "CONSTIME=?,"\
         "PROCESSSTATE=?"

/* SqlMacros-Define of TOURCONSTIME *******************************************/

 #define TOURCONSTIME_ZEIGER(x) \
         :x->FILIALNR,\
         :x->TOURID,\
         :x->DATUMKOMMI,\
         :x->CONSTIME,\
         :x->PROCESSSTATE

 #define TOURCONSTIME_ZEIGERSEL(x) \
         :x->FILIALNR,\
         :x->TOURID,\
         :x->DATUMKOMMI,\
         :x->CONSTIME,\
         :x->PROCESSSTATE

 #define TOURCONSTIME_UPDATE(x) \
         TOURCONSTIME.FILIALNR=:x->FILIALNR,\
         TOURCONSTIME.TOURID=:x->TOURID,\
         TOURCONSTIME.DATUMKOMMI=:x->DATUMKOMMI,\
         TOURCONSTIME.CONSTIME=:x->CONSTIME,\
         TOURCONSTIME.PROCESSSTATE=:x->PROCESSSTATE

/* SqlMacros390-Define of TOURCONSTIME ****************************************/

 #define TOURCONSTIME_ZEIGER_390 \
         :FILIALNR,\
         :TOURID,\
         :DATUMKOMMI,\
         :CONSTIME,\
         :PROCESSSTATE

 #define TOURCONSTIME_UPDATE_390 \
         FILIALNR=:FILIALNR,\
         TOURID=:TOURID,\
         DATUMKOMMI=:DATUMKOMMI,\
         CONSTIME=:CONSTIME,\
         PROCESSSTATE=:PROCESSSTATE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of TOURCONSTIME *******************************************/

 #ifndef TRANSCLASS
 typedef struct N_TOURCONSTIME {
         short FILIALNR;
         char TOURID[7];
         long DATUMKOMMI;
         long CONSTIME;
         char PROCESSSTATE[2];
        } tourconstimeS;
 #else /*TRANSCLASS*/
 typedef struct N_TOURCONSTIME {
         short FILIALNR;
         char TOURID[7];
         long DATUMKOMMI;
         long CONSTIME;
         char PROCESSSTATE[2];

                        bool operator==(const N_TOURCONSTIME& right) const {
                        return(
                                FILIALNR == right.FILIALNR &&
                                !strcmp(TOURID, right.TOURID) &&
                                DATUMKOMMI == right.DATUMKOMMI &&
                                CONSTIME == right.CONSTIME &&
                                !strcmp(PROCESSSTATE, right.PROCESSSTATE)
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                FILIALNR = 0;
                                strcpy(TOURID, " " );
                                DATUMKOMMI = 0;
                                CONSTIME = 0;
                                strcpy(PROCESSSTATE, " " );
#endif
                        }
         } tourconstimeS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TOURCONSTIME **************************************/

 struct S_TOURCONSTIME {
         char FILIALNR[7];
         char TOURID[6 + 1];
         char DATUMKOMMI[11];
         char CONSTIME[11];
         char PROCESSSTATE[1 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of TOURCONSTIME *********************/

 struct O_TOURCONSTIME {
         char FILIALNR[7];
         char TOURID[6];
         char DATUMKOMMI[11];
         char CONSTIME[11];
         char PROCESSSTATE[1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of TOURCONSTIME ********************************/

 struct C_TOURCONSTIME {
         short FILIALNR;
         char TOURID[7];
         long DATUMKOMMI;
         long CONSTIME;
         char PROCESSSTATE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of TOURCONSTIME ******************************/

 struct I_TOURCONSTIME {
         short FILIALNR;
         short TOURID;
         short DATUMKOMMI;
         short CONSTIME;
         short PROCESSSTATE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TOURCONSTIME ****************************************/

#if defined (BUF_DESC)
 static struct buf_desc TOURCONSTIME_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc TOURCONSTIME_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#endif

/* description for datatypes of TOURCONSTIME **********************************/

 #define TOURCONSTIME_S390 \
         short FILIALNR; \
         char TOURID[7]; \
         long DATUMKOMMI; \
         long CONSTIME; \
         char PROCESSSTATE; \



/* Copy-Function Struct to single Data TOURCONSTIME ***************************/

 #define TOURCONSTIME_S390_COPY_TO_SINGLE(_x_) \
         FILIALNR=_x_->FILIALNR;\
          strcpy(TOURID,_x_->TOURID);\
         DATUMKOMMI=_x_->DATUMKOMMI;\
         CONSTIME=_x_->CONSTIME;\
         PROCESSSTATE=_x_->PROCESSSTATE;\

 #define TOURCONSTIME_S390_COPY_TO_STRUCT(_x_) \
          _x_->FILIALNR=FILIALNR;\
          strcpy(_x_->TOURID,TOURID);\
          _x_->DATUMKOMMI=DATUMKOMMI;\
          _x_->CONSTIME=CONSTIME;\
          _x_->PROCESSSTATE=PROCESSSTATE;\



/* FunctionNumber-Define of TourConsTime **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of TourConsTime **********************************/


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

class CTOURCONSTIME : public ppDadeVirtual
{
        //data members
        public:
                tourconstimeS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<tourconstimeS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<tourconstimeS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<tourconstimeS>; Strip(s); tourconstimeS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<tourconstimeS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<tourconstimeS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<tourconstimeS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetFilialnr() const     { return s.FILIALNR; }
                const char*     GetTourid(ppString& t) const    { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
                long            GetDatumkommi() const   { return s.DATUMKOMMI; }
                long            GetConstime() const     { return s.CONSTIME; }
                char            GetProcessstate() const { return s.PROCESSSTATE[0]; }
                const tourconstimeS& GetStruct() const { return s; }
                void            SetFilialnr(short t) { s.FILIALNR = t; }
                void            SetTourid(const ppString& t) { ppGStrCopy(s.TOURID,t.c_str() ,L_TOURCONSTIME_TOURID); }
                void            SetDatumkommi(long t) { s.DATUMKOMMI = t; }
                void            SetConstime(long t) { s.CONSTIME = t; }
                void            SetProcessstate(char t) { s.PROCESSSTATE[0] = t; s.PROCESSSTATE[1] = '\0';}
                void            SetStruct(const tourconstimeS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CTOURCONSTIME()  //constructor
                {
                        ::buf_default((void *)&s, TOURCONSTIME_BES, TOURCONSTIME_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CTOURCONSTIME()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, TOURCONSTIME_BES, TOURCONSTIME_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, TOURCONSTIME_BES, TOURCONSTIME_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, TOURCONSTIME_BES, TOURCONSTIME_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_TOURCONSTIME& d)
                {
#ifdef WIN32
                        ppGStripLast(d.TOURID);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, TOURCONSTIME_BES, TOURCONSTIME_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of TOURCONSTIME *****************************************/

 #define TOURCONSTIME_CREATE(x) exec sql create table x (\
         FILIALNR smallint default 0 not null,\
         TOURID char(6) default " " not null,\
         DATUMKOMMI integer default 0 not null,\
         CONSTIME integer default 0 not null,\
         PROCESSSTATE char(1) default " " not null) in ksc extent size 80 next size 8 lock mode row;



/* CreateIndexStatement of TOURCONSTIME ***************************************/

 #define TOURCONSTIME_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_tourcons_1 on _X_(\
              filialnr,\
              tourid,\
              datumkommi ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TOURCONSTIME ***************************************/

 #define TOURCONSTIME_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_tourcons_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
