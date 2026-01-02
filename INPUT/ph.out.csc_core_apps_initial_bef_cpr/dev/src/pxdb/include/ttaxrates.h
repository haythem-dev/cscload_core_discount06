#ifndef __PP_TAXRATES_H_
#define __PP_TAXRATES_H_

/******************************************************************************/
/* v:\TaxRates ****************************************************************/
/******************************************************************************/

/* Length-Define of TAXRATES **************************************************/

  #define L_TAXRATES_TAXLEVEL 6
  #define L_TAXRATES_SALESTAXRATE 5
  #define N_TAXRATES_SALESTAXRATE 2

/* Length/Count-Define of TAXRATES ********************************************/

  #define LS_TAXRATES_TAXLEVEL 5 + 1
  #define LS_TAXRATES_SALESTAXRATE 5 + 2

  #define TAXRATESTAXLEVEL 0
  #define TAXRATESSALESTAXRATE 1

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define TAXRATES_H
 #define TAXRATES_ANZ ( sizeof(TAXRATES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TAXRATES ******************************************************/

 #define TAXRATES_LISTE \
         TAXRATES.TAXLEVEL,\
         TAXRATES.SALESTAXRATE

 #define TAXRATES_LISTE_390 \
         TAXLEVEL,\
         SALESTAXRATE

 #define TAXRATES_PLISTE \
         "TAXRATES.TAXLEVEL,"\
         "TAXRATES.SALESTAXRATE"

 #define TAXRATES_PELISTE \
         "TAXLEVEL,"\
         "SALESTAXRATE"

 #define TAXRATES_UPDLISTE \
         "TAXLEVEL=?,"\
         "SALESTAXRATE=?"

/* SqlMacros-Define of TAXRATES ***********************************************/

 #define TAXRATES_ZEIGER(x) \
         :x->TAXLEVEL,\
         :x->SALESTAXRATE

 #define TAXRATES_ZEIGERSEL(x) \
         :x->TAXLEVEL,\
         :x->SALESTAXRATE

 #define TAXRATES_UPDATE(x) \
         TAXRATES.TAXLEVEL=:x->TAXLEVEL,\
         TAXRATES.SALESTAXRATE=:x->SALESTAXRATE

/* SqlMacros390-Define of TAXRATES ********************************************/

 #define TAXRATES_ZEIGER_390 \
         :TAXLEVEL,\
         :SALESTAXRATE

 #define TAXRATES_UPDATE_390 \
         TAXLEVEL=:TAXLEVEL,\
         SALESTAXRATE=:SALESTAXRATE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of TAXRATES ***********************************************/

 #ifndef TRANSCLASS
 typedef struct N_TAXRATES {
         short TAXLEVEL;
         double SALESTAXRATE;
        } taxratesS;
 #else /*TRANSCLASS*/
 typedef struct N_TAXRATES {
         short TAXLEVEL;
         double SALESTAXRATE;

                        bool operator==(const N_TAXRATES& right) const {
                        return(
                                TAXLEVEL == right.TAXLEVEL &&
                                SALESTAXRATE == right.SALESTAXRATE
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                TAXLEVEL = 0;
                                SALESTAXRATE = 0;
#endif
                        }
         } taxratesS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TAXRATES ******************************************/

 struct S_TAXRATES {
         char TAXLEVEL[7];
         char SALESTAXRATE[5 + 2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of TAXRATES *************************/

 struct O_TAXRATES {
         char TAXLEVEL[7];
         char SALESTAXRATE[5];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of TAXRATES ************************************/

 struct C_TAXRATES {
         short TAXLEVEL;
         double SALESTAXRATE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of TAXRATES **********************************/

 struct I_TAXRATES {
         short TAXLEVEL;
         short SALESTAXRATE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TAXRATES ********************************************/

#if defined (BUF_DESC)
 static struct buf_desc TAXRATES_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc TAXRATES_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
 };
#endif

/* description for datatypes of TAXRATES **************************************/

 #define TAXRATES_S390 \
         short TAXLEVEL; \
         double SALESTAXRATE; \



/* Copy-Function Struct to single Data TAXRATES *******************************/

 #define TAXRATES_S390_COPY_TO_SINGLE(_x_) \
         TAXLEVEL=_x_->TAXLEVEL;\
         SALESTAXRATE=_x_->SALESTAXRATE;\

 #define TAXRATES_S390_COPY_TO_STRUCT(_x_) \
          _x_->TAXLEVEL=TAXLEVEL;\
          _x_->SALESTAXRATE=SALESTAXRATE;\



/* FunctionNumber-Define of TaxRates ******************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of TaxRates **************************************/


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

class CTAXRATES : public ppDadeVirtual
{
        //data members
        public:
                taxratesS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<taxratesS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<taxratesS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<taxratesS>; Strip(s); taxratesS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<taxratesS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<taxratesS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<taxratesS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetTaxlevel() const     { return s.TAXLEVEL; }
                double          GetSalestaxrate() const { return s.SALESTAXRATE; }
                const taxratesS& GetStruct() const { return s; }
                void            SetTaxlevel(short t) { s.TAXLEVEL = t; }
                void            SetSalestaxrate(double t) { s.SALESTAXRATE = t; }
                void            SetStruct(const taxratesS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CTAXRATES()  //constructor
                {
                        ::buf_default((void *)&s, TAXRATES_BES, TAXRATES_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CTAXRATES()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, TAXRATES_BES, TAXRATES_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, TAXRATES_BES, TAXRATES_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, TAXRATES_BES, TAXRATES_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_TAXRATES& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, TAXRATES_BES, TAXRATES_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of TAXRATES *********************************************/

 #define TAXRATES_CREATE(x) exec sql create table x (\
         TAXLEVEL smallint default 0 not null,\
         SALESTAXRATE decimal(5,2) default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of TAXRATES *******************************************/

 #define TAXRATES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_taxrates_1 on _X_(\
              TaxLevel ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TAXRATES *******************************************/

 #define TAXRATES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_taxrates_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
