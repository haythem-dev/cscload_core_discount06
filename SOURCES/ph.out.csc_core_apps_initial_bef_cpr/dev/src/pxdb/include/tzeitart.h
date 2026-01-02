#ifndef __PP_ZEITARTEN_H_
#define __PP_ZEITARTEN_H_

/******************************************************************************/
/* v:\zeitarten ***************************************************************/
/******************************************************************************/

/* Length-Define of ZEITARTEN *************************************************/

  #define L_ZEITARTEN_LFDNR 11
  #define L_ZEITARTEN_ZEITART 11
  #define L_ZEITARTEN_ZEITSCHLUESSEL 16
  #define L_ZEITARTEN_TAGESTYP 6
  #define L_ZEITARTEN_ZEITBEGIN 11
  #define L_ZEITARTEN_ZEITENDE 11
  #define L_ZEITARTEN_ZEITZUSATZ 1
  #define L_ZEITARTEN_VERTRIEBSZENTRUMNR 6
  #define L_ZEITARTEN_WEEKDAY 6

/* Length/Count-Define of ZEITARTEN *******************************************/

  #define LS_ZEITARTEN_LFDNR 10 + 1
  #define LS_ZEITARTEN_ZEITART 10 + 1
  #define LS_ZEITARTEN_ZEITSCHLUESSEL 16 + 1
  #define LS_ZEITARTEN_TAGESTYP 6 + 1
  #define LS_ZEITARTEN_ZEITBEGIN 10 + 1
  #define LS_ZEITARTEN_ZEITENDE 10 + 1
  #define LS_ZEITARTEN_ZEITZUSATZ 1 + 1
  #define LS_ZEITARTEN_VERTRIEBSZENTRUMNR 5 + 1
  #define LS_ZEITARTEN_WEEKDAY 5 + 1

  #define ZEITARTENLFDNR 0
  #define ZEITARTENZEITART 1
  #define ZEITARTENZEITSCHLUESSEL 2
  #define ZEITARTENTAGESTYP 3
  #define ZEITARTENZEITBEGIN 4
  #define ZEITARTENZEITENDE 5
  #define ZEITARTENZEITZUSATZ 6
  #define ZEITARTENVERTRIEBSZENTRUMNR 7
  #define ZEITARTENWEEKDAY 8

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ZEITARTEN_H
 #define ZEITARTEN_ANZ ( sizeof(ZEITARTEN_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ZEITARTEN *****************************************************/

 #define ZEITARTEN_LISTE \
         ZEITARTEN.LFDNR,\
         ZEITARTEN.ZEITART,\
         ZEITARTEN.ZEITSCHLUESSEL,\
         ZEITARTEN.TAGESTYP,\
         ZEITARTEN.ZEITBEGIN,\
         ZEITARTEN.ZEITENDE,\
         ZEITARTEN.ZEITZUSATZ,\
         ZEITARTEN.VERTRIEBSZENTRUMNR,\
         ZEITARTEN.WEEKDAY

 #define ZEITARTEN_LISTE_390 \
         LFDNR,\
         ZEITART,\
         ZEITSCHLUESSEL,\
         TAGESTYP,\
         ZEITBEGIN,\
         ZEITENDE,\
         ZEITZUSATZ,\
         VERTRIEBSZENTRUMNR,\
         WEEKDAY

 #define ZEITARTEN_PLISTE \
         "ZEITARTEN.LFDNR,"\
         "ZEITARTEN.ZEITART,"\
         "ZEITARTEN.ZEITSCHLUESSEL,"\
         "ZEITARTEN.TAGESTYP,"\
         "ZEITARTEN.ZEITBEGIN,"\
         "ZEITARTEN.ZEITENDE,"\
         "ZEITARTEN.ZEITZUSATZ,"\
         "ZEITARTEN.VERTRIEBSZENTRUMNR,"\
         "ZEITARTEN.WEEKDAY"

 #define ZEITARTEN_PELISTE \
         "LFDNR,"\
         "ZEITART,"\
         "ZEITSCHLUESSEL,"\
         "TAGESTYP,"\
         "ZEITBEGIN,"\
         "ZEITENDE,"\
         "ZEITZUSATZ,"\
         "VERTRIEBSZENTRUMNR,"\
         "WEEKDAY"

 #define ZEITARTEN_UPDLISTE \
         "LFDNR=?,"\
         "ZEITART=?,"\
         "ZEITSCHLUESSEL=?,"\
         "TAGESTYP=?,"\
         "ZEITBEGIN=?,"\
         "ZEITENDE=?,"\
         "ZEITZUSATZ=?,"\
         "VERTRIEBSZENTRUMNR=?,"\
         "WEEKDAY=?"

/* SqlMacros-Define of ZEITARTEN **********************************************/

 #define ZEITARTEN_ZEIGER(x) \
         :x->LFDNR,\
         :x->ZEITART,\
         :x->ZEITSCHLUESSEL,\
         :x->TAGESTYP,\
         :x->ZEITBEGIN,\
         :x->ZEITENDE,\
         :x->ZEITZUSATZ,\
         :x->VERTRIEBSZENTRUMNR,\
         :x->WEEKDAY

 #define ZEITARTEN_ZEIGERSEL(x) \
         :x->LFDNR,\
         :x->ZEITART,\
         :x->ZEITSCHLUESSEL,\
         :x->TAGESTYP,\
         :x->ZEITBEGIN,\
         :x->ZEITENDE,\
         :x->ZEITZUSATZ,\
         :x->VERTRIEBSZENTRUMNR,\
         :x->WEEKDAY

 #define ZEITARTEN_UPDATE(x) \
         ZEITARTEN.ZEITART=:x->ZEITART,\
         ZEITARTEN.ZEITSCHLUESSEL=:x->ZEITSCHLUESSEL,\
         ZEITARTEN.TAGESTYP=:x->TAGESTYP,\
         ZEITARTEN.ZEITBEGIN=:x->ZEITBEGIN,\
         ZEITARTEN.ZEITENDE=:x->ZEITENDE,\
         ZEITARTEN.ZEITZUSATZ=:x->ZEITZUSATZ,\
         ZEITARTEN.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
         ZEITARTEN.WEEKDAY=:x->WEEKDAY

/* SqlMacros390-Define of ZEITARTEN *******************************************/

 #define ZEITARTEN_ZEIGER_390 \
         :LFDNR,\
         :ZEITART,\
         :ZEITSCHLUESSEL,\
         :TAGESTYP,\
         :ZEITBEGIN,\
         :ZEITENDE,\
         :ZEITZUSATZ,\
         :VERTRIEBSZENTRUMNR,\
         :WEEKDAY

 #define ZEITARTEN_UPDATE_390 \
         LFDNR=:LFDNR,\
         ZEITART=:ZEITART,\
         ZEITSCHLUESSEL=:ZEITSCHLUESSEL,\
         TAGESTYP=:TAGESTYP,\
         ZEITBEGIN=:ZEITBEGIN,\
         ZEITENDE=:ZEITENDE,\
         ZEITZUSATZ=:ZEITZUSATZ,\
         VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
         WEEKDAY=:WEEKDAY

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ZEITARTEN **********************************************/

 #ifndef TRANSCLASS
 typedef struct N_ZEITARTEN {
         long LFDNR;
         long ZEITART;
         char ZEITSCHLUESSEL[17];
         char TAGESTYP[7];
         long ZEITBEGIN;
         long ZEITENDE;
         char ZEITZUSATZ[2];
         short VERTRIEBSZENTRUMNR;
         short WEEKDAY;
        } zeitartenS;
 #else /*TRANSCLASS*/
 typedef struct N_ZEITARTEN {
         long LFDNR;
         long ZEITART;
         char ZEITSCHLUESSEL[17];
         char TAGESTYP[7];
         long ZEITBEGIN;
         long ZEITENDE;
         char ZEITZUSATZ[2];
         short VERTRIEBSZENTRUMNR;
         short WEEKDAY;

                        bool operator==(const N_ZEITARTEN& right) const {
                        return(
                                LFDNR == right.LFDNR &&
                                ZEITART == right.ZEITART &&
                                !strcmp(ZEITSCHLUESSEL, right.ZEITSCHLUESSEL) &&
                                !strcmp(TAGESTYP, right.TAGESTYP) &&
                                ZEITBEGIN == right.ZEITBEGIN &&
                                ZEITENDE == right.ZEITENDE &&
                                !strcmp(ZEITZUSATZ, right.ZEITZUSATZ) &&
                                VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
                                WEEKDAY == right.WEEKDAY
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                LFDNR = 0;
                                ZEITART = 0;
                                strcpy(ZEITSCHLUESSEL, " " );
                                strcpy(TAGESTYP, " " );
                                ZEITBEGIN = 0;
                                ZEITENDE = 0;
                                strcpy(ZEITZUSATZ, " " );
                                VERTRIEBSZENTRUMNR = 0;
                                WEEKDAY = 0;
#endif
                        }
         } zeitartenS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ZEITARTEN *****************************************/

 struct S_ZEITARTEN {
         char LFDNR[11];
         char ZEITART[11];
         char ZEITSCHLUESSEL[16 + 1];
         char TAGESTYP[6 + 1];
         char ZEITBEGIN[11];
         char ZEITENDE[11];
         char ZEITZUSATZ[1 + 1];
         char VERTRIEBSZENTRUMNR[7];
         char WEEKDAY[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ZEITARTEN ************************/

 struct O_ZEITARTEN {
         char LFDNR[11];
         char ZEITART[11];
         char ZEITSCHLUESSEL[16];
         char TAGESTYP[6];
         char ZEITBEGIN[11];
         char ZEITENDE[11];
         char ZEITZUSATZ[1];
         char VERTRIEBSZENTRUMNR[7];
         char WEEKDAY[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ZEITARTEN ***********************************/

 struct C_ZEITARTEN {
         long LFDNR;
         long ZEITART;
         char ZEITSCHLUESSEL[17];
         char TAGESTYP[7];
         long ZEITBEGIN;
         long ZEITENDE;
         char ZEITZUSATZ;
         short VERTRIEBSZENTRUMNR;
         short WEEKDAY;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ZEITARTEN *********************************/

 struct I_ZEITARTEN {
         short LFDNR;
         short ZEITART;
         short ZEITSCHLUESSEL;
         short TAGESTYP;
         short ZEITBEGIN;
         short ZEITENDE;
         short ZEITZUSATZ;
         short VERTRIEBSZENTRUMNR;
         short WEEKDAY;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ZEITARTEN *******************************************/

#if defined (BUF_DESC)
 static struct buf_desc ZEITARTEN_BES [] =
 {
   { TYP_L ,  11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 16, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ZEITARTEN_BES [] =
 {
   { TYP_L ,  11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 16, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of ZEITARTEN *************************************/

 #define ZEITARTEN_S390 \
         long LFDNR; \
         long ZEITART; \
         char ZEITSCHLUESSEL[17]; \
         char TAGESTYP[7]; \
         long ZEITBEGIN; \
         long ZEITENDE; \
         char ZEITZUSATZ; \
         short VERTRIEBSZENTRUMNR; \
         short WEEKDAY; \



/* Copy-Function Struct to single Data ZEITARTEN ******************************/

 #define ZEITARTEN_S390_COPY_TO_SINGLE(_x_) \
         LFDNR=_x_->LFDNR;\
         ZEITART=_x_->ZEITART;\
          strcpy(ZEITSCHLUESSEL,_x_->ZEITSCHLUESSEL);\
          strcpy(TAGESTYP,_x_->TAGESTYP);\
         ZEITBEGIN=_x_->ZEITBEGIN;\
         ZEITENDE=_x_->ZEITENDE;\
         ZEITZUSATZ=_x_->ZEITZUSATZ;\
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         WEEKDAY=_x_->WEEKDAY;\

 #define ZEITARTEN_S390_COPY_TO_STRUCT(_x_) \
          _x_->LFDNR=LFDNR;\
          _x_->ZEITART=ZEITART;\
          strcpy(_x_->ZEITSCHLUESSEL,ZEITSCHLUESSEL);\
          strcpy(_x_->TAGESTYP,TAGESTYP);\
          _x_->ZEITBEGIN=ZEITBEGIN;\
          _x_->ZEITENDE=ZEITENDE;\
          _x_->ZEITZUSATZ=ZEITZUSATZ;\
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->WEEKDAY=WEEKDAY;\



/* FunctionNumber-Define of zeitarten *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of zeitarten *************************************/


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

class CZEITARTEN : public ppDadeVirtual
{
        //data members
        public:
                zeitartenS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<zeitartenS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<zeitartenS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<zeitartenS>; Strip(s); zeitartenS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<zeitartenS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<zeitartenS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<zeitartenS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetLfdnr() const        { return s.LFDNR; }
                long            GetZeitart() const      { return s.ZEITART; }
                const char*     GetZeitschluessel(ppString& t) const    { t = s.ZEITSCHLUESSEL; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetTagestyp(ppString& t) const  { t = s.TAGESTYP; t.erasespace(ppString::END); return t.c_str(); }
                long            GetZeitbegin() const    { return s.ZEITBEGIN; }
                long            GetZeitende() const     { return s.ZEITENDE; }
                char            GetZeitzusatz() const   { return s.ZEITZUSATZ[0]; }
                short           GetVertriebszentrumnr() const   { return s.VERTRIEBSZENTRUMNR; }
                short           GetWeekday() const      { return s.WEEKDAY; }
                const zeitartenS& GetStruct() const { return s; }
                void            SetLfdnr(long t) { s.LFDNR = t; }
                void            SetZeitart(long t) { s.ZEITART = t; }
                void            SetZeitschluessel(const ppString& t) { ppGStrCopy(s.ZEITSCHLUESSEL,t.c_str() ,L_ZEITARTEN_ZEITSCHLUESSEL); }
                void            SetTagestyp(const ppString& t) { ppGStrCopy(s.TAGESTYP,t.c_str() ,L_ZEITARTEN_TAGESTYP); }
                void            SetZeitbegin(long t) { s.ZEITBEGIN = t; }
                void            SetZeitende(long t) { s.ZEITENDE = t; }
                void            SetZeitzusatz(char t) { s.ZEITZUSATZ[0] = t; s.ZEITZUSATZ[1] = '\0';}
                void            SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
                void            SetWeekday(short t) { s.WEEKDAY = t; }
                void            SetStruct(const zeitartenS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CZEITARTEN()  //constructor
                {
                        ::buf_default((void *)&s, ZEITARTEN_BES, ZEITARTEN_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CZEITARTEN()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ZEITARTEN_BES, ZEITARTEN_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ZEITARTEN_BES, ZEITARTEN_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, ZEITARTEN_BES, ZEITARTEN_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ZEITARTEN& d)
                {
#ifdef WIN32
                        ppGStripLast(d.ZEITSCHLUESSEL);
                        ppGStripLast(d.TAGESTYP);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, ZEITARTEN_BES, ZEITARTEN_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ZEITARTEN ********************************************/

 #define ZEITARTEN_CREATE(x) exec sql create table x (\
         LFDNR serial not null,\
         ZEITART integer default 0 not null,\
         ZEITSCHLUESSEL char(16) default " " not null,\
         TAGESTYP char(6) default " " not null,\
         ZEITBEGIN integer default 0 not null,\
         ZEITENDE integer default 0 not null,\
         ZEITZUSATZ char(1) default " " not null,\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         WEEKDAY smallint default 0 not null) in KscCustomer extent size 2508 next size 252 lock mode row;



/* CreateIndexStatement of ZEITARTEN ******************************************/

 #define ZEITARTEN_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_zeitarten_1 on _X_(\
              VertriebszentrumNr,\
              zeitschluessel,\
              zeitart ) in KscCustomerIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create unique index i_zeitarten_2 on _X_(\
              lfdnr ) in KscCustomerIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create unique index i_zeitarten_3 on _X_(\
              VertriebszentrumNr,\
              zeitart,\
              zeitschluessel,\
              tagestyp,\
              zeitbegin,\
              zeitende ) in KscCustomerIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ZEITARTEN ******************************************/

 #define ZEITARTEN_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_zeitarten_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_zeitarten_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_zeitarten_3;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
