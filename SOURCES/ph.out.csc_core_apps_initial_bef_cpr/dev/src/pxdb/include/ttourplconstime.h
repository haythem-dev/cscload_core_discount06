#ifndef __PP_TOURPLANCONSTIME_H_
#define __PP_TOURPLANCONSTIME_H_

/******************************************************************************/
/* v:\TourplanConsTime ********************************************************/
/******************************************************************************/

/* Length-Define of TOURPLANCONSTIME ******************************************/

  #define L_TOURPLANCONSTIME_VERTRIEBSZENTRUMNR 6
  #define L_TOURPLANCONSTIME_KUNDENNR 11
  #define L_TOURPLANCONSTIME_TOURID 6
  #define L_TOURPLANCONSTIME_DATUMKOMMI 11
  #define L_TOURPLANCONSTIME_CONSTIME 11
  #define L_TOURPLANCONSTIME_PROCESSSTATE 1

/* Length/Count-Define of TOURPLANCONSTIME ************************************/

  #define LS_TOURPLANCONSTIME_VERTRIEBSZENTRUMNR 5 + 1
  #define LS_TOURPLANCONSTIME_KUNDENNR 10 + 1
  #define LS_TOURPLANCONSTIME_TOURID 6 + 1
  #define LS_TOURPLANCONSTIME_DATUMKOMMI 10 + 1
  #define LS_TOURPLANCONSTIME_CONSTIME 10 + 1
  #define LS_TOURPLANCONSTIME_PROCESSSTATE 1 + 1

  #define TOURPLANCONSTIMEVERTRIEBSZENTRUMNR 0
  #define TOURPLANCONSTIMEKUNDENNR 1
  #define TOURPLANCONSTIMETOURID 2
  #define TOURPLANCONSTIMEDATUMKOMMI 3
  #define TOURPLANCONSTIMECONSTIME 4
  #define TOURPLANCONSTIMEPROCESSSTATE 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define TOURPLANCONSTIME_H
 #define TOURPLANCONSTIME_ANZ ( sizeof(TOURPLANCONSTIME_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TOURPLANCONSTIME **********************************************/

 #define TOURPLANCONSTIME_LISTE \
         TOURPLANCONSTIME.VERTRIEBSZENTRUMNR,\
         TOURPLANCONSTIME.KUNDENNR,\
         TOURPLANCONSTIME.TOURID,\
         TOURPLANCONSTIME.DATUMKOMMI,\
         TOURPLANCONSTIME.CONSTIME,\
         TOURPLANCONSTIME.PROCESSSTATE

 #define TOURPLANCONSTIME_LISTE_390 \
         VERTRIEBSZENTRUMNR,\
         KUNDENNR,\
         TOURID,\
         DATUMKOMMI,\
         CONSTIME,\
         PROCESSSTATE

 #define TOURPLANCONSTIME_PLISTE \
         "TOURPLANCONSTIME.VERTRIEBSZENTRUMNR,"\
         "TOURPLANCONSTIME.KUNDENNR,"\
         "TOURPLANCONSTIME.TOURID,"\
         "TOURPLANCONSTIME.DATUMKOMMI,"\
         "TOURPLANCONSTIME.CONSTIME,"\
         "TOURPLANCONSTIME.PROCESSSTATE"

 #define TOURPLANCONSTIME_PELISTE \
         "VERTRIEBSZENTRUMNR,"\
         "KUNDENNR,"\
         "TOURID,"\
         "DATUMKOMMI,"\
         "CONSTIME,"\
         "PROCESSSTATE"

 #define TOURPLANCONSTIME_UPDLISTE \
         "VERTRIEBSZENTRUMNR=?,"\
         "KUNDENNR=?,"\
         "TOURID=?,"\
         "DATUMKOMMI=?,"\
         "CONSTIME=?,"\
         "PROCESSSTATE=?"

/* SqlMacros-Define of TOURPLANCONSTIME ***************************************/

 #define TOURPLANCONSTIME_ZEIGER(x) \
         :x->VERTRIEBSZENTRUMNR,\
         :x->KUNDENNR,\
         :x->TOURID,\
         :x->DATUMKOMMI,\
         :x->CONSTIME,\
         :x->PROCESSSTATE

 #define TOURPLANCONSTIME_ZEIGERSEL(x) \
         :x->VERTRIEBSZENTRUMNR,\
         :x->KUNDENNR,\
         :x->TOURID,\
         :x->DATUMKOMMI,\
         :x->CONSTIME,\
         :x->PROCESSSTATE

 #define TOURPLANCONSTIME_UPDATE(x) \
         TOURPLANCONSTIME.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
         TOURPLANCONSTIME.KUNDENNR=:x->KUNDENNR,\
         TOURPLANCONSTIME.TOURID=:x->TOURID,\
         TOURPLANCONSTIME.DATUMKOMMI=:x->DATUMKOMMI,\
         TOURPLANCONSTIME.CONSTIME=:x->CONSTIME,\
         TOURPLANCONSTIME.PROCESSSTATE=:x->PROCESSSTATE

/* SqlMacros390-Define of TOURPLANCONSTIME ************************************/

 #define TOURPLANCONSTIME_ZEIGER_390 \
         :VERTRIEBSZENTRUMNR,\
         :KUNDENNR,\
         :TOURID,\
         :DATUMKOMMI,\
         :CONSTIME,\
         :PROCESSSTATE

 #define TOURPLANCONSTIME_UPDATE_390 \
         VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
         KUNDENNR=:KUNDENNR,\
         TOURID=:TOURID,\
         DATUMKOMMI=:DATUMKOMMI,\
         CONSTIME=:CONSTIME,\
         PROCESSSTATE=:PROCESSSTATE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of TOURPLANCONSTIME ***************************************/

 #ifndef TRANSCLASS
 typedef struct N_TOURPLANCONSTIME {
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         char TOURID[7];
         long DATUMKOMMI;
         long CONSTIME;
         char PROCESSSTATE[2];
        } tourplanconstimeS;
 #else /*TRANSCLASS*/
 typedef struct N_TOURPLANCONSTIME {
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         char TOURID[7];
         long DATUMKOMMI;
         long CONSTIME;
         char PROCESSSTATE[2];

                        bool operator==(const N_TOURPLANCONSTIME& right) const {
                        return(
                                VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
                                KUNDENNR == right.KUNDENNR &&
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
                                VERTRIEBSZENTRUMNR = 0;
                                KUNDENNR = 0;
                                strcpy(TOURID, " " );
                                DATUMKOMMI = 0;
                                CONSTIME = 0;
                                strcpy(PROCESSSTATE, " " );
#endif
                        }
         } tourplanconstimeS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TOURPLANCONSTIME **********************************/

 struct S_TOURPLANCONSTIME {
         char VERTRIEBSZENTRUMNR[7];
         char KUNDENNR[11];
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

/* Stringbuffer (without strend) Structur of TOURPLANCONSTIME *****************/

 struct O_TOURPLANCONSTIME {
         char VERTRIEBSZENTRUMNR[7];
         char KUNDENNR[11];
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

/* Structur with real chartype of TOURPLANCONSTIME ****************************/

 struct C_TOURPLANCONSTIME {
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
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

/* Sizetype  Structur (buf_desc) of TOURPLANCONSTIME **************************/

 struct I_TOURPLANCONSTIME {
         short VERTRIEBSZENTRUMNR;
         short KUNDENNR;
         short TOURID;
         short DATUMKOMMI;
         short CONSTIME;
         short PROCESSSTATE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TOURPLANCONSTIME ************************************/

#if defined (BUF_DESC)
 static struct buf_desc TOURPLANCONSTIME_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc TOURPLANCONSTIME_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#endif

/* description for datatypes of TOURPLANCONSTIME ******************************/

 #define TOURPLANCONSTIME_S390 \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         char TOURID[7]; \
         long DATUMKOMMI; \
         long CONSTIME; \
         char PROCESSSTATE; \



/* Copy-Function Struct to single Data TOURPLANCONSTIME ***********************/

 #define TOURPLANCONSTIME_S390_COPY_TO_SINGLE(_x_) \
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
          strcpy(TOURID,_x_->TOURID);\
         DATUMKOMMI=_x_->DATUMKOMMI;\
         CONSTIME=_x_->CONSTIME;\
         PROCESSSTATE=_x_->PROCESSSTATE;\

 #define TOURPLANCONSTIME_S390_COPY_TO_STRUCT(_x_) \
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          strcpy(_x_->TOURID,TOURID);\
          _x_->DATUMKOMMI=DATUMKOMMI;\
          _x_->CONSTIME=CONSTIME;\
          _x_->PROCESSSTATE=PROCESSSTATE;\



/* FunctionNumber-Define of TourplanConsTime **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of TourplanConsTime ******************************/


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

class CTOURPLANCONSTIME : public ppDadeVirtual
{
        //data members
        public:
                tourplanconstimeS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<tourplanconstimeS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<tourplanconstimeS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<tourplanconstimeS>; Strip(s); tourplanconstimeS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<tourplanconstimeS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<tourplanconstimeS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<tourplanconstimeS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetVertriebszentrumnr() const   { return s.VERTRIEBSZENTRUMNR; }
                long            GetKundennr() const     { return s.KUNDENNR; }
                const char*     GetTourid(ppString& t) const    { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
                long            GetDatumkommi() const   { return s.DATUMKOMMI; }
                long            GetConstime() const     { return s.CONSTIME; }
                char            GetProcessstate() const { return s.PROCESSSTATE[0]; }
                const tourplanconstimeS& GetStruct() const { return s; }
                void            SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
                void            SetKundennr(long t) { s.KUNDENNR = t; }
                void            SetTourid(const ppString& t) { ppGStrCopy(s.TOURID,t.c_str() ,L_TOURPLANCONSTIME_TOURID); }
                void            SetDatumkommi(long t) { s.DATUMKOMMI = t; }
                void            SetConstime(long t) { s.CONSTIME = t; }
                void            SetProcessstate(char t) { s.PROCESSSTATE[0] = t; s.PROCESSSTATE[1] = '\0';}
                void            SetStruct(const tourplanconstimeS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CTOURPLANCONSTIME()  //constructor
                {
                        ::buf_default((void *)&s, TOURPLANCONSTIME_BES, TOURPLANCONSTIME_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CTOURPLANCONSTIME()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, TOURPLANCONSTIME_BES, TOURPLANCONSTIME_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, TOURPLANCONSTIME_BES, TOURPLANCONSTIME_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, TOURPLANCONSTIME_BES, TOURPLANCONSTIME_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_TOURPLANCONSTIME& d)
                {
#ifdef WIN32
                        ppGStripLast(d.TOURID);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, TOURPLANCONSTIME_BES, TOURPLANCONSTIME_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of TOURPLANCONSTIME *************************************/

 #define TOURPLANCONSTIME_CREATE(x) exec sql create table x (\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null,\
         TOURID char(6) default " " not null,\
         DATUMKOMMI integer default 0 not null,\
         CONSTIME integer default 0 not null,\
         PROCESSSTATE char(1) default " " not null) in ksc extent size 1568 next size 160 lock mode row;



/* CreateIndexStatement of TOURPLANCONSTIME ***********************************/

 #define TOURPLANCONSTIME_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_tourplancons_1 on _X_(\
              VertriebszentrumNr,\
              KundenNr,\
              tourid,\
              datumkommi ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TOURPLANCONSTIME ***********************************/

 #define TOURPLANCONSTIME_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_tourplancons_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
