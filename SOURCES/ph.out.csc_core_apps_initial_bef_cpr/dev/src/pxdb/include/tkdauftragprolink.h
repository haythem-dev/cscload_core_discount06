#ifndef __PP_KDAUFTRAGPROLINK_H_
#define __PP_KDAUFTRAGPROLINK_H_

/******************************************************************************/
/* u:\KdauftragProLink ********************************************************/
/******************************************************************************/

/* Length-Define of KDAUFTRAGPROLINK ******************************************/

  #define L_KDAUFTRAGPROLINK_KDAUFTRAGNR 11
  #define L_KDAUFTRAGPROLINK_INVOICENUMBERPRO 15
  #define L_KDAUFTRAGPROLINK_INVOICENUMBER 15
  #define L_KDAUFTRAGPROLINK_DATEPROFORMA 11
  #define L_KDAUFTRAGPROLINK_KDAUFTRAGNRPRO 11

/* Length/Count-Define of KDAUFTRAGPROLINK ************************************/

  #define LS_KDAUFTRAGPROLINK_KDAUFTRAGNR 10 + 1
  #define LS_KDAUFTRAGPROLINK_INVOICENUMBERPRO 15 + 1
  #define LS_KDAUFTRAGPROLINK_INVOICENUMBER 15 + 1
  #define LS_KDAUFTRAGPROLINK_DATEPROFORMA 10 + 1
  #define LS_KDAUFTRAGPROLINK_KDAUFTRAGNRPRO 10 + 1

  #define KDAUFTRAGPROLINKKDAUFTRAGNR 0
  #define KDAUFTRAGPROLINKINVOICENUMBERPRO 1
  #define KDAUFTRAGPROLINKINVOICENUMBER 2
  #define KDAUFTRAGPROLINKDATEPROFORMA 3
  #define KDAUFTRAGPROLINKKDAUFTRAGNRPRO 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KDAUFTRAGPROLINK_H
 #define KDAUFTRAGPROLINK_ANZ ( sizeof(KDAUFTRAGPROLINK_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGPROLINK **********************************************/

 #define KDAUFTRAGPROLINK_LISTE \
         KDAUFTRAGPROLINK.KDAUFTRAGNR,\
         KDAUFTRAGPROLINK.INVOICENUMBERPRO,\
         KDAUFTRAGPROLINK.INVOICENUMBER,\
         KDAUFTRAGPROLINK.DATEPROFORMA,\
         KDAUFTRAGPROLINK.KDAUFTRAGNRPRO

 #define KDAUFTRAGPROLINK_LISTE_390 \
         KDAUFTRAGNR,\
         INVOICENUMBERPRO,\
         INVOICENUMBER,\
         DATEPROFORMA,\
         KDAUFTRAGNRPRO

 #define KDAUFTRAGPROLINK_PLISTE \
         "KDAUFTRAGPROLINK.KDAUFTRAGNR,"\
         "KDAUFTRAGPROLINK.INVOICENUMBERPRO,"\
         "KDAUFTRAGPROLINK.INVOICENUMBER,"\
         "KDAUFTRAGPROLINK.DATEPROFORMA,"\
         "KDAUFTRAGPROLINK.KDAUFTRAGNRPRO"

 #define KDAUFTRAGPROLINK_PELISTE \
         "KDAUFTRAGNR,"\
         "INVOICENUMBERPRO,"\
         "INVOICENUMBER,"\
         "DATEPROFORMA,"\
         "KDAUFTRAGNRPRO"

 #define KDAUFTRAGPROLINK_UPDLISTE \
         "KDAUFTRAGNR=?,"\
         "INVOICENUMBERPRO=?,"\
         "INVOICENUMBER=?,"\
         "DATEPROFORMA=?,"\
         "KDAUFTRAGNRPRO=?"

/* SqlMacros-Define of KDAUFTRAGPROLINK ***************************************/

 #define KDAUFTRAGPROLINK_ZEIGER(x) \
         :x->KDAUFTRAGNR,\
         :x->INVOICENUMBERPRO,\
         :x->INVOICENUMBER,\
         :x->DATEPROFORMA,\
         :x->KDAUFTRAGNRPRO

 #define KDAUFTRAGPROLINK_ZEIGERSEL(x) \
         :x->KDAUFTRAGNR,\
         :x->INVOICENUMBERPRO,\
         :x->INVOICENUMBER,\
         :x->DATEPROFORMA,\
         :x->KDAUFTRAGNRPRO

 #define KDAUFTRAGPROLINK_UPDATE(x) \
         KDAUFTRAGPROLINK.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
         KDAUFTRAGPROLINK.INVOICENUMBERPRO=:x->INVOICENUMBERPRO,\
         KDAUFTRAGPROLINK.INVOICENUMBER=:x->INVOICENUMBER,\
         KDAUFTRAGPROLINK.DATEPROFORMA=:x->DATEPROFORMA,\
         KDAUFTRAGPROLINK.KDAUFTRAGNRPRO=:x->KDAUFTRAGNRPRO

/* SqlMacros390-Define of KDAUFTRAGPROLINK ************************************/

 #define KDAUFTRAGPROLINK_ZEIGER_390 \
         :KDAUFTRAGNR,\
         :INVOICENUMBERPRO,\
         :INVOICENUMBER,\
         :DATEPROFORMA,\
         :KDAUFTRAGNRPRO

 #define KDAUFTRAGPROLINK_UPDATE_390 \
         KDAUFTRAGNR=:KDAUFTRAGNR,\
         INVOICENUMBERPRO=:INVOICENUMBERPRO,\
         INVOICENUMBER=:INVOICENUMBER,\
         DATEPROFORMA=:DATEPROFORMA,\
         KDAUFTRAGNRPRO=:KDAUFTRAGNRPRO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KDAUFTRAGPROLINK ***************************************/

 #ifndef TRANSCLASS
 typedef struct N_KDAUFTRAGPROLINK {
         long KDAUFTRAGNR;
         char INVOICENUMBERPRO[16];
         char INVOICENUMBER[16];
         long DATEPROFORMA;
         long KDAUFTRAGNRPRO;
        } kdauftragprolinkS;
 #else /*TRANSCLASS*/
 typedef struct N_KDAUFTRAGPROLINK {
         long KDAUFTRAGNR;
         char INVOICENUMBERPRO[16];
         char INVOICENUMBER[16];
         long DATEPROFORMA;
         long KDAUFTRAGNRPRO;

                        bool operator==(const N_KDAUFTRAGPROLINK& right) const {
                        return(
                                KDAUFTRAGNR == right.KDAUFTRAGNR &&
                                !strcmp(INVOICENUMBERPRO, right.INVOICENUMBERPRO) &&
                                !strcmp(INVOICENUMBER, right.INVOICENUMBER) &&
                                DATEPROFORMA == right.DATEPROFORMA &&
                                KDAUFTRAGNRPRO == right.KDAUFTRAGNRPRO
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                KDAUFTRAGNR = 0;
                                strcpy(INVOICENUMBERPRO, " " );
                                strcpy(INVOICENUMBER, " " );
                                DATEPROFORMA = 0;
                                KDAUFTRAGNRPRO = 0;
#endif
                        }
         } kdauftragprolinkS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGPROLINK **********************************/

 struct S_KDAUFTRAGPROLINK {
         char KDAUFTRAGNR[11];
         char INVOICENUMBERPRO[15 + 1];
         char INVOICENUMBER[15 + 1];
         char DATEPROFORMA[11];
         char KDAUFTRAGNRPRO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGPROLINK *****************/

 struct O_KDAUFTRAGPROLINK {
         char KDAUFTRAGNR[11];
         char INVOICENUMBERPRO[15];
         char INVOICENUMBER[15];
         char DATEPROFORMA[11];
         char KDAUFTRAGNRPRO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGPROLINK ****************************/

 struct C_KDAUFTRAGPROLINK {
         long KDAUFTRAGNR;
         char INVOICENUMBERPRO[16];
         char INVOICENUMBER[16];
         long DATEPROFORMA;
         long KDAUFTRAGNRPRO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGPROLINK **************************/

 struct I_KDAUFTRAGPROLINK {
         short KDAUFTRAGNR;
         short INVOICENUMBERPRO;
         short INVOICENUMBER;
         short DATEPROFORMA;
         short KDAUFTRAGNRPRO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGPROLINK ************************************/

#if defined (BUF_DESC)
 static struct buf_desc KDAUFTRAGPROLINK_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDAUFTRAGPROLINK_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of KDAUFTRAGPROLINK ******************************/

 #define KDAUFTRAGPROLINK_S390 \
         long KDAUFTRAGNR; \
         char INVOICENUMBERPRO[16]; \
         char INVOICENUMBER[16]; \
         long DATEPROFORMA; \
         long KDAUFTRAGNRPRO; \



/* Copy-Function Struct to single Data KDAUFTRAGPROLINK ***********************/

 #define KDAUFTRAGPROLINK_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
          strcpy(INVOICENUMBERPRO,_x_->INVOICENUMBERPRO);\
          strcpy(INVOICENUMBER,_x_->INVOICENUMBER);\
         DATEPROFORMA=_x_->DATEPROFORMA;\
         KDAUFTRAGNRPRO=_x_->KDAUFTRAGNRPRO;\

 #define KDAUFTRAGPROLINK_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          strcpy(_x_->INVOICENUMBERPRO,INVOICENUMBERPRO);\
          strcpy(_x_->INVOICENUMBER,INVOICENUMBER);\
          _x_->DATEPROFORMA=DATEPROFORMA;\
          _x_->KDAUFTRAGNRPRO=KDAUFTRAGNRPRO;\



/* FunctionNumber-Define of KdauftragProLink **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of KdauftragProLink ******************************/


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

class CKDAUFTRAGPROLINK : public ppDadeVirtual
{
        //data members
        public:
                kdauftragprolinkS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<kdauftragprolinkS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragprolinkS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<kdauftragprolinkS>; Strip(s); kdauftragprolinkS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragprolinkS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<kdauftragprolinkS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<kdauftragprolinkS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetKdauftragnr() const  { return s.KDAUFTRAGNR; }
                const char*     GetInvoicenumberpro(ppString& t) const  { t = s.INVOICENUMBERPRO; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetInvoicenumber(ppString& t) const     { t = s.INVOICENUMBER; t.erasespace(ppString::END); return t.c_str(); }
                long            GetDateproforma() const { return s.DATEPROFORMA; }
                long            GetKdauftragnrpro() const       { return s.KDAUFTRAGNRPRO; }
                const kdauftragprolinkS& GetStruct() const { return s; }
                void            SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
                void            SetInvoicenumberpro(const ppString& t) { ppGStrCopy(s.INVOICENUMBERPRO,t.c_str() ,L_KDAUFTRAGPROLINK_INVOICENUMBERPRO); }
                void            SetInvoicenumber(const ppString& t) { ppGStrCopy(s.INVOICENUMBER,t.c_str() ,L_KDAUFTRAGPROLINK_INVOICENUMBER); }
                void            SetDateproforma(long t) { s.DATEPROFORMA = t; }
                void            SetKdauftragnrpro(long t) { s.KDAUFTRAGNRPRO = t; }
                void            SetStruct(const kdauftragprolinkS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CKDAUFTRAGPROLINK()  //constructor
                {
                        ::buf_default((void *)&s, KDAUFTRAGPROLINK_BES, KDAUFTRAGPROLINK_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CKDAUFTRAGPROLINK()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, KDAUFTRAGPROLINK_BES, KDAUFTRAGPROLINK_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGPROLINK_BES, KDAUFTRAGPROLINK_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGPROLINK_BES, KDAUFTRAGPROLINK_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_KDAUFTRAGPROLINK& d)
                {
#ifdef WIN32
                        ppGStripLast(d.INVOICENUMBERPRO);
                        ppGStripLast(d.INVOICENUMBER);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGPROLINK_BES, KDAUFTRAGPROLINK_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of KDAUFTRAGPROLINK *************************************/

 #define KDAUFTRAGPROLINK_CREATE(x) exec sql create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         INVOICENUMBERPRO char(15) default " " not null,\
         INVOICENUMBER char(15) default " " not null,\
         DATEPROFORMA integer default 0 not null,\
         KDAUFTRAGNRPRO integer default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of KDAUFTRAGPROLINK ***********************************/

 #define KDAUFTRAGPROLINK_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_kdaufpro_1 on _X_(\
              kdauftragnr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGPROLINK ***********************************/

 #define KDAUFTRAGPROLINK_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kdaufpro_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
