#ifndef __PP_ARTIKELZENTRALFR_H_
#define __PP_ARTIKELZENTRALFR_H_

/******************************************************************************/
/* u:\artikelzentralfr ********************************************************/
/******************************************************************************/

/* Length-Define of ARTIKELZENTRALFR ******************************************/

  #define L_ARTIKELZENTRALFR_ARTIKEL_NR 11
  #define L_ARTIKELZENTRALFR_ARTIKEL_MC 12
  #define L_ARTIKELZENTRALFR_ARTIKEL_NAME 30
  #define L_ARTIKELZENTRALFR_EINHEIT 9
  #define L_ARTIKELZENTRALFR_DARREICHFORM 3

/* Length/Count-Define of ARTIKELZENTRALFR ************************************/

  #define LS_ARTIKELZENTRALFR_ARTIKEL_NR 10 + 1
  #define LS_ARTIKELZENTRALFR_ARTIKEL_MC 12 + 1
  #define LS_ARTIKELZENTRALFR_ARTIKEL_NAME 30 + 1
  #define LS_ARTIKELZENTRALFR_EINHEIT 9 + 1
  #define LS_ARTIKELZENTRALFR_DARREICHFORM 3 + 1

  #define ARTIKELZENTRALFRARTIKEL_NR 0
  #define ARTIKELZENTRALFRARTIKEL_MC 1
  #define ARTIKELZENTRALFRARTIKEL_NAME 2
  #define ARTIKELZENTRALFREINHEIT 3
  #define ARTIKELZENTRALFRDARREICHFORM 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTIKELZENTRALFR_H
 #define ARTIKELZENTRALFR_ANZ ( sizeof(ARTIKELZENTRALFR_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTIKELZENTRALFR **********************************************/

 #define ARTIKELZENTRALFR_LISTE \
         ARTIKELZENTRALFR.ARTIKEL_NR,\
         ARTIKELZENTRALFR.ARTIKEL_MC,\
         ARTIKELZENTRALFR.ARTIKEL_NAME,\
         ARTIKELZENTRALFR.EINHEIT,\
         ARTIKELZENTRALFR.DARREICHFORM

 #define ARTIKELZENTRALFR_LISTE_390 \
         ARTIKEL_NR,\
         ARTIKEL_MC,\
         ARTIKEL_NAME,\
         EINHEIT,\
         DARREICHFORM

 #define ARTIKELZENTRALFR_PLISTE \
         "ARTIKELZENTRALFR.ARTIKEL_NR,"\
         "ARTIKELZENTRALFR.ARTIKEL_MC,"\
         "ARTIKELZENTRALFR.ARTIKEL_NAME,"\
         "ARTIKELZENTRALFR.EINHEIT,"\
         "ARTIKELZENTRALFR.DARREICHFORM"

 #define ARTIKELZENTRALFR_PELISTE \
         "ARTIKEL_NR,"\
         "ARTIKEL_MC,"\
         "ARTIKEL_NAME,"\
         "EINHEIT,"\
         "DARREICHFORM"

 #define ARTIKELZENTRALFR_UPDLISTE \
         "ARTIKEL_NR=?,"\
         "ARTIKEL_MC=?,"\
         "ARTIKEL_NAME=?,"\
         "EINHEIT=?,"\
         "DARREICHFORM=?"

/* SqlMacros-Define of ARTIKELZENTRALFR ***************************************/

 #define ARTIKELZENTRALFR_ZEIGER(x) \
         :x->ARTIKEL_NR,\
         :x->ARTIKEL_MC,\
         :x->ARTIKEL_NAME,\
         :x->EINHEIT,\
         :x->DARREICHFORM

 #define ARTIKELZENTRALFR_ZEIGERSEL(x) \
         :x->ARTIKEL_NR,\
         :x->ARTIKEL_MC,\
         :x->ARTIKEL_NAME,\
         :x->EINHEIT,\
         :x->DARREICHFORM

 #define ARTIKELZENTRALFR_UPDATE(x) \
         ARTIKELZENTRALFR.ARTIKEL_NR=:x->ARTIKEL_NR,\
         ARTIKELZENTRALFR.ARTIKEL_MC=:x->ARTIKEL_MC,\
         ARTIKELZENTRALFR.ARTIKEL_NAME=:x->ARTIKEL_NAME,\
         ARTIKELZENTRALFR.EINHEIT=:x->EINHEIT,\
         ARTIKELZENTRALFR.DARREICHFORM=:x->DARREICHFORM

/* SqlMacros390-Define of ARTIKELZENTRALFR ************************************/

 #define ARTIKELZENTRALFR_ZEIGER_390 \
         :ARTIKEL_NR,\
         :ARTIKEL_MC,\
         :ARTIKEL_NAME,\
         :EINHEIT,\
         :DARREICHFORM

 #define ARTIKELZENTRALFR_UPDATE_390 \
         ARTIKEL_NR=:ARTIKEL_NR,\
         ARTIKEL_MC=:ARTIKEL_MC,\
         ARTIKEL_NAME=:ARTIKEL_NAME,\
         EINHEIT=:EINHEIT,\
         DARREICHFORM=:DARREICHFORM

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTIKELZENTRALFR ***************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTIKELZENTRALFR {
         long ARTIKEL_NR;
         char ARTIKEL_MC[13];
         char ARTIKEL_NAME[31];
         char EINHEIT[10];
         char DARREICHFORM[4];
        } artikelzentralfrS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTIKELZENTRALFR {
         long ARTIKEL_NR;
         char ARTIKEL_MC[13];
         char ARTIKEL_NAME[31];
         char EINHEIT[10];
         char DARREICHFORM[4];

                        bool operator==(const N_ARTIKELZENTRALFR& right) const {
                        return(
                                ARTIKEL_NR == right.ARTIKEL_NR &&
                                !strcmp(ARTIKEL_MC, right.ARTIKEL_MC) &&
                                !strcmp(ARTIKEL_NAME, right.ARTIKEL_NAME) &&
                                !strcmp(EINHEIT, right.EINHEIT) &&
                                !strcmp(DARREICHFORM, right.DARREICHFORM)
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                ARTIKEL_NR = 0;
                                strcpy(ARTIKEL_MC, " " );
                                strcpy(ARTIKEL_NAME, " " );
                                strcpy(EINHEIT, " " );
                                strcpy(DARREICHFORM, " " );
#endif
                        }
         } artikelzentralfrS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTIKELZENTRALFR **********************************/

 struct S_ARTIKELZENTRALFR {
         char ARTIKEL_NR[11];
         char ARTIKEL_MC[12 + 1];
         char ARTIKEL_NAME[30 + 1];
         char EINHEIT[9 + 1];
         char DARREICHFORM[3 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTIKELZENTRALFR *****************/

 struct O_ARTIKELZENTRALFR {
         char ARTIKEL_NR[11];
         char ARTIKEL_MC[12];
         char ARTIKEL_NAME[30];
         char EINHEIT[9];
         char DARREICHFORM[3];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTIKELZENTRALFR ****************************/

 struct C_ARTIKELZENTRALFR {
         long ARTIKEL_NR;
         char ARTIKEL_MC[13];
         char ARTIKEL_NAME[31];
         char EINHEIT[10];
         char DARREICHFORM[4];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTIKELZENTRALFR **************************/

 struct I_ARTIKELZENTRALFR {
         short ARTIKEL_NR;
         short ARTIKEL_MC;
         short ARTIKEL_NAME;
         short EINHEIT;
         short DARREICHFORM;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTIKELZENTRALFR ************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTIKELZENTRALFR_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 12, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 9, 0 },
   { TYP_C, 3, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELZENTRALFR_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 12, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 9, 0 },
   { TYP_C, 3, 0 },
 };
#endif

/* description for datatypes of ARTIKELZENTRALFR ******************************/

 #define ARTIKELZENTRALFR_S390 \
         long ARTIKEL_NR; \
         char ARTIKEL_MC[13]; \
         char ARTIKEL_NAME[31]; \
         char EINHEIT[10]; \
         char DARREICHFORM[4]; \



/* Copy-Function Struct to single Data ARTIKELZENTRALFR ***********************/

 #define ARTIKELZENTRALFR_S390_COPY_TO_SINGLE(_x_) \
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
          strcpy(ARTIKEL_MC,_x_->ARTIKEL_MC);\
          strcpy(ARTIKEL_NAME,_x_->ARTIKEL_NAME);\
          strcpy(EINHEIT,_x_->EINHEIT);\
          strcpy(DARREICHFORM,_x_->DARREICHFORM);\

 #define ARTIKELZENTRALFR_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          strcpy(_x_->ARTIKEL_MC,ARTIKEL_MC);\
          strcpy(_x_->ARTIKEL_NAME,ARTIKEL_NAME);\
          strcpy(_x_->EINHEIT,EINHEIT);\
          strcpy(_x_->DARREICHFORM,DARREICHFORM);\



/* FunctionNumber-Define of artikelzentralfr **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of artikelzentralfr ******************************/


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

class CARTIKELZENTRALFR : public ppDadeVirtual
{
        //data members
        public:
                artikelzentralfrS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<artikelzentralfrS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<artikelzentralfrS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<artikelzentralfrS>; Strip(s); artikelzentralfrS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<artikelzentralfrS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<artikelzentralfrS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<artikelzentralfrS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetArtikel_nr() const   { return s.ARTIKEL_NR; }
                const char*     GetArtikel_mc(ppString& t) const        { t = s.ARTIKEL_MC; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetArtikel_name(ppString& t) const      { t = s.ARTIKEL_NAME; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetEinheit(ppString& t) const   { t = s.EINHEIT; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetDarreichform(ppString& t) const      { t = s.DARREICHFORM; t.erasespace(ppString::END); return t.c_str(); }
                const artikelzentralfrS& GetStruct() const { return s; }
                void            SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
                void            SetArtikel_mc(const ppString& t) { ppGStrCopy(s.ARTIKEL_MC,t.c_str() ,L_ARTIKELZENTRALFR_ARTIKEL_MC); }
                void            SetArtikel_name(const ppString& t) { ppGStrCopy(s.ARTIKEL_NAME,t.c_str() ,L_ARTIKELZENTRALFR_ARTIKEL_NAME); }
                void            SetEinheit(const ppString& t) { ppGStrCopy(s.EINHEIT,t.c_str() ,L_ARTIKELZENTRALFR_EINHEIT); }
                void            SetDarreichform(const ppString& t) { ppGStrCopy(s.DARREICHFORM,t.c_str() ,L_ARTIKELZENTRALFR_DARREICHFORM); }
                void            SetStruct(const artikelzentralfrS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CARTIKELZENTRALFR()  //constructor
                {
                        ::buf_default((void *)&s, ARTIKELZENTRALFR_BES, ARTIKELZENTRALFR_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CARTIKELZENTRALFR()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ARTIKELZENTRALFR_BES, ARTIKELZENTRALFR_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTIKELZENTRALFR_BES, ARTIKELZENTRALFR_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, ARTIKELZENTRALFR_BES, ARTIKELZENTRALFR_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ARTIKELZENTRALFR& d)
                {
#ifdef WIN32
                        ppGStripLast(d.ARTIKEL_MC);
                        ppGStripLast(d.ARTIKEL_NAME);
                        ppGStripLast(d.EINHEIT);
                        ppGStripLast(d.DARREICHFORM);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, ARTIKELZENTRALFR_BES, ARTIKELZENTRALFR_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ARTIKELZENTRALFR *************************************/

 #define ARTIKELZENTRALFR_CREATE(x) exec sql create table x (\
         ARTIKEL_NR integer default 0 not null,\
         ARTIKEL_MC char(12) default " " not null,\
         ARTIKEL_NAME char(30) default " " not null,\
         EINHEIT char(9) default " " not null,\
         DARREICHFORM char(3) default " " not null) in ksc extent size 3920 next size 392 lock mode row;



/* CreateIndexStatement of ARTIKELZENTRALFR ***********************************/

 #define ARTIKELZENTRALFR_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_zentralfr_1 on _X_(\
              artikel_nr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_zentralfr_2 on _X_(\
              artikel_mc ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTIKELZENTRALFR ***********************************/

 #define ARTIKELZENTRALFR_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_zentralfr_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_zentralfr_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
