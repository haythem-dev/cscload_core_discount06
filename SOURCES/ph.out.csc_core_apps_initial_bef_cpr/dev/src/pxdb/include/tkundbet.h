#ifndef __PP_KDBETRIEBSENDE_H_
#define __PP_KDBETRIEBSENDE_H_

/******************************************************************************/
/* v:\kdbetriebsende **********************************************************/
/******************************************************************************/

/* Length-Define of KDBETRIEBSENDE ********************************************/

  #define L_KDBETRIEBSENDE_IDFNR 11
  #define L_KDBETRIEBSENDE_TAGESTYP 6
  #define L_KDBETRIEBSENDE_ZEITBEGINAM 11
  #define L_KDBETRIEBSENDE_ZEITENDEAM 11
  #define L_KDBETRIEBSENDE_ZEITBEGINPM 11
  #define L_KDBETRIEBSENDE_ZEITENDEPM 11
  #define L_KDBETRIEBSENDE_VERTRIEBSZENTRUMNR 6
  #define L_KDBETRIEBSENDE_KUNDENNR 11
  #define L_KDBETRIEBSENDE_WEEKDAY 6

/* Length/Count-Define of KDBETRIEBSENDE **************************************/

  #define LS_KDBETRIEBSENDE_IDFNR 10 + 1
  #define LS_KDBETRIEBSENDE_TAGESTYP 6 + 1
  #define LS_KDBETRIEBSENDE_ZEITBEGINAM 10 + 1
  #define LS_KDBETRIEBSENDE_ZEITENDEAM 10 + 1
  #define LS_KDBETRIEBSENDE_ZEITBEGINPM 10 + 1
  #define LS_KDBETRIEBSENDE_ZEITENDEPM 10 + 1
  #define LS_KDBETRIEBSENDE_VERTRIEBSZENTRUMNR 5 + 1
  #define LS_KDBETRIEBSENDE_KUNDENNR 10 + 1
  #define LS_KDBETRIEBSENDE_WEEKDAY 5 + 1

  #define KDBETRIEBSENDEIDFNR 0
  #define KDBETRIEBSENDETAGESTYP 1
  #define KDBETRIEBSENDEZEITBEGINAM 2
  #define KDBETRIEBSENDEZEITENDEAM 3
  #define KDBETRIEBSENDEZEITBEGINPM 4
  #define KDBETRIEBSENDEZEITENDEPM 5
  #define KDBETRIEBSENDEVERTRIEBSZENTRUMNR 6
  #define KDBETRIEBSENDEKUNDENNR 7
  #define KDBETRIEBSENDEWEEKDAY 8

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KDBETRIEBSENDE_H
 #define KDBETRIEBSENDE_ANZ ( sizeof(KDBETRIEBSENDE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDBETRIEBSENDE ************************************************/

 #define KDBETRIEBSENDE_LISTE \
         KDBETRIEBSENDE.IDFNR,\
         KDBETRIEBSENDE.TAGESTYP,\
         KDBETRIEBSENDE.ZEITBEGINAM,\
         KDBETRIEBSENDE.ZEITENDEAM,\
         KDBETRIEBSENDE.ZEITBEGINPM,\
         KDBETRIEBSENDE.ZEITENDEPM,\
         KDBETRIEBSENDE.VERTRIEBSZENTRUMNR,\
         KDBETRIEBSENDE.KUNDENNR,\
         KDBETRIEBSENDE.WEEKDAY

 #define KDBETRIEBSENDE_LISTE_390 \
         IDFNR,\
         TAGESTYP,\
         ZEITBEGINAM,\
         ZEITENDEAM,\
         ZEITBEGINPM,\
         ZEITENDEPM,\
         VERTRIEBSZENTRUMNR,\
         KUNDENNR,\
         WEEKDAY

 #define KDBETRIEBSENDE_PLISTE \
         "KDBETRIEBSENDE.IDFNR,"\
         "KDBETRIEBSENDE.TAGESTYP,"\
         "KDBETRIEBSENDE.ZEITBEGINAM,"\
         "KDBETRIEBSENDE.ZEITENDEAM,"\
         "KDBETRIEBSENDE.ZEITBEGINPM,"\
         "KDBETRIEBSENDE.ZEITENDEPM,"\
         "KDBETRIEBSENDE.VERTRIEBSZENTRUMNR,"\
         "KDBETRIEBSENDE.KUNDENNR,"\
         "KDBETRIEBSENDE.WEEKDAY"

 #define KDBETRIEBSENDE_PELISTE \
         "IDFNR,"\
         "TAGESTYP,"\
         "ZEITBEGINAM,"\
         "ZEITENDEAM,"\
         "ZEITBEGINPM,"\
         "ZEITENDEPM,"\
         "VERTRIEBSZENTRUMNR,"\
         "KUNDENNR,"\
         "WEEKDAY"

 #define KDBETRIEBSENDE_UPDLISTE \
         "IDFNR=?,"\
         "TAGESTYP=?,"\
         "ZEITBEGINAM=?,"\
         "ZEITENDEAM=?,"\
         "ZEITBEGINPM=?,"\
         "ZEITENDEPM=?,"\
         "VERTRIEBSZENTRUMNR=?,"\
         "KUNDENNR=?,"\
         "WEEKDAY=?"

/* SqlMacros-Define of KDBETRIEBSENDE *****************************************/

 #define KDBETRIEBSENDE_ZEIGER(x) \
         :x->IDFNR,\
         :x->TAGESTYP,\
         :x->ZEITBEGINAM,\
         :x->ZEITENDEAM,\
         :x->ZEITBEGINPM,\
         :x->ZEITENDEPM,\
         :x->VERTRIEBSZENTRUMNR,\
         :x->KUNDENNR,\
         :x->WEEKDAY

 #define KDBETRIEBSENDE_ZEIGERSEL(x) \
         :x->IDFNR,\
         :x->TAGESTYP,\
         :x->ZEITBEGINAM,\
         :x->ZEITENDEAM,\
         :x->ZEITBEGINPM,\
         :x->ZEITENDEPM,\
         :x->VERTRIEBSZENTRUMNR,\
         :x->KUNDENNR,\
         :x->WEEKDAY

 #define KDBETRIEBSENDE_UPDATE(x) \
         KDBETRIEBSENDE.IDFNR=:x->IDFNR,\
         KDBETRIEBSENDE.TAGESTYP=:x->TAGESTYP,\
         KDBETRIEBSENDE.ZEITBEGINAM=:x->ZEITBEGINAM,\
         KDBETRIEBSENDE.ZEITENDEAM=:x->ZEITENDEAM,\
         KDBETRIEBSENDE.ZEITBEGINPM=:x->ZEITBEGINPM,\
         KDBETRIEBSENDE.ZEITENDEPM=:x->ZEITENDEPM,\
         KDBETRIEBSENDE.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
         KDBETRIEBSENDE.KUNDENNR=:x->KUNDENNR,\
         KDBETRIEBSENDE.WEEKDAY=:x->WEEKDAY

/* SqlMacros390-Define of KDBETRIEBSENDE **************************************/

 #define KDBETRIEBSENDE_ZEIGER_390 \
         :IDFNR,\
         :TAGESTYP,\
         :ZEITBEGINAM,\
         :ZEITENDEAM,\
         :ZEITBEGINPM,\
         :ZEITENDEPM,\
         :VERTRIEBSZENTRUMNR,\
         :KUNDENNR,\
         :WEEKDAY

 #define KDBETRIEBSENDE_UPDATE_390 \
         IDFNR=:IDFNR,\
         TAGESTYP=:TAGESTYP,\
         ZEITBEGINAM=:ZEITBEGINAM,\
         ZEITENDEAM=:ZEITENDEAM,\
         ZEITBEGINPM=:ZEITBEGINPM,\
         ZEITENDEPM=:ZEITENDEPM,\
         VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
         KUNDENNR=:KUNDENNR,\
         WEEKDAY=:WEEKDAY

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KDBETRIEBSENDE *****************************************/

 #ifndef TRANSCLASS
 typedef struct N_KDBETRIEBSENDE {
         long IDFNR;
         char TAGESTYP[7];
         long ZEITBEGINAM;
         long ZEITENDEAM;
         long ZEITBEGINPM;
         long ZEITENDEPM;
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         short WEEKDAY;
        } kdbetriebsendeS;
 #else /*TRANSCLASS*/
 typedef struct N_KDBETRIEBSENDE {
         long IDFNR;
         char TAGESTYP[7];
         long ZEITBEGINAM;
         long ZEITENDEAM;
         long ZEITBEGINPM;
         long ZEITENDEPM;
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         short WEEKDAY;

                        bool operator==(const N_KDBETRIEBSENDE& right) const {
                        return(
                                IDFNR == right.IDFNR &&
                                !strcmp(TAGESTYP, right.TAGESTYP) &&
                                ZEITBEGINAM == right.ZEITBEGINAM &&
                                ZEITENDEAM == right.ZEITENDEAM &&
                                ZEITBEGINPM == right.ZEITBEGINPM &&
                                ZEITENDEPM == right.ZEITENDEPM &&
                                VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
                                KUNDENNR == right.KUNDENNR &&
                                WEEKDAY == right.WEEKDAY
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                IDFNR = 0;
                                strcpy(TAGESTYP, " " );
                                ZEITBEGINAM = 0;
                                ZEITENDEAM = 0;
                                ZEITBEGINPM = 0;
                                ZEITENDEPM = 0;
                                VERTRIEBSZENTRUMNR = 0;
                                KUNDENNR = 0;
                                WEEKDAY = 0;
#endif
                        }
         } kdbetriebsendeS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDBETRIEBSENDE ************************************/

 struct S_KDBETRIEBSENDE {
         char IDFNR[11];
         char TAGESTYP[6 + 1];
         char ZEITBEGINAM[11];
         char ZEITENDEAM[11];
         char ZEITBEGINPM[11];
         char ZEITENDEPM[11];
         char VERTRIEBSZENTRUMNR[7];
         char KUNDENNR[11];
         char WEEKDAY[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDBETRIEBSENDE *******************/

 struct O_KDBETRIEBSENDE {
         char IDFNR[11];
         char TAGESTYP[6];
         char ZEITBEGINAM[11];
         char ZEITENDEAM[11];
         char ZEITBEGINPM[11];
         char ZEITENDEPM[11];
         char VERTRIEBSZENTRUMNR[7];
         char KUNDENNR[11];
         char WEEKDAY[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDBETRIEBSENDE ******************************/

 struct C_KDBETRIEBSENDE {
         long IDFNR;
         char TAGESTYP[7];
         long ZEITBEGINAM;
         long ZEITENDEAM;
         long ZEITBEGINPM;
         long ZEITENDEPM;
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         short WEEKDAY;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDBETRIEBSENDE ****************************/

 struct I_KDBETRIEBSENDE {
         short IDFNR;
         short TAGESTYP;
         short ZEITBEGINAM;
         short ZEITENDEAM;
         short ZEITBEGINPM;
         short ZEITENDEPM;
         short VERTRIEBSZENTRUMNR;
         short KUNDENNR;
         short WEEKDAY;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDBETRIEBSENDE **************************************/

#if defined (BUF_DESC)
 static struct buf_desc KDBETRIEBSENDE_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDBETRIEBSENDE_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of KDBETRIEBSENDE ********************************/

 #define KDBETRIEBSENDE_S390 \
         long IDFNR; \
         char TAGESTYP[7]; \
         long ZEITBEGINAM; \
         long ZEITENDEAM; \
         long ZEITBEGINPM; \
         long ZEITENDEPM; \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         short WEEKDAY; \



/* Copy-Function Struct to single Data KDBETRIEBSENDE *************************/

 #define KDBETRIEBSENDE_S390_COPY_TO_SINGLE(_x_) \
         IDFNR=_x_->IDFNR;\
          strcpy(TAGESTYP,_x_->TAGESTYP);\
         ZEITBEGINAM=_x_->ZEITBEGINAM;\
         ZEITENDEAM=_x_->ZEITENDEAM;\
         ZEITBEGINPM=_x_->ZEITBEGINPM;\
         ZEITENDEPM=_x_->ZEITENDEPM;\
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
         WEEKDAY=_x_->WEEKDAY;\

 #define KDBETRIEBSENDE_S390_COPY_TO_STRUCT(_x_) \
          _x_->IDFNR=IDFNR;\
          strcpy(_x_->TAGESTYP,TAGESTYP);\
          _x_->ZEITBEGINAM=ZEITBEGINAM;\
          _x_->ZEITENDEAM=ZEITENDEAM;\
          _x_->ZEITBEGINPM=ZEITBEGINPM;\
          _x_->ZEITENDEPM=ZEITENDEPM;\
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          _x_->WEEKDAY=WEEKDAY;\



/* FunctionNumber-Define of kdbetriebsende ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdbetriebsende ********************************/


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

class CKDBETRIEBSENDE : public ppDadeVirtual
{
        //data members
        public:
                kdbetriebsendeS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<kdbetriebsendeS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdbetriebsendeS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<kdbetriebsendeS>; Strip(s); kdbetriebsendeS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdbetriebsendeS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<kdbetriebsendeS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<kdbetriebsendeS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetIdfnr() const        { return s.IDFNR; }
                const char*     GetTagestyp(ppString& t) const  { t = s.TAGESTYP; t.erasespace(ppString::END); return t.c_str(); }
                long            GetZeitbeginam() const  { return s.ZEITBEGINAM; }
                long            GetZeitendeam() const   { return s.ZEITENDEAM; }
                long            GetZeitbeginpm() const  { return s.ZEITBEGINPM; }
                long            GetZeitendepm() const   { return s.ZEITENDEPM; }
                short           GetVertriebszentrumnr() const   { return s.VERTRIEBSZENTRUMNR; }
                long            GetKundennr() const     { return s.KUNDENNR; }
                short           GetWeekday() const      { return s.WEEKDAY; }
                const kdbetriebsendeS& GetStruct() const { return s; }
                void            SetIdfnr(long t) { s.IDFNR = t; }
                void            SetTagestyp(const ppString& t) { ppGStrCopy(s.TAGESTYP,t.c_str() ,L_KDBETRIEBSENDE_TAGESTYP); }
                void            SetZeitbeginam(long t) { s.ZEITBEGINAM = t; }
                void            SetZeitendeam(long t) { s.ZEITENDEAM = t; }
                void            SetZeitbeginpm(long t) { s.ZEITBEGINPM = t; }
                void            SetZeitendepm(long t) { s.ZEITENDEPM = t; }
                void            SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
                void            SetKundennr(long t) { s.KUNDENNR = t; }
                void            SetWeekday(short t) { s.WEEKDAY = t; }
                void            SetStruct(const kdbetriebsendeS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CKDBETRIEBSENDE()  //constructor
                {
                        ::buf_default((void *)&s, KDBETRIEBSENDE_BES, KDBETRIEBSENDE_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CKDBETRIEBSENDE()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, KDBETRIEBSENDE_BES, KDBETRIEBSENDE_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDBETRIEBSENDE_BES, KDBETRIEBSENDE_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, KDBETRIEBSENDE_BES, KDBETRIEBSENDE_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_KDBETRIEBSENDE& d)
                {
#ifdef WIN32
                        ppGStripLast(d.TAGESTYP);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, KDBETRIEBSENDE_BES, KDBETRIEBSENDE_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of KDBETRIEBSENDE ***************************************/

 #define KDBETRIEBSENDE_CREATE(x) exec sql create table x (\
         IDFNR integer default 0 not null,\
         TAGESTYP char(6) default " " not null,\
         ZEITBEGINAM integer default 0 not null,\
         ZEITENDEAM integer default 0 not null,\
         ZEITBEGINPM integer default 0 not null,\
         ZEITENDEPM integer default 0 not null,\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null,\
         WEEKDAY smallint default 0 not null) in KscCustomer extent size 2744 next size 276 lock mode row;



/* CreateIndexStatement of KDBETRIEBSENDE *************************************/

 #define KDBETRIEBSENDE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_kdbetriebsende_2 on _X_(\
              VertriebszentrumNr,\
              KundenNr,\
              tagestyp ) in KscCustomerIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index kdbetriebsendex on _X_(\
              idfnr,\
              tagestyp ) in KscCustomerIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDBETRIEBSENDE *************************************/

 #define KDBETRIEBSENDE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kdbetriebsende_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index kdbetriebsendex;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
