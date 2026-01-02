#ifndef __PP_CUSTOMERROUTING_H_
#define __PP_CUSTOMERROUTING_H_

/******************************************************************************/
/* v:\CustomerRouting *********************************************************/
/******************************************************************************/

/* Length-Define of CUSTOMERROUTING *******************************************/

  #define L_CUSTOMERROUTING_CUSTOMERNO 11
  #define L_CUSTOMERROUTING_BRANCHNO 6
  #define L_CUSTOMERROUTING_TIMEFROM 11
  #define L_CUSTOMERROUTING_TIMETO 11
  #define L_CUSTOMERROUTING_DESTBRANCHNO 6
  #define L_CUSTOMERROUTING_DAYOFWEEK 2
  #define L_CUSTOMERROUTING_WEEKDAY 6

/* Length/Count-Define of CUSTOMERROUTING *************************************/

  #define LS_CUSTOMERROUTING_CUSTOMERNO 10 + 1
  #define LS_CUSTOMERROUTING_BRANCHNO 5 + 1
  #define LS_CUSTOMERROUTING_TIMEFROM 10 + 1
  #define LS_CUSTOMERROUTING_TIMETO 10 + 1
  #define LS_CUSTOMERROUTING_DESTBRANCHNO 5 + 1
  #define LS_CUSTOMERROUTING_DAYOFWEEK 2 + 1
  #define LS_CUSTOMERROUTING_WEEKDAY 5 + 1

  #define CUSTOMERROUTINGCUSTOMERNO 0
  #define CUSTOMERROUTINGBRANCHNO 1
  #define CUSTOMERROUTINGTIMEFROM 2
  #define CUSTOMERROUTINGTIMETO 3
  #define CUSTOMERROUTINGDESTBRANCHNO 4
  #define CUSTOMERROUTINGDAYOFWEEK 5
  #define CUSTOMERROUTINGWEEKDAY 6

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define CUSTOMERROUTING_H
 #define CUSTOMERROUTING_ANZ ( sizeof(CUSTOMERROUTING_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CUSTOMERROUTING ***********************************************/

 #define CUSTOMERROUTING_LISTE \
         CUSTOMERROUTING.CUSTOMERNO,\
         CUSTOMERROUTING.BRANCHNO,\
         CUSTOMERROUTING.TIMEFROM,\
         CUSTOMERROUTING.TIMETO,\
         CUSTOMERROUTING.DESTBRANCHNO,\
         CUSTOMERROUTING.DAYOFWEEK,\
         CUSTOMERROUTING.WEEKDAY

 #define CUSTOMERROUTING_LISTE_390 \
         CUSTOMERNO,\
         BRANCHNO,\
         TIMEFROM,\
         TIMETO,\
         DESTBRANCHNO,\
         DAYOFWEEK,\
         WEEKDAY

 #define CUSTOMERROUTING_PLISTE \
         "CUSTOMERROUTING.CUSTOMERNO,"\
         "CUSTOMERROUTING.BRANCHNO,"\
         "CUSTOMERROUTING.TIMEFROM,"\
         "CUSTOMERROUTING.TIMETO,"\
         "CUSTOMERROUTING.DESTBRANCHNO,"\
         "CUSTOMERROUTING.DAYOFWEEK,"\
         "CUSTOMERROUTING.WEEKDAY"

 #define CUSTOMERROUTING_PELISTE \
         "CUSTOMERNO,"\
         "BRANCHNO,"\
         "TIMEFROM,"\
         "TIMETO,"\
         "DESTBRANCHNO,"\
         "DAYOFWEEK,"\
         "WEEKDAY"

 #define CUSTOMERROUTING_UPDLISTE \
         "CUSTOMERNO=?,"\
         "BRANCHNO=?,"\
         "TIMEFROM=?,"\
         "TIMETO=?,"\
         "DESTBRANCHNO=?,"\
         "DAYOFWEEK=?,"\
         "WEEKDAY=?"

/* SqlMacros-Define of CUSTOMERROUTING ****************************************/

 #define CUSTOMERROUTING_ZEIGER(x) \
         :x->CUSTOMERNO,\
         :x->BRANCHNO,\
         :x->TIMEFROM,\
         :x->TIMETO,\
         :x->DESTBRANCHNO,\
         :x->DAYOFWEEK,\
         :x->WEEKDAY

 #define CUSTOMERROUTING_ZEIGERSEL(x) \
         :x->CUSTOMERNO,\
         :x->BRANCHNO,\
         :x->TIMEFROM,\
         :x->TIMETO,\
         :x->DESTBRANCHNO,\
         :x->DAYOFWEEK,\
         :x->WEEKDAY

 #define CUSTOMERROUTING_UPDATE(x) \
         CUSTOMERROUTING.CUSTOMERNO=:x->CUSTOMERNO,\
         CUSTOMERROUTING.BRANCHNO=:x->BRANCHNO,\
         CUSTOMERROUTING.TIMEFROM=:x->TIMEFROM,\
         CUSTOMERROUTING.TIMETO=:x->TIMETO,\
         CUSTOMERROUTING.DESTBRANCHNO=:x->DESTBRANCHNO,\
         CUSTOMERROUTING.DAYOFWEEK=:x->DAYOFWEEK,\
         CUSTOMERROUTING.WEEKDAY=:x->WEEKDAY

/* SqlMacros390-Define of CUSTOMERROUTING *************************************/

 #define CUSTOMERROUTING_ZEIGER_390 \
         :CUSTOMERNO,\
         :BRANCHNO,\
         :TIMEFROM,\
         :TIMETO,\
         :DESTBRANCHNO,\
         :DAYOFWEEK,\
         :WEEKDAY

 #define CUSTOMERROUTING_UPDATE_390 \
         CUSTOMERNO=:CUSTOMERNO,\
         BRANCHNO=:BRANCHNO,\
         TIMEFROM=:TIMEFROM,\
         TIMETO=:TIMETO,\
         DESTBRANCHNO=:DESTBRANCHNO,\
         DAYOFWEEK=:DAYOFWEEK,\
         WEEKDAY=:WEEKDAY

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of CUSTOMERROUTING ****************************************/

 #ifndef TRANSCLASS
 typedef struct N_CUSTOMERROUTING {
         long CUSTOMERNO;
         short BRANCHNO;
         long TIMEFROM;
         long TIMETO;
         short DESTBRANCHNO;
         char DAYOFWEEK[3];
         short WEEKDAY;
        } customerroutingS;
 #else /*TRANSCLASS*/
 typedef struct N_CUSTOMERROUTING {
         long CUSTOMERNO;
         short BRANCHNO;
         long TIMEFROM;
         long TIMETO;
         short DESTBRANCHNO;
         char DAYOFWEEK[3];
         short WEEKDAY;

                        bool operator==(const N_CUSTOMERROUTING& right) const {
                        return(
                                CUSTOMERNO == right.CUSTOMERNO &&
                                BRANCHNO == right.BRANCHNO &&
                                TIMEFROM == right.TIMEFROM &&
                                TIMETO == right.TIMETO &&
                                DESTBRANCHNO == right.DESTBRANCHNO &&
                                !strcmp(DAYOFWEEK, right.DAYOFWEEK) &&
                                WEEKDAY == right.WEEKDAY
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                CUSTOMERNO = 0;
                                BRANCHNO = 0;
                                TIMEFROM = 0;
                                TIMETO = 0;
                                DESTBRANCHNO = 0;
                                strcpy(DAYOFWEEK, " " );
                                WEEKDAY = 0;
#endif
                        }
         } customerroutingS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CUSTOMERROUTING ***********************************/

 struct S_CUSTOMERROUTING {
         char CUSTOMERNO[11];
         char BRANCHNO[7];
         char TIMEFROM[11];
         char TIMETO[11];
         char DESTBRANCHNO[7];
         char DAYOFWEEK[2 + 1];
         char WEEKDAY[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CUSTOMERROUTING ******************/

 struct O_CUSTOMERROUTING {
         char CUSTOMERNO[11];
         char BRANCHNO[7];
         char TIMEFROM[11];
         char TIMETO[11];
         char DESTBRANCHNO[7];
         char DAYOFWEEK[2];
         char WEEKDAY[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CUSTOMERROUTING *****************************/

 struct C_CUSTOMERROUTING {
         long CUSTOMERNO;
         short BRANCHNO;
         long TIMEFROM;
         long TIMETO;
         short DESTBRANCHNO;
         char DAYOFWEEK[3];
         short WEEKDAY;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CUSTOMERROUTING ***************************/

 struct I_CUSTOMERROUTING {
         short CUSTOMERNO;
         short BRANCHNO;
         short TIMEFROM;
         short TIMETO;
         short DESTBRANCHNO;
         short DAYOFWEEK;
         short WEEKDAY;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CUSTOMERROUTING *************************************/

#if defined (BUF_DESC)
 static struct buf_desc CUSTOMERROUTING_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc CUSTOMERROUTING_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of CUSTOMERROUTING *******************************/

 #define CUSTOMERROUTING_S390 \
         long CUSTOMERNO; \
         short BRANCHNO; \
         long TIMEFROM; \
         long TIMETO; \
         short DESTBRANCHNO; \
         char DAYOFWEEK[3]; \
         short WEEKDAY; \



/* Copy-Function Struct to single Data CUSTOMERROUTING ************************/

 #define CUSTOMERROUTING_S390_COPY_TO_SINGLE(_x_) \
         CUSTOMERNO=_x_->CUSTOMERNO;\
         BRANCHNO=_x_->BRANCHNO;\
         TIMEFROM=_x_->TIMEFROM;\
         TIMETO=_x_->TIMETO;\
         DESTBRANCHNO=_x_->DESTBRANCHNO;\
          strcpy(DAYOFWEEK,_x_->DAYOFWEEK);\
         WEEKDAY=_x_->WEEKDAY;\

 #define CUSTOMERROUTING_S390_COPY_TO_STRUCT(_x_) \
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->BRANCHNO=BRANCHNO;\
          _x_->TIMEFROM=TIMEFROM;\
          _x_->TIMETO=TIMETO;\
          _x_->DESTBRANCHNO=DESTBRANCHNO;\
          strcpy(_x_->DAYOFWEEK,DAYOFWEEK);\
          _x_->WEEKDAY=WEEKDAY;\



/* FunctionNumber-Define of CustomerRouting ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CustomerRouting *******************************/


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

class CCUSTOMERROUTING : public ppDadeVirtual
{
        //data members
        public:
                customerroutingS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<customerroutingS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<customerroutingS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<customerroutingS>; Strip(s); customerroutingS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<customerroutingS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<customerroutingS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<customerroutingS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetCustomerno() const   { return s.CUSTOMERNO; }
                short           GetBranchno() const     { return s.BRANCHNO; }
                long            GetTimefrom() const     { return s.TIMEFROM; }
                long            GetTimeto() const       { return s.TIMETO; }
                short           GetDestbranchno() const { return s.DESTBRANCHNO; }
                const char*     GetDayofweek(ppString& t) const         { t = s.DAYOFWEEK; t.erasespace(ppString::END); return t.c_str(); }
                short           GetWeekday() const      { return s.WEEKDAY; }
                const customerroutingS& GetStruct() const { return s; }
                void            SetCustomerno(long t) { s.CUSTOMERNO = t; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetTimefrom(long t) { s.TIMEFROM = t; }
                void            SetTimeto(long t) { s.TIMETO = t; }
                void            SetDestbranchno(short t) { s.DESTBRANCHNO = t; }
                void            SetDayofweek(const ppString& t) { ppGStrCopy(s.DAYOFWEEK,t.c_str() ,L_CUSTOMERROUTING_DAYOFWEEK); }
                void            SetWeekday(short t) { s.WEEKDAY = t; }
                void            SetStruct(const customerroutingS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CCUSTOMERROUTING()  //constructor
                {
                        ::buf_default((void *)&s, CUSTOMERROUTING_BES, CUSTOMERROUTING_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CCUSTOMERROUTING()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, CUSTOMERROUTING_BES, CUSTOMERROUTING_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CUSTOMERROUTING_BES, CUSTOMERROUTING_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, CUSTOMERROUTING_BES, CUSTOMERROUTING_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_CUSTOMERROUTING& d)
                {
#ifdef WIN32
                        ppGStripLast(d.DAYOFWEEK);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTOMERROUTING_BES, CUSTOMERROUTING_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of CUSTOMERROUTING **************************************/

 #define CUSTOMERROUTING_CREATE(x) exec sql create table x (\
         CUSTOMERNO integer default 0 not null,\
         BRANCHNO smallint default 0 not null,\
         TIMEFROM integer default 0 not null,\
         TIMETO integer default 0 not null,\
         DESTBRANCHNO smallint default 0 not null,\
         DAYOFWEEK char(2) default " " not null,\
         WEEKDAY smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of CUSTOMERROUTING ************************************/

 #define CUSTOMERROUTING_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_customerrout_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              DayOfWeek,\
              TimeFrom ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CUSTOMERROUTING ************************************/

 #define CUSTOMERROUTING_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_customerrout_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
