#ifndef __PP_TARTNUM_H_
#define __PP_TARTNUM_H_

/******************************************************************************/
/* u:artikelnummern ***********************************************************/
/******************************************************************************/

/* Length-Define of ARTIKELNUMMERN ********************************************/

  #define L_ARTIKELNUMMERN_PZN 11
  #define L_ARTIKELNUMMERN_EAN 13
  #define L_ARTIKELNUMMERN_ARTIKEL_NR 11

/* Length/Count-Define of ARTIKELNUMMERN **************************************/

  #define LS_ARTIKELNUMMERN_PZN 10 + 1
  #define LS_ARTIKELNUMMERN_EAN 13 + 1
  #define LS_ARTIKELNUMMERN_ARTIKEL_NR 10 + 1

  #define ARTIKELNUMMERNPZN 0
  #define ARTIKELNUMMERNEAN 1
  #define ARTIKELNUMMERNARTIKEL_NR 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTIKELNUMMERN_H
 #define ARTIKELNUMMERN_ANZ ( sizeof(ARTIKELNUMMERN_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTIKELNUMMERN ************************************************/

 #define ARTIKELNUMMERN_LISTE \
         ARTIKELNUMMERN.PZN,\
         ARTIKELNUMMERN.EAN,\
         ARTIKELNUMMERN.ARTIKEL_NR

 #define ARTIKELNUMMERN_LISTE_390 \
         PZN,\
         EAN,\
         ARTIKEL_NR

 #define ARTIKELNUMMERN_PLISTE \
         "ARTIKELNUMMERN.PZN,"\
         "ARTIKELNUMMERN.EAN,"\
         "ARTIKELNUMMERN.ARTIKEL_NR"

 #define ARTIKELNUMMERN_PELISTE \
         "PZN,"\
         "EAN,"\
         "ARTIKEL_NR"

 #define ARTIKELNUMMERN_UPDLISTE \
         "PZN=?,"\
         "EAN=?,"\
         "ARTIKEL_NR=?"

/* SqlMacros-Define of ARTIKELNUMMERN *****************************************/

 #define ARTIKELNUMMERN_ZEIGER(x) \
         :x->PZN,\
         :x->EAN,\
         :x->ARTIKEL_NR

 #define ARTIKELNUMMERN_ZEIGERSEL(x) \
         :x->PZN,\
         :x->EAN,\
         :x->ARTIKEL_NR

 #define ARTIKELNUMMERN_UPDATE(x) \
         ARTIKELNUMMERN.PZN=:x->PZN,\
         ARTIKELNUMMERN.EAN=:x->EAN,\
         ARTIKELNUMMERN.ARTIKEL_NR=:x->ARTIKEL_NR

/* SqlMacros390-Define of ARTIKELNUMMERN **************************************/

 #define ARTIKELNUMMERN_ZEIGER_390 \
         :PZN,\
         :EAN,\
         :ARTIKEL_NR

 #define ARTIKELNUMMERN_UPDATE_390 \
         PZN=:PZN,\
         EAN=:EAN,\
         ARTIKEL_NR=:ARTIKEL_NR

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTIKELNUMMERN *****************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTIKELNUMMERN {
         long PZN;
         char EAN[14];
         long ARTIKEL_NR;
        } artikelnummernS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTIKELNUMMERN {
         long PZN;
         char EAN[14];
         long ARTIKEL_NR;

                        bool operator==(const N_ARTIKELNUMMERN& right) const {
                        return(
                                PZN == right.PZN &&
                                !strcmp(EAN, right.EAN) &&
                                ARTIKEL_NR == right.ARTIKEL_NR
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                PZN = 0;
                                strcpy(EAN, " " );
                                ARTIKEL_NR = 0;
#endif
                        }
         } artikelnummernS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTIKELNUMMERN ************************************/

 struct S_ARTIKELNUMMERN {
         char PZN[11];
         char EAN[13 + 1];
         char ARTIKEL_NR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTIKELNUMMERN *******************/

 struct O_ARTIKELNUMMERN {
         char PZN[11];
         char EAN[13];
         char ARTIKEL_NR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of ARTIKELNUMMERN *******************************/

 struct C_ARTIKELNUMMERN {
         long PZN;
         char EAN[14];
         long ARTIKEL_NR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of ARTIKELNUMMERN *****************************/

 struct I_ARTIKELNUMMERN {
         short PZN;
         short EAN;
         short ARTIKEL_NR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTIKELNUMMERN **************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTIKELNUMMERN_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 13, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELNUMMERN_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 13, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of ARTIKELNUMMERN ********************************/

 #define ARTIKELNUMMERN_S390 \
         long PZN; \
         char EAN[14]; \
         long ARTIKEL_NR; \



/* Copy-Function Struct to single Data ARTIKELNUMMERN *************************/

 #define ARTIKELNUMMERN_S390_COPY_TO_SINGLE(_x_) \
         PZN=_x_->PZN;\
          strcpy(EAN,_x_->EAN);\
         ARTIKEL_NR=_x_->ARTIKEL_NR;\

 #define ARTIKELNUMMERN_S390_COPY_TO_STRUCT(_x_) \
          _x_->PZN=PZN;\
          strcpy(_x_->EAN,EAN);\
          _x_->ARTIKEL_NR=ARTIKEL_NR;\



/* FunctionNumber-Define of artikelnummern ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of artikelnummern ********************************/


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
                virtual int SelList(int FetchRel = 1,int pos=0) = 0;
                virtual int SelListHist(int FetchRel = 1,int pos=0) = 0;
                virtual int SelListFuture(int FetchRel = 1,int pos=0) = 0;
                virtual int Load(int pos=0) = 0;
                virtual int Delete(int pos=0) = 0;
                virtual int Save(int pos=0) = 0;
};
#endif

class CARTIKELNUMMERN : public ppDadeVirtual
{
        //data members
        public:
                artikelnummernS s;
                int rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<artikelnummernS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<artikelnummernS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<artikelnummernS>; Strip(s); artikelnummernS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<artikelnummernS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<artikelnummernS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<artikelnummernS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetPzn() const  { return s.PZN; }
                const char*     GetEan(ppString& t) const       { t = s.EAN; t.erasespace(ppString::END); return t.c_str(); }
                long            GetArtikel_nr() const   { return s.ARTIKEL_NR; }
                const artikelnummernS& GetStruct() const { return s; }
                void            SetPzn(long t) { s.PZN = t; }
                void            SetEan(const ppString& t) { ppGStrCopy(s.EAN,t.c_str() ,L_ARTIKELNUMMERN_EAN); }
                void            SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
                void            SetStruct(const artikelnummernS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CARTIKELNUMMERN()  //constructor
                {
                        ::buf_default((void *)&s,ARTIKELNUMMERN_BES,ARTIKELNUMMERN_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CARTIKELNUMMERN()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ARTIKELNUMMERN_BES, ARTIKELNUMMERN_ANZ );
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc=::ServerNr(pos, fkt_nr, (void *)&s,ARTIKELNUMMERN_BES,ARTIKELNUMMERN_ANZ, error_msg);
                        #else
                        rc=::Server(fkt_nr, (void *)&s,ARTIKELNUMMERN_BES,ARTIKELNUMMERN_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ARTIKELNUMMERN& d)
                {
#ifdef WIN32
                        ppGStripLast(d.EAN);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc=::ServerNr(pos, FncNr, (void *)&s,ARTIKELNUMMERN_BES,ARTIKELNUMMERN_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ARTIKELNUMMERN ***************************************/

 #define ARTIKELNUMMERN_CREATE(x) exec sql create table x (\
         PZN integer default 0 not null,\
         EAN char(13) default " " not null,\
         ARTIKEL_NR integer default 0 not null) in ksc extent size 3920 next size 392 lock mode row;



/* CreateIndexStatement of ARTIKELNUMMERN *************************************/

 #define ARTIKELNUMMERN_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_artikelnummern_1 on _X_(\
              pzn ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_artikelnummern_2 on _X_(\
              artikel_nr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_artikelnummern_3 on _X_(\
              ean ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTIKELNUMMERN *************************************/

 #define ARTIKELNUMMERN_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_artikelnummern_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_artikelnummern_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_artikelnummern_3;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
